#include <vector>
#include <stack>
#include <unordered_map>

using std::unordered_map;
using std::stack;
using std::vector;


/*
496. Next Greater Element I

You are given two integer arrays nums1 and nums2 both of unique elements, where nums1 is a subset of nums2.

Find all the next greater numbers for nums1's elements in the corresponding places of nums2.

The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. If it does not exist, return -1 for this number.

 

Example 1:

Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Explanation:
For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
For number 1 in the first array, the next greater number for it in the second array is 3.
For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
Example 2:

Input: nums1 = [2,4], nums2 = [1,2,3,4]
Output: [3,-1]
Explanation:
For number 2 in the first array, the next greater number for it in the second array is 3.
For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
 

Constraints:

1 <= nums1.length <= nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 104
All integers in nums1 and nums2 are unique.
All the integers of nums1 also appear in nums2.
 

Follow up: Could you find an O(nums1.length + nums2.length) solution?
*/
class NextGreaterElementI {

    /*
        496.Next-Greater-Element-I
        此题用普通模拟的方法遍历会很慢。高级的算法是利用到单调栈，时间复杂度是o(n)。

        维护一个单调递减的栈，即当nums[i]小于栈顶元素时就不断入栈。当发现nums[i]大于栈顶元素时，说明nums[i]就是此栈顶元素所遇到的第一个greater number，把这个信息记录在一个Hash Map里，然后把栈顶元素退栈；重复上述操作直至nums[i]小于栈顶元素，再将其入栈并继续遍历nums。
            
    */
    vector<int> doit_stack(vector<int>& findNums, vector<int>& nums) 
    {
        stack<int>Stack;
        unordered_map<int,int>Map;
        
        for (int i=0; i<nums.size(); i++)
        {
            if (Stack.empty() || Stack.top()>nums[i])
                Stack.push(nums[i]);
            else
            {
                while (!Stack.empty() && Stack.top()<nums[i])
                {
                    Map[Stack.top()]=nums[i];
                    Stack.pop();
                }
                Stack.push(nums[i]);
            }
        }
        
        vector<int>results;
        for (int i=0; i<findNums.size(); i++)
        {
            if (Map.find(findNums[i])==Map.end())
                results.push_back(-1);
            else
                results.push_back(Map[findNums[i]]);
        }
        
        return results;
    }



public:
    vector<int> doit_stack(vector<int>& nums1, vector<int>& nums2) {

        unordered_map<int, int> buf;
        stack<int> st;
        
        for (int i = 0; i < nums2.size(); i++) {
            
            while (!st.empty() && st.top() < nums2[i]) {
                buf[st.top()] = nums2[i];
                st.pop();
            }
            
            st.push(nums2[i]);
        }
        
        vector<int> ans(nums1.size(), -1);
        for (int i = 0; i < nums1.size(); i++) {
            if (buf.count(nums1[i]) > 0)
                ans[i] = buf[nums1[i]];
        }
        
        return ans;
    }
};



/*
503. Next Greater Element II


Given a circular array (the next element of the last element is the first element of the array), print the Next Greater Number for every element. 
The Next Greater Number of a number x is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. 
If it doesn't exist, output -1 for this number.

Example 1:
Input: [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2; 
The number 2 can't find next greater number; 
The second 1's next greater number needs to search circularly, which is also 2.
Note: The length of given array won't exceed 10000.

*/
class NextGreaterElementsII {

    /*
        503.Next-Greater-Element-II
        此题类似 496.Next-Greater-Element-I。

        变化是需要遍历的个数多了一倍，即要将nums遍历两遍。因为根据题意，有些元素的greater number需要回到数组开头去找。
    */
    vector<int> doit_monotonic_stack(vector<int>& nums) 
    {
        int N=nums.size();
        stack<pair<int,int>> Stack;
        vector<int> results(N,-1);
        
        for (int j=0; j<N*2; j++)
        {
            int i=j;
            if (i>=N) i=i-N;
            
            if (Stack.empty() || Stack.top().first>nums[i])
                Stack.push({nums[i],i});
            else
            {
                while (!Stack.empty() && Stack.top().first<nums[i])
                {
                    results[Stack.top().second]=nums[i];
                    Stack.pop();
                }
                Stack.push({nums[i],i});
            }
        }
        
        return results;
    }

public:
    
    vector<int> doit_stack(vector<int>& nums) {
        
        int n = nums.size();
        vector<int> res(n, -1), buff;
        int i = 0;
        
        while (i < nums.size() * 2) {
            
            while (!buff.empty() && nums[buff.back()] < nums[i%n]) {
                res[buff.back()] = nums[i%n];
                buff.pop_back();
            }
            
            if (i < n)
                buff.push_back(i);
            i++;
        }
        
        return res;
    }
};
