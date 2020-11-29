"""
1424. Diagonal Traverse II

Given a list of lists of integers, nums, return all elements of nums in diagonal order as shown in the below images.


Example 1:



Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,4,2,7,5,3,8,6,9]
Example 2:



Input: nums = [[1,2,3,4,5],[6,7],[8],[9,10,11],[12,13,14,15,16]]
Output: [1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16]
Example 3:

Input: nums = [[1,2,3],[4],[5,6,7],[8],[9,10,11]]
Output: [1,4,2,5,3,8,6,9,7,10,11]
Example 4:

Input: nums = [[1,2,3,4,5,6]]
Output: [1,2,3,4,5,6]


Constraints:

1 <= nums.length <= 10^5
1 <= nums[i].length <= 10^5
1 <= nums[i][j] <= 10^9
There at most 10^5 elements in nums.


"""


class DiagonalTraverseII:


    """
    O(E) E is total numbers
    """
    def doit_math(self, nums: list) -> list:

        rows, cols = len(nums), max(len(nums[k]) for k in range(len(nums)))
        lines = rows + cols - 1
        ans = [[] for _ in range(lines)]

        for i in range(rows-1, -1, -1):

            for j in range(len(nums[i])):

                ans[(i + j) % lines].append(nums[i][j])

        res = []
        for c in ans:
            res.extend(c)
        return res

    """
    O(n * m)
    """
    def doit_math_tle(self, nums: list) -> list:

        ans = []
        rows, cols = len(nums), max(len(nums[k]) for k in range(len(nums)))

        for i in range(rows + cols - 1):

            x, y = (i, 0) if i <= rows - 1 else (rows - 1, i - rows + 1)

            while x >= 0:
                if y < len(nums[x]):
                    ans.append(nums[x][y])
                x -= 1
                y += 1

        return ans

