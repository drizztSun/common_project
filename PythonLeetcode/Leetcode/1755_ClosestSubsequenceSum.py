"""
1755. Closest Subsequence Sum


You are given an integer array nums and an integer goal.

You want to choose a subsequence of nums such that the sum of its elements is the closest possible to goal.
That is, if the sum of the subsequence's elements is sum, then you want to minimize the absolute difference abs(sum - goal).

Return the minimum possible value of abs(sum - goal).

Note that a subsequence of an array is an array formed by removing some elements (possibly all or none) of the original array.



Example 1:

Input: nums = [5,-7,3,5], goal = 6
Output: 0
Explanation: Choose the whole array as a subsequence, with a sum of 6.
This is equal to the goal, so the absolute difference is 0.
Example 2:

Input: nums = [7,-9,15,-2], goal = -5
Output: 1
Explanation: Choose the subsequence [7,-9,-2], with a sum of -4.
The absolute difference is abs(-4 - (-5)) = abs(1) = 1, which is the minimum.
Example 3:

Input: nums = [1,2,3], goal = -7
Output: 7


Constraints:

1 <= nums.length <= 40
-10^7 <= nums[i] <= 10^7
-10^9 <= goal <= 10^9


All Python TLE, 

"""
from bisect import bisect_left


class MinAbsDifference:


    def doit_dfs(self, nums: list, goal: int):

        n = len(nums)
        q, cnt = [0] * (1<<n), 0
        ans = float('inf')

        def dfs1(u, s):
            nonlocal cnt, n, q
            if u == (n+1) // 2:
                q[cnt] = s
                cnt += 1
                return

            dfs1(u+1, s)
            dfs1(u+1, s + nums[u])

        def dfs2(u, s):
            nonlocal ans
            if u == n:
                l, r = 0, cnt - 1
                while l < r:
                    mid = (l + r + 1) // 2

                    if q[mid] + s <= goal:
                        l = mid
                    else:
                        r = mid - 1

                ans = min(ans, abs(q[r] + s - goal))

                if r + 1 < cnt:
                    ans = min(ans, abs(q[r+1] + s - goal))
                
                return

            dfs2(u+1, s)
            dfs2(u+1, s + nums[u])

        dfs1(0, 0)
        q[:cnt] = sorted(q[:cnt])
        dfs2((n+1)//2, 0)

        return ans

    """
    
        1755.Closest-Subsequence-Sum
        这道题的数据范围限定了解题方法。

        如果nums的元素不超过20个，那么我们可以穷举所有的subset sum，最多有2^20 = 1e6，时间复杂度是可以接受的。我们遍历一下这些subset，找到最接近goal的那个即可。

        如果nums的元素很多，但是值的范围很小，比如说限定了都是正数、所有的和不超过1000之类的，那么就可以当做动态规划来解。每处理一个新元素x，我们遍历所有subset sum的可能，更新dp[sum] = dp[sum-x].

        对于本题而言，以上两种方法都不适用。对于有经验的同学而言，nums的元素个数是40，提示了一种非常巧妙的解法：就是将nums平均拆成两个数组nums1和nums2来处理。
        对于每个数组，我们分别可以穷举所有的subset sum，时间复杂度是o(2^N/2)，然后各自排序得到sum1和sum2。然后对于sum1的每个元素x而言，我们要在sum2里面找到最接近goal-x的那个。
        反之对于sum2的每个元素x而言，我们要在sum1里面找到最接近goal-x的那个。最后找到全局最接近的abs diff即可。

        在上面的解法中，如果先求得所有的subset sum，然后排序，将会使得时间复杂度达到o(MlogM)，其中M=2^N/2. 有一种方法可以直接用o(2^N/2)得到有序的subset sum。
        假设nums的前i-1个元素已经得到了有序的subset sum的集合{a_k},那么加上第i个元素之后的subset sum的集合就是{a_k}和{a_k+nums[i]}的并集。我们发现这两个集合是各自有序的，这样我们可以用归并排序的方法将两者合并成一个更大的有序集合。


        num.size() <= 20
        check every subset sum: 2^20

        total |nums| sum <= 1000

        data is too big to use DP
        for (int i = 0; i < nums.size(); i++)
            dp[sum] = dp_old[sum]
            for sum in range(0, 1000):
                dp[sum] = dp_old[sum-nums[i]]

        No, this problem is NP-complete. It's basically https://en.wikipedia.org/wiki/Subset_sum_problem
        So there is a DP approach which has the complexity of O(n * goal), but goal can be up to 10^9, so it's too slow.
        Given n < 40 and goal < 10^9 the only possible exact approach is an optimised bruteforce (e.g. using meet in the middle technique).

        // vector<int> getSubSetsSum(vector<int>&nums)
        // {
        //     vector<int> sums;
        //     int m = nums.size();
        //     for (int state=0; state<(1<<m); state++)
        //     {
        //         int sum = 0;
        //         for (int i=0; i<32; i++)
        //         {
        //             if ((state>>i)&1)
        //                 sum += nums[i];
        //         }
        //         sums.push_back(sum);
        //     }
        //     sort(sums.begin(), sums.end());
        //     return sums;
        // }
    
    
    """




    def doit_(self, nums: list, goal: int) -> int:

        m = len(nums)

        first = nums[:m+1]
        second = nums[m+1:]

        def getallsums(targets):

            sums = [0]

            for x in targets:

                tmp = []
                i, j, n = 0, 0, len(sums)

                while i < n and j < n:

                    if sums[i] + x < sums[j]:
                        tmp.append(sums[i] + x)
                        i += 1
                    else:
                        tmp.append(sums[j])
                        j += 1

                while i < n:
                    tmp.append(sums[i] + x)
                    i += 1

                while j < n:
                    tmp.append(sums[j])
                    j += 1

                sums = tmp

            return sums

        def findClosestSum(A, B):

            res = float('inf')
            for x in A:

                t = bisect_left(B, goal - x)
                if t != len(B):
                    res = min(res, abs(B[t] + x - goal))

                if t != 0:
                    res = min(res, abs(B[t-1] + x - goal))

            return res

        firstsums, secondsums = getallsums(first), getallsums(second)

        return min(findClosestSum(firstsums, secondsums), findClosestSum((secondsums, firstsums)))



