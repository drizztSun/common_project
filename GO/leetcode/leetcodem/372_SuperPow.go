package leetcodem

/*
372. Super Pow

Your task is to calculate ab mod 1337 where a is a positive integer and b is an extremely large positive integer given in the form of an array.


Example 1:

Input: a = 2, b = [3]
Output: 8
Example 2:

Input: a = 2, b = [1,0]
Output: 1024
Example 3:

Input: a = 1, b = [4,3,3,8,5,2]
Output: 1
Example 4:

Input: a = 2147483647, b = [2,0,0]
Output: 1198
*/

func pow(a, b int) int {

	if b == 0 {
		return 1
	}

	if b == 1 {
		return a
	}

	if b%2 == 1 {
		x := pow(a, (b-1)/2)
		return (a * (x * x) % 1337) % 1337
	} else {
		x := pow(a, b/2)
		return (x * x) % 1337
	}
}

func superPow(a int, b []int) int {

	result := 1
	for _, c := range b {
		result = pow(result, 10) * pow(a%1337, c) % 1337
	}

	return result

}
