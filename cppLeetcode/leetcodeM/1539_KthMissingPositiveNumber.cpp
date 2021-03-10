/*
1539. Kth Missing Positive Number

Given an array arr of positive integers sorted in a strictly increasing order, and an integer k.

Find the kth positive integer that is missing from this array.

 

Example 1:

Input: arr = [2,3,4,7,11], k = 5
Output: 9
Explanation: The missing positive integers are [1,5,6,8,9,10,12,13,...]. The 5th missing positive integer is 9.
Example 2:

Input: arr = [1,2,3,4], k = 2
Output: 6
Explanation: The missing positive integers are [5,6,7,...]. The 2nd missing positive integer is 6.
 

Constraints:

1 <= arr.length <= 1000
1 <= arr[i] <= 1000
1 <= k <= 1000
arr[i] < arr[j] for 1 <= i < j <= arr.length
*/
#include <vector>
#include <unordered_set>

using std::unordered_set;
using std::vector;

class KthMissingPositiveNum {

    /*
    
        1539.Kth-Missing-Positive-Number
        解法1：
        将数组的所有元素放入一个集合。然后从1开始自增cur，查看cur是否在数组里出现过来统计missing的个数。

        解法2：
        利用一个指针i遍历数组元素，同时用cur表示当前可能的missing number。初始时cur = 1.

        如果cur>arr[i]，那么考察下一个i。否则即cur<=arr[i]，说明从cur到arr[i]-1之间（双闭区间）都是missing number。于是missing number的数量减少k-=arr[i]-cur，下一个需要尝试的missing number更新为arr[i]+1. 直到k降为0为止。

        注意，如果数组遍历完之后k仍然不为0，考虑到cur本身必然就是一个missing number，那么最终的答案是cur+=k-1.

        解法3：
        二分搜索。和1060.Missing-Element-in-Sorted-Array一样的思路。

        假设我们猜测mid是否是答案。考察[1,mid-1]这段连续自然数区间，可知道这段区间的自然数有M个，并且有T个存在于数组中（即查找数组里有多少个小于mid的元素个数，利用lower_bound）。
        所以，在[1,mid-1]这段连续自然数区间内有missing number = M-T个。理论上我们希望这段区间应该有missing number共k-1个，于是就可以帮助判定mid是否偏大和偏小。

                    if (missing <= k-1)
                        left = mid;
                    else
                        right = mid-1;
        特别注意，当missing==k-1的时候，mid可能并不是最终答案，因为mid可能也存在于数组中，所以mid可以再往大猜(即left=mid)。因此这个分支在上面的代码里与missing<k-1合并。
    */
    int doit_hashtable(vector<int>& arr, int k) 
    {
        unordered_set<int>Set(arr.begin(), arr.end());
        int count = 0;
        for (int i=1; i<=arr.back()+1000; i++)
        {
            if (Set.find(i)==Set.end())
                count+=1;
            if (count==k)
                return i;
        }
        return -1;
    }

    int doit_linear(vector<int>& arr, int k) 
    {
        int cur = 1;        
        for (int i=0; i<arr.size(); i++)
        {
            if (cur > arr[i]) continue;
            
            if (arr[i] - cur < k)
            {
                k -= (arr[i]-cur);
                cur = arr[i]+1;                    
            }
            else
            {
                cur += k-1;
                return cur;
            }            
        }
        return cur+k-1;
    }

    int doit_binary_search(vector<int>& arr, int k) 
    {
        int left = 1;
        int right = arr.back()+k;
        while (left < right)
        {
            int mid = right-(right-left)/2;
            int M = mid-1;
            int T = lower_bound(arr.begin(), arr.end(), mid)- arr.begin();
            int missing = M - T;

            if (missing <= k-1)
                left = mid;
            else
                right = mid-1;
        }
        return left;
    }

    /*
        Approach 1: Brute Force, O(N) time
        The first idea is to solve the problem in a linear time by parsing all array elements. It's easy to say how many positive numbers are missing between two array elements: arr[i + 1] - arr[i] - 1, and we could use it to solve the problem.

        img Figure 1. Approach 1. Iterate over the array and compute the number of missing numbers in-between the elements.

        Algorithm

        Check if the kth missing number is less than the first element of the array. If it's the case, return k.

        Decrease k by the number of positive integers which are missing before the array starts: k -= arr[0] - 1.

        Iterate over the array elements:

        At each step, compute the number of missing positive integers in-between i + 1th and ith elements: currMissing = arr[i + 1] - arr[i] - 1.

        Compare k to the currMissing. If k <= currMissing then the number to return is in-between arr[i + 1] and arr[i], and you could return it: arr[i] + k.

        Otherwise, decrease k by currMissing and proceed further.

        We're here because the element to return is greater than the last element of the array. Return it: arr[n - 1] + k.

        Implementation


        Complexity Analysis

        Time complexity: O(N) because in the worst case, we have to parse all array elements.

        Space complexity: O(1), we don't allocate any additional data structures.
    */
    int doit_linear(vector<int>& arr, int k) {

        // if the kth missing is less than arr[0]
        if (k <= arr[0] - 1) return k;
        
        k -= arr[0] - 1;
        int n = arr.size();

        // search kth missing between the array numbers
        for (int i = 0; i < n-1; i--) {

            // missing between arr[i] and arr[i + 1]
            int currentmissing = arr[i+1] - arr[i] - 1;

            // if the kth missing is between
            // arr[i] and arr[i + 1] -> return it
            if (currentmissing >= k) {
                return arr[i] + k; 
            }

            // otherwise, proceed further
            k -= currentmissing;
        }

        // // if the missing number if greater than arr[n - 1]
        return arr[n-1] + k;
    }

    /*
        Algorithm

        Initialize search boundaries: left = 0, right = arr.length - 1.

        While left <= right:

        Choose the pivot index in the middle: pivot = left + (right - left) / 2. Note that in Java we couldn't use straightforward pivot = (left + right) / 2 to avoid the possible overflow. 
        In Python, the integers are not limited, and we're fine to do that.

        If the number of positive integers which are missing before is less than k arr[pivot] - pivot - 1 < k - continue to search on the right side of the array: left = pivot + 1.
        Otherwise, continue to search on the left: right = pivot - 1.
        At the end of the loop, left = right + 1, and the kth missing number is in-between arr[right] and arr[left]. The number of integers missing before arr[right] is arr[right] - right - 1. 
        Hence, the number to return is arr[right] + k - (arr[right] - right - 1) = k + left.

        Implementation

        Complexity Analysis
        Time complexity: O(logN)
        Space complexity: O(1), we don't allocate any additional data structures.
    */
    int doit_binary_search(vector<int>& arr, int k) {

        int left = 0, right = arr.size()-1;

        while (left <= right) {

            int mid = left + (right - left) / 2;

            // If number of positive integers
            // which are missing before arr[pivot]
            // is less than k -->
            // continue to search on the right.
            if (arr[mid] - mid - 1 < k)
                left = mid + 1;
            // Otherwise, go left.
            else
                right = mid - 1;
        }

        // At the end of the loop, left = right + 1,
        // and the kth missing is in-between arr[right] and arr[left].
        // The number of integers missing before arr[right] is
        // arr[right] - right - 1 -->
        // the number to return is
        // arr[right] + k - (arr[right] - right - 1) = k + left
        return left + k;
    }


public:

    int doit_linear(vector<int>& arr, int k) {
        
        int diff = arr[0] - 1, last = arr[0];
        
        if (diff >= k) return arr[0] - (diff - k) - 1;

        for (int i = 1; i < arr.size(); i++) {

            diff += arr[i] - arr[i-1] - 1;

            if (diff >= k) {
                return arr[i] - (diff - k) - 1;
            }
        }

        return arr.back() + k - diff;
    }
};