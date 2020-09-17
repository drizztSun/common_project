"""
# 327. Count of Range Sum

# Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
# Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ? j), inclusive.

# Note:
# A naive algorithm of O(n2) is trivial. You MUST do better than that.

# Example:
# Given nums = [-2, 5, -1], lower = -2, upper = 2,
# Return 3.
# The three ranges are : [0, 0], [2, 2], [0, 2] and their respective sums are: -2, -1, 2.

"""


class Segnode:
    def __init__(self, s, e, val=0):
        self.s_, self.e_ = s, e
        self.sum_ = val
        self.left_, self.right_ = None, None


class Segtree:

    def __init__(self, nums):

        self.root_ = self.buildTree(nums)
        
    def buildTree(self, nums):

        def forge(s, e, nums) :
            
            if s == e:
                return Segnode(s, e, nums[s])

            mid = (s + e) // 2

            root = Segnode(s, e)
            root.left_ = forge(s, mid, nums)
            root.right_ = forge(mid+1, e, nums)
            root.sum_ = root.left_.sum_ + root.right_.sum_

            return root

        if not nums:
            return 0

        return forge(0, len(nums) - 1, nums)

    def segsum(self, s, e):
        
        def search(node, s, e):

            if s <= node.s_ and node.e_ <= e:
                return node.sum_

            mid = (node.s_ + node.e_) // 2
            res = 0

            if mid >= e :
                res = search(s, e, node.left_)
            elif mid <= s:
                res = search(s, e, node.right_) 
            else:
                res = search(s, mid, node.left_) + search(mid+1, e, node.right_);
            
            return res

        return search(self.root_, s, e)
    
    def searchSeg(self, lower, upper):

        def search(node, lower, upper):
            if not node:
                return 0

            res = 0
            if lower <= node.sum_ <= upper:
                res += 1

            mid = (node.s_ + node.e_) // 2

            res += search(node.left_, lower, upper) + search(node.right_, lower, upper)
            return res
       
        return search(self.root_, lower, upper)


class CountRangeSum:

    """
    # First compute the prefix sums: first[m] is the sum of the first m numbers.
    # Then the sum of any subarray nums[i:k] is simply first[k] - first[i].
    # So we just need to count those where first[k] - first[i] is in [lower,upper].

    # To find those pairs, I use mergesort with embedded counting.
    # The pairs in the left half and the pairs in the right half get counted in the recursive calls.
    # We just need to also count the pairs that use both halves.

    # For each left in first[lo:mid], I find all right in first[mid:hi] so that right - left lies in [lower, upper].
    # Because the halves are sorted, these fitting right values are a subarray first[i:j].
    # With increasing left we must also increase right, meaning must we leave out first[i]
    # if it’s too small and and we must include first[j] if it’s small enough.

    # Besides the counting, I also need to actually merge the halves for the sorting.
    # I let sorted do that, which uses Timsort and takes linear time to recognize and merge the already sorted halves.
    """
    def doit_divide_and_conquer(self, nums, lower, upper):
        """
        :type nums: List[int]
        :type lower: int
        :type upper: int
        :rtype: int
        """
        first = [0]
        for c in nums:
            first.append(first[-1] + c)

        def search(low, high):

            mid = (low + high) // 2
            count = 0

            if low == mid:
                return 0

            count = search(low, mid) + search(mid, high)
            # i, j both are  in the higher block, because each one's index in higher block is greater than lower block.
            # Than (first[i], first[j]] includes all element, which substracted left is still in [lower, high] scope
            i, j = mid, mid
            for left in first[low: mid]:
                
                # 
                while i < high and first[i] - left < lower:
                    i += 1

                while j < high and first[j] - left <= upper:
                    j += 1

                count += j - i

            # sort the sum array in [low, high]
            first[low:high] = sorted(first[low: high])

            return count            
                        
        return search(0, len(first))


# BIT Solution
class BITRangeSum(object):

    def countRangeSum(self, nums, lower, upper):
        """
        :type nums: List[int]
        :type lower: int
        :type upper: int
        :rtype: int
        """
        cum_sum = [0]
        for i, num in enumerate(nums):
            cum_sum.append(cum_sum[-1] + num)

        min_sum = min(cum_sum)
        add_on = max(0, 1 - min_sum, 1 - lower)
        for i in range(len(cum_sum)):
            cum_sum[i] += add_on
            # can also distionary to map num to index

        lower += add_on
        upper += add_on
        max_sum = max(cum_sum)
        bit = [0 for _ in range(max_sum + 1)]
        bit[add_on] = 1
        res = 0

        for i in range(1, len(cum_sum)):
            res += self.query(bit, upper) - self.query(bit, lower - 1)
            self.update(bit, cum_sum[i])

        return res

    def query(self, bit, num):
        res = 0
        while num > 0:
            res += bit[num]
            num -= self.lowbit(num)
        return res

    def lowbit(self, num):
        return num & - num

    def update(self, bit, num):
        while num <= len(bit) - 1:
            bit[num] += 1
            num += self.lowbit(num)


if __name__== "__main__":

    # res = CountRangeSum().doit_divide_and_conquer([], 0, 0)

    res = CountRangeSum().doit_divide_and_conquer([-2, 5, -1], -2, 2)

    res = CountRangeSum().doit_divide_and_conquer([0,-3,-3,1,1,2], 3, 5)

    pass