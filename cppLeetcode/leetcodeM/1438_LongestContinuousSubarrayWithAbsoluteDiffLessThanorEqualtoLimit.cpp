/*
1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit


Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to limit.

 

Example 1:

Input: nums = [8,2,4,7], limit = 4
Output: 2 
Explanation: All subarrays are: 
[8] with maximum absolute diff |8-8| = 0 <= 4.
[8,2] with maximum absolute diff |8-2| = 6 > 4. 
[8,2,4] with maximum absolute diff |8-2| = 6 > 4.
[8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
[2] with maximum absolute diff |2-2| = 0 <= 4.
[2,4] with maximum absolute diff |2-4| = 2 <= 4.
[2,4,7] with maximum absolute diff |2-7| = 5 > 4.
[4] with maximum absolute diff |4-4| = 0 <= 4.
[4,7] with maximum absolute diff |4-7| = 3 <= 4.
[7] with maximum absolute diff |7-7| = 0 <= 4. 
Therefore, the size of the longest subarray is 2.
Example 2:

Input: nums = [10,1,2,4,7,2], limit = 5
Output: 4 
Explanation: The subarray [2,4,7,2] is the longest since the maximum absolute diff is |2-7| = 5 <= 5.
Example 3:

Input: nums = [4,2,2,2,4,4,2,2], limit = 0
Output: 3
 

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
0 <= limit <= 10^9

*/
#include <vector>
#include <deque>
#include <set>

using std::multiset;
using std::deque;
using std::vector;

//TC: O(n)
//SC: O(n)
class LongestContinuousSubarray {

    /*
        1438.Longest-Continuous-Subarray-With-Absolute-Diff-Less-Than-or-Equal-to-Limit
        解法1：Heap
        本题如果用multiset会非常好做。固定左端点i，不断试探右端点j能前进到哪里。[i,j]内的元素都放入一个multiset，自动就知道了最大值和最小值。如果满足mx-mn<=limit，则这段区间长度就合法。否则我们就移动一次左端点i，同时要更新这个set把nums[i]从中移出去。

        解法2：monotone deque
        multiset是o(NlogN)的解法，如果使用单调队列，可以优化到o(N)。

        我们不用multset来维护最大值和最小值，而是用一个deque来维护当前区间[i,j]的最大值，用另一个deque来维护当前区间[i,j]的最小值。其中用deque来维护一个滑动窗口的最大值，就是239.Sliding-Window-Maximum的做法。

        基本思想是：当将nums[j]加入队列时，如果发现它比队尾的元素还大，那么说明此时队尾元素可以抛弃，这是因为在未来相当一段时间内区间都会包含有j，所以最大值肯定轮不到是队尾的那个元素。这就提示我们维护的这个deque应该是单调递减的（因为新元素会把所有小的队尾元素都弹出）。每次我们要找当前区间的最大值，就只要看deque的队首元素就行。

        同理，我们维护一个单调递增的deque来获取当前区间的最小值，其中最小值也是deque的队首元素。

        注意，当j前进到区间[i,j]无法满足mx-mn<=limit时，j的前进就停止，我们要移动i。因此需要将nums[i]从这两个deque中移出。移出的操作就是看队首元素（的index）是否就是i，是的话把这个队首元素弹出就行。同时记得更新mx和mn。
    */
    int doit_(vector<int>& nums, int limit) {

        deque<int>qmax({0});
        deque<int>qmin({0});

        int j = 0;
        int ret = 1;
        int mx = nums[0], mn = nums[0];
        for (int i=0; i<nums.size() && j<nums.size(); i++)
        {
            while (mx-mn <= limit)
            {
                ret = std::max(ret, j-i+1);
                j++;
                if (j>=nums.size()) break;

                while (qmax.size()>0 && nums[j] >= nums[qmax.back()])                
                    qmax.pop_back();                
                qmax.push_back(j);
                mx = nums[qmax.front()];
                
                while (qmin.size()>0 && nums[j] <= nums[qmin.back()])                
                    qmin.pop_back();
                qmin.push_back(j);
                mn = nums[qmin.front()];
            }

            if (j>=nums.size()) break;

            if (qmax.size()>0 && qmax.front()<=i)
            {
                qmax.pop_front();
                mx = nums[qmax.front()];
            }
            if (qmin.size()>0 && qmin.front()<=i)
            {
                qmin.pop_front();
                mn = nums[qmin.front()];
            }
        }

        return ret;
    }

    int longestSubarray(vector<int>& nums, int limit) 
    {
        multiset<int>Set({nums[0]});
        int j = 0;
        int ret = 0;        
        
        for (int i=0; i<nums.size(); i++)
        {            
            while (*Set.rbegin()-*Set.begin()<=limit)
            {
                ret = std::max(ret, j-i+1);
                j++;
                if (j>=nums.size()) break;
                Set.insert(nums[j]);
            }

            if (j>=nums.size()) break;
            
            Set.erase(Set.find(nums[i]));     
        }
        
        return ret;
    }
    
    int doit_(vector<int>& nums, int limit) {
        int maxLen = 1;
        multiset<int> curEl{nums[0]};
        
        for (int r = 1, l = 0; r < nums.size(); r++) {
            curEl.insert(nums[r]);
            while (*curEl.rbegin() - *curEl.begin() > limit) {
                curEl.erase(curEl.find(nums[l]));
                l++;
            }
            maxLen = std::max(maxLen, static_cast<int>(curEl.size()));
        }
        return maxLen;
    }


public:


    /*
        Intuition
        Last week we learned,
        in 1425. Constrained Subsequence Sum
        how to get minimum in a subarray when sliding.

        This week, we need to get both the maximum and the minimum,
        at the same time.

        So I opened my post last week,
        and copy some my own codes.


        Solution 0: Binary insert and remove
        Keep an increasing list L.
        Binary insert the current element.
        If the L[L.size() - 1] - L[0] > limit,
        binary search the position of A[i] and remove it from the list.

        Time O(N^2)
        Space O(N)

        Solution 1: Use two heaps
        Time O(NogN)
        Space O(N)


    */

    /*
        Solution 2: Use TreeMap
        Use one tree map can easily get the maximum and the minimum at the same time.
        In java, we can use TreeMap to count elements.
        In cpp, it suports multi treeset, that's even better.

        Time O(NogN)
        Space O(N)
    */
    int doit_(vector<int>& A, int limit) {
        int i = 0, j;
        multiset<int> m;
        for (j = 0; j < A.size(); ++j) {
            m.insert(A[j]);
            if (*m.rbegin() - *m.begin() > limit)
                m.erase(m.find(A[i++]));
        }
        return j - i;
    }

    /*
        Solution 3: Use two deques
        Time O(N)
        Space O(N)
    */
    int doit_sliding_window(vector<int>& A, int limit) {
        deque<int> maxd, mind;
        int i = 0, j;
        for (j = 0; j < A.size(); ++j) {
            while (!maxd.empty() && A[j] > maxd.back()) maxd.pop_back();
            while (!mind.empty() && A[j] < mind.back()) mind.pop_back();
            maxd.push_back(A[j]);
            mind.push_back(A[j]);
            if (maxd.front() - mind.front() > limit) {
                if (maxd.front() == A[i]) maxd.pop_front();
                if (mind.front() == A[i]) mind.pop_front();
                ++i;
            }
        }
        return j - i;
    }

    /*
        monotonic queue, increasing and decreaing for min value and max value
    */
    int doit_monotonic_queue(vector<int>& nums, int limit) {
        
        int l = 0;
        int r = 0;
        int res = 0;
        
        deque<int> tmin{INT_MAX};
        deque<int> tmax{INT_MIN};
        
        while(r < nums.size()) {
            
            while(!tmin.empty() && tmin.back() > nums[r]) tmin.pop_back();
            while(!tmax.empty() && tmax.back() < nums[r]) tmax.pop_back();

            tmin.push_back(nums[r]);
            tmax.push_back(nums[r]);
            
            if(abs(tmax.front() - tmin.front()) <= limit)
                res = std::max(res, r - l + 1);
            
            while(l < r && abs(tmax.front() - tmin.front()) > limit){
                if(nums[l] == tmin.front()) tmin.pop_front();
                if(nums[l] == tmax.front()) tmax.pop_front();
                l++;
            }

            r++;
        }
        
        return res;
    }
};