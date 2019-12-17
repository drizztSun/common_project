package leetcodeE

import "fmt"

func OrderOfLargestPlusSign_1(N int, mines [][]int) int {

	grid := make([][]int, N)
	for i := range grid {
		grid[i] = make([]int, N)
	}

	for i := range grid {
		for j := range grid {
			grid[i][j] = N
		}
	}

	for i := range mines {
		grid[mines[i][0]][mines[i][1]] = 0
	}

	for i := range grid {

		var Left, Right, Bottom, Top int

		for j := range grid {
			k := N - 1 - j

			if grid[i][j] == 0 {
				Left = 0
			} else {
				Left += 1
			}
			if Left < grid[i][j] {
				grid[i][j] = Left
			}

			if grid[i][k] == 0 {
				Right = 0
			} else {
				Right += 1
			}
			if Right < grid[i][k] {
				grid[i][k] = Right
			}

			if grid[k][i] == 0 {
				Bottom = 0
			} else {
				Bottom += 1
			}
			if Bottom < grid[k][i] {
				grid[k][i] = Bottom
			}

			if grid[j][i] == 0 {
				Top = 0
			} else {
				Top += 1
			}
			if Top < grid[j][i] {
				grid[j][i] = Top
			}

		}
	}

	res := -1
	for i := range grid {
		for j := range grid {
			if grid[i][j] > res {
				res = grid[i][j]
			}
		}
	}

	return res
}

func Test_744_OrderOfLargestPlusSign() {

	var res int

	res = OrderOfLargestPlusSign_1(5, [][]int{[]int{4, 2}})

	res = OrderOfLargestPlusSign_1(2, [][]int{})

	res = OrderOfLargestPlusSign_1(1, [][]int{[]int{0, 0}})

	fmt.Println(res)

}
