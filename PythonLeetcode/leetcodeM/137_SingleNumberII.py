"""
136. Single Number

Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.

Follow up: Could you implement a solution with a linear runtime complexity and without using extra memory?

 

Example 1:

Input: nums = [2,2,1]
Output: 1
Example 2:

Input: nums = [4,1,2,1,2]
Output: 4
Example 3:

Input: nums = [1]
Output: 1
 

Constraints:

1 <= nums.length <= 3 * 104
-3 * 104 <= nums[i] <= 3 * 104
Each element in the array appears twice except for one element which appears only once.

"""
class SingleNumberI:
    
    def doit_(self, nums: list) -> int:
        ans = 0
        for c in nums:
            ans ^= c
        return ans


"""
137. Single Number II


Given an integer array nums where every element appears three times except for one, which appears exactly once. 
Find the single element and return it.

 

Example 1:

Input: nums = [2,2,3,2]
Output: 3
Example 2:

Input: nums = [0,1,0,1,0,1,99]
Output: 99
 

Constraints:

1 <= nums.length <= 3 * 104
-231 <= nums[i] <= 231 - 1
Each element in nums appears exactly three times except for one element which appears once.
 

Follow up: Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?


Solution
Overview
The problem seems to be quite simple and one could solve it in \mathcal{O}(N)O(N) time and \mathcal{O}(N)O(N) space by using an additional data structure like set or hashmap.

The real game starts at the moment when Google interviewer (the problem is quite popular at Google the last six months) asks you to solve the problem in a constant space, testing if you are OK with bitwise operators.

"""


class SingleNumberII:
    
    """
        Approach 1: HashSet
        The idea is to convert an input array into hashset and then to compare the tripled sum of the set with the array sum

        3 \times (a + b + c) - (a + a + a + b + b + b + c) = 2 c3×(a+b+c)−(a+a+a+b+b+b+c)=2c

        Implementation

            Complexity Analysis

            Time complexity : O(N) to iterate over the input array.

            Space complexity : O(N) to keep the set of N/3 elements.

    """
    def doit_search(self, nums: list) -> int:
        return (3 * sum(set(nums)) - sum(nums)) // 2

    """
        Approach 2: HashMap
        Let's iterate over the input array to count the frequency of each number, and then return an element with a frequency 1.

        Implementation
        Complexity Analysis

        Time complexity : O(N) to iterate over the input array.

        Space complexity : O(N) to keep the hashmap of N/3 elements.
    """
    def singleNumber(self, nums):
        from collections import Counter
        hashmap = Counter(nums)
        for k in hashmap.keys():
            if hashmap[k] == 1:
                return k

    """
        Approach 3: Bitwise Operators : NOT, AND and XOR
        Intuition

        Now let's discuss \mathcal{O}(1)O(1) space solution by using three bitwise operators

        \sim x \qquad \textrm{that means} \qquad \textrm{bitwise NOT}∼xthat meansbitwise NOT

        x \& y \qquad \textrm{that means} \qquad \textrm{bitwise AND}x&ythat meansbitwise AND

        x \oplus y \qquad \textrm{that means} \qquad \textrm{bitwise XOR}x⊕ythat meansbitwise XOR

        XOR

        Let's start from XOR operator which could be used to detect the bit which appears odd number of times: 1, 3, 5, etc.

        XOR of zero and a bit results in that bit

        0 \oplus x = x0⊕x=x

        XOR of two equal bits (even if they are zeros) results in a zero

        x \oplus x = 0x⊕x=0

        and so on and so forth, i.e. one could see the bit in a bitmask only if it appears odd number of times.

        fig

        That's already great, so one could detect the bit which appears once, and the bit which appears three times. The problem is to distinguish between these two situations.

        AND and NOT

        To separate number that appears once from a number that appears three times let's use two bitmasks instead of one: seen_once and seen_twice.

        The idea is to

        change seen_once only if seen_twice is unchanged

        change seen_twice only if seen_once is unchanged

        fig

        This way bitmask seen_once will keep only the number which appears once and not the numbers which appear three times.

        Implementation

        Complexity Analysis

        Time complexity : O(N) to iterate over the input array.

        Space complexity : O(1) since no additional data structures are allocated.
    """
    def doit_search(self, nums: List[int]) -> int:
        seen_once = seen_twice = 0
        
        for num in nums:
            # first appearance: 
            # add num to seen_once 
            # don't add to seen_twice because of presence in seen_once
            
            # second appearance: 
            # remove num from seen_once 
            # add num to seen_twice
            
            # third appearance: 
            # don't add to seen_once because of presence in seen_twice
            # remove num from seen_twice
            seen_once = ~seen_twice & (seen_once ^ num)
            seen_twice = ~seen_once & (seen_twice ^ num)

        return seen_once


"""
260. Single Number III

Given an integer array nums, in which exactly two elements appear only once and all the other elements appear exactly twice. 
Find the two elements that appear only once. You can return the answer in any order.

Follow up: Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?

 

Example 1:

Input: nums = [1,2,1,3,2,5]
Output: [3,5]
Explanation:  [5, 3] is also a valid answer.
Example 2:

Input: nums = [-1,0]
Output: [-1,0]
Example 3:

Input: nums = [0,1]
Output: [1,0]
 

Constraints:

2 <= nums.length <= 3 * 10^4
-231 <= nums[i] <= 231 - 1
Each integer in nums will appear twice, only two integers will appear once.
"""


class SingleNumberIII:

    """
        Approach 1: Hashmap
        Build a hashmap : element -> its frequency. Return only the elements with the frequency equal to 1.

        Implementation

        Complexity Analysis

        Time complexity : O(N) to iterate over the input array.

        Space complexity : O(N) to keep the hashmap of N elements.
    """
    def doit_search(self, nums: list) -> list:
        from collections import Counter
        hashmap = Counter(nums)
        return [x for c in hashmap if hashmap[x] == 1]

    """
        Approach 2: Two bitmasks
        Prerequisites

        This article will use two bitwise tricks, discussed in details last week :

        If one builds an array bitmask with the help of XOR operator, following bitmask ^= x strategy, the bitmask would keep only the bits which appear odd number of times. That was discussed in details in the article Single Number II.
        fig

        x & (-x) is a way to isolate the rightmost 1-bit, i.e. to keep the rightmost 1-bit and to set all the others bits to zero. Please refer to the article Power of Two for the detailed explanation.
        fig

        Intuition

        An interview tip. Imagine, you have a problem to indentify an array element (or elements), which appears exactly given number of times. Probably, the key is to build first an array bitmask using XOR operator. Examples: In-Place Swap, Single Number, Single Number II.

        So let's create an array bitmask : bitmask ^= x. This bitmask will not keep any number which appears twice because XOR of two equal bits results in a zero bit a^a = 0.

        Instead, the bitmask would keep only the difference between two numbers (let's call them x and y) which appear just once. The difference here it's the bits which are different for x and y.

        fig

        Could we extract x and y directly from this bitmask? No. Though we could use this bitmask as a marker to separate x and y.

        Let's do bitmask & (-bitmask) to isolate the rightmost 1-bit, which is different between x and y. Let's say this is 1-bit for x, and 0-bit for y.

        fig

        Now let's use XOR as before, but for the new bitmask x_bitmask, which will contain only the numbers which have 1-bit in the position of bitmask & (-bitmask). This way, this new bitmask will contain only number x x_bitmask = x, because of two reasons:

        y has 0-bit in the position bitmask & (-bitmask) and hence will not enter this new bitmask.

        All numbers but x will not be visible in this new bitmask because they appear two times.

        fig

        Voila, x is identified. Now to identify y is simple: y = bitmask^x.

        Implementation

        Complexity Analysis

        Time complexity : O(N) to iterate over the input array.

        Space complexity : O(1), it's a constant space solution.

    """
    def doit_search(self, nums: list) -> list:
        # difference between two numbers (x and y) which were seen only once
        bitmask = 0
        for num in nums:
            bitmask ^= num
        
        # rightmost 1-bit diff between x and y
        diff = bitmask & (-bitmask)
        
        x = 0
        for num in nums:
            # bitmask which will contain only x
            if num & diff:
                x ^= num
        
        return [x, bitmask^x]