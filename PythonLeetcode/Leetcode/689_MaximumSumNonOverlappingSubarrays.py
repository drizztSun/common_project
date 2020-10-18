"""
# 689. Maximum Sum of 3 Non-Overlapping Subarrays

# In a given array nums of positive integers, find three non-overlapping subarrays with maximum sum.

# Each subarray will be of size k, and we want to maximize the sum of all 3*k entries.

# Return the result as a list of indices representing the starting position of each interval (0-indexed).
# If there are multiple answers, return the lexicographically smallest one.

# Example:
# Input: [1,2,1,2,6,7,5,1], 2
# Output: [0, 3, 5]

# Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
# We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.

# Note:
# nums.length will be between 1 and 20000.
# nums[i] will be between 1 and 65535.
# k will be between 1 and floor(nums.length / 3).

"""


class MaxSumOfThreeSubarrays:

    """
    Approach #1: Ad-Hoc [Accepted]
    Intuition

    It is natural to consider an array W of each interval's sum, where each interval is the given length k.
    To create W, we can either use prefix sums, or manage the sum of the interval as a window slides along the array.

    From there, we approach the reduced problem: Given some array W and an integer k, what is the lexicographically smallest tuple of indices (i, j, l) with i + l <= j and j + k <= l that maximizes W[i] + W[j] + W[l]?

    Algorithm

    Suppose we fixed j.
    We would like to know on the intervals i \in [0, j - k]i∈[0,j−k] and l \in [j + k, \text{len}(W) - 1]l∈[j+k,len(W)−1], where the largest value of W[i]W[i] (and respectively W[l]W[l]) occurs first.
    (Here, first means the smaller index.)

    We can solve these problems with dynamic programming.
    For example, if we know that ii is where the largest value of W[i]W[i] occurs first on [0, 5][0,5], then on [0, 6][0,6] the first occurrence of the largest W[i]W[i] must be either ii or 66.
    If say, 66 is better, then we set best = 6.

    At the end, left[z] will be the first occurrence of the largest value of W[i] on the interval i \in [0, z]i∈[0,z], and right[z] will be the same but on the interval i \in [z, \text{len}(W) - 1]i∈[z,len(W)−1].
    This means that for some choice j, the candidate answer must be (left[j - k], j, right[j + k]). We take the candidate that produces the maximum W[i] + W[j] + W[l].

    """
    def doit_dp(self, nums, k: int):
        W = []  # array of sums of windows
        curr_sum = 0
        for i, x in enumerate(nums):
            curr_sum += x
            if i >= k:
                curr_sum -= nums[i - k]
            if i >= k - 1:
                W.append(curr_sum)

        left = [0] * len(W)
        best = 0
        for i in range(len(W)):
            if W[i] > W[best]:
                best = i
            left[i] = best

        right = [0] * len(W)
        best = len(W) - 1
        for i in range(len(W) - 1, -1, -1):
            if W[i] >= W[best]:
                best = i
            right[i] = best

        ans = None
        for j in range(k, len(W) - k):
            i, l = left[j - k], right[j + k]
            if ans is None or (W[i] + W[j] + W[l] > W[ans[0]] + W[ans[1]] + W[ans[2]]):
                ans = i, j, l
        return ans

    """
    # I must admit that those start and end points of for loops are really disgusting due to problem :)
    # We first calculate sum(nums[i:i + k]), sum of one single subarray, for suitable indexes and store them in "single" dictionary.
    # After that from right to left we match next max subarray for each suitable subarray and store two subarrays information in "double" dictionary.
    # Finally, we match next max subarray couple (double) for each suitable subarray and change result if current subarray + couple bigger than result (sm).
    # Return result
    """

    def doit(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        n = len(nums)
        single, double, cur = {}, {}, sum(nums[0:k])
        
        for i in range(k-1, n):
            cur += nums[i]
            single[i - k + 1] = cur
            cur -= nums[i - k + 1]
            
        cur = (n - k, single[n - k])
        for i in range(n - k, k - 1, -1):
            if single[i] >= cur[1]:
                cur = (i, single[i])
            double[i - k] = (cur[1] + single[i - k], i - k, cur[0])
            
        cur = double[n - 2 * k]
        third, res = 0, []
        for i in range(n - 2 * k, k - 1, -1):
            if double[i][0] >= cur[0]:
                cur = double[i]
                
            if single[i - k] + cur[0] >= third:
                third = single[i - k] + cur[0]
                res = [i - k, cur[1], cur[2]]
                
        return res
            

    """
    # Since it's 3 non-overlapping sub-array, we can divide it into left, mid, right.
    # Suppose mid is [i, i+k-1] because it needs to hav at least k elements, then
    # we can have left is from [0,i-1] and right is from [i+k, n-1].
    
    # Since left must have at least k elements then i-1-0+1 >= k , thus we have i>=k
    # Same thing for the right, since n-1-(i-k)+1 >= k, thus we have i<=n-2k
    # Thus we have k<=i<=n-2k , this is very important math to figure out.
    
    # Then we have 2 arrays which stores the maximum starting index from left and from right.
    
    # Finally, we figure out when i is in the range mentioned above, what would be the max from left and right and take
    # the global max.
    
    # k<=i<=n-2k 
    
    """
    # <DP>
    def doit_dp(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        N = len(nums)
        sums = [0 for _ in range(N + 1)]
        for i in range(N):
            sums[i+1] = sums[i] + nums[i]
        
        # left[i] left side maximum of subarray
        left, leftM = [0 for _ in range(N)], sums[k] - sums[0] 
        for i in range(k, N):
            if sums[i + 1] - sums[i + 1 - k] > leftM:
                left[i] = i - k + 1
                leftM = sums[i + 1] - sums[i + 1 - k]
            else:
                left[i] = left[i - 1]

        # right[i] right side maximum of subarray 
        right, rightM = [0 for _ in range(N)], sums[N] - sums[N - k]
        right[N - k] = N - k 
        for i in range(N - k - 1, -1, - 1):
            if sums[i + k] - sums[i] > rightM:
                right[i] = i
                rightM = sums[i + k] - sums[i]
            else:
                right[i] = right[i + 1]              

        maxV = 0
        for i in range(k, N - 2 * k + 1):
            l, r = left[i-1], right[i + k]
            leftMax = sums[l + k] - sums[l]
            rightMax = sums[r + k] - sums[r]

            total = leftMax + rightMax + sums[i + k] - sums[i] 
                                     
            if total >= maxV:
                maxV = total
                res = [l, i, r]

        return res


if __name__ == "__main__":

    res = MaxSumOfThreeSubarrays().doit_dp([1,2,1,2,6,7,5,1], 2) # [0, 3, 5]

    res = MaxSumOfThreeSubarrays().doit_dp([7,13,20,19,19,2,10,1,1,19], 3) # [1,4,7]

    pass