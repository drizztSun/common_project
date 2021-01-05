"""
1124. Longest Well-Performing Interval

We are given hours, a list of the number of hours worked per day for a given employee.

A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.

A well-performing interval is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.

Return the length of the longest well-performing interval.

 

Example 1:

Input: hours = [9,9,6,0,6,6,9]
Output: 3
Explanation: The longest well-performing interval is [9,9,6].
 

Constraints:

1 <= hours.length <= 10000
0 <= hours[i] <= 16
"""


class LongestWellPerformingInterval:

    def longestWPI(self, hours: list) -> int:
        
        pos, s = {}, 0
        ans = 0
        
        for i in range(len(hours)):
            
            s += 1 if hours[i] > 8 else -1
            
            if s > 0:
                ans = i + 1
                continue
                
            if s not in pos:
                pos[s] = i
                
            if (s - 1) in pos:
                ans = max(ans, i - pos[s-1])
                
        return ans