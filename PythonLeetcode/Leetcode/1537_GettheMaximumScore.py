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

    """
                1537.Get-the-Maximum-Score
        本题是一个另类的双指针题。

        我们可以认为上路和下路有若干个传送门。当你在某条支路非传送门的位置时，你别无选择，只能继续前进，并将该点的数值加入该支路的score。假设你从上路走到传送门的位置时累计的分数是score1，从下路走到同一个传送门的位置时累计的分数是score2，
        那么你无论之后选择走哪一条路，你都会以max(score1,score2)作为新的base。也就是说，如果score1更大，那么意味着在来到传送门之前，你应该选择的是上路；反之你应该选择的是下路。在传送门之前选择上路或者下路，完全不影响你之后的选择，因为传送门的转移是没有代价的。

        于是我们为上下两路设计两个双指针。当到达传送门之前时，指针各自前进，但都会在同一个传送门的位置停下来。然后综合两者分数的取较大值。然后继续分别走上下两路。

        那么如何让两个指针都恰好在传送门的位置停下来呢？简单的比较两个指针对应的数值大小就行了。如果nums1[i]更小就移动i指针，反之就移动j指针。最终i和j会在同一个传送门停下来。

        注意，指针移动的过程中不能对M取模。必须上下两路都走完了，再在两个score里面取最大值后再取模。
    """
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

    """
        Intuition
        We must take the common elements and won't miss them;
        And there will be two path between the common elements,
        and we will take and only take one path.

        We calculate the sum of both path, and take the bigger one.


        Explanation
        So we apply two points solutions,
        and always take the step in the smaller element.

        If two elements are the same,
        we compare the accumulated sum in the both paths,
        and we pick the bigger one.


        Complexity
        Time O(N)
        Space O(1)
    """
    def doit_twopointer(self, nums1: list, nums2: list) -> int:
        
        n1, n2 = len(nums1), len(nums2)
        i, j = 0, 0
        a, b = 0, 0
        
        
        while i < n1 or j < n2:
            
            if i < n1 and (j == n2 or nums1[i] < nums2[j]):
                a += nums1[i]
                i += 1
            elif j < n2 and (i == n1 or nums1[i] > nums2[j]):
                b += nums2[j]
                j += 1
            else:
                a = b = max(a, b) + nums1[i]
                i += 1
                j += 1
                
        return max(a, b) % (10**9 + 7) 

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