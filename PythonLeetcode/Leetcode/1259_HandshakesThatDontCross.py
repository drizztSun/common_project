"""
1259. Handshakes That Don't Cross

You are given an even number of people num_people that stand around a circle and each person shakes hands with someone else,
so that there are num_people / 2 handshakes total.

Return the number of ways these handshakes could occur such that none of the handshakes cross.

Since this number could be very big, return the answer mod 10^9 + 7



Example 1:

Input: num_people = 2
Output: 1
Example 2:



Input: num_people = 4
Output: 2
Explanation: There are two ways to do it, the first way is [(1,2),(3,4)] and the second one is [(2,3),(4,1)].
Example 3:



Input: num_people = 6
Output: 5
Example 4:

Input: num_people = 8
Output: 14


Constraints:

2 <= num_people <= 1000
num_people % 2 == 0
"""


class NumberOfWays:

    """
    - If we currently have n people
    - If 2 people shake hands
        - Then the rest of the people will be separated into two groups
            - This is because we can not have handshakes that crosses each other
    - If any of the two groups has an odd number of people
        - We will not be able to perform any handshakes, so there are 0 handshakes
    - The total number of handshakes when two people shake hands is
        - number of handshakes on the left side * number of handshakes on the right side
        - Example:
            - 2 people
                - After our current 2 people shake hands
                    - There are 0 people and 0 people on the left/right side
                    - So, the total number of handshakes will be 1 * 1
            - 4 people
                - After our current 2 people shake hands
                    - Here are the following combinations for the people on the 'left/right'
                        - (0)(2) -> 1 * 1 = 1
                        - (1)(1) -> 0 * 0 = 0
                        - (2)(0) -> 1 * 1 = 1
                    - So, we have a total of 2 ways to perform handshakes
    """
    def doit_dp_1(self, num_people):

        MOD = 10 ** 9 + 7

        def search(n, memo):

            if n in memo:
                return memo[n]

            res = 0
            for i in range(0, n, 2):
                res += search(i, memo) * search(n - i - 2, memo)

            res %= 10 ** 9 + 7
            memo[n] = res
            return res

        memo = {2: 1, 0: 1}
        return search(num_people, memo)

    def doit_dp(self, num_people):

        dp = [0 for _ in range(num_people//2+1)]
        dp[0] = dp[1] = 1

        for i in range(2, num_people//2+1):

            res = 0
            for j in range(i):

                res += dp[j] * dp[i-j-1]

            res %= 10**9+7

            dp[i] = res

        return dp[-1]

    def doit_dp_2(self, num_people):
        dp = {0: 1, 2: 1}
        cap = 1000000007
        for i in range(4, 1000 + 1, 2):
            dp[i] = sum(dp[j] % cap * dp[i - j - 2] % cap for j in range(0, i, 2)) % cap
        return dp[num_people]


if __name__ == '__main__':

    NumberOfWays().doit_dp(2)
    NumberOfWays().doit_dp(4)
    NumberOfWays().doit_dp(6)
    NumberOfWays().doit_dp(8)


