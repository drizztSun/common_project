package leetcodeH

/*
188. Best Time to Buy and Sell Stock IV

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

Example 1:

Input: [2,4,1], k = 2
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
Example 2:

Input: [3,2,6,5,0,3], k = 2
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4.
			 Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.

*/

import (
	"container/heap"
	"math"
)

type profit []int

func (c profit) Len() int {
	return len(c)
}

func (c profit) Less(i, j int) bool {
	return c[i] < c[j]
}

func (c profit) Swap(i, j int) {
	c[i], c[j] = c[j], c[i]
}

func (c *profit) Push(x interface{}) {
	*c = append(*c, x.(int))
}

func (c *profit) Pop() interface{} {
	old := *c
	n := len(old)

	v := old[n-1]
	*c = old[0 : n-1]

	return v
}

func maxProfitIV(k int, prices []int) int {

	i := 0
	//var hprofit profit
	hprofit := &profit{1, 5, 2}
	heap.Init(hprofit)
	var pairs [][2]int

	for i < len(prices) {

		v := i
		for v < len(prices)-1 && prices[v] > prices[v+1] {
			v++
		}

		p := v + 1
		for p < len(prices) && prices[p] > prices[p-1] {
			p++
		}

		for len(pairs) > 0 && pairs[len(pairs)-1][0] > prices[v] {
			x, y := pairs[len(pairs)-1][0], pairs[len(pairs)-1][1]
			heap.Push(hprofit, prices[x]-prices[y-1])
			pairs = pairs[0 : len(pairs)-1]
		}

		for len(pairs) > 0 && prices[p-1] >= prices[pairs[len(pairs)-1][1]-1] {
			x, y := pairs[len(pairs)-1][0], pairs[len(pairs)-1][1]
			heap.Push(hprofit, prices[v]-prices[y-1])
			v = x
			pairs = pairs[0 : len(pairs)-1]
		}

		pairs = append(pairs, [2]int{v, p})
	}

	for i := 0; i < len(pairs); i++ {
		heap.Push(hprofit, prices[pairs[i][0]]-prices[pairs[i][1]-1])
	}

	ans := 0
	for k > 0 {
		ans += -heap.Pop(hprofit).(int)
		k--
	}

	return ans
}

// <DP>
func maxProfitIV2(k int, prices []int) int {

	if len(prices) < 2 {
		return 0
	}

	if k >= len(prices)/2 {
		ans := 0
		for i := 1; i < len(prices); i++ {
			if prices[i] > prices[i-1] {
				ans += prices[i] - prices[i-1]
			}
		}
		return ans
	}

	global := make([][]int, k+1)

	for i := 0; i < len(global); i++ {
		global[i] = make([]int, len(prices))

	}

	for i := 1; i < len(global); i++ {

		local := make([]int, len(prices))

		for j := 1; j < len(prices); j++ {
			profit := prices[j] - prices[j-1]

			local[j] = int(math.Max(math.Max(float64(global[i-1][j]), float64(global[i-1][j-1]+profit)),
				math.Max(float64(global[i-1][j]), float64(local[j-1]+profit))))

			global[i][j] = int(math.Max(float64(local[j]), float64(global[i][j-1])))
		}
	}

	return global[k][len(prices)-1]
}
