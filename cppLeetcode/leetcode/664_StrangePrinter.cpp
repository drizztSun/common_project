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
#include <array>
#include <vector>
#include <functional>

using std::string;
using std::vector;

class StrangePrinter {


	/*
		664.Strange-Printer
		拿到这题，我会考虑这样一个问题，最基本款的打印方案是什么？当然是一个字一个字地打印，也就是打印N次。

		然后我想，题目中的打印方式会带来什么优势？我会想到这样一个例子：a X X X X a X X X X。如果我们在打印第一个a的时候，顺便把整个字符串都打印上a，那么字符串中间的那个a就占了便宜。
		我们接下来只需要考虑处理两个更小的区间X X X X怎么打印就行了。也就是说，此时动态转移方程呼之欲出：

		设计动态转移方程dp[i][j]，表示打印以s[i]开始、s[j]结尾的子串，需要最少的turns。

		dp[i][j] = 1+dp[i+1][j]  //基本款
		dp[i][j] = min { dp[i][k-1] + dp[k+1][j] }  for s[k]==s[i]
		注意，如果k+1>j，那么dp[k+1][j]的值默认为0.

		如果你有兴趣，会更深入地想，在处理dp[i][j]的时候，为什么首先一定是先从i位置开始打印一串s[i]的字符呢？为什么不是先打印其他地方的字符，再从i位置开始打印一串s[i]的字符呢？
		原因是s[i]不能依靠打印其他字符时被“捎带”上，必须老老实实在i的位置单独打印。与其在i位置单独打一个s[i]，肯定不如顺便直接打出一串s[i]。
		
		想到这点的话，如果我们先打印了其他地方的XXXX的字符、再不幸被这串s[i]覆盖的话，显然效率肯定低，不如索性第一步就从i位置开始打印一串s[i]的字符。这就是以上思想为什么总是我们在处理dp[i][j]时，总是考虑首先要打印一串s[i]的原因。

		因为根据dp[i][j]的定义，显然是从小区间推导出大区间的过程，所以两层循环的模板如下：

				for (int len=2; len<=N; len++)
					for (int i=0; i<=N-len; i++)
					{
						int j = i+len-1;
						dp[i][j] = 1+dp[i+1][j];
						
						for (int k=i+1; k<=j; k++)
						{
							if (s[k]==s[i])                    
								dp[i][j] = min(dp[i][j], dp[i][k-1] + ((k+1>j)?0:dp[k+1][j]));
						}                    
					}      
		初始条件是：

		dp[i][j]==1 when i==j，即len的长度为1;
		dp[i][j]==0 when i>j; C语言里如果用int[][]来定义二维数组的话，元素默认值都是0.

	*/
	int strangePrinter(string s) 
    {        
        int N = s.size();
        if (N==0) return 0;
        
        auto dp = vector<vector<int>>(N,vector<int>(N));
        for (int i=0; i<N; i++)
            dp[i][i] = 1;
                
        for (int len=2; len<=N; len++)
            for (int i=0; i<=N-len; i++)
            {
                int j = i+len-1;
                dp[i][j] = 1+dp[i+1][j];
                
                for (int k=i+1; k<=j; k++)
                {
                    if (s[k]==s[i])
                    {
                        dp[i][j] = min(dp[i][j], dp[i][k-1] + ((k+1>j)?0:dp[k+1][j]));
                    }                        
                }    
                
            }        
        return dp[0][N-1];
    }

public:

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
	int doit_dp_topdown_dfs(string s) {

		int l = s.length();
		vector<vector<int>> memo(l, vector<int>(l, 0));

		std::function<int(int, int)> helper = [&](int i, int j) {

			if (i > j)
				return 0;

			if (memo[i][j] != 0)
				return memo[i][j];

			int ans = helper(i + 1, j) + 1;

			for (int k = i + 1; k < j + 1; k++) {
				if (s[k] == s[i]) {
					ans = std::min(ans, helper(i, k - 1) + helper(k + 1, j));
				}
			}
			
			memo[i][j] = ans;
			return ans;
		};


		return helper(0, s.size()-1);
	}
    
    int doit_dp_botomup(string s) {
        
        if (s.length() == 0)
            return 0;
        
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, n));
        
        for (int j = 0; j < n; j++) {
            
            for (int i = j; i > -1; i--) {
                
                if (i == j) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = 1 + dp[i+1][j];
                    for (int k = i+1; k <= j; k++) {
                        
                        if (s[i] == s[k])
                            dp[i][j] = std::min(dp[i][j], dp[i][k-1] + ((k+1 > j) ? 0 : dp[k+1][j]));
                    }
                }
            }
        }
        
        return dp[0][n-1];
    }
};