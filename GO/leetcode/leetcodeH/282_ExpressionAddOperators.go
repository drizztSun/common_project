package leetcodeH

import "strconv"

/*
282. Expression Add Operators

Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.

Example 1:

Input: num = "123", target = 6
Output: ["1+2+3", "1*2*3"]
Example 2:

Input: num = "232", target = 8
Output: ["2*3+2", "2+3*2"]
Example 3:

Input: num = "105", target = 5
Output: ["1*0+5","10-5"]
Example 4:

Input: num = "00", target = 0
Output: ["0+0", "0-0", "0*0"]
Example 5:

Input: num = "3456237490", target = 9191
Output: []


Constraints:

0 <= num.length <= 10
num only contain digits.
*/

func search_parts_result(num string, i int, last int, tmp int, target int, path string, res *[]string) {

	max := func(a, b int) int {
		if a < b {
			return b
		}
		return a
	}

	abs := func(a int) int {
		if a < 0 {
			return -a
		}
		return a
	}

	if i == len(num) {
		if tmp == target {
			*res = append(*res, path)
		}
		return
	}

	rest, _ := strconv.Atoi(num[i:])
	if max(1, abs(last))*rest < abs(target-tmp) {
		return
	}

	cur := 0
	for j := i; j < len(num); j++ {

		cur = cur*10 + int(num[j]-'0')

		if j > i && num[i] == '0' {
			break
		}

		if len(path) == 0 {
			search_parts_result(num, j+1, cur, cur, target, num[i:j+1], res)
		} else {

			search_parts_result(num, j+1, cur, tmp+cur, target, path+string('+')+num[i:j+1], res)

			search_parts_result(num, j+1, -cur, tmp-cur, target, path+string('-')+num[i:j+1], res)

			search_parts_result(num, j+1, last*cur, tmp-last+last*cur, target, path+string('*')+num[i:j+1], res)
		}
	}
}

func addOperators(num string, target int) []string {
	res := make([]string, 0)
	search_parts_result(num, 0, 0, 0, target, string(""), &res)
	return res
}
