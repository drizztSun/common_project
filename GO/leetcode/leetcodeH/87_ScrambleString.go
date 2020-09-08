package leetcodeH

/*
87. Scramble String

We can scramble a string s to get a string t using the following algorithm:

If the length of the string is 1, stop.
If the length of the string is > 1, do the following:
Split the string into 2 non-empty substrings at a random index, i.e. if the string is s, divide it to x and y where s = x + y.
Randomly, decide to swap the two substrings or to keep them in the same order. i.e. after this step, s may become s = x + y or s = y + x.
Apply step 1 recursively on each of the two substrings x and y.
Given two strings s1 and s2 of the same length, return true if s2 is a scrambled string of s1, otherwise, return false.



Example 1:

Input: s1 = "great", s2 = "rgeat"
Output: true
Explanation: One possible scenario applied on s1 is:
"great" --> "gr/eat" // divide at random index.
"gr/eat" --> "gr/eat" // random decision is not to swap the two substrings and keep them in order.
"gr/eat" --> "g/r / e/at" // apply the same algorith recursively on both substrings. divide at ranom index each of them.
"g/r / e/at" --> "r/g / e/at" // random decision was to swap the first substing and to keep the second substring in the same order.
"r/g / e/at" --> "r/g / e/ a/t" // again apply the algorithm recursively, divide "at" to "a/t".
"r/g / e/ a/t" --> "r/g / e/ a/t" // random decision is to keep both substings in the same order.
The algorithm stops now and the result string is "rgeat" which is s2.
As there is one possible scenario that led s1 to be scrambled to s2, we return true.

Example 2:

Input: s1 = "abcde", s2 = "caebd"
Output: false

Example 3:

Input: s1 = "a", s2 = "a"
Output: true


Constraints:

s1.length == s2.length
1 <= s1.length <= 30
s1 and s2 consist of lower-case English letters.
*/

import (
	"reflect"
)

func search_isscranble(x string, y string) bool {

	if len(x) != len(y) {
		return false
	}

	if x == y {
		return true
	}

	if len(x) == 1 {
		return x == y
	}

	d := make(map[byte]int)
	dleft := make(map[byte]int)
	dright := make(map[byte]int)

	for i := 0; i < len(x)-1; i++ {

		d[x[i]]++
		dleft[y[i]]++
		dright[y[len(y)-1-i]]++

		if reflect.DeepEqual(d, dleft) && search_isscranble(x[:i+1], y[:i+1]) && search_isscranble(x[i+1:], y[i+1:]) {
			return true
		}

		if reflect.DeepEqual(d, dright) && search_isscranble(x[:i+1], y[len(y)-i-1:]) && search_isscranble(x[i+1:], y[:len(y)-i-1]) {
			return true
		}
	}

	return false
}

func isScramble_dp_memo(s1 string, s2 string) bool {

	return search_isscranble(s1, s2)
}

func Test_87_ScrambleString() {

	isScramble_dp_memo("great", "rgeat")
}

/*

func isScramble(s1 string, s2 string) bool {
  if s1 == s2 {
    return true
  }

	size := len(s1)
  if size == 1 {
    return false
  }

  if size == 2 {
    return s1[0] == s2[1] && s1[1] == s2[0]
  }

  check := make(map[byte]int)
  for i := range s1 {
    check[s1[i]]++
    check[s2[i]]--
  }

  for _, v := range check {
    if v != 0 {
      return false
    }
  }

  // partisitioning
  for i := 1; i < size; i++ {
    if isScramble(s1[:i], s2[:i]) && isScramble(s1[i:], s2[i:]) {
      return true
    }

    if isScramble(s1[:i], s2[size-i:]) && isScramble(s1[i:], s2[:size-i]) {
      return true
    }
  }

  return false
}

func buildTree(s string) *node {
  size := len(s)

  if size == 1 {
    c := make([]int, 26)
    c[s[0] - 'a'] = 1

    return &node {
      c: c,
      left: nil,
      right: nil,
    }
  }

  m := size/2
  c := make([]int, 26)

  l := buildTree(s[:m])
  r := buildTree(s[m:])

  for i := range c {
    c[i] = l.c[i] + r.c[i]
  }

  return &node {
    c: c,
    left: l,
    right: r,
  }
}

func verifyTree(r1, r2 *node) bool {
  // both null, valid
  if r1 == nil && r2 == nil {
    return true
  }

  // only 1 root is non-null, invaild
  if (r1 == nil && r2 != nil) || (r1 != nil && r2 == nil) {
    return false
  }

  // both roots are non-null, check

  for i := range r1.c {
    if r1.c[i] != r2.c[i] {
      return false
    }
  }

  return (verifyTree(r1.left, r2.left) && verifyTree(r1.right, r2.right)) || (verifyTree(r1.right, r2.left) && verifyTree(r1.left, r2.right))

  // todo ... split and verify
}

type node struct {
  c []int
  left *node
  right *node
}

*/
