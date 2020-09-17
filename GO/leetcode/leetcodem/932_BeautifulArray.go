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

	odd := search_beautiful_array((n+1)/2)
	even := search_beautiful_array(n/2)

	for i := range odd {
		odd[i] = 2 * odd[i] - 1
	}

	for j := range even {
		even[j] = 2 * even[j]
	}

	odd = append(odd, even...)
	memo[n] = odd
	return odd
}

func beautifulArray_divide_and_conquer(N, int) []int {

	memo := map[int][]int{1: []int{1}}

	return search_beautiful_array(N)
}
