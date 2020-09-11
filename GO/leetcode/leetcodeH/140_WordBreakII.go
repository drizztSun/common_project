package leetcodeH

/*
140. Word Break II

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences.

Note:

The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.
Example 1:

Input:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
Output:
[
  "cats and dog",
  "cat sand dog"
]
Example 2:

Input:
s = "pineapplepenapple"
wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
Output:
[
  "pine apple pen apple",
  "pineapple pen apple",
  "pine applepen apple"
]
Explanation: Note that you are allowed to reuse a dictionary word.
Example 3:

Input:
s = "catsandog"
wordDict = ["cats", "dog", "sand", "and", "cat"]
Output:
[]
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
				res = append(res, w+string(' ')+c)
			}
		}
	}
	buff[i] = res
	return res
}

func WordBreakII_dfs(s string, wordDict []string) []string {

	buff := make(map[int][]string)

	wordBreakSearch(s, 0, wordDict, buff)

	return buff[0]
}
