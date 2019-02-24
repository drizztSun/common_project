package leetcodeE

import (
	"unicode"
)

/*
784. Letter Case Permutation

Given a string S, we can transform every letter individually to be lowercase or uppercase to create another string.
Return a list of all possible strings we could create.

Examples:
Input: S = "a1b2"
Output: ["a1b2", "a1B2", "A1b2", "A1B2"]

Input: S = "3z4"
Output: ["3z4", "3Z4"]

Input: S = "12345"
Output: ["12345"]
Note:

S will be a string with length between 1 and 12.
S will consist only of letters or digits.


*/

func buildString(S string, i int) []string {

	if i == len(S) {
		return []string{""}
	}

	res := buildString(S, i+1)
	for j, c := range res {
		s := rune(S[i])
		res[j] = string(s) + res[j]
		if unicode.IsLetter(s) {
			var l rune
			if unicode.IsLower(s) {
				l = unicode.ToUpper(s)
			} else {
				l = unicode.ToLower(s)
			}

			res = append(res, string(l)+c)
		}
	}

	return res
}

func letterCasePermutation(S string) []string {

	return buildString(S, 0)
}
