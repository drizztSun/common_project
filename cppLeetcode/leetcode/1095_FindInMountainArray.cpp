/*
1095. Find in Mountain Array

(This problem is an interactive problem.)

You may recall that an array A is a mountain array if and only if:

A.length >= 3
There exists some i with 0 < i < A.length - 1 such that:
A[0] < A[1] < ... A[i-1] < A[i]
A[i] > A[i+1] > ... > A[A.length - 1]
Given a mountain array mountainArr, return the minimum index such that mountainArr.get(index) == target.  If such an index doesn't exist, return -1.

You can't access the mountain array directly.  You may only access the array using a MountainArray interface:

MountainArray.get(k) returns the element of the array at index k (0-indexed).
MountainArray.length() returns the length of the array.
Submissions making more than 100 calls to MountainArray.get will be judged Wrong Answer.  Also, any solutions that attempt to circumvent the judge will result in disqualification.

 

Example 1:

Input: array = [1,2,3,4,5,3,1], target = 3
Output: 2
Explanation: 3 exists in the array, at index=2 and index=5. Return the minimum index, which is 2.
Example 2:

Input: array = [0,1,2,4,2,1], target = 3
Output: -1
Explanation: 3 does not exist in the array, so we return -1.
 

Constraints:

3 <= mountain_arr.length() <= 10000
0 <= target <= 10^9
0 <= mountain_arr.get(index) <= 10^9
*/



/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class MountainArray {

public:
    
    int doit_binary_search(int target, MountainArray &mountainArr) {
        
        int length = mountainArr.length();
        
        auto findpeak = [&]() {
          
            int low = 0, high = length;
            
            while (low < high) {
                int mid = (low + high) / 2;
                int midv = mountainArr.get(mid);
                if (mid == length - 1) break;
                int midnext = mountainArr.get(mid+1);
                
                if (midnext > midv)
                    low = mid + 1;
                else
                    high = mid;
            }
            
            return low;
        };
        
        auto search = [&](int s, int e, bool asc) {
          
            while (s < e) {
                
                int mid = (s + e) / 2;
                
                int midv = mountainArr.get(mid);
                
                if (midv == target) return mid;
                
                if (midv > target && asc || !asc && midv < target)
                    e = mid;
                else 
                    s = mid + 1;
            }
            
            return -1;
        };
        
        int p = findpeak();
        
        if (mountainArr.get(p) == target) return p;
        
        int a = search(0, p, true), b = search(p+1, length, false);
        
        return a > -1 ? a : b;
    }
};