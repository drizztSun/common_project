package leetcodeH

import (
	"math"
)

/*

650. 2 Keys Keyboard

Initially on a notepad only one character 'A' is present. You can perform two operations on this notepad for each step:

Copy All: You can copy all the characters present on the notepad (partial copy is not allowed).
Paste: You can paste the characters which are copied last time.
Given a number n. You have to get exactly n 'A' on the notepad by performing the minimum number of steps permitted. Output the minimum number of steps to get n 'A'.

Example 1:
Input: 3
Output: 3
Explanation:
Intitally, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.

*/

func do(length int) int {

	if length == 1 {
		return 0
	} else {
		for i := 2; i < int(math.Sqrt(float64(length))+1); i++ {
			if length%i == 0 {
				return do(i) + do(length/i)
			}

		}
		return length
	}

}

func minSteps(n int) int {

	return do(n)
}
