# 556. Next Greater Element III

# Given a positive 32-bit integer n, you need to find the smallest 32-bit integer 
# which has exactly the same digits existing in the integer n and is greater in value than n.
# If no such positive 32-bit integer exists, you need to return -1.

# Example 1:

# Input: 12
# Output: 21
 

# Example 2:

# Input: 21
# Output: -1


class NextGreaterElementIII(object):

    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        nums = [ c for c in str(n) ]
        for l in range(len(nums) - 2, -1, -1):

            r = len(nums) - 1
            while l < r and nums[r] <= nums[l]:
                r -= 1

            if l != r:
                nums[l], nums[r] = nums[r], nums[l]
                nums[l+1:] = sorted(nums[l+1:])

                num = int(''.join(nums))
                return num if -2**31 - 1 <= num <= 2**31 -1 else -1
        
        return -1


if __name__ == "__main__":

    res = NextGreaterElementIII().doit("12")

    res = NextGreaterElementIII().doit("21")

    pass