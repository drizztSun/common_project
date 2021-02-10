/*
1682. Longest Palindromic Subsequence II

A subsequence of a string s is considered a good palindromic subsequence if:

It is a subsequence of s.
It is a palindrome (has the same value if reversed).
It has an even length.
No two consecutive characters are equal, except the two middle ones.
For example, if s = "abcabcabb", then "abba" is considered a good palindromic subsequence, 
while "bcb" (not even length) and "bbbb" (has equal consecutive characters) are not.

Given a string s, return the length of the longest good palindromic subsequence in s.

 

Example 1:

Input: s = "bbabab"
Output: 4
Explanation: The longest good palindromic subsequence of s is "baab".
Example 2:

Input: s = "dcbccacdb"
Output: 4
Explanation: The longest good palindromic subsequence of s is "dccd".
 

Constraints:

1 <= s.length <= 250
s consists of lowercase English letters.


*/
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using std::map;
using std::vector;
using std::string;

class LongestPalindromeSubseq {

public:
    
    int doit_(string s) {

        int n = s.length();

        vector<vector<map<char, int>>> dp(n, vector<map<char, int>>(n));

        std::function<int(int, int, char)> dfs = [&](int i, int j, char last) {
            
            if (i >= j) return 0;

            if (dp[i][j].count(last) > 0) return dp[i][j];

            if (s[i] == s[j] and s[i] != last) {
                dp[i][j] = 2 + search(i+1, j-1, s[i]);
            } else {
                dp[i][j] = std::max(search(i, j-1, last), search(i+1, j-1, last));
            }
        }

        return search(0, n-1, '#');
    }

    int dp_dp_bottomup(string s) {
        const int n = s.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(26))); 
        
        for(int len = 2; len <= n;len++){
            for(int i = 0; i + len <= n; i++){
                for(int k = 0; k < 26; k++){
                    dp[len][i][k] = std::max(dp[len-1][i][k], dp[len-1][i+1][k]);
                }
                if(s[i] == s[i+len-1]){
                    int p = s[i] - 'a';
                    int maxDp = 0;
                    for(int k = 0; k < 26; k++){
                        if(k == p) continue;
                        maxDp = std::max(maxDp, dp[len-2][i+1][k]);
                    }
                    dp[len][i][p] = std::max(dp[len][i][p], 2+maxDp);
                }
            }
        }
        return *std::max_element(dp[n][0].begin(), dp[n][0].end());
    }

    int doit_dp_bottomup(string s) 
    {
        int result=0,n=s.length();
        vector<vector<int>> total(26); //store all the indices for each character
        for(int i=0;i<n;i++)
            total[s[i]-'a'].push_back(i);

        int dp[n][n]; //dp[i][j] is the maximum palindrome length from s[i:j] (both ends inclusive)
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n-1;i++) //the length of the palindrome
        {
            for(int j=0;j<n-i;j++) //the start index of the palindrome
            {
                if(s[j]!=s[j+i]) //check if the character is the same
                    continue;

                dp[j][j+i]=2; //the length should be at least 2 if the left and right bounding character is the same
                for(int k=0;k<26;k++)
                {
                    //for each a to z, find the leftmost and rightmost occurrence between the bounding characters
                    if(s[j]==(char)(k+'a')) //there should not be any consecutive characters except the 2 in the middle
                        continue;

                    vector<int>::iterator low;
                    low=lower_bound(total[k].begin(),total[k].end(),j+1);
                    vector<int>::iterator up;
                    up=upper_bound(total[k].begin(),total[k].end(),j+i-1);
                    int index_low=(int)(low-total[k].begin());
                    int index_up=(int)(up-total[k].begin())-1;
                    if(index_low>=index_up||index_up==n)
                        continue;

                    dp[j][j+i]=max(dp[j][j+i],dp[total[k][index_low]][total[k][index_up]]+2); //the maximum palindrome length should be the maximum of those palindrome length between j and j+i plus 2
                }
            }
        }

        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                result=max(result,dp[i][j]);
                
        return result;
    }
};