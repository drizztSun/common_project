# 650. 2 Keys Keyboard

# Initially on a notepad only one character 'A' is present. You can perform two operations on this notepad for each step:

# Copy All: You can copy all the characters present on the notepad (partial copy is not allowed).
# Paste: You can paste the characters which are copied last time.
# Given a number n. You have to get exactly n 'A' on the notepad by performing the minimum number of steps permitted. Output the minimum number of steps to get n 'A'.

# Example 1:
# Input: 3
# Output: 3
# Explanation:
# Intitally, we have one character 'A'.
# In step 1, we use Copy All operation.
# In step 2, we use Paste operation to get 'AA'.
# In step 3, we use Paste operation to get 'AAA'.
# Note:
# The n will be in the range [1, 1000].

import math

class MinSteps:


    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        def minSteps(length):
            if length == 1:
                return 0
            else:
                for i in range(2, int(math.sqrt(length)) + 1):
                    if length % i == 0:
                        return int(minSteps(i) + minSteps(length/i))
                return length
        return minSteps(n)

    # <BFS> 
    # TLE error
    def doit1(self, n):
        """
        :type n: int
        :rtype: int
        """
        copy, length, steps = 0, 1, 0
        buff = [(length, copy)]
        memo = set([(length, copy)])

        while buff:
            tmp = []
            for c in buff:
                
                if c[0] == n:
                    return steps
                
                if c[0] > n:
                    continue

                copy, paste = (c[0], c[0]), (c[1] + c[0], c[1]) 

                if copy not in memo:
                    tmp.append(copy)

                if paste not in memo:
                    tmp.append(paste)

            buff = tmp
            steps += 1

        return -1

if __name__ == "__main__":

    res = MinSteps().doit(3)

    res = 0