/*
862. Shortest Subarray with Sum at Least K

Return the length of the shortest, non-empty, contiguous subarray of A with sum at least K.

If there is no non-empty subarray with sum at least K, return -1.

 

Example 1:

Input: A = [1], K = 1
Output: 1
Example 2:

Input: A = [1,2], K = 4
Output: -1
Example 3:

Input: A = [2,-1,2], K = 3
Output: 3
 

Note:

1 <= A.length <= 50000
-10 ^ 5 <= A[i] <= 10 ^ 5
1 <= K <= 10 ^ 9
*/
#include <vector>
#include <deque>
#include <map>

using std::map;
using std::deque;
using std::vector;

class ShortestSubarray {


    /*
        862.Shortest-Subarray-with-Sum-at-Least-K
        解法１
        遇到continous subarray的题目,最常用的策略就是构建累加和preSum数组.这样,此题就转化为在preSum中找到两个间距最短的位置j和i,使得preSum[j]-preSum[i]>=K.对于这种题,通常我们会遍历i,然后在每个i之前的index查找满足条件的最小j.

        对于此类问题,我们会把所有经历过的preSum都存在一个有序集合里.这里我们使用map,记录曾经出现过的preSum以及它对应的在数组中的index.注意到如果遇到相同的preSum,后加入的index会覆盖先前的值,这是合理的:因为对于任何preSum我们恰需要更新的,较大的index来保持[j,i]之间的距离最短.

        假设我们考虑某个i,那么在i之前出现的所有preSum都已经在map里.此时如果map里所有键小于preSum[i]-K的preSum都是符合要求的.我们只要遍历这些键对应的值(也就是index),找到最大的那个就是距离i最近的j.

        这样的算法仍然会超时,主要是因为上面遍历键值的过程花时间.怎么优化呢?

        我们每次在将{preSum[i],i}插入map时,插入的可能是map中间的某个位置.我们发现,此时所有大于preSum[i]的键都是没有意义的,因为你preSum[i]带来了当前最新(也是最大)的值i.举个例子,如果此时目标键为k且k>preSum[i],那么在map中搜索所有小于等于k的"键"并且找它们之中最大的"值",得到的结果必然是i.所以每个回合里,我们插入{preSum[i],i}之后,可以将map从后往前不断删除元素,直至遇到preSum[i]为止,这样可以使得map始终保持精简.

        上面这个操作会带来一个意想不到的好处!那就是我们不需要找在map里遍历所有小于等于preSum[i]-K的所有键并求最大的值．因为这些"键"对应的最大"值"就存在于离preSum[i]-K最近的那个键里面．更本质的原因是，map里不仅键是递增的，而且对应的值也是递增的．

        所以每个回合的过程可以总结为:

        1.在map里找到小于并且离preSum[i]-K最近的那个键,其值就是所需的满足条件的最大j
        2.在map里插入{preSum[i],i}
        3.在map删除所有大于preSum[i]的键

        解法2
        上述的解法复杂度是o(NlogN),但实际上还有更好的o(N)的解法．

        我们维护一个双端队列q，里面存储的q[j]表示的是一个递增的index的序列．同时要保证presum[q[j]]也是递增的．是不是有点绕？

        假设我们现在处理A[i]，其对应的前缀和是presum[i]，那么我们想在这个队列里面找到一个位置j，恰好使得presum[q[j]]+K<=presum[i]，那么队列中的q[0]~q[j]这些index都是满足at least K条件的位置，我们可以找其中最大的一个，比如说q[j']，就能使得subarray长度i-q[j']是最小的．接下来的操作很重要，我们可以将q[0]到q［j']都从队列前端弹出．因为以后的i会更大，如果它在队列中找到的满足at least K条件的左边界位置比q[j']小的话，不会比已经得到的result更好．所以任何早于q[j']的队列元素对以后的搜索都没有帮助．

        接下来，我们需要将presum[i]的信息加入这个队列．我们的策略是不断在后端弹出元素，直到presum[q.back()]<presum[i]，即保证这个队列对应的presum依然是递增的．这个比较好理解，和解法１的道理一样．因为当前的i是最靠后，那么所有队里中已有的presum大于presum[i]的元素都是没有意义的，完全可以被i取代（即依然保证at least K同时能使subarray更短）．

        所以每次处理一个presum[i]时，遵循上述两个步骤，就能保证队列存储的是一个递增的index序列，而且对应的presum也是递增的．
    */
    int doit_heap(vector<int>& A, int K) 
    {        
        int N = A.size();
        
        A.insert(A.begin(),0);
        
        vector<int>Sum(N+1,0);
        map<int,int>Map;
        
        Map[0] = 0;        
        int ret = INT_MAX;
        
        for (int i=1; i<=N; i++)
        {
            Sum[i]=Sum[i-1]+A[i];
                        
            int num = Sum[i]-K;

            auto it = Map.upper_bound(num);            
            if (it!=Map.begin())
            {                
                it = prev(it,1);
                ret = std::min(ret, i-it->second);
            }
            
            Map[Sum[i]] = i;
            while (Map.rbegin()->first!=Sum[i])
                Map.erase(Map.rbegin()->first);            
        }
        
        return (ret==INT_MAX) ? -1 : ret;
    }

    int doit_monotonic_queue(vector<int>& A, int K) 
    {
        int N = A.size();
        vector<int>presum(N+1,0);        
        for (int i=0; i<N; i++) presum[i+1]=presum[i]+A[i];
        
        deque<int>q;
        int result = INT_MAX;
        for (int i=0; i<=N; i++)
        {
            while (q.size()>0 && presum[q.front()]+K<=presum[i])
            {
                result = std::min(result,i-q.front());
                q.pop_front();
            }
            while (q.size()>0 && presum[q.back()]>=presum[i])
                q.pop_back();
            q.push_back(i);
        }
        return result==INT_MAX? -1:result;
        
    }

public:
    /*
        Approach 1: Sliding Window
        Intuition

        We can rephrase this as a problem about the prefix sums of A. Let P[i] = A[0] + A[1] + ... + A[i-1]. We want the smallest y-x such that y > x and P[y] - P[x] >= K.

        Motivated by that equation, let opt(y) be the largest x such that P[x] <= P[y] - K. We need two key observations:

        If x1 < x2 and P[x2] <= P[x1], then opt(y) can never be x1, as if P[x1] <= P[y] - K, then P[x2] <= P[x1] <= P[y] - K but y - x2 is smaller. This implies that our candidates x for opt(y) will have increasing values of P[x].

        If opt(y1) = x, then we do not need to consider this x again. For if we find some y2 > y1 with opt(y2) = x, then it represents an answer of y2 - x which is worse (larger) than y1 - x.

        Algorithm

        Maintain a "monoqueue" of indices of P: a deque of indices x_0, x_1, ... such that P[x_0], P[x_1], ... is increasing.

        When adding a new index y, we'll pop x_i from the end of the deque so that P[x_0], P[x_1], ..., P[y] will be increasing.

        If P[y] >= P[x_0] + K, then (as previously described), we don't need to consider this x_0 again, and we can pop it from the front of the deque.


        Complexity Analysis

        Time Complexity: O(N), where NN is the length of A.

        Space Complexity: O(N).
        
        Monotonic queue
    */

    int doit_slidingwindow_monotonicqueue(vector<int>& A, int K) {
        int N = A.size(), res = N + 1;
        deque<int> d;

        for (int i = 0; i < N; i++) {
        
            if (i > 0)
                A[i] += A[i - 1];

            if (A[i] >= K)
                res = std::min(res, i + 1);

            // pop out it, becuase it is useless. any later one make it larget than k will be larger than current one.
            while (d.size() > 0 && A[i] - A[d.front()] >= K) {
                res = std::min(res, i - d.front()); 
                d.pop_front();
            }

            // Monotonic queue increasing, save index 
            while (d.size() > 0 && A[i] <= A[d.back()])
                d.pop_back();

            d.push_back(i);
        }
        
        return res <= N ? res : -1;
    }

    /*
        Prepare
        From @Sarmon:
        "What makes this problem hard is that we have negative values.
        If you haven't already done the problem with positive integers only,
        I highly recommend solving it first"

        Minimum Size Subarray Sum

        Explanation
        Calculate prefix sum B of list A.
        B[j] - B[i] represents the sum of subarray A[i] ~ A[j-1]
        Deque d will keep indexes of increasing B[i].
        For every B[i], we will compare B[i] - B[d[0]] with K.


        Complexity:
        Every index will be pushed exactly once.
        Every index will be popped at most once.

        Time O(N)
        Space O(N)


        How to think of such solutions?
        Basic idea, for array starting at every A[i], find the shortest one with sum at leat K.
        In my solution, for B[i], find the smallest j that B[j] - B[i] >= K.
        Keep this in mind for understanding two while loops.


        What is the purpose of first while loop?
        For the current prefix sum B[i], it covers all subarray ending at A[i-1].
        We want know if there is a subarray, which starts from an index, ends at A[i-1] and has at least sum K.
        So we start to compare B[i] with the smallest prefix sum in our deque, which is B[D[0]], hoping that [i] - B[d[0]] >= K.
        So if B[i] - B[d[0]] >= K, we can update our result res = min(res, i - d.popleft()).
        The while loop helps compare one by one, until this condition isn't valid anymore.


        Why we pop left in the first while loop?
        This the most tricky part that improve my solution to get only O(N).
        D[0] exists in our deque, it means that before B[i], we didn't find a subarray whose sum at least K.
        B[i] is the first prefix sum that valid this condition.
        In other words, A[D[0]] ~ A[i-1] is the shortest subarray starting at A[D[0]] with sum at least K.
        We have already find it for A[D[0]] and it can't be shorter, so we can drop it from our deque.


        What is the purpose of second while loop?
        To keep B[D[i]] increasing in the deque.


        Why keep the deque increase?
        If B[i] <= B[d.back()] and moreover we already know that i > d.back(), it means that compared with d.back(),
        B[i] can help us make the subarray length shorter and sum bigger. So no need to keep d.back() in our deque.

    */
    int doit_slidingwindow_1(vector<int> A, int K) {
        int N = A.size(), res = N + 1;
        deque<int> d;
        for (int i = 0; i < N; i++) {
            if (i > 0)
                A[i] += A[i - 1];
            
            if (A[i] >= K)
                res = std::min(res, i + 1);

            while (d.size() > 0 && A[i] - A[d.front()] >= K)
                res = std::min(res, i - d.front()), d.pop_front();
            
            while (d.size() > 0 && A[i] <= A[d.back()])
                d.pop_back();
            
            d.push_back(i);
        }
        return res <= N ? res : -1;
    }
};