/*

44. Wildcard Matching


Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like ? or *.
Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:

Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
Example 4:

Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
Example 5:

Input:
s = "acdcb"
p = "a*c?b"
Output: false

*/

#include <string>
#include <vector>
using namespace std;

class isMatch {

	bool match(string& s, int s1, string& p, int p1, vector<vector<int>>& dict) {

		if (dict[s1][p1] != -1)
			return dict[s1][p1];


		if (p1 == p.size()) {
			return s1 == s.size();
		}

		if (s1 == s.size()) {
			bool res = true;
			for (;p1 < p.length() && res; p1++)
				res = p[p1] == '*';
			return res;
		}

		bool res = false;
		if (s[s1] == p[p1] || p[p1] == '?') {
			res = match(s, s1 + 1, p, p1 + 1, dict);
		}
		else if (p[p1] == '*') {
			while (p1 < p.size() && p[p1] == '*') 
				p1++;

			for (auto i = 0; s1 + i <= s.length(); i++) {
				if (match(s, s1 + i, p, p1, dict)) {
					res = true;
					break;
				} 
			}
		}

		dict[s1][p1] = res;

		return res;
	}


public:
	
	

	bool doit1(string s, string p) {
		int M = s.size(), N = p.size();
		vector<vector<int>> dict(M+1, vector<int>(N+1, -1));

		return match(s, 0, p, 0, dict);
	}


	bool doit(string s, string p) {
		int s1 = 0, p1 = 0;
		int ss = s.size(), ps = p.size();

		while (s1 < s.length()) {

			if (s[s1] == p[p1] || p[p1] == '?') {
				s1++, p1++;
			}
			else if (p[p1] == '*') {
				ss = s1;
				ps = p1++;
			}
			else if (ps != p.length()) {
				s1 = ++ss;
				p1 = ps + 1;
			}
			else {
				return false;
			}
		}

		while (p1 < p.length() && p[p1] == '*') p1++;

		return p1 == p.length();
	}


};



void Test_44_WildcardMatching() {

	bool res1 = isMatch().doit("aa", "a");

	bool res2 = isMatch().doit("aa", "*");

	bool res3 = isMatch().doit("cb", "?a");

	bool res4 = isMatch().doit("adceb", "a*b");

	bool res5 = isMatch().doit("acdcb", "a*c?b");

	bool res6 = isMatch().doit("mississippi", "m??*ss*?i*pi");

	res6 = isMatch().doit("mississippi", "mi**ss*?i*pi");

	bool res7 = isMatch().doit("abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb", 
		"**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb");

}