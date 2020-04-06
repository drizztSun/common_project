package leetcodem

/*
1017. Convert to Base -2

Given a number N, return a string consisting of "0"s and "1"s that represents its value in base -2 (negative two).

The returned string must have no leading zeroes, unless the string is "0".

 

Example 1:

Input: 2
Output: "110"
Explantion: (-2) ^ 2 + (-2) ^ 1 = 2
Example 2:

Input: 3
Output: "111"
Explantion: (-2) ^ 2 + (-2) ^ 1 + (-2) ^ 0 = 3
Example 3:

Input: 4
Output: "100"
Explantion: (-2) ^ 2 = 4


*/

func baseNeg2(N int) string {

    if N == 0 {
        return "0"
    }
    
    ans := ""

	for N != 0 {

		if N % (-2) == 0 {
			ans = "0" + ans
		} else {
            N -= 1
			ans = "1" + ans
		}

		N /= -2
	}

	return ans
}

func Test_1017_ConvertToBase2() {

	baseNeg2(2)

	baseNeg2(3)

	baseNeg2(4)
}