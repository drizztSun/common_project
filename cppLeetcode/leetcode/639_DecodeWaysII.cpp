/*
# 639. Decode Ways II

# A message containing letters from A-Z is being encoded to numbers using the following mapping way:

# 'A' -> 1
# 'B' -> 2
# ...
# 'Z' -> 26
# Beyond that, now the encoded string can also contain the character '*',
# which can be treated as one of the numbers from 1 to 9.

# Given the encoded message containing digits and the character '*', return the total number of ways to decode it.

# Also, since the answer may be very large, you should return the output mod 109 + 7.

# Example 1:
# Input: "*"
# Output: 9
# Explanation: The encoded message can be decoded to the string: "A", "B", "C", "D", "E", "F", "G", "H", "I".

# Example 2:
# Input: "1*"
# Output: 9 + 9 = 18

*/
#include <algorithm>
#include <string>
#include <vector>

using std::vector;
using std::string;


class DecodeWaysII {

	/*
				639.Decode-Ways-II
		此题是和91.Decode-Ways类似的DP做法，但分情况讨论的类别更加复杂。

		情况I：如果s[i]是数字，分别考虑单位译码和双位译码（和前一个字符组合）。
		单位译码，dp[i] = dp[i-1]*1，

		双位译码，得考虑前面是否是数字。

						if (isdigit(s[i-1]))  // 如果前面也是数字，查看最后两位组合的数字是否合法
						{
							int num = (s[i-1]-'0')*10+(s[i]-'0');
							if (num>=10 && num<=26)
								dp[i]+=dp[i-2];
						}
						else   // 如果是通配符，则需要讨论s[i]本身
						{
							if (s[i]<='6') dp[i] += dp[i-2]*2;  // 类似*5，其中通配符可以代表1或者2
							else dp[i] += dp[i-2];              // 类似*9，其中通配符只能代表12
						}   
		情况II：如果s[i]是通配符，同样分别考虑单位译码和双位译码（和前一个字符组合）。
		单位译码，dp[i] = dp[i-1]*9，最后一位可以是1~9.

		双位译码，同样得考虑前面是否是数字。

						if (s[i-1]=='1') dp[i]+=dp[i-2]*9;        // 1*
						else if (s[i-1]=='2') dp[i]+=dp[i-2]*6;   // 2*
						else if (s[i-1]=='*') dp[i]+=dp[i-2]*15;  // **，注意通配符不能代表零
	*/
	int numDecodings(string s) 
    {
        int n = s.size();
        s = "#"+s;
        vector<long>dp(n+1,0);
        long M = 1e9+7;

        dp[0] = 1;
        if (s[1] == '*') dp[1] = 9;
        else if (s[1] == '0') dp[1] = 0;
        else dp[1] = 1;

        for (int i=2; i<=n; i++)
        {
            if (isdigit(s[i]))
            {
                dp[i] += s[i]=='0' ? 0:dp[i-1];
                if (isdigit(s[i-1]))
                {
                    int num = (s[i-1]-'0')*10+(s[i]-'0');
                    if (num>=10 && num<=26)
                        dp[i]+=dp[i-2];
                }
                else
                {
                    if (s[i]<='6') dp[i] += dp[i-2]*2;
                    else dp[i] += dp[i-2];
                }                
            }
            else
            {
                dp[i] += dp[i-1]*9;
                if (s[i-1]=='1') dp[i]+=dp[i-2]*9;
                else if (s[i-1]=='2') dp[i]+=dp[i-2]*6;
                else if (s[i-1]=='*') dp[i]+=dp[i-2]*15;
            }
            dp[i]%=M;
        }
        return dp[n];
    }


public:

	/*
		# Let�s keep track of:

		# e0 = current number of ways we could decode, ending on any number;
		# e1 = current number of ways we could decode, ending on an open 1;
		# e2 = current number of ways we could decode, ending on an open 2;
		# (Here, an �open 1� means a 1 that may later be used as the first digit of a 2 digit number,
		# because it has not been used in a previous 2 digit number.)

		# With the right idea of what to keep track of, our dp proceeds straightforwardly.

		# Say we see some character c. We want to calculate f0, f1, f2, the corresponding versions of e0, e1, e2 after parsing character c.

		# If c == '*', then the number of ways to finish in total is: we could put * as a single digit number (9*e0),
		# or we could pair * as a 2 digit number 1* in 9*e1 ways, or we could pair * as a 2 digit number 2* in 6*e2 ways.
		# The number of ways to finish with an open 1 (or 2) is just e0.

		# If c != '*', then the number of ways to finish in total is: we could put c as a single digit if it is not zero ((c>'0')*e0),
		# or we could pair c with our open 1, or we could pair c with our open 2 if it is 6 or less ((c<='6')*e2).
		# The number of ways to finish with an open 1 (or 2) is e0 iff c == '1' (or c == '2').
	*/
	int doit_dp_bottomup(string s) {
		int e0 = 1, e1 = 0, e2 = 0;
		int f0 = 0, f1 = 0, f2 = 0;
		long long mod = 1000000007;

		for (auto c : s) {

			if (c == '*') {
				f0 = 9 * e0 + 9 * e1 + 6 * e2;
				f1 = e0;
				f2 = e0;
			} else {
				f0 = int(c > '0') * e0 + e1 + int(c < '7') * e2;
				f1 = int(c == '1') * e0;
				f2 = int(c == '2') * e0;
			}

			e0 = f0 % mod;
			e1 = f1;
			e2 = f2;
		}

		return e0;
	}

	/*
		The idea is DP. One of the hints is that you need mod the answer with a huge prime number.

		For any string s longer than 2, we can decode either the last 2 characters as a whole or the last 1 character. 
		So dp[i] = dp[i-1]* f(s.substr(i,1)) + dp[i-2]* f(s.substr(i-1, 2)). f() is the number of ways to decode a string of length 1 or 2.
		f() could be 0, for example f(�67�).
	
		There is a lot of cases and corner cases for f(string s). For example, * cannot be �0�, so ** has 15 instead of 16 possibilities,
		because �20� is excluded. But the time complexity is still O(n).
		The code is as below.
	*/
	int doit_dp_bottomup(string s) {

		int n = s.length(), p = 1000000007;

		long f1 = 1, f2 = help(s.substr(0, 1));

		for (int i = 1; i < n; i++) {
			long f3 = f1 * help(s.substr(i - 1, 2)) + f2 * help(s.substr(i, 1));
			f1 = f2;
			f2 = f3 % p;
		}

		return f2;
	}

private:

	int help(string s) {

		if (s.length() == 1) {
			if (s == "*")
				return 9;

			return s == "0" ? 0 : 1;
		}

		if (s == "**") {
			return 15;
		}
		else if (s[1] == '*') {
			if (s[0] == '1')
				return 9;
			return s[0] == '2' ? 6 : 0;
		}
		else if (s[0] == '*') {
			return s[1] <= '6' ? 2 : 1;
		}
		else {
			int c = stoi(s);
			return c >= 10 && c <= 26 ? 1 : 0;
		}
	}

};