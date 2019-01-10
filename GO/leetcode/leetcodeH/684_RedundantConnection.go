/*

In this problem, a tree is an undirected graph that is connected and has no cycles.

The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N), with one additional edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] with u < v, that represents an undirected edge connecting nodes u and v.

Return an edge that can be removed so that the resulting graph is a tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array. The answer edge [u, v] should be in the same format, with u < v.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given undirected graph will be like this:
  1
 / \
2 - 3
Example 2:
Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
Output: [1,4]
Explanation: The given undirected graph will be like this:
5 - 1 - 2
    |   |
	4 - 3

*/

package leetcodeH

type union_find struct {
	parents []int
}

func (i *union_find) find(a int) int {
	if i.parents[a] != a {
		i.parents[a] = i.find(i.parents[a])
	}
	return i.parents[a]
}

func (i *union_find) union(a, b int) bool {

	i.parents[a] = i.find(a)
	i.parents[b] = i.find(b)

	if i.parents[a] != i.parents[b] {
		i.parents[i.parents[a]] = i.parents[b]
		return true
	} else {
		return false
	}
}

func findRedundantConnection(edges [][]int) []int {

	unionfind := union_find{make([]int, len(edges)+1)}

	for _, edge := range edges {

		if !unionfind.union(edge[0], edge[1]) {
			return edge
		}
	}
	return []int{-1, -1}
}