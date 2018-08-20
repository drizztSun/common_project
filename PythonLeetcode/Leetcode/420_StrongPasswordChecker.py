



# 420. Strong Password Checker


# A password is considered strong if below conditions are all met:

# It has at least 6 characters and at most 20 characters.
# It must contain at least one lowercase letter, at least one uppercase letter, and at least one digit.
# It must NOT contain three repeating characters in a row ("...aaa..." is weak, but "...aa...a..." is strong, assuming other conditions are met).
# Write a function strongPasswordChecker(s), that takes a string s as input, and return the MINIMUM change required to make s a strong password. If s is already strong, return 0.

# Insertion, deletion or replace of any one character are all considered as one change.



# <important>


class strongPasswordChecker:
    def doit1(self, s):
        """
        :type s: str
        :rtype: int
        """
        hLowerCase, hUpperCase, Digit = False, False, False
        length = len(s)
        repeated = []
        buff = []

        for i, c in enumerate(s):
            
            if c.isdigit():
                Digit = True
            if c.islower():
                hLowerCase = True
            if c.isupper():
                hUpperCase = True

            if buff:
                if c == buff[-1]:
                    buff.append(c)
                    
                if c != buff[-1] or i == len(s)-1:
                    if len(buff) > 2:
                        repeated.append(buff)
                    buff = []

            if not buff:
                buff.append(c)

        if 6 <= len(s) <= 20 and hLowerCase and hUpperCase and Digit and not repeated:
            return 0

        added, removed, changed = 0, 0, 0
        added = [hLowerCase, hUpperCase, Digit].count(False)

        for c in repeated:
            changed += len(c) // 3
            
        if len(s) < 6:
            added = max(6 - len(s) + changed, added)
            changed = 0

        elif len(s) > 20:
            delete = len(s) - 20
            removed = max(delete, changed, added)
            changed = 0
            added = 0
        else: 
            added = max(changed, added)
            changed = 0
        
        return added + removed + changed





# I’ve separated the problem into three cases:
# (1) s.length() < 6
# (2) 6 <= s.length() <= 20
# (3) s.length() > 20

# Let’s look at case (1) first. If s.length() < 6, we know we have room to insert some more letters into s. Question is how to use the insertions effectively to reduce the number of potential replacements. I’m using a greedy approach for this one: I’m inserting one char between the second and third chars whenever I see a repetition of 3 letters as substring.

# e.g. Say we have room to insert some chars in string and we see a substring of "aaaa". I’ll insert a 'B' to make it "aaBaa" to break the 3-char repetition, thus reducing potential replacement by 1. And we’ll do this until we can’t insert any more chars into s. When we reach this point, we’ll start dealing with case (2)

# For case (2), I still follow a greedy approach. I’m simply searching for 3-char repetitions, and replacing one of the chars to break the repetition.
# e.g. If we see a substring of "aaaa", we’ll make it "aaBa".

# My code deals with (1) and (2) together as s.length() <= 20.

# Case (3) is a little bit tricky because simple greedy doesn’t work any more.
# When s.length() > 20, we want to delete some chars instead of inserting chars to reduce potential replacements. Question is the same: how to do it effectively? Let’s do some observations here:

# Say len is the length of each repetition.
# (a) len % 3 only has three possible values, namely 0, 1 and 2.
# (b) Minimum number of replacements needed to break each repetition is len / 3.
# © Based on (a) and (b), we know that deletion can reduce replacements only if the deletion can change the value of len / 3
# (d) Based on ©, we know if we want to reduce 1 replacement, we need 1 deletion for len % 3 == 0, and 2 deletions for len % 3 == 1, and 3 deletions for len % 3 == 2.

# Given above observations, I simply implemented the solution to do (d).

#Also note that missing of upper case char, lower case char, or digit can always be resolved by insertion or replacement.


    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        deleteTarget, addTarget = max(0, len(s) - 20), max(0, 6 - len(s))
        needDigit, needUpper, needLower = 1, 1, 1
        toAdd, toReplace = 0, 0

        # ##################################
        # For cases of s.length() <= 20
        # ##################################
        l, r = 0, 0
        for r in range(len(s)):

            if s[r].isdigit():
                needDigit = 0

            elif s[r].isupper():
                needUpper = 0

            elif s[r].islower():
                needLower = 0

            if r - l == 2:                                # if it's a three-letter window
                if s[r] == s[l+1] and s[l+1] == s[l]:     # found a three-repeating substr
                    if toAdd < addTarget:                 # insert letter to break repetition if possible 
                        toAdd += 1                        # replace current word to avoid three repeating chars
                        l = r                             # keep the window with no more than 3 letters
                    else:
                        toReplace += 1
                        l = r + 1
                else:
                    l += 1

        if len(s) <= 20:
            return max(addTarget + toReplace, needDigit + needUpper + needLower)

        ######################################
        #  For cases of s.length() > 20 
        ######################################
        toReplace, toDelete = 0, 0
        l = 0
        # reset toReplace
        # to record repetitions with (length % 3) == 0, 1 or 2. record all repetion frequencies
        replaceLength = [{}, {}, {}]
        for r in range(len(s)+1):
            if r == len(s) or s[r] != s[l]:
                length = r - l
                if length > 2:
                    replaceLength[length % 3][length] = replaceLength[length % 3].get(length, 0) + 1
                l = r


        # Use deletions to minimize replacements, following below orders:
        # (1) Try to delete one letter from repetitions with (length % 3) == 0. Each deletion decreases replacement by 1
        # (2) Try to delete two letters from repetitions with (length % 3) == 1. Each deletion decreases repalcement by 1
        # (3) Try to delete multiple of three letters from repetions with (length % 3) == 2. Each deletion (of three 
        # letters) decreases repalcements by 1
        for i in range(3):
            for c in replaceLength[i].keys():
                if i < 2:
                    numLetter = i + 1
                    # dec is the number of repetitions we'll delete from
                    dec = min(replaceLength[i][c],  (deleteTarget - toDelete) // numLetter)
                    # update number of repetitions left
                    toDelete += dec * numLetter
                    replaceLength[i][c] -= dec

                    # after letters deleted, it fits in the group where (length % 3) == 2
                    if c - numLetter > 2:
                        replaceLength[2][c - numLetter] = replaceLength[2].get(c - numLetter, 0) + dec

                # record number of replacements needed
                # note if len is the length of repetition, we need (len / 3) number of replacements
                toReplace += replaceLength[i][c] * (c//3)
            
        # try to delete multiple of three letters as many as possible            
        dec = (deleteTarget - toDelete) // 3

        toReplace -= dec
        toDelete -= dec * 3

        return deleteTarget + max(toReplace, needDigit + needLower + needUpper)
                    



    def doit1(self, s):
        """
        :type s: str
        :rtype: int
        """
        lowerCase = False
        upperCase = False
        digit = False
        slen = len(s)
        print('strlen:',slen)
        diverseChange = 0
        repeatAdd = 0
        repeatChange = {}
        repeatChange[0] = 0
        repeatChange[1] = 0
        repeatChange[2] = 0
        repeatDel = 0
        repeatReplace = 0
        lenAdd = 6 - slen
        lenDel = slen - 20
        
        # if slen < 6:  # all cases can be solved by adding
        # if 6 < slen < 20: # all cases can be solved be replace
        # if slen > 20: # using delete to cover as much replace as possible
        
        count = 1
        pre = ''
        for r in s:
            if not lowerCase and (r >= 'a' and r <= 'z'):
                lowerCase = True
            if not upperCase and (r >= 'A' and r <= 'Z'):
                upperCase = True
            if not digit and (r >= '0' and r <= '9'):
                digit = True
            if pre == r:
                count += 1
            else:
                if count >= 3:
                    repeatAdd += (count-1) // 2
                    while(count >= 3):
                        tmpdel = count%3
                        repeatChange[tmpdel] += 1
                        count -= tmpdel+1
                count = 1
            pre = r

        if count >= 3:
            repeatAdd += (count-1) // 2
            while(count >= 3):
                tmpdel = count%3
                repeatChange[tmpdel] += 1
                count -= tmpdel+1
        # if we want to reduce 1 replacement, 
        # we need 1 deletion for len % 3 == 0, 
        # and 2 deletions for len % 3 == 1, 
        # and 3 deletions for len % 3 == 2
        repeatDel = lenDel
        for i in range(3):
            print('lenDel',lenDel,'repeatChange',repeatChange)
            if lenDel >= repeatChange[i]*(i+1):
                lenDel -= repeatChange[i]*(i+1)
                repeatChange[i] = 0
            elif lenDel > 0:
                repeatChange[i] -= lenDel//(i+1)
                lenDel = lenDel % (i+1)
            repeatReplace += repeatChange[i]

        if not lowerCase:
            diverseChange += 1
        if not upperCase:
            diverseChange += 1
        if not digit:
            diverseChange += 1

        if slen < 6:
            print('<6:','lenAdd',lenAdd,'diverseChange',diverseChange,'repeatAdd',repeatAdd)
            return max(lenAdd,diverseChange,repeatAdd)
            repeat = repeatAdd
        elif slen > 20:

            print('>20:','lenDel',lenDel,'repeatDel',repeatDel,'repeatReplace',repeatReplace,'diverseChange',diverseChange)
            return repeatDel + max(repeatReplace,diverseChange)
        else:
            print('6~20:','repeatReplace',repeatReplace,'diverseChange',diverseChange)
            return max(repeatReplace,diverseChange)   


if __name__=="__main__":

    res = strongPasswordChecker().doit("")

    res = strongPasswordChecker().doit("aa")
    
    res = strongPasswordChecker().doit("aaa")
    
    res = strongPasswordChecker().doit("aaaa")
    
    res = strongPasswordChecker().doit("aaaaa")

    res = strongPasswordChecker().doit("aaabbb")


    res = strongPasswordChecker().doit("aaAA11")

    res = strongPasswordChecker().doit("aaaaaaaaaaaaaaaaaaaaa")


    res = strongPasswordChecker().doit("aaaaaaaaaaaaaaaaaaaaabbbccccdddddeeeeeeffffffff")

    res = strongPasswordChecker().doit("ABABABABABABABABABAB1") #2

    pass