package leetcodem

func findNumberOfLIS(nums []int) int {

	min := func(a, b int) int {
		if a > b {
			return b
		}

		return a
	}

	minv := 1000000
	for _, v := range nums {
		minv = min(minv, v)
	}

	buff := []map[int]int{{minv - 1: 1}}
	standard := []int{minv - 1}

	search := func(b int) int {

		low, high := 0, len(standard)
		for low < high {
			mid := (low + high) / 2

			if standard[mid] >= b {
				high = mid
			} else {
				low = mid + 1
			}
		}

		return low
	}

	for _, c := range nums {

		i, t := search(c)-1, 0

		if i == len(standard)-1 {
			buff = append(buff, map[int]int{})
			standard = append(standard, c)
		}

		for k, v := range buff[i] {
			if k < c {
				t += v
			} else {
				delete(buff[i], k)
			}
		}

		buff[i+1][c] += t
		standard[i+1] = min(standard[i+1], c)
	}

	res := 0
	for _, v := range buff[len(buff)-1] {
		res += v
	}

	return res
}

func Test_673_NumberOfLongestIncreasingSequence() {

	findNumberOfLIS([]int{-100, -99, -98, -97, -96, -96})

	findNumberOfLIS([]int{1, 3, 5, 4, 7})
}
