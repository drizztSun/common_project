/*
1673. Find the Most Competitive Subsequence

Given an integer array nums and a positive integer k, return the most competitive subsequence of nums of size k.

An array's subsequence is a resulting sequence obtained by erasing some (possibly zero) elements from the array.

We define that a subsequence a is more competitive than a subsequence b (of the same length) if in the first position where a and b differ, subsequence a has a number less than the corresponding number in b. 
For example, [1,3,4] is more competitive than [1,3,5] because the first position they differ is at the final number, and 4 is less than 5.

 

Example 1:

Input: nums = [3,5,2,6], k = 2
Output: [2,6]
Explanation: Among the set of every possible subsequence: {[3,5], [3,2], [3,6], [5,2], [5,6], [2,6]}, [2,6] is the most competitive.
Example 2:

Input: nums = [2,4,3,3,5,4,9,6], k = 4
Output: [2,3,3,4]
 

Constraints:

1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9
1 <= k <= nums.length
*/
#include <vector>
#include <stack>

using std::stack;
using std::vector;

class MostCompetitiveSubsequence {

    /*
        1673.Find-the-Most-Competitive-Subsequence
        本题和LC.402 Remove K Digits一模一样，本质上就是求长度为k的最小序列。

        我们维护一个递增的栈，一旦发现新数字a比栈顶元素b更小，我们肯定希望把这个a尽量前移（这样必然使得序列更小）。把a每前移一位，就意味着要舍弃栈顶的数字，直至已经被舍弃的数字总数达到上限。

        当所有数字都入了栈，那么栈里面的就是最小的递增序列。当然，如果这个序列的数字数目大于了k，那么就舍弃最后的数字舍得剩下的恰好有k个。
    */
    vector<int> doit_stack(vector<int>& nums, int k) 
    {
        int count = nums.size()-k;
        stack<int>Stack;
        for (int x: nums)
        {
            if (Stack.empty() || x>Stack.top())
            {
                Stack.push(x);
            }
            else
            {
                while (!Stack.empty() && x<Stack.top() && count>0)
                {
                    Stack.pop();
                    count--;
                }
                Stack.push(x);
            }
        }
        while (count>0)
        {
            Stack.pop();
            count--;
        }
        vector<int>ret;
        while (!Stack.empty())
        {
            ret.push_back(Stack.top());
            Stack.pop();
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }



public:


    vector<int> doit_monotonic_stack(vector<int>& nums, int k) {
        vector<int> st;
        int n = nums.size();
        for (int i = 0; i < nums.size(); i++) {
            while(!st.empty() && n-i+st.size() > k && st.back() > nums[i]) st.pop_back();   
            if (st.size() < k) st.push_back(nums[i]);
        }
        return st;
    }

    vector<int> doit_(vector<int>& nums, int k) {
        vector<int> stack;
        int nums_to_delete = nums.size()-k;
        for (int i = 0; i < nums.size(); i++) {
            while (!stack.empty() && nums[i] < stack.back() && nums_to_delete) {
                stack.pop_back();
                nums_to_delete--;
            }
            stack.push_back(nums[i]);
        }
        return vector<int>(stack.begin(), stack.begin()+k);
    }
};