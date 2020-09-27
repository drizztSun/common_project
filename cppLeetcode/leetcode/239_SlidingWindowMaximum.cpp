#include <stdio.h>
#include <vector>
#include <deque>
using std::deque;
using std::vector;

/*
 239. Sliding Window Maximum
 
 You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

 Return the max sliding window.

  

 Example 1:

 Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 Output: [3,3,5,5,6,7]
 Explanation:
 Window position                Max
 ---------------               -----
 [1  3  -1] -3  5  3  6  7       3
  1 [3  -1  -3] 5  3  6  7       3
  1  3 [-1  -3  5] 3  6  7       5
  1  3  -1 [-3  5  3] 6  7       5
  1  3  -1  -3 [5  3  6] 7       6
  1  3  -1  -3  5 [3  6  7]      7
 Example 2:

 Input: nums = [1], k = 1
 Output: [1]
 Example 3:

 Input: nums = [1,-1], k = 1
 Output: [1,-1]
 Example 4:

 Input: nums = [9,11], k = 2
 Output: [11]
 Example 5:

 Input: nums = [4,-2], k = 2
 Output: [4]
  
 */


class MaxSlidingWindow {
public:
    vector<int> doit_array(vector<int>& nums, int k) {
        
        deque<int> buf;
        vector<int> res;
        
        for (int i = 0; i < nums.size(); i++) {
            
            while (! buf.empty() && nums[buf.back()] < nums[i]) {
                buf.pop_back();
            }
            
            buf.push_back(i);
            
            if (i - buf.front() >= k) {
                buf.pop_front();
            }
            
            if (i >= k - 1) {
                res.push_back(nums[buf.front()]);
            }
        }
        
        return res;
    }
    
    vector<int> doit_array_1(vector<int>& nums, int k) {
    
           int q[100010];
           int hh = 0, tt = -1;
           vector<int> ans;

           for (int i = 0 ; i < nums.size(); i++) {
               
               while (hh <= tt && (i - k + 1 > q[hh])) hh++;
               
               while (hh <= tt && nums[q[tt]] <= nums[i]) tt--;
               
               q[++tt] = i;
               if (i >= k - 1) ans.push_back(nums[q[hh]]);
           }
           
           return ans;
       }
};
