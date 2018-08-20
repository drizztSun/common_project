



# 312. Burst Balloons

# Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums.
# You are asked to burst all the balloons. 
# If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. 
# Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

# Find the maximum coins you can collect by bursting the balloons wisely.

# Note: 
# (1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
# (2) 0 <= n <= 500, 0 <= nums[i] <= 100

# Example:

# Given [3, 1, 5, 8]

# Return 167

#    nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
#   coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167


class maxCoins:

    # <TLE> O(2**n)
    def doit100(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if not nums:
            return 0

        nums = [1] + nums + [1]
        def search(nums):
            if len(nums) <= 3:
                res = 1
                for c in nums:
                    res *= c
                return res

            res = 1
            for i in range(1, len(nums) - 1):
                accu = nums[i] * nums[i-1] * nums[i+1]
                res = max(res, search(nums[:i] + nums[i+1:]) + accu)
            return res

        return search(nums)


    # O(n**3)
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if not nums:
            return 0

        nums = [1] + nums + [1]
        
        D = [[-1 for _ in range(len(nums))] for j in range(len(nums))]

        def search(nums, s, e, D):
            if s > e:
                return 0

            if D[s][e] != -1:
                return D[s][e]


            for i in range(s, e + 1):
                accu = nums[s-1] * nums[i] * nums[e+1]
                accu += search(nums, s, i-1, D) + search(nums, i + 1, e, D)
                D[s][e] = max(D[s][e], accu)

            return D[s][e]

        return search(nums, 1, len(nums) - 2, D)


    #  O(n**3)
    # <DP>
    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        lenth = len(nums)
        nums = [1] + nums + [1]
        BestGain = [[0 for _ in range(lenth + 2)] for _ in range(lenth + 2)]

        for l in range(2, (lenth + 2)):
            for i in range(0, (lenth + 2 - l)):
                j = i + l
                maxGain = 0
                for k in range(i + 1, j):
                    nowGain = BestGain[i][k] + BestGain[k][j] + nums[i] * nums[k] * nums[j]
                    if nowGain > maxGain:
                        maxGain = nowGain
                BestGain[i][j] = maxGain

        return BestGain[0][lenth + 1]
             


    # O(n**3)
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums = [1] + nums + [1]
        D = [ [ 0 for _ in range(len(nums))] for _ in range(len(nums))]
        
        for l in range(1, len(nums)-1):
            for s in range(1, len(nums) - l):
                
                for k in range(s, s+l):
                    accu = nums[s-1] * nums[k] * nums[s+l]
                    accu += D[s][k-1] + D[k+1][s+l-1]
                    
                    if accu > D[s][s+l-1]:
                        D[s][s+l-1] = accu
                        
        return D[1][len(nums) - 2]




if __name__=="__main__":

    

    res = maxCoins().doit([3, 1, 5, 8])

    res = maxCoins().doit([35,16,83,87,84,59,48,41,20,54])

    pass