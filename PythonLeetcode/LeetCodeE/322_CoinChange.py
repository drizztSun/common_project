# 322. Coin Change

# You are given coins of different denominations and a total amount of money amount. 
# Write a function to compute the fewest number of coins that you need to make up that amount. 
# If that amount of money cannot be made up by any combination of the coins, return -1.

# Example 1:

# Input: coins = [1, 2, 5], amount = 11
# Output: 3 
# Explanation: 11 = 5 + 5 + 1
# Example 2:

# Input: coins = [2], amount = 3
# Output: -1
# Note:
# You may assume that you have an infinite number of each kind of coin.


class CoinChange:

    # DP
    def doit(self, coins, amount):
        """
        :type coins: List[int]
        :type amount: int
        :rtype: int
        """
        totals = [float("inf") for _ in range(amount + 1)]
        totals[0] = 0

        for c in coins:

            for i in range(c, amount + 1):

                totals[i] = min(totals[i], totals[i - c] + 1)

        return -1 if totals[amount] == float("inf") else totals[amount]
         

    def change(self, coins, amount):
        """
        :type coins: List[int]
        :type amount: int
        :rtype: int
        """
        coins.sort(reverse=True)
        Infinity = 2**31-1
        self.res = Infinity
        
        def dfs(s, remain, count):
            
            if remain == 0:
                self.res = min(self.res, count)
                return
                
            for c in range(s, len(coins)):
                if coins[c] <= remain < coins[c] * (self.res - count):
                    dfs(c, remain - coins[c], count + 1)
                    
        
        for i in range(len(coins)):
            dfs(i, amount, 0)
            
        return self.res if self.res != Infinity else -1


    def doit1(self, coins, amount):
        """
        :type coins: List[int]
        :type amount: int
        :rtype: int
        """
        coins.sort(reverse = 1)
        total = amount
        nums = 0
        Infinity = 2**31-1
        self.res = Infinity

        def search(idx, total, nums):

            if nums > self.res:
                return

            if total == 0:
                self.res = min(self.res, nums)
                return

            if idx >= len(coins):
                return

            base = total // coins[idx]

            for i in reversed(range(base + 1)):

                if total - i * coins[idx] >= 0:
                    nums += i 
                    search(idx + 1, total - i * coins[idx], nums)
                    nums -= i
            
            return
                
           
        search(0, total, nums)
        return self.res if self.res == Infinity else -1


if __name__ == "__main__":

    res = CoinChange().doit([1, 2, 5], 11)

    res = CoinChange().change([357,239,73,52], 9832)

    res = CoinChange().doit([357,239,73,52], 9832)

    pass