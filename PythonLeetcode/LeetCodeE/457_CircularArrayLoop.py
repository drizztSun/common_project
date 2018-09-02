# 457. Circular Array Loop

# You are given an array of positive and negative integers. If a number n at an index is positive, then move forward n steps. 
# Conversely, if it's negative (-n), move backward n steps. Assume the first element of the array is forward next to the last element,
# and the last element is backward next to the first element. Determine if there is a loop in this array.
# 
#  A loop starts and ends at a particular index with more than 1 element along the loop. The loop must be "forward" or "backward'.

# Example 1: Given the array [2, -1, 1, 2, 2], there is a loop, from index 0 -> 2 -> 3 -> 0.

# Example 2: Given the array [-1, 2], there is no loop.

# Note: The given array is guaranteed to contain no element "0".

# Can you do it in O(n) time complexity and O(1) space complexity?


class CircularArrayLoop(object):

    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """

        # For each starting num, attempt to find a sequence of n steps, which implies there must be a loop.
        # A loop is not found if any step returns to the same index or moves in the opposite direction.
        n = len(nums)

        for i, num in enumerate(nums):

            pos = num > 0               # direction of movements
            j = (i + num) % n           # take the first step
            steps = 1

            while steps < n and nums[j] % n != 0 and (nums[j] > 0) == pos:
                j = (j + nums[j]) % n   # take the next step
                steps += 1

            if steps == n:              # loop is found
                return True
            
            j = i
            while nums[j] % n != 0 and pos == (nums[j] > 0):
                nums[j], j = 0, (j + nums[j]) % n

        return False


    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        def next(self, nums, dire, index):
            if index is None:
                return None

            if dire * nums[index] <= 0:
                return None

            next_index = (index + nums[index]) % len(nums)
            if next_index == index:
                return None

            return next_index  

        for i, num in enumerate(nums):
            slow = i
            dire = num
            fast = next(nums, dire, slow)
            while slow is not None and fast is not None and slow != fast:
                slow = next(nums, dire, slow)
                fast = next(nums, dire, next(nums, dire, fast))

            if slow is not None and slow == fast:
                return True
        return False


if __name__ == "__main__":

    res = CircularArrayLoop().doit([2, -1, 1, 2, 2]) #loop [0, 2, 3, 0]

    res = 1

      

            