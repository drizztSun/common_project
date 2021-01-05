"""
477. Total Hamming Distance


The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Now your job is to find the total Hamming distance between all pairs of the given numbers.

Example:
Input: 4, 14, 2

Output: 6

Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
showing the four bits relevant in this case). So the answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.
Note:
Elements of the given array are in the range of 0 to 10^9
Length of the array will not exceed 10^4.

"""

class TotalHammingDistance:
    
    def doit_(self, nums: list) -> int:

        ans = 0        
        for i in range(32):
            
            bits = 0
            for c in nums:
                bits += (c >> i) & 1
                
            ans += bits * (len(nums) - bits)

        return ans

    def doit_(self, nums: list) -> int:

        buf = [0] * 32
        for n in nums:
            for i in range(32):
                buf[i] += (n >> i & 1)
        
        return sum(c * (len(nums) - c) for c in buf)

    def doit_list(self, nums: list) -> int:
#         z = max(nums, default=0)
#         n = len(nums)
    
#         i = 0
#         mask = 1
#         total = 0
#         while mask <= z:
#             ones = sum((n & mask) for n in nums) >> i
#             total += ones * (n - ones)
#             mask <<= 1
#             i += 1
    
#         return total
        n = len(nums); su = 1
        for b in zip(*map('{:032b}'.format, nums)):
            y = b.count('0')
            su += y * (n-y)
        return su - 1