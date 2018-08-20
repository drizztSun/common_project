/*

# 761. Special Binary String

# Special binary strings are binary strings with the following two properties:

# The number of 0's is equal to the number of 1's.
# Every prefix of the binary string has at least as many 1's as 0's.
# Given a special string S, a move consists of choosing two consecutive,
# non-empty, special substrings of S, and swapping them.

# (Two strings are consecutive if the last character of the first string
# is exactly one index before the first character of the second string.)

# At the end of any number of moves, what is the lexicographically largest resulting string possible?

# Example 1:
# Input: S = "11011000"
# Output: "11100100"

# Explanation:
# The strings "10" [occuring at S[1]] and "1100" [at S[3]] are swapped.
# This is the lexicographically largest string possible after some number of swaps.
# Note:

# S has length at most 50.
# S is guaranteed to be a special binary string as defined above.


*/


#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;


class MakeLargestSpecial {


	string largestSpecString(string S) {

		int count = 0, j = 0;
		vector<string> res;

		for (size_t i = 0; i < S.size(); i++) {

			if (S[i] == '1')
				count++;
			else
				count--;

			if (count == 0) {
				res.push_back("1" + largestSpecString(S.substr(j + 1, i - j - 1)) + "0");
				j = i + 1;
			}
		}

		sort(res.begin(), res.end(), greater<string>());

		string res2;
		for (auto c : res)
			res2 += c;

		return res2;
	}

public:

	string doit(string S) {

		return largestSpecString(S);
	}



	string makeLargestSpecial(string S) {
		int res = 0, pre = 0;
		vector<string> v;
		for (int i = 0; i < S.size(); i++) {
			res += S[i] == '1';
			res -= S[i] == '0';
			if (res == 0) {
				string s = "1";
				if (pre + 1 != i)
					s += makeLargestSpecial(S.substr(pre + 1, i - pre - 1));
				s += "0";
				v.push_back(s);
				pre = i + 1;
			}
		}

		sort(v.begin(), v.end(), greater<string>());
		string ret;
		for (auto vs : v)
			ret += vs;

		return ret;
	};
};

void Test_761_SpecialBinaryString() {

	string res = MakeLargestSpecial().doit("11011000");

	return;
}