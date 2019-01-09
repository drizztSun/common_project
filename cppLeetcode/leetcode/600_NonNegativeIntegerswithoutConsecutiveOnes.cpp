
/*
# 600. Non-negative Integers without Consecutive Ones
#    Given a positive integer n, find the number of non-negative integers less than or equal to n,
#    whose binary representations do NOT contain consecutive ones.
#
#    Example 1:
#    Input: 5
#    Output: 5
#    Explanation:
#
#    Here are the non-negative integers <= 5 with their corresponding binary representations:
#
#   0 : 0
#   1 : 1
#   2 : 10
#   3 : 11
#   4 : 100
#   5 : 101
#
# Among them, only integer 3 disobeys the rule (two consecutive ones) and the other 5 satisfy the rule.
#   Note: 1 <= n <= 109

*/

class BiggestIntergersWOConsecutiveOnes {

public:
	/*
	If we have n bits, the number of integers without consecutive ones f(n) = f(n - 1) + f (n - 2).
	f(n - 1) is for the case when first bit is zero, and
	f(n - 2) is when then the first bit is one and second bit is zero (as we cannot have consecutive ones):

	f(n) = “0” f(n - 1) + “10” f(n - 2).
	These are Fibonacci numbers, and we can have them in a static array for [0…31] bits.

	First, we find n, which is the position of the highest set bit in our number.

	Now, if the binary representation of our number starts with “11”, then all integers will be smaller than our number,
	and we can just return a Fibonacci number for n bits.

	For example, if n == 12 (binary 0b1100), highest bit at the position 4, next bit is set, so the result is 8 (fb[4]).
	If the binary representation of our number starts with “10”, then all integers with n - 1 bits will be smaller than our number.
	So, we will grab a Fibonacci number for n - 1 bits. That’s “0” + f(n - 1) case.
	Plus, we need to add “10…” case, so we remove the highest bit from our number and recursively call our function.

	For example, if n == 18 (binary 0b10010), the highest bit at the position 5, next bit is unset,
	so taking 8 (fb[4] for 0x01111) and adding 3 (fb[2] for 0x00010).
	*/

	int findInteger(int num) {
		// below are fibonacci number
		static int fb[31] = { 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946,
			17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578 };

		if (num < 3)
			return num;

		for (int bt = 29; bt >= 0; bt--) {
			if (num & 1 << bt)
				return num & (1 << (bt - 1)) ? fb[bt] : fb[bt - 1] + findInteger((num & ~(1 << bt)));
		} 
	}

};

void Test_600_WithOutConsecutveOnes() {

	int res = 0;

	res = BiggestIntergersWOConsecutiveOnes().findInteger(5);

	res = BiggestIntergersWOConsecutiveOnes().findInteger(5);

	res = BiggestIntergersWOConsecutiveOnes().findInteger(5);
}
