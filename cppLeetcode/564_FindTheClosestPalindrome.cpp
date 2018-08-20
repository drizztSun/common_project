

/*

# 564. Find the Closest Palindrome

# Given an integer n, find the closest integer (not including itself), which is a palindrome.

# The 'closest' is defined as absolute difference minimized between two integers.

# Example 1:
# Input: "123"
# Output: "121"

# Note:
# The input n is a positive integer represented by string, whose length will not exceed 18.
# If there is a tie, return the smaller one as answer.



# Let�s build a list of candidate answers for which the final answer must be one of those candidates. Afterwards,
# choosing from these candidates is straightforward.

# If the final answer has the same number of digits as the input string S, then
# the answer must be the middle digits + (-1, 0, or 1) flipped into a palindrome.
# For example, 23456 had middle part 234, and 233, 234, 235 flipped into a palindrome yields 23332, 23432, 23532.
# Given that we know the number of digits, the prefix 235 (for example) uniquely determines the corresponding palindrome 23532, so all palindromes with larger prefix like 23732 are strictly farther away from S than 23532 >= S.

# If the final answer has a different number of digits, it must be of the form 999....999 or 1000...0001, as any palindrome smaller than 99....99 or bigger than 100....001 will be farther away from S.


*/

#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class NearestPalindromic {
public:
	string doit(string n) {
		
		size_t numsLength = n.length();
		vector<long> candidates;

		candidates.push_back(pow(10, numsLength) + 1);
		candidates.push_back(pow(10, numsLength) - 1);

		candidates.push_back(pow(10, numsLength - 1) + 1);
		candidates.push_back(pow(10, numsLength - 1) - 1);

		long prefix = stol(n.substr(0, (numsLength + 1) / 2));
		for (long i = -1; i < 2; i++) {
			string p = to_string(prefix + i);
			string pp = p + string(p.rbegin() + (numsLength & 1), p.rend());
			candidates.push_back(stol(pp));
		}

		long ans = 0, diff = INT_MAX;
		long base = stol(n);
		for (auto c : candidates) {

			long d = abs(c - base);
			if (d == 0 || d > diff || (d == diff && c > ans))
				continue;

			ans = c;
			diff = d;
		}

		return to_string(ans);
	}


	string doit1(string n) {

		int l = n.size();
		set<long> candidates;

		// biggest, one more digit, 10...01
		candidates.insert(long(pow(10, l)) + 1);
		// smallest, one less digit, 9...9 or 0
		candidates.insert(long(pow(10, l - 1)) - 1);
		
		// the closest must be in middle digit +1, 0, -1, then flip left to right
		long prefix = stol(n.substr(0, (l + 1) / 2));
		for (long i = -1; i <= 1; ++i) {
			string p = to_string(prefix + i);
			string pp = p + string(p.rbegin() + (l & 1), p.rend());
			candidates.insert(stol(pp));
		}
		
		long num = stol(n), minDiff = LONG_MAX, diff, minVal;
		candidates.erase(num);
		for (long val : candidates) {
			diff = abs(val - num);
			if (diff < minDiff) {
				minDiff = diff;
				minVal = val;
			}
			else if (diff == minDiff) {
				minVal = min(minVal, val);
			}
		}
		
		return to_string(minVal);
	}
};


void Test_564_FindCloestPalindrome() {


}