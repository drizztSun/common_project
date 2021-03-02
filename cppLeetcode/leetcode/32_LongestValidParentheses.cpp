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
#include <stack>

using namespace std;


class LongestValidParentheses {


	/*
		O(n) /O(1)
	*/
    int doit_parenthesis(string s) {

        int left = 0, right = 0;
        int res = 0;
        for (int i = 0; i < s.length(); i++) {
            
            if (s[i] == '(') {
                left++;
            } else {
                right++;
            }
            
            if (left == right)
                res = std::max(res, left + right);
            
            if (right > left)
                left = right = 0;
        }
        
        left = right = 0;
        
        for (int i = s.size()-1; i >= 0; i--) {
            
            if (s[i] == ')') {
                right++;
            } else {
                left++;
            }
            
            if (left == right) 
                res = std::max(res, left + right);
            
            if (left > right) 
                left = right = 0;
        }
        
        return res;
    }



	/*
			032.Longest-Valid-Parentheses
		此题用stack来做非常巧妙.

		我们考虑用一个stack来做常规的符号匹配，即

		遇到左括号入栈；
		遇到右括号，尝试用它对消栈顶的左括号，使其退栈（如果有的话）。否则的话我们就将右括号入栈。
		由此，if possible，我们可以为每一个右括号i，寻找与之匹配的左括号j的位置（即离它左边最近的、可以匹配的左括号）。并且我们可以确定，[j:i]这对括号内的字符肯定也是已经正确匹配了的。

		但是[j:i]就一定是以j结尾的最长的合法字串了吗？不一定。此时观察，将栈顶元素j退栈“对消”之后，此时新的栈顶元素对应的位置并不一定是与j相邻的。
		中间这段“空隙”意味着什么呢？对，这段“空隙”是之前已经退栈了的其他合法字符串。所以我们可以在区间[j:i]的左边再加上这段长度。因此，真正的“以j结尾的最长的合法字串”的长度是i - Stack.top()。注意stack存放的是所有字符的index。	
	*/
	int doit_stack(string s) 
    {
        stack<int>Stack;
        int ret = 0;
        for (int i=0; i<s.size(); i++)
        {
            if (s[i]=='(')            
                Stack.push(i);                            
            else
            {
                if (!Stack.empty() && s[Stack.top()] == '(')
                {
                    Stack.pop();                    
                    ret = max(ret, i - (Stack.empty()?-1 : Stack.top()));
                }
                else
					// we have to put invalid ')' into it, because we need it to placeholder of index.
                    Stack.push(i);
            }
        }
        return ret;
    }

public:

	/*
		Approach 2: Using Dynamic Programming
		Algorithm

		This problem can be solved by using Dynamic Programming. We make use of a \text{dp}dp array where iith element of \text{dp}dp represents the length of the longest valid substring ending at iith index. We initialize the complete \text{dp}dp array with 0's. Now, it's obvious that the valid substrings must end with \text{‘)’}‘)’. This further leads to the conclusion that the substrings ending with \text{‘(’}‘(’ will always contain '0' at their corresponding \text{dp}dp indices. Thus, we update the \text{dp}dp array only when \text{‘)’}‘)’ is encountered.

		To fill \text{dp}dp array we will check every two consecutive characters of the string and if

		\text{s}[i] = \text{‘)’}s[i]=‘)’ and \text{s}[i - 1] = \text{‘(’}s[i−1]=‘(’, i.e. string looks like ``.......()" \Rightarrow‘‘.......()"⇒

		\text{dp}[i]=\text{dp}[i-2]+2dp[i]=dp[i−2]+2

		We do so because the ending "()" portion is a valid substring anyhow and leads to an increment of 2 in the length of the just previous valid substring's length.

		\text{s}[i] = \text{‘)’}s[i]=‘)’ and \text{s}[i - 1] = \text{‘)’}s[i−1]=‘)’, i.e. string looks like ``.......))" \Rightarrow‘‘.......))"⇒

		if \text{s}[i - \text{dp}[i - 1] - 1] = \text{‘(’}s[i−dp[i−1]−1]=‘(’ then

		\text{dp}[i]=\text{dp}[i-1]+\text{dp}[i-\text{dp}[i-1]-2]+2dp[i]=dp[i−1]+dp[i−dp[i−1]−2]+2

		The reason behind this is that if the 2nd last \text{‘)’}‘)’ was a part of a valid substring (say sub_ssub 
		s
		​	
		), for the last \text{‘)’}‘)’ to be a part of a larger substring, there must be a corresponding starting \text{‘(’}‘(’ which lies before the valid substring of which the 2nd last \text{‘)’}‘)’ is a part (i.e. before sub_ssub 
		s
		​	
		). Thus, if the character before sub_ssub 
		s
		​	
		happens to be \text{‘(’}‘(’, we update the \text{dp}[i]dp[i] as an addition of 22 in the length of sub_ssub 
		s
		​	
		which is \text{dp}[i-1]dp[i−1]. To this, we also add the length of the valid substring just before the term "(,sub_s,)" , i.e. \text{dp}[i-\text{dp}[i-1]-2]dp[i−dp[i−1]−2].

		For better understanding of this method, see this example:

		Current
		1 / 8

		Complexity Analysis

		Time complexity : O(n)O(n). Single traversal of string to fill dp array is done.

		Space complexity : O(n)O(n). dp array of size nn is used.
	*/
	int doit_dp(string s) {

		int maxans = 0;
		vector<int> dp(s.size());

		for (int i = 1; i < s.size(); i++) {

			if (s[i] == ')') {

				if (s[i-1] == '(') {
					dp[i] = 2 + (i > 2 ? dp[i-2]: 0);
				} else if (i - dp[i-1] > 0 && s[i-dp[i-1]-1] == '(') {
					dp[i] = 2 + dp[i-1] + (i - dp[i-1] - 2 >= 0 ? dp[i-dp[i-1]-2] : 0);
				}

				maxans = std::max(maxans, dp[i]);
			}
		}

		return maxans;
	}

	/*
	
		Time: O(n)
		Space: O()
	*/
	int doit(string s) {
	
		int i = 0;
		while (i < s.length() && s[i] == ')') i++;

		int j = s.length() - 1;
		while (j >= 0 && s[j] == '(') j--;

		string area = s.substr(i, j - i + 1);
		vector<std::pair<int, int>> st;

		for (auto i = 0; i < area.length(); i++) {

			int sign = (area[i] == '(') ? 1 : -1;

			if (st.empty() || !(sign == -1 && st.back().first == 1))
				st.push_back({ sign, i });
			else 
				st.pop_back();
		}

		int max_length = 0, last = -1;

		for (auto c : st) {
			max_length = std::max(c.second - last - 1, max_length);
			last = c.second;
		}

		return std::max(max_length, int(area.length()) - last - 1);
	}
};