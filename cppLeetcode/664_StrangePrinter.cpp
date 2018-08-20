

/*


# 664. Strange Printer


# There is a strange printer with the following two special requirements:

# The printer can only print a sequence of the same character each time.
# At each turn, the printer can print new characters starting from and ending at any places,
# and will cover the original existing characters.
# Given a string consists of lower English letters only, your job is to count the minimum number of turns the printer needed in order to print it.

# Example 1:
# Input: "aaabbb"
# Output: 2
# Explanation: Print "aaa" first and then print "bbb".

# Example 2:
# Input: "aba"
# Output: 2
# Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the existing character 'a'.

# Hint: Length of the given string will not exceed 100.


*/

#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class StrangePrinter {

/*
# Let dp(i, j) be the number of turns needed to print S[i:j+1].

# Note that whichever turn creates the final print of S[i], might as well be the first turn,
# and also there might as well only be one print, since any later prints on interval [i, k] could just be on [i+1, k].

# So suppose our first print was on [i, k]. We only need to consider prints where S[i] == S[k],
# because we could instead take our first turn by printing up to the last printed index where S[k] == S[i] to get the same result.

# Then, when trying to complete the printing of interval [i, k] (with S[i] == S[k]),
# the job will take the same number of turns as painting [i, k-1].
# This is because it is always at least as good to print [i, k] first in one turn rather than separately.

# Also, we would need to complete [k+1, j].
# So in total, our candidate answer is dp(i, k-1) + dp(k+1, j).

# Of course, when k == i, our candidate is 1 + dp(i+1, j): we paint S[i] in one turn, then paint the rest in dp(i+1, j) turns.

*/

	int helper(string& s, int i, int j, vector<vector<int>>& memo) {

		if (i > j)
			return 0;

		if (memo[i][j] != 0)
			return memo[i][j];

		int ans = helper(s, i + 1, j, memo) + 1;

		for (int k = i + 1; k < j + 1; k++) {
			if (s[k] == s[i]) {
				ans = std::min(ans, helper(s, i, k - 1, memo) + helper(s, k + 1, j, memo));
			}
		}
		
		memo[i][j] = ans;
		return ans;
	}

public:

	int doit(string s) {

		int l = s.length();
		vector<vector<int>> memo(l, vector<int>(l, 0));
		// unordered_map<pair<int, int>, int> A;

		return helper(s, 0, s.size()-1, memo);
	}

};


void Test_664_StangePrinter() {

	int res = StrangePrinter().doit("aaabbb");

	int res1 = StrangePrinter().doit("aba");


	return;
}