/*
 # 962. Maximum Width Ramp

 # Given an array A of integers, a ramp is a tuple (i, j) for which i < j and A[i] <= A[j].
 # The width of such a ramp is j - i.

 # Find the maximum width of a ramp in A.  If one doesn't exist, return 0.


 # Example 1:

 # Input: [6,0,8,2,1,5]
 # Output: 4
 # Explanation:
 # The maximum width ramp is achieved at (i, j) = (1, 5): A[1] = 0 and A[5] = 5.

 # Example 2:

 # Input: [9,8,1,0,1,9,4,0,4,1]
 # Output: 7
 # Explanation:
 # The maximum width ramp is achieved at (i, j) = (2, 9): A[2] = 1 and A[9] = 1.


 # Note:

 # 2 <= A.length <= 50000
 # 0 <= A[i] <= 50000
 
 
 */

#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <stack>

using std::stack;
using std::map;
using std::vector;
using std::multimap;


class MaxWidthRamp {

    /*
        962.Maximum-Width-Ramp
        解法1
        比赛的时候，比较容易想到的是o(NlogN)的解法。

        遍历这个数组，同时维护一个数值递减的栈。比如，我们考察A[i]的时候，就会在这个stack里通过二分法，找到恰好小于等于A[i]的数以及它对应的索引（比如是j）。那么i-j就是考察A[i]时能得到的"最宽"的pair。
        然后我们需要将A[i]加入这个栈中，可以想象，如果A[i]大于等于栈顶元素，那么A[i]就没有再入栈的意义，这是因为此时的栈顶元素，数值既比A[i]小，索引也比i小，无论如何在后续的处理中都是比A[i]更好的选择。
        于是，依此处理完所有的A[i]，找到最宽的(j,i)配对，就是答案。

        以上的算法在实际代码过程中需要用到较多的数据结构。我们其实需要维护两个栈，一个栈存数值，一个栈存索引。两个栈的压入都是同步的。但是二分法查找的时候是用的数值栈，而在更新(j,i)配对的时候用的是索引栈。

        另外，由于这是一个递减的栈，所以用lower_bound的时候，要注意用逆向的迭代器auto it = upper_bound(q.rbegin(),q.rend(),nums[i])在根据迭代器计算索引位置的时候：int k = it-q.rbegin()表示在数组中倒数的位置。

        解法2
        本题还有更惊艳的 O(N) 的解法。

        同样遍历这个数组，同时维护一个数组递减的栈。但是在生成这个栈的过程中，我们并不针对每个A[i]取找最宽的配对。而是直接先把这个栈生成完毕。

                for i in range(len(A)):
                    if len(Stack)==0 or A[Stack[-1]]>=A[i]:
                        Stack.append(i)
        绝妙的下一步是：从后往前依次考察A，对于每个A[i]，我们从栈尾依次弹出元素直至遇到一个恰好小于等于A[i]的索引j，那么(j,i)就是关乎A[i]我们能得到的最宽的配对。
        至于那些已经弹出栈的元素，其实丢了就丢了，并不会对答案有更多的贡献。比如说，j+1和i-1即使配对成功，也不能超越(j,i)的宽度。这样将A从后往前扫一遍，就能找到最宽的配对。
    */
    int maxWidthRamp(vector<int>& nums) 
    {
        vector<int>q;
        vector<int>idx;
        int result = 0;
        
        for (int i=0; i<nums.size();i++)
        {           
            if (q.size()==0 || q.size()>0 && nums[i]<q.back())
            {
                q.push_back(nums[i]);
                idx.push_back(i);
            }
            else
            {
                auto it = upper_bound(q.rbegin(),q.rend(),nums[i]);
                int k = it-q.rbegin();
                k = q.size()-1-k + 1;
                result = std::max(result, i-idx[k]);                
            }            
        }        
        return result;
    }


public:
    /*
    """
        Solution 1
        Intuition:
        Keep a decreasing stack.
        For each number,
        binary search the first smaller number in the stack.

        When the number is smaller the the last,
        push it into the stack.

        Time Complexity:
        O(NlogN)
    """


    """
        Solution 2
        Improve the idea above.
        Still one pass and keep a decraesing stack.

        Time Complexity:
        O(N)
    """
    */
    int doit_monotonic_stack(vector<int>& A) {
        stack<int> s;
        int res = 0, n = A.size();

        // Decreasing stack
        for (int i = 0; i < n; ++i)
            if (s.empty() || A[s.top()] > A[i]) s.push(i);

        // backwarding find the target. find a pair (i, j). Then anyone possible one should (i1, j1, i1< i <= j1 < j) 
        // i > res, there is no longer one, after i > res.
        for (int i = n - 1; i > res; --i)
            while (!s.empty() && A[s.top()] <= A[i]){
                res = std::max(res, i - s.top()); 
                s.pop();
            }
                
        return res;
    }


    int doit_sort(vector<int>& A) {
        
        vector<int> range(A.size());
        std::iota(begin(range), end(range), 0);
        std::sort(begin(range), end(range), [&](auto a, auto b) {
           return A[a] < A[b] || (A[a] == A[b] && a < b);
        });
        
        int ans = 0, mini = range[0];
        for (auto c : range) {
            ans = std::max(ans, c - mini);
            mini = std::min(mini, c);
        }
        
        return ans;
    }

    /*
        Monotonic queue, we iterate form left to right, so index is monotonic increasing. 
        the queue will be queue A[i < j], A value is monotoic increasing, and we attach value, i < j. from index, it also decreasing, index[A[i]] > index[A[j]]
    */
    int doit_binary_search(vector<int>& A) {
        
        map<int, int, std::greater<int>> m;
        int maxv = 0;

        for (int i = 0; i < A.size(); i++) { 
            auto it = m.lower_bound(A[i]);
            if (it == m.end()) {
                m[A[i]] = i;
            } else {
                maxv = std::max(maxv, i - it->second);
            }
        }
        return maxv;
    }

    int doit_(vector<int>& A) {
        multimap<int, int> map;
        for (int i = 0; i < A.size(); i++) {
            map.insert({ A[i], i });
        }

        int minIndex = INT_MAX;
        int result = 0;
        for (auto& it : map) {
            result = std::max(result, it.second - minIndex);
            minIndex = std::min(minIndex, it.second);
        }
        return result;
    }

    int doit_binary_search_monotonic_queue(vector<int>&& A) {
        
        int n = A.size(), ans = 0;
        map<int, int> queue{{A[n-1], n-1}};

        for (int i = n-2; i > -1; i--) {

            auto it = queue.upper_bound(A[i]);

            if (it == queue.end()) {
                queue.insert({A[i], i});
            } else {
                ans = std::max(ans, it->second - i);
            }
        }
        return ans;
    }
};