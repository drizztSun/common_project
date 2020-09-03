package leetcodem

import (
	"fmt"
	"math"
)

/*

There are N network nodes, labelled 1 to N.

Given times, a list of travel times as directed edges times[i] = (u, v, w), where u is the source node, v is the target node, and w is the time it takes for a signal to travel from source to target.

Now, we send a signal from a certain node K. How long will it take for all nodes to receive the signal? If it is impossible, return -1.

Input: times = [[2,1,1],[2,3,1],[3,4,1]], N = 4, K = 2
Output: 2


Note:

N will be in the range [1, 100].
K will be in the range [1, N].
The length of times will be in the range [1, 6000].
All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 0 <= w <= 100.

*/

func networkDelayTime(times [][]int, N int, K int) int {

    dict := make(map[int][][2]int)

    for _, elem := range times {
        u, v, w := elem[0], elem[1], elem[2]
		if  _ , ok := dict[u-1]; ok {
            dict[u-1] = append(dict[u-1], [2]int{v-1, w})
		} else {
			dict[u-1] = [][2]int{{v-1, w}}
		}
	}

    uv := make([]int, N)
	for i := range uv {
		uv[i] = math.MaxInt32
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
			if ! done[i] && v <= minv {
				minv = v
				u = i
			}
		}

		if elem, ok := dict[u]; ok {
			for _, w := range elem {
                fmt.Println(w)

				if w[1] + minv < uv[w[0]] {
					uv[w[0]] = w[1] + minv
				}
			}
		}

        fmt.Println(u)
        fmt.Println(done)
        fmt.Println(uv)
		done[u] = true
	}

	ans := 0
    for _, v := range uv {
		if v == math.MaxInt32 {
			return -1
		} else if v > ans {
			ans = v
		}
	}
	return ans
}