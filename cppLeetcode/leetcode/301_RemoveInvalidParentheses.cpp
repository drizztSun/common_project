/*
 301. Remove Invalid Parentheses
 
 Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.

 Note: The input string may contain letters other than the parentheses ( and ).

 Example 1:

 Input: "()())()"
 Output: ["()()()", "(())()"]
 Example 2:

 Input: "(a)())()"
 Output: ["(a)()()", "(a())()"]
 Example 3:

 Input: ")("
 Output: [""]
 
 */
#include <stack>
#include <string>
#include <queue>
#include <vector>
#include <unordered_set>

using std::unordered_set;
using std::vector;
using std::queue;
using std::stack;
using std::string;

class MinRemoveToMakeValid {
    
public:

    bool check(string s)
    {
        int count = 0;
            for (const char ch : s) {
                if (ch == '(') count++;
                if (ch == ')') count--;
                if (count < 0)
                    return false;
            }
            return count == 0;
    }
    vector<string> doit_bfs(string s)
    {
        queue<string> q;
        q.push(s);
        vector<string> ret;
        unordered_set<string> v;
        bool flag=false;
        
        while(!q.empty() && !flag)
        {
            int n=q.size();
            for(int i=0;i<n;++i)
            {
                string a=q.front();
                //cout<<a<<endl;
                q.pop();
                if(check(a))
                {
                    ret.push_back(a);
                    flag=true;// marks the flag whether the solution is found or not
                }
                else if(!flag) {
                    for(int j=0; j<a.length(); ++j)
                    {
                        string t=a;
                        if(a[j]=='('||a[j]==')'){
                            t.erase(j,1);
                        }
                        else
                            continue;
                        
                        if(v.find(t)==v.end())
                        {
                            q.push(t);
                            v.insert(t);
                        }
                    }
                }
            }
        }
        return ret;
    }
    
    
    void flip(string& s) {
        reverse(s.begin(), s.end());
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                s[i] = ')';
            } else if (s[i] == ')') s[i] ='(';
        }
    }
    
    vector<string> res;
    
    // doit_dfs
    vector<string> removeInvalidParentheses(string s, int start = 0, int remove_start = 0, bool flipped = false) {
      //  cout << s << " " << start << " " <<  remove_start << " " << flipped << endl;
        int bal = 0, i = start;
        for (; i < s.length(); i++) {
            if (s[i] == '(') bal++;
            if (s[i] == ')') bal--;
            if (bal < 0) {
                break;
            }
        }
        
        if (i == s.length() && bal == 0) {
            if (flipped) {
                flip(s);
            }
            res.push_back(s);
            return res;
        }
        
        if (i == s.length() && bal > 0) {
            // deal with extra opening brackets.
            flip(s);
            removeInvalidParentheses(s, 0, 0, true);
            return res;
        }
        
        for (int j = remove_start; j <= i; j++) {
            if (s[j] == ')' && (j == remove_start || s[j-1] != ')')) {
                removeInvalidParentheses(s.substr(0, j) + s.substr(j+1), i, j, flipped);
            }
        }

        return res;
    }
};
