/*

# 805. Split Array With Same Average

# In a given integer array A, we must move every element of A to either list B or list C. (B and C initially start empty.)

# Return true if and only if after such a move, it is possible that the average value of
# B is equal to the average value of C, and B and C are both non-empty.

# Example :

# Input:
# [1,2,3,4,5,6,7,8]

# Output: true
# Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both of them have the average of 4.5.

# Note:

# The length of A will be in the range [1, 30].
# A[i] will be in the range of [0, 10000].

*/

#include <algorithm>
#include <vector>
using namespace std;


class SplitArraySameAverage {

public:
	
	bool doit(vector<int>& A) {
		
		int N = A.size();
		int S = 0;
		for (auto c : A)
			S += c;

		vector<int> p(S + 1, 1);

		for (auto c : A) {

			for (auto i = S - c; i >= 0; i--) {
				p[i + c] |= p[i] << 1;
			}
		}

		for (auto i = 0; i < N; i++)
			// i * S % N == 0, to make sure that part value of the array is integer, S / N = s / i
			// p[i * S / N], to make sure that s = S * i / N really existed,
			// (1 << i) to get the ith bit, so i's number made the subsequence
			if (i * S % N == 0 && p[i * S / N] & (1 << i))
				return true;

		return false;
	}

	bool doit1(vector<int>& A) {
		return true;
	}

};

void Test_805_SplitArrayWithSameAverage() {

	bool res1 = SplitArraySameAverage().doit(vector<int>{1, 2, 3, 4, 5, 6, 7, 8});

	bool res2 = SplitArraySameAverage().doit(vector<int>{17, 5, 5, 1, 14, 10, 13, 1, 6});

	bool res4 = SplitArraySameAverage().doit(vector<int>{904, 8738, 6439, 1889, 138, 5771, 8899, 5790, 662, 8402, 3074, 1844, 5926, 8720, 7159, 6793, 7402, 9466, 1282, 1748, 434, 842, 22});

	return;
}
