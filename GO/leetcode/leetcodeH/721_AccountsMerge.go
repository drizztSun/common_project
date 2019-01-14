package leetcodeH

type DSU []int

func (I DSU) Init(length int) {
	I = make([]int, length)
	for i := range I {
		I[i] = i
	}
}

func (I DSU) find(a int) int {
	for a != I[a] {
		I[a] = I[I[a]]
		a = I[a]
	}
	return a
}

func (I DSU) union(a, b int) {
	I[I.find(a)] = I.find(b)
}

func (I DSU) reunion() {
	for i := range I {
		I.find(i)
	}
}

func accountsMerge(accounts [][]string) [][]string {

	uf := DSU{}
	uf.Init(len(accounts))

	email2idex := make(map[string][]int)
	for i := range accounts {
		for j := 1; j < len(accounts[j]); j++ {
			email2idex[accounts[i][j]] = append(email2idex[accounts[i][j]], i)
		}
	}

	for _, v := range email2idex {
		if len(v) > 1 {
			for i := 1; i < len(v); i++ {
				uf.union(v[0], v[i])
			}
		}
	}

	uf.reunion()

	res := make(map[int]map[string]int)
	for i := range uf {
		for j := 1; j < len(accounts[uf[i]]); j++ {
			if _, ok := res[i]; !ok {
				res[i] = make(map[string]int)
			}
			if _, ok := res[i][accounts[uf[i]][0]]; !ok {
				res[i][accounts[uf[i]][0]] = 0
			}
		}
	}

	ans := make([][]string, len(res))
	for k, v := range res {
		var tmp []string
		tmp = append(tmp, accounts[k][0])
		for k, _ := range v {
			tmp = append(tmp, k)
		}
		ans = append(ans, tmp)
	}

	return ans
}

/*
func main() {
	input := [][]string {
		{"John","johnsmith@mail.com","john_newyork@mail.com"},
		{"John","johnsmith@mail.com","john00@mail.com"},
		{"Mary","mary@mail.com"},
		{"John","johnnybravo@mail.com"} }

	res := accountsMerge(input)
}*/
