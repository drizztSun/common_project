/*
1234. Replace the Substring for Balanced String

You are given a string containing only 4 kinds of characters 'Q', 'W', 'E' and 'R'.

A string is said to be balanced if each of its characters appears n/4 times where n is the length of the string.

Return the minimum length of the substring that can be replaced with any other string of the same length to make the original string s balanced.

Return 0 if the string is already balanced.

 

Example 1:

Input: s = "QWER"
Output: 0
Explanation: s is already balanced.
Example 2:

Input: s = "QQWE"
Output: 1
Explanation: We need to replace a 'Q' to 'R', so that "RQWE" (or "QRWE") is balanced.
Example 3:

Input: s = "QQQW"
Output: 2
Explanation: We can replace the first "QQ" to "ER". 
Example 4:

Input: s = "QQQQ"
Output: 3
Explanation: We can replace the last 3 'Q' to make s = "QWER".
 

Constraints:

1 <= s.length <= 10^5
s.length is a multiple of 4
s contains only 'Q', 'W', 'E' and 'R'.
*/
#include <string>
#include <map>

using std::map;
using std::string;

class BalancedString {

public:

    int balancedString(string s) {
        
        map<int, int> cnt;
        for (auto c: s)
            cnt[c]++;
        
        int larger = 0;
        int ave = s.size() / 4;
        for (auto c : "QWER") {
            if (cnt[c] > ave) larger += 1;
        }
        
        if (larger == 0) return 0;
        
        int i = 0, ans = s.size();
        for (int j = 0; j < s.size(); j++) {
            
            cnt[s[j]] -= 1;
            if (cnt[s[j]] == ave)
                larger -= 1;
            
            while (i <= j && larger == 0) {
                ans = std::min(ans, j - i + 1);
                cnt[s[i]] += 1;
                if (cnt[s[i]] == ave + 1) {
                    larger += 1;
                }
                i += 1;
            }
        }
        
        return ans;
    }

    bool checker(int*count , int*current)
    {
        for(int i=0;i<4;++i)
            if(count[i] && current[i]<count[i]) return 0;
        return 1;
    }

    void counter(int *count,char &ch,bool sign)
    {
        int val=1;
        if(sign) val=-1;
        
        if(ch=='Q')
            count[0]+=val;
        else if(ch=='W')
            count[1]+=val;
        else if(ch=='E')
            count[2]+=val;
        else
            count[3]+=val;
    }
    
    int doit_(string s) {

        int len = s.length();
        int count[4] = {0,0,0,0}; // Q:0 , W:1 , E:2, R:3
        // finding count of characters
        for(int i=0;i<len;++i)
           counter(count,s[i],0);
        
        int ans = INT_MAX, val = len/4; // val is the required number of count of each character
        
        for(int i=0;i<4;++i)     // here we try to find count of char that occur more than len/4 times as they can be replaced to compensate others
            count[i] -= val;
        
        // check to see if there are any extra characters
        int b=0;
        for(;b<4;++b)
            if(count[b]>0) break;
        
        if(b==4) return 0; // no extra chars
        
        b=0;
        int current[4] = {0,0,0,0};
        
        // we need to find the smallest substring that contains extra characters left in count array
        for(int i=0;i<len;++i)
        {
            counter(current,s[i],0);
            if(checker(count,current))
            {
                while(checker(count,current))
                {
                    ans = std::min(ans,i-b+1);
                    counter(current,s[b],1);
                    b++;
                }
            }
        }
        return ans;
    }
};