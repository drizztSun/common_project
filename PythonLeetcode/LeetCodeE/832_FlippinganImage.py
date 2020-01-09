# 832. Flipping an Image

# Given a binary matrix A, we want to flip the image horizontally, then invert it, and return the resulting image.

# To flip an image horizontally means that each row of the image is reversed.  For example, flipping [1, 1, 0] horizontally results in [0, 1, 1].

# To invert an image means that each 0 is replaced by 1, and each 1 is replaced by 0. For example, inverting [0, 1, 1] results in [1, 0, 0].

# Example 1:

# Input: [[1,1,0],[1,0,1],[0,0,0]]
# Output: [[1,0,0],[0,1,0],[1,1,1]]
# Explanation: First reverse each row: [[0,1,1],[1,0,1],[0,0,0]].
# Then, invert the image: [[1,0,0],[0,1,0],[1,1,1]]

# Example 2:

# Input: [[1,1,0,0],[1,0,0,1],[0,1,1,1],[1,0,1,0]]
# Output: [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]
# Explanation: First reverse each row: [[0,0,1,1],[1,0,0,1],[1,1,1,0],[0,1,0,1]].
# Then invert the image: [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]
# Notes:

# 1 <= A.length = A[0].length <= 20
#0 <= A[i][j] <= 1

"""
Approach #1: Direct [Accepted]
Intuition and Algorithm

We can do this in place. In each row, the ith value from the left is equal to the inverse of the ith value from the right.

We use (C+1) / 2 (with floor division) to iterate over all indexes i in the first half of the row, including the center.

Complexity Analysis

Time Complexity: O(N), where N is the total number of elements in A.

Space Complexity: O(1) in additional space complexity.



"""


class FlipAndInvertImage:

    def doit(self, A):
        A1 = []
        for list in A:
            for i in range(len(list)):
                if(list[i] == 1):
                    list[i] = 0
                else:
                    list[i] = 1
            A1.append(list[::-1])
        return A1

    def doit(self, A):
        for row in A:
            for i in range((len(row) + 1) / 2):
                """
                In Python, the shortcut row[~i] = row[-i-1] = row[len(row) - 1 - i]
                helps us find the i-th value of the row, counting from the right.
                """
                row[i], row[~i] = row[~i] ^ 1, row[i] ^ 1
        return A

    def doit(self, A):
        reversed_A, ans = [], []
        for c in A:
            reversed_A.append(list(reversed(c)))

        return [[0 if reversed_A[i][j] == 1 else 1 for j in range(len(reversed_A[0]))] for i in range(len(reversed_A))]


if __name__ == '__main__':

    res = FlipAndInvertImage().doit(
        [[1, 1, 0], [1, 0, 1], [0, 0, 0]])  # [[1,0,0],[0,1,0],[1,1,1]]

    res = FlipAndInvertImage().doit([[1, 1, 0, 0], [1, 0, 0, 1], [0, 1, 1, 1], [
        1, 0, 1, 0]])  # [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]

    pass
