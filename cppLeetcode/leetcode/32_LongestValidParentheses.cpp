/*
# 32. Longest Valid Parentheses

Given a string containing just the characters '(' and ')', 
find the length of the longest valid (well-formed) parentheses substring.

Example 1:

Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"
Example 2:

Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"


*/
#include <algorithm>
#include <string>
#include <vector>
using namespace std;


class LongestValidParentheses {

public:

	int doit(string s) {
	
		int i = 0;
		while (i < s.length() && s[i] == ')') i++;

		int j = s.length() - 1;
		while (j >= 0 && s[j] == '(') j--;

		string area = s.substr(i, j - i + 1);
		vector<pair<int, int>> st;

		for (auto i = 0; i < area.length(); i++) {

			int sign = (area[i] == '(') ? 1 : -1;

			if (st.empty() || !(sign == -1 && st.back().first == 1))
				st.push_back({ sign, i });
			else 
				st.pop_back();
		}

		int max_length = 0, last = -1;

		for (auto c : st) {
			max_length = max(c.second - last - 1, max_length);
			last = c.second;
		}


		return max(max_length, int(area.length()) - last - 1);
	}
};

void Test_32_LongestValidParentheses() {

	int res1 = LongestValidParentheses().doit("(()");

	int res2 = LongestValidParentheses().doit(")()())");

	int res3 = LongestValidParentheses().doit(")()())()()(");
}