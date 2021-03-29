/*
45. Jump Game II

Given an array of non-negative integers nums, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

You can assume that you can always reach the last index.

 

Example 1:

Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [2,3,0,1,4]
Output: 2
 

Constraints:

1 <= nums.length <= 1000
0 <= nums[i] <= 10^5

*/
#include <vector>
using std::vector;

class JumpGameII {

    /*
        45.Jump-Game-II
        求最少步数到达目的地的算法，最常见的就是BFS。本题可以仿照其思想。

        第0步所能到达的点就是0. 第一步所能到的点的右边界就是0+nums[0]，也就是说第一步跨越的范围就是[1, 0+nums[0]。那么第二步所能到达的范围是什么呢？最小的位置，应该是第一步所能达到的最远点的下一个位置；最大的位置，应该是第一步所能达到的所有的点所共同更新的最远边界。

        所以我们可以类似BFS的层级遍历，每走一步，弹出旧的元素区间[start,end]，然后装入新的元素区间[start_new, end_new]。

        start_new = end+1; 
        end_new = max{i+nums[i]} for i=[start,end]
        每一步只要start<=end，就可以认为队列里还有元素，BFS就能继续。直至end_new到达最末的位置，或者start>end。
    */
    int doit_(vector<int>& nums) 
    {
        int start = 0, end = 0;
        int step = 0;
        if (nums.size()==1) return 0;

        while (end >= start)
        {
            int start_old = start;
            int end_old = end;            
            for (int i=start_old; i<=end_old; i++)            
            {
                end = std::max(end, i+nums[i]);
                if (end >= nums.size()-1)
                    return step+1;
            }
            step++;
            start = end_old+1;
        }
        return 0;
    }

public:
    
    int doit_(vector<int>& nums) {
    
        int i = 0, step = 0;
        int far = 0;
        
        while (i < nums.size()-1 && far < nums.size()-1){
            
            int end = far;
            step++;
            
            for (int j = i; j <= end; j++) {
                far = std::max(far, j + nums[j]);
            }
            
            i = end+1;
        }
        
        return step;
    }
};