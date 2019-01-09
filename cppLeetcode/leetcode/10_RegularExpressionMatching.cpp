/*


# leetcode 10. Regular Expression Matching

# Implement regular expression matching with support for '.' and '*'.
# '.' Matches any single character.
# '*' Matches zero or more of the preceding element.

# The matching should cover the entire input string (not partial).

# The function prototype should be:
# bool isMatch(const char *s, const char *p)

# Some examples:
# isMatch("aa","a") ? false
# isMatch("aa","aa") ? true
# isMatch("aaa","aa") ? false
# isMatch("aa", "a*") ? true
# isMatch("aa", ".*") ? true
# isMatch("ab", ".*") ? true
# isMatch("aab", "c*a*b") ? true

*/
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
using namespace std;


namespace std {

	template <>
	class pair<int, int> {
	public:
		int _a;
		int	_b;

		pair(int a, int b) :_a(a), _b(b) {}

		bool operator == (const pair<int, int>& item) const {
			return item._a == _a && item._b == _b;
		}

		auto& operator = (const pair<int, int>& item) {
			this->_a = item._a;
			this->_b = item._b;
			return *this;
		}

	};

	typedef pair<int, int> pairInt;

	template<>
	class hash<pairInt> {
	public:
		auto operator() (const pairInt& a) const {
			return hash<int>()(a._a) ^ hash<int>()(a._b);
		}
	};

};

class RegularExpressMatch1 {


	bool search(const string& s, int i, const string& p, int j, unordered_map<pair<int, int>, bool>& A) {

		if (j == p.length())
			return i == s.length();

		if (A.find({ i, j }) == A.end())
			return A[{i, j}];

		bool res = false;
		bool isStart = j < p.length()-1 && p[j + 1] == '*';

		if (isStart) {
			res = search(s, i, p, j + 2, A) || ((s[i] == p[j] || p[j] == '.') && search(s, i + 1, p, j, A));
		}
		else {
			res = (s[i] == p[j] || p[j] == '.') && search(s, i + 1, p, j + 1, A);
		}

		A[{1, j}] = res;

		return res;
	}

public:



	bool isMatch(string s, string p) {

		return search(s, 0, p, 0, unordered_map<pair<int, int>, bool>());
	}
};

class RegularExpressMatch {

public:

	/*
	    # *
        # * f[i][j]: if s[0..i-1] matches p[0..j-1]
        #
        # * if p[j - 1] != '*'
        # *      f[i][j] = f[i - 1][j - 1] && s[i - 1] == p[j - 1]
        #
        # * if p[j - 1] == '*', denote p[j - 2] with x
        # *      f[i][j] is true iff any of the following is true
        # *      1) "x*" repeats 0 time and matches empty: f[i][j - 2]
        # *      2) "x*" repeats >= 1 times and matches "x*x": s[i - 1] == x && f[i - 1][j]
        # * '.' matches any single character
        # *
	*/

	bool isMatch(string s, string p) {
		int M = s.length(), N = p.length();
		vector<vector<bool>> DP(M + 1, vector<bool>(N + 1, false));
		DP[0][0] = true;

		for (int i = 1; i <= N; i++) {
			DP[0][i] = (i > 1) && p[i - 1] == '*' && DP[0][i - 2];
		}
		
		for (int i = 1; i <= M; i++) {

			for (int j = 1; j <= N; j++) {

				if (p[j-1] == '*') {
					// s[0..i - 1] p[0..j] is matched, so '*' match one more time, 's[i-1]'
					// 1) DP[i][j-2]
					// 2) (DP[i-1][j] && (s[i-1] == p[j-2] || p[j-2] == '.'));
					//    it means that it match one more 's[i-1]' again
					DP[i][j] = DP[i][j - 2] || (DP[i-1][j] && (s[i-1] == p[j-2] || p[j-2] == '.'));
				}
				else {
					DP[i][j] = DP[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
				}
			}
		}

		return DP[M][N];
	}

};


void Test_10_RegularExpressionMatching() {

	bool res9 = RegularExpressMatch().isMatch("a", "ab*");

	bool res8 = RegularExpressMatch().isMatch("mississippi", "mis*is*p*.");

	bool res7 = RegularExpressMatch().isMatch("aab", "c*a*b");

	bool res1 = RegularExpressMatch().isMatch("aa", "a");

	bool res2 = RegularExpressMatch().isMatch("aa", "aa");

	bool res3 = RegularExpressMatch().isMatch("aaa", "aa");

	bool res4 = RegularExpressMatch().isMatch("aa", "a*");

	bool res5 = RegularExpressMatch().isMatch("aa", ".*");

	bool res6 = RegularExpressMatch().isMatch("ab", ".*");
		
	return;
}