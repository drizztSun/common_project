package leetcodeE

/*
766. Toeplitz Matrix

# A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same element.

# Now given an M x N matrix, return True if and only if the matrix is Toeplitz.


# Example 1:

# Input:
# matrix = [
#  [1,2,3,4],
#  [5,1,2,3],
#  [9,5,1,2]
#]
# Output: True

# Explanation:
# In the above grid, the diagonals are:
# "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]".
# In each diagonal all elements are the same, so the answer is True.

# Example 2:

# Input:
# matrix = [
#  [1,2],
#  [2,2]
# ]
# Output: False
# Explanation:
# The diagonal "[1, 2]" has different elements.

# Note:

# matrix will be a 2D array of integers.
# matrix will have a number of rows and columns in range [1, 20].
# matrix[i][j] will be integers in range [0, 99].

*/

func isToeplitzMatrix1(matrix [][]int) bool {
	for i := 1; i < len(matrix); i++ {
		for j := 1; j < len(matrix[0]); j++ {
			if matrix[i-1][j-1] == matrix[i][j] {
				continue
			}

			return false
		}
	}

	return true
}

func isToeplitzMatrix(matrix [][]int) bool {

	M, N := len(matrix), len(matrix[0])

	for i := 0; i < M; i++ {
		c, t, b := matrix[i][0], i, 0
		for t < M && b < N {
			if matrix[t][b] != c {
				return false
			}
			b++
			t++
		}
	}

	for i := 1; i < N; i++ {
		c, t, b := matrix[0][i], 0, i
		for t < M && b < N {
			if matrix[t][b] != c {
				return false
			}
			b++
			t++
		}
	}

	return true
}
