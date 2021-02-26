/*
1425. Constrained Subsequence Sum


Given an integer array nums and an integer k, return the maximum sum of a non-empty subsequence of that array such that for every two consecutive integers in the subsequence, 
nums[i] and nums[j], where i < j, the condition j - i <= k is satisfied.

A subsequence of an array is obtained by deleting some number of elements (can be zero) from the array, leaving the remaining elements in their original order.

 

Example 1:

Input: nums = [10,2,-10,5,20], k = 2
Output: 37
Explanation: The subsequence is [10, 2, 5, 20].
Example 2:

Input: nums = [-1,-2,-3], k = 1
Output: -1
Explanation: The subsequence must be non-empty, so we choose the largest number.
Example 3:

Input: nums = [10,-2,-10,-5,20], k = 2
Output: 23
Explanation: The subsequence is [10, -2, -5, 20].
 

Constraints:

1 <= k <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4


*/
#include <vector>
#include <deque>
#include <set>

using std::multiset;
using std::deque;
using std::vector;


class ConstrainedSubsetSum {

public:

    /*
        Intuition
        We need to know the maximum in the window of size k.
        Use heqp will be O(NlogN)
        Use TreeMap will be O(NlogK)
        Use deque will be O(N)
        Done. (If not done, continue read)


        Prepare
        How about google "sliding window maximum",
        and make sure you understand 239. Sliding Window Maximum
        Done. (If not done, continue read)


        Explanation
        Update res[i],
        where res[i] means the maximum result you can get if the last element is A[i].

        I directly modify on the input A,
        if you don't like it,
        use a copy of A

        Keep a decreasing deque q,
        deque[0] is the maximum result in the last element of result.

        If deque[0] > 0. we add it to A[i]

        In the end, we return the maximum res.


        Complexity
        Because all element are pushed and popped at most once.
        Time O(N)

        Because at most O(K) elements in the deque.
        Space O(K)


        More
        Deque can be widely used in all bfs problems.
        For more complecated usage,
        I recall this problem
        862. Shortest Subarray with Sum at Least K

        Monotonic queue
    */
    int doit_slidingwindow_monotonicqueue(vector<int>& A, int k) {
    
        deque<int> q;
        int res = A[0];

        for (int i = 0; i < A.size(); ++i) {
        
            A[i] += q.size() ? q.front() : 0;
            res = std::max(res, A[i]);
        
            while (q.size() && A[i] > q.back())
                q.pop_back();
        
            if (A[i] > 0)
                q.push_back(A[i]);

            if (i >= k && q.size() && q.front() == A[i - k])
                q.pop_front();
        }

        return res;
    }

    /*
    
                1425.Constrained-Subsequence-Sum
        解法1：DP
        显然，如果设计dp[i]表示以nums[i]结尾的subsequence能够得到的满足条件的最大和，那么我们可以很轻松地写出转移方程：

        dp[i] = max{nums[i], dp[i-k] + nums[i]}, k=1,2,...,K
        那么这显然是一个O(NK)级别的算法，根据数据范围肯定会超时。

        解法2：Heap
        一个优化的思路就是我们在这K个candidate中高效地找到最大值。这可以用自动排序的容器比如说multiset来实现。我们在Set中维护最近的K个dp值并保持升序，这样每次直接在Set尾部取值就行。
        但是注意的是，每一个回合我们需要弹出最老的那个DP值（即dp[i-k]），那个值是什么我们需要额外记录，并且手工从Set中删除掉。

        解法2：单调队列 mono deque
        数据结构“双端队列dequeu”不是很常用，但其最重要的用法就是维护单调队列。

        我们想象，如果最近得到了一个dp[i]，如果它比我们以前所遇到的dp值都要大，那么就意味着以前所有的dp值我们都不需要再保留？为什么？因为i是最近的index，而且dp[i]又最大，这种“又新又大”的特点使得它在两个维度上都是最优的解。
        因此，在i之后的任何元素j都只可能与i关联，而不会与i之前的元素关联。所以我们不用保留任何i之前的dp值了。

        这就提示了我们，我们需要保留的dp值应该是一个单调递减的序列。队列首端的元素最大，但是比较老；队列末端的元素最小，但是比较新。它们有各自的优势。对于任何新来的元素nums[i]，它要与队列中的哪个元素关联，都是有可能的。
        
        具体的方案是：首先看队列首的元素j（因为它最大），如果满足在index上的条件i-j>=K，那么就以为着关联成功，dp[i]=dp[j]+nums[i]。否则说明j这个index太老了，无法满足i-j>=k，以后也肯定不会再用到了，可以直接踢出队列。就这样不停地后移j，直到找到合适的元素。

        再更新dp[i]之后，我们也需要将其加入队列。注意到之前的结论，我们需要保持队列单调递减。如果队列尾部的元素dp[j]比dp[i]小，那么我们就可以直接弹出j。道理已经解释过了，j相比于i而言“又老又小”，总是不合算的。

        用单调队列的做法，时间复杂度就是o(N).
    */
    int doit_slidingwindow_monotonicqueue(vector<int>& nums, int k) 
    {
        int n = nums.size();
        vector<int>dp(n,0);
        deque<int>q;
        
        int ret = INT_MIN;
        for (int i=0; i<n; i++)
        {
            while (q.size()>0 && q.front() < i-k)
                q.pop_front();
            
            dp[i] = nums[i];
            if (q.size()>0) 
                dp[i] = std::max(dp[i], dp[q.front()] + nums[i]);
            
            while (q.size()>0 && dp[q.back()] <= dp[i])
                q.pop_back();
            q.push_back(i);
        }
                
        for (int i=0; i<n; i++)
            ret = std::max(ret, dp[i]);
        return ret;
    }

    int doit_heap_monotonicqueue(vector<int>& nums, int k) 
    {
        int n = nums.size();
        multiset<int>Set;
        vector<int>dp(n,0);
        
        int ret = INT_MIN;
        
        for (int i=0; i<n; i++)
        {
            if (Set.size() > k && i-k-1>=0)
                Set.erase(Set.lower_bound(dp[i-k-1]));
            
            dp[i] = nums[i];
            
            if (Set.size()>0) 
                dp[i] = std::max(dp[i], *Set.rbegin()+nums[i]);
            
            ret = std::max(ret, dp[i]);
            
            Set.insert(dp[i]);            
        }
        
        return ret;
    }

    int doit_heap_monotonicqueue_1(vector<int>& nums, int k) {
        
        int res = -1;
        deque<std::pair<int, int>> mq;
        
        for (int i = 0; i < nums.size(); i++) {
            
            while (!mq.empty() && i - mq.front().second > k)
                mq.pop_front();
            
            int cur = nums[i] + std::max(0, mq.empty() ? 0 : mq.front().first);
            
            res = std::max(res, cur);
            
            while (!mq.empty() && mq.back().first <= cur) {
                mq.pop_back();
            }
            
            mq.push_back({cur, i});
        }
        
        return res;
        
    }

};