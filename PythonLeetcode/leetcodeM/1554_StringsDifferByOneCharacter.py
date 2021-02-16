"""
1554. Strings Differ by One Character


Given a list of strings dict where all the strings are of the same length.

Return True if there are 2 strings that only differ by 1 character in the same index, otherwise return False.

Follow up: Could you solve this problem in O(n*m) where n is the length of dict and m is the length of each string.

 

Example 1:

Input: dict = ["abcd","acbd", "aacd"]
Output: true
Explanation: Strings "abcd" and "aacd" differ only by one character in the index 1.
Example 2:

Input: dict = ["ab","cd","yz"]
Output: false
Example 3:

Input: dict = ["abcd","cccc","abyd","abab"]
Output: true
 

Constraints:

Number of characters in dict <= 10^5
dict[i].length == dict[j].length
dict[i] should be unique.
dict[i] contains only lowercase English letters.

"""


class StringsDifferByOneCharater:

    def doit_(self, dict: list) -> bool:
        
        visited = set()
        
        for c in dict:
            
            for i in range(len(c)):
                
                target = c[:i] + '*' + c[i+1:]
                
                if target in visited: return True
                
                visited.add(target)
                
        return False


    def doit_hashtable(self, dict: list) -> bool:
        
        n = len(dict)
        if n < 2: return False

        m = len(dict[0])
        
        for i in range(m):
        
            valids = set()

            for word in dict:

                s = word[:i] + word[i + 1:]
        
                if s in valids: return True
        
                valids.add(s)
        
        return False