"""
799 Backpack VIII

# Given:
# n = 10
# value = [1,2,4]
# amount = [2,1,1]

# Return: 8
# They can combine all the values in 1 ~ 8
"""


class BackPackVIII:
    """
    @param n: the value from 1 - n
    @param value: the value of coins
    @param amount: the number of coins
    @return: how many different value
    """
    def doit(self, n, value, amount):
        # write your code here
        dp = [False for _ in range(n+1)]
        dp[0] = True

        for j in range(len(value)):
            for i in reversed(range(1, n+1)):
                cnt, val = amount[j], value[j]
                for z in reversed(range(1, cnt+1)):
                    if not dp[i] and i - z*val >= 0 and dp[i - z*val]:
                        dp[i] = True
                        break

        return sum(dp) - 1

    """
    @param n: the value from 1 - n
    @param value: the value of coins
    @param amount: the number of coins
    @return: how many different value
    """
    def doit1(self, n, value, amount):

        dp = [[False for _ in range(n+1)] for _ in range(len(value)+1)]

        for j in range(len(value) + 1):

            for i in range(n + 1):

                if i == 0 or j == 0 or dp[i][j]:
                    dp[i][j] = True
                    continue
                else:
                    cnt, val = amount[j-1], value[j-1]
                    for z in range(cnt):
                        if not dp[i][j] and j - z*val >= 0 and dp[i][j - z*val]:
                            dp[i][j] = True
                            break

        return sum(dp[-1][:]) - 1


if __name__ == "__main__":

    res = BackPackVIII().doit(10, [1, 2, 4], [2, 1, 1])