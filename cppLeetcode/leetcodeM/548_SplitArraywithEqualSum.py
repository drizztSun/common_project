"""
548. Split Array with Equal Sum


Given an array with n integers, you need to find if there are triplets (i, j, k) which satisfies following conditions:

0 < i, i + 1 < j, j + 1 < k < n - 1
Sum of subarrays (0, i - 1), (i + 1, j - 1), (j + 1, k - 1) and (k + 1, n - 1) should be equal.
where we define that subarray (L, R) represents a slice of the original array starting from the element indexed L to the element indexed R.
Example:
Input: [1,2,1,2,1,2,1]
Output: True
Explanation:
i = 1, j = 3, k = 5. 
sum(0, i - 1) = sum(0, 0) = 1
sum(i + 1, j - 1) = sum(2, 2) = 1
sum(j + 1, k - 1) = sum(4, 4) = 1
sum(k + 1, n - 1) = sum(6, 6) = 1
Note:
1 <= n <= 2000.
Elements in the given array will be in range [-1,000,000, 1,000,000].
"""


class SplitArray:

    """
        Approach #5 Using Cumulative Sum and HashSet [Accepted]
        Algorithm

        In this approach, firstly we form a cumulative sum array sumsum, where sum[i]sum[i] stores the cumulative sum of the array numsnums upto the i-th index. 
        Then, we start by traversing over the possible positions for the middle cut formed by jj. For every jj, firstly, we find all the left cut's positions, ii, 
        that lead to equalizing the sum of the first and the second part (i.e. sum[i-1] = sum [j-1] - sum[i]sum[i−1]=sum[j−1]−sum[i]) and store such sums in the setset (a new HashSet is formed for every jj chosen). 
        Thus, the presence of a sum in setset implies that such a sum is possible for having equal sum of the first and second part for the current position of the middle cut(jj).

        Then, we go for the right cut and find the position of the right cut that leads to equal sum of the third and the fourth part (sum[n-1]-sum[k]=sum[k-1] - sum[j]sum[n−1]−sum[k]=sum[k−1]−sum[j]), 
        for the same middle cut as chosen earlier. We also, look if the same sum exists in the setset. If so, such a triplet (i, j, k)(i,j,k) exists which satisfies the required criteria, otherwise not.

        Look at the animation below for a visual representation of the process:
    """
    def doit_(self, nums: list) -> bool:
        n = len(nums)
        presum = [0] * n
        presum[0] = nums[0]
        for i in range(1, n):
            presum[i] = presum[i-1] + nums[i]
            
        for j in range(3, n-3):
            
            buff = set()
            
            for i in range(1, j-1):
                if presum[i-1] == presum[j-1] - presum[i]:
                    buff.add(presum[i-1])
                    
            for i in range(j+2, n-1):
                if (presum[n-1] - presum[i] == presum[i-1] - presum[j]) and (presum[n-1] - presum[i]) in buff:
                    return True
                
        return False

    def doit_(self, nums: list) -> bool:
        n = len(nums)
        s = [0] * (n + 1)

        for i in range(n): 
            s[i + 1] = s[i] + nums[i]
        
        def check(l, r):
            return set(s[m] - s[l] for m in range(l + 1, r + 1) if s[m] - s[l] == s[r + 1] - s[m + 1])
        
        return any(check(0, j - 1) & check(j + 1, n - 1) for j in range(n))