/*
1525. Number of Good Ways to Split a String


You are given a string s, a split is called good if you can split s into 2 non-empty strings p and q where its concatenation is equal to s and the number of distinct letters in p and q are the same.

Return the number of good splits you can make in s.

 

Example 1:

Input: s = "aacaba"
Output: 2
Explanation: There are 5 ways to split "aacaba" and 2 of them are good. 
("a", "acaba") Left string and right string contains 1 and 3 different letters respectively.
("aa", "caba") Left string and right string contains 1 and 3 different letters respectively.
("aac", "aba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aaca", "ba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aacab", "a") Left string and right string contains 3 and 1 different letters respectively.
Example 2:

Input: s = "abcd"
Output: 1
Explanation: Split the string as follows ("ab", "cd").
Example 3:

Input: s = "aaaaa"
Output: 4
Explanation: All possible splits are good.
Example 4:

Input: s = "acbadbaada"
Output: 2
 

Constraints:

s contains only lowercase English letters.
1 <= s.length <= 10^5
*/
#include <string>
#include <vector>

using std::vector;
using std::string;


class NumSplits {

    /*
        1525.Number-of-Good-Ways-to-Split-a-String
        遍历p和q的分界点的位置i。我们可以提前用two pass计算出i左边的字符种类数left[i]，i右边的字符种类数right[i]。然后第三次遍历所有位置i，检查当left[i]==right[i]的时候，说明在此处划分字符串是符合要求的。
    */
    int numSplits(string s) 
    {
        int n = s.size();
        vector<int>left(n,0);
        vector<int>right(n,0);
        
        vector<int>count(26,0);
        int sum = 0;
        for (int i=0; i<s.size(); i++)
        {
            count[s[i]-'a']+=1;
            if (count[s[i]-'a']==1)
                sum+=1;
            left[i] = sum;
        }
        
        count.assign(26,0);
        sum = 0;
        for (int i=s.size()-1; i>=0; i--)
        {
            count[s[i]-'a']+=1;
            if (count[s[i]-'a']==1)
                sum+=1;
            right[i] = sum;
        }
        
        int ret = 0;
        for (int i=0; i<s.size()-1; i++)
        {
            if (left[i]==right[i+1])
                ret+=1;
        }
        return ret;
    }


public:

    int doit_hashtable_greedy(string s) {
        
        int total[26] = {}, left[26] = {}, ans = 0;
        for (char c : s) total[c - 'a']++;
        
        for (char c : s) {
            ++left[c - 'a'];
            int L = 0, R = 0;
            for (int i = 0; i < 26; ++i) {
                if (left[i]) ++L;
                if (total[i] - left[i]) ++R;
            }
            if (L == R) ++ans;
            if (L > R) break;
        }
        return ans;
    }
};