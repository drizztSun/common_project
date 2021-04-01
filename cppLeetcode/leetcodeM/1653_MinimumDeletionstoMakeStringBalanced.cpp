/*
1653. Minimum Deletions to Make String Balanced


You are given a string s consisting only of characters 'a' and 'b'​​​​.

You can delete any number of characters in s to make s balanced. s is balanced if there is no pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.

Return the minimum number of deletions needed to make s balanced.

 

Example 1:

Input: s = "aababbab"
Output: 2
Explanation: You can either:
Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").
Example 2:

Input: s = "bbaaaaabb"
Output: 2
Explanation: The only solution is to delete the first two characters.
 

Constraints:

1 <= s.length <= 10^5
s[i] is 'a' or 'b'​​.
*/

#include <string>
#include <vector>

using std::vector;
using std::string;



class MinimumDeletions {

    /*
        1653.Minimum-Deletions-to-Make-String-Balanced
        注意到最终变换后的形式是"aaaa....bbbbb"，关键点就是这个ab的分界处。所以我们遍历这个分界点：假设最终状态是[0:i]都变成'a'，[i+1:n-1]都变成'b'，那么所需要的操作数，
        就是[0:i]中'b'的个数加上[i+1:n-1]中'a'的个数。对于这两个量，我们可以提前two pass预处理以前缀和/后缀和数组的形式存下来，即ret[i] = pre[i]+suf[i+1]。

        本题有两个corner cases，分别是把所有的字母变成a或者b，对应的是pre[n-1]和suf[0]，这需要单独考察。
    */
    int minimumDeletions(string s) 
    {
        int n = s.size();

        vector<int>pre(n);        
        pre[0] = (s[0]=='b');

        for (int i=1; i<n; i++)
            pre[i] = pre[i-1] + (s[i]=='b');
        
        vector<int>suf(n);
        suf[n-1] = (s[n-1]=='a');
        for (int i=n-2; i>=0; i--)
            suf[i] = suf[i+1] + (s[i]=='a');
        
        int ret = std::min(pre[n-1], suf[0]);
        for (int i=0; i<n-1; i++)
            ret = std::min(ret, pre[i] + suf[i+1]);
        
        return ret;
    }

public:

    /*
        Greedy. Use bCnt to record count for preserved b (have no way to be replaced by a) up till now, use res to record deletion count.

        Traverse string s, for each char ch:
        (1) If it's b, we don't know whether to delete it or not, only increase bCnt by 1.
        (2) If it's a, we will make deletion only when bCnt is > 0, which means there're b preserved before and has no way to be replaced by traversed a. 
        We might delete current a, or delete previous b, but we don't know yet since this is decided by furture remainig chars. 
        But no matter what we delete, the deletion cnt res will always increase by 1. Use the greedy idea, even if we delete current a, still decrease bCnt by 1 to indicate this b can be replaced by a if later we need it to be replaced

        eg1. aabba
        aabb -> res = 0, bCnt = 2;
        aabba -> res = 1, bCnt = 1;
        ans: aabb

        eg2. aabbaaa
        aabb -> res = 0, bCnt = 2;
        aabba -> res = 1, bCnt = 1 (aabb, or aaba)
        aabbaa -> res = 2, bCnt = 0 (aabb, or aaaa)
        aabbaaa -> res = 2, bCnt = 0 (aaaaa)
    */

    int doit_greedy(string s) {

        int b = 0, res = 0;

        for (auto c: s) {
            
            if (c == 'b') {
                b++;
            } else if (c == 'a' && b > 0) {
                // abbbaaaaaabbbaabbbbb, we always keep left side is a, right side is b.
                // first three bbb, when we meet a, we submit 1, it means we submit a 'b' or a 'a' is which one is less
                // then next "bbbaa" is same we can think anout like just submitting the less one.
                // when meet an 'a', we submit one, less 'a' trigger will left 'b'. the more 'a' trigger, but at most b is back to zero, because we check b > 0. 
                // we always remove shorter part.
                b--;
                res++;
            }
        }
        return res;
    }
};
