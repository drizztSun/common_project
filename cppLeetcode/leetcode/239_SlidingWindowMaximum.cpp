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
#include <vector>
#include <deque>
#include <queue>
#include <set>

using std::multiset;
using std::priority_queue;
using std::deque;
using std::vector;


class MaxSlidingWindow {


    /*
        239.Sliding-Window-Maximum
        解法1
        我们希望设计这样一个队列，每次读入一个新数nums[i]之后，希望队列弹出的就是当前窗口的最大值。当然，这个最大值不一定要真正“弹出去”，因为可能它处于窗口的中间位置，等下一个新数来的时候，可能依然是读取这个最大值。
        所以我们希望这个最大值能就一直保持在队列的首端，等待需要的时候再真正清除。什么时候需要清除呢？那就是发现当这个最大值的index等于i-k的时候，说明它超出了窗口长度，不得不踢掉了。

        如果把这个最大值踢掉了，我们希望在队列首端的是接下来第二大的值。于是，这就提示了我们：这个队列盛装的是一个递减的序列！这个序列是这个窗口里的最大的几个值的降序排列。这就告诉我们，每进入一个新数nums[i]，这个队列尾端的那些小于nums[i]的都可以踢掉了，然后把新数装进去。这样，直到nums[i]离开窗口之前，函数读取的最大值都是这些比nums[i]大的数。

        可以想见，我们需要的数据结构就是一个双端队列dequeu。每次加入新数nums[i]，但从后端弹出一些，以使得里面保持一个递减的序列。每次的队首元素就是当前k窗口的最大值，直到这个队首元素对应的index超出了k窗口的范围才被弹出。

        这种解法的时间复杂度是O(N)。

        解法2
        可以直接使用multiset，能够实时有序，并且允许多个相同元素的存在。这个代码比较好写，但时间复杂度是 o(NlogK)
    */
    vector<int> doit_slidingwindow_monotonicqueue(vector<int>& nums, int k) 
    {        
        vector<int>results;
        deque<int>q;
        for (int i=0; i<nums.size(); i++)
        {
            while (q.size()>0 && nums[q.back()]<nums[i])
                q.pop_back();
            q.push_back(i);

            if (q.front()<=i-k)
                q.pop_front();

            if (i>=k-1)
                results.push_back(nums[q.front()]);
        }
        return results;
    }

    vector<int> doit_heap(vector<int>& nums, int k) 
    {
        vector<int>results;
        multiset<int>Set;
        
        for (int i=0; i<nums.size(); i++)
        {
            Set.insert(nums[i]);
            if (Set.size()>k)
                Set.erase(Set.lower_bound(nums[i-k]));
            
            if (Set.size()<k) continue;
            results.push_back(*Set.rbegin());
        }
        
        return results;
    }
    
    vector<int> doit_heap(vector<int>& nums, int k) {
        
        std::priority_queue<std::pair<int, int>> que;
        vector<int> res;
        
        for (int i = 0; i < nums.size(); i++) {
         
            while (!que.empty() && que.top().second <= i - k) {
                que.pop();
            }
            
            que.push({nums[i], i});
            
            if (i >= k - 1)
                res.push_back(que.top().first);
        }
        return res;
    }
    
    // monotonic queue
    vector<int> doit_array_stack(vector<int>& nums, int k) {
        
        deque<int> buf;
        vector<int> res;
        
        for (int i = 0; i < nums.size(); i++) {
            
            while (!buf.empty() && nums[buf.back()] < nums[i]) {
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
