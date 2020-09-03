package leetcodem

/*
1306. Jump Game III

Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach to any index with value 0.

Notice that you can not jump outside of the array at any time.



Example 1:

Input: arr = [4,2,3,0,3,1,2], start = 5
Output: true
Explanation:
All possible ways to reach at index 3 with value 0 are:
index 5 -> index 4 -> index 1 -> index 3
index 5 -> index 6 -> index 4 -> index 1 -> index 3
Example 2:

Input: arr = [4,2,3,0,3,1,2], start = 0
Output: true
Explanation:
One possible way to reach at index 3 with value 0 is:
index 0 -> index 4 -> index 1 -> index 3
Example 3:

Input: arr = [3,0,2,1,2], start = 2
Output: false
Explanation: There is no way to reach at index 1 with value 0.
*/

func canReach_dfs(arr []int, start int) bool {

	if start < 0 || start >= len(arr) || arr[start] < 0 {
		return false
	}

	if arr[start] == 0 {
		return true
	}

	// seen one
	arr[start] = -arr[start]

	return canReach_dfs(arr, start+arr[start]) || canReach_dfs(arr, start-arr[start])
}

func canReach_bfs(arr []int, start int) bool {

	buff := []int{start}

	for len(buff) > 0 {

		n := buff[0]
		buff = buff[1:]

		if arr[n] < 0 {
			continue
		}

		if arr[n] == 0 {
			return true
		}

		for _, i := range []int{n + arr[n], n - arr[n]} {
			if i >= 0 && i < len(arr) {
				buff = append(buff, i)
			}
		}

		arr[n] = -arr[n]
	}

	return false
}

func Test_1306_JumpGameIII() {

	canReach_bfs([]int{3, 0, 2, 1, 2}, 2)
}
