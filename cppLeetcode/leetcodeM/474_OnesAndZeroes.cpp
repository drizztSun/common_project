/*
 474. Ones and Zeroes
 
 You are given an array of binary strings strs and two integers m and n.

 Return the size of the largest subset of strs such that there are at most m 0's and n 1's in the subset.

 A set x is a subset of a set y if all elements of x are also elements of y.

  

 Example 1:

 Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
 Output: 4
 Explanation: The largest subset with at most 5 0's and 3 1's is {"10", "0001", "1", "0"}, so the answer is 4.
 Other valid but smaller subsets include {"0001", "1"} and {"10", "1", "0"}.
 {"111001"} is an invalid subset because it contains 4 1's, greater than the maximum of 3.
 Example 2:

 Input: strs = ["10","0","1"], m = 1, n = 1
 Output: 2
 Explanation: The largest subset is {"0", "1"}, so the answer is 2.
  

 Constraints:

 1 <= strs.length <= 600
 1 <= strs[i].length <= 100
 strs[i] consists only of digits '0' and '1'.
 1 <= m, n <= 100
 */
#include <vector>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;
using std::vector;


class OnesAndZeros {
    
public:
    
    
    int doit_dp_1(vector<string>&& strs, int m, int n) {
        auto size = strs.size();
        vector<vector<vector<int>>>dp(size+1,vector<vector<int>>(m+1,vector<int>(n+1,0)));
        
        for(int i = 1; i <= size; i++){
            
            auto zero = count(strs[i-1].begin(), strs[i-1].end(), '0');
            auto one = strs[i-1].length()-zero;
            
            for(int nZero=m; nZero>=zero; nZero--){
                
                for(int nOne=n; nOne>=one; nOne--){
                    
                    dp[i][nZero][nOne] = std::max(dp[i-1][nZero][nOne],dp[i-1][nZero-zero][nOne-one] + 1);
                }
            }
        }
        return dp[size][m][n];
    }
    
    
    int doit_dp(vector<string>&& strs, int m, int n) {
        
        auto hash = [](auto& b) {
            return int(b.first) ^ int(b.second);
        };
        
        auto equal = [](auto& a, auto&b) {
            return a.first == b.first && a.second == b.second;
        };
        
        unordered_map<std::pair<int, int>, int, decltype(hash), decltype(equal)> dp(0, hash, equal);
        dp.insert({{0, 0}, 1});
        
        
        for (auto& item : strs) {
            
            auto z = 0, o = 0;
            for (auto c: item)
                if (c == '1')
                    z++;
                else
                    o++;
            
            auto tmp(dp);
            //unordered_map<std::pair<int, int>, int, decltype(hash), decltype(equal)> tmp(0, hash, equal);
            for (auto i = z; i <= m; i++)
                for(auto j = o; j <= n; j++) {
                    std::pair<int,int> key{i - z, j - o};
                    if (dp.count(key) > 0) {
                        tmp[{i, j}] = std::max(tmp[{i, j}], dp[key] + 1);
                    }
                }
            
            dp.swap(tmp);
        }
        
        int res = 0;
        for (auto [k, v] : dp)
            res = std::max(res, v);
        
        return res;
    }
};

void test_474_zeros_and_ones() {
    
    OnesAndZeros().doit_dp(vector<string>{"10","0001","111001","1","0"}, 5, 5);
}
