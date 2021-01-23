"""
1654. Minimum Jumps to Reach Home

A certain bug's home is on the x-axis at position x. Help them get there from position 0.

The bug jumps according to the following rules:

It can jump exactly a positions forward (to the right).
It can jump exactly b positions backward (to the left).
It cannot jump backward twice in a row.
It cannot jump to any forbidden positions.
The bug may jump forward beyond its home, but it cannot jump to positions numbered with negative integers.

Given an array of integers forbidden, where forbidden[i] means that the bug cannot jump to the position forbidden[i], and integers a, b, and x, 
return the minimum number of jumps needed for the bug to reach its home. If there is no possible sequence of jumps that lands the bug on position x, return -1.

 

Example 1:

Input: forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
Output: 3
Explanation: 3 jumps forward (0 -> 3 -> 6 -> 9) will get the bug home.
Example 2:

Input: forbidden = [8,3,16,6,12,20], a = 15, b = 13, x = 11
Output: -1
Example 3:

Input: forbidden = [1,6,2,14,5,17,4], a = 16, b = 9, x = 7
Output: 2
Explanation: One jump forward (0 -> 16) then one jump backward (16 -> 7) will get the bug home.
 

Constraints:

1 <= forbidden.length <= 1000
1 <= a, b, forbidden[i] <= 2000
0 <= x <= 2000
All the elements in forbidden are distinct.
Position x is not forbidden.
"""


class MinimumHumpsToReachHome:


    def doit_bfs_1(self, forbidden: list, a: int, b: int, x: int) -> int:
        from collections import deque
        MAX_LIM = max(x, max(forbidden)) + a + b
        forbidden = set(forbidden)
        visited = set([0])
        queue = deque()        
        queue.append((0, 0))
        h = 0
        
        while queue:
            
            size = len(queue)
            
            for _ in range(size):
                pos, back = queue.popleft()
                if pos == x:
                    return h
                forw, backw = pos + a, pos - b
                if backw >= 0 and back == 0 and backw not in forbidden and backw not in visited:
                    queue.append((backw, 1))
                    visited.add(backw)
                    
                if forw <= MAX_LIM and forw not in forbidden and forw not in visited:
                    queue.append((forw, 0))
                    visited.add(forw)
                
            h += 1
        return -1

    def doit_bfs(self, forbidden: list, a: int, b: int, x: int) -> int:

        from collections import deque
        
        furthest =max(x, max(forbidden)) + a + b
        visited = set()
        for c in forbidden:
            visited.add((c, 1))
            visited.add((c, 0))
            
        queue = deque([(0, 0)])
        visited.add((0, 0))
        steps = 0
        
        while queue:
            
            size = len(queue)
            
            for _ in range(size):
            
                cur, back = queue.popleft()
                if cur == x: 
                    return steps
                
                if back == 0:
                    if cur + a <= furthest and (cur + a) not in visited and (cur + a) not in forbidden:
                        visited.add((cur + a, 0))
                        queue.append((cur + a, 0))
                        
                    if cur - b > 0 and (cur - b, 1) not in visited:
                        visited.add((cur - b, 1))
                        queue.append((cur - b, 1))
                
                if back == 1:
                    if cur + a <= furthest and (cur + a, 0 ) not in visited:
                        visited.add((cur + a, 0))
                        queue.append((cur + a, 0))
                    
            steps += 1

        return -1