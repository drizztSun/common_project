


# 174. Dungeon Game

# The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon.
# The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned
# in the top-left room and must fight his way through the dungeon to rescue the princess.

# The knight has an initial health point represented by a positive integer.
# If at any point his health point drops to 0 or below, he dies immediately.

# Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms;
# other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

# In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.


# Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

# For example, given the dungeon below, the initial health of the knight must be at least 7 
# if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

# -2 (K)  -3	3
# -5	  -10	1
# 10	  30	-5 (P)

# Notes:

# The knight's health has no upper bound.
# Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room
# where the princess is imprisoned.


class CalculateMinimumHP:


# seems pretty simple� and easy to understand explanations�

# It is easy to know that at grid P, since " at any point his health point drops to 0 or below,
# he dies immediately", the remaining health value should be at least 1, that is, initialHealth + dungeon >= 1,
# we have initialHealth = max(1, 1 - dungeon[i][j]). (Notice, at any grid, the initial health should be at least 1
# (for example, test case [1,0,0] require initial health 1 even though it has positive remaining health at grid[0][1] and grid[0][2])

# Similarly, to satisfy the initial health of dungeon[i][j], the initial health of dungeon[i-1][j] 
#(or dungeon[i][j-1]) should be at least initialHealth[i-1][j] + dungeon[i-1][j] = initialHealth[i][j], that is,
# initialHealth[i][j] = initialHealth[i][j] - dungeon[i-1][j].

# In addition, if grid[i][j] can go both grid[i+1][j] and grid[i][j+1] to P,
# we should choose a path with less initial health between grid[i+1][j] and grid[i][j+1] since it require less initial health of grid[i][j].
# We can simply code the solution by having the dynamic programming equations.

    # <DP>
    def doit(self, dungeon):
        """
        :type dungeon: List[List[int]]
        :rtype: int
        """
        m, n = len(dungeon), len(dungeon[0])

        DP = [ [ [0] for j in range(n)] for i in range(m)]

        for i in reversed(range(m)):

            for j in reversed(range(n)):

                if i == m-1 and j == n-1:

                    DP[i][j] = max(1, 1 - dungeon[i][j])

                elif i == m-1:
                    
                    DP[i][j] = max(1,  DP[i][j+1] - dungeon[i][j])

                elif j == n-1:
    
                    DP[i][j] = max(1, DP[i+1][j] - dungeon[i][j])

                else:

                    DP[i][j] = max(1, min(DP[i+1][j], DP[i][j+1]) - dungeon[i][j])
                        
        return DP[0][0]


    def doit(self, dungeon):
        """
        :type dungeon: List[List[int]]
        :rtype: int
        """
        n = len(dungeon[0])
        needed = [2**31]*(n-1)+[1]

        for i in dungeon[::-1]:
            for j in range(n)[::-1]:
                needed[j]=max(min(needed[j:j+2])-i[j],1)

        return needed[0]



    def doit1(self, dungeon):
        """
        :type dungeon: List[List[int]]
        :rtype: int
        """
        m, n = len(dungeon), len(dungeon[0])
        DP = [ [ [ [0, 0] ] for j in range(n)] for i in range(m)]
        
        for i in range(m):
            for j in range(n):

                if i == 0 and j == 0:
                    DP[0][0] = max(0, 1 - dungeon[i][j])
        
                elif i == 0:
                    DP[i][j] = max(DP[i][j-1], DP[i][j-1] - dungeon[i][j])

                elif j == 0:
                    DP[i][j] = max(DP[i-1][j], DP[i-1][j] - dungeon[i][j])

                else:
                    Less = min(DP[i-1][j], DP[i][j-1])
                    DP[i][j] = max(Less, Less - dungeon[i][j])

        return DP[-1][-1]

if __name__=="__main__":


    A = [ [-2,  -3,  3], 
          [-5, -10,  1],
          [10,  30, -5]]

    res = CalculateMinimumHP().doit(A)

    pass    