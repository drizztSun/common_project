/*
164. Maximum Gap

Given an integer array nums, return the maximum difference between two successive elements in its sorted form. If the array contains less than two elements, return 0.

 

Example 1:

Input: nums = [3,6,9,1]
Output: 3
Explanation: The sorted form of the array is [1,3,6,9], either (3,6) or (6,9) has the maximum difference 3.
Example 2:

Input: nums = [10]
Output: 0
Explanation: The array contains less than 2 elements, therefore return 0.
 

Constraints:

1 <= nums.length <= 10^4
0 <= nums[i] <= 10^9
 

Follow up: Could you solve it in linear time/space?

*/
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <limits>

using std::unordered_set;
using std::vector;


class MaximumGap {

    /*
        164.Maximum-Gap
        假设有N个元素A到B。

        那么可以推算，相邻元素的最大差值不会小于(B - A) / (N - 1)，否则无法达到B-A的跨越。

        所以令bucket（桶）的大小 bucket_size = (B - A) / (N - 1)，则最多会有 bucket_nums = (B - A) / bucket_size + 1个桶。

        对于数组中的任意整数nums[i]，很容易通过算式 idx = (nums[i] - A) / bucket_nums 找出其桶的位置，然后维护每一个桶的最大值和最小值。

        由于同一个桶内的元素之间的差值至多为len - 1，因此最终答案不会从同一个桶中选择。

        对于每一个非空的桶p，找出下一个非空的桶q，则q.min - p.max可能就是备选答案。返回所有这些可能值中的最大值。
    */
    int maximumGap(vector<int>& nums) 
    {
        int N=nums.size();
        if (N<2) return 0;
        
        int MIN=INT_MAX;
        int MAX=INT_MIN;
        for (int i=0; i<nums.size(); i++)
        {
            MIN=std::min(MIN,nums[i]);
            MAX=std::max(MAX,nums[i]);
        }
        
        int bucket_size = std::max(1,(MAX-MIN)/(N-1));
        int bucket_nums = (MAX-MIN)/bucket_size+1;
        vector<int>bucket_min(bucket_nums,INT_MAX);
        vector<int>bucket_max(bucket_nums,INT_MIN);
        
        unordered_set<int>Set;
        for (int i=0; i<N; i++)
        {
            int idx=(nums[i]-MIN)/bucket_size;
            bucket_min[idx]=std::min(nums[i],bucket_min[idx]);
            bucket_max[idx]=std::max(nums[i],bucket_max[idx]);
            Set.insert(idx);
        }
        
        int result=INT_MIN;
        int pre=0;
        for (int i=0; i<bucket_nums; i++)
        {
            if (Set.count(i)==0) continue;
            result=std::max(result,bucket_min[i]-bucket_max[pre]);
            pre = i;
        }
        
        return result;        
    }

public:

    int doit_bucketsort(vector<int>& nums) {
        
        int N = nums.size();
        
        if (N < 2) return 0;
        
        int maxi = *max_element(begin(nums), end(nums)), mini = *min_element(begin(nums), end(nums));
        
        int bucketsize = std::max(1, (maxi - mini) / (N - 1));
    
        int bucketNum = (maxi - mini) / bucketsize + 1;
        
        vector<std::pair<int, int>> buckets(bucketNum, {INT_MAX, INT_MIN});
        
        for (auto c: nums) {
            
            int idx = (c - mini) / bucketsize;
            buckets[idx].first = std::min(buckets[idx].first, c);
            buckets[idx].second = std::max(buckets[idx].second, c);
            
        }
    
        int res = INT_MIN;
        int pre = 0;
        
        for (int i = 0; i < bucketNum; i++) {
            if (buckets[i].first == INT_MAX) continue;
            res = std::max(res, buckets[i].first - buckets[pre].second);
            pre = i;
        }
        
        return res;
    }

    /*
        Approach 1: Comparison Sorting
        Intuition

        Do what the question says.

        Algorithm

        Sort the entire array. Then iterate over it to find the maximum gap between two successive elements.

        Complexity Analysis

        Time complexity: O(nlogn).

        Time taken to sort the array is O(nlogn) (average case). Time taken for linear iteration through the array is of O(n) complexity. Hence overall time complexity is O(nlogn).

        Space complexity: No extra space needed, other than the input array (since sorting can usually be done in-place).
    */
    int doit_sort(vector<int>& nums) {
        if (nums.empty() || nums.size() < 2)            // check if array is empty or small sized
            return 0;

        std::sort(nums.begin(), nums.end());                 // sort the array

        int maxGap = 0;
        for (int i = 0; i < nums.size() - 1; i++)
            maxGap = std::max(nums[i + 1] - nums[i], maxGap);
        return maxGap;
    }

    /*
        Approach 2: Radix Sort
        Algorithm

        This approach is similar to Approach 1, except we use Radix Sort instead of a traditional comparison sort.


        Complexity Analysis

        Time complexity: O(d⋅(n+k))≈O(n).

        Since a linear iteration over the array (once it is sorted) is of linear (i.e. O(n)O(n)) complexity, the performance of this approach is limited by the performance of Radix sort.

        Radix sort uses Counting sort as a subroutine.

        Counting sort runs in O(n + k)O(n+k) time (where kk is the radix or base of the digits comprising the nn elements in the array). If k \leq O(n)k≤O(n), Counting sort would run in linear time. 
        In our case, the radix is fixed (i.e. k = 10k=10). Hence our Counting sort subroutine runs in O(n)O(n) linear time.

        Radix sort works by running dd passes of the Counting sort subroutine (where the elements are composed of, maximally, dd digits). 
        Hence effective runtime of Radix sort would be O(d \cdot (n + k))O(d⋅(n+k)). However, in our case an element can, maximally, be the maximum 32-bit signed integer 2,147,483,647. Hence d \leq 10d≤10 is a constant.

        Thus Radix sort has a runtime performance complexity of about O(n)O(n) for reasonably large input.

        Space complexity: O(n + k) \approx O(n)O(n+k)≈O(n) extra space.

        Counting sort requires O(k)O(k) extra space. Radix sort requires an auxiliary array of the same size as input array. 
        However given that kk is a small fixed constant, the space required by Counting sort can be ignored for reasonably large input.
    */
    int doit_(vector<int>& nums) {
        if (nums.empty() || nums.size() < 2)
        return 0;

        int maxVal = *max_element(nums.begin(), nums.end());

        int exp = 1;                                 // 1, 10, 100, 1000 ...
        int radix = 10;                              // base 10 system

        vector<int> aux(nums.size());

        /* LSD Radix Sort */
        while (maxVal / exp > 0) {                   // Go through all digits from LSD to MSD
            vector<int> count(radix, 0);

            for (int i = 0; i < nums.size(); i++)    // Counting sort
                count[(nums[i] / exp) % 10]++;

            for (int i = 1; i < count.size(); i++)   // you could also use partial_sum()
                count[i] += count[i - 1];

            for (int i = nums.size() - 1; i >= 0; i--)
                aux[--count[(nums[i] / exp) % 10]] = nums[i];

            for (int i = 0; i < nums.size(); i++)
                nums[i] = aux[i];

            exp *= 10;
        }

        int maxGap = 0;

        for (int i = 0; i < nums.size() - 1; i++)
            maxGap = std::max(nums[i + 1] - nums[i], maxGap);

        return maxGap;
    }


    class Bucket {
    public:
        bool used = false;
        int minval = numeric_limits<int>::max();        // same as INT_MAX
        int maxval = numeric_limits<int>::min();        // same as INT_MIN
    };

    int maximumGap(vector<int>& nums)
    {
        if (nums.empty() || nums.size() < 2)
            return 0;

        int mini = *min_element(nums.begin(), nums.end()), maxi = *max_element(nums.begin(), nums.end());

        int bucketSize = std::max(1, (maxi - mini) / ((int)nums.size() - 1));        // bucket size or capacity
        int bucketNum = (maxi - mini) / bucketSize + 1;                         // number of buckets
        vector<Bucket> buckets(bucketNum);

        for (auto&& num : nums) {
            int bucketIdx = (num - mini) / bucketSize;                          // locating correct bucket
            buckets[bucketIdx].used = true;
            buckets[bucketIdx].minval = std::min(num, buckets[bucketIdx].minval);
            buckets[bucketIdx].maxval = std::max(num, buckets[bucketIdx].maxval);
        }

        int prevBucketMax = mini, maxGap = 0;
        for (auto&& bucket : buckets) {
            if (!bucket.used)
                continue;

            maxGap = std::max(maxGap, bucket.minval - prevBucketMax);
            prevBucketMax = bucket.maxval;
        }

        return maxGap;
    }
};