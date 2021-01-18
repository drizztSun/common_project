"""
377. Combination Sum IV

Given an integer array with all positive numbers and no duplicates, find the number of possible combinations that add up to a positive integer target.

Example:

nums = [1, 2, 3]
target = 4

The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

Note that different sequences are counted as different combinations.

Therefore the output is 7.
 

Follow up:
What if negative numbers are allowed in the given array?
How does it change the problem?
What limitation we need to add to the question to allow negative numbers?

"""

class CombinationSumIV:

    def doit_(self, nums: list, target: int) -> int:
        dp = [1] + [0] * target

        for i in range(1, target+1):
            
            for num in nums:
                if i >= num:
                    dp[i] += dp[i - num]

        return dp[target]

    """
    Approach 1: Top-Down Dynamic Programming
    Intuition

    Let us start with an example. Given the input array of nums = [1, 2, 3] and the target = 4, we are asked to come up with a set of combinations so that the sum of each combination is equal to the target value.

    Let us clarify a bit on the reference of combination here, which is more of a permutation, to be more precise, where the order of elements does matter. For instance, we could have two combinations such as [1, 3] and [3, 1], which are valid and different for this problem. While, for the problem of Coin Changes II, these two combinations would be considered to be the same.

    So to summarize a bit, the order of elements in the combination does matter for this problem.
    """
    def doit_dp_topdown(self, nums: list, target: int) -> int:
        # potential optimization
        # nums.sort()

        @functools.lru_cache(maxsize = None)
        def combs(remain):
            if remain == 0:
                return 1

            result = 0
            for num in nums:
                if remain - num >= 0:
                    result += combs(remain - num)
                # potential optimization
                # else:
                #     break

            return result

        return combs(target)

    """
    Approach 2: Bottom-Up Dynamic Programming
    Intuition

    Another well-known form of dynamic programming algorithm is bottom-up, as opposed to top-down, where one often sees the application of one dimentional or multi-dimentional array (i.e. dp[]).

    As a reminder, here is the formula we derived before:
    Algorithm

    Based on the above intuition, here are some sample implementations.

    One can see the ressemblance between the top-down and bottom-up approaches. In certain perspective, the bottom-up approach is equivalent to the unfolding of the top-down approach with memoization.

    Complexity Analysis

    Let TT be the target value, and NN be the number of elements in the input array.

    Time Complexity: \mathcal{O}(T \cdot N)O(T⋅N)

    We have a nested loop, with the number of iterations as TT and NN respectively.

    Hence, the overall time complexity of the algorithm is \mathcal{O}(T \cdot N)O(T⋅N).

    Space Complexity: \mathcal{O}(T)O(T)

    We allocate an array dp[i] to hold all the intermediate values, which amounts to \mathcal{O}(T)O(T) space.
    """
    def doit_dp_bottomup_1(self, nums: list, target: int) -> int:
        # minor optimization
        # nums.sort()
        dp = [0 for i in range(target+1)]
        dp[0] = 1

        for comb_sum in range(target+1):

            for num in nums:
                if comb_sum - num >= 0:
                    dp[comb_sum] += dp[comb_sum-num]
                # minor optimization, early stopping.
                # else:
                #    break
        return dp[target]

    def doit_dp_bottomup(self, nums: list, target: int) -> int:

        dp = [1] + [0] * target

        for i in range(1, target+1):
            
            for num in nums:

                if i >= num:
                
                    dp[i] += dp[i - num]

        return dp[target]



        