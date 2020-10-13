"""
265. Paint House II

There are a row of n houses, each house can be painted with one of the k colors. The cost of painting each house with a certain color is different.
You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x k cost matrix.
For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with color 2, and so on...
Find the minimum cost to paint all houses.

Note:
All costs are positive integers.

Example:

Input: [[1,5,3],[2,9,4]]
Output: 5
Explanation: Paint house 0 into color 0, paint house 1 into color 2. Minimum cost: 1 + 4 = 5;
             Or paint house 0 into color 2, paint house 1 into color 0. Minimum cost: 3 + 2 = 5.
Follow up:
Could you solve it in O(nk) runtime?

"""


class PaintHouseMinCostII:

    def doit_dp_1(self, costs):
        """
        O(n*k**2)
        """
        houses, colors = len(costs), len(costs[0])
        dp = [[0 for _ in range(colors)] for _ in range(houses)]
        dp[0] = costs[0]

        for i in range(1, houses):
            for col in range(colors):
                best = float('inf')
                for pre_color in range(colors):
                    if pre_color == col:
                        continue
                    best = min(best, dp[i-1][pre_color] + costs[i][col])
                dp[i][col] = best
        return min(dp[-1])

    def doit_dp_2(self, costs):
        """
        O(n*k**2)
        """
        n = len(costs)
        k = len(costs[0])

        for house in range(1, n):
            for color in range(k):
                best = float('inf')
                for previous_color in range(k):
                    if color == previous_color:
                        continue
                    best = min(best, costs[house - 1][previous_color])
                costs[house][color] += best

        return min(costs[-1])

    """
    Approach 4: Dynamic programming with Optimized Time
    Intuition
    Despite Paint House II being listed as a hard question, and the problem statement listing O(n⋅k) time as a "follow up", 
    you'd possibly be expected to come up with this solution at top companies as it's still a fairly basic dynamic programming algorithm. 
    You should, therefore, ensure you're comfortable with this approach and could identify and apply similar observations in other dynamic programming problems. 
    At the very least, it'll make you look awesome!
    
    So far, all of our approaches have had a O(n⋅k**2) time complexity. 
    This is because calculating the new value for each of the O(n⋅k) cells required looking at each of the k cells in the row immediately below.
    
    However, we don't need to look at the entire previous row for every cell. Let's look again at the large example from above. 
    When we're calculating the values for the second row, we're adding the minimum from the first row onto them. 
    The only cell we can't do this for is the one that was directly below the minimum, as this would break the adjacency rule.
    For this one, it makes sense to add the second minimum.
    
    Complexity Analysis
    Time complexity : O(n⋅k).
    The first loop that finds the minimums of the first row is O(k)O(k) because it looks at each of the kk values in the first row exactly once. 
    The second loop is O(n⋅k) because the outer loop loops nn times, and the inner loop loops k times. 
    O(n⋅k) + O(k) = O(n⋅k)+O(k)=O(n⋅k). We know it is impossible to ever do better here, 
    because we cannot solve the problem without at least looking at each of the n⋅k cells once.
    
    Space complexity : O(1).
    
    Like approach 2, this approach also modifies the input instead of allocating its own space.
    """
    def doit_dp(self, costs):

        n = len(costs)
        k = len(costs[0])

        for house in range(1, n):
            # Find the colors with the minimum and second to minimum
            # in the previous row.
            min_color = second_min_color = None
            for color in range(k):
                cost = costs[house - 1][color]
                if min_color is None or cost < costs[house - 1][min_color]:
                    second_min_color = min_color
                    min_color = color
                elif second_min_color is None or cost < costs[house - 1][second_min_color]:
                    second_min_color = color
            # And now update the costs for the current row.
            for color in range(k):
                if color == min_color:
                    costs[house][color] += costs[house - 1][second_min_color]
                else:
                    costs[house][color] += costs[house - 1][min_color]

        # The answer will now be the minimum of the last row.
        return min(costs[-1])

    """
    Approach 5: Dynamic programming with Optimized Time and Space
    Intuition
    
    There is another way we can still solve the problem in O(1)O(1) space and O(n \cdot k)O(n⋅k) time complexity, and preserving the input.
    
    The only thing the algorithm in the previous approach is really doing is going through the rows, and finding the 2 minimums of each row. 
    It does this by calculating all the new costs for the row, writing them into the input, and then finding the minimums. 
    This overwriting isn't necessary though—we can simply keep track of the 2 smallest values we've seen so far, as we go, in the current row. 
    We also need to remember the 2 from the previous row.
    
    Algorithm
    
    The approach is a hybrid of approach 3 and 4. Like approach 4, it finds the minimums once instead of repeatedly. 
    Like approach 3, it keeps track of information only from the current and previous rows. Unlike approach 3 though, the only information kept is the minimums.
    
    
    There are many ways to compact the code a bit more, particularly in the case of the Python. I haven't done this here as it could be problematic for those less familiar with the 2 languages I have provided solutions in, however feel free to post your own solutions in the comments. I'm excited to see the elegance you can come up with!

    Complexity Analysis
    Time complexity : O(n⋅k).
    
    Same as the previous approach.
    
    Space complexity : O(1).
    
    The only additional working memory we're using is a constant number of single-value variables to keep track of the 2 minimums in the current and previous row, 
    and to calculate the cost of the current cell. Because the memory usage is constant, we say it is O(1)O(1). 
    Unlike the previous approach one though, this one does not overwrite the input.
    """
    def doit_dp(self, costs) -> int:
        n = len(costs)
        if n == 0:
            return 0  # This is a valid case.
        k = len(costs[0])

        # Firstly, we need to determine the 2 lowest costs of
        # the first row. We also need to remember the color of
        # the lowest.
        prev_min_cost = prev_second_min_cost = prev_min_color = None
        for color, cost in enumerate(costs[0]):
            if prev_min_cost is None or cost < prev_min_cost:
                prev_second_min_cost = prev_min_cost
                prev_min_color = color
                prev_min_cost = cost
            elif prev_second_min_cost is None or cost < prev_second_min_cost:
                prev_second_min_cost = cost

        # And now, we need to work our way down, keeping track of the minimums.
        for house in range(1, n):
            min_cost = second_min_cost = min_color = None
            for color in range(k):
                # Determime cost for this cell (without writing it into input array.)
                cost = costs[house][color]
                if color == prev_min_color:
                    cost += prev_second_min_cost
                else:
                    cost += prev_min_cost
                # And work out whether or not it is a current minimum.
                if min_cost is None or cost < min_cost:
                    second_min_cost = min_cost
                    min_color = color
                    min_cost = cost
                elif second_min_cost is None or cost < second_min_cost:
                    second_min_cost = cost
            # Transfer currents to be prevs.
            prev_min_cost = min_cost
            prev_min_color = min_color
            prev_second_min_cost = second_min_cost

        return prev_min_cost


if __name__ == '__main__':

    PaintHouseMinCostII().doit([[1,5,3],[2,9,4]])
