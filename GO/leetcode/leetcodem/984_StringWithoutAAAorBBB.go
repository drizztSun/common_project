package leetcodem

/*

984. String Without AAA or BBB

Given two integers A and B, return any string S such that:

S has length A + B and contains exactly A 'a' letters, and exactly B 'b' letters;
The substring 'aaa' does not occur in S;
The substring 'bbb' does not occur in S.


Example 1:

Input: A = 1, B = 2
Output: "abb"
Explanation: "abb", "bab" and "bba" are all correct answers.
Example 2:

Input: A = 4, B = 1
Output: "aabaa"

*/

func strWithout3a3b(A int, B int) string {

	var ans string

	for A > 0 && B > 0 {

		if A > B {
			ans += "aab"
			A -= 2
			B -= 1
		} else if A < B {
			ans += "bba"
			A -= 1
			B -= 2
		} else {
			for A > 0 {
				ans += "ab"
				A--
			}
			A = 0
			B = 0
		}

	}

	if A > 0 {
		if A > 1 {
			ans += "aa"
		} else {
			ans += "a"
		}

	} else if B > 0 {
		if B > 1 {
			ans += "bb"
		} else {
			ans += "b"
		}

	}

	return ans
}

func Test_984_StringWithoutAAAorBBB() {

	strWithout3a3b(1, 2)

	strWithout3a3b(4, 1)
}
