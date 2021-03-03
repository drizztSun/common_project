/*
739. Daily Temperatures

Given a list of daily temperatures T, return a list such that, for each day in the input, tells you how many days you would have to wait until a warmer temperature. If there is no future day for which this is possible, put 0 instead.

For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73], your output should be [1, 1, 4, 2, 1, 1, 0, 0].

Note: The length of temperatures will be in the range [1, 30000]. Each temperature will be an integer in the range [30, 100].



*/

#include <vector>
#include <stack>

using std::vector;
using std::stack;


class DailyTemperatures {

    /*
        739.Daily-Temperatures
        解法1：贪心法
        此题可以从后往前考虑．对于results[i]，我们考察其右边的那个元素，即results[j],where j=i+1.

        当temp[j]<=temp[i],我们将指针跳转j+=results[j]，这样就可以加快搜索的效率．这样直到找到一个temp[j]>temp[i]即为找到结果；或者直到发现results[j]==0时说明再也找不下去了．

        解法2：栈
        此题可以非常类似于 maximum histgram，维护一个递减序列的栈，并且存放这的是index而不是数值。

        此题可以从后往前遍历数组。此题转化为：对于任意的nums[i]，查找早于它处理的最近一个大于它的数的位置。于是这就是一个套路题。构造一个栈，维护一个递减数列：这样如果进入一个新数nums[i]小于栈顶元素，
        那么它的最近的大于nums[i]的数就是这个栈顶元素。如果这个新数nums[i]大于栈顶元素，就不断退栈直至遇到比它大的为止，那么当前这个栈顶元素也就是最近的一个比nums[i]大的数。因为存储的是index，所以很容易得到两个数在位置上的
    */
    vector<int> doit_stack_1(vector<int>& temperatures) 
    {
        stack<int>Stack;
        vector<int>results;
        for (int i=temperatures.size()-1; i>=0; i--)
        {
            if (Stack.empty())
            {
                results.push_back(0);
                Stack.push(i);                
            }
            else if (temperatures[i]<temperatures[Stack.top()])
            {
                results.push_back(Stack.top()-i);
                Stack.push(i);
            }
            else 
            {
                while (!Stack.empty() && temperatures[i]>=temperatures[Stack.top()])
                    Stack.pop();
                if (Stack.empty())
                    results.push_back(0);
                else
                    results.push_back(Stack.top()-i);
                Stack.push(i);
            }
        }
        reverse(results.begin(),results.end());
        return results;
    }

    vector<int> dailyTemperatures(vector<int>& temperatures) 
    {
        int N = temperatures.size();
        vector<int>results(N,0);
        
        for (int i=N-2; i>=0; i--)
        {
            int j = i+1;
            while (results[j]!=0 && temperatures[j]<=temperatures[i])
                j = j+results[j];
            if (temperatures[j]>temperatures[i])
                results[i] = j-i;
            else
                results[i] = 0;
        }
        return results;
    }



    

public:
    vector<int> doit_stack(vector<int>& T) {
        
        vector<int> ans(T.size(), 0);
        stack<int> buff;
        
        for (int i = 0; i < T.size(); i++) {
            
            while (!buff.empty() && T[buff.top()] < T[i]) {
                ans[buff.top()] = i - buff.top();
                buff.pop();
            }
            
            buff.push(i);
        }
        
        return ans;
    }


    vector<int> doit_stack(vector<int>& T) {
        
        vector<int> ans(T.size(), 0);
        stack<int> st;
        
        for (int i = T.size()-1; i >= 0; i--) {
            
            while (!st.empty() && T[st.top()] <= T[i]) {
                st.pop();
            }
            
            if (!st.empty()) {
                ans[i] = st.top() - i;
            }
            
            st.push(i);
        }
        
        return ans;
    }
};
