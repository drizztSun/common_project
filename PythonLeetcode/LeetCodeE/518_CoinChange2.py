# 518. Coin Change 2

# You are given coins of different denominations and a total amount of money. 
# Write a function to compute the number of combinations that make up that amount. 
# You may assume that you have infinite number of each kind of coin.

# Note: You can assume that

# 0 <= amount <= 5000
# 1 <= coin <= 5000
# the number of coins is less than 500
# the answer is guaranteed to fit into signed 32-bit integer
 

# Example 1:

# Input: amount = 5, coins = [1, 2, 5]
# Output: 4
# Explanation: there are four ways to make up the amount:
# 5=5
# 5=2+2+1
# 5=2+1+1+1
# 5=1+1+1+1+1
 

# Example 2:

# Input: amount = 3, coins = [2]
# Output: 0
# Explanation: the amount of 3 cannot be made up just with coins of 2.
 

# Example 3:

# Input: amount = 10, coins = [10] 
# Output: 1


class CoinChangeII(object):



    # The detail is in by blog.
    # Here is the summary :
    # Let's say we have coin[1]~coin[n], and the amount = A.
    # This is how we came up with DP solution.

    # The relation between original problem and sub-problem.
    # We can separate the solution of original problem into 2 mutually exclusive cases.
    # And the solution is the sum of case1 & case2
    # case1: make up A without coin[n]
    # So the problem becomes
    # "number of ways to make up A, with coin[1]~coin[n-1]"
    # case 2: make up A with at least one coin[n]
    # So the problem becomes
    # "number of ways to make up A-coin[n], with coin[1]~coin[n]"
    # The base case
    # When A=0, there is only 1 way to make up A.
    # Since we have a DP relation, and the base case,
    # we can build up a reference table, and the final answer is table[A]

    def doit(self, amount, coins):
        """
        :type amount: int
        :type coins: List[int]
        :rtype: int
        """
        totals = [ 0 for _ in range(amount + 1)]
        totals[0] = 1

        for c in coins:

            for i in range(c, amount + 1):

                totals[i] += totals[i - c]

        return totals[amount]

    # wrong solution, because for each amount, we pick different coins again, 
    # it will make some dulipcate event, 3 = 2 + 1 = 1 + 2
    def wrong_doit1(self, amount, coins):
        """
        :type amount: int
        :type coins: List[int]
        :rtype: int
        """
        totals = [ 0 for _ in range(amount + 1)]
        totals[0] = 1

        for i in range(1, amount + 1):

            for c in coins:

                if i - c >= 0:
                    totals[i] +=  totals[i - c]

        return totals[amount]
             

    def doit2(self, amount, coins):
        """
        :type amount: int
        :type coins: List[int]
        :rtype: int
        """
        self.res = 0

        def dfs(s, total):

            if total == 0:
                self.res += 1
                return

            for c in range(s, len(coins)):
                if coins[c] <= total:
                    dfs(c, total - coins[c])

        for i in range(len(coins)):
            dfs(i, amount)

        return self.res 


if __name__ == "__main__":

    res = CoinChangeII().doit(5, [1, 2, 5])

    res = CoinChangeII().doit(3, [2])

    res = CoinChangeII().doit(10, [10])

    pass
        