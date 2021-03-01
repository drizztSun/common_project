/*
238. Product of Array Except Self

Given an array nums of n integers where n > 1,  return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Example:

Input:  [1,2,3,4]
Output: [24,12,8,6]
Constraint: It's guaranteed that the product of the elements of any prefix or suffix of the array (including the whole array) fits in a 32 bit integer.

Note: Please solve it without division and in O(n).

Follow up:
Could you solve it with constant space complexity? (The output array does not count as extra space for the purpose of space complexity analysis.)

*/
#include <vector>

using std::vector;


class ProductExceptSelf {

public:

    vector<int> doit_twopointer(vector<int>& nums) {

        vector<int> left{1};
        
        for (int i = 0; i < nums.size() - 1; i++) {
            left.push_back(left.back() * nums[i]);
        }
        
        vector<int> right{1};
        for (int i = nums.size()-1; i > 0; i--) {
            right.push_back(right.back()*nums[i]);
        }
        
        int n = nums.size();
        vector<int> ans(n);
        
        for (int i = 0; i < nums.size(); i++) {
            ans[i] = left[i] * right[n - i - 1];
        }
        
        return ans;
    }

    vector<int> doit_(vector<int>& nums) {

        int n = nums.size();
        vector<int> ans(n, 1);

        for (int i = 0; i < nums.size()-1; i++) {
            ans[i+1] *= nums[i] * ans[i];
        }

        int rightproduct = 1;
        for (int i = nums.size()-1; i >= 0; i--) {
            ans[i] *= rightproduct;
            rightproduct *= nums[i];
        }

        return ans;
    }
};