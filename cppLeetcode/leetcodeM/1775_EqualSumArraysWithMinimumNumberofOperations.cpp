/*
1775. Equal Sum Arrays With Minimum Number of Operations

You are given two arrays of integers nums1 and nums2, possibly of different lengths. The values in the arrays are between 1 and 6, inclusive.

In one operation, you can change any integer's value in any of the arrays to any value between 1 and 6, inclusive.

Return the minimum number of operations required to make the sum of values in nums1 equal to the sum of values in nums2. Return -1​​​​​ if it is not possible to make the sum of the two arrays equal.

 

Example 1:

Input: nums1 = [1,2,3,4,5,6], nums2 = [1,1,2,2,2,2]
Output: 3
Explanation: You can make the sums of nums1 and nums2 equal with 3 operations. All indices are 0-indexed.
- Change nums2[0] to 6. nums1 = [1,2,3,4,5,6], nums2 = [6,1,2,2,2,2].
- Change nums1[5] to 1. nums1 = [1,2,3,4,5,1], nums2 = [6,1,2,2,2,2].
- Change nums1[2] to 2. nums1 = [1,2,2,4,5,1], nums2 = [6,1,2,2,2,2].
Example 2:

Input: nums1 = [1,1,1,1,1,1,1], nums2 = [6]
Output: -1
Explanation: There is no way to decrease the sum of nums1 or to increase the sum of nums2 to make them equal.
Example 3:

Input: nums1 = [6,6], nums2 = [1]
Output: 3
Explanation: You can make the sums of nums1 and nums2 equal with 3 operations. All indices are 0-indexed. 
- Change nums1[0] to 2. nums1 = [2,6], nums2 = [1].
- Change nums1[1] to 2. nums1 = [2,2], nums2 = [1].
- Change nums2[0] to 4. nums1 = [2,2], nums2 = [4].
 

Constraints:

1 <= nums1.length, nums2.length <= 10^5
1 <= nums1[i], nums2[i] <= 6
*/
#include <vector>
#include <algorithm>
#include <numeric>

using std::vector;

class MinOperations {

    /*
        1775.Equal-Sum-Arrays-With-Minimum-Number-of-Operations
        假设nums1比num2的sum要大，那么我们要将这两个sum更靠近，无非就是两种思路：要么将nums1里面的元素改小，要么将num2里面的元素改大。为了减少操作次数，我们必须最大化改动的效率。
        也就是说，如果选择将nums1里面的元素改小，那么我们一定会将最大的元素改成1；反之，我们也可以将nums2里面最小的元素改成6。至于这两种方案里面怎么选，自然是查看它们的变动幅度，看哪个更大一些。一旦改动幅度能够cover当前的diff，就说明可以将这两个sum变成一致的。

        所以我们将两个数组都排个序。对于nums1，我们从后往前改动；对于nums2，我们从前往后改动。于是本题本质就是一个双指针，每改动一次，就移动相应的一个指针。直至diff小于等于零（实现目标），或者两个指针都到了尽头（无法实现目标）。
            
    */

    int doit_twopointer_best(vector<int>& nums1, vector<int>& nums2) {
        
        int m = nums1.size(), n = nums2.size(), sum1 = 0, sum2 = 0;
        vector<int> cnt1(7, 0), cnt2(7, 0);
        for(int num : nums1){
            sum1 += num;
            cnt1[num]++;
        }
        for(int num : nums2){
            sum2 += num;
            cnt2[num]++;
        }

        if(sum1 == sum2) return 0;
        if(6 * m < n || m > 6 * n) return -1;
        
        int ans = 0;
        if(sum2 < sum1){
            std::swap(sum1, sum2);
            std::swap(cnt1, cnt2);
        }
        
        // sum2 > sum1
        for(int i = 1; i <= 6; i++){
            
            if(sum1 + (6 - i) * cnt1[i] >= sum2){
                return ans + (sum2 - sum1 - 1) / (6 - i) + 1;
            }else{
                sum1 += (6 - i) * cnt1[i];
                ans += cnt1[i];
            }

            if(sum2 - (6 - i) * cnt2[7-i] <= sum1){
                return ans + (sum2 - sum1 - 1) / (6 - i) + 1;
            }else{
                sum2 -= (6 - i) * cnt2[7-i];
                ans += cnt2[7-i];
            }
        }
        return -1;
    }

public:
    
    int doit_slidingwindow(vector<int>& nums1, vector<int>& nums2) {

        int sum1 = std::accumulate(nums1.begin(), nums1.end(), 0);
        int sum2 = std::accumulate(nums2.begin(), nums2.end(), 0);

        if (sum1 < sum2)
            return doit_slidingwindow(nums2, nums1);
        
        int diff = sum1 - sum2;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        
        int i = nums1.size()-1, j = 0;
        int count = 0;
        while (diff > 0)
        {
            if (i<0 && j==nums2.size())
                return -1;
            if (i<0)
            {
                diff -= (6 - nums2[j]);
                j++;
            }
            else if (j==nums2.size())
            {
                diff -= (nums1[i] - 1);
                i--;
            }
            else if (nums1[i] - 1> 6-nums2[j])
            {
                diff -= (nums1[i] - 1);
                i--;
            }
            else
            {
                diff -= (6 - nums2[j]);
                j++;
            }
            count++;            
        }
        
        return count;
    }

    int doit_sort_greedy(vector<int>& nums1, vector<int>& nums2) {
        
        const int l1 = nums1.size();
        const int l2 = nums2.size();
        if (std::min(l1, l2) * 6 < std::max(l1, l2)) return -1;

        int s1 = accumulate(begin(nums1), end(nums1), 0);
        int s2 = accumulate(begin(nums2), end(nums2), 0);
        
        if (s1 > s2) return doit_sort_greedy(nums2, nums1);

        sort(begin(nums1), end(nums1));
        sort(begin(nums2), end(nums2));
        
        int ans = 0;    
        int i = 0;
        int j = l2 - 1;
        
        while (s1 != s2) {      
            
            const int diff = s2 - s1;      
        
            if (j == l2 || (i != l1 && 6 - nums1[i] >= nums2[j] - 1)) {
                const int x = std::min(6, nums1[i] + diff);
                s1 += x - nums1[i++];        
            } else {
                const int x = std::max(1, nums2[j] - diff);
                s2 += x - nums2[j--];      
            }
            
            ++ans;
        }

        return ans;
    }
};