/*
 
 1671. Minimum Number of Removals to Make Mountain Array
 
 
 You may recall that an array arr is a mountain array if and only if:

 arr.length >= 3
 There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
 arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
 arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
 Given an integer array nums​​​, return the minimum number of elements to remove to make nums​​​ a mountain array.

  

 Example 1:

 Input: nums = [1,3,1]
 Output: 0
 Explanation: The array itself is a mountain array so we do not need to remove any elements.
 Example 2:

 Input: nums = [2,1,1,5,6,2,3,1]
 Output: 3
 Explanation: One solution is to remove the elements at indices 0, 1, and 5, making the array nums = [1,5,6,3,1].
 Example 3:

 Input: nums = [4,3,2,1,1,2,3,1]
 Output: 4
 Example 4:

 Input: nums = [1,2,3,4,4,3,2,1]
 Output: 1
  

 Constraints:

 3 <= nums.length <= 1000
 1 <= nums[i] <= 109
 It is guaranteed that you can make a mountain array out of nums.
 */

#include <vector>


using std::vector;


class MinimumNumberOfRemovalsToMakeMountainArray {
    
public:
    
    // O(n^2)
    int doit_dp(vector<int>&& nums) {
        
        int n = nums.size();
        vector<int> left(n, 1), right(n, 1);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j])
                   left[i] = std::max(left[i], left[j]+1);
            }
        }
        
        for (int i = n; i >= 0; i--) {
            for (int j = i+1; j < n; j++) {
                if (nums[i] > nums[j])
                    right[i] = std::max(right[i], right[j]+1);
            }
        }
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (left[i] > 1 && right[i] > 1)
               ans = std::max(ans, left[i] + right[i] - 1);
        }
        
        return n - ans;
    }
    
    //  O(nlog(n))
    int doit_dp_1(vector<int>&& nums) {
     
        int n = nums.size();
        vector<int> left(n, 1), right(n, 1);
        vector<int> buff;
        for (int i = 0; i < n; i++) {
            auto it = std::lower_bound(begin(buff), end(buff), nums[i]);
            left[i] = it - begin(buff) + 1;
            if (it == buff.end())
                buff.push_back(nums[i]);
            else
                *it = nums[i];
        }
        
        buff.clear();
        for (int i = n-1; i >= 0; i--) {
            auto it = std::lower_bound(begin(buff), end(buff), nums[i]);
            right[i] = it - begin(buff) + 1;
            if (it == buff.end())
                buff.push_back(nums[i]);
            else
                *it = nums[i];
        }
         
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (left[i] >= 2 && right[i] >= 2)
                ans = std::max(ans, left[i] + right[i] - 1);
        }
        
        return n - ans;
    }
};


void test_1671_make_mountain_array() {
    
    
    MinimumNumberOfRemovalsToMakeMountainArray().doit_dp_1(vector<int>{1, 3, 1});
    
}
