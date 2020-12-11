"""
1537. Get the Maximum Score

You are given two sorted arrays of distinct integers nums1 and nums2.

A valid path is defined as follows:

Choose array nums1 or nums2 to traverse (from index-0).
Traverse the current array from left to right.
If you are reading any value that is present in nums1 and nums2 you are allowed to change your path to the other array.
(Only one repeated value is considered in the valid path).
Score is defined as the sum of uniques values in a valid path.

Return the maximum score you can obtain of all possible valid paths.

Since the answer may be too large, return it modulo 10^9 + 7.



Example 1:



Input: nums1 = [2,4,5,8,10], nums2 = [4,6,8,9]
Output: 30
Explanation: Valid paths:
[2,4,5,8,10], [2,4,5,8,9], [2,4,6,8,9], [2,4,6,8,10],  (starting from nums1)
[4,6,8,9], [4,5,8,10], [4,5,8,9], [4,6,8,10]    (starting from nums2)
The maximum is obtained with the path in green [2,4,6,8,10].
Example 2:

Input: nums1 = [1,3,5,7,9], nums2 = [3,5,100]
Output: 109
Explanation: Maximum sum is obtained with the path [1,3,5,100].
Example 3:

Input: nums1 = [1,2,3,4,5], nums2 = [6,7,8,9,10]
Output: 40
Explanation: There are no common elements between nums1 and nums2.
Maximum sum is obtained with the path [6,7,8,9,10].
Example 4:

Input: nums1 = [1,4,5,8,9,11,19], nums2 = [2,3,4,11,12]
Output: 61


Constraints:

1 <= nums1.length <= 10^5
1 <= nums2.length <= 10^5
1 <= nums1[i], nums2[i] <= 10^7
nums1 and nums2 are strictly increasing.



"""


class GetTheMaximumScore:

    def doit_twopointer(self, nums1: list, nums2: list) -> int:

        m, n = len(nums1), len(nums2)
        i, j = 0, 0
        x, y = 0, 0

        while i < m or j < n:

            if i == m:
                y += nums2[j]
                j += 1
            elif j == n:
                x += nums1[i]
                i += 1
            elif nums1[i] < nums2[j]:
                x += nums1[i]
                i += 1
            elif nums1[i] > nums2[j]:
                y += nums2[j]
                j += 1
            elif nums1[i] == nums2[j]:
                y = max(x, y) + nums1[i]
                x = y
                i += 1
                j += 1

        return max(x, y) % (10**9+7)




    def doit_dfs(self, nums1: list, nums2: list) -> int:

        pos1 = {c: i for i, c in enumerate(nums1)}
        pos2 = {c: i for i, c in enumerate(nums1)}

        dp = {}

        def search(i, p):

            if p == 0 and i == len(nums1) or p == 1 and i == len(nums2):
                return 0

            if (i, p) in dp:
                return dp[(i, p)]

            ans = search(i+1, p)

            if p == 0 and nums1[i] in pos2:
                ans = max(ans, search(pos2[nums1[i]], 1 - p))
            elif p == 1 and nums2[i] in pos1:
                ans = max(ans, search(pos1[nums2[i]]), 1 - p)

            ans += nums1[i] if p == 0 else nums2[i]

            dp[(i, p)] = ans
            return ans

        return max(search(0, 0), search(0, 1)) % (10**9 + 7)

        def doit_dfs_2(self, nums1: list, nums2: list):

            def arrSum(array, other):
                ans = []
                sum = 0

                for num in array:
                    if num in other:
                        ans.append(sum)
                        sum = 0
                    sum += num
                ans.append(sum)
                return ans

            n1, n2 = set(nums1), set(nums2)
            l1, l2 = arrSum(nums1, n2), arrSum(nums2, n1)

            ans = 0

            for idx in range(len(l1)):
                ans += max(l1[idx], l2[idx])

            return ans % (10 ** 9 + 7)


if __name__ == '__main__':

    GetTheMaximumScore().doit(nums1 = [2,4,5,8,10], nums2 = [4,6,8,9])

    GetTheMaximumScore().doit(nums1 = [1,3,5,7,9], nums2 = [3,5,100])

    GetTheMaximumScore().doit(nums1 = [1,2,3,4,5], nums2 = [6,7,8,9,10])

    GetTheMaximumScore().doit(nums1 = [1,4,5,8,9,11,19], nums2 = [2,3,4,11,12])