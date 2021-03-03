/*
84. Largest Rectangle in Histogram

Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

 

Example 1:


Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.
Example 2:


Input: heights = [2,4]
Output: 4
 

Constraints:

1 <= heights.length <= 10^5
0 <= heights[i] <= 10^4

*/
#include <vector>
#include <stack>

using std::stack;
using std::vector;

class LargestRectangleArea {

    /*
        leetcode-84-Largest-Rectangle-in-Histogram
        此类是贪心法的典型题。
        贪心法的原则是维护一个递增（严格的说是非递减）的栈序列s，s里面是所给数组元素的index（注意不是数组元素本身）。当下一个元素满足递增的要求时，入栈：

        if (height[i]>height[s.top()]) 
        s.push(height[i]);  
        当下一个元素不满足递增的要求时，就退栈处理栈顶的一些元素，使得即将入列的元素依然满足递增关系。退栈处理的过程中可以方便地考察那些退栈元素所围成的最大面积。其高度易知是height[s.top()]，但宽度是什么呢？注意是和次顶元素的位置有关：

        while (height[s.back()]>height[i])
        {
        Height = height[s.top()];  
        s.pop(); // 提取次顶元素的位置  
        result = max(result, Height * (i-s.top()-1);  
        }
        注意如果写成以下就是错误的:

        result = max(result, height[s.top()] * (i-s.top());  
        原因是次顶元素和栈顶元素可能在index上并不是相邻的，中间可能隔着一些已经被处理掉的大数。因此在考虑当前的栈顶元素围成的面积，应该包括这些位置，所以其宽度不仅是i-s.top()，而要更大。  

        其他的技巧：  
        在height数组末添加元素0，是为了保证最后强制回溯。在height数组首端添加元素0，是为了便于处理s.pop()之后栈为空的特殊情况；这样处理后永远不会栈空。
    */
    int doit_monotonic_stack(vector<int> &height) 
    {
        if (height.size()==0) return 0;
        if (height.size()==1) return height[0];
        
        height.push_back(0);
        height.insert(height.begin(),0);
        stack<int>s;

        int result=0;
        
        for (int i=0; i<height.size(); i++)
        {

            if (s.empty() || height[i]>=height[s.top()])
            {
                s.push(i);
                continue;
            }

            if (height[i]<height[s.top()])
            {
                while (!s.empty() && height[s.top()]>height[i])
                {
                    
                    int Height = height[s.top()];
                    s.pop();
                    result = std::max(result, Height*(i-s.top()-1));

                }
                s.push(i);
            }            
        }
        
        return result;
    }


public:
    
    // increasing monotonic stack
    int doit_stack(vector<int>& heights) {
        
        stack<int> pos;
        int maxv = 0;

        for (int i = 0; i <= heights.size(); i++) {

            while (!pos.empty() && (i == heights.size() || heights[pos.top()] > heights[i])) {
                int H = heights[pos.top()];
                pos.pop();
                int last = pos.empty() ? -1 : pos.top();
                int L = i - last - 1;
                maxv = std::max(maxv, L * H); 
            }

            pos.push(i);
        }        

        return maxv;
    }
};