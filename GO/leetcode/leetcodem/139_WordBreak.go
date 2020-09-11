package leetcodem

/*
139. Word Break

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

Note:

The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.
Example 1:

Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
Example 2:

Input: s = "applepenapple", wordDict = ["apple", "pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
             Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
Output: false

*/

func wordBreakSearch(s string, i int, wordDict []string, buff map[int][]string) []string {

	if c, ok := buff[i]; ok {
		return c
	}

	if i == len(s) {
		return []string{""}
	}

	res := make([]string, 0)
	for _, w := range wordDict {

		if len(s) >= i+len(w) && w == s[i:i+len(w)] {

			left := wordBreakSearch(s, i+len(w), wordDict, buff)

			for _, c := range left {
				if len(c) > 0 {
					res = append(res, w+string(' ')+c)
				} else {
					res = append(res, w)
				}
			}
		}
	}
	buff[i] = res
	return res
}

func wordBreak(s string, wordDict []string) []string {
	buff := make(map[int][]string)

	wordBreakSearch(s, 0, wordDict, buff)

	return buff[0]
}
