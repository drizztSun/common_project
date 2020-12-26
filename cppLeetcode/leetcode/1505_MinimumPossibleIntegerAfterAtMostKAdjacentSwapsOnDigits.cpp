/*
1505. Minimum Possible Integer After at Most K Adjacent Swaps On Digits

Given a string num representing the digits of a very large integer and an integer k.

You are allowed to swap any two adjacent digits of the integer at most k times.

Return the minimum integer you can obtain also as a string.

 

Example 1:


Input: num = "4321", k = 4
Output: "1342"
Explanation: The steps to obtain the minimum integer from 4321 with 4 adjacent swaps are shown.
Example 2:

Input: num = "100", k = 1
Output: "010"
Explanation: It's ok for the output to have leading zeros, but the input is guaranteed not to have any leading zeros.
Example 3:

Input: num = "36789", k = 1000
Output: "36789"
Explanation: We can keep the number without any swaps.
Example 4:

Input: num = "22", k = 22
Output: "22"
Example 5:

Input: num = "9438957234785635408", k = 23
Output: "0345989723478563548"
 

Constraints:

1 <= num.length <= 30000
num contains digits only and doesn't have leading zeros.
1 <= k <= 10^9


https://zxi.mytechroad.com/blog/greedy/leetcode-1505-minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/

*/
#include <string>
#include <vector>
#include <queue>

using std::queue;
using std::vector;
using std::string;


class Fenwick {

public:

    explicit Fenwick(int n): _sums(n+1) {}

    void update(int i, int delta) {
        i++;
        while (i < _sums.size()) {
            _sums[i] += delta;
            i += i & -i;
        }
    }

    int query(int i) {
        i++;
        int ans = 0;
        while (i > 0) {
            ans += _sums[i];
            i -= i & -i;
        }
        return ans;
    }

    vector<int> _sums;
};


class MinimumPossibleIntegerAfterKSwap {

public:
    
    /*
    Observation:

    1. If k is "large enough", the answer should be the sorted string. minNum("543210", inf) = "012345".

    2. Else fund the smallest movalbe number and move it to the front. minNum("543210", 2) = "354210"

    Very similar to bubble sort. We can do it recursively to build the right part of the string.

    minNum("543210", 10)

    = "0" + minNum("54321", 5)
    = "0" + "1" + minNUm("54321", 1)

    Time O(n^2)

    Constraints:

    1 <= num.length <= 30000
    num contains digits only and doesn’t have leading zeros.
    1 <= k <= 10^9
    Solution: Greedy + Recursion (Update: TLE after 7/6/2020)
    Move the smallest number to the left and recursion on the right substring with length equals to n -= 1.

    4321 k = 4 => 1 + solve(432, 4-3) = 1 + solve(432, 1) = 1 + 3 + solve(42, 0) = 1 + 3 + 42 = 1342.

    Time complexity: O(n^2)
    Space complexity: O(1)
    */
    string doit_greedy_recursive(string num, int k) {
        const int n = num.size();
        if (k >= n * (n - 1) / 2) {
            sort(begin(num), end(num));
            return num;
        }
        
        int s = 0;
        while (k > 0 && s < n) {
            auto bit = begin(num);
            auto it = std::min_element(bit + s, bit + std::min(s + k + 1, n));
            k -= distance(bit + s, it);
            rotate(bit + (s++), it, next(it));
        }
        return num;

    }

    /*

        cost of nums[i] is moving it to the front part of the stirng, and behead any char less than it. there are maybe multiple ones has been movec.
        so the cost is dynamic for each char, cost(nums[i]) = i - {how many chars has been moved before him}


        Moving elements in a string is a very expensive operation, basically O(n) per op. Actually, we don’t need to move the elements physically, 
        instead we track how many elements before i has been moved to the “front”. Thus we know the cost to move the i-th element to the “front”, 
        which is i – elements_moved_before_i or prefix_sum(0~i-1) if we mark moved element as 1.

        We know BIT / Fenwick Tree is good for dynamic prefix sum computation which helps to reduce the time complexity to O(nlogn).

        Time complexity: O(nlogn)
        Space complexity: O(n)
    */
    string doit_BIT_fenwick(string nums, int k) {

        int n = nums.size();
        vector<queue<int>> pos;
        for (int i = 0; i < nums.size(); i++)
            pos[nums[i] - '0'].push(i);

        Fenwick tree(n);
        vector<bool> used(n, false);
        string ans;

        while (k > 0 && ans.length() < n) {

            for (int cur = 0; cur < 10; cur++) {
                if (pos[cur].empty()) continue;

                const int i = pos[cur].front();
                const int cost = i - tree.query(i-1);

                if (cost > k)
                    continue;
                
                k -= cost;
                tree.update(i, 1);
                pos[cur].pop();
                used[i] = true;
                break;
            }
        }

        for (int i = 0; i < n; i++)
            if (!used[i])
                ans += nums[i];
        return ans;
    }
};