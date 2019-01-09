package leetcodeE

/*
746. Min Cost Climbing Stairs

On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).

Once you pay the cost, you can either climb one or two steps. You need to find minimum cost to reach the top of the floor, and you can either start from the step with index 0, or the step with index 1.

Example 1:
Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.
Example 2:
Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].
Note:
cost will have a length in the range [2, 1000].
Every cost[i] will be an integer in the range [0, 999].

*/

import (
	"math"
)

// iterate
func doit(cost []int) int {
	cost = append(cost, 0)
	dp := make([]int, len(cost))

	for i := range cost {
		if i == 0 {
			dp[i] = cost[0]
		} else if i == 1 {
			dp[i] = cost[i]
		} else {
			dp[i] = int(math.Min(float64(dp[i-1]), float64(dp[i-2]))) + cost[i]
		}
	}

	return dp[len(cost)-1]
}

// recursive
func recursive(i int, cost []int, lib map[int]int) int {
	if i == 0 || i == 1 {
		return cost[i]
	} else {
		if v, ok := lib[i]; ok {
			return v
		}

		lib[i] = int(math.Min(float64(recursive(i-1, cost, lib)), float64(recursive(i-2, cost, lib)))) + cost[i]
		return lib[i]
	}
}

func doit1(cost []int) int {

	cost = append(cost, 0)
	dp := make(map[int]int)

	return recursive(len(cost)-1, cost, dp)
}
