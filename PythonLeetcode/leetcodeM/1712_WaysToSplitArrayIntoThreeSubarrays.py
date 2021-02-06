"""
1712. Ways to Split Array Into Three Subarrays

A split of an integer array is good if:

The array is split into three non-empty contiguous subarrays - named left, mid, right respectively from left to right.
The sum of the elements in left is less than or equal to the sum of the elements in mid, and the sum of the elements in mid is less than or equal to the sum of the elements in right.
Given nums, an array of non-negative integers, return the number of good ways to split nums. As the number may be too large, return it modulo 10^9 + 7.



Example 1:

Input: nums = [1,1,1]
Output: 1
Explanation: The only good way to split nums is [1] [1] [1].
Example 2:

Input: nums = [1,2,2,2,5,0]
Output: 3
Explanation: There are three good ways of splitting nums:
[1] [2] [2,2,5,0]
[1] [2,2] [2,5,0]
[1,2] [2,2] [5,0]
Example 3:

Input: nums = [3,2,1]
Output: 0
Explanation: There is no good way to split nums.


Constraints:

3 <= nums.length <= 105
0 <= nums[i] <= 104

"""


class WaysToSplit:

    def doit_binary_search(self, nums: list) -> int:

        from bisect import bisect_right

        n, hmod = len(nums), 10**9 + 7
        presum = [0] * n 
        
        for i in range(n):
            presum[i] = nums[i] + (0 if i == 0 else presum[i-1])

        j, ans = 0, 0
        for i in range(n-2):

            while j <= i or (j < n and presum[j] - presum[i] < presum[i]):
                j += 1
                
            if j == n: break

            k = bisect_right(presum, (presum[n-1] + presum[i])//2) - 1

            #if k == n-1:
            #    k -= 1
                
            if k < j:
                continue

            ans = (ans + k - j + 1) % hmod


        return ans % (10**9 + 7)

    """
        Solution
        Overview
        The problem asks us to split the array into three parts such that the sum of the left part \leq≤ sum of the middle part \leq≤ the sum of the right part.

        Figure 0.1

        A brute force approach is to iterate over all possible locations of the first and second cut in the picture, which costs \mathcal{O}(N^{2})O(N 
        2
        ), given that NN is the length of nums.

        However, with Binary Search, we can achieve \mathcal{O}(N\log N)O(NlogN).

        Below, two approaches are introduced: Binary Search (Built-in) and Binary Search (Handmade). The first one calls the built-in API in the programming language for binary search, and in the second one, we write our own binary search implementation, in case that interviewers require so.

        Approach 1: Binary Search (Built-in)
        Intuition

        An important insight is that: the sum of the middle part must fall in the range of the sum of the left and right parts.

        \text{LeftSum} \leq \text{MidSum} \leq \text{RightSum}LeftSum≤MidSum≤RightSum

        Figure 1.1

        Also,

        \text{LeftSum} + \text{MidSum} + \text{RightSum} = \text{TotalSum}LeftSum+MidSum+RightSum=TotalSum

        We can easily calculate the \text{TotalSum}TotalSum by simple adding.

        This means, once the \text{LeftSum}LeftSum is determined, the range of \text{MidSum}MidSum is also determined.

        \text{LeftSum} \leq \text{MidSum} \leq \text{RightSum} = \text{TotalSum} - (\text{LeftSum} + \text{MidSum})LeftSum≤MidSum≤RightSum=TotalSum−(LeftSum+MidSum)

        We can simplify the right part:

        \text{MidSum} \leq \text{TotalSum} - (\text{LeftSum} + \text{MidSum}) = \text{TotalSum} - \text{LeftSum} - \text{MidSum}MidSum≤TotalSum−(LeftSum+MidSum)=TotalSum−LeftSum−MidSum

        2 \cdot \text{MidSum} \leq \text{TotalSum} - \text{LeftSum}2⋅MidSum≤TotalSum−LeftSum

        \text{MidSum} \leq \frac{\text{TotalSum} - \text{LeftSum}}{2}MidSum≤ 
        2
        TotalSum−LeftSum
        ​	
        

        Combine together, we have:

        \text{LeftSum} \leq \text{MidSum} \leq \frac{\text{TotalSum} - \text{LeftSum}}{2}LeftSum≤MidSum≤ 
        2
        TotalSum−LeftSum
        ​	
        

        This give us the range of \text{MidSum}MidSum once \text{LeftSum}LeftSum is determined.

        Since all numbers in nums are natural number, we can use Binary Search to find out the minimal possible index and the maximum possible index of \text{MidSum}MidSum.

        In conclusion, we can iterate over the first cut to determine \text{LeftSum}LeftSum, and use binary search to find all possible locations of the second cut.

        To speed up the calculation of sum, Prefix Sum can help us.

        Algorithm

        Step 1: Initialize a prefix sum list presum, where presum[i+1] store the sum from nums[0] to nums[i], inclusive.

        Step 2: Iterate over nums. For each element nums[i]:

        Cut nums into (nums[0],...,nums[i]) | (nums[i+1], nums[i+2], ...).
        Calculate the sum of (nums[0],..., nums[i]) with presum. Mark as leftSum.
        Calculate the sum of (nums[i+1], nums[i+2], ...) with presum. Mark as remain.
        Then we need to cut the remaining part into two pieces, and the sum of the middle piece should be between leftSum and remain/2.
        Binary search the minimal first such that nums[i+1] + ... + nums[first] >= leftSum.
        Binary search the maximum last such that nums[i+1] + ... + nums[second] <= remain/2.
        Add last - first + 1 to the final result.
        Step 3: Return the final result.

        In this approach, we use built-in functions to perform binary searches. In the next approach, we will implement our own binary search functions.

        Warning!: Unfortunately, Java does not have a nice built-in binary search to find out the upper bound of the index of the second cut (such as upper_bound in C++).

        In this case, we have to use a TreeMap to mimic the function. If you are not familiar with TreeMap, this trick is not recommended since implementing your own binary search functions would be usually faster.

        Challenge: Can you implement the code yourself without seeing our implementations?

        Implementation


        Complexity Analysis

        Let NN be the length of nums.

        Time Complexity: \mathcal{O}(N\log N)O(NlogN), since we need to iterate over nums and for each element, we perform binary search twice which costs \mathcal{O}(\log N)O(logN).

        Space Complexity: \mathcal{O}(N)O(N), since we need \mathcal{O}(N)O(N) to store presum.
    """

    def doit_binary_search_1(self, nums: list) -> int:
        import bisect
        n = len(nums)
        MOD = 10**9+7
        presum = [0]*(n+1)
        for i in range(n):
            presum[i+1] = presum[i]+nums[i]

        result = 0
        for i in range(n-2):
            # nums[0],...,nums[i] | nums[i+1], nums[i+2], ...
            leftSum = presum[i+1]
            remain = presum[n]-leftSum
            if remain < leftSum*2:
                break
            # search first & last in presum[i+2:n]
            first = bisect.bisect_left(presum, leftSum + leftSum, i+2, n)
            # minus 1 since bisect_right finds the less one, not less or equal one
            last = bisect.bisect_right(presum, leftSum+remain//2, i+2, n) - 1
            result += max(last-first+1, 0)

        return result % MOD

            


if __name__ == '__main__':

    WaysToSplit().doit_binary_search([0, 3, 3])



