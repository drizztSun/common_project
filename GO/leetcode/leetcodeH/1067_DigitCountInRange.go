package leetcodeH

/*
1067. Digit Count in Range

Given an integer d between 0 and 9, and two positive integers low and high as lower and upper bounds, respectively.
Return the number of times that d occurs as a digit in all integers between low and high, including the bounds low and high.


Example 1:

Input: d = 1, low = 1, high = 13
Output: 6
Explanation:
The digit d=1 occurs 6 times in 1,10,11,12,13. Note that the digit d=1 occurs twice in the number 11.
Example 2:

Input: d = 3, low = 100, high = 250
Output: 35
Explanation:
The digit d=3 occurs 35 times in 103,113,123,130,131,...,238,239,243.


Note:

0 <= d <= 9
1 <= low <= high <= 2×10^8
*/

func digitsCount_math_cal(d int, num int) int {

	/*
	   Rather than counting the occurence of d from each number, we count the the occurent of d on each digit from 1 to the number.

	   Think about the form of the number abcTxyz and the current digit T, and we want to count the occurence of d on that position.
	   1. If T>d, then from 000 to abc, each corresponds to 1000 counts
	   2. If T==d, then from 000 to abc, each corresponds to 1000 counts except the last one, and xyz correponds to a count of abcT000 to abcTxyz, which is xyz+1 counts.
	   3. If T<d, then only from 000 to abc(excluded), each corresponds to 1000 counts.

	   Pay attention to d=0, for that case, we cannot start from 000, so we need to subtract them
	*/
	step, res, n := 1, 0, 0
	zero, r := 0, 0
	if d == 0 {
		zero = 1
	}

	for num > 0 {

		num, r = num/10, num%10

		if r > d {
			res += (1 + num - zero) * step
		} else if r == d {
			res += (num-zero)*step + n + 1
		} else {
			res += (num - zero) * step
		}

		n += r * step
		step *= 10
	}

	return res
}

func digitsCount_math(d int, low int, high int) int {

	return digitsCount_math_cal(d, high) - digitsCount_math_cal(d, low-1)
}

func Test_1067_digital_count_in_range() {

	digitsCount_math(1, 1, 13)
}
