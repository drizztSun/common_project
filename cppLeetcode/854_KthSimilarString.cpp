/*

# 854. K-Similar Strings

# Strings A and B are K-similar (for some non-negative integer K)
# if we can swap the positions of two letters in A exactly K times so that the resulting string equals B.

# Given two anagrams A and B, return the smallest K for which A and B are K-similar.

# Example 1:

# Input: A = "ab", B = "ba"
# Output: 1
# Example 2:

# Input: A = "abc", B = "bca"
# Output: 2
# Example 3:

# Input: A = "abac", B = "baca"
# Output: 2
# Example 4:

# Input: A = "aabc", B = "abca"
# Output: 2
# Note:

# 1 <= A.length == B.length <= 20
# A and B contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}

*/
#include <algorithm>
#include <vector>
#include <string>


#include <queue>
using namespace std;


class KthSimiliar {


public:

	int kSimilarity(string A, string B) {

		for (size_t i = 0; i < A.length(); i++) {

			if (A[i] == B[i])
				continue;

			vector<int> matches;
			for (size_t j = i + 1; j < A.length(); j++) {

				if (A[j] != B[j] && A[j] == B[i]) {

					matches.push_back(j);

					if (A[i] == B[j]) {
						swap(A[i], A[j]);
						return 1 + kSimilarity(A.substr(i + 1), B.substr(i + 1));
					}
						
				}
			}

			int best = A.size() - 1;
			for (auto j : matches) {
				swap(A[i], A[j]);
				best = min(best, 1 + kSimilarity(A.substr(i + 1), B.substr(i + 1)));
				swap(A[i], A[j]);
			}

			return best;
		}

		return 0;
	}


	// #<bfs>
	int bfs(string A, string B) {

		int len = A.length();
		queue<pair<string, int>> q;
		q.push(make_pair(A, 0));
		vector<vector<int>> pos(6);
		for (int i = 0; i < len; i++)
			pos[B[i] - 'a'].push_back(i);

		while (!q.empty()) {

			string t = q.front().first;
			int d = q.front().second;

			int i = 0;
			for (; i < len && t[i] == B[i]; i++);
			if (i == len)
				return d;

			q.pop();
			for (int n : pos[t[i] - 'a']) {
				if (t[n] != B[n]) {
					string p = t;
					swap(p[i], p[n]);
					q.push(make_pair(p, d + 1));
				}
			}
		}

		return -1;
	}
};


void Test_854_KthSimilarString() {

	auto res1 = KthSimiliar().kSimilarity("abccaacceecdeea", "bcaacceeccdeaae");

	auto res2 = KthSimiliar().kSimilarity("aabc", "abca");
	
	auto res3 = KthSimiliar().bfs("abccaacceecdeea", "bcaacceeccdeaae");

	auto res4 = KthSimiliar().bfs("aabc", "abca");
}