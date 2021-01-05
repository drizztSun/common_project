"""
567. Permutation in String

Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. 
In other words, one of the first string's permutations is the substring of the second string.

 

Example 1:

Input: s1 = "ab" s2 = "eidbaooo"
Output: True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input:s1= "ab" s2 = "eidboaoo"
Output: False
 

Constraints:

The input strings only contain lower case letters.
The length of both given strings is in range [1, 10,000].

"""


class PermutationInStrings:

    """
    Approach #6 Optimized Sliding Window [Accepted]:
    Algorithm

    The last approach can be optimized, if instead of comparing all the elements of the hashmaps for every updated s2maps2map corresponding to every window of s2s2 considered, 
    we keep a track of the number of elements which were already matching in the earlier hashmap and update just the count of matching elements when we shift the window towards the right.

    To do so, we maintain a countcount variable, which stores the number of characters(out of the 26 alphabets), which have the same frequency of occurence in s1 and the current window in s2. 
    When we slide the window, if the deduction of the last element and the addition of the new element leads to a new frequency match of any of the characters, 
    we increment the countcount by 1. If not, we keep the countcount intact. But, if a character whose frequency was the same earlier(prior to addition and removal) is added, 
    it now leads to a frequency mismatch which is taken into account by decrementing the same countcount variable. If, after the shifting of the window, the countcount evaluates to 26, 
    it means all the characters match in frequency totally. So, we return a True in that case immediately.
    """

    def doit_slidingwindow(self, s1: str, s2: str) -> bool:
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """
        from collections import defaultdict
        n1, n2 = len(s1), len(s2)
        
        if n1 > n2:
            return False
        
        m1, m2 = defaultdict(int), defaultdict(int)
        for c in s1:
            m1[c] += 1
        
        for c in s2[:n1]:
            m2[c] += 1
        
        for i in range(n1, n2):

            if m1 == m2:
                return True
            
            last = i - n1
            m2[s2[last]] -= 1
            if m2[s2[last]] == 0:
                del m2[s2[last]]
                
            m2[s2[i]] += 1
            
        return m1 == m2