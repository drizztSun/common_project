"""
798. Backpack VII

# Assume that you have n yuan. There are many kinds of rice in the supermarket.
# Each kind of rice is bagged and must be purchased in the whole bag.
# Given the weight, price and quantity of each type of rice, find the maximum weight of rice that you can purchase.

# Example
# Given:
# n = 8
# prices = [2,4]
# weight = [100,100]
# amounts = [4,2]

# Return:400

"""


class BackPackVII:
    """
    @param n: the money of you
    @param prices: the price of rice[i]
    @param weight: the weight of rice[i]
    @param amounts: the amount of rice[i]
    @return: the maximum weight
    """
    def doit(self, n, prices, weight, amounts):
        # write your code here

        dp = [0 for _ in range(n+1)]

        for j in range(len(prices)):

            for m in reversed(range(prices[j], n+1)):

                for s in range(m - prices[j] * (amounts[j]-1), m+1, prices[j]):

                    if s >= prices[j]:
                        dp[s] = max(dp[s], dp[s-prices[j]] + weight[j])

        return dp[-1]


if __name__ == "__main__":

    res = BackPackVII().doit(8, [2, 4], [100, 100], [4, 2]) #400

    res = BackPackVII().doit(8, [3,2], [300,160], [1,6]) #640