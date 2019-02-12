package leetcodeE

/*
# 748. Shortest Completing Word

# Find the minimum length word from a given dictionary words, which has all the letters from the string licensePlate.
# Such a word is said to complete the given string licensePlate

# Here, for letters we ignore case. For example, "P" on the licensePlate still matches "p" on the word.

# It is guaranteed an answer exists. If there are multiple answers, return the one that occurs first in the array.

# The license plate might have the same letter occurring multiple times.
# For example, given a licensePlate of "PP", the word "pair" does not complete the licensePlate, but the word "supper" does.

# Example 1:
# Input: licensePlate = "1s3 PSt", words = ["step", "steps", "stripe", "stepple"]
# Output: "steps"
# Explanation: The smallest length word that contains the letters "S", "P", "S", and "T".
# Note that the answer is not "step", because the letter "s" must occur in the word twice.
# Also note that we ignored case for the purposes of comparing whether a letter exists in the word.

# Example 2:
# Input: licensePlate = "1s3 456", words = ["looks", "pest", "stew", "show"]
# Output: "pest"
# Explanation: There are 3 smallest length words that contains the letters "s".
# We return the one that occurred first.

*/

import (
	"strings"
	"fmt"
)

func ShortestCompletingWord(licensePlate string, words []string) string {

	plate := make(map[rune]int)
	for _, v := range strings.ToLower(licensePlate) {
		if v < 'a' || v > 'z' {
			continue
		}

		if _, ok := plate[v]; !ok {
			plate[v] = 0
		}

		plate[v]++
	}

	ans := ""

	for _, w := range words {

		data := make(map[rune]int)
		for v := range plate {
			data[v] = plate[v]
		}

		for _, c := range w {
			if _, ok := data[c]; ok {
				data[c]--
				if data[c] == 0 {
					delete(data, c)
				}
			}
		}

		if len(data) == 0 && (len(ans) == 0 || len(ans) > len(w)) {
			ans = w
		}
	}

	return ans
}


func Test_748() {

	fmt.Println(ShortestCompletingWord(
		"1s3 PSt",
		[]string {"step","steps","stripe","stepple"}))
}