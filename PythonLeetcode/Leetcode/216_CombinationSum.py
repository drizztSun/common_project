import os


# leetcode 39. Combination Sum
# Given a set of candidate numbers (C) (without duplicates) and a target number (T), 
# find all unique combinations in C where the candidate numbers sums to T.

# The same repeated number may be chosen from C unlimited number of times.

# Note:
# All numbers (including target) will be positive integers.
# The solution set must not contain duplicate combinations.
# For example, given candidate set [2, 3, 6, 7] and target 7, 
# A solution set is: 

# [
#   [7],
#   [2, 2, 3]
# ]

class combinationSum(object):
    def doit(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        def search(nums, i, target, cur, res):
            
            if target == 0:
                res.append(cur)
                return

            for j in range(i, len(nums)):
                if target - nums[j] >= 0:
                    search(nums, j, target - nums[j], cur + [nums[j]], res)  

        res = []
        search(candidates, 0, target, [], res)
        return res

    def doit2(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        def dfs(candidates, sublist, target, last):
            if target == 0:
                resList.append(sublist[:])

            for n in candidates:
                if n > target:
                    return

                if n < last:
                    continue

                sublist.append(n)
                dfs(candidates, sublist, target - n, n)
                sublist.pop()

        resList = []
        candidates = sorted(candidates)
        dfs(candidates, [], target, 0)
        return resList




# leetcode 40. Combination Sum II

# Given a collection of candidate numbers (C) and a target number (T), 
# find all unique combinations in C where the candidate numbers sums to T.

# Each number in C may only be used once in the combination.

# Note:
# All numbers (including target) will be positive integers.
# The solution set must not contain duplicate combinations.
# For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8, 
# A solution set is: 

# [
#  [1, 7],
#  [1, 2, 5],
#  [2, 6],
#  [1, 1, 6]
# ]

class combinationSum2(object):
    def doit1(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        def search(nums, j, target, cur, res):
            if target == 0:
                res.append(cur)
                return

            if j == len(nums) or target < 0:
                return 

            curNum, s = nums[j], j
            while s < len(nums) and nums[s] == curNum:
                s += 1

            i = 0
            while i <= s-j:
                search(nums, s, target - curNum * i, cur + [curNum] * i, res)
                i += 1

        res = []
        candidates.sort()
        search(candidates, 0, target, [], res)
        return res
        
    def doit(self, candidates, targets):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        def dfs(start, target, item, result, candidates, n):
            if target == 0:
                result.append(item[:])
                return

            if target < 0:
                return
        
            for i in range(start, n):
                if candidates[i] > target:
                    break

                if i > start and candidates[i] == candidates[i - 1]:
                    continue

                item.append(candidates[i])
                dfs(i + 1, target - candidates[i], item, result, candidates, n)
                item.pop()

        if candidates is None or len(candidates) == 0:
            return [[]]
        
        candidates.sort()
        item, result, n = [], [], len(candidates)
        dfs(0, targets, item, result, candidates, n)
        return result
    
    

# leetcode 216. Combination Sum III
# Find all possible combinations of k numbers that add up to a number n, 
# given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

# Example 1:
# Input: k = 3, n = 7
# Output: [[1,2,4]]

# Example 2:
# Input: k = 3, n = 9
# Output: [[1,2,6], [1,3,5], [2,3,4]]

class combinationSum3(object):
    def doit(self, k, n):
        """
        :type k: int
        :type n: int
        :rtype: List[List[int]]
        """
        def search(nums, i, k, target, cur, res):
            if k == 0:
                if target == 0:
                    res.append(cur[:])
                return

            for j in range(i, len(nums)):
                if nums[j] > target:
                    break

                cur.append(nums[j])
                search(nums, j + 1, k - 1, target - nums[j], cur, res)
                cur.pop()


        res = []
        nums = [x for x in range(1, 10)]
        search(nums, 0, k, n, [], res)
        return res
        

    def doit2(self, k, n):
        """
        :type k: int
        :type n: int
        :rtype: List[List[int]]
        """
        def find(cur, startIndex, k, target):
            if target == 0 and len(cur) == k:
                ans.append(cur[:])
                return

            if target < 0:
                return
        
            for i in range(startIndex, len(candidates)):
                if len(cur) < k:
                    cur.append(candidates[i])
                    find(cur, i+1, k, target-self.candidates[i])
                    cur.pop()


        candidates = range(1, 10)
        ans = []
        find([], 0, k, n)
        return ans
    



# leetcode 377. Combination Sum IV
# Given an integer array with all positive numbers and no duplicates, 
# find the number of possible combinations that add up to a positive integer target.

# nums = [1, 2, 3]
# target = 4

# The possible combination ways are:
# (1, 1, 1, 1)
# (1, 1, 2)
# (1, 2, 1)
# (1, 3)
# (2, 1, 1)
# (2, 2)
# (3, 1)

# Note that different sequences are counted as different combinations.
# Therefore the output is 7.

class combinationSum4(object):


    def doit(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        D = [0 for _ in range(target+1)]
        D[0] = 1
        nums.sort()
        
        for idx in range(1, target+1):
            res = 0
            for num in nums:
                if idx < num:
                    break
                res += D[idx - num]
            D[idx] = res

        return D[target]


    def doit2(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        dp = [0]*(target+1)
        dp[0] = 1
        for i in range(1, target+1):
            for num in nums:
                if i < num:
                    continue
                if num == i:
                    dp[i] += 1
                if i > num:
                    dp[i] += dp[i-num]
        return dp[-1]

        
    # It will get 'Time Limit Exceeded'
    def doit1(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        nums.sort()
        
        def search(nums, target, cur, res) :
            if target == 0:
                res.append(cur[:])
                return

            for i in nums:
                if i > target:
                    break

                cur.append(i)
                search(nums, target - i, cur, res)
                cur.pop()

        res = []
        search(nums, target, [], res)
        return len(res)


if __name__=="__main__":

    # [1, 1, 2, 5, 6, 7, 10]
    res = combinationSum2().doit([10, 1, 2, 7, 6, 1, 5], 8)

    
    res = combinationSum3().doit(3, 7)

    res = combinationSum3().doit(3, 9)

    res = combinationSum4().doit([1, 2, 3], 4)

    res = combinationSum4().doit([4, 2, 1], 32)

    #res = combinationSum4().doit1([3, 33, 333], 10000)

    res = combinationSum4().doit([3, 33, 333], 10000)

    pass