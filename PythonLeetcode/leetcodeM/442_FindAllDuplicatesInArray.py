"""
442. Find All Duplicates in an Array


Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements that appear twice in this array.

Could you do it without extra space and in O(n) runtime?

Example:
Input:
[4,3,2,7,8,2,3,1]

Output:
[2,3]

"""


class FindAllDuplicates:


    def doit_hashtable(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        D = set()
        res = []
        for c in nums:
            if c not in D:
                D.add(c)
            else:
                res.append(c)

        return res

    def doit_search(self, nums: list) -> list:

        i = 0
        ans = set()
        while i < len(nums):

            if nums[i] != i+1:
                if nums[nums[i]-1] != nums[i]:
                    nums[nums[i]-1], nums[i] = nums[i], nums[nums[i]-1]
                    continue
                else:
                    ans.add(nums[i])

            i += 1

        return list(ans)

    def doit_(self, nums: list):

        for i in range(len(nums)):
            nums[abs(nums[i])-1] *= -1

        ans = []
        for i in range(len(nums)):

            if nums[abs(nums[i]) - 1] > 0:
                ans.append(abs(nums[i]))
                nums[abs(nums[i]) - 1] *= -1 
        return ans

    def doit_(self, nums: list):

        ans = []
        for i in range(len(nums)):

            if nums[abs(nums[i])-1] < 0:
                ans.append(abs(nums[i]))

            nums[abs(nums[i])-1] *= -1

        return ans
    

if __name__ == '__main__':

    FindAllDuplicates().doit_search([4,3,2,7,8,2,3,1])