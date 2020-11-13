package leetcodeH

func dfs(cur, last int, level int, graph map[int][]int, jump []int, res *[][]int) int {

	jump[cur] = level + 1

	for _, c := range graph[cur] {

		if c == last {
			continue
		} else if jump[c] == -1 {
			n := dfs(c, cur, level+1, graph, jump, res)
			if jump[cur] > n {
				jump[cur] = n
			}
		} else if jump[c] < jump[cur] {
			jump[cur] = jump[c]
		}
	}

	if jump[cur] == level+1 && cur != 0 {
		*res = append(*res, []int{last, cur})
	}

	return jump[cur]
}

func criticalConnections(n int, connections [][]int) [][]int {

	graph := make(map[int][]int)

	for _, c := range connections {
		graph[c[1]] = append(graph[c[1]], c[0])
		graph[c[0]] = append(graph[c[0]], c[1])
	}

	jump := make([]int, n)
	for i := range jump {
		jump[i] = -1
	}
	ans := make([][]int, 0)

	dfs(0, -1, -1, graph, jump, &ans)

	return ans
}
