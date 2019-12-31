

/*

# 629. K Inverse Pairs Array

# Given two integers n and k, find how many different arrays consist of numbers from 1 to n
# such that there are exactly k inverse pairs.

# We define an inverse pair as following: For ith and jth element in the array,
# if i < j and a[i] > a[j] then it's an inverse pair; Otherwise, it's not.

# Since the answer may be very large, the answer should be modulo 109 + 7.

# Example 1:
# Input: n = 3, k = 0
# Output: 1
# Explanation:
# Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pair.

# Example 2:
# Input: n = 3, k = 1
# Output: 2
# Explanation:
# The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.

# Note:
# The integer n is in the range [1, 1000] and k is in the range [0, 1000].

*/

#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class KthInversePairsArray {

	const int mod = pow(10, 9) + 7;

public:

	// refer same python file
	int doit(int n, int k) {

		long long MOD = static_cast<long long>(pow(10, 9) + 7);
		vector<int> dp(k + 2, 1);
		dp[0] = 0;

		for (auto x = 2; x < n+1; x++) {
			vector<int> tmp(1, 0);

			for (auto y = 0; y < k + 1; y++) {

				int v = dp[y + 1];
				v -= y >= x ? dp[y - x + 1] : 0;

				tmp.push_back((tmp.back() + v) % MOD);
			}

			dp = tmp;
		}

		return (dp[k + 1] - dp[k]) % MOD;
	}

	/*
	For a better understanding, I would use O(n * k ) space instead of O(k) space. It’s easy to write O(k) space version when you understand this DP process.
		As @awice said in his Post

		For example, if we have some permutation of 1…4

		5 x x x x creates 4 new inverse pairs
		x 5 x x x creates 3 new inverse pairs
		…
		x x x x 5 creates 0 new inverse pairs
		O(n * k ^ 2) Solution
		We can use this formula to solve this problem

		dp[i][j] //represent the number of permutations of (1...n) with k inverse pairs.
		dp[i][j] = dp[i-1][j] + dp[i-1][j-1] + dp[i-1][j-2] + ..... +dp[i-1][j - i + 1]

		So, We write a O(k*n^2) Solution through above formula like this
	*/

	// <TLE> <DP>
	int doit3(int n, int k) {

		vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
		dp[0][0] = 1;

		for (auto x = 1; x < n + 1; x++) {

			for (auto y = 0; y < k + 1; y++) {

				for (auto j = y; j >= std::max(y - x + 1, 0); j--) {

					dp[x][y] = (dp[x][y] + dp[x - 1][j]) % mod;
				}
			}
		}

		return dp[n][k];
	}

	int doit2(int n, int k) {

		vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
		dp[0][0] = 1;

		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < i; ++j) { // In number i, we can create 0 ~ i-1 inverse pairs 
				for (int m = 0; m <= k; ++m) { //dp[i][m] +=  dp[i-1][m-j]
					if (m - j >= 0 && m - j <= k) {
						dp[i][m] = (dp[i][m] + dp[i - 1][m - j]) % mod;
					}
				}
			}
		}
		return dp[n][k];
	}

	

	/*

	But the above solution is too slow, it spends 1000+ms

	O(n * l) Solution
	Look back to the above formula.

	dp[i][j] = dp[i-1][j] + dp[i-1][j-1] + dp[i-1][j-2] + ..... +dp[i-1][j - i + 1]
	Let’s consider this example
	if i = 5

	dp[i][0] = dp[i-1][0] (creates 0 inverse pair)
	dp[i][1] = dp[i-1][0] (1) + dp[i-1][1] (0)  =  dp[i][0] + dp[i-1][1]
	dp[i][2] = dp[i-1][0] (2) + dp[i-1][1] (1) + dp[i-1][2] (0) = dp[i][1] + dp[i-1][2]
	.
	.
	.
	dp[i][4] = dp[i-1][0] (4) + dp[i-1][1] (3) + dp[i-1][2] (2) + dp[i-1][3] (1) + dp[i-1][4] (0)  = dp[i][3] + dp[i-1][4]
	Can you find the rules about above formula.
	if j < i , we can compute dp[i][j] = dp[i][j-1] +dp[i-1][j]

	So, how about j >= i
	We know if we add number i into permutation(0 … i -1 ), i can create 0 ~i -1 inverse pair
	If j >= i , we still use dp[i][j] = dp[i][j-1] +dp[i-1][j].
	We must minus dp[i][j-i]. (In fact it minusdp[i-1][j-i], because everyj >= iin dp vecor,it minus dp[i-1][j-i]individually)
	For example, if i = 5

	dp[i][5] = dp[i][4] + dp[i-1][5] - dp[i-1][0]
	dp[i][6] = dp[i][5] + dp[i-1][6] - dp[i-1][1]

	reference code

	*/

	int kInversePairs(int n, int k) {

		vector<vector<int>> dp(n + 1, vector<int>(k + 1));
		dp[0][0] = 1;

		for (int i = 1; i <= n; ++i) {
			dp[i][0] = 1;

			for (int j = 1; j <= k; ++j) {
				dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % mod;

				if (j - i >= 0) {
					dp[i][j] = (dp[i][j] - dp[i - 1][j - i] + mod) % mod;
					//It must + mod, If you don't know why, you can check the case 1000, 1000
				}
			}
		}

		return dp[n][k];
	}
};


void Test_629_KthInversePairsArray() {

	int res = 0;

	res = KthInversePairsArray().doit(3, 0);

	res = KthInversePairsArray().doit(3, 1);

	res = KthInversePairsArray().doit(1000, 1000);
}
