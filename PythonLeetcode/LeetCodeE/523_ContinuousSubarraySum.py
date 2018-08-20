# 523. Continuous Subarray Sum

# Given a list of non-negative numbers and a target integer k, write a function to check if the array has a 
# continuous subarray of size at least 2 that sums up to the multiple of k, that is, sums up to n*k where n is also an integer.

# Example 1:
# Input: [23, 2, 4, 6, 7],  k=6
# Output: True
# Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.

# Example 2:
# Input: [23, 2, 6, 4, 7],  k=6
# Output: True
# Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.

# Note:
# The length of the array won't exceed 10,000.
# You may assume the sum of all the numbers is in the range of a signed 32-bit integer.


class CheckSubarraySum(object):


    def doit(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: bool
        """
        buff = { 0 : -1}
        runningTotal = 0

        for i in range(0, len(nums)):

            runningTotal += nums[i]

            if k != 0:
                runningTotal %= k

            if runningTotal in buff:
                if i - buff[runningTotal] > 1:
                    return True
            else:
                buff[runningTotal] = i 

        return False        


    # wrong, because it is continuous subarray sequence
    def doit1(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: bool
        """
        from collections import Counter
        remains = [ nums[x] % 6 for x in range(len(nums))]
        cnt = Counter(remains)
        keys = list(cnt.keys())

        def search(i, total):
            if total > 0 and total % 6 == 0:
                return True

            for j in range(i, len(keys)):
                if cnt[keys[j]] > 0:
                    cnt[keys[j]] -= 1
                    if search(j, total + keys[j]):
                        return True
                    cnt[keys[j]] += 1

            return False

        return search(0, 0)
        
        
            
    


if __name__ == "__main__":

    res = CheckSubarraySum().doit([23, 2, 4, 6, 7],  k = 6)

    res = CheckSubarraySum().doit([23, 2, 6, 4, 7],  k = 6)

    res = CheckSubarraySum().doit([0, 0], 0)

    pass