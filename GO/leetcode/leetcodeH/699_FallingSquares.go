package leetcodeH

func fallingSquares(positions [][]int) []int {

	left_bound := func(pos []int, target int) int {

		left, right := 0, len(pos)
		for left < right {

			mid := (left + right) / 2

			if pos[mid] >= target {
				right = mid
			} else {
				left = mid + 1
			}

		}
		return left
	}

	right_bound := func(pos []int, target int) int {

		left, right := 0, len(pos)
		for left < right {

			mid := (left + right) / 2

			if pos[mid] <= target {
				left = mid + 1
			} else {
				right = mid
			}

		}
		return left
	}

	pos, height := []int{0}, []int{0}
	currentHeight := 0
	ans := make([]int, 0)

	for _, c := range positions {

		left, side := c[0], c[1]
		right := left + side

		i := right_bound(pos, left)
		j := left_bound(pos, right)

		maxh := 0
		for c := i - 1; c < j; c++ {
			if height[c] > maxh {
				maxh = height[c]
			}
		}

		maxh += side

		if i >= len(pos) {
			pos = append(pos, []int{left, right}...)
			height = append(height, []int{maxh, height[j-1]}...)
		} else {
			pos = append(pos[:i-1], append([]int{left, right}, pos[j:]...)...)
			height = append(height[:i-1], append([]int{maxh, height[j-1]}, height[j:]...)...)
		}

		if maxh > currentHeight {
			currentHeight = maxh
		}

		ans = append(ans, currentHeight)
	}

	return ans
}

func Test_699_FallSquare() {

	fallingSquares([][]int{[]int{1, 2}, []int{2, 3}, []int{6, 1}})
}
