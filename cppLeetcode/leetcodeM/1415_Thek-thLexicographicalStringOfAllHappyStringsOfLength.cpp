/*
1415. The k-th Lexicographical String of All Happy Strings of Length n




*/
#include <vector>
#include <string>
#include <functional>

using std::string;
using std::vector;

class KthLexicographicalStringOfAllHappyString {

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

    string doit_(int n, int k) {

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