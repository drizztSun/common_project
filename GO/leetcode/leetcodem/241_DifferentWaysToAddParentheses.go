package leetcodem

/*
241. Different Ways to Add Parentheses

Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.

Example 1:

Input: "2-1-1"
Output: [0, 2]
Explanation:
((2-1)-1) = 0
(2-(1-1)) = 2
Example 2:

Input: "2*3-4*5"
Output: [-34, -14, -10, -10, 10]
Explanation:
(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10
*/

import (
	"strconv"
)

func cal_formula(input string, seen map[string][]int) []int {

	if c, ok := seen[input]; ok {
		return c
	}

	res := make([]int, 0)

	for i, c := range input {

		if c == '-' || c == '+' || c == '*' {

			res1, res2 := cal_formula(input[:i], seen), cal_formula(input[i+1:], seen)

			for _, c1 := range res1 {
				for _, c2 := range res2 {
					r := 0
					if input[i] == '-' {
						r = c1 - c2
					} else if input[i] == '+' {
						r = c1 + c2
					} else if input[i] == '*' {
						r = c1 * c2
					}

					res = append(res, r)
				}
			}
		}

	}

	if len(res) == 0 {
		if c, err := strconv.ParseInt(input, 10, 32); err == nil {
			res = append(res, int(c))
		}
	}

	seen[input] = res
	return res
}

func diffWaysToCompute_divide_and_conquer(input string) []int {

	seen := make(map[string][]int)

	return cal_formula(input, seen)
}
