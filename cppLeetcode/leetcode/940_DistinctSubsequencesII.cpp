/*
 
 940. Distinct Subsequences II
 
 Given a string S, count the number of distinct, non-empty subsequences of S .

 Since the result may be large, return the answer modulo 10^9 + 7.

  

 Example 1:

 Input: "abc"
 Output: 7
 Explanation: The 7 distinct subsequences are "a", "b", "c", "ab", "ac", "bc", and "abc".
 Example 2:

 Input: "aba"
 Output: 6
 Explanation: The 6 distinct subsequences are "a", "b", "ab", "ba", "aa" and "aba".
 Example 3:

 Input: "aaa"
 Output: 3
 Explanation: The 3 distinct subsequences are "a", "aa" and "aaa".
 
 */

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <unordered_map>
using std::unordered_map;

class DistinctSubseqII {
    
public:
    
    // because if in overflow, it is not dorable
    int doit3(string S) {
        
        vector<std::pair<int, int>> dp = {{0, 1}};
        unordered_map<char, int> last;
        int mod = 1000000007;
        
        for (int i = 0; i < S.length(); i++) {
            std::pair<int, int> next{dp.back().first, dp.back().second};
            next.first *= 2, next.second *= 2;
            if (next.second > mod) {
                next.first += 1;
                next.second -= mod;
            }
            
            dp.push_back(next);
            if (last.count(S[i]) != 0) {
                if (dp.back().second > dp[last[S[i]]].second) {
                    dp.back().second -= dp[last[S[i]]].second;
                } else {
                    dp.back().second += (mod - dp[last[S[i]]].second);
                    dp.back().first -= 1;
                }
                
            }
            
            last[S[i]] = i;
        }
        
        return dp.back().second - 1;
    }
    
    int distinctSubseqII(string S) {
        
        vector<long long int> dp = {1};
        unordered_map<char, int> last;
        int mod = 1000000007;
        
        for (int i = 0; i < S.length(); i++) {
            int next = ((dp.back() * 2 - (last.count(S[i]) == 0 ? 0 : dp[last[S[i]]] ) + 1) % mod + mod) % mod;
            dp.push_back(next);
            last[S[i]] = i;
        }
        
        return (dp.back() - 1) % mod;
    }
    
    /*
     Denote by dp[i] the number of distinct subsequences ending with the character S[i], and init to '1' for all 'i'.
     S[i] = Sum{j in 0 to i-1} S[j], if S[i] != S[j]
     S[i] = (Sum{j in k to i-1} S[j]) - 1, otherwise. Here S[k] = S[i] and no element between k and i are S[i].
     The -1 comes for eliminating the subsequnce consisting of the single character S[i], which is already
     accounted for in S[k].
    */
    int doit2(string S) {
      long mod = 1000000007;
      vector<long>dp(S.size(),1);
      long cnt = 0;
      for(int i = 0; i< S.size(); i++){
        for(int j = i-1; j >=0; j--) {
          dp[i] = (dp[i] + dp[j]) % mod;
          if(S[i] == S[j]){
            dp[i] = (dp[i] -1) % mod;
            break;
          }
        }
        cnt = (cnt + dp[i]) % mod;
      }
      return cnt;
    }
    
    // O(n) and space O(1)
    int doit(string s) {
        int len = s.size();
        int ans = 0;
        int f[26] = {};
        int mod = 1000000007;
        
        for(int i = len-1; i>=0; i--){
            int a = 1;
            for(int j = 0; j<26; j++){
                a += f[j];
                if(a >= mod)
                    a -= mod;
            }
            f[s[i]-'a'] = a;
        }
        
        for(int i = 0; i<26; i++){
            ans += f[i];
            if(ans>=mod)
                ans -= mod;
        }
        
        return ans;
    }
    
    /*
    This is similar in much easier to 730. Count Different Palindromic Subsequences.

    We can observe that when appending a char c to the left of a string s, we modify only the count of those unique subseq starting by c.
     By maintaining count of subseq according to their the first character we are guaranteed to not count the same subseq more than once.

    To count distinct subseq in string c + s:

    1. find index j of first occurrence of c in s to retrieve the count d of already found distinct subseq starting by char c in s.
    2. Notice now the set of subseq starting by c in augmented string c + s, is exactly {c} U { c+str , str is any non empty subseq in s }. So the updated count is dp[1][i] = dp[0][i+1] + 1;
    3. Update the total number of distinct subseq with dp[0][i] = dp[0][i+1] - d + (dp[0][i+1] + 1);
    */
    
    int doit1(string s) {
        
        int n = s.length();
        
        // dp[1][i] is the number of distinct subseq
        // int the substring starting from indice i,
        // starting by character s[i].
        // dp [0][[i] is the total of distinct subseq.
        std::vector<std::vector<int>> dp(2, std::vector<int>(n+1,0));
        std::vector<int> memo(26,0); // memorize last time a char was seen.

        const int modulo = 1000000007;

        for(int i=n-1; i>=0; --i){
            std::size_t j = memo[s[i]-'a'];
            memo[s[i]-'a'] = i;
                
            dp[0][i] = ((2*dp[0][i+1]- dp[1][j] + 1)%modulo + modulo)%modulo;
            dp[1][i] = (dp[0][i+1] + 1)%modulo;
            
        }
        
        return dp[0][0];
    }
};


void test_940_distinct_subsequences_II() {
    
    auto res = DistinctSubseqII().doit("zchmliaqdgvwncfatcfivphddpzjkgyygueikthqzyeeiebczqbqhdytkoawkehkbizdmcnilcjjlpoeoqqoqpswtqdpvszfaksn");
    
    res = DistinctSubseqII().doit1("zchmliaqdgvwncfatcfivphddpzjkgyygueikthqzyeeiebczqbqhdytkoawkehkbizdmcnilcjjlpoeoqqoqpswtqdpvszfaksn");
    
    res = DistinctSubseqII().doit1("knqmywztzgalovcyitifjmllyltjjnwbehsqaofidwzygekdylwmwxtsnhowpyuwkxomdqsldbcuseojgyimebpvqyzmvubgwhku");
    
    auto res1 = DistinctSubseqII().doit("abc");
    
    auto res2 = DistinctSubseqII().doit("aba");
    
    auto res3 = DistinctSubseqII().doit("aaa");
}
