/*
 
 1012. Numbers With Repeated Digits
 
  Given a positive integer N, return the number of positive integers less than or equal to N that have at least 1 repeated digit.

   

  Example 1:

  Input: 20
  Output: 1
  Explanation: The only positive number (<= 20) with at least 1 repeated digit is 11.
  Example 2:

  Input: 100
  Output: 10
  Explanation: The positive numbers (<= 100) with atleast 1 repeated digit are 11, 22, 33, 44, 55, 66, 77, 88, 99, and 100.
  Example 3:

  Input: 1000
  Output: 262
 
 */

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <unordered_set>
using std::unordered_set;

class NumDupDigitsAtMostN {

    
public:
    typedef long long ll;
    string s;
    int dp[10][2][2][2][1<<10];

    ll ff(int pos, bool tight, bool st, bool cnt, int mask) {
        // If index reaches the length of the string return whether
        // any repetition till now has been found or not?
        if (pos == s.size())
            return cnt ? 1 : 0;
        
        // Look in the DP table
        if (dp[pos][tight][st][cnt][mask] != -1)
            return dp[pos][tight][st][cnt][mask];

        ll res = 0;
        ll en = tight ? s[pos]-'0':9;

        if (!st) {
            // Place 0s, go to the rightmost
            res = ff(pos+1, tight&s[pos]=='0', st, cnt, mask);
            for (ll i=1; i<=en; i++) {
                // Start the number, st = true
                res += ff(pos+1, tight&(i==en), st|(i > 0), cnt, mask|1<<i);
            }
        }else {
            // Number has started
            for (ll i=0; i<=en; i++) {
                // If number is found repeated, check using bitmask (mask & (1 << i))
                // Make the cnt = true, i.e. cnt | mask&(1<<i)
                res += ff(pos+1, tight&(i==en), st, cnt|(mask&(1<<i)), mask|1<<i);
            }
        }

        return dp[pos][tight][st][cnt][mask] = res;
    }

    int doit1(int N) {
        s = std::to_string(N);
        memset(dp, -1, sizeof dp);
        return ff(0, true, false, false, 0);
    }
    
    
public:
    
    /*
     Intuition
     Count res the Number Without Repeated Digit
     Then the number with repeated digits = N - res

     Similar as
     788. Rotated Digits
     902. Numbers At Most N Given Digit Set

     Explanation:
     Transform N + 1 to arrayList
     Count the number with digits < n
     Count the number with same prefix
     For example,
     if N = 8765, L = [8,7,6,6],
     the number without repeated digit can the the following format:
     XXX
     XX
     X
     1XXX ~ 7XXX
     80XX ~ 86XX
     870X ~ 875X
     8760 ~ 8765

     Time Complexity:
     the number of permutations A(m,n) is O(1)
     We count digit by digit, so it's O(logN)
    */
    
    int doit(int N) {
        

        vector<int> digits;
        int num = N + 1;
        while (num > 0) {
            digits.insert(digits.begin(), num % 10);
            num /= 10;
        }
        
        int n = digits.size(), res = 0;
        
        for (size_t i = 1; i < n; i++) {
            int r = 9 * d(9, i -1);
            res += r;
        }
        
        unordered_set<int> sd;
        for (int i = 0; i < digits.size(); i++) {
            for (int y = i == 0 ? 1 : 0; y < digits[i]; y++) {
                if (sd.count(y) == 0)
                    res += d(9-i, n - i - 1);
            }
            
            if (sd.count(digits[i]) != 0)
                break;
            
            sd.insert(digits[i]);
        }
        
        return N - res;
    }
    
    // cal  m, how many digits we can use, n, how many number we need to remove
    int d(int m, int n) {
        return n == 0 ? 1 : d(m, n-1) * (m - n + 1);
    }
};

void test_1012_Numbers_with_repeated_digits() {
    
    auto res1 = NumDupDigitsAtMostN().doit(20);
    
    auto res3 = NumDupDigitsAtMostN().doit(8765);
    
    return;
}
