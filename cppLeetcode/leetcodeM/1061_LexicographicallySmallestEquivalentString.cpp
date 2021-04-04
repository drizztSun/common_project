/*
1061. Lexicographically Smallest Equivalent String

Given strings A and B of the same length, we say A[i] and B[i] are equivalent characters. For example, if A = "abc" and B = "cde", then we have 'a' == 'c', 'b' == 'd', 'c' == 'e'.

Equivalent characters follow the usual rules of any equivalence relation:

    . Reflexivity: 'a' == 'a'
    . Symmetry: 'a' == 'b' implies 'b' == 'a'
    . Transitivity: 'a' == 'b' and 'b' == 'c' implies 'a' == 'c'

For example, given the equivalency information from A and B above, S = "eed", "acd", and "aab" are equivalent strings, and "aab" is the lexicographically smallest equivalent string of S.

Return the lexicographically smallest equivalent string of S by using the equivalency information from A and B.

 

Example 1:

Input: A = "parker", B = "morris", S = "parser"
Output: "makkek"
Explanation: Based on the equivalency information in A and B, we can group their characters as [m,p], [a,o], [k,r,s], [e,i]. The characters in each group are equivalent and sorted in lexicographical order. So the answer is "makkek".
Example 2:

Input: A = "hello", B = "world", S = "hold"
Output: "hdld"
Explanation:  Based on the equivalency information in A and B, we can group their characters as [h,w], [d,e,o], [l,r]. So only the second letter 'o' in S is changed to 'd', the answer is "hdld".
Example 3:

Input: A = "leetcode", B = "programs", S = "sourcecode"
Output: "aauaaaaada"
Explanation:  We group the equivalent characters in A and B as [a,o,e,r,s,c], [l,p], [g,t] and [d,m], thus all letters in S except 'u' and 'd' are transformed to 'a', the answer is "aauaaaaada".
 

Note:

String A, B and S consist of only lowercase English letters from 'a' - 'z'.
The lengths of string A, B and S are between 1 and 1000.
String A and B are of the same length.

*/

#include <vector>
#include <string>

using std::vector;
using std::string;



class SmallestEquivalentString {

    /*
        1061.Lexicographically-Smallest-Equivalent-String
        最基本的UF的模板题。我们根据A[i]和B[i]的"等效"关系进行Union，得到所有联通集合。对于每个集合，我们推选最小的字母作为代表。

        然后遍历S，对于每个字母，我们替换为它所在Union的代表字母。得到的就是字典序最小的“等效字符串”
    */
    int Father[26];
    int FindFather(int x)
    {
        if (Father[x]!=x)
            Father[x] = FindFather(Father[x]);
        return Father[x];
    }
    
    void Union(int x, int y)
    {
        x = Father[x];
        y = Father[y];
        if (x<y)
            Father[y] = x;
        else
            Father[x] = y;
    }
    
    string smallestEquivalentString(string A, string B, string S) 
    {
        for (int i=0; i<26; i++)
            Father[i] = i;
        
        for (int i=0; i<A.size(); i++)
        {
            if (FindFather(A[i]-'a')!=FindFather(B[i]-'a'))
                Union(A[i]-'a', B[i]-'a');
        }
        
        
        string ret;
        for (auto ch: S)
            ret.push_back('a'+FindFather(ch-'a'));
        
        return ret;
    }


public:

    string doit_disjoint(string A, string B, string S) {
        
        int n = A.length();
        vector<int> parent(26, -1);
        
        for (int i = 0; i < 26; i++)
            parent[i] = i;
        
        
        auto find = [&](int n) {
          
            while (n != parent[n]) {
                parent[n] = parent[parent[n]];
                n = parent[n];
            }
            
            return n;
        };
        
        auto merge = [&](int a, int b) {
            int pa = find(a), pb = find(b);
            if (pa < pb) 
                parent[pb] = pa;
            else
                parent[pa] = pb;
        };
        
        
        for (int i = 0; i < n; i++) {
            merge(A[i]-'a', B[i]-'a');    
        }
        
        string ans;
        for (int i = 0; i < S.length(); i++) {
            ans.push_back(find(S[i] - 'a') + 'a');
        }
        
        return ans;
    }
};