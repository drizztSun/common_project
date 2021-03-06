/*
875. Koko Eating Bananas

Koko loves to eat bananas.  There are N piles of bananas, the i-th pile has piles[i] bananas.  The guards have gone and will come back in H hours.

Koko can decide her bananas-per-hour eating speed of K.  Each hour, she chooses some pile of bananas, and eats K bananas from that pile. 
If the pile has less than K bananas, she eats all of them instead, and won't eat any more bananas during this hour.

Koko likes to eat slowly, but still wants to finish eating all the bananas before the guards come back.

Return the minimum integer K such that she can eat all the bananas within H hours.

 

Example 1:

Input: piles = [3,6,7,11], H = 8
Output: 4
Example 2:

Input: piles = [30,11,23,4,20], H = 5
Output: 30
Example 3:

Input: piles = [30,11,23,4,20], H = 6
Output: 23
 

Constraints:

1 <= piles.length <= 10^4
piles.length <= H <= 10^9
1 <= piles[i] <= 10^9
*/
#include <vector>
#include <algorithm>

using std::vector;

class MinEatingSpeed {

    /*
        Explanation
        Binary search between [1, 10^9] or [1, max(piles)] to find the result.
        Time complexity: O(NlogM)

        (p + m - 1) / m equal to ceil(p / m) (just personal behavior)

        Here you find another similar problem.
        774. Minimize Max Distance to Gas Station


        Complexity
        Time O(Nlog(MaxP))
        Space O(1)
    */
    int doit_binary_search(vector<int>& piles, int H) {
        int l = 1, r = 1000000000;
        while (l < r) {
            int m = (l + r) / 2, total = 0;
            for (int p : piles)
                total += (p + m - 1) / m;
            if (total > H)
                l = m + 1;
            else
                r = m;
        }
        return l;
    }

public:

    int doit_binary_search(vector<int>& piles, int H) {

        auto valid = [&](int k) {
            int ans = 0;
            for (auto c: piles) {
                ans += (c - 1) / k + 1;
            }
            return ans <= H;
        };
        
        int low = 1, high = *max_element(begin(piles), end(piles));

        while (low < high) {
            int mid = (low + high) / 2;
            if (valid(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        return low;
    }
};