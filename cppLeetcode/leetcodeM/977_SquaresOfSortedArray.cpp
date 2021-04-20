/*
977. Squares of a Sorted Array

Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.

 

Example 1:

Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Explanation: After squaring, the array becomes [16,1,0,9,100].
After sorting, it becomes [0,1,9,16,100].
Example 2:

Input: nums = [-7,-3,2,3,11]
Output: [4,9,9,49,121]
 

Constraints:

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums is sorted in non-decreasing order.
 

Follow up: Squaring each element and sorting the new array is very trivial, could you find an O(n) solution using a different approach?

*/

#include <vector>
#include <algorithm>

using std::vector;

class SortedSquares {

public:

    vector<int> doit_sort(vector<int>& nums) {
        vector<int> ans;
        for (auto c:nums) ans.push_back(c*c);
        std::sort(begin(ans), end(ans));
        return ans;
    }

    vector<int> doit_(vector<int>& nums) {
        
        int i = -1;
        int n = nums.size();
        vector<int> ans;

        while (i < n - 1 && nums[i + 1] < 0) i++;

        if (i == -1) {
            for (int j = 0; j < n; j++) 
                ans.push_back(nums[j] * nums[j]);
        }
        else if (i == n - 1) {
            for (int j = n - 1; j >= 0; j--) 
                ans.push_back(nums[j] * nums[j]);
        } else {

            int j = i + 1;

            while (i >= 0 || j < n) {

                if (i == -1) {
                    ans.push_back(nums[j] * nums[j]);
                    j++;
                }
                else if (j == n) {
                    ans.push_back(nums[i] * nums[i]);
                    i--;
                }
                else {
                    int left = nums[i] * nums[i], right = nums[j] * nums[j];

                    if (left < right) {
                        ans.push_back(left);
                        i--;
                    }
                    else {
                        ans.push_back(right);
                        j++;
                    }
                }
            }
        }

        return ans;
    }
};