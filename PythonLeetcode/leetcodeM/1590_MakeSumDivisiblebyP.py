"""
1590. Make Sum Divisible by P

Given an array of positive integers nums, remove the smallest subarray (possibly empty) such that the sum of the remaining elements is divisible by p. It is not allowed to remove the whole array.

Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.

A subarray is defined as a contiguous block of elements in the array.

 

Example 1:

Input: nums = [3,1,4,2], p = 6
Output: 1
Explanation: The sum of the elements in nums is 10, which is not divisible by 6. We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.
Example 2:

Input: nums = [6,3,5,2], p = 9
Output: 2
Explanation: We cannot remove a single element to get a sum divisible by 9. The best way is to remove the subarray [5,2], leaving us with [6,3] with sum 9.
Example 3:

Input: nums = [1,2,3], p = 3
Output: 0
Explanation: Here the sum is 6. which is already divisible by 3. Thus we do not need to remove anything.
Example 4:

Input: nums = [1,2,3], p = 7
Output: -1
Explanation: There is no way to remove a subarray in order to get a sum divisible by 7.
Example 5:

Input: nums = [1000000000,1000000000,1000000000], p = 3
Output: 0
 

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= p <= 10^9

"""


class MakeSumDivisibleByP:

    def doit_(self, A, p):
        need = sum(A) % p
        dp = {0: -1}
        cur = 0
        res = n = len(A)
        for i, a in enumerate(A):
            cur = (cur + a) % p
            dp[cur] = i
            if (cur - need) % p in dp:
                res = min(res, i - dp[(cur - need) % p])
        return res if res < n else -1
    
    def doit_(self, nums: list, p: int) -> int:
        
        from collections import defaultdict
        total = sum(nums)
        if total % p == 0: return 0
        if total // p < 1: return -1
        
        target = total % p 
        # Caution! HERE We can's use Array to replace dict, if p is so big like 2^10 level, it will extremely use more memory and performance.
        # lastpos = [None for _ in range(p)]
        lastpos = defaultdict(int)
        lastpos[0] = -1
        ans = float('inf')
        
        total = 0
        for i, c in enumerate(nums):
            total += c
            r = total % p
            part = (r - target + p) % p
            
            if part in lastpos:
                ans = min(ans, i - lastpos[part])
            lastpos[r] = i
        
        return -1 if ans >= len(nums) else ans
                

if __name__ == '__main__':

    # MakeSumDivisibleByP().doit_([4,4,2], 7)

    # MakeSumDivisibleByP().doit_([8,32,31,18,34,20,21,13,1,27,23,22,11,15,30,4,2], 148)