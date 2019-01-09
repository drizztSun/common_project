


/*

# 552. Student Attendance Record II

# Given a positive integer n, return the number of all possible attendance records with length n,
# which will be regarded as rewardable.
# The answer may be very large, return it after mod 109 + 7.

# A student attendance record is a string that only contains the following three characters:

# 'A' : Absent.
# 'L' : Late.
# 'P' : Present.
# A record is regarded as rewardable if it doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).

# Example 1:
# Input: n = 2
# Output: 8

# Explanation:
# There are 8 records with length 2 will be regarded as rewardable:
# "PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
# Only "AA" won't be regarded as rewardable owing to more than one absent times.


*/

#include <vector>
#include <algorithm>


using namespace std;

class StudentAttendanceRecorder {


public:

	int checkRecord(int n) {

		int N = 1, NL = 1, NLL = 0;
		int AN = 1, ANL = 0, ANLL = 0;
		int MOD = pow(10, 9) + 7;


		while (n > 1) {

			int ON = N, ONL = NL, ONLL = NLL, OAN = AN, OANL = ANL, OANLL = ANLL;

			N = (ON + ONL + ONLL) % MOD;
			NL = ON;
			NLL = ONL;

			AN = (ON + ONL + ONLL + OAN + OANL + OANLL) % MOD;
			ANL = OAN;
			ANLL = OANL;

			n--;
		}

		return (N + NL + NLL + AN + ANL + ANLL) % MOD;
	}

};


class Solution {

public:
	/*
		Let f[i][j][k] denote the # of valid sequences of length i where:

		There can be at most j A's in the entire sequence.
		There can be at most k trailing L's.
		We give the recurrence in the following code, which should be self - explanatory, and the final answer is f[n][1][2].



	*/


	int checkRecord(int n) {

		int MOD = 1e9 + 7;
		vector<vector<vector<int>>> fn(n + 1, vector<vector<int>>(2, vector<int>(3, 1)));

		for (auto i = 1; i < fn.size(); i++) {

			for (auto j = 0; j < 2; j++) {

				for (auto k = 0; k < 3; k++) {

					int val = fn[i- 1][j][2]; // ......P
 
					if (j > 0)
						val += (val + fn[i - 1][j - 1][2]) % MOD;  // .......A

					if (k > 0)
						val += (val + fn[i - 1][j][k - 1]) % MOD;  // .....L

					fn[i][j][k] = val;
				}

			}
		}

		return fn[n][1][2];
	}

	/*
	
		The runtime of this solution is clearly O(n), using linear space (which can be easily optimized to O(1) though). Now, let's see how to further improve the runtime.

		In fact, if we treat f[i][][] and f[i-1][][] as two vectors, we can represent the recurrence of f[i][j][k] as follows:

		f[i][0][0]   | 0 0 1 0 0 0 |   f[i-1][0][0]
		f[i][0][1]   | 1 0 1 0 0 0 |   f[i-1][0][1]
		f[i][0][2] = | 0 1 1 0 0 0 | * f[i-1][0][2]
		f[i][1][0]   | 0 0 1 0 0 1 |   f[i-1][1][0]
		f[i][1][1]   | 0 0 1 1 0 1 |   f[i-1][1][1]
		f[i][1][2]   | 0 0 1 0 1 1 |   f[i-1][1][2]
		Let A be the matrix above, then f[n][][] = A^n * f[0][][], where f[0][][] = [1 1 1 1 1 1]. The point of this approach is that we can compute A^n using exponentiating by squaring (thanks to @StefanPochmann for the name correction), which will take O(6^3 * log n) = O(log n) time. Therefore, the runtime improves to O(log n), which suffices to handle the case for much larger n, say 10^18.
		Update: The final answer is f[n][1][2], which involves multiplying the last row of A^n and the column vector [1 1 1 1 1 1]. Interestingly, it is also equal to A^(n+1)[5][2] as the third column of A is just that vector. Credit to @StefanPochmann.

	*/

	


};



void Test_552_StudentAttendanceRecordII() {

	int res = StudentAttendanceRecorder().checkRecord(2);

	int res2 = StudentAttendanceRecorder().checkRecord(3);

	int res1 = StudentAttendanceRecorder().checkRecord(4);
	
	return;
}