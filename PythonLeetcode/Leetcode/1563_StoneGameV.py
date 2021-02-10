"""
1563. Stone Game V

There are several stones arranged in a row, and each stone has an associated value which is an integer given in the array stoneValue.

In each round of the game, Alice divides the row into two non-empty rows (i.e. left row and right row),
then Bob calculates the value of each row which is the sum of the values of all the stones in this row.
Bob throws away the row which has the maximum value, and Alice's score increases by the value of the remaining row.
If the value of the two rows are equal, Bob lets Alice decide which row will be thrown away. The next round starts with the remaining row.

The game ends when there is only one stone remaining. Alice's is initially zero.

Return the maximum score that Alice can obtain.



Example 1:

Input: stoneValue = [6,2,3,4,5,5]
Output: 18
Explanation: In the first round, Alice divides the row to [6,2,3], [4,5,5]. The left row has the value 11 and the right row has value 14.
Bob throws away the right row and Alice's score is now 11.
In the second round Alice divides the row to [6], [2,3]. This time Bob throws away the left row and Alice's score becomes 16 (11 + 5).
The last round Alice has only one choice to divide the row which is [2], [3].
Bob throws away the right row and Alice's score is now 18 (16 + 2). The game ends because only one stone is remaining in the row.

Example 2:

Input: stoneValue = [7,7,7,7,7,7,7]
Output: 28
Example 3:

Input: stoneValue = [4]
Output: 0


Constraints:

1 <= stoneValue.length <= 500
1 <= stoneValue[i] <= 10^6


"""


class StoneGameV:

    def doit_dp_topdown(self, stoneValue: list) -> int:
        from functools import lru_cache
        n = len(stoneValue)
        sums = [0] *(n+1)
        for i in range(n):
            sums[i+1] = sums[i] + stoneValue[i]

        @lru_cache(None)
        def dfs(l, r):
            if l >= r: return 0

            ans = 0
            for k in range(l, r):

                sum_l, sum_r = sums[k+1] - sums[l], sums[r+1] - sums[k+1]

                if sum_l < sum_r:
                    ans = max(ans, sum_l + dfs(l, k))
                elif sum_l > sum_r:
                    ans = max(ans, sum_r + dfs(k+1, r))
                else:
                    ans = max(ans, sum_l + max(dfs(l, k), dfs(k+1, r)))

            return ans

        return dfs(0, n-1)

    """
        O(n^2 log n)

        Optimization
        As k goes from i to j in stones[i..j], sum of left part sum[i][k] increases continuously and it remains a valid subarray for our consideration for calculating dp[i][j] until the point when it becomes greater than right half.
        From that point onwards, all the right ones are valid subarrays for consideration. We can find this critical k (= k') using binary search. Forget about boundary cases and equal halves etc for now, just try to understand the general idea.

        dp[i][j] = max( max(sum[i][k] + dp[i][k]) for k: i to k', max(sum[k][j] + dp[k][j]) for k: k'+1 to j )
        (refer to the code for exact condition for all cases)

        If we have to calculate first and second terms in above by iterating from k: i to k' or k: k'+1 to j, then it'd take O(n) time and we are back to first solution.
        
        What we can instead do is maintain 2 more arrays defined as:
        left[i][j] = max( sum[i][k] + dp[i][k] for k: i to j )
        right[i][j] = max( sum[k][j] + dp[k][j] for k: i to j )

        and use them to redefine dp[i][j] = max( left[i][k'], right[k'+1][j] )

        Note that left and right arrays can also be calculated along with dp table so they don't increase our worst case time complexity.

        left[i][j] = max( left[i][j-1], sum[i][j] + dp[i][j] )
        right[i][j] = max( right[i+1][j], sum[i][j] + dp[i][j] )

        With these ideas in mind and taking care of boundary cases like k' == i or k' == j and equal halves etc, we have our solution ready.

    """
    def doit_dp_binary_search(self, stoneValue: list) -> int:

        n = len(stoneValue)
        presum = [0] * (n+1)
        for i in range(n):
            presum[i+1] = presum[i] + stoneValue[i]
            
        dp = [[0 for _ in range(n)] for _ in range(n)]
        left = [[0 for _ in range(n)] for _ in range(n)]
        right = [[0 for _ in range(n)] for _ in range(n)]

        for i in range(n):
            left[i][i] = right[i][i] = stoneValue[i]

        def search(l, r):
            L = l
            total = presum[r+1] - presum[l]
            while l < r:
                mid = (l + r) // 2
                if 2 * (presum[mid+1] - presum[L]) >= total:
                    r = mid
                else:
                    l = mid + 1
            return l 

        for L in (1, n):
            for i in range(n-L):
                
                j = i + L
                k = search(i, j)

                leftpart, total = presum[k+1] - presum[i], presum[j+1] - presum[i]

                if 2 * leftpart == total:
                    dp[i][j] = max(left[i][k], right[k+1][j])
                else:
                    dp[i][j] = max(0 if k == i else left[i][k-1], 0 if k == j else right[k+1][j])
                

                left[i][j] = max(left[i][j-1], total + dp[i][j])
                right[i][j] = max(right[i+1][j], total + dp[i][j])

        return dp[0][n-1]


    """
        O(n^2)

        Optimization
        We can optimize the previous solution even further by getting rid of the binary search step needed to find the critical k (= k') of stones[i..j].
        Binary search is great when we need the answer for arbitrary i and j but why not calculate dp[i][j] in such an order where we could leverage the k' information from previous i and j.

        Suppose we know the k' for stones[i..j], what do we know about k' for stones[i..j+1]? It is either the same or it got shifted a few places to the right.
        And so if we calculate dp values in the order: dp[i][i], dp[i][i+1], dp[i][i+2], ..., dp[i][j], we can essentially keep track of k' as we go within that same linear time bound.

        Using this idea, we implement the final solution. Couple of pointers about my code:

        1) mid: represents k' or first index such that left half >= right half
        
        2) with i < j, max[i][j] represents left[i][j] of previous solution i.e. max(dp[i][i], dp[i][i+1], dp[i][i+2] .. dp[i][j]) and 
                        max[j][i] represents right[i][j] of previous solution i.e.max(dp[i][j], dp[i+1][j], dp[i+2][j] .. dp[j][j]). 
            We could have used two different arrays left and right just like previous solution but this trick saves space.
        
        3) I am traversing in the order: dp[j][j], dp[j-1,j], dp[j-2, j], .., dp[i][j] instead of the above mentioned order but the idea remains same.
    """
    def doit_dp_(self, stoneValue: list) -> int:

        n = len(stoneValue)
        dp = [[0 for _ in range(n)] for _ in range(n)]
        maxvalue = [[0 for _ in range(n)] for _ in range(n)]

        for i in range(n):
            maxvalue[i][i] = stoneValue[i]

        for j in range(n):
            total, rightpart, mid = stoneValue[j], 0, j
            for i in range(j-1, -1, -1):

                total += stoneValue[i]

                while 2 * (rightpart + stoneValue[mid]) <= total:
                    rightpart += stoneValue[mid]
                    mid -= 1

                if 2 * rightpart == total:
                    dp[i][j] = max(maxvalue[i][mid], maxvalue[j][mid+1])
                else:
                    dp[i][j] = max(0 if mid == i else maxvalue[i][mid-1], 0 if mid == j else maxvalue[j][mid+1])


                maxvalue[i][j] = max(maxvalue[i][j-1], total + dp[i][j])
                maxvalue[j][i] = max(maxvalue[j][i+1], total + dp[i][j])

        return dp[0][n-1]