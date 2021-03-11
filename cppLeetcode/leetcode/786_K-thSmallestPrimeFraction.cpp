/*

786. K-th Smallest Prime Fraction

You are given a sorted integer array arr containing 1 and prime numbers, where all the integers of arr are unique. You are also given an integer k.

For every i and j where 0 <= i < j < arr.length, we consider the fraction arr[i] / arr[j].

Return the kth smallest fraction considered. Return your answer as an array of integers of size 2, where answer[0] == arr[i] and answer[1] == arr[j].

 

Example 1:

Input: arr = [1,2,3,5], k = 3
Output: [2,5]
Explanation: The fractions to be considered in sorted order are:
1/5, 1/3, 2/5, 1/2, 3/5, and 2/3.
The third fraction is 2/5.
Example 2:

Input: arr = [1,7], k = 1
Output: [1,7]
 

Constraints:

2 <= arr.length <= 1000
1 <= arr[i] <= 3 * 104
arr[0] == 1
arr[i] is a prime number for i > 0.
All the numbers of arr are unique and sorted in strictly increasing order.
1 <= k <= arr.length * (arr.length - 1) / 2

*/
#include <vector>
#include <queue>

using std::priority_queue;
using std::vector;

class KthSmallestPrimeFraction {

    /*
        786.K-th Smallest-Prime-Fraction
        此题和 774 Minimize Max Distance to Gas Station 非常类似，用二分法的思想非常巧妙。

        在所有的候选分数中，第K个数会是什么呢？假设是M。我们如果想试探一个M是否成立的话，需要计算所有小于等于M的分数的个数。显然，这个是可以计算出来的：只要遍历所有的nums的元素作为分子，可以很快在nums里确定对应的临界分母，使得分数小于等于M。因此count+=数组里大于等于这个临界分母的个数。

        另外考虑，M一定会有下界A[0]/A[n-1]；其次它也有上界，存在于所有的相邻两个数所组成的分数A[i-1]/A[i]中的一个。PS：粗糙一点，直接设置上下姐是（0，1）的话也没有问题。

        于是二分夹逼的思路就呼之欲出了。根据left,right，得到mid，试探小于等于mid的分数的个数，并以此相应更新left和right。最后得到的mid，表示小于等于mid的分数个数恰好为K。

        有了这个mid，再遍历一遍nums的所有元素作为分子，找到对应的临界分母。取出所有“分子/分母”里最接近mid的那个就是最终答案。
    */
    vector<int> doit_binary_search(vector<int>& nums, int K) 
    {
        double left = 0;
        double right = 1;
        double mid;
        
        while (left < right)
        {
            mid = (left+right)/2;
            
            int count = 0;
            for (int i=0; i<nums.size(); i++)
            {
                auto pos = lower_bound(nums.begin(),nums.end(), nums[i]*1.0/mid);
                count += nums.end()-pos;
            }
            
            if (count < K)
                left = mid; // next time, mid >left
            else if (count > K)
                right = mid;
            else
                break; 
        }
        
        vector<int>ret;
        double ans = 0;
        
        for (int i=0; i<nums.size(); i++)
        {
            auto pos = lower_bound(nums.begin(), nums.end(), nums[i]*1.0/mid);
            int j = pos-nums.begin();
            if (pos!=nums.end() && nums[i]*1.0/nums[j] > ans)
            {
                ans = nums[i]*1.0/nums[j];
                ret = {nums[i], nums[j]};
            }
        }
        
        return ret;
        
    }

    /*
        Approach #1: Binary Search [Accepted]
        Intuition

        Let under(x) be the number of fractions below x. It's an increasing function on x, so we can binary search for the correct answer.

        Algorithm

        Let's binary search for x such that there are exactly K fractions below x. At the same time, we'll record the largest such fraction seen that was still below x.

        Our binary search follows a similar template as other binary searches: we have some interval [lo, hi] and a midpoint mi = (lo + hi) / 2.0. If the number of fractions below mi is less than K, then we will now consider the interval [mi, hi]; otherwise we will consider the interval [lo, mi]. For more on Binary Search, please visit the excellent LeetCode Explore card here on this topic.

        Our under(x) function has two objectives: to return the number of fractions below x, as well as the maximum such fraction below x. To count this, we will use a sliding window approach: for each primes[j], we'll find the largest i so that primes[i] / primes[j] < x. These is are necessarily increasing as j (and primes[j]) increases, so this check is linear.


        Complexity Analysis

        Time Complexity: O(NlogW), where NN is the length of primes, and W is the width (in quantized units) of our binary search, (hi - lo) / 1e-9 which is 10^9
        Space Complexity: O(1).
    */
    vector<int> doit_binary_search(vector<int>& arr, int k) {

        double lo = 0, hi = 1;
        
        auto under = [&](double num) -> vector<int> { 
            // Returns {count, numerator, denominator}
            int numer = 0, denom = 1, count = 0, i = -1;
            for (int j = 1; j < arr.size(); ++j) {
                // For each j, find the largest i so that primes[i] / primes[j] < x
                // It has to be at least as big as the previous i, so reuse it ("two pointer")
                while (arr[i+1] < arr[j] * num) ++i;

                // There are i+1 fractions: (primes[0], primes[j]),
                // (primes[1], primes[j]), ..., (primes[i], primes[j])
                count += i+1;
                if (i >= 0 && numer * arr[j] < denom * arr[i]) {
                    numer = arr[i];
                    denom = arr[j];
                }
            }
            return {count, numer, denom};
        };
        
        vector<int> ans{0, 1};
        while (hi - lo > 1e-9) {
            
            double mid = (lo + hi) / 2.0;
            auto res = under(mid); 
            if (res[0] >= k) {
                ans = {res[1], res[2]};
                hi = mid;
            }
            else
                lo = mid;
        }
        
        return ans;
    }
    
public:

    /*
        It's O(n) where n is the size of A. Reusing my old O(n) solution for "Kth Smallest Element in a Sorted Matrix" again, similar to how I did it for "Find K-th Smallest Pair Distance". 
        I build a virtual sorted matrix of entries p/q, [p, q], get the K-th smallest entry, and extract and return its [p, q]. For example, for A = [1, 2, 5, 7] my fractions matrix looks like this:

        |  7    5    2    1
        --+-------------------
        1 | 1/7  1/5  1/2  1/1
        2 | 2/7  2/5  2/2  2/1
        5 | 5/7  5/5  5/2  5/1
        7 | 7/7  7/5  7/2  7/1
    */
    vector<int> doit_heap(vector<int>& arr, int k) {
        
        int n = arr.size();
        priority_queue<std::pair<double, std::pair<int, int>>, vector<std::pair<double, std::pair<int, int>>>, std::greater<>> pq;
        pq.push({double(arr[0])/double(arr[n-1]), {0, n-1}});
        
        while (!pq.empty() && k--) {
            
            auto it = pq.top();
            pq.pop();
            
            int i = it.second.first, j = it.second.second; 
            
            if (k == 0) return {arr[i], arr[j]};
            
            if (j - 1 != i)
                pq.push({double(arr[i]) / double(arr[j-1]), {i, j-1}});
            
            if (j == n-1 && i+1 != j)
                pq.push({double(arr[i+1]) / double(arr[j]), {i+1, j}});
            
        }
        
        return {};
    }

    vector<int> doit_quickselect(vector<int>& arr, int k) {
        
        vector<std::pair<double, std::pair<int, int>>> ans;
        
        for (int i = 0; i < arr.size(); i++)
            for (int j = i + 1; j < arr.size(); j++) {
                ans.push_back({double(arr[i]) / double(arr[j]), {i, j}});
            }
        
        nth_element(begin(ans), begin(ans) + k - 1, end(ans), [](auto& a, auto& b){
            return a.first < a.first;
        });
        
        return {arr[ans[k-1].second.first], arr[ans[k-1].second.second]};
    }
};