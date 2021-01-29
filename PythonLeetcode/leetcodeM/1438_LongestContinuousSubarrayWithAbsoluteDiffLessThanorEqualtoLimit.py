"""
1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit


Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to limit.

 

Example 1:

Input: nums = [8,2,4,7], limit = 4
Output: 2 
Explanation: All subarrays are: 
[8] with maximum absolute diff |8-8| = 0 <= 4.
[8,2] with maximum absolute diff |8-2| = 6 > 4. 
[8,2,4] with maximum absolute diff |8-2| = 6 > 4.
[8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
[2] with maximum absolute diff |2-2| = 0 <= 4.
[2,4] with maximum absolute diff |2-4| = 2 <= 4.
[2,4,7] with maximum absolute diff |2-7| = 5 > 4.
[4] with maximum absolute diff |4-4| = 0 <= 4.
[4,7] with maximum absolute diff |4-7| = 3 <= 4.
[7] with maximum absolute diff |7-7| = 0 <= 4. 
Therefore, the size of the longest subarray is 2.
Example 2:

Input: nums = [10,1,2,4,7,2], limit = 5
Output: 4 
Explanation: The subarray [2,4,7,2] is the longest since the maximum absolute diff is |2-7| = 5 <= 5.
Example 3:

Input: nums = [4,2,2,2,4,4,2,2], limit = 0
Output: 3
 

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
0 <= limit <= 10^9


"""


class LongestSubarray:
   
    """
        Monotonic queue
    """
    def doit_monotonic_queue(self, nums: list, limit: int) -> int:

        from collections import deque

        l, r, ans = 0, 0, 0

        minv, maxv = deque([float('inf')]), deque([float('-inf')])

        while r < len(nums):

            while minv and minv[-1] > nums[r]:
                minv.pop()

            while maxv and maxv[-1] < nums[r]:
                maxv.pop()

            minv.append(nums[r])
            maxv.append(nums[r])

            if abs(maxv[0] - minv[0]) <= limit:
                ans = max(ans, r - l + 1)


            while l < r and abs(maxv[0] - minv[0]) > limit:

                if maxv[0] == nums[l]: 
                    maxv.popleft()

                if minv[0] == nums[l]:
                    minv.popleft()

                l += 1

            r += 1

        return ans

    def doit_monotonic_queue(self, nums: list, limit: int) -> int:

        from collections import deque

        min_vals = deque()
        max_vals = deque()
        idx = 0
        
        for num in nums:
            while min_vals and num < min_vals[-1]:
                min_vals.pop()
            
            while max_vals and num > max_vals[-1]:
                max_vals.pop()
            
            min_vals.append(num)
            max_vals.append(num)
            
            if max_vals[0] - min_vals[0] > limit:
                if nums[idx] == min_vals[0]:
                    min_vals.popleft()
                
                elif nums[idx] == max_vals[0]:
                    max_vals.popleft()
                    
                idx += 1
        
        return len(nums) - idx



            



        