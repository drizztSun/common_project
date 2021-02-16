"""
1546. Maximum Number of Non-Overlapping Subarrays With Sum Equals Target


Given an array nums and an integer target.

Return the maximum number of non-empty non-overlapping subarrays such that the sum of values in each subarray is equal to target.

 

Example 1:

Input: nums = [1,1,1,1,1], target = 2
Output: 2
Explanation: There are 2 non-overlapping subarrays [1,1,1,1,1] with sum equals to target(2).
Example 2:

Input: nums = [-1,3,5,1,4,2,-9], target = 6
Output: 2
Explanation: There are 3 subarrays with sum equal to 6.
([5,1], [4,2], [3,5,1,4,2,-9]) but only the first 2 are non-overlapping.
Example 3:

Input: nums = [-2,6,6,3,5,4,1,2,8], target = 10
Output: 3
Example 4:

Input: nums = [0,0,0], target = 0
Output: 3
 

Constraints:

1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
0 <= target <= 10^6


"""


class MaxNonOverlapping:
    
    def doit_greedy_hashtable(self, nums: list, target: int) -> int:

        from collections import defaultdict
        
        presum, buff = [], defaultdict(int)
        start, ans = -1, 0
        buff[0] = -1

        for i in range(len(nums)):
            
            cur = nums[i] + (presum[-1] if len(presum) > 0 else 0)
            presum.append(cur)
            cur -= target

            if cur in buff and start <= buff[cur]:
                ans += 1
                start = i+1

            buff[presum[-1]] = i+1

        return ans

    def doit_hashtable(self, nums: list, target: int) -> int:
        from collections import defaultdict
        ans = { 0: 0 }
        total = 0
        count = 0
        
        for num in nums:
            total += num
            if total-target in ans:
                count = max(count, ans[total-target]+1)
            ans[total] = count

        return ans[total]



        