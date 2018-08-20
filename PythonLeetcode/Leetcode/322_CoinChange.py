


# 322. Coin Change
# You are given coins of different denominations and a total amount of money amount.
# Write a function to compute the fewest number of coins that you need to make up that amount.
# If that amount of money cannot be made up by any combination of the coins, return -1.

# Example 1:
# coins = [1, 2, 5], amount = 11
# return 3 (11 = 5 + 5 + 1)

# Example 2:
# coins = [2], amount = 3
# return -1.


class coinChange(object):

    # <DP>
    def doitDP(self, coins, amount):
        """
        :type coins: List[int]
        :type amount: int
        :rtype: int
        """
        D = [0] * (amount+1)
        
        for cur in range(1, len(D)):

            minS = float('inf')
            for c in coins:
                if cur >= c and D[cur - c] != -1:
                    minS = min(minS, D[cur - c]+1)

            D[cur] = minS if minS != float('inf') else -1
    
        return D[-1]

    # <DFS> Best way so far, dfs. for skip TLE, it use reverse order way and 
    def doit(self, coins, amount):                
        """
        :type coins: List[int]
        :type amount: int
        :rtype: int
        """
        coins.sort(reverse=True)
        self.res = 2**31-1
        

        def dfs(s, rest, dep):

            if rest == 0:
                self.res = min(self.res, dep)
                return

            for c in range(s, len(coins)):
                if coins[c] <= rest < coins[c] * (self.res - dep):
                    dfs(c, rest - coins[c], dep+1)

        for i in range(len(coins)):
            dfs(i, amount, 0)
        
        return self.res if self.res < 2**31 - 1 else -1
            
        

    def doit1(self, coins, amount):
        """
        :type coins: List[int]
        :type amount: int
        :rtype: int
        """
        nums = [1]
        steps = [0]

        t = [0] * len(coins) 
 
        while nums[-1] < amount:

            minv = min( coins[x] + nums[t[x]] for x in range(len(coins)))
     
            nums.append(minv)
            minStep = float('inf')

            for c in range(len(coins)):
                if coins[c] + nums[t[c]] == minv:
                    minStep = min(minStep, steps[t[c]])
                    t[c] += 1

            steps.append(minStep)

            if minv > amount:
                return -1
            elif minv == amount:
                return steps[-1]

        return -1


    def doit2(self, coins, amount):
        """
        :type coins: List[int]
        :type amount: int
        :rtype: int
        """
        if amount == 0:
            return 0

        buff = set()
        buff.add(amount)
        i = 1

        while buff:
            tmp = set()
            for c in buff:
                for s in coins:

                    if c - s == 0:
                        return i 

                    elif c > s:
                        tmp.add(c-s)

            i += 1
            buff = tmp                        

        return -1
    
        

        

        
if __name__=="__main__":


    res = coinChange().doit([1], 1)


    res = coinChange().doit([139,442,147,461,244,225,28,378,371], 9914)

    res = coinChange().doit([474,83,404,3], 264)

    res = coinChange().doit([1,2,5], 100)

    res = coinChange().doit([1], 0)

    res = coinChange().doit([1, 2, 5], 11)

    res = coinChange().doit([2], 3)

    pass
        