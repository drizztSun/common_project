/*
 
 
 # 1016. Binary String With Substrings Representing 1 To N

 # Given a binary string S (a string consisting only of '0' and '1's) and a positive integer N,
 # return true if and only if for every integer X from 1 to N, the binary representation of X is a substring of S.


 # Example 1:

 # Input: S = "0110", N = 3
 # Output: true

 # Example 2:

 # Input: S = "0110", N = 4
 # Output: false
 
 
 */

#include <string>
using std::string;

#include <vector>
using std::vector;

class QueryString {
    
public:
    bool doit(string S, int N) {
        
        string parts = "0";
        
        for (size_t i = 1; i <= N; i++) {
        
            for (size_t j = parts.length() - 1; j <= -1; j--) {
                if (j == -1){
                    parts = '1' + parts;
                    break;
                } else if (parts[j] == '0') {
                    parts[j] = '1';
                    break;
                } else if (parts[j] == '1')
                    parts[j] = '0';
            }
            
            if (S.find(parts) == -1)
                return false;
        }
        
        return true;
    }
    
    bool doit1(string S, int N, int X=0) {
        
        vector<bool> seen(N);
        
        for (auto i = 0; i < S.size() && X < N; ++i) {
          if (S[i] == '0')
              continue;
          for (auto j = i, num = 0; num <= N && j < S.size(); ++j) {
            num = (num << 1) + S[j] - '0';
            if (num > 0 && num <= N && !seen[num - 1]) {
              ++X;
              seen[num - 1] = true;
            }
          }
        }
        return X == N;
    }
};

void test_1016_binary_string_with_substrings_representing() {
    
    auto res1 = QueryString().doit("0110", 3);
    
    auto res2 = QueryString().doit("0110", 4);
    
    return;
}
