


# 316. Remove Duplicate Letters


# Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once.
# You must make sure your result is the smallest in lexicographical order among all possible results.

# Example:
# Given "bcabc"
# Return "abc"

# Given "cbacdcbc"
# Return "acdb"

# Credits:
# Special thanks to @dietpepsi for adding this problem and creating all test cases.


# TODO

# <hard> <important>
class removeDuplicateLetters(object):



# Given the string s, the greedy choice (i.e., the leftmost letter in the answer) is the smallest s[i], s.t.
# the suffix s[i … ] contains all the unique letters. (Note that, when there are more than one smallest s[i]'s,
# we choose the leftmost one. Why? Simply consider the example: “abcacb”.)

# After determining the greedy choice s[i], we get a new string s’ from s by

# removing all letters to the left of s[i],
# removing all s[i]'s from s.
# We then recursively solve the problem w.r.t. s’.

# The runtime is O(26 * n) = O(n).

    # <recursion> <greedy>
    def doit(self, s):
        """
        :type s: str
        :rtype: str
        """
        def removeleftLetters(s):

            if len(s) == 0:
                return ''

            D = [0 for _ in range(28)]

            for i, c in enumerate(s):
                D[ord(c) - ord('a')] += 1
        
            pos = 0 
            for i , c in enumerate(s):
                # The leftmost position of the minimum letter
                if c < s[pos]:
                    pos = i

                # Make sure that the letters after current i is a non-complete string
                # continuing to search result in this field is wasting time
                D[ord(c) - ord('a')] -= 1
                if D[ord(c) - ord('a')] == 0:
                    break

            return s[pos] + removeleftLetters(s[pos+1:].replace(s[pos], ''))

        return removeleftLetters(s)

    # 
    def doit(self, s):
        """
        :type s: str
        :rtype: str
        """
        last_loc={}
        for i,c in enumerate(s):
            last_loc[c]=i
        
        stack=''
        for i,c in enumerate(s):
            if c not in stack:
                while stack and stack[-1] > c and last_loc[stack[-1]] > i:
                    stack=stack[:-1]
                stack+=c
                
        return stack
    
        


if __name__=="__main__":

    res = removeDuplicateLetters().doit("abacb") # abc

    res = removeDuplicateLetters().doit("bcabc") # abc

    res = removeDuplicateLetters().doit("cbacdcbc") # acdb


    pass