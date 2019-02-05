package leetcodeE

/*
728. Self Dividing Numbers


A self-dividing number is a number that is divisible by every digit it contains.

For example, 128 is a self-dividing number because 128 % 1 == 0, 128 % 2 == 0, and 128 % 8 == 0.

Also, a self-dividing number is not allowed to contain the digit zero.

Given a lower and upper number bound, output a list of every possible self dividing number, including the bounds if possible.

Example 1:
Input:
left = 1, right = 22
Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22]
*/

func selfDividingNumbers(left int, right int) []int {

	var nums []int

	for i := left; i < right+1; i++ {
		div := i
		for div > 0 {
			c := div % 10
			if c == 0 || i%c != 0 {
				break
			}
			div /= 10
		}

		if div == 0 {
			nums = append(nums, i)
		}

	}

	return nums
}
