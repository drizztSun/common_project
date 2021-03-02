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

    /*
        301.Remove-Invalid-Parentheses
        本题没有太高明的办法，基本就是靠搜索，数量级应该就是O(2^N).DFS和BFS均可。感觉对于在同一个数组或字符串里面搜若干个元素的话，DFS写起来更舒服一些。
        基本思想就是对于每一个s[i]都有“选用”（append到当前curStr中去）和“不选用”两种选择，然后依次递归下去。如果遇到curStr不合法的情况，就及时中断这条支路。

        但本题最大的考点应该在于如何避免最后大量重复的结果。比如说我们想在“((()”里面最终得到"()"，其实就有好几种DFS的路径。比如说"OOXX", "XOOX", "OXOX"（O表示不选，X表示选）。
        可见原字符串中的三个“(((”，可以有三种不同的路径得到最后只剩一个"("。如果无脑地对每个字符都尝试“选用”和“不选用”，那么最后势必要依靠字符串类型的集合来去重，效率会很低。

        本题的精彩之处，是在于设计一种DFS路径选择机制，能够避开任何可能造成重复的路径。规则如下：

        1. 如果备选字符s[i]与已选字符串的最后一位相同，那么你必须选择使用这个字符，即curStr.append(s[i])
        2. 如果备选字符s[i]与已选字符串的最后一位不相同，那么你可以选择使用这个字符，也可以选择不使用，接下来的两条分叉递归处理。
        上面规则的本质是，如果最终生成的字符串含有若干个相同的字符，那么这些相同字符在s中的顺序也必须是连续的，并且是最后的若干个连续的字符。

        举个例子，如果s中有四个连续的左括号，我们选择保留下来两个左括号，那么我们对这四个左括号的选择一定是XXOO的形式，即我们只选择最后两个。而不能是OOXX,OXOX,OXXO,XOOX,XOXO这五种其他的形式。这样就避免了六种DFS搜索形式对应同一个最终结果的复杂局面。
    
    */
    vector<string> doit_dfs(string s) 
    {
        vector<string>rets;
        int retLen = -1;
        string curStr = "";

        std::function<void(string, string&, int, int)> dfs = [&](string curStr, string &s, int i, int count)
        {
            if (count<0) return;
            
            if (i==s.size())
            {
                if (count!=0) return;
                                        
                if (curStr.size() == retLen)
                    rets.push_back(curStr);
                else if ((int)curStr.size() > retLen)
                {
                    // getting longer one, we are finding minimum number removing
                    rets.clear();
                    rets.push_back(curStr);
                    retLen = curStr.size();
                }            
                return;
            }
            
            if (s[i]!='(' && s[i]!=')')
            {
                dfs(curStr+s.substr(i,1), s, i+1, count);
                return;
            }
            
            dfs(curStr+s.substr(i,1), s, i+1, count+(s[i]=='('?1:-1));
            
            if (curStr.size()==0 || curStr.back()!=s[i])
                // remove current one.
                dfs(curStr, s, i+1, count);
        };
        
        dfs(curStr, s, 0, 0);
        return rets;
    }

public:
    
    vector<string> doit_dfs_backtracking(string str) {
        
        int left = 0, right = 0;
        unordered_set<string> res;
        
        for (auto c: str) {
            
            if (c == '(')
                left++;
            else if (c == ')') {
                
                if (left == 0)
                    right++;
                
                if (left > 0)
                    left--;
            }
        }
        
        string path;
        
        
        std::function<void(int, int, int, int, int, string&)> dfs = [&](int index, int left, int right, int left_rem, int right_rem, string& path) {
          
            if (index == str.length()) {
                if (left_rem == 0 && right_rem == 0 && res.count(path) == 0)
                    res.insert(path);
                return;
            }
            
            // remove ( or )
            if (str[index] == '(' && left_rem > 0 || str[index] == ')' && right_rem) {
                dfs(index + 1, left, right, left_rem - (str[index] == '('), right_rem - (str[index] == ')'), path);
            }
            
            // don't remove
            path.push_back(str[index]);
            
            // non-parenthesis 
            if (str[index] != '(' && str[index] != ')')
                dfs(index + 1, left, right, left_rem, right_rem, path);
            // putting left
            else if (str[index] == '(')
                dfs(index+1, left+1, right, left_rem, right_rem, path);
            // putting right
            else if (str[index] == ')' && left > right)
                dfs(index+1, left, right+1, left_rem, right_rem, path);
            
            path.pop_back();
        };
        
        
        dfs(0, 0, 0, left, right, path);
        return vector<string>(res.begin(), res.end());
    }

    vector<string> doit_bfs(string s)
    {
        queue<string> q;
        q.push(s);
        vector<string> ret;
        unordered_set<string> v;
        bool flag=false;

        auto check = [](string s) {
            int count = 0;
            for (const char ch : s) {
                if (ch == '(') count++;
                if (ch == ')') count--;
                if (count < 0)
                    return false;
            }
            return count == 0;
        };
        
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
};
