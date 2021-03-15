/*
485. Max Consecutive Ones

Given a binary array, find the maximum number of consecutive 1s in this array.

Example 1:
Input: [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s.
    The maximum number of consecutive 1s is 3.
Note:

The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000
*/
#include <vector>

using std::vector;

class MaxConsecutiveOnesI {

public:
    
    int doit_(vector<int>& nums) {
        
    }
};
/*
487. Max Consecutive Ones II


Given a binary array, find the maximum number of consecutive 1s in this array if you can flip at most one 0.

Example 1:
Input: [1,0,1,1,0]
Output: 4
Explanation: Flip the first zero will get the the maximum number of consecutive 1s.
    After flipping, the maximum number of consecutive 1s is 4.
Note:

The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000
Follow up:
What if the input numbers come in one by one as an infinite stream? In other words, you can't store all numbers coming from the stream as it's too large to hold in memory. Could you solve it efficiently?

*/



class MaxConsecutiveOnesII {

    /*
        Approach 2: Sliding Window
        Intuition

        The naive approach works but our interviewer is not convinced. Let's see how we can optimize the code we just wrote.

        The brute force solution had a time complexity of O(n^2). What was the bottleneck? Checking every single consecutive sequence. 
        Intuitively, we know we're doing repeated work because sequences overlap. We are checking consecutive sequence blindly. We need to establish some rules on how to move our sequence forward.

        If our sequence is valid, let's continue expanding our sequence (because our goal is to get the largest sequence possible).
        If our sequence is invalid, let's stop expanding and contract our sequence (because an invalid sequence will never count towards our largest sequence).
        The pattern that comes to mind for expanding/contracting sequences is the sliding window. Let's define valid and invalid states.

        Valid State = one or fewer 0's in our current sequence
        Invalid State = two 0's in our current sequence
        Algorithm

        Great. How do we apply all this to the sliding window?

        Let's use left and right pointers to keep track of the current sequence a.k.a. our window. Let's expand our window by moving the right pointer forward until we reach a point where we have more than one 0 in our window. 
        When we reach this invalid state, let's contract our window by moving the left pointer forward until we have a valid window again. 
        By expanding and contracting our window from valid and invalid states, we are able to traverse the array efficiently without repeated overlapping work.

        Now we can break this approach down into a few actionable steps:

        While our window is in bounds of the array...

        Add the rightmost element to our window
        Check if our window is invalid. If so, contract the window until valid.
        Update our the longest sequence we've seen so far
        Continue to expand our window
        This will look like this:

        Current
        1 / 10

        Complexity Analysis

        Let nn be equal to the length of the input nums array.

        Time complexity : O(n). Since both the pointers only move forward, each of the left and right pointer traverse a maximum of n steps. Therefore, the timecomplexity is O(n).
        Space complexity : O(1). Same as the previous approach. We don't store anything other than variables. Thus, the space we use is constant because it is not correlated to the length of the input array.
    */
    int doit_slidingwindow(vector<int>& nums) {
        
        int zeros = 0, last = -1, lastzero = -1;
        int total = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            
            if (nums[i] == 0) {
                last = lastzero, lastzero = i;
            }
            total = std::max(total, i - last);
            
        }
        
        return total > 0 ? total : 1;
    }

    int doit_(vector<int>& nums) {
        
        int longestSequence = 0;
        int left = 0;
        int right = 0;
        int numZeroes = 0;

        // while our window is in bounds
        while (right < nums.size()) {

            // add the right most element into our window
            if (nums[right] == 0) {
                numZeroes++;
            }

            // if our window is invalid, contract our window
            while (numZeroes == 2) {
                if (nums[left] == 0) {
                    numZeroes--;
                }
                left++;
            }

            // update our longest sequence answer
            longestSequence = std::max(longestSequence, right - left + 1);

            // expand our window
            right++;
        }
        return longestSequence;
    }

public:
    
    int doit_dp(vector<int>& nums) {
        
        int flip = 0, nonflip = 0;
        int res = 0;
        
        for (auto c : nums) {
            
            if (c == 1) {
                flip++;
                nonflip++;
            } else {
                std::swap(flip, nonflip);
                flip = 0, nonflip++;
            }
            
            res = std::max(res, std::max(flip, nonflip));
        }
        
        return res;
    }
};