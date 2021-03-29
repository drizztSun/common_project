/*
55. Jump Game


Given an array of non-negative integers nums, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

 

Example 1:

Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
 

Constraints:

1 <= nums.length <= 3 * 104
0 <= nums[i] <= 105
Accepted

*/
#include <vector>

using std::vector;


class JumpGame {

    /*
        055.Jump-Game
        比较简单的贪心法。我们从做往右每遍历一个元素，都可以动态地更新未来的右边界。直到我们遍历到右边界位置无法前进的时候，仍然没有走到数组的最后一个位置，就返回false。
    */
    bool canJump(vector<int>& nums) {
        
        int far = 0; 
        for(int i = 0; i<nums.size()-1; i++)
        {
            if (far < i) return false;
            far = std::max(far,i+nums[i]);            
        }
        
        return far>=nums.size()-1;
    }

public:

    int doit_greedy(vector<int>& nums) {

        int i = 0, far = 0;

        while (i < nums.size() && i <= far) {
            far = std::max(far, i + nums[i]);
            i++;
        }

        return i >= nums.size();
    }
}