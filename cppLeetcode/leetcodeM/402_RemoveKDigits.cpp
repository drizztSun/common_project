/*
402. Remove K Digits


Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.

Note:
The length of num is less than 10002 and will be ≥ k.
The given num does not contain any leading zero.
Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.

*/
#include <string>
#include <vector>
#include <stack>

using std::stack;
using std::vector;
using std::string;

class RemoveKdigits {

    /*
        402.Remove-K-Digits
        解决原题的直观思路是寻找一个尽可能小的递增序列，但要满足位数的要求。

        这是栈的典型应用。利用栈维护一个递增序列。当遍历的元素小于栈顶元素时，就不断退栈直至 Stack.top()<num[i]，这样继续加入元素后仍然是一个递增序列。

        需要注意的几点：

        1. 需要一个计数器count来记录退栈的数目。只有当count<k时，才进行退栈操作（即模拟删除）。
        2. 都把所有元素都遍历结束后，如果发现仍然count<k，那么就把Stack末尾的弹出，直至count==k
        3. 需要去除结果里的前导零。
    */
    string removeKdigits(string num, int k) 
    {
        stack<char>Stack;
        int count=0;
            
        for (int i=0; i<num.size(); i++)
        {
            if (Stack.empty()||num[i]>=Stack.top())
            {
                Stack.push(num[i]);
            }
            else if (num[i]<Stack.top())
            {
                while (!Stack.empty() && num[i]<Stack.top() && count<k)
                {
                    Stack.pop();
                    count++;
                }
                Stack.push(num[i]);
            }
        }
        
        for (int i=count+1; i<=k; i++)
            Stack.pop();
        
        string result;
        while (!Stack.empty())
        {
            result+=Stack.top();
            Stack.pop();
        }
        while (result.size()>0 && result.back()=='0')
            result.pop_back();
                
        reverse(result.begin(),result.end());
        if (result=="")
            result="0";
        
        return result;
            
    }

public:
    
    string doit_stack(string num, int k) {
        
        vector<char> buff;
        int keep = num.length() - k;
        for (auto c: num) {
            while (!buff.empty() && k > 0 && buff.back() > c) {
                buff.pop_back();
                k--;
            }
            buff.push_back(c);
        }
        
        buff.resize(keep);
        if (buff.empty()) return "0";
        
        auto it = begin(buff);
        if (buff.size() > 1)
            while (it != end(buff) && *it == '0') it++;
        
        string res(it, buff.end());
        
        return res.empty() ? "0" : res;
    }
};