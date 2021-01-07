"""
151. Reverse Words in a String

Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.

Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.

 

Example 1:

Input: s = "the sky is blue"
Output: "blue is sky the"
Example 2:

Input: s = "  hello world  "
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.
Example 3:

Input: s = "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.
Example 4:

Input: s = "  Bob    Loves  Alice   "
Output: "Alice Loves Bob"
Example 5:

Input: s = "Alice does not even like bob"
Output: "bob like even not does Alice"
 

Constraints:

1 <= s.length <= 104
s contains English letters (upper-case and lower-case), digits, and spaces ' '.
There is at least one word in s.
 

Follow up:

Could you solve it in-place with O(1) extra space?

"""

class ReverseWords(object):


    """
        Approach 1: Built-in Split + Reverse
        Complexity Analysis
        Time complexity: O(N), where N is a number of characters in the input string.
        Space complexity: O(N), to store the result of split by spaces.
    """
    def doit_(self, s):
        """
        :type s: str
        :rtype: str
        """
        return " ".join(reversed(s.split()))

    """
        Approach 2: Reverse the Whole String and Then Reverse Each Word
        The implementation of this approach will be different for Java/Python (= immutable strings) and C++ (= mutable strings).
        In the case of immutable strings one has first to convert string into mutable data structure, and hence it makes sense to trim all spaces during that conversion.

        Complexity Analysis

        Time complexity: O(N).
        Space complexity: O(N).
    """
    def doit_(self, s):

        def trim_spaces(s: str) -> list:
            left, right = 0, len(s) - 1
            # remove leading spaces
            while left <= right and s[left] == ' ':
                left += 1
            
            # remove trailing spaces
            while left <= right and s[right] == ' ':
                right -= 1
            
            # reduce multiple spaces to single one
            output = []
            while left <= right:
                if s[left] != ' ':
                    output.append(s[left])
                elif output[-1] != ' ':
                    output.append(s[left])
                left += 1
            
            return output
            
        def reverse(l: list, left: int, right: int) -> None:
            while left < right:
                l[left], l[right] = l[right], l[left]
                left, right = left + 1, right - 1
                
        def reverse_each_word(l: list) -> None:
            n = len(l)
            start = end = 0
            
            while start < n:
                # go to the end of the word
                while end < n and l[end] != ' ':
                    end += 1
                # reverse the word
                reverse(l, start, end - 1)
                # move to the next word
                start = end + 1
                end += 1
                    
        # converst string to char array 
        # and trim spaces at the same time
        l = trim_spaces(s)
        
        # reverse the whole string
        reverse(l, 0, len(l) - 1)
        
        # reverse each word
        reverse_each_word(l)
        
        return ''.join(l)

    """
        Approach 3: Deque of Words
    """
    def reverseWords(self, s: str) -> str:
        from collections import deque
        left, right = 0, len(s) - 1
        # remove leading spaces
        while left <= right and s[left] == ' ':
            left += 1
        
        # remove trailing spaces
        while left <= right and s[right] == ' ':
            right -= 1
            
        d, word = deque(), []
        # push word by word in front of deque
        while left <= right:
            if s[left] == ' ' and word:
                d.appendleft(''.join(word))
                word = []
            elif s[left] != ' ':
                word.append(s[left])
            left += 1
        d.appendleft(''.join(word))
        
        return ' '.join(d)

    def doit_(self, s):
        """
        :type s: str
        :rtype: str
        """
        i, res, tempt = 0, '', ''
        while i < len(s):
            if s[i] != ' ':
                tempt += s[i]
                
            if i == len(s) - 1 or s[i] == ' ':
                if tempt:
                    if res:
                        res = tempt + ' ' + res
                    else:
                        res = tempt
                        
                    tempt = ''
            i += 1

        return res
        