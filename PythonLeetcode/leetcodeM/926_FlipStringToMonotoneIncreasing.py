# 926. Flip String to Monotone Increasing

# A string of '0's and '1's is monotone increasing if it consists of some number of '0's (possibly 0),
#  followed by some number of '1's (also possibly 0.)

# We are given a string S of '0's and '1's, and we may flip any '0' to a '1' or a '1' to a '0'.

# Return the minimum number of flips to make S monotone increasing.


# Example 1:

# Input: "00110"
# Output: 1
# Explanation: We flip the last digit to get 00111.

# Example 2:

# Input: "010110"
# Output: 2
# Explanation: We flip to get 011111, or alternatively 000111.

# Example 3:

# Input: "00011000"
# Output: 2
# Explanation: We flip to get 00000000.

class MinFlipsMonoIncr:

    """
    Approach 1: Prefix Sums
    Intuition

    For say a 5 digit string, the answer is either '00000', '00001', '00011', '00111', '01111', or '11111'. Let's try to calculate the cost of switching to that answer. The answer has two halves, a left (zero) half, and a right (one) half.

    Evidently, it comes down to a question of knowing, for each candidate half: how many ones are in the left half, and how many zeros are in the right half.

    We can use prefix sums. Say P[i+1] = A[0] + A[1] + ... + A[i], where A[i] = 1 if S[i] == '1', else A[i] = 0. We can calculate P in linear time.

    Then if we want x zeros followed by N-x ones, there are P[x] ones in the start that must be flipped,
    plus (N-x) - (P[N] - P[x]) zeros that must be flipped. The last calculation comes from the fact that there are P[N] - P[x] ones in the later segment of length N-x, but we want the number of zeros.

    Algorithm

    For example, with S = "010110": we have P = [0, 0, 1, 1, 2, 3, 3]. Now say we want to evaluate having x=3 zeros.

    There are P[3] = 1 ones in the first 3 characters, and P[6] - P[3] = 2 ones in the later N-x = 3 characters.

    So, there is (N-x) - (P[N] - P[x]) = 1 zero in the later N-x characters.

    We take the minimum among all candidate answers to arrive at the final answer.

    Complexity Analysis

    Time Complexity: O(N), where N is the length of S.

    Space Complexity: O(N).
    """

    def doit(self, S):
        P = [0]
        for c in S:
            P.append(P[-1] + int(c))

        return min(P[i] + len(S) - i - (P[-1] - P[i]) for i in range(len(P)))

    def doit(self, S):

        flip, ones = 0, 0

        for c in S:
            if c == '0':
                flip += 1
            else:
                ones += 1

            if flip > ones:
                flip = ones

        return min(flip, ones)


if __name__ == '__main__':

    res = MinFlipsMonoIncr().doit("00110")

    res = MinFlipsMonoIncr().doit("010110")

    res = MinFlipsMonoIncr().doit("00011000")
