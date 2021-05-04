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
#include <functional>

using namespace std;

class isMatch {

	/*
				044.Wildcard-Matching
		这道题的入手点是当做双序列的DP问题来做。设计dp[i][j]表示s的前i个元素、p的前j个元素能否匹配。（注意，预先调整成为1-index）

		分析转移方程的时候，依然是关注s的第i个元素，p的第j个元素。其中p[j]是关键，因为它可能是通配符。所以常规的思路是：

		如果p[j]='?'，它必须匹配s的第i个元素，显然dp[i][j]=dp[i-1][j-1].
		如果p[j]='*'，它可以匹配s结尾的任意多个元素，所以有：
		for (int k=0; k<=i; k++)
		if (dp[k][j-1]==1) dp[i][j]=1;
		如果p[j]是普通字符，则必须与s的第i各元素完全一致。所以
		if (s[i]==p[j])
		dp[i][j]=dp[i-1][j-1]
		接下来考虑两个问题。首先是边界条件。最常见的dp[0][0]=1是必然的。但同时要注意到第二种情况时，我们会查看dp[0][j-1]，而这个是未定义的。事实上dp[0][x]对任何的j而言不一定是0，比如当

		s = ""
		p = ****
		所以我们需要对所有的dp[0][x]设计初始值。只有当p的前若干个都是星号时，才有dp[0][x]=1.

		另外一个问题，就是如何改进第二种情况。用一个for循环是比较低效的，其实有一个更优秀的判定手段。

		我们知道，当p[j]=='*'的前提下，我们有dp[i][j] = dp[0][j-1] || dp[1][j-1] || dp[2][j-1] || ... || dp[i-1][j-1] || dp[i][j-1]。

		我们将i用i-1替换，就同理可以写出dp[i-1][j] = dp[0][j-1] || dp[1][j-1] || dp[2][j-1] || ... || dp[i-1][j-1]。

		用第二式替换第一式右边的大部分项，就有dp[i][j] = dp[i-1][j] || dp[i][j-1].惊喜不惊喜？
	*/
	bool isMatch(string &s, string &p) 
    {
        int M = s.size();
        int N = p.size();
        s="0"+s;
        p="0"+p;
        auto dp = vector<vector<int>>(M+1,vector<int>(N+1,0));        

        dp[0][0] = 1;
        for (int j=1; j<=N; j++)
        {
            if (p[j]!='*') break;
            dp[0][j] = 1;
        }
        
        for (int i=1; i<=M; i++)
            for (int j=1; j<=N; j++)
            {
                if (p[j]=='?')
                    dp[i][j] = dp[i-1][j-1];
                else if (p[j]=='*')
                {
                    // for (int k=0; k<=i; k++)
                    //     if (dp[k][j-1]==1) dp[i][j]=1;
                    dp[i][j] = dp[i][j-1]||dp[i-1][j];
                }
                else if (s[i]==p[j])
                    dp[i][j] = dp[i-1][j-1];
            }
        
        return dp[M][N];
    }

public:

	bool doit_topdown_dp(string s, string p) {

		int M = s.size(), N = p.size();
		
		vector<vector<int>> dict(M+1, vector<int>(N+1, -1));

		std::function<bool(int, int)> match = [&](int s1, int p1) {

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
				res = match(s1 + 1, p1 + 1);
			}
			else if (p[p1] == '*') {
				while (p1 < p.size() && p[p1] == '*') 
					p1++;

				for (auto i = 0; s1 + i <= s.length(); i++) {
					if (match(s1 + i, p1)) {
						res = true;
						break;
					} 
				}
			}

			dict[s1][p1] = res;

			return res;
		};

		return match(0, 0);
	}

public:

	bool doit_dp_bottomup(string s, string p) {

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