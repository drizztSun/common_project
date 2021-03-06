"""
1536. Minimum Swaps to Arrange a Binary Grid

Given an n x n binary grid, in one step you can choose two adjacent rows of the grid and swap them.

A grid is said to be valid if all the cells above the main diagonal are zeros.

Return the minimum number of steps needed to make the grid valid, or -1 if the grid cannot be valid.

The main diagonal of a grid is the diagonal that starts at cell (1, 1) and ends at cell (n, n).

 

Example 1:


Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
Output: 3
Example 2:


Input: grid = [[0,1,1,0],[0,1,1,0],[0,1,1,0],[0,1,1,0]]
Output: -1
Explanation: All rows are similar, swaps have no effect on the grid.
Example 3:


Input: grid = [[1,0,0],[1,1,0],[1,1,1]]
Output: 0
 

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 200
grid[i][j] is 0 or 1


"""

class MinimumSwapsToArragge:

    """
        First, count the number of trailing 0s for each row as zeros.
        Second, for i-th row, which needs n - i - 1 trailing 0s, just find the nearest j that j >= i and zeros[j] >= n - i - 1, 
        then the swap operation needed is j - i - 1, so that j-th row move forward to i-th row. If deque is applied to zeros, then zeros denotes the rows not used. 
        for i-th row, find the nearest j that zeros[j] >= n - i - 1, then the swap operation needed is j. Then pop j-th since it is used.
    """
    def doit_(self, grid: list) -> int:
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        zeros = []
        need = n - 1
        ans = 0

        for i in range(n):
            cur_zeros = n
            for j in range(n - 1, -1, -1):
                if grid[i][j] == 1:
                    cur_zeros = n - j - 1
                    break
            zeros.append(cur_zeros)

        while zeros:
            for i in range(len(zeros)):
                if zeros[i] >= need:
                    need -= 1
                    break
            else:
                return -1
            ans += i
            zeros.pop(i)
        return ans

    """
                1536.Minimum-Swaps-to-Arrange-a-Binary-Grid
        本题先进行一下转换。将每行末尾的零的个数统计一下，得到数组zeros，即zeros[i]表示第i行末尾的零的个数。我们的目标是将zeros通过adjacent swap操作，变成一个数组target，其中target[i]>=n-1-i. 求最小的操作数。

        我们首先考虑target[0]，它的要求最高（需要有n-1个零）。我们考察所有的行，看看有哪些满足条件。加入有a和b两行满足条件，即zeros[a]>=n-1，zeros[b]>=n-1，那么我们应该选择将哪一行挪到第0行的位置上来呢？我们不妨举个例子：

        X X X a X b X
        如果我们选择将第b行提到最前面，那么需要操作5次得到

        b X X X a X X   (1)
        如果我们选择将第a行提到最前面，那么需要操作3次得到

        a X X X X b X   (2)
        别停，我们如果对(2)继续操作1次（将b前移一位）能得到

        a X X X b X X   (3)
        我们比较一下(1)和(3)。我们发现对于第0行的处理，两种方案都满足条件。唯一的区别是，第一种方案第4行是zeros[a]，第二种方案第4行是zeros[b]。
        
        但是由于zeros[a]和zeros[b]都是大于等于n-1的，而除了target[0]之外的target[i]的要求都不到n-1，
        
        所以这两行（a和b）对于以后的安排而言都是“溢价”的，即“价值”是没有区别的。但是第一种方案需要5次操作，第二种方案只需要4次操作。

        所以我们得到一个贪心的结论：当我们处理target[i]时需要找某个zeros[j]>=n-1-i时，只要从i开始往后顺次查找第一个满足zeros[j]>=n-1-i的位置即可。然后将j所对应的行提前到第i行。然后处理target[i+1]，不断重复。

    """
    def doit_greedy(self, grid: list) -> int:
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        zeros = [0] * n

        for i in range(n):
            cur_zeros = 0
            for j in range(n - 1, -1, -1):
                if grid[i][j] == 1:
                    break
                cur_zeros += 1
            zeros[i] = cur_zeros
            
        ans = 0
        for i in range(n):

            need = n - 1 - i

            for j in range(i, n):
                if zeros[j] >= need:
                    break
            else:
                return -1

            ans += j - i
            temp = zeros[j]
            for k in reversed(range(i+1, j+1)):
                zeros[k] = zeros[k-1]
            zeros[i] = temp
            
        return ans
        