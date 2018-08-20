


# 421. Maximum XOR of Two Numbers in an Array

# Given a non-empty array of numbers, a0, a1, a2, .... , an-1, where 0 ? ai < 231.

# Find the maximum result of ai XOR aj, where 0 ? i, j < n.

# Could you do this in O(n) runtime?

# Example:

# Input: [3, 10, 5, 25, 2, 8]

# Output: 28

# Explanation: The maximum result is 5 ^ 25 = 28.

# <important>
class findMaximumXOR:


# Build the answer bit by bit from left to right.
# Let�s say we already know the largest first seven bits we can create.
# How to find the largest first eight bits we can create?
# Well it�s that maximal seven-bits prefix followed by 0 or 1.
# Append 0 and then try to create the 1 one (i.e., answer ^ 1) from two eight-bits prefixes from nums.
# If we can, then change that 0 to 1.


# key idea: answer += any(answer^1 ^ p in prefixes for p in prefixes)
# if (answer^1) XOR p matches Z in prefixes, then p XOR Z matches (answer^1),
# which is what I am looking for. p and Z are both elements in the prefix set.


    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        #answer = 0
        #for i in range(32)[::-1]:
        #    answer <<= 1
        #    prefixes = {num >> i for num in nums}
        #    answer += any(answer^1 ^ p in prefixes for p in prefixes)
        #return answer
        answer = 0

        for i in range(32)[::-1]:

            answer <<= 1

            prefixes = {num >> i for num in nums}

            A = [answer ^ 1 ^ p in prefixes for p in prefixes]

            answer += any(A)

        return answer



if __name__=="__main__":

    

    res = findMaximumXOR().doit([3, 10, 5, 25, 2, 8])

    pass