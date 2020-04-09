/*
 906. Super Palindromes
 
 Let's say a positive integer is a superpalindrome if it is a palindrome, and it is also the square of a palindrome.

 Now, given two positive integers L and R (represented as strings), return the number of superpalindromes in the inclusive range [L, R].

  

 Example 1:

 Input: L = "4", R = "1000"
 Output: 4
 Explanation: 4, 9, 121, and 484 are superpalindromes.
 Note that 676 is not a superpalindrome: 26 * 26 = 676, but 26 is not a palindrome.
 
 */

#include <string>
using std::string;

#include <math.h>

#include <vector>
using std::vector;

#include <queue>
using std::queue;

class SuperPalindromesInRange {
    
public:
    
    int doit1(string L, string R) {
        long double lb = sqrtl(stol(L)), ub = sqrtl(stol(R));
        int ans = lb <= 3 && 3 <= ub;
        queue<std::pair<long, int>> q;
        q.push({1, 1}), q.push({2, 1});
        while (true) {
            auto p = q.front(); q.pop();
            long x = p.first, len = p.second;
            if (x > ub) break;
            long W = powl(10, (len + 1) / 2);
            if (x >= lb) ans += is_palindrome(x * x);
            long r = x % W, l = x - (len % 2 ? x % (W / 10) : r);
            if (len % 2)
                q.push({10 * l + r, len + 1});
            else
                for (int d = 0; d <= 2; d++)
                    q.push({10 * l + d * W + r, len + 1});
        }
        return ans;
    }
    
private:
    bool is_palindrome(long x) {
        if (x == 0)
            return true;
        if (x % 10 == 0)
            return false;
        long left = x, right = 0;
        
        while (left >= right) {
            if (left == right || left / 10 == right)
                return true;
            
            right = 10 * right + (left % 10), left /= 10;
        }
        return false;
    }
    
public:
    int doit(string L, string R) {
        
        int ans = 0;
        // int lnum = std::stoi(L), rnum = std::stoi(R);
        char* pEnd;
        long long int lnum = strtoll(L.c_str(), &pEnd, 10);
        long long int rnum = strtoll(R.c_str(), &pEnd, 10);
        
        vector<long long int> sequence = {1, 2};
        if (lnum <= 9 && 9 <= rnum)
            ans++;
        
        auto is_Palindromes = [](long long int a){
            
            string tmp = std::to_string(a);
            int l = 0, r = int(tmp.size()) - 1;
            
            while (l < r) {
                if (tmp[l] != tmp[r])
                    return false;
                l++;
                r--;
            }
            
            return true;
        };
        
        auto reverse_string = [](string a) {
            int l = 0, r = a.length()-1;
            while (l < r) {
                std::swap(a[l], a[r]);
                l++, r--;
            }
            return a;
        };
        
        for (size_t i = 0; i < sequence.size(); i++) {
            long long int s = sequence[i];
            if (s * s > rnum)
                break;
            
            if (s * s >= lnum && is_Palindromes(s * s))
                ans++;
            
            string snum = std::to_string(s);
            int left = snum.length() / 2;
            int odd = snum.length() % 2;
            
            if (odd == 1) {
                string tmp = snum.substr(0, left+1) + reverse_string(snum.substr(0, left+1));
                sequence.push_back( strtoll(tmp.c_str(), &pEnd,10) );
            } else {
                for (auto c : {'0', '1', '2'}) {
                    
                    string tmp = snum.substr(0, left) + c + reverse_string(snum.substr(0,left));
                    sequence.push_back(strtoll(tmp.c_str(), &pEnd,10) );
                }
            }
        }
        
        return ans;
    }
};


void test_906_SuperPalindromes() {
    
    auto res = SuperPalindromesInRange().doit("4", "1000");
    
    auto re1 = SuperPalindromesInRange().doit("398904669", "13479046850");
}
