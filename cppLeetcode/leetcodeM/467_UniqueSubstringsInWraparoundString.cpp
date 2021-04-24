/*
467. Unique Substrings in Wraparound String


Consider the string s to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so s will look like this: "...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".

Now we have another string p. Your job is to find out how many unique non-empty substrings of p are present in s. 
In particular, your input is the string p and you need to output the number of different non-empty substrings of p in the string s.

Note: p consists of only lowercase English letters and the size of p might be over 10000.

Example 1:
Input: "a"
Output: 1

Explanation: Only the substring "a" of string "a" is in the string s.
Example 2:
Input: "cac"
Output: 2
Explanation: There are two substrings "a", "c" of string "cac" in the string s.
Example 3:
Input: "zab"
Output: 6
Explanation: There are six substrings "z", "a", "b", "za", "ab", "zab" of string "zab" in the string s.

*/

#include <vector>
#include <string>
#include <unordered_map>

using std::vector;
using std::unordered_map;
using std::string;

class UniqueSubstringsinWraparoundString {


    int findSubstringInWraproundString_best(string p) {
        
        if(p.empty()==true) return 0;
        
        vector<int> buf(26, 0);
        int prev = 1;
        buf[p[0]-'a']=1;
        
        for(int i=1; i<p.size(); i++){
            if(p[i]-p[i-1]==1||(p[i]=='a'&&p[i-1]=='z')){
                prev++;
            }
            else{
                prev=1;
            }

            buf[p[i]-'a'] = std::max(buf[p[i]-'a'],prev);
        }

        int res=0;
        for(int i = 0; i < 26; i++)
            res += buf[i];

        return res;
    }

    /*
        467.Unique-Substrings-in-Wraparound-String
        注意s串的性质，其子串必然是递增的。发现这一点后，只要是在p中的所有递增子串，都是s的字串。

        那么p中有多少不同的递增子串呢？任何不同的递增字串，只需要两个参数就能确定其独特性。一个是起始字符，另一个是字串的长度。于是只要遍历p的每一个字符，找出以其为开头的最长递增字串即可。
        比如说p中以'a'开头的递增字串的最大长度是n，那么就有n种不同的以'a'开头的递增字串。

        创建一个Hash表，遍历p[i]。以遍历的字符p[i]作为key，记录以p[i]开头的递增字串的最大长度（这个value会随着p的遍历而不断被更新）。最终结果就是把所有key的value都加起来。
    */
    int findSubstringInWraproundString(string p) 
    {
        unordered_map<char,int>Map;
        for (int i=0; i<p.size(); i++)
        {
            int j=i;
            while (j+1<p.size() && (p[j+1]==p[j]+1 || p[j]=='z' && p[j+1]=='a'))
                j++;
                
            if (j-i+1>Map[p[i]])
                Map[p[i]]=j-i+1;            
        }
        
        int result=0;
        for (auto a:Map)
            result+=a.second;
        return result;
    }
};