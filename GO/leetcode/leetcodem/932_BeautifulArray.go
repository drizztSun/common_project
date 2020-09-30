package leetcodem

/*
932. Beautiful Array

For some fixed N, an array A is beautiful if it is a permutation of the integers 1, 2, ..., N, such that:

For every i < j, there is no k with i < k < j such that A[k] * 2 = A[i] + A[j].

Given N, return any beautiful array A.  (It is guaranteed that one exists.)



Example 1:

Input: 4
Output: [2,1,4,3]
Example 2:

Input: 5
Output: [3,1,2,5,4]

*/

func search_beautiful_array(n int, memo map[int][]int) []int {

	if c, ok := memo[n]; ok {
		return c
	}

	odd := search_beautiful_array((n+1)/2, memo)
	even := search_beautiful_array(n/2, memo)

	res := make([]int, len(odd)+len(even))

	b := 0
	for i := range odd {
		res[b] = 2*odd[i] - 1
		b++
	}

	for j := range even {
		res[b] = 2 * even[j]
		b++
	}

	memo[n] = res
	return res
}

func beautifulArray_divide_and_conquer(N int) []int {

	memo := map[int][]int{1: []int{1}}

	return search_beautiful_array(N, memo)
}
