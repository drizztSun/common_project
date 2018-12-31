package leetcodeE

/*
Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators.
The valid operators are +, - and *.

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

func compute(input string) []int {

	res := make([]int, 0, 0)
	for i, c := range input {
		if c == '+' || c == '-' || c == '*' {
			left := compute(input[:i])
			right := compute(input[i+1:])

			for _, num1 := range left {
				for _, num2 := range right {
					switch c {
					case '+':
						res = append(res, num1+num2)
					case '-':
						res = append(res, num1-num2)
					case '*':
						res = append(res, num1*num2)
					}
				}
			}
		}
	}

	if len(res) == 0 {
		a, _ := strconv.Atoi(input)
		res = append(res, a)
	}

	return res
}

func diffWaysToCompute(input string) []int {

	return compute(input)
}
