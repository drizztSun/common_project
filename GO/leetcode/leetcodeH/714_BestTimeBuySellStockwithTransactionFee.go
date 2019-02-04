package leetcodeH

import "math"

/*
714. Best Time to Buy and Sell Stock with Transaction Fee


*/

type maxProfit int

func (this maxProfit) doit(prices []int, fee int) int {

	holding := make([]int, len(prices))
	unhold := make([]int, len(prices))
	holding[0] = -prices[0]
	unhold[0] = 0

	for i := 1; i < len(prices); i++ {
		holding[i] = int(math.Max(float64(holding[i]), float64(unhold[i-1]-prices[i])))
		unhold[i] = int(math.Max(float64(unhold[i-1]), float64(holding[i-1]+prices[i]-fee)))
	}

	return unhold[len(prices)-1]
}

func (this maxProfit) doit1(prices []int, fee int) int {
	sell, buy := 0, -prices[0]

	for i := 1; i < len(prices); i++ {
		sell = int(math.Max(float64(sell), float64(buy+prices[i]-fee)))
		buy = int(math.Max(float64(buy), float64(sell-prices[i])))
	}
	return sell
}

func (this maxProfit) doit2(prices []int, fee int) int {

	ans := 0
	minv := prices[0]
	for i := 1; i < len(prices); i++ {

		if prices[i] < minv {
			minv = prices[i]
		} else if prices[i] > minv+fee {
			ans += prices[i] - minv - fee
			minv = prices[i] - fee
		}
	}
	return ans
}
