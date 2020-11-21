"""
# 454. 4Sum II
# Given four lists A, B, C, D of integer values, compute how many tuples (i, j, k, l)
# there are such that A[i] + B[j] + C[k] + D[l] is zero.

# To make problem a bit easier, all A, B, C, D have same length of N where 0 ? N ? 500.
# All integers are in the range of -228 to 228 - 1 and the result is guaranteed to be at most 231 - 1.

# Example:

# Input:
# A = [ 1, 2]
# B = [-2,-1]
# C = [-1, 2]
# D = [ 0, 2]

# Output:
# 2

# Explanation:
# The two tuples are:
# 1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
# 2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
"""


class FourSumCount:

    def doit1(self, A, B, C, D):
        """
        :type A: List[int]
        :type B: List[int]
        :type C: List[int]
        :type D: List[int]
        :rtype: int
        """
        d34 = {}
        for i in C:
            for j in D:
                d34[i + j] = d34.get(i+j, 0) + 1

        amount = 0 
        for s in A:
            for z in B:
                index = - (s + z)
                if index in d34:
                    amount += d34[index]

        return amount

    def doit2(self, A, B, C, D):
        """
        :type A: List[int]
        :type B: List[int]
        :type C: List[int]
        :type D: List[int]
        :rtype: int
        """
        length = len(A)
        count = 0
        A_B_sum_dic = {}

        for index_a in range(length):
            for index_b in range(length):
                A_B_sum = A[index_a] + B[index_b]
                if A_B_sum in A_B_sum_dic:
                    A_B_sum_dic[A_B_sum] += 1
                else:
                    A_B_sum_dic[A_B_sum] = 1
                # A_B_sum_dic.setdefault ?

        for index_c in range(length):
            for index_d in range(length):
                neg_C_D_sum = -(C[index_c] + D[index_d])
                if neg_C_D_sum in A_B_sum_dic:
                    count += A_B_sum_dic[neg_C_D_sum]

        return count


if __name__=="__main__":

    res = fourSumCount().doit([1,2], [-2,-1], [-1,2], [0,2])