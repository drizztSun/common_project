/*
907. Sum of Subarray Minimums

Given an array of integers A, find the sum of min(B), where B ranges over every (contiguous) subarray of A.

Since the answer may be large, return the answer modulo 10^9 + 7.

 

Example 1:

Input: [3,1,2,4]
Output: 17
Explanation: Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.  Sum is 17.
 

Note:

1 <= A.length <= 30000
1 <= A[i] <= 30000
 

 

Example 1:

Input: arr = [3,1,2,4]
Output: 17
Explanation: 
Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
Sum is 17.
Example 2:

Input: arr = [11,81,94,43,3]
Output: 444
 

Constraints:

1 <= arr.length <= 3 * 104
1 <= arr[i] <= 3 * 104


*/
#include <vector>
#include <stack>

using std::stack;
using std::vector;


class SumSubarrayMins {

public:

    /*
    Intuition:
    I guess this is a general intuition for most solution.
    res = sum(A[i] * f(i))
    where f(i) is the number of subarrays,
    in which A[i] is the minimum.

    To get f(i), we need to find out:
    left[i], the length of strict bigger numbers on the left of A[i],
    right[i], the length of bigger numbers on the right of A[i].

    Then,
    left[i] + 1 equals to
    the number of subarray ending with A[i],
    and A[i] is single minimum.

    right[i] + 1 equals to
    the number of subarray starting with A[i],
    and A[i] is the first minimum.

    Finally f(i) = (left[i] + 1) * (right[i] + 1)

    For [3,1,2,4] as example:
    left + 1 = [1,2,1,1]
    right + 1 = [1,3,2,1]
    f = [1,6,2,1]
    res = 3 * 1 + 1 * 6 + 2 * 2 + 4 * 1 = 17


    Explanation:
    To calculate left[i] and right[i],
    we use two increasing stacks.

    It will be easy if you can refer to this problem and my post:
    901. Online Stock Span
    I copy some of my codes from this solution.


    Complexity:
    All elements will be pushed twice and popped at most twice
    O(n) time, O(n) space
    */
    int doit_stack(vector<int>& A) {

        long res = 0, n = A.size(), mod = 1e9 + 7;
        
        vector<int> left(n), right(n);
        stack<std::pair<int, int>> s1,s2;
        
        for (int i = 0; i < n; ++i) {
            int count = 1;
            while (!s1.empty() && s1.top().first > A[i]) {
                count += s1.top().second;
                s1.pop();
            }
            s1.push({A[i], count});
            left[i] = count;
        }
        
        for (int i = n - 1; i >= 0; --i) {
            int count = 1;
            while (!s2.empty() && s2.top().first >= A[i]) {
                count += s2.top().second;
                s2.pop();
            }
            s2.push({A[i], count});
            right[i] = count;
        }
        
        for (int i = 0; i < n; ++i)
            res = (res + (long)A[i] * left[i] * right[i]) % mod;
        return res;
    }

    /*
    Improvement
    1.Here I record (A[i], count) in the stack.
    We can also only record index.
    2. For left part and right part, the logic is same.
    So for each, I used one stack and one pass.
    This process can be optimized to one pass using one stack in total.

    O(n) time, O(n) space

    */
    int doit_stack_1(vector<int> A) {
        long res = 0, n = A.size(), mod = 1e9 + 7, j, k;
        stack<int> s;
        for (int i = 0; i <= n; ++i) {
            while (!s.empty() && A[s.top()] > (i == n ? 0 : A[i])) {
                j = s.top(), s.pop();
                k = s.empty() ? -1 : s.top();
                res = (res + (long)A[j] * (i - j) * (j - k)) % mod;
            }
            s.push(i);
        }
        return res;
    }

    int doit_(vector<int>& arr) {
        
        int n = arr.size();
        int hmod = 1e9 + 7;

        vector<int> left(n), right(n);
        stack<int> stleft, stright;

        for (int i = 0; i < n; i++) {

            while (!stleft.empty() && arr[i] < arr[stleft.top()]) {
                stleft.pop();
            }
            left[i] = stleft.empty() ? -1 : stleft.top();
            stleft.push(i);
        }

        for (int i = n - 1; i >= 0; i--) {

            while (!stright.empty() && arr[i] < arr[stright.top()]) {
                stright.pop();
            } 
            right[i] = stright.empty() ? n : stright.top();
            stright.push(i);
        }

        long long  ans = 0;
        for (int i = 0; i < n; i++)
            ans = (ans + (i - left[i]) * (right[i] - i) * arr[i]) % hmod;

        return ans;
    }
};