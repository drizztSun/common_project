package leetcodem

/*
240. Search a 2D Matrix II

Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
Example:

Consider the following matrix:

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
Given target = 5, return true.

Given target = 20, return false.
*/

func search_matrix_scope(matrix [][]int, target int, r1, c1 int, r2, c2 int) bool {

	if r1 > r2 || c1 > c2 {
		return false
	}

	r, c := (r1+r2)/2, (c1+c2)/2

	if matrix[r][c] == target {
		return true
	}

	if matrix[r][c] > target {
		return search_matrix_scope(matrix, target, r1, c1, r-1, c2) || search_matrix_scope(matrix, target, r, c1, r2, c-1)
	}

	return search_matrix_scope(matrix, target, r+1, c1, r2, c2) || search_matrix_scope(matrix, target, r1, c+1, r, c2)
}

func searchMatrix_divide_and_conquer(matrix [][]int, target int) bool {

	if len(matrix) == 0 || len(matrix[0]) == 0 {
		return false
	}

	return search_matrix_scope(matrix, target, 0, 0, len(matrix)-1, len(matrix[0])-1)
}

func searchMatrix(matrix [][]int, target int) bool {

	if len(matrix) == 0 || len(matrix[0]) == 0 {
		return false
	}

	m, n := len(matrix), len(matrix[0])
	r, l := 0, n - 1

	for r < m && l >= 0 {

		if matrix[r][l] == target {
			return true
		}

		if matrix[r][l] > target {
			l -= 1
		} else {
			r += 1
		}
	}

	return false
}
