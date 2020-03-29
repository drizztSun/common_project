package leetcodem

/*
1015. Smallest Integer Divisible by K

Given a positive integer K, you need find the smallest positive integer N such that N is divisible by K, and N only contains the digit 1.

Return the length of N.  If there is no such N, return -1.



Example 1:

Input: 1
Output: 1
Explanation: The smallest answer is N = 1, which has length 1.
Example 2:

Input: 2
Output: -1
Explanation: There is no such positive integer N divisible by 2.
Example 3:

Input: 3
Output: 3
Explanation: The smallest answer is N = 111, which has length 3.

*/

func smallestRepunitDivByK(K int) int {

	if K%2 == 0 || K%5 == 0 {
		// if it could devide by 2, 5. it means '1' is not the end of number
		return -1
	}

	l, n := 1, 1

	for n%K != 0 {

		n = (10*n + 1) % K
		l++
	}

	return l

}

func Test_1015_SmallestIntegerDivisibleByK() {

	smallestRepunitDivByK(1)

	smallestRepunitDivByK(2)

	smallestRepunitDivByK(3)
}
