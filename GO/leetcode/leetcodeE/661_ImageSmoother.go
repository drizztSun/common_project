/*
661 Image Smoother

Given a 2D integer matrix M representing the gray scale of an image, you need to design a smoother
to make the gray scale of each cell becomes the average gray scale (rounding down) of all the 8 surrounding cells and itself.
If a cell has less than 8 surrounding cells, then use as many as you can.

Example 1:
Input:
[[1,1,1],
 [1,0,1],
 [1,1,1]]
Output:
[[0, 0, 0],
 [0, 0, 0],
 [0, 0, 0]]
Explanation:
For the point (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
For the point (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
For the point (1,1): floor(8/9) = floor(0.88888889) = 0

*/
package leetcodeE

import (
	"fmt"
)

func imageSmoother(M [][]int) [][]int {

	row, col := len(M), len(M[0])
	res := make([][]int, row)
	for i := range res {
		res[i] = make([]int, col)
	}

	for i := range M {
		for j := range M[i] {
			total, amount := 0, 0

			for x := i - 1; x < i+2; x++ {
				for y := j - 1; y < j+2; y++ {
					if (x >= 0 && x < row) && (y >= 0 && y < col) {
						total += M[x][y]
						amount += 1
					}
				}
			}

			res[i][j] = total / amount
		}
	}

	return res
}

func main() {

	M := [][]int{{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}
	N := imageSmoother(M)

	for i := range N {
		for j := range N[i] {
			fmt.Print("%d, ", N[i][j])
		}
		fmt.Println()
	}

}
