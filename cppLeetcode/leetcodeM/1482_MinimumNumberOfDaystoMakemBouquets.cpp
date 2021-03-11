/*
1482. Minimum Number of Days to Make m Bouquets

Given an integer array bloomDay, an integer m and an integer k.

We need to make m bouquets. To make a bouquet, you need to use k adjacent flowers from the garden.

The garden consists of n flowers, the ith flower will bloom in the bloomDay[i] and then can be used in exactly one bouquet.

Return the minimum number of days you need to wait to be able to make m bouquets from the garden. If it is impossible to make m bouquets return -1.



Example 1:

Input: bloomDay = [1,10,3,10,2], m = 3, k = 1
Output: 3
Explanation: Let's see what happened in the first three days. x means flower bloomed and _ means flower didn't bloom in the garden.
We need 3 bouquets each should contain 1 flower.
After day 1: [x, _, _, _, _]   // we can only make one bouquet.
After day 2: [x, _, _, _, x]   // we can only make two bouquets.
After day 3: [x, _, x, _, x]   // we can make 3 bouquets. The answer is 3.
Example 2:

Input: bloomDay = [1,10,3,10,2], m = 3, k = 2
Output: -1
Explanation: We need 3 bouquets each has 2 flowers, that means we need 6 flowers. We only have 5 flowers
so it is impossible to get the needed bouquets and we return -1.
Example 3:

Input: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3
Output: 12
Explanation: We need 2 bouquets each should have 3 flowers.
Here's the garden after the 7 and 12 days:
After day 7: [x, x, x, x, _, x, x]
We can make one bouquet of the first three flowers that bloomed. We cannot make another bouquet from the last three flowers
that bloomed because they are not adjacent.
After day 12: [x, x, x, x, x, x, x]
It is obvious that we can make two bouquets in different ways.
Example 4:

Input: bloomDay = [1000000000,1000000000], m = 1, k = 1
Output: 1000000000
Explanation: You need to wait 1000000000 days to have a flower ready for a bouquet.
Example 5:

Input: bloomDay = [1,10,2,9,3,8,4,7,5,6], m = 4, k = 2
Output: 9


Constraints:

bloomDay.length == n
1 <= n <= 10^5
1 <= bloomDay[i] <= 10^9
1 <= m <= 10^6
1 <= k <= n


*/
#include <vector>
#include <algorithm>
#include <numeric>

using std::vector;

class MinimumNumberOfDaystoMakeBouquets {

    /*
        1482.Minimum-Number-of-Days-to-Make-m-Bouquets
        可以想见，如果天数越靠后，那么可供选择的花就越多，能找到连续的k朵花的概率就越大。这是一个单调递增的过程。所以这非常适合用二分搜值的方法。如果t天的时候，无法找到连续的k多花，那么我们就猜更大的t并检验是否能成功，反之就猜测较小的t。
    */
    int minDays(vector<int>& bloomDay, int m, int k) 
    {
        int n = bloomDay.size();
        if (n<m*k) return -1;
        
        int left = 0;
        int right = INT_MAX;
        while (left<right)
        {
            int mid = left+(right-left)/2;
            if (isOK(bloomDay, m, k, mid))
                right = mid;
            else
                left = mid+1;
        }
        return left;
        
    }
    
    bool isOK(vector<int>& bloomDay, int m, int k, int t)
    {
        int cnt = 0;
        int cur = 0;
        for (int i=0; i<bloomDay.size(); i++)
        {
            if (bloomDay[i] > t)
            {
                cur = 0;
            }
            else 
            {
                cur += 1;
                if (cur==k)
                {
                    cur = 0;
                    cnt += 1;
                }
            }
            if (cnt >=m ) return true;
        }
        return false;
    }

public:
    


    /*
        Intuition
        If m * k > n, it impossible, so return -1.
        Otherwise, it's possible, we can binary search the result.
        left = 1 is the smallest days,
        right = 1e9 is surely big enough to get m bouquests.
        So we are going to binary search in range [left, right].


        Explanation
        Given mid days, we can know which flowers blooms.
        Now the problem is, given an array of true and false,
        find out how many adjacent true bouquest in total.

        If bouq < m, mid is still small for m bouquest.
        So we turn left = mid + 1

        If bouq >= m, mid is big enough for m bouquest.
        So we turn right = mid


        Complexity
        Time O(Nlog(maxA))
        Space O(1)

        Note that the result must be one A[i],
        so actually we can sort A in O(NlogK),
        Where K is the number of different values.
        and then binary search the index of different values.

        Though I don't thik worth doing that.


        More Good Binary Search Problems
        Here are some similar binary search problems.
        Also find more explanations.
        Good luck and have fun.

        5455. Minimum Number of Days to Make m Bouquets
        1283. Find the Smallest Divisor Given a Threshold
        1231. Divide Chocolate
        1011. Capacity To Ship Packages In N Days
        875. Koko Eating Bananas
        774. Minimize Max Distance to Gas Station
        410. Split Array Largest Sum

        Solution 2:
        Note that the result must be one A[i],
        so actually we can sort A in O(NlogK),
        Where K is the number of different values.
        and then binary search the index of different values.

        I notcied many mentioned that.
        I didn't do that for the 2 main reasons,

        1. this didn't change the main idea of binary search,
        and save just O(log1000) in time complexity,
        in sacrifice much of writing complexity.
        
        2. If we already sort A out,
        we don't even need O(NlogN) binary search at all.
        The problem can be already solved in O(N)
        
        The idea of O(N) is that,
        One pass the bloom days from in ascending order,
        mark the bloomed flower,
        calculate the the continous flowers connnected,
        update the bouquets and compared with m.
    
    */
    int doit_binary_search(vector<int>& bloomDay, int m, int k) {

        int low = 0, high = *std::max_element(begin(bloomDay), end(bloomDay));
        int n = bloomDay.size();

        // Only possible failure is no enough flowers for bouquet.
        if (m * k > n) return -1;
        
        auto cal = [&](int day) {
            int cnt = 0, last = 0;
            for (int i = 0; i < bloomDay.size(); i++) {
                
                if (bloomDay[i] > day) {
                    last = 0;
                    continue;
                }
                
                last++;
                if (last == k) {
                    cnt++;
                    last = 0;
                }
            }
            return cnt;
        };
        
        while (low < high) {
            
            int mid = (low + high) / 2;
            
            int cnt = cal(mid);
            
            if (cnt < m)
                low = mid + 1;
            else
                high = mid;
        }
        
        return low;
    }
}