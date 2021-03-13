/*
75. Sort Colors

Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.

 

Example 1:

Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
Example 2:

Input: nums = [2,0,1]
Output: [0,1,2]
Example 3:

Input: nums = [0]
Output: [0]
Example 4:

Input: nums = [1]
Output: [1]
 

Constraints:

n == nums.length
1 <= n <= 300
nums[i] is 0, 1, or 2.
 

Follow up:

Could you solve this problem without using the library's sort function?
Could you come up with a one-pass algorithm using only O(1) constant space?
*/


#include <vector>

using std::vector;

class SortColors {

    /*
        075.Sort-Colors
        难点在于如何in-palce实现。基本思想是设置三个指针：

        int left=0;
        int mid=0;
        int right=nums.size()-1;
        遍历mid指针，当遇到2号球时，便和right指针进行交换；遇到1号球时，继续前进；与到0号球时，便和left指针进行交换。 理解的难点在于：

        if (nums[mid]==0)
        {
        swap(nums[left],nums[mid]);
        left++;
        mid++;
        }
        因为left和mid初始位置相同，他们之间出现异步只是因为1号球的出现。所以这两个指针之间间隔的永远只会是1号球，所以当left和mid交换时，left指针传给mid的一定会是1号球而不是0号球。
    */
    void sortColors(vector<int>& nums) 
    {
        int left=0;
        int right=nums.size()-1;
        int mid=0;
        
        while (mid<=right)
        {
            if (nums[mid]==2)
            {
                std::swap(nums[mid],nums[right]);
                right--;
            }
            else if (nums[mid]==0)
            {
                std::swap(nums[mid],nums[left]);
                left++;
                mid++;
            }
            else
            {
                mid++;
            }
        }
    }

public:

    /*
        Approach 1: One Pass
        Intuition

        The problem is known as Dutch National Flag Problem and first was proposed by Edsger W. Dijkstra. The idea is to attribute a color to each number and then to arrange them following the order of colors on the Dutch flag.

        bla

        Let's use here three pointers to track the rightmost boundary of zeros, the leftmost boundary of twos and the current element under the consideration.

        bla

        The idea of solution is to move curr pointer along the array, if nums[curr] = 0 - swap it with nums[p0], if nums[curr] = 2 - swap it with nums[p2].

        Algorithm

        Initialise the rightmost boundary of zeros : p0 = 0. During the algorithm execution nums[idx < p0] = 0.

        Initialise the leftmost boundary of twos : p2 = n - 1. During the algorithm execution nums[idx > p2] = 2.

        Initialise the index of current element to consider : curr = 0.

        While curr <= p2 :

        If nums[curr] = 0 : swap currth and p0th elements and move both pointers to the right.

        If nums[curr] = 2 : swap currth and p2th elements. Move pointer p2 to the left.

        If nums[curr] = 1 : move pointer curr to the right.

        Implementation

        Current
        1 / 13

        Complexity Analysis

        Time complexity : O(N) since it's one pass along the array of length NN.

        Space complexity : O(1) since it's a constant space solution.
    */
    void sortColors(vector<int>& nums) {
        // for all idx < p0 : nums[idx < p0] = 0
        // curr is an index of element under consideration
        int p0 = 0, curr = 0;
        // for all idx > p2 : nums[idx > p2] = 2
        int p2 = nums.size() - 1;

        while (curr <= p2) {
            if (nums[curr] == 0) {
                std::swap(nums[curr++], nums[p0++]);
            }
            else if (nums[curr] == 2) {
                std::swap(nums[curr], nums[p2--]);
            }
            else curr++;
        }
    }

    void doit_twopointer(vector<int>& nums) {

        int left = 0, right = nums.size()-1;
        int i = 0;

        while (i <= right) {
            if (nums[i] == 0) {
                std::swap(nums[i], nums[left]);
                left++;
            }

            if (nums[i] == 2) {
                std::swap(nums[i], nums[right]);
                right--;
                continue;
            }
            i++;
        }
    }
    
    void doit_twopointer(vector<int>& nums) {
        
        int left = -1, right = nums.size();

        for (int i = 0; i < right; i++) {

            while (i > left && i < right && nums[i] != 1) {

                if (nums[i] == 0) {
                    left++;
                    std::swap(nums[i], nums[left]);
                }
                else if (nums[i] == 2) {
                    right--;
                    std::swap(nums[i], nums[right]);
                }
            }
        }
    }
};