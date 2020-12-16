"""
1340. Jump Game V

Given an array of integers arr and an integer d. In one step you can jump from index i to index:

i + x where: i + x < arr.length and 0 < x <= d.
i - x where: i - x >= 0 and 0 < x <= d.
In addition, you can only jump from index i to index j if arr[i] > arr[j] and arr[i] > arr[k] for all indices k between i and j (More formally min(i, j) < k < max(i, j)).

You can choose any index of the array and start jumping. Return the maximum number of indices you can visit.

Notice that you can not jump outside of the array at any time.


Example 1:

Input: arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2
Output: 4
Explanation: You can start at index 10. You can jump 10 --> 8 --> 6 --> 7 as shown.
Note that if you start at index 6 you can only jump to index 7. You cannot jump to index 5 because 13 > 9.
You cannot jump to index 4 because index 5 is between index 4 and 6 and 13 > 9.

Similarly You cannot jump from index 3 to index 2 or index 1.

Example 2:

Input: arr = [3,3,3,3,3], d = 3
Output: 1
Explanation: You can start at any index. You always cannot jump to any index.

Example 3:

Input: arr = [7,6,5,4,3,2,1], d = 1
Output: 7
Explanation: Start at index 0. You can visit all the indicies.

Example 4:

Input: arr = [7,1,7,1,7,1], d = 2
Output: 2

Example 5:

Input: arr = [66], d = 1
Output: 1


Constraints:

1 <= arr.length <= 1000
1 <= arr[i] <= 10^5
1 <= d <= arr.length


"""


class JumpGameV:

    def doit_dp(self, arr: list, d: int) -> int:
        # results = [1 for _ in range(len(arr) + 1)]
        import math
        s, r = [], 0

        for i, a in enumerate(arr + [math.inf]):
            c = int(a != math.inf)
            while s and arr[s[-1][0]] < a:
                l = [s.pop()]
                while s and arr[s[-1][0]] == arr[l[0][0]]:
                    l.append(s.pop())
                for j, v in l:
                    r = max(r, v)
                    if j + d >= i:
                        c = max(c, v + 1)
                    if s and s[-1][0] + d >= j:
                        s[-1][1] = max(s[-1][1], v + 1)

            s.append([i, c])
        return r

    def doit_dp_Bottomup(self, arr: list, d: int) -> int:

        n = len(arr)
        heights = sorted(range(n), key=arr.__getitem__)
        dp = [0] * n
        total = 0

        for i in heights:
            ans = 1
            j = i + 1
            while j < min(n, i + d + 1) and arr[i] > arr[j]:
                ans = max(ans, dp[j] + 1)
                j += 1

            j = i - 1
            while j >= max(0, i - d) and arr[i] > arr[j]:
                ans = max(ans, dp[j] + 1)
                j -= 1

            dp[i] = ans
            total = max(total, ans)

        return total

    def doit_dp_topdown(self, arr: list, d: int) -> int:
        from functools import lru_cache
        n = len(arr)

        @lru_cache(None)
        def search(i):
            ans = 1
            j = i + 1
            while j < min(n, i + d + 1) and arr[i] > arr[j]:
                ans = max(ans, search(j) + 1)
                j += 1

            j = i - 1
            while j >= max(0, i - d) and arr[i] > arr[j]:
                ans = max(ans, search(j) + 1)
                j -= 1  

            return ans

        rtv = 0
        for i in range(n):
            rtv = max(rtv, search(i))

        return rtv




if __name__ == '__main__':

    JumpGameV().doit_dfs(arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2)

    JumpGameV().doit_dfs(arr = [3,3,3,3,3], d = 3)

    JumpGameV().doit_dfs(arr = [7,6,5,4,3,2,1], d = 1)

    JumpGameV().doit_dfs(arr = [7,1,7,1,7,1], d = 2)

    JumpGameV().doit_dfs(arr = [66], d = 1)
