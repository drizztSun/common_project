package leetcodeE

import "strings"

func reverseOnlyLetters(S string) string {

	s := strings.Split(S, "")
	l, h := 0, len(s)-1

	IsNotLetter := func(a string) bool {
		if (a[0] >= 'a' && a[0] <= 'z') || (a[0] >= 'A' && a[0] <= 'Z') {
			return false
		}
		return true
	}

	for l < h {

		if IsNotLetter(s[l]) {
			l++
		} else if IsNotLetter(s[h]) {
			h--
		} else {
			s[l], s[h] = s[h], s[l]
			l++
			h--
		}
	}

	return strings.Join(s, "")
}

func Test_917_ReverseOnlyLetters() {

	reverseOnlyLetters("ab-cd")
}
