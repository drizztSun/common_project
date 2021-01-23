"""
1647. Minimum Deletions to Make Character Frequencies Unique


A string s is called good if there are no two different characters in s that have the same frequency.

Given a string s, return the minimum number of characters you need to delete to make s good.

The frequency of a character in a string is the number of times it appears in the string. For example, in the string "aab", the frequency of 'a' is 2, while the frequency of 'b' is 1.

 

Example 1:

Input: s = "aab"
Output: 0
Explanation: s is already good.
Example 2:

Input: s = "aaabbbcc"
Output: 2
Explanation: You can delete two 'b's resulting in the good string "aaabcc".
Another way it to delete one 'b' and one 'c' resulting in the good string "aaabbc".
Example 3:

Input: s = "ceabaacb"
Output: 2
Explanation: You can delete both 'c's resulting in the good string "eabaab".
Note that we only care about characters that are still in the string at the end (i.e. frequency of 0 is ignored).
 

Constraints:

1 <= s.length <= 10^5
s contains only lowercase English letters.

"""

class MinimumDeletionsToMakeCharaterFrequenceUnique:

    def doit_hashtable(self, s: str) -> int:
        
        from collections import Counter
        
        cnt = Counter(s)
        values = sorted(cnt.values())
        ans, seen = 0, set() 
        
        for i in range(len(values)):
            
            if i > 0 and values[i] == values[i-1]:
                tmp = values[i]
                while tmp in seen and tmp > 0:
                    tmp -= 1
                ans += values[i] - tmp
                seen.add(tmp)
                continue
                
            seen.add(values[i])
            
        return ans

    def doit_heap(self, s):
        from collections import Counter
        from heapq import heappush, heappop
        freq = Counter(s)
        heap = []
        for key, value in freq.items():
            heappush(heap, (-value, key))
            
        top, ans = heappop(heap)[0], 0
        top = -top
        while heap:
            v = heappop(heap)[0]
            v = -v
            if top > 0:
                if v > top:
                    ans += (v - top) + 1
                    top -= 1
                elif v == top:
                    ans += 1
                    top = v - 1
                else:
                    top = v
            else:
                ans += v
        return ans