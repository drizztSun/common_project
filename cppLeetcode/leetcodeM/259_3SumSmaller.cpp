/*
259. 3Sum Smaller

Given an array of n integers nums and an integer target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

Follow up: Could you solve it in O(n2) runtime?

 

Example 1:

Input: nums = [-2,0,1,3], target = 2
Output: 2
Explanation: Because there are two triplets which sums are less than 2:
[-2,0,1]
[-2,0,3]
Example 2:

Input: nums = [], target = 0
Output: 0
Example 3:

Input: nums = [0], target = 0
Output: 0
 

Constraints:

n == nums.length
0 <= n <= 300
-100 <= nums[i] <= 100
-100 <= target <= 100

*/

#include <vector>
#include <algorithm>


using std::vector;



class ThreeSumSmaller {

    /*
        ###259.3Sum-Smaller
        注意计数的方法

        if (nums[left]+nums[right]<sum)
            count+=right-left;
    */
    int threeSumSmaller(vector<int>& nums, int target) 
    {
        int count=0;
        sort(nums.begin(),nums.end());
        
        for (int a=0; a<nums.size(); a++)
        {
            int sum=target-nums[a];
            int left=a+1;
            int right=nums.size()-1;
            
            while (left<right)
            {
                if (nums[left]+nums[right]<sum)
                {
                    count+=right-left;
                    left++;
                }
                else
                {
                    right--;
                }
            }
        }
        
        return count;
    }

public:

    /*
        Approach #2 (Binary Search) [Accepted]
        Before we solve this problem, it is helpful to first solve this simpler twoSum version.

        Given a numsnums array, find the number of index pairs ii, jj with 0 \leq i < j < n0≤i<j<n that satisfy the condition nums[i] + nums[j] < targetnums[i]+nums[j]<target

        If we sort the array first, then we could apply binary search to find the largest index jj such that nums[i] + nums[j] < targetnums[i]+nums[j]<target for each ii. Once we found that largest index jj, we know there must be j-ij−i pairs that satisfy the above condition with ii's value fixed.

        Finally, we can now apply the twoSum solution to threeSum directly by wrapping an outer for-loop around it.

        public int threeSumSmaller(int[] nums, int target) {
            Arrays.sort(nums);
            int sum = 0;
            for (int i = 0; i < nums.length - 2; i++) {
                sum += twoSumSmaller(nums, i + 1, target - nums[i]);
            }
            return sum;
        }

        private int twoSumSmaller(int[] nums, int startIndex, int target) {
            int sum = 0;
            for (int i = startIndex; i < nums.length - 1; i++) {
                int j = binarySearch(nums, i, target - nums[i]);
                sum += j - i;
            }
            return sum;
        }

        private int binarySearch(int[] nums, int startIndex, int target) {
            int left = startIndex;
            int right = nums.length - 1;
            while (left < right) {
                int mid = (left + right + 1) / 2;
                if (nums[mid] < target) {
                    left = mid;
                } else {
                    right = mid - 1;
                }
            }
            return left;
        }
        Note that in the above binary search we choose the upper middle element (\frac{left+right+1}{2})( 
        2
        left+right+1
        ​	
        ) instead of the lower middle element (\frac{left+right}{2})( 
        2
        left+right
        ​	
        ). The reason is due to the terminating condition when there are two elements left. If we chose the lower middle element and the condition nums[mid] < targetnums[mid]<target evaluates to true, then the loop will never terminate. Choosing the upper middle element will guarantee termination.

        Complexity analysis

        Time complexity : O(n^2 \log n)O(n 
        2
        logn). The binarySearch function takes O(\log n)O(logn) time, therefore the twoSumSmaller takes O(n \log n)O(nlogn) time. The threeSumSmaller wraps with another for-loop, and therefore is O(n^2 \log n)O(n 
        2
        logn) time.

        Space complexity : O(1)O(1).
    */


    /*
        Approach #3 (Two Pointers) [Accepted]
        Let us try sorting the array first. For example, nums = [3,5,2,8,1]nums=[3,5,2,8,1] becomes [1,2,3,5,8][1,2,3,5,8].

        Let us look at an example nums = [1,2,3,5,8]nums=[1,2,3,5,8], and target = 7target=7.

        [1, 2, 3, 5, 8]
        ↑           ↑
        left       right
        Let us initialize two indices, leftleft and rightright pointing to the first and last element respectively.

        When we look at the sum of first and last element, it is 1 + 8 = 91+8=9, which is \geq target≥target. That tells us no index pair will ever contain the index rightright. So the next logical step is to move the right pointer one step to its left.

        [1, 2, 3, 5, 8]
        ↑        ↑
        left    right
        Now the pair sum is 1 + 5 = 61+5=6, which is < target<target. How many pairs with one of the index = leftindex=left that satisfy the condition? You can tell by the difference between rightright and leftleft which is 33, namely (1,2), (1,3),(1,2),(1,3), and (1,5)(1,5). Therefore, we move leftleft one step to its right.

        public int threeSumSmaller(int[] nums, int target) {
            Arrays.sort(nums);
            int sum = 0;
            for (int i = 0; i < nums.length - 2; i++) {
                sum += twoSumSmaller(nums, i + 1, target - nums[i]);
            }
            return sum;
        }

        private int twoSumSmaller(int[] nums, int startIndex, int target) {
            int sum = 0;
            int left = startIndex;
            int right = nums.length - 1;
            while (left < right) {
                if (nums[left] + nums[right] < target) {
                    sum += right - left;
                    left++;
                } else {
                    right--;
                }
            }
            return sum;
        }
        Complexity analysis

        Time complexity : O(n^2). The twoSumSmaller function takes O(n)O(n) time because both left and right traverse at most n steps. Therefore, the overall time complexity is O(n^2).
        Space complexity : O(1).
    */
    int doit_twopointer(vector<int>& nums, int target) {
        
        int ans = 0;
        std::sort(begin(nums), end(nums));
            
        for (int i = 0; i < nums.size(); i++) {
            
            //if (nums[i] > target) break;
            
            int left = i+1, right = nums.size()-1;
            
            while (left < right) {
            
                int t = nums[i] + nums[left] + nums[right];
                
                if (t >= target) {
                    right--;
                } else {
                    ans += right - left;
                    left++;
                }
            }
        }
        
        return ans;
    }
};