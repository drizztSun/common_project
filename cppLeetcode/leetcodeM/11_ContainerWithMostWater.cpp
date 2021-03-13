/*
11. Container With Most Water

Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). 
n vertical lines are drawn such that the two endpoints of the line i is at (i, ai) and (i, 0). Find two lines, which, together with the x-axis forms a container, such that the container contains the most water.

Notice that you may not slant the container.

 

Example 1:


Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
Example 2:

Input: height = [1,1]
Output: 1
Example 3:

Input: height = [4,3,2,1,4]
Output: 16
Example 4:

Input: height = [1,2,1]
Output: 2
 

Constraints:

n == height.length
2 <= n <= 10^5
0 <= height[i] <= 10^4
*/



#include <vector>

using std::vector;


class ContainerMostWater {

    /*
        11. Container With Most Water
        算法：双指针。  
        让左指针指向0，右指针指向height.size()-1。每次考虑如果减少横向距离1，判断应该选择移左指针还是右指针，还是考察both？  

        事实上，只需要移动height[left]和height[right]中较矮的一个板子即可，这样才有使总面积增大的可能。否则移动较高的板子，只会使结果变小，因为面积受限于较矮的那块板子。

        if (height[left]>=height[right])
        right--;
        else
        left++;
    
    */
    int maxArea(vector<int>& height) 
    {
        int left=0;
        int right=height.size()-1;
        
        int temp=0;
        int result=0;
        
        while (left<right)
        {
            int temp = (right-left)* std::min(height[left],height[right]);
            if (temp>result) result=temp;
            
            if (height[left]>=height[right])
                right--;
            else
                left++;
        }
        
        return result;
        
    }


public:

    /*
        Approach 2: Two Pointer Approach
        Algorithm

        The intuition behind this approach is that the area formed between the lines will always be limited by the height of the shorter line. Further, the farther the lines, the more will be the area obtained.

        We take two pointers, one at the beginning and one at the end of the array constituting the length of the lines. 
        Futher, we maintain a variable \text{maxarea}maxarea to store the maximum area obtained till now. At every step, we find out the area formed between them, update maxarea and move the pointer pointing to the shorter line towards the other end by one step.

        The algorithm can be better understood by looking at the example below:

        1 8 6 2 5 4 8 3 7
        Current
        1 / 8
        How this approach works?

        Initially we consider the area constituting the exterior most lines. Now, to maximize the area, we need to consider the area between the lines of larger lengths. 
        If we try to move the pointer at the longer line inwards, we won't gain any increase in area, since it is limited by the shorter line. 
        But moving the shorter line's pointer could turn out to be beneficial, as per the same argument, despite the reduction in the width. 
        This is done since a relatively longer line obtained by moving the shorter line's pointer might overcome the reduction in area caused by the width reduction.

        For further clarification click here and for the proof click here.


        Complexity Analysis

        Time complexity : O(n). Single pass.

        Space complexity : O(1). Constant space is used.
    */
    int doit_twopointer(vector<int>& height) {
        
        int left = 0, right = height.size()-1;
        int area = 0;
        
        while (left < right) {
            
            area = std::max(area, (right - left) * std::min(height[left], height[right]));
            
            if (height[left] >=height[right]) 
                right--;
            else
                left++;
        }
        
        return area;
    }
};