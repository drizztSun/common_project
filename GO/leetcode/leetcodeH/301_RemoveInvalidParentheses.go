package leetcodeH

/*
301. Remove Invalid Parentheses

Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).

Example 1:

Input: "()())()"
Output: ["()()()", "(())()"]
Example 2:

Input: "(a)())()"
Output: ["(a)()()", "(a())()"]
Example 3:

Input: ")("
Output: [""]


*/

func search(s string, i int, left, right int, leftRem, rightRem int, express string, res map[string]bool) {

	if i == len(s) {
		if leftRem == 0 && rightRem == 0 {
			res[express] = true
		}
		return
	}

	if s[i] == '(' && leftRem > 0 {
		search(s, i+1, left, right, leftRem-1, rightRem, express, res)
	}

	if s[i] == ')' && rightRem > 0 {
		search(s, i+1, left, right, leftRem, rightRem-1, express, res)
	}

	express += string(s[i])

	if s[i] != '(' && s[i] != ')' {
		search(s, i+1, left, right, leftRem, rightRem, express, res)
	}

	if s[i] == '(' {
		search(s, i+1, left+1, right, leftRem, rightRem, express, res)
	}

	if s[i] == ')' && left > right {
		search(s, i+1, left, right+1, leftRem, rightRem, express, res)
	}
}

func removeInvalidParentheses(s string) []string {

	leftRem, rightRem := 0, 0

	for _, c := range s {

		if c == '(' {
			leftRem++
		} else if c == ')' {
			if leftRem == 0 {
				rightRem++
			} else {
				leftRem--
			}
		}
	}

	res := make(map[string]bool)

	search(s, 0, 0, 0, leftRem, rightRem, "", res)

	ans := make([]string, 0)
	for k := range res {
		ans = append(ans, k)
	}

	return ans
}
