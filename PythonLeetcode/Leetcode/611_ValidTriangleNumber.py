# 611. Valid Triangle Number


# Given an array consists of non-negative integers, your task is to count the number of triplets chosen from the array that can make triangles 
# if we take them as side lengths of a triangle.

# Example 1:
# Input: [2,2,3,4]
# Output: 3
# Explanation:
# Valid combinations are: 
# 2,3,4 (using the first 2)
# 2,3,4 (using the second 2)
# 2,2,3

# Note:
# The length of the given array won't exceed 1000.
# The integers in the given array are in the range of [0, 1000].


class TriangleNumber:


    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        count = 0

        for i in range(2, len(nums)):
            
            low = 0
            high = i - 1

            while low < high:

                if nums[lows] + nums[high] > nums[i]:
                    count += high - low
                    high -= 1
                else:
                    low += 1

        return count
                          

    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        lines, count = sorted(nums, reverse = 1), 0

        for i in range(len(lines)):

            j, e = i + 1, len(lines) - 1

            while j < k:

                if lines[j] + lines[k] > lines[i]:
                    count += k - j
                    j += 1                    

                else:
                    e -= 1
        return 



    # TLE
    def doitError(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        self.count_ = 0
        self.array_ = []

        def triangle(lines):
            nums = sorted(lines)
            if nums[0] + nums[1] > nums[2]:
                self.array_.append(nums)

            return nums[0] + nums[1] > nums[2]

        def search(nums, i, lines):

            if len(lines) == 3:
                if triangle(lines):
                    self.count_ += 1
                return

            for j in range(i + 1, len(nums)):

                lines.append(nums[j])
           
                search(nums, j, lines)

                lines.pop()
            
        search(nums, -1, [])

        return self.count_



if __name__ == "__main__":

    res = TriangleNumber().doit([2, 2, 3, 4])

    res = TriangleNumber().doit([2, 2, 2, 2, 3, 4])

    res = TriangleNumber().doit([48, 66, 61, 46, 94, 75])

    res = TriangleNumber().doit([86,2,54,7,10,60,25,87,66,7,68,10,19,70,40,15,46,71,9,34,74,24,8,33,80,71,1,29,19,38,20,56,14,67,70,100,74,33,79,6,92,83,70,22,14,88,48,38,61,1,76,53,67,6,23,39,66,50,54,17,1,61,43,57,0,45,55,56,21,94,70,22,100,20,75,25,28,5,80,48,8,33,100,69,10,34,52,21,38,20,41,84,89,99,83,18,43,11,61,65])

    res = 1

        