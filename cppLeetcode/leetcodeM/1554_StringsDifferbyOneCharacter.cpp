/*
1554. Strings Differ by One Character

Given a list of strings dict where all the strings are of the same length.

Return True if there are 2 strings that only differ by 1 character in the same index, otherwise return False.

Follow up: Could you solve this problem in O(n*m) where n is the length of dict and m is the length of each string.

 

Example 1:

Input: dict = ["abcd","acbd", "aacd"]
Output: true
Explanation: Strings "abcd" and "aacd" differ only by one character in the index 1.
Example 2:

Input: dict = ["ab","cd","yz"]
Output: false
Example 3:

Input: dict = ["abcd","cccc","abyd","abab"]
Output: true
 

Constraints:

Number of characters in dict <= 10^5
dict[i].length == dict[j].length
dict[i] should be unique.
dict[i] contains only lowercase English letters.


*/

#include <string>
#include <vector>
#include <unordered_set>

using std::string;
using std::vector;
using std::unordered_set;


class DifferByOne {

    /*
        1554.Strings-Differ-by-One-Character
        考虑这个例子:{123,124,134,213}. 如何快速判断是否有两个数字只差别一个digit？

        比较简单的方法就是：抹去所有的个位数，查看剩下的数值{120,120,130,210}，将它们一次加入集合，就可以判断出是否有重复元素。
        如果没有发现，我们可以抹去十位数，得到的是{103,104,104,203}，同理可以判断是否有重复元素... 对于任何位置的digit，我们一旦发现抹去之后剩余的数值有重复，那么就意味着至少有一对数字只差别这一位digit。

        本题就是把上述思想扩展到字符串。用rolling hash的方法给每个字符串完整编码。然后逐位考察每一位的数字，将每个字符串的完整编码抹去那一位的编码，查看剩下的编码是否有重复即可。
    */
    bool differByOne(vector<string>& dict) 
    {
        long base = 261;
        long M = 1e9+7;
        int n = dict.size();
        int m = dict[0].size();
        vector<long>hash(n);
        for (int i=0; i<n; i++)
        {
            int h = 0;
            for (int j=0; j<m; j++)
                h = (h*base+dict[i][j]-'a')%M;
            hash[i] = h;
        }
        
        long K = 1;
        for (int j=m-1; j>=0; j--)
        {
            unordered_set<long>Set;            
            
            for (int i=0; i<n; i++)
            {
                long h = (hash[i] + M - (dict[i][j]-'a') * K % M) %M;
                if (Set.find(h)!=Set.end())
                    return true;
                Set.insert(h);
            }
            K = K*base%M;
        }
        
        return false;
    }

public:
    
    bool doit_hashtable(vector<string>& dict) {
        
        unordered_set<string> buf;
        
        for (auto& word: dict) {
            
            for (int i = 0; i < word.length(); i++) {
                
                string tmp = word.substr(0, i) + '*' + word.substr(i+1);
                
                if (buf.count(tmp) > 0) return true;
                
                buf.insert(tmp);
            }
        }
        
        return false;
    }
};