/*
1698. Number of Distinct Substrings in a String


Given a string s, return the number of distinct substrings of s.

A substring of a string is obtained by deleting any number of characters (possibly zero) from the front of the string and any number (possibly zero) from the back of the string.

 

Example 1:

Input: s = "aabbaba"
Output: 21
Explanation: The set of distinct strings is ["a","b","aa","bb","ab","ba","aab","abb","bab","bba","aba","aabb","abba","bbab","baba","aabba","abbab","bbaba","aabbab","abbaba","aabbaba"]
Example 2:

Input: s = "abcdefg"
Output: 28
 

Constraints:

1 <= s.length <= 500
s consists of lowercase English letters.
 

Follow up: Can you solve this problem in O(n) time complexity?

*/
#include <string>
#include <unordered_set>

using std::unordered_set;
using std::string;


class CountDistinct {

    /*
                1698.Number-of-Distinct-Substrings-in-a-String
        这道题的暴力方法是枚举所有的substring，然后存储在集合里。虽然看上去时间复杂度是o(N^2)，但是对于长字符串的集合存储和查询的开销非常大，事实上不可以用o(1)时间来忽略。

        解法1：Trie
        我们在考虑类似axxxxaxxxxx的字符串时，需要解决的一个问题是，以第二个a开头的子串axxx是否会和以第一个a开头的子串axxx重复。为了避免用字符串集合来暴力查询，我们可以用字典树。
        我们在处理第一个a时，就把以其为开头的substring存入一个trie（此时这个trie没有任何分支，应该是一条长链）。这样当我们处理以第二个a为开头的substring时，就从trie里顺着a这条分支往下走，如果有任何重合的部分，都不算distinct substring。直至当前的substring延伸到一定程度之后不再与Trie中的已有路径重合，我们就在Trie里继续往下开辟新的路径和节点。同时每开辟新的一层，就意味着多了一个distinct substring。

        这种做法的时间复杂度也是真o(N^2)，每个基本操作就是遍历或创建Trie节点。但是当大量开辟动态空间时，也会造成TLE。

        解法2：Rolling Hash
        我们考虑固定长度len的滑窗，将滑窗范围内的字符串encode成一个数字放入集合里，就可以快速判断这个字符串是否之前出现过。编码的方法就是将这个字符串看成一个26进制的数，注意取模。窗口滑动的时候，针对老编码，用o(1)的时间加上新字符、减去老字符，就可以得到新的编码。
    */

    struct TrieNode{
        TrieNode* next[26];
    };

    int countDistinct(string s) 
    {
        TrieNode* root = new TrieNode();
        int count = 0;
        for (int i=0; i<s.size(); i++)
        {
            TrieNode* node = root;
            for (int j=i; j<s.size(); j++)
            {
                if (node->next[s[j]-'a']==NULL)
                {
                    node->next[s[j]-'a'] = new TrieNode();
                    count ++;
                }
                node = node->next[s[j]-'a'];
            }            
        }
        return count;        
    }

    int countDistinct(string s) 
    {
        int n = s.size();
        long base = 26;
        long M = 1e9+7;
        int count = 1;
        long power = 1;
        long hash0 = 0;
        
        for (int len = 1; len <=n-1; len++)
        {            
            hash0 = (hash0 * base % M + s[len-1]-'a') % M;            
            power = (power * base) % M;
            
            unordered_set<long>Set({hash0});
            long hash = hash0;            
            for (int i=len; i<n; i++)
            {
                hash = (hash * base % M + (s[i]-'a')) % M; 
                hash = (hash - power*(s[i-len]-'a') % M + M) %M ;
                Set.insert(hash);
            }
            count += Set.size();
        }
        return count;
    }

public:

    /*
        
    def build_lcp(self, s, sa):
        """
        Kasai algorithm to build LCP
        s: string
        sa: suffix array
        rank: inverse suffix array

        k: number of common prefixes between suffixes
        """
        n = len(sa)
        rank = [0] * n
        for i in range(n):
            rank[sa[i]] = i

        k = 0
        lcp = [0] * n
        for i in range(n):
            if rank[i] == n - 1:
                k = 0
                continue
            j = sa[rank[i] + 1]
            while i + k < n and j + k < n and s[i + k] == s[j + k]:
                k += 1
            lcp[rank[i]] = k
            k = max(k - 1, 0)
        return lcp

    def sort_bucket(self, s, buckets, order):
        d = defaultdict(list)
        for bucket in buckets:
            key = s[bucket : bucket + order]
            d[key].append(bucket)

        result = []
        for k, v in sorted(d.items()):
            if len(v) > 1:
                result.extend(self.sort_bucket(s, v, order << 1))  # or `order * 2`
            else:
                result.append(v[0])

        return result

    def suffix_array_manber_myers(self, s):
        return self.sort_bucket(s, (range(len(s))), 1)

    def countDistinct(self, s: str) -> int:
        """
        Example:
        -----
        String: azaza
        -----
        Total number of substrings: n(n + 1) / 2
        -------------------
        a az aza azaz azaza
        z za zaz zaza
        a az aza
        z za
        z
        --------------------
        15
        """
        sa = self.suffix_array_manber_myers(s)
        lcp = self.build_lcp(s, sa)
        n = len(s)
        return ((n * (n + 1)) // 2) - sum(lcp)
    
    */
    
    int doit_(string target) {

        


    }
};