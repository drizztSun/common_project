"""
474. Ones and Zeroes

You are given an array of binary strings strs and two integers m and n.

Return the size of the largest subset of strs such that there are at most m 0's and n 1's in the subset.

A set x is a subset of a set y if all elements of x are also elements of y.



Example 1:

Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
Output: 4
Explanation: The largest subset with at most 5 0's and 3 1's is {"10", "0001", "1", "0"}, so the answer is 4.
Other valid but smaller subsets include {"0001", "1"} and {"10", "1", "0"}.
{"111001"} is an invalid subset because it contains 4 1's, greater than the maximum of 3.
Example 2:

Input: strs = ["10","0","1"], m = 1, n = 1
Output: 2
Explanation: The largest subset is {"0", "1"}, so the answer is 2.


Constraints:

1 <= strs.length <= 600
1 <= strs[i].length <= 100
strs[i] consists only of digits '0' and '1'.
1 <= m, n <= 100

"""


class OnesAndZeros:

    def doit_dp(self, strs: list, m: int, n: int) -> int:

        numbers = list(map(lambda x: (x.count('0'), x.count('1')), strs))
        numbers.sort() # it doesn't matter we sort it or not
        dp = {(0, 0): 0}

        for i in range(len(numbers)):
            zeros, ones = numbers[i]
            tmp = dict(dp)
            for zero in range(zeros, m+1):
                for one in range(ones, n+1):
                    target = (zero - zeros, one - ones)
                    if target in dp:
                        tmp[(zero, one)] = max(dp.get((zero, one), 0), dp[target] + 1)
            dp = tmp

        res = 0
        for i in range(m+1):
            for j in range(n+1):
                res = max(res, dp.get((i, j), 0))
        return res

    def doit_dfs(self, strs, m, n):
        """
        :type strs: List[str]
        :type m: int
        :type n: int
        :rtype: int
        """
        numbers = list(map(lambda x: (x.count('0'), x.count('1')), strs))
        numbers.sort()
        dp = {}

        def dfs(m, n, idx):

            if (m, n, idx) in dp:
                return dp[(m, n, idx)]

            tmp = 0
            i = idx
            while i < len(numbers):

                if numbers[i][0] <= m and numbers[i][1] <= n:
                    tmp = max(tmp, 1 + dfs(m - numbers[i][0], n - numbers[i][1], i + 1))

                while i < len(numbers) - 1 and numbers[i] == numbers[i + 1]:
                    i += 1

                i += 1

            dp[(m, n, idx)] = tmp
            return tmp

        return dfs(m, n, 0)

    def doit_dfs_dp(self, strs, m, n):
        """
        :type strs: List[str]
        :type m: int
        :type n: int
        :rtype: int
        """
        import collections
        number = []
        for s in strs:
            counter = collections.Counter(s)
            if '0' not in counter:
                counter['0'] = 0
            elif '1' not in counter:
                counter['1'] = 0
            number.append((counter['0'], counter['1']))
        number.sort()
        dp = collections.defaultdict(int)

        def dfs(m, n, idx):
            if (m, n, idx) in dp:
                return dp[(m, n, idx)]
            tmp = 0
            i = idx
            while i < len(strs):
                zeros, ones = number[i]
                if m - zeros >= 0 and n - ones >= 0:
                    tmp = max(tmp, 1 + dfs(m - zeros, n - ones, i + 1))

                while i < len(strs) - 1 and number[i] == number[i + 1]:
                    i += 1
                i += 1

            dp[(m, n, idx)] = tmp
            return tmp

        return dfs(m, n, 0)


if __name__ == '__main__':

    OnesAndZeros().doit_dp(["10","0001","111001","1","0"], 50, 50)

    OnesAndZeros().doit_dp(strs = ["10","0001","111001","1","0"], m = 5, n = 3)

    OnesAndZeros().doit_dp(strs = ["10","0","1"], m = 1, n = 1)


