package leetcodem

/*
Given an array equations of strings that represent relationships between variables, each string equations[i] has length 4 and takes one of two different forms: "a==b" or "a!=b".  Here, a and b are lowercase letters (not necessarily different) that represent one-letter variable names.

Return true if and only if it is possible to assign integers to variable names so as to satisfy all the given equations.



Example 1:

Input: ["a==b","b!=a"]
Output: false
Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.  There is no way to assign the variables to satisfy both equations.
Example 2:

Input: ["b==a","a==b"]
Output: true
Explanation: We could assign a = 1 and b = 1 to satisfy both equations.
Example 3:

Input: ["a==b","b==c","a==c"]
Output: true
Example 4:

Input: ["a==b","b!=c","c==a"]
Output: false
Example 5:

Input: ["c==c","b==d","x!=z"]
Output: true


*/

func equationsPossible(equations []string) bool {

	graph := make(map[byte][]byte)

	for _, v := range equations {
		if v[1] == '=' {
			x := v[0] - 'a' + 1
			y := v[3] - 'a' + 1
			graph[x] = append(graph[x], y)
			graph[y] = append(graph[y], x)
		}
	}

	colors := make([]byte, 27)

	for i := 1; i < 27; i++ {
		if colors[i] == 0 {
			st := make([]byte, 0)
			st = append(st, byte(i))

			for len(st) > 0 {
				x := st[len(st)-1]
				st = st[:len(st)-1]
				colors[x] = byte(i)

				for _, v := range graph[x] {
					if colors[v] == 0 {
						st = append(st, v)
					}
				}
			}
		}
	}

	for _, v := range equations {
		if v[1] == '!' {
			x := v[0] - 'a' + 1
			y := v[3] - 'a' + 1

			if x == y {
				return false
			}

			if colors[x] != 0 && colors[x] == colors[y] {
				return false
			}
		}
	}

	return true
}

func Test_990_satifiability_of_equality_equation() {

	equationsPossible([]string{"a==b", "b!=a"})

	equationsPossible([]string{"b==a", "a==b"})

	equationsPossible([]string{"a==b", "b==c", "a==c"})

	equationsPossible([]string{"a==b", "b!=c", "c==a"})

	equationsPossible([]string{"c==c", "b==d", "x!=z"})
}
