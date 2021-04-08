/*
 
 902. Numbers At Most N Given Digit Set
 
 We have a sorted set of digits D, a non-empty subset of {'1','2','3','4','5','6','7','8','9'}.  (Note that '0' is not included.)

 Now, we write numbers using these digits, using each digit as many times as we want.  For example, if D = {'1','3','5'}, we may write numbers such as '13', '551', '1351315'.

 Return the number of positive integers that can be written (using the digits of D) that are less than or equal to N.

  

 Example 1:

 Input: D = ["1","3","5","7"], N = 100
 Output: 20
 Explanation:
 The 20 numbers that can be written are:
 1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.
 Example 2:

 Input: D = ["1","4","9"], N = 1000000000
 Output: 29523
 Explanation:
 We can write 3 one digit numbers, 9 two digit numbers, 27 three digit numbers,
 81 four digit numbers, 243 five digit numbers, 729 six digit numbers,
 2187 seven digit numbers, 6561 eight digit numbers, and 19683 nine digit numbers.
 In total, this is 29523 integers that can be written using the digits of D.
  
 
 */

#include <vector>
#include <string>
#include<math.h>
#include<algorithm>

using std::vector;
using std::string;


class AtMostNGivenDigitSet {

    /*
        902.Numbers-At-Most-N-Given-Digit-Set
        可以用常规的DFS的方法将所有小于N的数都访问（构造）一遍，但是当N很大的时候就很低效。

        比较高效的解法是多利用数学计算。假设数字N的位数是K，那么意味着任何小于K位的整数都不可能大于N，我们可以直接累加小于K位的整数的个数。

        然后我们只需考虑K位的整数里有多少小于N的。我们可以从最高位开始递归构造。当选择的第i位上的数字小于num[i]的时候，剩余的K-i位数字可以任取，总数肯定不会超过N，因此可以直接加上count+=pow(D.size(), K-i)。当选择的第i位上的数字确定为num[i]的时候，我们就递归处理下一位即可。

        注意在边界条件，当处理完所有的K位之后，这意味一路都是贴着上限走过来的，必须还要count+=1。这个代表着恰好所构造出来的上限N。
    */
    int count = 0;
    string num;
    int K;
    
    int atMostNGivenDigitSet(vector<string>& D, int N) 
    {
        num = to_string(N);
        K = num.size();
        
        for (int i=1; i<=K-1; i++)
            count += pow(D.size(), i);
        
        DFS(0, 0, D);
        
        return count;
    }
    
    void DFS(long cur, int pos, vector<string>& D)
    {
        if (pos==K)
        {
            count+=1;
            return;
        }
        
        for (string s: D)
        {
            if ('0'+stoi(s) < num[pos])
                count += pow( D.size(), K-1-pos);
            else if ('0'+stoi(s) == num[pos])
                DFS(cur*10+stoi(s), pos+1, D);            
        }               
    }

public:

    int doit_(vector<string>&& D, int N) {

        vector<int> digits;
        while (N>0) {
            digits.push_back(N%10);
            N /= 10;
        }
        int L = digits.size();
        int dp = 1;
        int nums = D.size();
        
        for (int i = 0; i < L; i++) {
            int tmp = 0;
            for (auto& c : D) {
                int n = std::stoi(c);
                if ( n < digits[i] ) {
                    tmp += pow(nums, i);
                } else if (n == digits[i]) {
                    tmp += dp;
                }
            }
            
            dp = tmp;
        }
        
        for (int i = 1; i < L; i++) {
            dp += pow(nums, i);
        }
        
        return dp;
    }
    
    
    int doit1(vector<string>& D, int N, bool flag = false) {
        int count = 0;
        string num = std::to_string(N);

        // 位数小于 N 的一定 比 N 小
        for(int i = 1; !flag && i < num.size(); ++i)
        {
            count += pow(D.size(), i);
        }

        // 位数和 N 一样的
        for(int i = 0; i < D.size(); ++i)
        {
            if(num[0] > D[i][0]) // 第一位小于 N
            {
                count += pow(D.size(), num.size()-1);
            }
            else if(num[0] == D[i][0]) //第一位等于 N
            {
                string subNum = num.substr(1, num.size());
                if(subNum.empty()) { ++count; continue; }
                else if(subNum[0] == '0') continue; // 首数字为 0
                count += doit1(D, stoi(subNum), true);
            }
        }

        return count;
    }
};