package leetcodeH

/*
739. Daily Temperatures

Given a list of daily temperatures T, return a list such that, for each day in the input,
tells you how many days you would have to wait until a warmer temperature. If there is no future day for which this is possible, put 0 instead.

For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73], your output should be [1, 1, 4, 2, 1, 1, 0, 0].

Note: The length of temperatures will be in the range [1, 30000]. Each temperature will be an integer in the range [30, 100].
*/

func dailyTemperatures(T []int) []int {

	ans := make([]int, len(T))

	for i := len(T) - 2; i >= 0; i-- {
		if T[i] < T[i+1] {
			ans[i] = 1
		} else {
			m := i + 1 + ans[i+1]
			for m < len(T) {
				if T[i] < T[m] {
					ans[i] = m - i
					break
				} else {
					if ans[m] != 0 {
						m = m + ans[m]
					} else {
						ans[i] = 0
						break
					}
				}
			}
		}
	}

	return ans
}
