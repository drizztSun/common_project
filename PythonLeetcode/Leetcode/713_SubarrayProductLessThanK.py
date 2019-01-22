# 713. Subarray Product Less Than K

# Your are given an array of positive integers nums.

# Count and print the number of (contiguous) subarrays where the product of all the elements in the subarray is less than k.

# Example 1:
# Input: nums = [10, 5, 2, 6], k = 100
# Output: 8
# Explanation: The 8 subarrays that have product less than 100 are: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
# Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.


class NumSubarrayProductLessThanK:

    def doit1(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        buff = [{nums[i] : 1} if nums[i] < k else {}]

        for i in range(1, len(nums)):
            buff.append({nums[i] : 1} if nums[i] < k else {})
            for val in buff[i-1].keys():
                if val * nums[i] < k:
                    buff[i][val * nums[i]] = buff[i].get(val * nums[i], 0) + buff[i-1][val]
        
        res = 0
        for n in range(len(buff)):
            res += sum(v for v in buff[n].values())
        return res

    def doit(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        cnt = 0
        left = right = 0
        prod = 1
        for right, n in enumerate(nums):
            prod *= n
            while prod >= k and left <= right:
                prod //= nums[left]
                left += 1
            cnt += right - left + 1
        return cnt



if __name__ == "__main__":

    res = NumSubarrayProductLessThanK().doit(nums = [10, 5, 2, 6], k = 100)

    res = NumSubarrayProductLessThanK().doit([10,2,2,5,4,4,4,3,7,7], 289)

    res = 0 