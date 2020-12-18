"""
1601. Maximum Number of Achievable Transfer Requests

We have n buildings numbered from 0 to n - 1. Each building has a number of employees. It's transfer season, and some employees want to change the building they reside in.

You are given an array requests where requests[i] = [fromi, toi] represents an employee's request to transfer from building fromi to building toi.

All buildings are full, so a list of requests is achievable only if for each building, the net change in employee transfers is zero.
This means the number of employees leaving is equal to the number of employees moving in.

For example if n = 3 and two employees are leaving building 0, one is leaving building 1, and one is leaving building 2,
there should be two employees moving to building 0, one employee moving to building 1, and one employee moving to building 2.

Return the maximum number of achievable requests.



Example 1:


Input: n = 5, requests = [[0,1],[1,0],[0,1],[1,2],[2,0],[3,4]]
Output: 5
Explantion: Let's see the requests:
From building 0 we have employees x and y and both want to move to building 1.
From building 1 we have employees a and b and they want to move to buildings 2 and 0 respectively.
From building 2 we have employee z and they want to move to building 0.
From building 3 we have employee c and they want to move to building 4.
From building 4 we don't have any requests.
We can achieve the requests of users x and b by swapping their places.
We can achieve the requests of users y, a and z by swapping the places in the 3 buildings.
Example 2:


Input: n = 3, requests = [[0,0],[1,2],[2,1]]
Output: 3
Explantion: Let's see the requests:
From building 0 we have employee x and they want to stay in the same building 0.
From building 1 we have employee y and they want to move to building 2.
From building 2 we have employee z and they want to move to building 1.
We can achieve all the requests.
Example 3:

Input: n = 4, requests = [[0,3],[3,1],[1,2],[2,0]]
Output: 4


Constraints:

1 <= n <= 20
1 <= requests.length <= 16
requests[i].length == 2
0 <= fromi, toi < n



"""


class MaximumRequests:

    def doit_backtracking(self, n: int, requests: list) -> int:
        from collections import defaultdict
        indegree = defaultdict(int)
        ans = 0

        def backtracking(i, count):
            nonlocal ans

            if i == len(requests):
                for k in indegree:
                    if indegree[k] != 0:
                        return

                ans = max(ans, count)
                return

            c1, c2 = requests[i][0], requests[i][1]

            # take ith
            indegree[c1] -= 1
            indegree[c2] += 1
            backtracking(i+1, count+1)

            indegree[c1] += 1
            indegree[c2] -= 1

            backtracking(i+1, count)

        backtracking(0, 0)
        return ans


    # Version 3: DFS with early stop
    # TC: O(mn + 2^m), SC: O(n+m)
    def doit_dfs(self, n: int, requests: list) -> int:

        def dfs(current, index, ans):
            if index >= m:
                return

            dfs(current, index + 1, ans)
            status[requests[index][0]] -= 1
            status[requests[index][1]] += 1
            skip = False
            current.append(index)
            if not any(status):
                ans[0] = max(ans[0], len(current))

            if status[requests[index][0]] < 0:
                ins = suffix_i[index + 1][requests[index][0]]
                # ins = sum([1 for k in range(index+1, m) if requests[k][1] == requests[index][0]])
                if ins < -status[requests[index][0]]:
                    skip = True

            if status[requests[index][1]] > 0:
                out = suffix_o[index + 1][requests[index][1]]
                # out = sum([1 for k in range(index+1, m) if requests[k][0] == requests[index][1]])
                if out < status[requests[index][1]]:
                    skip = True

            if not skip:
                dfs(current, index + 1, ans)

            current.pop()
            status[requests[index][0]] += 1
            status[requests[index][1]] -= 1

        m = len(requests)
        requests = list(filter(lambda x: x[0] != x[1], requests))
        same = m - len(requests)
        m = len(requests)
        count = [0] * n
        status = [0] * n
        suffix_i = [[0] * n for _ in range(m + 1)]
        suffix_o = [[0] * n for _ in range(m + 1)]
        cnt_i = [0] * n
        cnt_o = [0] * n

        for k in range(m - 1, -1, -1):
            cnt_o[requests[k][0]] += 1
            cnt_i[requests[k][1]] += 1
            for i in range(n):
                suffix_i[k][i] = cnt_i[i]
                suffix_o[k][i] = cnt_o[i]

        ans = [0]
        dfs([], 0, ans)

        return ans[0] + same

    def doit_1(self, n: int, requests: list) -> int:

        amount = len(requests)
        ans = 0

        for mask in range(1, 1 << amount):

            allmoves = [0 for _ in range(n)]

            for j in range(amount):
                if (1 << j) & mask:
                    allmoves[requests[j][0]] -= 1
                    allmoves[requests[j][1]] += 1

            for c in allmoves:
                if c != 0:
                    break
            else:
                nums = 0
                while mask > 0:
                    if mask % 2 == 1:
                        nums += 1
                    mask >>= 1
                ans = max(ans, nums)

        return ans

    # Version 1: Try with all combination
    # TC: O((m+n)*2^m), SC: O(n+m)
    def doit_2(self, n: int, requests: list) -> int:
        m = len(requests)
        ans = 0
        for k in range(1<<m):
            status = [0]*n
            for i in range(m):
                if k & (1<<i) > 0:
                    status[requests[i][0]] -= 1
                    status[requests[i][1]] += 1
            done = True
            for i in range(n):
                if status[i] != 0:
                    done = False
                    break
            if done:
                ans = max(ans, bin(k).count('1'))
        return ans

    # Version 2: Consider C(m, k) combinations
    # TC: O((m+n)*2^m), SC: O(n+m)
    def doit_3(self, n: int, requests: list) -> int:
        import itertools
        m = len(requests)
        ans = 0
        for k in range(m, -1, -1):
            for i in itertools.combinations(range(len(requests)), k):
                degree = [0]*n
                for j in i:
                    degree[requests[j][0]] -= 1
                    degree[requests[j][1]] += 1
                if not any(degree):
                    return k
        return ans


if __name__ == '__main__':

    MaximumRequests().doit_(5, [[0,1],[1,0],[0,1],[1,2],[2,0],[3,4]])