



# 442. Find All Duplicates in an Array


# Given an array of integers, 1 ? a[i] ? n (n = size of array), some elements appear twice and others appear once.

# Find all the elements that appear twice in this array.

# Could you do it without extra space and in O(n) runtime?

# Example:
# Input:
# [4,3,2,7,8,2,3,1]

# Output:
# [2,3]


class findDuplicates:
    def doit(self, nums):
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


    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        # super obvious, O(n^2)
#        dupes = set()
#        for i in range(len(nums)):
#            if nums[i] in nums[i+1:]:
#                dupes.add(nums[i])
#        return list(dupes)
        # better, sort it, O(nlogn)
#        dupes = set()
#        last = None
#        for n in sorted(nums):
#            if n == last:
#                dupes.add(n)
#            last = n
#        return list(dupes)
        # better still, use a set, O(n) amortized
#        seen = set()
#        dupes = set()
#        for n in nums:
#            if n in seen:
#                dupes.add(n)
#            else:
#                seen.add(n)
#        return list(dupes)
        # better better still, take advantage of the fact that all ints are [1, n]

        seen = [False] * (len(nums) + 1)
        dupes = []

        for n in nums:
            if seen[n]:
                dupes.append(n)
            else:
                seen[n] = True

        return dupes
        

if __name__=="__main__":

    res = findDuplicates().doit([4,3,2,7,8,2,3,1])

    pass