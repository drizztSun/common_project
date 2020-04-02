package leetcodem

/*

1049. Last Stone Weight II

We have a collection of rocks, each rock has a positive integer weight.

Each turn, we choose any two rocks and smash them together.  Suppose the stones have weights x and y with x <= y.  The result of this smash is:

If x == y, both stones are totally destroyed;
If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y-x.
At the end, there is at most 1 stone left.  Return the smallest possible weight of this stone (the weight is 0 if there are no stones left.)



Example 1:

Input: [2,7,4,1,8,1]
Output: 1
Explanation:
We can combine 2 and 4 to get 2 so the array converts to [2,7,1,8,1] then,
we can combine 7 and 8 to get 1 so the array converts to [2,1,1,1] then,
we can combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
we can combine 1 and 1 to get 0 so the array converts to [1] then that's the optimal value.


*/

func lastStoneWeightII(stones []int) int {

	total, start := 0, 10000000
	for _, w := range stones {
		if start > w {
			start = w
		}
		total += w
	}

	dp := make([]bool, total/2+1)
	dp[0] = true

	for _, c := range stones {

		for i := total / 2; i > start-1; i-- {
			if i-c >= 0 && dp[i-c] {
				dp[i] = true
			}
		}
	}

	i := total / 2
	for ; i > -1; i-- {
		if dp[i] {
			break
		}
	}

	c := 2*i - total
	if c < 0 {
		return -c
	}
	return c
}

func Test_1049_LastStoneWeightII() {

	lastStoneWeightII([]int{1, 1, 4, 2, 2})

	lastStoneWeightII([]int{2, 7, 4, 1, 8, 1})
}
