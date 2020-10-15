package leetcodeH

/*
472. Concatenated Words

Given a list of words (without duplicates), please write a program that returns all concatenated words in the given list of words.
A concatenated word is defined as a string that is comprised entirely of at least two shorter words in the given array.

Example:
Input: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]

Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]

Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats";
 "dogcatsdog" can be concatenated by "dog", "cats" and "dog";
"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
Note:
The number of elements of the given array will not exceed 10,000
The length sum of elements in the given array will not exceed 600,000.
All the input string will only include lower case letters.
The returned elements order does not matter.
*/

func searchConcatenatedWords(wordlist map[string]bool, s string, i, minLen, length int) bool {

	if c, ok := wordlist[s[i:]]; ok && c {
		return length > 1
	}

	for j := i + minLen; j <= len(s)-minLen; j++ {
		if c, ok := wordlist[s[i:j]]; ok && c && searchConcatenatedWords(wordlist, s, j, minLen, length+1) {
			return true
		}
	}

	return false
}

func findAllConcatenatedWordsInADict(words []string) []string {

	wordlist := make(map[string]bool, 0)
	minLen := 1000000007
	for _, w := range words {
		wordlist[w] = true

		if minLen > len(w) {
			minLen = len(w)
		}
	}

	res := make([]string, 0)
	for _, w := range words {
		if len(w) >= 2*minLen {
			wordlist[w] = false
			if search(wordlist, w, 0, minLen, 0) {
				res = append(res, w)
			}
			wordlist[w] = true
		}
	}

	return res
}

func findAllConcatenatedWordsInADict_dp(words []string) []string {

	dict := make(map[string]bool, 0)
	for _, w := range words {
		dict[w] = true
	}

	res := make([]string, 0)

	for _, w := range words {

		dp := make([]int, len(w)+1)
		dp[0] = 1

		for i := 0; i < len(w); i++ {
			if dp[i] == 0 {
				continue
			}

			for j := i + 1; j <= len(w); j++ {

				if j-i < len(w) {
					if _, ok := dict[w[i:j]]; ok {
						dp[j] = 1
					}
				}
			}

			if dp[len(w)] == 1 {
				res = append(res, w)
				break
			}
		}
	}

	return res
}
