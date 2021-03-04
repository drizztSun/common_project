/*
901. Online Stock Span

Write a class StockSpanner which collects daily price quotes for some stock, and returns the span of that stock's price for the current day.

The span of the stock's price today is defined as the maximum number of consecutive days (starting from today and going backwards) for which the price of the stock was less than or equal to today's price.

For example, if the price of a stock over the next 7 days were [100, 80, 60, 70, 60, 75, 85], then the stock spans would be [1, 1, 1, 2, 1, 4, 6].

 

Example 1:

Input: ["StockSpanner","next","next","next","next","next","next","next"], [[],[100],[80],[60],[70],[60],[75],[85]]
Output: [null,1,1,1,2,1,4,6]
Explanation: 
First, S = StockSpanner() is initialized.  Then:
S.next(100) is called and returns 1,
S.next(80) is called and returns 1,
S.next(60) is called and returns 1,
S.next(70) is called and returns 2,
S.next(60) is called and returns 1,
S.next(75) is called and returns 4,
S.next(85) is called and returns 6.

Note that (for example) S.next(75) returned 4, because the last 4 prices
(including today's price of 75) were less than or equal to today's price.
 

Note:

Calls to StockSpanner.next(int price) will have 1 <= price <= 10^5.
There will be at most 10000 calls to StockSpanner.next per test case.
There will be at most 150000 calls to StockSpanner.next across all test cases.
The total time limit for this problem has been reduced by 75% for C++, and 50% for all other languages.


*/
#include <stack>
#include <vector>

using std::vector;
using std::stack;

/*
    901.Online-Stock-Span
题意就是说，对于数组中的任何元素A[i]，需要回溯看它左边邻接有多少个连续的元素小于等于A[i]。显然应该有o(n)的单调栈解法。

我们尝试一下如果是维护一个递减的序列，比如5,4,3,2,1，显然每个元素能往左回溯的距离就只有1（就是它本身），因为栈顶元素比自己大。

接下来如果新元素是3，我们应该尝试退栈，得到5,4,[3,2,1],3（中括号内的部分就是退栈的元素）。退栈合理与否的关键，在于被退栈的元素以后是否还有利用价值。
在这里，[3,2,1]是被3逼退的，设想加入之后再出现了X，只要X比3大，自然X也会比这些已经退栈的[3,2,1]都大。所以退栈的这些元素以后是不用被记录的，对于X而言可以直接退栈到4或者更前面的位置。

所以方法就是维护递减的单调栈。每次加入新元素的时候，都可以通过退栈操作（也可能不退）来更新得到这个新元素对应的配对位置（也就是左边邻接最远的小于等于自身的元素）。
*/
class StockSpanner {
    vector<int>arr;
    stack<int>Stack;
    int i;
public:
    StockSpanner() {
        i = 0;
    }
    
    int next(int price) 
    {
        arr.push_back(price);
        int ret;
        
        if (Stack.empty() || arr[Stack.top()] > arr[i])
        {
            ret = 1;
            Stack.push(i);
        }
        else
        {
            while (!Stack.empty() && arr[Stack.top()] <= arr[i])
                Stack.pop();
            if (!Stack.empty())
                ret = i - Stack.top();
            else
                ret = i+1;
            Stack.push(i);
        }
        
        i++;
        
        return ret;           
    }
};


/*
    Explanation
    You can refer to the same problem 739. Daily Temperatures.

    Push every pair of <price, result> to a stack.
    Pop lower price from the stack and accumulate the count.

    One price will be pushed once and popped once.
    So 2 * N times stack operations and N times calls.
    I'll say time complexity is amortized O(1)
*/
class StockSpanner {

    stack<std::pair<int, int>> _st;
public:

    StockSpanner() {}
    
    int next(int price) {
        
        int weight = 1;

        while (!_st.empty() && _st.top().first <= price) {
            weight += _st.top().second;
            _st.pop();
        }

        _st.push({price, weight});
        return weight;
    }
};
