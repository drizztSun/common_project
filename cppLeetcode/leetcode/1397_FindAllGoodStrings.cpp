/*
1397. Find All Good Strings

Given the strings s1 and s2 of size n, and the string evil. Return the number of good strings.

A good string has size n, it is alphabetically greater than or equal to s1, it is alphabetically smaller than or equal to s2, 
and it does not contain the string evil as a substring. Since the answer can be a huge number, return this modulo 10^9 + 7.

 

Example 1:

Input: n = 2, s1 = "aa", s2 = "da", evil = "b"
Output: 51 
Explanation: There are 25 good strings starting with 'a': "aa","ac","ad",...,"az". 
Then there are 25 good strings starting with 'c': "ca","cc","cd",...,"cz" and finally there is one good string starting with 'd': "da". 
Example 2:

Input: n = 8, s1 = "leetcode", s2 = "leetgoes", evil = "leet"
Output: 0 
Explanation: All strings greater than or equal to s1 and smaller than or equal to s2 start with the prefix "leet", therefore, there is not any good string.
Example 3:

Input: n = 2, s1 = "gx", s2 = "gz", evil = "x"
Output: 2
 

Constraints:

s1.length == n
s2.length == n
s1 <= s2
1 <= n <= 500
1 <= evil.length <= 50
All strings consist of lowercase English letters.

*/
#include <string>
#include <vector>

using std::vector;
using std::string;

class GoodStrings {

public:

    int mod = 1000000007;
    vector<int>lps;
    int m, n;
    string s1, s2, evil;
    int dp[501][51][2][2];

    int solve(int i, int matched, int left, int right){
        if(matched == m) return 0;
        if(i == n) return 1;
        if(dp[i][matched][left][right] != -1) return dp[i][matched][left][right];
        char from = left ? s1[i] : 'a';
        char to = right ? s2[i] : 'z';
        int res = 0;
        for(char c = from; c <= to; c++){
            int j = matched;
            while(j > 0 && evil[j] != c) j = lps[j - 1];
            if(c == evil[j]) j++;
            res += solve(i + 1, j, left && (c == from) , right && (c == to));
            res %= mod;
        }
        //cout<<res<<endl;
        return dp[i][matched][left][right] = res;
    }

    int doit_dp_KMP(int n, string s1, string s2, string evil) {

        this->n = n;
        this->s1 = s1, this->s2 = s2, this->evil = evil;
        m = evil.size();
        memset(dp, -1, sizeof(dp));
        lps.resize(m, 0);
        int i = 1, j = 0;
        
        while(i < m){
            if(evil[i] == evil[j]){
                lps[i++] = ++j;
            }
            else{
                if(j != 0)
                    j = lps[j - 1];
                else i++;
            }
        }
        int ans = solve(0, 0, 1, 1);
        return ans;
    }


// --------

    int doit_dp(int n, string s1, string s2, string evil) {
        init(evil);
        auto noMoreThanS2 = lessThan(n, s2) + (s2.find(evil) == string::npos);
        auto lessThanS1 = lessThan(n, s1);
        auto res = (noMoreThanS2 + mod - lessThanS1) % mod;
        return res;
    }

    long lessThan(int n, string s) {
        
        auto pre = vector(m+1, pair{0LL, 0LL}), cur = pre;  //pair::first: num of curString < s; second: curString == s
        pre[0] = pair{0, 1};

        for (auto c : s) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < 26; j++) {
                    int k = mat[i][j];
                    if (k == m) continue;
                    cur[k].first += pre[i].first;
                    if ('a' + j == c) cur[k].second += pre[i].second;
                    if ('a' + j < c)  cur[k].first += pre[i].second;
                }
            }

            pre = move(cur);
            for (auto &[x, y] : pre) {
                x %= mod;
                y %= mod;
            }
            
            cur = vector(m+1, pair{0LL, 0LL});
        }
        
        long res = 0;
        for (auto &[x, y] : pre) res += x;
        return res % mod;
    }

    void init(const string evil) {
        m = evil.size();
        mat = vector<vector<int>>(m + 1, vector<int>(26, 0));
        for (int i = 0; i <= m; i++) {
            auto prefix = evil.substr(0, i);
            for (int k = 0; k < 26; k++) {
                auto prefixK = prefix + char('a' + k);
                for (int j = 0; j < prefixK.size(); j++) {
                    auto suffix = prefixK.substr(j);
                    if (evil.find(suffix) == 0) {
                        mat[i][k] = suffix.size();
                        break;
                    }
                }
            }
        }
    }

    int m = 0;
    vector<vector<int>> mat; // i is the cur len match eval prefix, j is 0-25,  // mat[i][j] is the len match after add 'a'+j
    const long mod = 1e9 + 7;
};