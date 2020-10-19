"""
leetcode 31. Next Permutation
# Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
# If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).
# The replacement must be in-place, do not allocate extra memory.
# Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
# 1,2,3 ? 1,3,2
# 3,2,1 ? 1,2,3
# 1,1,5 ? 1,5,1
"""


class NextPermutation:

    """
    Approach 2: Single Pass Approach
    Algorithm

    First, we observe that for any given sequence that is in descending order, no next larger permutation is possible. For example, no next permutation is possible for the following array:

    [9, 5, 4, 3, 1]
    We need to find the first pair of two successive numbers a[i]a[i] and a[i-1]a[i−1], from the right, which satisfy a[i] > a[i-1]a[i]>a[i−1]. Now, no rearrangements to the right of a[i-1]a[i−1] can create a larger permutation since that subarray consists of numbers in descending order. Thus, we need to rearrange the numbers to the right of a[i-1]a[i−1] including itself.

    Now, what kind of rearrangement will produce the next larger number? We want to create the permutation just larger than the current one. Therefore, we need to replace the number a[i-1]a[i−1] with the number which is just larger than itself among the numbers lying to its right section, say a[j]a[j].

    We swap the numbers a[i-1]a[i−1] and a[j]a[j]. We now have the correct number at index i-1i−1. But still the current permutation isn't the permutation that we are looking for. We need the smallest permutation that can be formed by using the numbers only to the right of a[i-1]a[i−1]. Therefore, we need to place those numbers in ascending order to get their smallest permutation.

    But, recall that while scanning the numbers from the right, we simply kept decrementing the index until we found the pair a[i]a[i] and a[i-1]a[i−1] where, a[i] > a[i-1]a[i]>a[i−1]. Thus, all numbers to the right of a[i-1]a[i−1] were already sorted in descending order. Furthermore, swapping a[i-1]a[i−1] and a[j]a[j] didn't change that order. Therefore, we simply need to reverse the numbers following a[i-1]a[i−1] to get the next smallest lexicographic permutation.

    The following animation will make things clearer:

    Complexity Analysis

    Time complexity : O(n)O(n). In worst case, only two scans of the whole array are needed.

    Space complexity : O(1)O(1). No extra space is used. In place replacements are done.
    """
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        for i in range(n-1, 0, -1):
            if nums[i] > nums[i-1]:
                j = i
                while j < n and nums[j] > nums[i-1]:
                    idx = j
                    j += 1
                nums[idx], nums[i-1] = nums[i-1], nums[idx]
                for k in range((n-i)//2):
                    nums[i+k], nums[n-1-k] = nums[n-1-k], nums[i+k]
        else:
            nums.reverse()

    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        i = len(nums) - 1
        while i > 0 and nums[i] <= nums[i-1]:           # scan backward to find the first element that is bigger than the element before it
            i -= 1
        if i > 0:
            j = len(nums) - 1
            while nums[j] <= nums[i-1]:                 # find the smallest number after nums[i] that is bigger than nums[i-1]
                j -= 1
            nums[i-1], nums[j] = nums[j], nums[i-1]     # swap nums[j] with nums[i-1]
        nums[i:] = reversed(nums[i:])


"""
46. Permutations 
# Given a collection of distinct numbers, return all possible permutations. 
# For example,
# [1,2,3] have the following permutations:

#[
#  [1,2,3],
#  [1,3,2],
#  [2,1,3],
#  [2,3,1],
#  [3,1,2],
#  [3,2,1]
#]
"""


class Permute:
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        def assemble(buff):
            if len(buff) == 1:
                return [[buff[0]]]

            res = []
            for i in range(len(buff)):
                c = buff[i]
                for j in assemble(buff[:i] + buff[i+1:]):
                    res.append([c] + j)

            return res

        return assemble(nums)


    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        def assemble(buff):
            if not buff:
                return [[]]

            res = []
            for i in range(len(buff)):
                c = buff[i]
                for j in assemble(buff[:i] + buff[i+1:]):
                    res.append([c] + j)

            return res

        return assemble(nums)
        

    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        if nums is None or len(nums) == 0:
            return list()
        
        result = [[]]
        for item in nums:
            tmp_result = list()
            for tmp_list in result:
                for j in range(len(tmp_list) + 1):
                    tmp_result.append(tmp_list[:j] + [item] + tmp_list[j:])
            result = tmp_result
        return result


"""
47. Permutations II 

# Given a collection of numbers that might contain duplicates, return all possible unique permutations. 
# For example,
# [1,1,2] have the following unique permutations:
# [
#  [1,1,2],
#  [1,2,1],
#  [2,1,1]
# ]
"""


class PermuteUniqueII:
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        def assemble(buff):
            if len(buff) == 1:
                return [[buff[0]]]

            res = []
            for i in range(len(buff)):
                if i > 0 and buff[i] == buff[i-1]:
                    continue

                for item in assemble(buff[:i] + buff[i+1:]):
                    res.append([buff[i]] + item) 
                
            return res

        nums.sort()
        return assemble(nums)

    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        result = []
        cur = []
        
        def permute(nums):
            if not len(nums):
                result.append(cur[:])
                return

            for i, num in enumerate(nums):
                if i > 0 and num == nums[i-1]:
                    continue

                cur.append(num)
                permute(nums[:i] + nums[i+1:])
                cur.pop()
            return

        permute(sorted(nums))
        return result
            

    
# leetcode 60. Permutation Sequence 

# The set [1,2,3,...,n] contains a total of n! unique permutations.
# By listing and labeling all of the permutations in order,
# We get the following sequence (ie, for n = 3): 
# "123"
# "132"
# "213"
# "231"
# "312"
# "321"

# Given n and k, return the kth permutation sequence.
# Note: Given n will be between 1 and 9 inclusive.

class getPermutation:
    def doit(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        f, k = 1, k-1
        nums = [x+1 for x in range(n)]
        for i in range(1, n):
            f *= i
    
        res = ""
        while n:
            res += str(nums[k//f])
            nums.pop(k//f) 
            k = k % f
            f = f//(n-1) if n > 1 else 1
            n -= 1

        return res

    def doit(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        result = ""
        get(list(range(1, n + 1)), k - 1)
        return self.result
    
        def get(currentlist, k):
            if(len(currentlist) == 0):
                return
            
            prev = math.factorial(len(currentlist) - 1)
            current = 0
            
            while(current * prev <= k):
                current += 1
            
            current -= 1
            result += str(currentlist[current])
            currentlist.remove(currentlist[current])
            k -= current * prev
            get(currentlist, k)


if __name__=="__main__":

    res = nextPermutation().doit()


    res = permute().doit([1,2,3])    

    res = permuteUnique().doit([1,1,2])


    res = getPermutation().doit(3, 1)

    res = getPermutation().doit(3, 2)

    res = getPermutation().doit(3, 3)

    res = getPermutation().doit(3, 4)

    res = getPermutation().doit(1, 1)
