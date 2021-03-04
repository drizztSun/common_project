/*
1063. Number of Valid Subarrays


Given an array A of integers, return the number of non-empty continuous subarrays that satisfy the following condition:

The leftmost element of the subarray is not larger than other elements in the subarray.

 

Example 1:

Input: [1,4,2,5,3]
Output: 11
Explanation: There are 11 valid subarrays: [1],[4],[2],[5],[3],[1,4],[2,5],[1,4,2],[2,5,3],[1,4,2,5],[1,4,2,5,3].
Example 2:

Input: [3,2,1]
Output: 3
Explanation: The 3 valid subarrays are: [3],[2],[1].
Example 3:

Input: [2,2,2]
Output: 6
Explanation: There are 6 valid subarrays: [2],[2],[2],[2,2],[2,2],[2,2,2].
 

Note:

1 <= A.length <= 50000
0 <= A[i] <= 100000

*/
#include <vector>
#include <stack>

using std::stack;
using std::vector;



class ValidSubarrays {

    /*
    
        1063.Number-of-Valid-Subarrays
        对于任意一个nums[i]作为subarray的左端点的话，右端点最远可以是哪里呢？显然是the next smaller element，假设位置是在j。那么显然从[i,j-1]区间内的任意一个元素都可以是组成合法subarray的右端点，因此count+=j-i.

        求数组内每个元素的next smaller element就是常规的单调栈的操作。

        特别注意的是，遍历结束的时候，栈里面可能还存有递增的元素，这些元素作为左端点的subarray都还未被计数。为了强制清空栈，我们可以nums的末尾添加一个INT_MIN，这样所有的nums的元素最终都会被退栈（退栈的时候会计算对应的subarray的数目）。
    
    */
    int doit_stack(vector<int>& nums) 
    {
        nums.push_back(INT_MIN);
        stack<int>Stack;
        int count = 0;
        for (int i=0; i<nums.size(); i++)
        {
            while (!Stack.empty() && nums[i]<nums[Stack.top()])
            {
                count += i-Stack.top();
                Stack.pop();
            }            
            Stack.push(i);
        }
        return count;        
    }


public:

    int doit_monotonic_stack(vector<int>& nums) {
        
        stack<int> st;
        int ans = 0, n = nums.size();
        
        for (int i = 0; i <= n; i++) {
            
            while (!st.empty() && (i == n || nums[st.top()] > nums[i])) {
                ans += i - st.top();
                st.pop();
            }
            
            st.push(i);
        }
        
        return ans;
    }
};