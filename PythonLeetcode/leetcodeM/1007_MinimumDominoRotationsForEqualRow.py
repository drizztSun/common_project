# 1007. Minimum Domino Rotations For Equal Row

# In a row of dominoes, A[i] and B[i] represent the top and bottom halves of the i-th domino.
# (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)

# We may rotate the i-th domino, so that A[i] and B[i] swap values.

# Return the minimum number of rotations so that all the values in A are the same, or all the values in B are the same.

# If it cannot be done, return -1.


# Example 1:
# Input: A = [2,1,2,4,2,2], B = [5,2,6,2,3,2]
# Output: 2
# Explanation:
# The first figure represents the dominoes as given by A and B: before we do any rotations.
# If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.

# Example 2:

# Input: A = [3,5,1,2,3], B = [3,6,3,3,4]
# Output: -1
# Explanation:
# In this case, it is not possible to rotate the dominoes to make one row of values equal.


class MinDominoRotations:

    def doit(self, A, B):
        """
        :type A: List[int]
        :type B: List[int]
        :rtype: int
        """
        from collections import Counter
        cnt = Counter(A + B)
        num, t = max([(v, k) for k, v in cnt.items()])
        if num < len(A):
            return -1

        a, b = 0, 0
        for i in range(len(A)):

            n = num
            if A[i] == t:
                num -= 1
                a += 1

            if B[i] == t:
                num -= 1
                b += 1

            if num == n or (num == 0 and i != len(A) - 1):
                return -1

        return len(A) - max(a, b)

    def doit(self, A, B):
        """
        :type A: List[int]
        :type B: List[int]
        :rtype: int
        """
        def check(A, B, val):
            a_rot = b_rot = 0

            for i in range(len(A)):
                if A[i] != val and B[i] != val:
                    return -1
                elif A[i] != val:
                    a_rot += 1
                elif B[i] != val:
                    b_rot += 1

            return min(a_rot, b_rot)

        min_rot = check(A, B, A[0])

        if min_rot != -1 or A[0] == B[0]:
            return min_rot

        return check(A, B, B[0])


if __name__ == '__main__':

    res = MinDominoRotations().doit(A=[2, 1, 2, 4, 2, 2], B=[5, 2, 6, 2, 3, 2])

    res = MinDominoRotations().doit(A=[3, 5, 1, 2, 3], B=[3, 6, 3, 3, 4])

    res = MinDominoRotations().doit(
        [1, 2, 1, 1, 1, 2, 2, 2], [2, 1, 2, 2, 2, 2, 2, 2])

    pass
