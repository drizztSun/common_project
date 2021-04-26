/*
1415. The k-th Lexicographical String of All Happy Strings of Length n


A happy string is a string that:

consists only of letters of the set ['a', 'b', 'c'].
s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is 1-indexed).
For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings and strings "aa", "baa" and "ababbc" are not happy strings.

Given two integers n and k, consider a list of all happy strings of length n sorted in lexicographical order.

Return the kth string of this list or return an empty string if there are less than k happy strings of length n.

 

Example 1:

Input: n = 1, k = 3
Output: "c"
Explanation: The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".
Example 2:

Input: n = 1, k = 4
Output: ""
Explanation: There are only 3 happy strings of length 1.
Example 3:

Input: n = 3, k = 9
Output: "cab"
Explanation: There are 12 different happy string of length 3 ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"]. You will find the 9th string = "cab"
Example 4:

Input: n = 2, k = 7
Output: ""
Example 5:

Input: n = 10, k = 100
Output: "abacbabacb"
 

Constraints:

1 <= n <= 10
1 <= k <= 100

*/
#include <vector>
#include <string>
#include <functional>
#include <unordered_set>

using std::unordered_set;
using std::string;
using std::vector;

class KthLexicographicalStringOfAllHappyString {

    /*
        1415.The-k-th-Lexicographical-String-of-All-Happy-Strings-of-Length-n
        解法1
        考虑到k只有不到100，可以暴力枚举出从小到大所有合法的字符串，取第k个。

        解法2
        更聪明点的递归。

        当我们尝试填写长度为n的字符串的首字母时，无论首字母是什么，之后的n-1位都有pow(2,n-1)种填写方法。所以我们用k/pow(2,n-1)就可以确定此时的首字母ch应该是字母表的第几个。注意这里的k应该用0-index更为方便。比如k=0，那么ch应该就是'a'，如果k=1，那么ch应该就是'b'.

        但是我们还需要考虑到之前一位的制约。如果发现计算得到的ch比上一位字母要大，那么意味着当前字母基数应该加1。因为此位我们不能尝试和前面一样的字母，所以会少pow(2,n-1)的可能性。
    */
    unordered_set<string>rets;
    string ans;
    int N,K;
public:
    string getHappyString(int n, int k) 
    {
        string s;
        ans = "";
        N = n;
        K = k;
        DFS(0,s);        
        return ans;
    }
    
    void DFS(int cur, string s)
    {
        if (cur==N)
        {
            rets.insert(s);
            if (rets.size()==K)
                ans = s;
            return;
        }
        
        if (ans!="") return;
        
        if (cur==0)
        {
            for (auto ch='a'; ch<='c'; ch++)
            {
                s.push_back(ch);
                DFS(cur+1, s);
                s.pop_back();
            }
        }
        else
        {
            for (auto ch='a'; ch<='c'; ch++)
            {
                if (ch==s.back()) continue;
                s.push_back(ch);
                DFS(cur+1, s);
                s.pop_back();
            }            
        }
    }


public:

    string ret;

    string getHappyString(int n, int k) 
    {      
        int total = pow(2,n-1)*3;
        if (k > total) return "";
        dfs(n, k-1);
        return ret;
    }

    void dfs(int n, long k)
    {
        if (n==0) return;

        int t = k / pow(2,n-1);
        char ch = 'a'+t;
        if (ret.size()>0 && ch>=ret.back())
            ch++;
        ret.push_back(ch);

        dfs(n-1, k - t*pow(2,n-1));
    }

public:
    
    string doit_dfs(int n, int k) {

        string s = "";
        vector<char> letters{'a','b','c'};
        string res;
        int count = 0;

        std::function<void(int, string&, char)> solve = [&](int n  , string& s , char last) {

            if(s.size() == n) {
                count++;
                if (count == k)
                    res = s;
                return;
            }

            for(int i = 0 ; i < 3; i++) {
                if(letters[i] != last) {
                    s += letters[i];
                    solve(n, s, letters[i]);
                    s.pop_back();
                }
            }
        };

        solve(n, s, '0');
        
        return k > count ? "": res;
    }


public:

    string doit_greedy(int n, int k) {
        
        int base = (1 << (n-1));
        
        if (k > 3*base) return "";
        
        string ans;
        
        if (base >= k) 
            ans += 'a';
        else if (2 * base >= k) {
            ans += 'b';
            k -= base; 
        } else {
            ans += 'c';
            k -= 2*base;
        }
        
        string push[3] = {"bc", "ac", "ab"};
        
        while (ans.length() < n) {
            
            base >>= 1;
            
            int idx = ans.back() - 'a';
            
            if (k > base) {
                ans.push_back(push[idx][1]);
                k -= base;
            } else
                ans.push_back(push[idx][0]);
        }
        
        return ans;
    }

    string doit_greedy(int n, int k) {

        // totoal is 
        int cnt = 3 * (1 << (n - 1));
        
        if (k > cnt) return "";
        
        string res;
        
        if (cnt / 3 >= k) 
            res.push_back('a');

        else if (2 * cnt / 3 >= k) 
            res.push_back('b'), k -= cnt / 3;
        else 
            res.push_back('c'), k -= 2 * cnt / 3;
        
        cnt /= 3;
        while (res.size() < n) {
            cnt >>= 1;
            if (res.back() == 'a') 
                res.push_back(k > cnt? 'c' : 'b'); 
            else if (res.back() == 'b') 
                res.push_back(k > cnt? 'c' : 'a');
            else 
                res.push_back(k > cnt? 'b' : 'a');
            
            if (k > cnt) 
                k -= cnt;
        }
        
        return res;
    }
};