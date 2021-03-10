/*
658. Find K Closest Elements

Given a sorted integer array arr, two integers k and x, return the k closest integers to x in the array. The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b
 

Example 1:

Input: arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]
Example 2:

Input: arr = [1,2,3,4,5], k = 4, x = -1
Output: [1,2,3,4]
 

Constraints:

1 <= k <= arr.length
1 <= arr.length <= 10^4
arr is sorted in ascending order.
-10^4 <= arr[i], x <= 10^4
*/
#include <vector>

using std::vector;


class KCloestElements {


    /*
        658.Find-K-Closest-Elements
        容易想到的基本思路是，找一个k-size的滑窗，使得x-arr[left]和arr[right]-x尽量地接近。以此为依据，调整起始点left的二分搜索范围。但这种二分法，最后的收敛结果并不一定是最终理想的k-size滑窗的起始点。

        有一个非常NB的方法。同样是调整起始点left的二分搜索范围，但是查看的是长度为k+1的滑窗。因为这个窗口有k+1个元素，肯定有一个元素不属于k-closest element，容易知道，这个不合格的元素肯定就是arr[left]和arr[left+k]中的一个！那怎么判断是其中哪一个呢？就找其中“相对不合格”的那个。

        如果x-arr[left] > arr[left+k]-x，说明arr[left]不合格，所以最终的k-size滑窗的起始点不会是left或其左边的任何位置。
        如果x-arr[left] < arr[left+k]-x，说明arr[left+k]不合格，所以最终的k-size滑窗的末尾点不会是right或其右边的任何位置，也就是说k-size滑窗的起始点不会是left右边的任何位置（注意可以是left）。
        如果x-arr[left] == arr[left+k]-x，说明arr[left]和arr[left+k]并列。根据规则，第k个closest只能算一个，所以那个不合格的元素只能给arr[left+k]，因此后续的处理就同2.
        因为此题一定有解，所以收敛后的位置就一定是最终理想的k-size滑窗的起始点。            
    */
    

public:

    vector<int> doit_binary_search(vector<int>& arr, int k, int x) {
        int low = 0;
        int hi = arr.size()-k;
        
        while (low<hi)
        {
            int mid = low+(hi-low)/2;
            
            if (x - arr[mid] > arr[mid+k] - x)
                low = mid+1;
            else
                hi = mid;
        }
        
        vector<int>ret;
        for (int i=low; i<low+k; i++)
            ret.push_back(arr[i]);
        
        return ret;
    }

    /*
        Approach 2: Binary Search and Two Pointers
        Algorithm

        The original array has been sorted so we can take this advantage by the following steps.

        If the target x is less or equal than the first element in the sorted array, the first k elements are the result.
        Similarly, if the target x is more or equal than the last element in the sorted array, the last k elements are the result.
        Otherwise, we can use binary search to find the index of the element, which is equal (when this list has x) or a little bit larger than x 
        (when this list does not have it). Then set low to its left k-1 position, and high to the right k-1 position of this index as a start. 
        
        The desired k numbers must in this rang [index-k-1, index+k-1]. So we can shrink this range to get the result using the following rules.
        If low reaches the lowest index 0 or the low element is closer to x than the high element, decrease the high index.
        If high reaches to the highest index arr.size()-1 or it is nearer to x than the low element, increase the low index.
        The looping ends when there are exactly k elements in [low, high], the subList of which is the result.

        Complexity Analysis

        Time complexity : O(logn+k).O(logn) is for the time of binary search, while O(k) is for shrinking the index range to k elements.

        Space complexity : O(k). It is to generate the required sublist.
    */
    vector<int> doit_binary_search(vector<int>& arr, int k, int x) {

        int l = 0, r = arr.size()-k;
        
        while (l < r) {
            int mid = (l + r) / 2;
            
            if (x - arr[mid] > arr[mid+k] - x)
                l = mid + 1;
            else
                r = mid;
        }
        
        return vector<int>(begin(arr) + l, begin(arr) + l + k);
    }
};