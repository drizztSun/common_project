package leetcodem

/*

1023. Camelcase Matching


A query word matches a given pattern if we can insert lowercase letters to the pattern word so that it equals the query.
(We may insert each character at any position, and may insert 0 characters.)

Given a list of queries, and a pattern, return an answer list of booleans, where answer[i] is true if and only if queries[i] matches the pattern.

Example 1:

Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
Output: [true,false,true,true,false]
Explanation: 
"FooBar" can be generated like this "F" + "oo" + "B" + "ar".
"FootBall" can be generated like this "F" + "oot" + "B" + "all".
"FrameBuffer" can be generated like this "F" + "rame" + "B" + "uffer".
Example 2:

Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBa"
Output: [true,false,true,false,false]
Explanation: 
"FooBar" can be generated like this "Fo" + "o" + "Ba" + "r".
"FootBall" can be generated like this "Fo" + "ot" + "Ba" + "ll".
Example 3:

Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBaT"
Output: [false,true,false,false,false]
Explanation: 
"FooBarTest" can be generated like this "Fo" + "o" + "Ba" + "r" + "T" + "est".


*/

func camelMatch(queries []string, pattern string) []bool {

	search := func(query, pa string) bool {
		j := 0
		for i := 0; i < len(query); i++ {
			if j < len(pa) && pa[j] == query[i] {
				j++
			} else if query[i] <= byte('Z') {
				return false
			}
		}
		return j == len(pa)
	}

	ans := make([]bool, 0)
	for _, v := range queries {
		ans = append(ans, search(v, pattern))
	}
	return ans
}

func Test_1023_CamelcaseMatching() {

	camelMatch([]string{"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"}, "FB")

	camelMatch([]string{"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"}, "FoBa")

	camelMatch([]string{"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"}, "FoBaT")
}