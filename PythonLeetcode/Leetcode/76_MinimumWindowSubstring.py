import os
import collections

# 76. Minimum Window Substring
# Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

# For example,
# S = "ADOBECODEBANC"
# T = "ABC"
# Minimum window is "BANC".

# Note:
# If there is no such window in S that covers all characters in T, return the empty string "".
# If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.



class minWindow(object):
    def doit(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        need, missing = collections.Counter(t), len(t)
        i = I = J = 0

        for j, c in enumerate(s, 1):
            missing -= need[c] > 0
            need[c] -= 1

            if not missing:
                while i < j and need[s[i]] < 0:
                    need[s[i]] += 1
                    i += 1

                if not J or j - i <= J - I:
                    I, J = i, j

        return s[I:J]


    def doit1(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        counter = [0 for _ in range(128)]
        i = I = J = 0
        for c in t:
            counter[ord(c)] += 1

        missing = len(t)
        for j, c in enumerate(s, 1):

            if counter[ord(c)] > 0:
                missing -= 1

            counter[ord(c)] -= 1

            if not missing:
                while i < j and counter[ord(s[i])] < 0:
                    counter[ord(s[i])] += 1
                    i += 1
                    
                if not J or j - i < J - I:
                    J, I = j, i

        return s[I:J]


    def doit3(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        num_char = len(t)
        size = len(s)
        length_substring = size+1
        start, end, pointer = 0, 0, 0
        dict_char_freq = {}
        
        for char in t:
            if char not in dict_char_freq: dict_char_freq[char] = 1
            else: dict_char_freq[char]+=1
        
        while end < size:
            if s[end] in dict_char_freq:
                if dict_char_freq[s[end]]>0: num_char-=1
                dict_char_freq[s[end]]-=1
            #else: dict_char_freq[s[end]] = -1
            end+=1
            while num_char==0:
                if end-start<length_substring:
                    pointer=start
                    length_substring=end-start
                
                if s[start] in dict_char_freq:
                    dict_char_freq[s[start]]+=1
                    if dict_char_freq[s[start]]>0: num_char+=1
                #else: dict_char_freq[s[start]]=1
                #if s[start] in dict_char_freq and dict_char_freq[s[start]]>0: num_char+=1
                start+=1

        return "" if length_substring == size+1 else s[pointer:pointer+length_substring]

    def doit2(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        if len(s) < len(t):
            return ""

        nums = [0 for _ in range(128)]
        for c in t:
            nums[ord(c)] += 1

        i, j = 0, 0
        min_len, imin, count = len(s) + 1, 0, len(t)
        
        while i < len(s) and j < len(s):
            
            if count > 0:
                
                c = ord(s[i])
                nums[c] -= 1
                
                if nums[c] >= 0:
                    count -= 1

                i += 1

            else:
                if min_len > i - j + 1:
                    min_len = i - j + 1
                    imin = j
                    
                c = ord(s[j])
                nums[c] += 1
                
                if nums[c] > 0:
                    count += 1
                    
                j += 1
                
                
        return "" if min_len == len(s) + 1 else s[imin: imin + min_len]


if __name__=="__main__":


    res = minWindow().doit("ab", "b")


    res = minWindow().doit("bdab", "ab")

    res = minWindow().doit1("bdab", "ab")

    res = minWindow().doit1("ab", "b")

    res = minWindow().doit("a", "a")

    res = minWindow().doit("a", "b")
    
    res = minWindow().doit("ADOBECODEBANC", "ABC")


    pass   
    