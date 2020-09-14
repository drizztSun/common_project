package leetcodem

/*
338. Counting Bits

Given a non negative integer number num.
For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.

Example 1:

Input: 2
Output: [0,1,1]
Example 2:

Input: 5
Output: [0,1,1,2,1,2]
Follow up:

It is very easy to come up with a solution with run time O(n*sizeof(integer)). But can you do it in linear time O(n) /possibly in a single pass?
Space complexity should be O(n).
Can you do it like a boss? Do it without using any builtin function like __builtin_popcount in c++ or in any other language.
*/
import (
	"math"
)

func countBits_dp(num int) []int {

	dp := make([]int, num+1)

	for i := 1; i <= num; i++ {
		dp[i] = dp[i/2] + i%2
	}

	return dp[num]
}

func countBits_dp_1(num int) []int {
	res := make([]int, num+1)
	res[0] = 0
	if num == 0 {
		return res
	}
	res[1] = 1
	if num == 1 {
		return res
	}

	last := 1
	for i := 2; i <= num; i++ {
		if i == last<<1 {
			res[i] = 1
			last = i
		} else {
			res[i] = 1 + res[i^last]
		}
	}
	return res
}

func countBits_dp_2(num int) []int {
	if num == 0 {
		return []int{0}
	} else if num == 1 {
		return []int{0, 1}
	}

	out := []int{0, 1}
	i := 2
	for ; num >= int(math.Pow(float64(2), float64(i)))-1; i++ {
		tmp := make([]int, 0)
		for _, c := range out {
			tmp = append(tmp, c+1)
		}
		out = append(out, tmp...)
	}

	rem := num - int(math.Pow(float64(2), float64(i-1))) + 1

	if rem > 0 {
		tmp := make([]int, 0)
		for i := 0; i < rem; i++ {
			tmp = append(tmp, out[i]+1)
		}
		out = append(out, tmp...)
	}

	return out
}
