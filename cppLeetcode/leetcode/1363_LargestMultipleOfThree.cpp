/*
 1363. Largest Multiple of Three
 
 Given an integer array of digits, return the largest multiple of three that can be formed by concatenating some of the given digits in any order.

 Since the answer may not fit in an integer data type, return the answer as a string.

 If there is no answer return an empty string.

  

 Example 1:

 Input: digits = [8,1,9]
 Output: "981"
 Example 2:

 Input: digits = [8,6,7,1,0]
 Output: "8760"
 Example 3:

 Input: digits = [1]
 Output: ""
 Example 4:

 Input: digits = [0,0,0,0,0,0]
 Output: "0"
  

 Constraints:

 1 <= digits.length <= 10^4
 0 <= digits[i] <= 9
 The returning answer must not contain unnecessary leading zeros.

 
 */
#include <string>
#include <vector>

using std::vector;
using std::string;

class LargestMultipleOfThree {
    
public:
    
    string doit_math(vector<int>& digits) {
        int table[10] = {0}, sum = 0;
        for(int e : digits)
            table[e]++, sum += e;
        
        sum %= 3;
        if(sum){
            if (table[sum] + table[sum + 3] + table[sum + 6])
                table[sum]--;
            else
                table[3 - sum] -= 2;
        }
        
        for(int i = 1; i < 10; i++)
            if(table[i] < 0)
                table[i + 3] += table[i], table[i] = 0;
        
        string res = "";
        for(int i = 9; i >= 0; i--)
            while(table[i]--)
                res += i + '0';
        
        return res[0] == '0' ? "0" : res;
    }
    
    string doit_dp_1(vector<int>& digits) {
        
        auto n = digits.size();
        std::sort(begin(digits), end(digits), std::greater<int>());
        digits.insert(begin(digits), 0);
        vector<vector<string>> dp(n+1, vector<string>(3));
        dp[0][0] = "", dp[0][1] = "#", dp[0][2] = "#";
        
        for (auto i = 1; i <= n; i++) {
            for (auto j = 0; j < 3; j++) {
                
                int C = digits[i];
                int last = (j-C%3+3)%3;
                
                if (dp[i-1][j] == "#" && dp[i-1][last] == "#")
                    dp[i][j] = "#";
                else if (dp[i-1][j] == "#")
                    dp[i][j] = dp[i-1][last] + std::to_string(C);
                else if (dp[i-1][last] == "#")
                    dp[i][j] = dp[i-1][j];
                else if (dp[i-1][j].size() >= dp[i-1][last].size() + 1)
                    dp[i][j] = dp[i-1][j];
                else
                    dp[i][j] = dp[i-1][last] + std::to_string(C);
            }
        }
        
        if (dp[n][0][0] == '0')
            return "0";
        
        return dp[n][0];
    }
    
    string doit_dp(vector<int>& digits) {
        
        sort(digits.begin(), digits.end(), std::greater<int>());
        auto n = digits.size();
        digits.insert(digits.begin(), 0);
        
        // int dp[n+1][3];
        // int prev[n+1][3];
        // int pick[n+1][3];
        vector<vector<int>> dp(n+1, vector<int>(3));
        vector<vector<int>> prev(n+1, vector<int>(3));
        vector<vector<int>> pick(n+1, vector<int>(3));
        dp[0][0] = 0, dp[0][1] = INT_MIN, dp[0][2] = INT_MIN;
        
        for (int i=1; i<=n; i++)
            for (int j=0; j<3; j++)
            {
                int last = (j-digits[i]%3+3)%3;
                
                if (dp[i-1][j] >= dp[i-1][last]+1)
                {
                    dp[i][j] = dp[i-1][j];
                    prev[i][j] = j;
                    pick[i][j] = 0;
                }
                else
                {
                    dp[i][j] = dp[i-1][last]+1;
                    prev[i][j] = last;
                    pick[i][j] = 1;
                }
            }

        int j = 0;
        string ret;
        for (int i = n; i >= 1; i--)
        {
            if (pick[i][j])
                ret += '0'+digits[i];
            j = prev[i][j];
        }

        reverse(ret.begin(), ret.end());
        if (ret[0]=='0')
            return "0";

        return ret;
    }
};
