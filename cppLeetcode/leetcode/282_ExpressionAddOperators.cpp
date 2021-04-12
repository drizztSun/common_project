/*
282. Expression Add Operators

Given a string num that contains only digits and an integer target, return all possibilities to add the binary operators '+', '-', or '*' 
between the digits of num so that the resultant expression evaluates to the target value.

 

Example 1:

Input: num = "123", target = 6
Output: ["1*2*3","1+2+3"]
Example 2:

Input: num = "232", target = 8
Output: ["2*3+2","2+3*2"]
Example 3:

Input: num = "105", target = 5
Output: ["1*0+5","10-5"]
Example 4:

Input: num = "00", target = 0
Output: ["0*0","0+0","0-0"]
Example 5:

Input: num = "3456237490", target = 9191
Output: []
 

Constraints:

1 <= num.length <= 10
num consists of only digits.
-231 <= target <= 231 - 1


*/

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <functional>

using std::unordered_map;
using std::unordered_set;
using std::vector;
using std::string;



class AddOperators {

    /*
        282.Expression-Add-Operators
        这是一道近乎暴力的DFS，没有太多优化剪枝的步骤。除了考虑怎么添加乘号之外，整理构架非常简明。

        构造DFS的函数：

        void DFS(string num, long long target, long long curRes, long long product, string expression)
        num表示剩余待处理的字符串，target表示目标数值（题目所给定），curRes是之前所构造字符串的估值，product是之前所以构造字符串里最后几项（疑似）乘法项的乘积。所以主程序最顶端调用 DFS(num,target,0,0,"");

        DFS的思想就是在待处理的字符串里遍历第一项的可能性：只要确定了第一项，剩余的字符串就扔给下一个DFS函数来处理。

        确定第一项，就需要确定它有多少个数字，以及第一项之前的运算符。

        第一项有多少个数字好办，从1到num的长度，逐个循环过来。第一项之前的运算符也就只有三个可能，加减乘。本题的架构就是：逐个考虑，一旦确认了第一项curString，如何设置下一个DSF函数的参数。

        添加的curString是加法项：更新后的字符串当前估值就是curRes+stoll(curString)；字符串末尾可以作为(未来的)乘法项的也就是curString，其估值就是stoll(curString)；更新后的字符串 expression+'+'+curString

        添加的curString是减法项：更新后的字符串当前估值就是curRes-stoll(curString)；字符串末尾可以作为(未来的)乘法项的也就是curString，其估值就是-stoll(curString)；更新后的字符串 expression+'-'+curString

        添加的curString是乘法项：更新后的字符串当前估值就是curRes-product+product*stoll(curString)；可以看到这里函数参数里的product派上了用场，之前的字符串的末尾几项的估值product需要作为被乘数和curString乘起来。更新后的字符串末尾可以作为(未来的)乘法项的变成product*stoll(curString)；更新后的字符串 expression+'*'+curString

        C++里字符串变长整形的函数是stoll，很好记 string to long long

                for (int i=1; i<=num.size(); i++)  //逐个尝试第一项的数字长度
                {
                    string curString=num.substr(0,i);  //确定了第一项
                    string nextString=num.substr(i);   //剩余的字符串
                    if (curString.size()>1 && curString[0]=='0') return; //第一项不能是有前导0的数字
                    
                    if (expression.size()==0)  //如果该第一项是作为整个字符串的开头，只能是加法项
                        DFS(nextString,target,stoll(curString),stoll(curString),curString);
                    else
                    {
                        DFS(nextString,target,curRes+stoll(curString),stoll(curString),expression+'+'+curString);                
                        DFS(nextString,target,curRes-stoll(curString),-stoll(curString),expression+'-'+curString);
                        DFS(nextString,target,curRes-product+product*stoll(curString),product*stoll(curString),expression+'*'+curString);
                    }
                }
    */
    vector<string>output;
    vector<string> addOperators(string num, int target) 
    {
        DFS(num,(long long)target,0,0,"");
        return output;
    }
    
    void DFS(string num, long long target, long long curRes, long long product, string expression)
    {
        if (num.size()==0 && curRes==target)
        {
            output.push_back(expression);
            return;
        }
        
        for (int i=1; i<=num.size(); i++)
        {            
            string curString=num.substr(0,i);
            string nextString=num.substr(i);
            if (curString.size()>1 && curString[0]=='0') return;
            
            if (expression.size()==0)
                DFS(nextString,target,stoll(curString),stoll(curString),curString);
            else
            {
                DFS(nextString,target,curRes+stoll(curString),stoll(curString),expression+'+'+curString);
                DFS(nextString,target,curRes-stoll(curString),-stoll(curString),expression+'-'+curString);
                DFS(nextString,target,curRes-product+product*stoll(curString),product*stoll(curString),expression+'*'+curString);
            }
        }        
    }


public:

    
    vector<string> addOperators(string num, int target) 
    {
        using ll = long long;
        vector<string>output;

        std::function<void(string, ll, ll, ll, string) > DFS = [&](string num, ll target, ll curRes, ll product, string expression)
        {
            if (num.size()==0 && curRes==target)
            {
                output.push_back(expression);
                return;
            }
            
            for (int i=1; i<=num.size(); i++)
            {            
                string curString=num.substr(0,i);
                string nextString=num.substr(i);
                if (curString.size()>1 && curString[0]=='0') return;
                
                if (expression.size()==0)
                    DFS(nextString,target,stoll(curString),stoll(curString),curString);
                else
                {
                    DFS(nextString,target,curRes+stoll(curString),stoll(curString),expression+'+'+curString);
                    DFS(nextString,target,curRes-stoll(curString),-stoll(curString),expression+'-'+curString);
                    DFS(nextString,target,curRes-product+product*stoll(curString),product*stoll(curString),expression+'*'+curString);
                }
            }        
        };

        DFS(num, static_cast<ll>(target), 0, 0, "");
        return output;
    }
    
public:

    vector<string> ret_ = {};
    string s_;
    int n_;

    void recursion(long prevSum, long prev, int idx, char* buf, int buf_idx, int target) {
        if(idx >= n_) {
            if(prevSum+prev == target) {
                buf[buf_idx] = 0;
                ret_.push_back(buf);
            }
            return;
        }
        int lmax = s_[idx] == '0'?idx+1:n_;
        int c = 0;
        for(int i = idx; i < lmax; i++) {
            c = 10*c+(s_[i]-'0');
            
            buf[buf_idx+i-idx+1] = s_[i];
            buf[buf_idx] = '+';
            recursion(prevSum+prev, c, i+1, buf, buf_idx+i-idx+2, target);
            buf[buf_idx] = '-';
            recursion(prevSum+prev, -1*c, i+1, buf, buf_idx+i-idx+2, target);
            buf[buf_idx] = '*';
            recursion(prevSum, prev*c, i+1, buf, buf_idx+i-idx+2, target);
        }
    } 

    vector<string> addOperators_str_best(string num, int target) {
        n_ = num.length();
        char buf[2*n_];
        s_ = num;

        // prevSum + prev(?c)
        int lmax = s_[0] == '0'?1:n_;
        long c = 0;
        for(int i = 0; i < lmax; i++) {
            c = 10*c+(s_[i]-'0');
            int buf_idx = i;
            buf[buf_idx++] = s_[i];
            recursion(0, c, i+1, buf, buf_idx, target);
        }
        return ret_;
    }

};