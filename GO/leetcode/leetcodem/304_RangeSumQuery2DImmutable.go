package leetcodem

/*
304. Range Sum Query 2D - Immutable

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
Note:
You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 ≤ row2 and col1 ≤ col2.

*/

type NumMatrix struct {
	NumSum [][]int
}

func Constructor(matrix [][]int) NumMatrix {

	if len(matrix) == 0 || len(matrix[0]) == 0 {
		return NumMatrix{NumSum: nil}
	}

	m, n := len(matrix), len(matrix[0])
	sumarr := make([][]int, m)
	for i := range sumarr {
		sumarr[i] = make([]int, n)
		sum := 0
		for j := range sumarr[i] {
			sum += matrix[i][j]
			if i == 0 {
				sumarr[i][j] = sum
			} else {
				sumarr[i][j] = sum + sumarr[i-1][j]
			}
		}
	}

	return NumMatrix{
		NumSum: sumarr,
	}
}

func (this *NumMatrix) SumRegion(row1 int, col1 int, row2 int, col2 int) int {

	if this.NumSum == nil {
		return 0
	}

	s3, s2, s1 := 0, 0, 0

	if row1 > 0 && col1 > 0 {
		s1 = this.NumSum[row1-1][col1-1]
	}

	if row1 > 0 {
		s2 = this.NumSum[row1-1][col2]
	}

	if col1 > 0 {
		s3 = this.NumSum[row2][col1-1]
	}

	return this.NumSum[row2][col2] - s2 - s3 + s1
}
