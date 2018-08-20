


# 368. Largest Divisible Subset

# Given a set of distinct positive integers, find the largest subset such 
# that every pair (Si, Sj) of elements in this subset satisfies: Si % Sj = 0 or Sj % Si = 0.

# If there are multiple solutions, return any subset is fine.

# Example 1:

# nums: [1,2,3]
# Result: [1,2] (of course, [1,3] will also be ok)

# Example 2:

# nums: [1,2,4,8]
# Result: [1,2,4,8]


class largestDivisibleSubset(object):
    
    #<DP>
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        if len(nums) < 2:
            return nums

        nums.sort()
        length = len(nums)
        LengthMax = [1] * (length + 1)
        Prev = [0] * (length + 1)
        longest, longestIndex = float('-inf'), -1

        for i in range(1, length+1):

            maxv = 0
            for j in range(1, i):

                if nums[i-1] % nums[j-1] == 0:

                    if LengthMax[j] + 1 > maxv:
                        maxv = LengthMax[j] + 1
                        Prev[i] = j
                        LengthMax[i] = maxv
                        
            if maxv > longest:
                longest = maxv
                longestIndex = i

        result = []
        while longestIndex != 0:
            result.append(nums[longestIndex - 1])
            longestIndex = Prev[longestIndex]

        result.reverse()
        return result


    #
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        S = {-1 : set()}

        for c in sorted(nums):
            S[c] = max((S[d] for d in S if c % d == 0), key=len) | {c}

        return list(max(S.values(), key=len))


    # Best way
    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        if not nums:
            return []

        def factor(num):
            ans = set()
            for i in range(1, int(num ** 0.5)+1):
                if num % i == 0:
                    ans.add(i)
                    ans.add(num/i)
            ans.discard(num)
            return ans
        
        nums.sort()
        ans = [nums[0]]
        dp = {nums[0]:[nums[0]]}

        for num in nums[1:]:
            dp[num] = [num]

            for f in factor(num):
                if f in dp and 1 + len(dp[f]) > len(dp[num]):
                    dp[num] = dp[f] + [num]

            if len(dp[num]) > len(ans):
                ans = dp[num]

        return ans
                    

if __name__=="__main__":

    
    res = largestDivisibleSubset().doit([])
    
    res = largestDivisibleSubset().doit([1])

    res = largestDivisibleSubset().doit([1, 2])

    res = largestDivisibleSubset().doit([1, 2, 3])

    res = largestDivisibleSubset().doit([1, 2, 4, 8])

    pass
        