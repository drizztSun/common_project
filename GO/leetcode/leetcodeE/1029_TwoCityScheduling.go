package leetcodeE

/*
# 1029. Two City Scheduling

# There are 2N people a company is planning to interview.
# The cost of flying the i-th person to city A is costs[i][0],
# and the cost of flying the i-th person to city B is costs[i][1].

# Return the minimum cost to fly every person to a city such that exactly N people arrive in each city.


# Example 1:

# Input: [[10,20],[30,200],[400,50],[30,20]]
# Output: 110
# Explanation:
# The first person goes to city A for a cost of 10.
# The second person goes to city A for a cost of 30.
# The third person goes to city B for a cost of 50.
# The fourth person goes to city B for a cost of 20.

# The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people interviewing in each city.


# Note:

# 1 <= costs.length <= 100
# It is guaranteed that costs.length is even.
# 1 <= costs[i][0], costs[i][1] <= 1000 */

import (
	"fmt"
	"sort"
)

func twoCitySchedCost(costs [][]int) int {

	sort.SliceStable(costs, func(i, j int) bool {
		return costs[i][0]-costs[i][1] < costs[j][0]-costs[j][1]
	})

	ans := 0
	N := len(costs) / 2
	for i := range costs {
		if i < N {
			ans += costs[i][0]
		} else {
			ans += costs[i][1]
		}
	}

	return ans
}

func twoCitySchedCost1(costs [][]int) int {

	abs := func(a int) int {
		if a > 0 {
			return a
		}
		return -a
	}

	sort.SliceStable(costs, func(i, j int) bool { return abs(costs[i][0]-costs[i][1]) > abs(costs[j][0]-costs[j][1]) })
	a, b := 0, 0
	N := len(costs) / 2
	ret := 0

	for i := 0; i < len(costs); i++ {
		if a == N {
			ret += costs[i][1]
			b++
			continue
		}
		if b == N {
			ret += costs[i][0]
			a++
			continue
		}
		if costs[i][0] < costs[i][1] {
			ret += costs[i][0]
			a++
		} else {
			ret += costs[i][1]
			b++
		}
	}
	return ret
}

func Test_1029_TwoCityScheduling() {

	input := [][]int{
		{10, 20},
		{30, 200},
		{400, 50},
		{30, 20},
	}

	fmt.Println(twoCitySchedCost(input))
}
