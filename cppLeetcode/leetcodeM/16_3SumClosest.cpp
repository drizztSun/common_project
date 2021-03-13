/*
16. 3Sum Closest

Given an array nums of n integers and an integer target, find three integers in nums such that the sum is closest to target. 
Return the sum of the three integers. You may assume that each input would have exactly one solution.

 

Example 1:

Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 

Constraints:

3 <= nums.length <= 10^3
-10^3 <= nums[i] <= 10^3
-10^4 <= target <= 10^4
*/

#include <vector>
#include <algorithm>

using std::vector;


class ThreeSumClosest {

    /*
        016. 3Sum-Closet  
        一定记得要先排序！

        在确定了第一个元素之后，第2、3个元素的指针该如何设计变动呢？

        while (left<right)
        {
        if (abs(nums[left]+nums[right]-sum)<CurSum)
            更新最小结果;
        if (nums[left]+nums[right]<sum)
            left++;
        else
            right--;
        }
    */
    int threeSumClosest(vector<int>& nums, int target) 
    {
        sort(nums.begin(),nums.end());
        
        int temp = INT_MAX;
        int result;
        
        for (int a=0; a<nums.size(); a++)
        {
            int left = a+1;
            int right = nums.size()-1;
            int sum = target - nums[a];
            
            while (left<right)
            {
                if (temp > abs(nums[left]+nums[right]-sum))
                {
                    temp = abs(nums[left]+nums[right]-sum);
                    result = nums[a]+nums[left]+nums[right];
                }
                if (nums[left]+nums[right]==sum)
                    return target;
                else if (nums[left]+nums[right]>sum)
                    right--;
                else if (nums[left]+nums[right]<sum)    
                    left++;
            }
            
        }
        
        return result;
        
    }

public:

    /*
        Approach 1: Two Pointers
        The two pointers pattern requires the array to be sorted, so we do that first. As our BCR is \mathcal{O}(n^2)O(n 
        2
        ), the sort operation would not change the overall time complexity.

        In the sorted array, we process each value from left to right. For value v, we need to find a pair which sum, ideally, is equal to target - v. 
        We will follow the same two pointers approach as for 3Sum, however, since this 'ideal' pair may not exist, we will track the smallest absolute difference between the sum and the target. The two pointers approach naturally enumerates pairs so that the sum moves toward the target.

        Current
        1 / 14
        Algorithm

        1. Initialize the minimum difference diff with a large value.
        2. Sort the input array nums.
        3. Iterate through the array:
            . For the current position i, set lo to i + 1, and hi to the last index.
            . While the lo pointer is smaller than hi:
                . Set sum to nums[i] + nums[lo] + nums[hi].
                . If the absolute difference between sum and target is smaller than the absolute value of diff:
                    . Set diff to target - sum.
                . If sum is less than target, increment lo.
                . Else, decrement hi.
            .If diff is zero, break from the loop.
        4. Return the value of the closest triplet, which is target - diff.

        Complexity Analysis

        Time Complexity: \mathcal{O}(n^2)O(n 
        2
        ). We have outer and inner loops, each going through nn elements.

        Sorting the array takes \mathcal{O}(n\log{n})O(nlogn), so overall complexity is \mathcal{O}(n\log{n} + n^2)O(nlogn+n 
        2
        ). This is asymptotically equivalent to \mathcal{O}(n^2)O(n 
        2
        ).

        Space Complexity: from \mathcal{O}(\log{n})O(logn) to \mathcal{O}(n)O(n), depending on the implementation of the sorting algorithm.
    */

    int doit_twopointer(vector<int>& nums, int target) {
        
        std::sort(begin(nums), end(nums));
        int diff = INT_MAX, res = 0;
        
        for (int s = 0; s < nums.size(); s++) {
            
            int left = s+1, right = nums.size()-1;
            
            while (left < right) {
            
                int total = nums[left] + nums[right] + nums[s];
                
                if (total == target) return total;
                
                if (abs(total - target) < diff) {
                    res = total, diff = abs(total - target);
                }
                
                if(total < target)
                    left++;
                else 
                    right--;
            }
        }
        
        return res;
    }

    /*
        Approach 2: Binary Search
        We can adapt the 3Sum Smaller: Binary Search approach to this problem.

        In the two pointers approach, we fix one number and use two pointers to enumerate pairs. Here, we fix two numbers, and use a binary search to find the third complement number. This is less efficient than the two pointers approach, however, it could be more intuitive to come up with.

        Note that we may not find the exact complement number, so we check the difference between the complement and two numbers: the next higher and the previous lower. For example, if the complement is 42, and our array is [-10, -4, 15, 30, 60], the next higher is 60 (so the difference is -18), and the previous lower is 30 (and the difference is 12).

        Algorithm

        Initialize the minimum difference diff with a large value.
        Sort the input array nums.
        Iterate through the array (outer loop):
        For the current position i, iterate through the array starting from j = i + 1 (inner loop):
        Binary-search for complement (target - nums[i] - nums[j]) in the rest of the array.
        For the next higher value, check its absolute difference with complement against diff.
        For the previous lower value, check its absolute difference with complement against diff.
        Update diff based on the smallest absolute difference.
        If diff is zero, break from the loop.
        Return the value of the closest triplet, which is target - diff.

        Complexity Analysis

        Time Complexity: O(n^2 *logn). Binary search takes O(logn), and we do it nn times in the inner loop. Since we are going through nn elements in the outer loop, the overall complexity is O(n^2*log{n}).

        Space Complexity: from O(logn) to O(n), depending on the implementation of the sorting algorithm.      
    */
    int threeSumClosest(vector<int>& nums, int target) {
        int diff = INT_MAX, sz = nums.size();
        sort(begin(nums), end(nums));
        for (int i = 0; i < sz && diff != 0; ++i) {
            for (int j = i + 1; j < sz - 1; ++j) {
                int complement = target - nums[i] - nums[j];
                auto it = upper_bound(begin(nums) + j + 1, end(nums), complement);
                int hi = it - begin(nums), lo = hi - 1;
                if (hi < sz && abs(complement - nums[hi]) < abs(diff))
                    diff = complement - nums[hi];
                if (lo > j && abs(complement - nums[lo]) < abs(diff))
                    diff = complement - nums[lo];
            }
        }
        return target - diff;
    }
};
