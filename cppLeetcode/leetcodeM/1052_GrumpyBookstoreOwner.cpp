/*
1052. Grumpy Bookstore Owner


Today, the bookstore owner has a store open for customers.length minutes.  Every minute, some number of customers (customers[i]) enter the store, and all those customers leave after the end of that minute.

On some minutes, the bookstore owner is grumpy.  If the bookstore owner is grumpy on the i-th minute, grumpy[i] = 1, otherwise grumpy[i] = 0.  
When the bookstore owner is grumpy, the customers of that minute are not satisfied, otherwise they are satisfied.

The bookstore owner knows a secret technique to keep themselves not grumpy for X minutes straight, but can only use it once.

Return the maximum number of customers that can be satisfied throughout the day.

 

Example 1:

Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], X = 3
Output: 16
Explanation: The bookstore owner keeps themselves not grumpy for the last 3 minutes. 
The maximum number of customers that can be satisfied = 1 + 1 + 1 + 1 + 7 + 5 = 16.
 

Note:

1 <= X <= customers.length == grumpy.length <= 20000
0 <= customers[i] <= 1000
0 <= grumpy[i] <= 1

*/
#include <vector>

using std::vector;


class MaxSatisfied {

    /*
            1052.Grumpy-Bookstore-Owner
        本题的意思是可以给你一个固定长度的滑窗，滑窗内的满意度可以累加（不管是否grumpy）。求某个滑窗位置时，整体满意度的最大值。

        首先算出sum的基本盘，就是在没有滑窗覆盖的情况下，可以得到的满意度之和。

        然后考虑一个长度为X的滑窗内，我们可能可以额外增加一些满意度。滑动窗口每一次移动，会加入一个元素customers[i]，考察它对应的grumpy[i]是否是1，是的话那就是额外增加的满意度，需要加入sum。同时也会有一个元素customers[i-X]离开滑窗，同样考察它对应的grumpy[i+X]是否是1，是的话我们就要退回额外的满意度，从sum中扣除。

        整个滑动过程中出现的最大sum，就是答案。
    */
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) 
    {
        int sum = 0;
        int n = grumpy.size();
        for (int i=0; i<n; i++)
            if (grumpy[i]==0)
                sum+=customers[i];

        int ret = 0;
        for (int i=0; i<n; i++)
        {
            if (grumpy[i]==1)
                sum += customers[i];
            if (i>=X && grumpy[i-X]==1)
                sum -= customers[i-X];
            ret = std::max(ret, sum);
        }
        return ret;
    }


public:

    int doit_slidingwindow(vector<int>& customers, vector<int>& grumpy, int X) {
        
        int totalungrumpy = 0, forcedungrumpy = 0;
        int window = 0;
        
        for (int i = 0; i < customers.size(); i++) {
            
            if (grumpy[i] == 0)
                totalungrumpy += customers[i]; 
            else
                window += customers[i];
            
            if (i - X >= 0 && grumpy[i-X] == 1)
                window -= customers[i-X];
            
            forcedungrumpy = std::max(forcedungrumpy, window);
        }
        
        return totalungrumpy + forcedungrumpy;
    }
};