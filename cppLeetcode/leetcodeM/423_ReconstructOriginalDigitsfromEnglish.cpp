/*
423. Reconstruct Original Digits from English


Given a string s containing an out-of-order English representation of digits 0-9, return the digits in ascending order.

 

Example 1:

Input: s = "owoztneoer"
Output: "012"
Example 2:

Input: s = "fviefuro"
Output: "45"
 

Constraints:

1 <= s.length <= 105
s[i] is one of the characters ["e","g","f","i","h","o","n","s","r","u","t","w","v","x","z"].
s is guaranteed to be valid.

*/


#include <string>
#include <unordered_map>
#include <vector>

using std::vector;
using std::string;
using std::unordered_map;


class OriginalDigits {

    /*
        423.Reconstruct-Original-Digits-from-English
        此题不必用DFS蛮干，有非常巧妙的解法。

        观察0,2,4,6,8,对应的单词zero,two,four,six,eight. 可以发现对应的z,w,r,x,g这个五个字母都是各自独有的（考虑全部十个单词）。 所有在一个长字符串中，有多少z,w,r,x,g,就说明了正好有多少个0,2,4,6,8.

        那剩下的五个单词数目如何确定呢？其实，在长字符串中刨除了之前说的这五个单词之后，"five","seven","one","three","nine" 又“依次”“分别”有各自的特征字母f,v,o,h,i。
        也就是说除去这个单词后，剩下的有多少个字母f，就说明有多少个5；再除去所有5之后，剩下的有多少v，就说明有多少个7，依次类推。
    */
    string originalDigits(string s) 
    {
        vector<string>words={"zero","two","four","six","eight","five","seven","one","three","nine"};
        vector<int>nums={0,2,4,6,8,5,7,1,3,9};
        vector<int>distinct={'z','w','u','x','g','f','v','o','h','i'};
        vector<int>str(26,0);
        string result;
        
        for (auto ch:s) str[ch-'a']++;
        for (int i=0; i<10; i++)
        {
            int k = str[distinct[i]-'a'];            
            
            for (int j=0; j<k; j++)
                result+=std::to_string(nums[i]);

            for (auto ch: words[i])            
                str[ch-'a']-=k;
        }
        
        sort(result.begin(),result.end());
        
        return result;
    }

public:

    string originalDigits(string s) {
        
        unordered_map<char, int> cnt;
        for (auto c : s) cnt[c]++;

        vector<string> nums{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
        unordered_map<char, int> index{ {'z',0}, {'x', 6}, {'w', 2}, {'u', 4}, {'g', 8}, {'f', 5}, {'r', 3}, {'o', 1}, {'v', 7}, {'i',9} };
        string priority = "zxwugfrovi";
        string ans;

        for (auto c : priority) {

            if (cnt.count(c) == 0) continue;

            int k = cnt[c];

            for (auto w : nums[index[c]]) {
                cnt[w] -= k;
            }

            while (k--) ans.push_back(index[c] + '0');


        }

        sort(begin(ans), end(ans));

        return ans;
    }
};