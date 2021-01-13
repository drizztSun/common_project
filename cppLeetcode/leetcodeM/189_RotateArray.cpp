/*
189. Rotate Array

Given an array, rotate the array to the right by k steps, where k is non-negative.

Follow up:

Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
Could you do it in-place with O(1) extra space?
 

Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
Example 2:

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]
 

Constraints:

1 <= nums.length <= 2 * 104
-231 <= nums[i] <= 231 - 1
0 <= k <= 105

*/
#include <vector>

using std::vector;

class RotateArray {

public:
    
    /*
            Approach 3: Using Cyclic Replacements
    Algorithm

    We can directly place every number of the array at its required correct position. But if we do that, we will destroy the original element. Thus, we need to store the number being replaced in a temptemp variable. Then, we can place the replaced number(\text{temp}temp) at its correct position and so on, nn times, where nn is the length of array. We have chosen nn to be the number of replacements since we have to shift all the elements of the array(which is nn). But, there could be a problem with this method, if n \% k = 0n%k=0 where k = k \% nk=k%n (since a value of kk larger than nn eventually leads to a kk equivalent to k \% nk%n). In this case, while picking up numbers to be placed at the correct position, we will eventually reach the number from which we originally started. Thus, in such a case, when we hit the original number's index again, we start the same process with the number following it.

    Now let's look at the proof of how the above method works. Suppose, we have nn as the number of elements in the array and kk is the number of shifts required. 
    Further, assume n \%k = 0n%k=0. Now, when we start placing the elements at their correct position, in the first cycle all the numbers with their index ii satisfying i \%k = 0i%k=0 get placed at their required position. 
    This happens because when we jump k steps every time, we will only hit the numbers k steps apart. We start with index i = 0i=0, having i \% k = 0i%k=0. Thus, we hit all the numbers satisfying the above condition in the first cycle. 
    When we reach back the original index, we have placed \frac{n}{k} 
    k
    n
    ​	
    elements at their correct position, since we hit only that many elements in the first cycle. Now, we increment the index for replacing the numbers. This time, we place other \frac{n}{k} 
    k
    n
    ​	
    elements at their correct position, different from the ones placed correctly in the first cycle, because this time we hit all the numbers satisfy the condition i \% k = 1i%k=1. 
    When we hit the starting number again, we increment the index and repeat the same process from i = 1i=1 for all the indices satisfying i \% k == 1i%k==1. This happens till we reach the number with the index i \% k = 0i%k=0 again, 
    which occurs for i=ki=k. We will reach such a number after a total of kk cycles. Now, the total count of numbers exclusive numbers placed at their correct position will be k \times \frac{n}{k} = nk× 
    k
    n
    ​	
    =n. Thus, all the numbers will be placed at their correct position.

    Look at the following example to clarify the process:
    Complexity Analysis
        Time complexity: \mathcal{O}(n)O(n). Only one pass is used.

        Space complexity: \mathcal{O}(1)O(1). Constant extra space is used.

    */
    void doit_(vector<int>& nums, int k) {
        
        k %= nums.size();
        if (k == 0) return;
        
        int cnt = nums.size();
        int start = 0;
        int base = nums.size();
        
        while (cnt) {
            int last = start, prev = nums[start];
            while (true) {
                int cur = (last + k) % base;
                int tmp = nums[cur];
                nums[cur] = prev;
                prev = tmp;
                cnt--;
                if (cur == start) 
                    break;
                last = cur;
            }
            start++;
        }
    }

    /*

    */
    void doit_(vector<int>& nums, int k) {

        auto reverse = [&](int i, int j) {
            while (i < j) {
                int tmp = nums[j];
                nums[j] = nums[i];
                nums[i] = tmp;
                i++, j--;
            }
        };

        k %= nums.size();
        if (k == 0) return;

        reverse(0, nums.size() - 1);
        reverse(0, k-1);
        reverse(k, nums.size() -1);
    }
};