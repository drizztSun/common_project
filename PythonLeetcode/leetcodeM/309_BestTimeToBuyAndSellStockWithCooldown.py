"""
309. Best Time to Buy and Sell Stock with Cooldown

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:

Input: [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]


"""


class BestTimeSellStockWithCooldown:

    def doit_dp(self, prices):
        n = len(prices)
        dp = [[0] * 3 for _ in range(n + 1)]
        # 0 sold, 1 held, 2 reset
        dp[0][0], dp[0][1], dp[0][2] = float('-inf'), float('-inf'), 0

        for i in range(1, n + 1):
            dp[i][0] = dp[i - 1][1] + prices[i - 1]
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][2] - prices[i - 1])
            dp[i][2] = max(dp[i - 1][2], dp[i - 1][0])

        return max(dp[n][0], dp[n][2])

    """
        Approach 1: Dynamic Programming with State Machine
        Intuition

        First of all, let us take a different perspective to look at the problem, unlike the other algorithmic problems.

        Here, we will treat the problem as a game, and the trader as an agent in the game. The agent can take actions that lead to gain or lose of game points (i.e. profits). And the goal of the game for the agent is to gain the maximal points.

        In addition, we will introduce a tool called state machine, which is a mathematical model of computation. Later one will see how the state machine coupled with the dynamic programming technique can help us solve the problem easily.

        In the following sections, we will first define a state machine that is used to model the behaviors and states of the game agent.

        Then, we will demonstrate how to apply the state machine to solve the problem.

        Definition

        Let us define a state machine to model our agent. The state machine consists of three states, which we define as follows:

        state held: in this state, the agent holds a stock that it bought at some point before.

        state sold: in this state, the agent has just sold a stock right before entering this state. And the agent holds no stock at hand.

        state reset: first of all, one can consider this state as the starting point, where the agent holds no stock and did not sell a stock before. More importantly, it is also the transient state before the held and sold. Due to the cooldown rule, after the sold state, the agent can not immediately acquire any stock, but is forced into the reset state. One can consider this state as a "reset" button for the cycles of buy and sell transactions.

        At any moment, the agent can only be in one state. The agent would transition to another state by performing some actions, namely:

        action sell: the agent sells a stock at the current moment. After this action, the agent would transition to the sold state.

        action buy: the agent acquires a stock at the current moment. After this action, the agent would transition to the held state.

        action rest: this is the action that the agent does no transaction, neither buy or sell. For instance, while holding a stock at the held state, the agent might simply do nothing, and at the next moment the agent would remain in the held state.

        Now, we can assemble the above states and actions into a state machine, which we show in the following graph where each node represents a state, and each edge represents a transition between two states. On top of each edge, we indicate the action that triggers the transition.
    """

    def doit_dp_1(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        sold, held, reset = float('-inf'), float('-inf'), 0

        for price in prices:
            # Alternative: the calculation is done in parallel.
            # Therefore no need to keep temporary variables
            #sold, held, reset = held + price, max(held, reset-price), max(reset, sold)

            pre_sold = sold
            sold = held + price
            held = max(held, reset - price)
            reset = max(reset, pre_sold)

        return max(sold, reset)


if __name__ == '__main__':

    BestTimeSellStockWithCooldown().doit_dp_1([1,2,4])

    BestTimeSellStockWithCooldown().doit_dp([1, 2, 4])


