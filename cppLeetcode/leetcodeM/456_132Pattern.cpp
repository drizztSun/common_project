/*
456. 132 Pattern

Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].

Return true if there is a 132 pattern in nums, otherwise, return false.

Follow up: The O(n^2) is trivial, could you come up with the O(n logn) or the O(n) solution?

 

Example 1:

Input: nums = [1,2,3,4]
Output: false
Explanation: There is no 132 pattern in the sequence.
Example 2:

Input: nums = [3,1,4,2]
Output: true
Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
Example 3:

Input: nums = [-1,3,2,0]
Output: true
Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].
 

Constraints:

n == nums.length
1 <= n <= 10^4
-109 <= nums[i] <= 10^9

*/
#include <vector>
#include <stack>

using std::stack;
using std::vector;

class Pattern132 {

public:

    bool doit_stack(vector<int>& nums) {
     
        stack<int> buff;
        int last = INT_MIN;
        
        for (int i = nums.size() - 1; i >= 0; i--) {
            
            if (nums[i] < last) return true;
            
            while (!buff.empty() && buff.top() < nums[i]) {
                last = buff.top();
                buff.pop();
            }
            
            buff.push(nums[i]);
        }
        
        return false;
    }

    /*
        Approach 1: Brute Force
        The simplest solution is to consider every triplet (i, j, k)(i,j,k) and check if the corresponding numbers satisfy the 132 criteria. If any such triplet is found, we can return a True value. If no such triplet is found, we need to return a False value.
    
        Complexity Analysis
        Time complexity : O(n^3). Three loops are used to consider every possible triplet. Here, nn refers to the size of numsnums array.
        Space complexity : O(1). Constant extra space is used.
    */

    bool doit_brute_force(vector<int>& nums) {
        if (nums.size() < 3) {
            return false;
        }
        for (size_t i = 0; i < nums.size() - 2; i++) {
            for (size_t j = i + 1; j < nums.size() - 1; j++) {
                for (size_t k = j + 1; k < nums.size(); k++) {
                    if (nums[k] > nums[i] and nums[j] > nums[k]) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    /*
        Approach 2: Better Brute Force
        Algorithm

        We can improve the last approach to some extent, if we make use of some observations. We can note that for a particular number nums[j]nums[j] chosen as 2nd element in the 132 pattern, if we don't consider nums[k]nums[k](the 3rd element) for the time being, our job is to find out the first element, nums[i]nums[i](i<ji<j) which is lesser than nums[j]nums[j].

        Now, assume that we have somehow found a nums[i],nums[j]nums[i],nums[j] pair. Our task now reduces to finding out a nums[k]nums[k](Kk>j>i)Kk>j>i), which falls in the range (nums[i], nums[j])(nums[i],nums[j]). Now, to maximize the likelihood of a nums[k]nums[k] falling in this range, we need to increase this range as much as possible.

        Since, we started off by fixing a nums[j]nums[j], the only option in our hand is to choose a minimum value of nums[i]nums[i] given a particular nums[j]nums[j]. Once, this pair nums[i],nums[j]nums[i],nums[j], has been found out, we simply need to traverse beyond the index jj to find if a nums[k]nums[k] exists for this pair satisfying the 132 criteria.

        Based on the above observations, while traversing over the numsnums array choosing various values of nums[j]nums[j], we simultaneously keep a track of the minimum element found so far(excluding nums[j]nums[j]). This minimum element always serves as the nums[i]nums[i] for the current nums[j]nums[j]. Thus, we only need to traverse beyond the j^{th}j 
        th
        index to check the nums[k]nums[k]'s to determine if any of them satisfies the 132 criteria.

        Complexity Analysis

        Time complexity : O(n^2). Two loops are used to find the nums[j], nums[k] pairs. Here, nn refers to the size of numsnums array.

        Space complexity : O(1). Constant extra space is used.
    */
    bool doit_brute_force_1(vector<int>& nums) {
        int min_i = INT_MAX;
        for (size_t j = 0; j < nums.size() - 1; j++) {
            min_i = std::min(min_i, nums[j]);
            for (size_t k = j + 1; k < nums.size(); k++) {
                if (nums[k] < nums[j] && min_i < nums[k]) {
                    return true;
                }
            }
        }
        return false;
    }

    /*
        Approach 5: Binary Search
        Algorithm

        In the last approach, we've made use of a separate stackstack to push and pop the nums[k]nums[k]'s. But, we can also note that when we reach the index jj while scanning backwards for finding nums[k]nums[k], the stackstack can contain atmost n-j-1n−j−1 elements. Here, nn refers to the number of elements in numsnums array.

        We can also note that this is the same number of elements which lie beyond the j^{th}j 
        th
        index in numsnums array. We also know that these elements lying beyond the j^{th}j 
        th
        index won't be needed in the future ever again. Thus, we can make use of this space in numsnums array instead of using a separate stackstack. The rest of the process can be carried on in the same manner as discussed in the last approach.

        We can try to go for another optimization here. Since, we've got an array for storing the potential nums[k]nums[k] values now, we need not do the popping process for a min[j]min[j] to find an element just larger than min[j]min[j] from amongst these potential values.

        Instead, we can make use of Binary Search to directly find an element, which is just larger than min[j]min[j] in the required interval, if it exists. If such an element is found, we can compare it with nums[j]nums[j] to check the 132 criteria. Otherwise, we continue the process as in the last approach.
    */
    bool doit_binary_search(vector<int>& nums) {
        if (nums.size() < 3) {
            return false;
        }
        vector<int> min_array(nums.size());
        min_array[0] = nums[0];

        for (size_t i = 1; i < nums.size(); i++) {
            min_array[i] = std::min(min_array[i - 1], nums[i]);
        }
        int k = nums.size();
        for (size_t j = nums.size() - 1; j > 0; j--) {
            if (nums[j] <= min_array[j]) {
                continue;
            }
            auto it = lower_bound(nums.begin() + k, nums.end(), min_array[j] + 1);
            k = it - nums.begin();
            if (k < nums.size() && nums[k] < nums[j]) {
                return true;
            }
            nums[--k] = nums[j];
        }
        return false;
    }
};