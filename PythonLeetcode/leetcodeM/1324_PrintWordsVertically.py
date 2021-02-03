"""
1324. Print Words Vertically

Given a string s. Return all the words vertically in the same order in which they appear in s.
Words are returned as a list of strings, complete with spaces when is necessary. (Trailing spaces are not allowed).
Each word would be put on only one column and that in one column there will be only one word.

 

Example 1:

Input: s = "HOW ARE YOU"
Output: ["HAY","ORO","WEU"]
Explanation: Each word is printed vertically. 
 "HAY"
 "ORO"
 "WEU"
Example 2:

Input: s = "TO BE OR NOT TO BE"
Output: ["TBONTB","OEROOE","   T"]
Explanation: Trailing spaces is not allowed. 
"TBONTB"
"OEROOE"
"   T"
Example 3:

Input: s = "CONTEST IS COMING"
Output: ["CIC","OSO","N M","T I","E N","S G","T"]
 

Constraints:

1 <= s.length <= 200
s contains only upper case English letters.
It's guaranteed that there is only one space between 2 words.

"""
import itertools

class PrintWordVertically:

    """
        With matrices or so, we'd use zip to transpose (= flip so that rows become columns and columns become rows). 
        But zip stops at the shortest, and here the columns aren't all the same length. So we use zip_longest instead and tell it to fill with spaces.

        Nice version in three steps:
    """
    def printVertically(self, s):
        columns = s.split()
        rows = itertools.zip_longest(*columns, fillvalue=' ')
        return [''.join(row).rstrip() for row in rows]

    # Oneliner (which is what I wrote during the contest):
    def printVertically(self, s):
        return [''.join(r).rstrip() for r in itertools.zip_longest(*s.split(), fillvalue=' ')]


    def doit_(self, s: str) -> list:
        
        lst = s.split(' ')
        max_len = max([len(x) for x in lst])
        n = len(lst)
        
        ans = []
        for i in range(max_len):
            ans.append([lst[j][i] if i < len(lst[j]) else ' ' for j in range(n)])    
        
        ans = [''.join(lst).rstrip() for lst in ans]
        
        return ans
        
        
        