
# 470. Implement Rand10() Using Rand7()


# Given a function rand7 which generates a uniform random integer in the range 1 to 7,
# write a function rand10 which generates a uniform random integer in the range 1 to 10.

# Do NOT use system's Math.random().

 

# Example 1:

# Input: 1
# Output: [7]

# Example 2:

# Input: 2
# Output: [8,4]

# Example 3:

# Input: 3
# Output: [8,1,10]


# The rand7() API is already defined for you.
# def rand7():
# @return a random integer in the range 1 to 7

class Solution:
    def rand10(self):
        """
        :rtype: int
        """


        # Time Complexity
        # The total number of iterations follows geometric distribution. For each iteration in the while loop, 
        # the probabilty of exiting the loop is p = 40/49. So the average time complexity T(n) = O(1/p) = O(49/40) = O(1).

        # Correctness
        # Note that rand49() generates a uniform random integer in [1, 49], so any number in this range has the same probability to be generated. 
        # Suppose k is an integer in range [1, 40], P(rand49() = k) = 1/49.

        #   P(result = k)
        #   P(rand49() = k in the 1st iteration) +
        #   P(rand49() > 40 in the 1st iteration) * P(rand49() = k in the 2nd iteration) +
        #   P(rand49() > 40 in the 1st iteration) * P(rand49() > 40 in the 2nd iteration) * P(rand49() = k in the 3rd iteration) +
        #   P(rand49() > 40 in the 1st iteration) * P(rand49() > 40 in the 2nd iteration) * P(rand49() > 40 in the 3rd iteration) * P(rand49() = k in the 4th iteration) +
        #   ...
        #= (1/49) + (9/49) * (1/49) + (9/49)^2 * (1/49) + (9/49)^3 * (1/49) + ...
        #= (1/49) * [1 + (9/49) + (9/49)^2 + (9/49)^3 + ... ]
        #= (1/49) * [1/(1-9/49)]
        #= (1/49) * (49/40)
        #= 1/40

        #Generalization
        #Implement randM() using randN() when M > N:
        #Step 1: Use randN() to generate randX(), where X >= M. In this problem, I use 7 * (rand7() - 1) + (rand7() - 1) to generate rand49() - 1.
        #Step 2: Use randX() to generate randM(). In this problem, I use rand49() to generate rand40() then generate rand10.

        #Note: N^b * (randN() - 1) + N^(b - 1) * (randN() - 1) + N^(b - 2) * (randN() - 1) + ... + N^0 * (randN() - 1) generates randX() - 1, where X = N^(b + 1).

        # rand7 - rand49 - rand40 - rand10
        res = 40
        while res >= 40:
            res = 7 * (rand7() - 1) + (rand7() - 1)

        return res % 10 + 1



# Generalization
# Implement randM() using randN() when M > N:
# Step 1: Use randN() to generate randX(), where X >= M. In this problem, I use 7 * (rand7() - 1) + (rand7() - 1) to generate rand49() - 1.
# Step 2: Use randX() to generate randM(). In this problem, I use rand49() to generate rand40() then generate rand10.

# Note: N^b * (randN() - 1) + N^(b - 1) * (randN() - 1) + N^(b - 2) * (randN() - 1) + ... + N^0 * (randN() - 1) generates randX() - 1, where X = N^(b + 1).

# More Examples
# (1) Implement rand11() using rand3():

    def rand11(self):
        res = 22
        while res >= 22:
            res = 3 * 3 * (rand3() - 1) + 3 * (rand3() - 1) + (rand3() - 1)

        return res % 11 + 1


#   Idea: rand3() -> rand27() -> rand22 -> rand11
#   Time Comlexity: O(27/22)
#   (2) Implement rand9() using rand7():

    def rand9(self):
        res = 45
        while res >= 45:
            res = 7 * (rand7() - 1) + (rand7() - 1)

        return res % 9 + 1


# Idea: rand7() -> rand49() -> rand45() -> rand9()
# Time Comlexity: O(49/45)

# (3) Implement rand13() using rand6():

    def rand13():
        res = 26
        while res >= 26:
            res = 6 * (rand6() - 1) + (rand6() - 1)

        return res % 13 + 1


# Idea: rand6() -> rand36() -> rand26 -> rand13()
# Time Comlexity: O(36/26)
        
