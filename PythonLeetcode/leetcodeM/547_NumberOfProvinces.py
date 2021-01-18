"""
547. Number of Provinces


There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.

A province is a group of directly or indirectly connected cities and no other cities outside of the group.

You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.

Return the total number of provinces.

 

Example 1:


Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2
Example 2:


Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
 

Constraints:

1 <= n <= 200
n == isConnected.length
n == isConnected[i].length
isConnected[i][j] is 1 or 0.
isConnected[i][i] == 1
isConnected[i][j] == isConnected[j][i]


"""


class NumberOfProvice:

    def doit_bfs(self, M: list) -> int:

        from collections import deque
        
        circles = 0
        visited = set()
        N = len(M)
        
        for i in range(N):
            
            if i not in visited:

                visited.add(i)
                
                qu = deque([i])
                
                while qu:
                    
                    c = qu.popleft()
                    
                    for j in range(N):
                
                        if M[c][j] == 1 and j not in visited:
                
                            qu.append(j)
                
                            visited.add(j)
                
                circles += 1
                
        return circles