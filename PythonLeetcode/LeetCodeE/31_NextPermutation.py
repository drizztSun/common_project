# 31. Next Permutation

# Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

# If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

# The replacement must be in-place and use only constant extra memory.

# Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

# 1,2,3 ? 1,3,2
# 3,2,1 ? 1,2,3
# 1,1,5 ? 1,5,1


class NextPermutation(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        for l in range(len(nums) - 2, -1, -1):

            r = len(nums) - 1
            while l < r and nums[l] >= nums[r]:
                r -= 1

            if l != r:
                nums[l], nums[r] = nums[r], nums[l]
                nums[l+1:] = sorted(nums[l+1:])
                return
                
        nums.sort()

    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        len_n = len(nums)
        if len_n < 2: 
            return 
        
        j = len_n - 2
        switch_a = -1
        while j >= 0:
            if nums[j] < nums[j+1]:
                switch_a = j
                break
            j -= 1

        if switch_a >= 0:
            # find switch b
            i = switch_a + 1
            switch_b = len_n - 1
            while i < len_n and nums[i] > nums[switch_a]:
                i += 1
            else:
                switch_b = i - 1
            nums[switch_a], nums[switch_b] = nums[switch_b], nums[switch_a]
        
        # reverse nums[switch_a+1: len_n]
        f = switch_a + 1
        b = len_n - 1
        while f < b:
            nums[f], nums[b] = nums[b], nums[f]
            f += 1
            b -= 1
        return 


if __name__ == "__main__":

    A = [1, 2, 3]

    NextPermutation().doit(A)

    A = [1, 1, 5]
    
    NextPermutation().doit(A)

    A = [1, 5, 1]
    
    NextPermutation().doit(A)

    pass