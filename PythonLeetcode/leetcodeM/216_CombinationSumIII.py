"""
216. Combination Sum III

Find all valid combinations of k numbers that sum up to n such that the following conditions are true:

Only numbers 1 through 9 are used.
Each number is used at most once.
Return a list of all possible valid combinations. The list must not contain the same combination twice, and the combinations may be returned in any order.

 

Example 1:

Input: k = 3, n = 7
Output: [[1,2,4]]
Explanation:
1 + 2 + 4 = 7
There are no other valid combinations.
Example 2:

Input: k = 3, n = 9
Output: [[1,2,6],[1,3,5],[2,3,4]]
Explanation:
1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9
There are no other valid combinations.
Example 3:

Input: k = 4, n = 1
Output: []
Explanation: There are no valid combinations. [1,2,1] is not valid because 1 is used twice.
Example 4:

Input: k = 3, n = 2
Output: []
Explanation: There are no valid combinations.
Example 5:

Input: k = 9, n = 45
Output: [[1,2,3,4,5,6,7,8,9]]
Explanation:
1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 = 45
​​​​​​​There are no other valid combinations.
 

Constraints:

2 <= k <= 9
1 <= n <= 60

"""



class CombinationIII:

    """
    Approach 1: Backtracking
    Intuition

    The problem asks us to come up with some fixed-length combinations that meet certain conditions.

    To solve the problem, it would be beneficial to build a combination by hand.

    If we represent the combination as an array, we then could fill the array one element at a time.

    For example, given the input k=3k=3 and n=9n=9, i.e. the size of the combination is 3, and the sum of the digits in the combination should be 9. Here are a few steps that we could do:
    """

    def combinationSum3(self, k: int, n: int) -> list:
        results = []
        def backtrack(remain, comb, next_start):
            if remain == 0 and len(comb) == k:
                # make a copy of current combination
                # Otherwise the combination would be reverted in other branch of backtracking.
                results.append(list(comb))
                return
            elif remain < 0 or len(comb) == k:
                # exceed the scope, no need to explore further.
                return

            # Iterate through the reduced list of candidates.
            for i in range(next_start, 9):
                comb.append(i+1)
                backtrack(remain-i-1, comb, i+1)
                # backtrack the current choice
                comb.pop()

        backtrack(n, [], 0)

        return results

    def doit_backtracking(self, k: int, n: int) -> list:

        def backtracking(i, d, path, target):
            if i == k:
                if target == 0: 
                    res.append(path[:])
                return

            for j in range(d, 10):
                if target < j: break

                path.append(j)
                backtracking(i+1, j+1, path, target - j)
                path.pop()

        res = []
        backtracking(0, 1, [], n)
        return res

if __name__ == '__main__':

    CombinationIII().doit_backtracking(9, 45)