"""
421. Maximum XOR of Two Numbers in an Array

Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 ≤ i ≤ j < n.

Follow up: Could you do this in O(n) runtime?



Example 1:

Input: nums = [3,10,5,25,2,8]
Output: 28
Explanation: The maximum result is 5 XOR 25 = 28.
Example 2:

Input: nums = [0]
Output: 0
Example 3:

Input: nums = [2,4]
Output: 6
Example 4:

Input: nums = [8,10,2]
Output: 10
Example 5:

Input: nums = [14,70,53,83,49,91,36,80,92,51,66,70]
Output: 127


Constraints:

1 <= nums.length <= 2 * 104
0 <= nums[i] <= 231 - 1


"""


class FindMaximumXOR:

    """
    Overview
    Requirements are to have \mathcal{O}(N)O(N) time complexity, and we'll discuss here two standard approaches to achieve that complexity.

    Bitwise Prefixes in HashSet.

    Bitwise Prefixes in Trie.

    The idea behind both solutions is the same: to convert all numbers into the binary form, and to construct the maximum XOR bit by bit, starting from the leftmost one.
    The difference is in the data structure used to store unique bitwise prefixes, i.e. the first ith bits.

    The first approach works faster on the given testcase set, but the second one is standard, more simple, and easily generalised for more complex problems like Find maximum subarray XOR in a given array.

    Prerequisites

    XOR of zero and a bit results in that bit

    0 \oplus x = x0⊕x=x

    XOR of two equal bits (even if they are zeros) results in a zero

    x \oplus x = 0x⊕x=0


    """

    """
    Approach 1: Bitwise Prefixes in HashSet
    Let's start from rewriting all numbers [3, 10, 5, 25, 2, 8] in binary from
    
    3 =  (00011)_2
    10 = (01010)_2
    5 =  (00101)_2
    25 = (11001)_2
    2 =  (00010)_2
    8 =  (01000)_2
    
    To simplify the work with prefixes, better to use the same number of bits LL for all the numbers. It's enough to take LL equal to the length of the max number in the binary representation.
    
    Now let's construct the max XOR starting from the leftmost bit. The absolute maximum one could have with L = 5 bits here is (11111). 
    So let's check bit by bit:
    
    Could we have the leftmost bit for XOR to be equal to 1-bit, i.e. max XOR to be equal to (1****)
    Yes, for that it's enough to pair 25 = (11001)_2
      with another number starting with the zero leftmost bit. So the max XOR is (1****)_2
    Next step. Could we have max XOR to be equal to (11***)_2
    For that, let's consider all prefixes of length 2 and check if there is a pair of them, p_1 and p_2, such that its XOR is equal to 11: 
    
    p_1 ^ p_2 == 11 

    
    3 = (00***)_2
    10 = (01***)_2
    5 = (00***)_2
    25 = (11***)_2
    2 = (00***)_2
    8 = (01***)_2
    
    Yes, it's the case, for example, pair 5 = (00***)_2 and 25 = (11***)_2, or 2 = (00***)_2  and 25 = (11***)_2, or 3 = (00***)_2 and 25 = (11***)_2.
    
    And so on, and so forth. The complexity remains linear. One has to perform NN operations to compute prefixes, though the number of prefixes containing L - i bits could not be greater than 2^{L - i}2 
    L−i
     . Hence the check if XOR could have the ith bit to be equal to 1-bit takes 2^{L - i} \times 2^{L - i}2 
    L−i
     ×2 
    L−i
      operations.
    
    Algorithm
    
    Compute the number of bits LL to be used. It's a length of max number in binary representation.
    
    Initiate max_xor = 0.
    
    Loop from i = L - 1i=L−1 down to i = 0i=0 (from the leftmost bit L - 1L−1 to the rightmost bit 0):
    
    Left shift the max_xor to free the next bit.
    
    Initiate variable curr_xor = max_xor | 1 by setting 1 in the rightmost bit of max_xor. Now let's check if curr_xor could be done using available prefixes.
    
    Compute all possible prefixes of length L - iL−i by iterating over nums.
    
    Put in the hashset prefixes the prefix of the current number of the length L - iL−i: num >> i.
    Iterate over all prefixes and check if curr_xor could be done using two of them: p1^p2 == curr_xor. Using self-inverse property of XOR p1^p2^p2 = p1, one could rewrite it as p1 == curr_xor^p2 and simply check for each p if curr_xor^p is in prefixes. If so, set max_xor to be equal to curr_xor, i.e. set 1-bit in the rightmost bit. Otherwise, let max_xor keep 0-bit in the rightmost bit.
    
    Return max_xor.
    """

    def doit_greedy(self, nums: list) -> int:

        # length of max number in a binary representation
        L = len(bin(max(nums))) - 2
        max_xor = 0
        for i in range(L)[::-1]:
            # go to the next bit by the left shift
            max_xor <<= 1
            # set 1 in the smallest bit
            curr_xor = max_xor | 1
            # compute all existing prefixes
            # of length (L - i) in binary representation
            prefixes = {num >> i for num in nums}
            # Update max_xor, if two of these prefixes could result in curr_xor.
            # Check if p1^p2 == curr_xor, i.e. p1 == curr_xor^p2
            max_xor |= any(curr_xor ^ p in prefixes for p in prefixes)

        return max_xor

    def doit_tire_(self, nums: list) -> int:
        # Compute length L of max number in a binary representation
        L = len(bin(max(nums))) - 2
        # zero left-padding to ensure L bits for each number
        nums = [[(x >> i) & 1 for i in range(L)][::-1] for x in nums]

        max_xor = 0
        trie = {}
        for num in nums:
            node = trie
            xor_node = trie
            curr_xor = 0
            for bit in num:
                # insert new number in trie
                if not bit in node:
                    node[bit] = {}
                node = node[bit]

                # to compute max xor of that new number
                # with all previously inserted
                toggled_bit = 1 - bit
                if toggled_bit in xor_node:
                    curr_xor = (curr_xor << 1) | 1
                    xor_node = xor_node[toggled_bit]
                else:
                    curr_xor = curr_xor << 1
                    xor_node = xor_node[bit]

            max_xor = max(max_xor, curr_xor)

        return max_xor

