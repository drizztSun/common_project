package leetcodem

/*

1048. Longest String Chain

Given a list of words, each word consists of English lowercase letters.

Let's say word1 is a predecessor of word2 if and only if we can add exactly one letter anywhere in word1 to make it equal to word2.  For example, "abc" is a predecessor of "abac".

A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1, where word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and so on.

Return the longest possible length of a word chain with words chosen from the given list of words.



Example 1:

Input: ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: one of the longest word chain is "a","ba","bda","bdca".

*/

func longestStrChain_search(wordlength map[int]map[string]struct{}, w string, wordres map[string]int) int {

	if v, ok := wordres[w]; ok {
		return v
	}

	if len(w) == 1 {
		if _, ok := wordlength[1][w]; ok {
			return 1
		}
		return 0
	}

	L := len(w)
	ans := 1
	for i := range w {
		parent := w[:i] + w[i+1:]
		if _, ok := wordlength[L-1][parent]; ok {
			w := longestStrChain_search(wordlength, parent, wordres) + 1
			if w > ans {
				ans = w
			}
		}
	}

	wordres[w] = ans
	return ans
}

func longestStrChain(words []string) int {

	wordlength := make(map[int]map[string]struct{})

	for _, c := range words {

		if _, ok := wordlength[len(c)]; !ok {
			wordlength[len(c)] = make(map[string]struct{})
		}

		wordlength[len(c)][c] = struct{}{}
	}

	ans := 0
	wordres := make(map[string]int)
	for i := range words {
		w := longestStrChain_search(wordlength, words[i], wordres)

		if w > ans {
			ans = w
		}
	}
	return ans
}

func Test_1048_LongestStringChain() {

	longestStrChain([]string{"a", "b", "ba", "bca", "bda", "bdca"})
}
