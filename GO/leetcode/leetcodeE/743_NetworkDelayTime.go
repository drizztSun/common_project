package leetcodeE

import (
	"math"
)

func networkDelayTime(times [][]int, N, K int) int {

	dict := make(map[int][][2]int)

	for _, elem := range times {
		u, v, w := elem[0], elem[1], elem[2]
		if _, ok := dict[u-1]; ok {
			dict[u-1] = append(dict[u-1], [2]int{v - 1, w})
		} else {
			dict[u-1] = [][2]int{{v, w}}
		}
	}

	uv := make([]int, N)
	for i := range uv {
		uv[i] = math.MaxUint32
	}
	uv[K-1] = 0

	done := make([]bool, N)
	for i := range uv {
		done[i] = false
	}

	for i := 0; i < N; i++ {
		u := -1
		minv := math.MaxInt32

		for i, v := range uv {
			if !done[i] && v < minv {
				minv = v
				u = i
			}
		}

		if elem, ok := dict[u]; ok {
			for _, w := range elem {
				if w[1]+minv < uv[i] {
					uv[i] = w[1] + minv
				}
			}
		}

		done[u] = true
	}

	ans := 0
	for _, v := range uv {
		if v == math.MaxUint32 {
			return -1
		} else if v > ans {
			ans = v
		}
	}
	return ans
}
