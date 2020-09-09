package leetcodem

/*

96. Unique Binary Search Trees

Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?

Example:

Input: 3
Output: 5
Explanation:
Given n = 3, there are a total of 5 unique BST's:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

*/
func find_NumTree(n int, buff []int) int {

	if buff[n] != -1 {
		return buff[n]
	}

	res := 0
	for i := 1; i < n+1; i++ {
		res += find_NumTree(i-1, buff) * find_NumTree(n-i, buff)
	}

	buff[n] = res
	return res
}

func numTrees(n int) int {

	buff := make([]int, n+1)
	for i := 0; i < n+1; i++ {
		buff[i] = -1
	}

	buff[0], buff[1] = 1, 1

	return find_NumTree(n, buff)
}
