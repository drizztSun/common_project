"""
 368. Largest Divisible Subset

# Given a set of distinct positive integers, find the largest subset such
# that every pair (Si, Sj) of elements in this subset satisfies: Si % Sj = 0 or Sj % Si = 0.

# If there are multiple solutions, return any subset is fine.

# Example 1:

# nums: [1,2,3]
# Result: [1,2] (of course, [1,3] will also be ok)

# Example 2:

# nums: [1,2,4,8]
# Result: [1,2,4,8]

"""


class largestDivisibleSubset(object):
    
    #<DP>
    """
    Approach 1: Dynamic Programming
    Intuition

    At the first glance, the problem might seem to be similar with those combination problems such as two sum and 3sum. Indeed, like those combinations problems,
    it turned out to be rather helpful to sort the original list first, which would help us to reduce the number of enumerations at the end.

    As another benefit of sorting the original list, we would be able to apply the mathematical corollaries explained at the beginning of the article.

    So first of all, we sort the original list. And as it turns out, this is another dynamic programming problem. The key of solving a dynamic programming problem is to formulate the problem in a recursive and sound way.


    Complexity Analysis

    Time complexity : \mathcal{O}(N^2)O(N
    2
     ). In the major loop of the algorithm, we need to calculate the \text{EDS}(X_i)EDS(X
    i
    ​
     ) for each element in the input list. And for each \text{EDS}(X_i)EDS(X
    i
    ​
     ) calculation, we need to enumerate all elements before X_iX
    i
    ​
     . As a result, we end up with the \mathcal{O}(N^2)O(N
    2
     ) time complexity.

    Space complexity : \mathcal{O}(N^2)O(N
    2
     ). We maintain a container to keep track of \text{EDS}(X_i)EDS(X
    i
    ​
     ) value for each element in the list. And in the worst case where the entire list is a divisible set, the value of \text{EDS}(X_i)EDS(X
    i
    ​
     ) would be the sublist of [X_1, X_2...X_i][X
    1
    ​
     ,X
    2
    ​
     ...X
    i
    ​
     ]. As a result, we end up with the \mathcal{O}(N^2)O(N
    2
     ) space complexity.

    """
    def doit_dp(self, nums):
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

    def doit_dp_memory_opt(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        if len(nums) == 0:
            return []

        # important step !
        nums.sort()

        # The container that keep the size of the largest divisible subset that ends with X_i
        # dp[i] corresponds to len(EDS(X_i))
        dp = [0] * (len(nums))

        """ Build the dynamic programming matrix/vector """
        for i, num in enumerate(nums):
            maxSubsetSize = 0
            for k in range(0, i):
                if nums[i] % nums[k] == 0:
                    maxSubsetSize = max(maxSubsetSize, dp[k])

            maxSubsetSize += 1
            dp[i] = maxSubsetSize

        """ Find both the size of largest divisible set and its index """
        maxSize, maxSizeIndex = max([(v, i) for i, v in enumerate(dp)])
        ret = []

        """ Reconstruct the largest divisible subset """
        # currSize: the size of the current subset
        # currTail: the last element in the current subset
        currSize, currTail = maxSize, nums[maxSizeIndex]
        for i in range(maxSizeIndex, -1, -1):
            if currSize == dp[i] and currTail % nums[i] == 0:
                ret.append(nums[i])
                currSize -= 1
                currTail = nums[i]

        return reversed(ret)

    #
    def doit_dp_best(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        S = {-1 : set()}

        for c in sorted(nums):
            S[c] = max((S[d] for d in S if c % d == 0), key=len) | {c}

        return list(max(S.values(), key=len))


    # Best way
    def doit_bestway(self, nums):
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