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
    int doit_stack(vector<int>& A) {
        stack<int> s;
        int res = 0, n = A.size();

        for (int i = 0; i < n; ++i)
            if (s.empty() || A[s.top()] > A[i]) s.push(i);

        for (int i = n - 1; i > res; --i)
            while (!s.empty() && A[s.top()] <= A[i])
                res = std::max(res, i - s.top()), s.pop();
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
            result = max(result, it.second - minIndex);
            minIndex = min(minIndex, it.second);
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

void test_962_maximum_width_range() {
    
    auto res = MaxWidthRamp().doit(vector<int>{3,28,15,1,4,12,6,19,8,15,3,9,6,4,13,12,6,12,10,1,2,1,4,1,4,0,0,1,1,0});
    
    return;
}
