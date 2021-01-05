"""
249. Group Shifted Strings

Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:

"abc" -> "bcd" -> ... -> "xyz"
Given a list of non-empty strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.

Example:

Input: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"],
Output: 
[
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
]

"""

class GroupShiftedStrings:

    def doit_(self, strings: list) -> list:
        from collections import defaultdict
        
        buff = defaultdict(list)
        for s in strings:
            
            if len(s) == 1:
                buff[-1].append(s)
            else:
                key = ''
                for i in range(len(s)-1):
                    diff = str((ord(s[i+1]) - ord(s[i]) + 26) % 26)
                    if len(diff) < 2:
                        diff = '0' + diff
                    key += diff
                    
                buff[key].append(s)
            
        return buff.values()