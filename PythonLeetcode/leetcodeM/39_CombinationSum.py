"""
39. Combination Sum

Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.

It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.



Example 1:

Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.
Example 2:

Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]
Example 3:

Input: candidates = [2], target = 1
Output: []
Example 4:

Input: candidates = [1], target = 1
Output: [[1]]
Example 5:

Input: candidates = [1], target = 2
Output: [[1,1]]


Constraints:

1 <= candidates.length <= 30
1 <= candidates[i] <= 200
All elements of candidates are distinct.
1 <= target <= 500

"""


class CombinationSum:

    """
    Approach 1: Backtracking
    Intuition

    As a reminder, backtracking is a general algorithm for finding all (or some) solutions to some computational problems. The idea is that it incrementally builds candidates to the solutions, and abandons a candidate ("backtrack") as soon as it determines that this candidate cannot lead to a final solution.

    Specifically, to our problem, we could incrementally build the combination, and once we find the current combination is not valid, we backtrack and try another option.

    Algorithm

    As one can see, the above backtracking algorithm is unfolded as a DFS (Depth-First Search) tree traversal, which is often implemented with recursion.

    Here we define a recursive function of backtrack(remain, comb, start) (in Python), which populates the combinations, starting from the current combination (comb), the remaining sum to fulfill (remain) and the current cursor (start) to the list of candidates. Note that, the signature of the recursive function is slightly different in Java. But the idea remains the same.

    For the first base case of the recursive function, if the remain==0, i.e. we fulfill the desired target sum, therefore we can add the current combination to the final list.

    As another base case, if remain < 0, i.e. we exceed the target value, we will cease the exploration here.

    Other than the above two base cases, we would then continue to explore the sublist of candidates as [start ... n]. For each of the candidate, we invoke the recursive function itself with updated parameters.

    Specifically, we add the current candidate into the combination.

    With the added candidate, we now have less sum to fulfill, i.e. remain - candidate.

    For the next exploration, still we start from the current cursor start.

    At the end of each exploration, we backtrack by popping out the candidate out of the combination.

    """
    def doit_backtracking(self, candidates: List[int], target: int) -> List[List[int]]:

        results = []

        def backtrack(remain, comb, start):
            if remain == 0:
                # make a deep copy of the current combination
                results.append(list(comb))
                return
            elif remain < 0:
                # exceed the scope, stop exploration.
                return

            for i in range(start, len(candidates)):
                # add the number into the combination
                comb.append(candidates[i])
                # give the current number another chance, rather than moving on
                backtrack(remain - candidates[i], comb, i)
                # backtrack, remove the number from the combination
                comb.pop()

        backtrack(target, [], 0)

        return results

    def doit(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        def search(nums, i, target, cur):

            if target == 0:
                res.append(cur)
                return

            for j in range(i, len(nums)):
                if target - nums[j] >= 0:
                    # next level starting from j, because we wanna same num nums[j]
                    search(nums, j, target - nums[j], cur + [nums[j]])

        res = []
        search(candidates, 0, target, [])
        return res


"""
40. Combination Sum II

Given a collection of candidate numbers (candidates) and a target number (target), 
find all unique combinations in candidates where the candidate numbers sum to target.

Each number in candidates may only be used once in the combination.

Note: The solution set must not contain duplicate combinations.

 

Example 1:

Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: 
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
Example 2:

Input: candidates = [2,5,2,1,2], target = 5
Output: 
[
[1,2,2],
[5]
]
 

Constraints:

1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30
"""


class CombinationSumII(object):

    """
        Approach 2: Backtracking with Index
        Intuition

        There is another way to adapt the solution of 39. Combination Sum.

        Rather than building a counter table to group the numbers together explicitly, we could sort the input, which could also group all the same numbers together.

        Similar to the solution of 39. Combination Sum, we iterate through the sorted input array, via backtracking to build the combinations.

        In addition, we need to do some tricks with the index of the iteration, in order to avoid generating duplicated combinations.

        We demonstrate the idea with the same example in the previous approach, i.e. input = [2, 5, 2, 2].

        index demo

        As we can see from the above graph, once we sort the input array, the occurrance of each unique number would be adjacent to each other.

        In the above graph, we show the moment we start to process the group of number 2, with the iteration index pointed to the beginning of the group.

        Next, we need to move the index forward, in order to choose the next number to be added to the combination. More importantly, we need to skip certain positions, in order to avoid the generation of duplicated combinations. We skip the position if the following two condtions are met:

        1). next_curr > curr: we will pick the number at the current curr position into the combination, regardless the other conditions. This is important, since the iteration should allow us to select multiple instances of a unique number into the combination.

        2). candidates[next_curr] == candidates[next_curr-1]: we will skip the occurances all repetitive numbers in-between, e.g. we skip the second and third occurance of number 2 in this round of backtracking.

        The combined effects of the above sorting and iterating operations are equivalent to the previous approach with counter table.

        Algorithm

        It would be clearer to see how the above tricks with index play out in the algorithm.

        Similiar to the previous approach, we implement the backtracking process with the function named backtrack(comb, remain, curr, results), but with less parameters, compared to the previous approach.

        The bulk of the function remains the same as the solution of 39. Combination Sum, except the specific conditions on the index as we discussed before.

        In addition, we optimize the backtracking a bit by adopting the measure of early stopping, i.e. once the sum of current combination exceeds the target, we can stop the exploration for the rest of the numbers. Because all the numbers are positve, as specified in the problem, the sum of combination will increase monotonically. It is needless to explore more combinations whose sum goes beyond the desired target.
        O(2^N)
    """
    def doit(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        def dfs(start, target, item):
            if target == 0:
                result.append(item[:])
                return

            if target < 0:
                return

            for i in range(start, len(candidates)):
                if candidates[i] > target:
                    break
                if i > start and candidates[i] == candidates[i - 1]:
                    continue

                item.append(candidates[i])
                dfs(i + 1, target - candidates[i], item)
                item.pop()

        if candidates is None or len(candidates) == 0:
            return [[]]

        candidates.sort()
        result = []
        dfs(0, target, [])
        return result