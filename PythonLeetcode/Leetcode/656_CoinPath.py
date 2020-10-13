"""
656. Coin Path

Given an array A (index starts at 1) consisting of N integers: A1, A2, ..., AN and an integer B.
The integer B denotes that from any place (suppose the index is i) in the array A,
you can jump to any one of the place in the array A indexed i+1, i+2, …, i+B if this place can be jumped to.
Also, if you step on the index i, you have to pay Ai coins. If Ai is -1, it means you can’t jump to the place indexed i in the array.

Now, you start from the place indexed 1 in the array A, and your aim is to reach the place indexed N using the minimum coins.
You need to return the path of indexes (starting from 1 to N) in the array you should take to get to the place indexed N using minimum coins.

If there are multiple paths with the same cost, return the lexicographically smallest such path.

If it's not possible to reach the place indexed N then you need to return an empty array.

Example 1:

Input: [1,2,4,-1,2], 2
Output: [1,3,5]


Example 2:

Input: [1,2,4,-1,2], 1
Output: []


Note:

Path Pa1, Pa2, ..., Pan is lexicographically smaller than Pb1, Pb2, ..., Pbm,
if and only if at the first i where Pai and Pbi differ, Pai < Pbi; when no such i exists, then n < m.
A1 >= 0. A2, ..., AN (if exist) will in the range of [-1, 100].
Length of A is in the range of [1, 1000].
B is in the range of [1, 100].

"""


class CheapestJump:

    """
    Approach #2 Using Memoization [Accepted]
    Algorithm

    In the recursive solution just discussed, a lot of duplicate function calls are made, since we are considering the same index through multiple paths.
    To remove this redundancy, we can make use of memoization.

    We keep a memomemo array, such that memo[i]memo[i] is used to store the minimum cost of jumps to reach the end of the array AA.
    Whenever the value for any index is calculated once, it is stored in its appropriate location.
    Thus, next time whenever the same function call is made, we can return the result directly from this memomemo array, pruning the search space to a great exte

    Complexity Analysis

    Time complexity : O(nB). memo array of size nn is filled only once. We also do a traversal over the nextnext array,
    which will go upto BB steps. Here, nn refers to the number of nodes in the given tree.

    Space complexity : O(n). The depth of the recursive tree can grow upto nn. nextnext array of size nn is used.
    """
    def doit_dp_dfs(self, A, B):
        """
        :type A: List[int]
        :type B: int
        :rtype: List[int]
        """
        path = [-1 for _ in range(len(A))]

        def dfs(pos, path, memo):

            if pos in memo:
                return memo[pos]

            if pos == len(A) - 1:
                return A[pos]

            res = float('inf')
            for j in range(pos+1, pos+B+1):

                if j == len(A):
                    break

                if A[j] != -1:
                    d = dfs(j, path, memo)
                    if d < res:
                        res = d
                        path[pos] = j

            res += A[pos]
            memo[pos] = res
            return res

        if A[-1] == -1:
            return []

        dfs(0, path, {})
        res = []
        i = 0
        while 0 <= i < len(path):
            res.append(i+1)
            i = path[i]

        return [] if res[-1] != len(A) else res

    """
    Approach #3 Using Dynamic Programming [Accepted]
    Algorithm
    
    From the solutions discussed above, we can observe that the cost of jumping till the end of the array A 
    starting from the index ii is only dependent on the elements following the index ii and not the ones before it. 
    This inspires us to make use of Dynamic Programming to solve the current problem.
    
    We again make use of a next array to store the next jump locations. We also make use of a dp with the same size as that of the given AA array. 
    dp[i]dp[i] is used to store the minimum cost of jumping till the end of the array AA, starting from the index ii. 
    We start with the last index as the current index and proceed backwards for filling the nextnext and dpdp array.
    
    With ii as the current index, we consider all the next possible positions from i+1, i+2,..., i+B, and determine the position, j, 
    which leads to a minimum cost of reaching the end of AA, which is given by A[i]+dp[j]A[i]+dp[j]. We update next[i]next[i] with this corresponding index. 
    We also update dp[i]dp[i] with the minimum cost, to be used by the previous indices' cost calculations.
    
    At the end, we again jump over the indices as per the next array and put these indices in the resres array to be returned.
    Complexity Analysis

    Time complexity : O(nB). We need to consider all the possible BB positions for every current index considered in the A array. 
    Here, A refers to the number of elements in AA.
    
    Space complexity : O(n). dp and nextnext array of size nn are used.
    """
    def doit_dp(self, A, B):

        N = len(A)
        dp = [-1 for _ in range(N)]
        path = [-1 for _ in range(N)]
        dp[-1] = A[-1]

        for i in range(N-2, -1, -1):
            if A[i] == -1:
                continue

            for j in range(i + 1, min(len(A), i + B + 1)):
                if dp[j] == -1:
                    continue

                if dp[i] == -1 or dp[i] > dp[j]:
                    dp[i] = dp[j]
                    path[i] = j

            dp[i] += A[i]

        i, res = 0, []
        while 0 <= i < len(A):
            res.append(i+1)
            i = path[i]

        if res[-1] != len(A):
            return []

        return res






if __name__ == '__main__':

    res = CheapestJump().doit_dp([1, 2, 4, -1, 2], 2)


