package leetcodeH

func catMouseGame(graph [][]int) int {

	N := len(graph)

	// i mouse, j cat, k turn, value 0 has been solved
	// adj_cnt[mouse position][cat position][0/1 = mouse/cat to move]
	// is the number of possibly non-losing moves for current player
	// (if zero, means the state has been solved)
	adj_cnt := make([][][]int, N)
	for i := range adj_cnt {
		adj_cnt[i] = make([][]int, N)
		for j := range adj_cnt[i] {
			adj_cnt[i][j] = []int{len(graph[i]), len(graph[j])}
		}
	}

	queue := make([][]int, 0)
	// {{mouse pos, cat pos}, {0/1 = mouse/cat, 0/1 = current/previous player wins}}
	for i := 1; i < N; i++ {
		queue = append(queue, []int{i, i, 0, 1})
		queue = append(queue, []int{i, i, 1, 0})
		queue = append(queue, []int{0, i, 1, 1}) // if mouse reaches 0, it's cat's turn to move and it loses
		queue = append(queue, []int{i, 0, 0, 0}) // if cat reaches 0 (invalid move), it's mouse's turn to move and it wins

		adj_cnt[i][0] = []int{0, 0}
		adj_cnt[0][i] = []int{0, 0}
		adj_cnt[i][i] = []int{0, 0}
	}

	for len(queue) > 0 {
		idx := len(queue)
		for i := 0; i < idx; i++ {
			cur_player, prev_win := queue[i][2], queue[i][3]
			preturn := 1 - cur_player
			lpp := queue[i][preturn]
			parent := []int{queue[i][0], queue[i][1], queue[i][2] ^ 1, queue[i][3] ^ 1}

			for _, v := range graph[lpp] {
				parent[preturn] = v
				var entries *int = &adj_cnt[parent[0]][parent[1]][preturn]
				if *entries > 0 {
					*entries--
					if prev_win == 1 || *entries == 0 {
						*entries = 0
						queue = append(queue, parent)
						if cur_player == 1 && parent[0] == 1 && parent[1] == 2 {
							if prev_win == 1 {
								return 1
							}
							return 2
						}
					}
				}
			}
		}

		queue = queue[idx:]
	}

	return 0
}

func Test_913_CatAndMouse() {

	catMouseGame([][]int{[]int{2, 5}, []int{3}, []int{0, 4, 5}, []int{1, 4, 5}, []int{2, 3}, []int{0, 2, 3}})

	catMouseGame([][]int{[]int{1, 3}, []int{0}, []int{3}, []int{0, 2}})

	catMouseGame([][]int{[]int{2, 3}, []int{3, 4}, []int{0, 4}, []int{0, 1}, []int{1, 2}})

}
