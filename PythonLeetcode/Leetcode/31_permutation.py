import os



# leetcode 31. Next Permutation 
# Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers. 
# If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order). 
# The replacement must be in-place, do not allocate extra memory. 
# Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
# 1,2,3 ? 1,3,2
# 3,2,1 ? 1,2,3
# 1,1,5 ? 1,5,1

class nextPermutation:
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        for i in reversed(range(1, len(nums))):
            if nums[i-1] < nums[i]:
                break

        if i == 0:
            return

        start, maxV = i-1, 0
        for i in range(start+1, len(nums)):
            if nums[i] > maxV:
                maxV = nums[i]
                maxIdx = i

        nums[start], nums[maxIdx] = nums[maxIdx], nums[start]

        reversed(nums[start, len(num)])

        

                 
        
        

        
        

# leetcode 46. Permutations 
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

class permute:
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


                               
# leetcode 47. Permutations II 

# Given a collection of numbers that might contain duplicates, return all possible unique permutations. 
# For example,
# [1,1,2] have the following unique permutations:
# [
#  [1,1,2],
#  [1,2,1],
#  [2,1,1]
# ]
class permuteUnique:
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


    pass

    res = nextPermutation().doit()


    res = permute().doit([1,2,3])    

    res = permuteUnique().doit([1,1,2])


    res = getPermutation().doit(3, 1)

    res = getPermutation().doit(3, 2)

    res = getPermutation().doit(3, 3)

    res = getPermutation().doit(3, 4)

    res = getPermutation().doit(1, 1)



    pass
