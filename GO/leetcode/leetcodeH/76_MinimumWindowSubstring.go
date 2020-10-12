package leetcodeH

/*
76. Minimum Window Substring

Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

Example:

Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"
Note:

If there is no such window in S that covers all characters in T, return the empty string "".
If there is such window, you are guaranteed that there will always be only one unique minimum window in S.
*/

func minWindow_array(s string, t string) string {

	cnt := make(map[byte]int, 0)

	for i := 0; i < len(t); i++ {
		cnt[t[i]]++
	}

	total := len(t)
	j, I, J := 0, -1, -1

	for i := 0; i < len(s); i++ {

		if cnt[s[i]] > 0 {
			total--
		}
		cnt[s[i]]--

		if total == 0 {
			for j < i && cnt[s[j]] < 0 {
				cnt[s[j]]++
				j++
			}

			if I == -1 || i-j < I-J {
				I, J = i, j
			}
		}
	}

	if total > 0 {
		return ""
	}

	return s[J : I+1]
}
