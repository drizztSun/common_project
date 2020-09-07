package leetcodeH

/*
84. Largest Rectangle in Histogram

Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.
*/

func largestRectangleArea_stack(heights []int) int {

	/*
	   idea: Each value of Heights has a potential Area, by its heights.
	   We need find the index of its first, left and right height, which is less than its heights.
	   They are the left board and right board
	*/

	boards, maxArea := make([]int, 0), 0
	heights = append([]int{0}, heights...) // 0, in the left side
	heights = append(heights, 0)           // 0, in the right side

	for i := range heights {

		// boards, stack only index j, heights[i] > heighs[j], pop out every one, heights[j+1] > heights[i].
		// leftboard is the first left one, less than current Height[len(heights)-1]
		// rightboard is the i, the first right now, less than last index, height[len(heights)-1]
		// calculate rectangle Area, high == heights[board[len(heights)-1]].
		for len(boards) > 0 && heights[i] < heights[boards[len(boards)-1]] {
			height := heights[boards[len(boards)-1]]
			boards = boards[:len(boards)-1]
			leftboard, rightboard := boards[len(boards)-1], i
			area := height * (rightboard - leftboard - 1)
			if area > maxArea {
				maxArea = area
			}
		}

		boards = append(boards, i)
	}

	return maxArea
}
