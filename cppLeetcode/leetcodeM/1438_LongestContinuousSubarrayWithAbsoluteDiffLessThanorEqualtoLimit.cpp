/*
1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit


Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to limit.

 

Example 1:

Input: nums = [8,2,4,7], limit = 4
Output: 2 
Explanation: All subarrays are: 
[8] with maximum absolute diff |8-8| = 0 <= 4.
[8,2] with maximum absolute diff |8-2| = 6 > 4. 
[8,2,4] with maximum absolute diff |8-2| = 6 > 4.
[8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
[2] with maximum absolute diff |2-2| = 0 <= 4.
[2,4] with maximum absolute diff |2-4| = 2 <= 4.
[2,4,7] with maximum absolute diff |2-7| = 5 > 4.
[4] with maximum absolute diff |4-4| = 0 <= 4.
[4,7] with maximum absolute diff |4-7| = 3 <= 4.
[7] with maximum absolute diff |7-7| = 0 <= 4. 
Therefore, the size of the longest subarray is 2.
Example 2:

Input: nums = [10,1,2,4,7,2], limit = 5
Output: 4 
Explanation: The subarray [2,4,7,2] is the longest since the maximum absolute diff is |2-7| = 5 <= 5.
Example 3:

Input: nums = [4,2,2,2,4,4,2,2], limit = 0
Output: 3
 

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
0 <= limit <= 10^9

*/
#include <vector>
#include <deque>
#include <set>

using std::multiset;
using std::deque;
using std::vector;

//TC: O(n)
//SC: O(n)
class LongestContinuousSubarray {

public:


    /*
        Intuition
        Last week we learned,
        in 1425. Constrained Subsequence Sum
        how to get minimum in a subarray when sliding.

        This week, we need to get both the maximum and the minimum,
        at the same time.

        So I opened my post last week,
        and copy some my own codes.


        Solution 0: Binary insert and remove
        Keep an increasing list L.
        Binary insert the current element.
        If the L[L.size() - 1] - L[0] > limit,
        binary search the position of A[i] and remove it from the list.

        Time O(N^2)
        Space O(N)

        Solution 1: Use two heaps
        Time O(NogN)
        Space O(N)


    */

    /*
        Solution 2: Use TreeMap
        Use one tree map can easily get the maximum and the minimum at the same time.
        In java, we can use TreeMap to count elements.
        In cpp, it suports multi treeset, that's even better.

        Time O(NogN)
        Space O(N)
    */
    int doit_(vector<int>& A, int limit) {
        int i = 0, j;
        multiset<int> m;
        for (j = 0; j < A.size(); ++j) {
            m.insert(A[j]);
            if (*m.rbegin() - *m.begin() > limit)
                m.erase(m.find(A[i++]));
        }
        return j - i;
    }

    /*
        Solution 3: Use two deques
        Time O(N)
        Space O(N)
    */
    int doit_sliding_window(vector<int>& A, int limit) {
        deque<int> maxd, mind;
        int i = 0, j;
        for (j = 0; j < A.size(); ++j) {
            while (!maxd.empty() && A[j] > maxd.back()) maxd.pop_back();
            while (!mind.empty() && A[j] < mind.back()) mind.pop_back();
            maxd.push_back(A[j]);
            mind.push_back(A[j]);
            if (maxd.front() - mind.front() > limit) {
                if (maxd.front() == A[i]) maxd.pop_front();
                if (mind.front() == A[i]) mind.pop_front();
                ++i;
            }
        }
        return j - i;
    }

    /*
        monotonic queue, increasing and decreaing for min value and max value
    */
    int doit_(vector<int>& nums, int limit) {
        
        int l = 0;
        int r = 0;
        int res = 0;
        
        deque<int> tmin{INT_MAX};
        deque<int> tmax{INT_MIN};
        
        while(r < nums.size()){
            
            while(!tmin.empty() && tmin.back() > nums[r]) tmin.pop_back();
            while(!tmax.empty() && tmax.back() < nums[r]) tmax.pop_back();

            tmin.push_back(nums[r]);
            tmax.push_back(nums[r]);
            
            if(abs(tmax.front() - tmin.front()) <= limit)
                res = std::max(res, r - l + 1);
            
            while(l < r && abs(tmax.front() - tmin.front()) > limit){
                if(nums[l] == tmin.front()) tmin.pop_front();
                if(nums[l] == tmax.front()) tmax.pop_front();
                l++;
            }

            r++;
        }
        
        return res;
    }


    int doit_(vector<int>& nums, int limit) {
        int maxLen = 1;
        multiset<int> curEl{nums[0]};
        
        for (int r = 1, l = 0; r < nums.size(); r++) {
            curEl.insert(nums[r]);
            while (*curEl.rbegin() - *curEl.begin() > limit) {
                curEl.erase(curEl.find(nums[l]));
                l++;
            }
            maxLen = std::max(maxLen, static_cast<int>(curEl.size()));
        }
        return maxLen;
    }
};