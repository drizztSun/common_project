"""
562. Longest Line of Consecutive One in Matrix

Given a 01 matrix M, find the longest line of consecutive one in the matrix. The line could be horizontal, vertical, diagonal or anti-diagonal.
Example:
Input:
[[0,1,1,0],
 [0,1,1,0],
 [0,0,0,1]]
Output: 3
Hint: The number of elements in the given matrix will not exceed 10,000.

"""


class LongestLineOfConsecuiveOne:


    """
        Approach 2: Using 3D Dynamic Programming
        Algorithm

        Instead of traversing over the same matrix multiple times, we can keep a track of the 1' along all the lines possible while traversing the matrix once only.
        In order to do so, we make use of a 4mn4mn sized dpdp array. Here, dp[0]dp[0], dp[1]dp[1], dp[2]dp[2] ,dp[3]dp[3] are used to store the maximum number of continuous 1's found so far along the Horizontal,
        Vertical, Diagonal and Anti-diagonal lines respectively. e.g. dp[i][j][0]dp[i][j][0] is used to store the number of continuous 1's found so far(till we reach the element M[i][j]M[i][j]),
        along the horizontal lines only.

        Thus, we traverse the matrix MM in a row-wise fashion only but, keep updating the entries for every dpdp appropriately.

        The following image shows the filled dpdp values for this matrix:

         0 1 1 0

         0 1 1 0

         0 0 1 1

        Complexity Analysis

        Time complexity : O(mn). We traverse the entire matrix once only.

        Space complexity : O(mn). dpdp array of size 4mn4mn is used, where mm and nn are the number of rows ans coloumns of the matrix.
    """

    def doit_dpLine(self, Matrix: list) -> int:

        M, N = len(Matrix), len(Matrix[0])
        ans = 0
        dp = [[[0 for _ in range(4)] for _ in range(N+1)] for _ in range(2)]

        for i in range(M):

            index = i % 2

            for j in range(1, N+1):

                dp[index][j] = [0, 0, 0, 0]

                if Matrix[i][j-1] == 1:
                    dp[index][j][0] = dp[index][j-1][0] + 1
                    dp[index][j][1] = dp[1-index][j][1] + 1
                    dp[index][j][2] = dp[1-index][j-1][2] + 1
                    dp[index][j][3] = 1 if j == N else (dp[1-index][j+1][3] + 1)

                ans = max(ans, max(dp[index][j]))

        return ans

    """
        Approach 3: Using 2D Dynamic Programming
        Algorithm
        
        In the previous approach, we can observe that the current dpdp entry is dependent only on the entries of the just previous corresponding dpdp row. Thus, 
        instead of maintaining a 2-D dpdp matrix for each kind of line of 1's possible, we can use a 1-d array for each one of them, and update the corresponding entries in the same row during each row's traversal. 
        Taking this into account, the previous 3-D dpdp matrix shrinks to a 2-D dpdp matrix now. The rest of the procedure remains same as the previous approach.
        
        Complexity Analysis
        
        Time complexity : O(mn). The entire matrix is traversed once only.
        
        Space complexity : O(n). dpdp array of size 4n4n is used, where nn is the number of columns of the matrix.

    """


if __name__ == '__main__':

    LongestLineOfConsecuiveOne().doit_dpLine([[0,1,1,0],[0,1,1,0],[0,0,0,1]])

    LongestLineOfConsecuiveOne().doit_dpLine([[1,1,0,0,1,0,0,1,1,0],
                                              [1,0,0,1,0,1,1,1,1,1],
                                              [1,1,1,0,0,1,1,1,1,0],
                                              [0,1,1,1,0,1,1,1,1,1],
                                              [0,0,1,1,1,1,1,1,1,0],
                                              [1,1,1,1,1,1,0,1,1,1],
                                              [0,1,1,1,1,1,1,0,0,1],
                                              [1,1,1,1,1,0,0,1,1,1],
                                              [0,1,0,1,1,0,1,1,1,1],
                                              [1,1,1,0,1,0,1,1,1,1]])