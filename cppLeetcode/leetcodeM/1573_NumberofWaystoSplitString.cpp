/*
1573. Number of Ways to Split a String

Given a binary string s (a string consisting only of '0's and '1's), we can split s into 3 non-empty strings s1, s2, s3 (s1+ s2+ s3 = s).

Return the number of ways s can be split such that the number of characters '1' is the same in s1, s2, and s3.

Since the answer may be too large, return it modulo 10^9 + 7.

 

Example 1:

Input: s = "10101"
Output: 4
Explanation: There are four ways to split s in 3 parts where each part contain the same number of letters '1'.
"1|010|1"
"1|01|01"
"10|10|1"
"10|1|01"
Example 2:

Input: s = "1001"
Output: 0
Example 3:

Input: s = "0000"
Output: 3
Explanation: There are three ways to split s in 3 parts.
"0|0|00"
"0|00|0"
"00|0|0"
Example 4:

Input: s = "100100010100110"
Output: 12
 

Constraints:

3 <= s.length <= 10^5
s[i] is '0' or '1'.

*/

#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;


class WaysToSplitNumbers {

    /*
        1573.Number-of-Ways-to-Split-a-String
        基本思想是统计字符串内的“1”的个数count。首先我们必须要count%3==0才能实现满足题意的分割。

        接下来我们知道，第一个cut必然位于第count/3个“1”和第count/3+1个“1”之间。第二个cut必然位于第count/32个“1”和第count/32+1个“1”之间。数一下分别有几个可供插入的位置，两者的成绩就是答案。如何快速定位第count/3个“1”在哪里呢？其实在之前统计的时候，就可以用一个hash表存储count到index的映射，这样可以快速定位。

        此外，还有一个corner case，就是当字符串全为0的时候。这时候有n-1个空位，可以任意选择两个进行cut。所以答案要加上(n-1)*(n-2)/2.
    */
    int numWays(string s) 
    {
        long ret = 0;
        long M = 1e9+7;

        unordered_map<int,int>Map;     
        int count = 0;   
        for (int i=0; i<s.size(); i++)
        {
            if (s[i]=='1') 
            {
                count++;
                Map[count] = i;
            }
        }            
        if (count%3!=0) return 0;
        long n = s.size();
        if (count==0) return (n-1)*(n-2)/2%M;

        long x = Map[count/3+1] - Map[count/3];
        long y = Map[count/3*2+1] - Map[count/3*2];
        return x*y%M;
    }
public:

    int doit_(string s) {
        
        int n = s.size();
        int total = 0;
        for (auto c: s) total += c == '1'? 1 : 0;
        
        int hmod = 1e9+7;
        if (total == 0) return (long(n-1) * long(n-2) / 2) % hmod; 
        
        if (total % 3 != 0) return 0;
        
        int ave = total / 3;
        
        long cnt1 = 0, cnt2= 0;
        total = 0;
        
        for (int i = 0; i < s.size(); i++) {
            
            total += s[i] == '1';
            
            if (total == 2*ave + 1) {
                break;
            } else if (total == 2 * ave) {
                cnt2++;
            } else if (total == ave) {
                cnt1++;
            }
        }
        
        return cnt1 * cnt2 % hmod;
    }
};