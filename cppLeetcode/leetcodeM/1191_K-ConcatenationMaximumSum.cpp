/*
1191. K-Concatenation Maximum Sum

Given an integer array arr and an integer k, modify the array by repeating it k times.

For example, if arr = [1, 2] and k = 3 then the modified array will be [1, 2, 1, 2, 1, 2].

Return the maximum sub-array sum in the modified array. Note that the length of the sub-array can be 0 and its sum in that case is 0.

As the answer can be very large, return the answer modulo 109 + 7.

 

Example 1:

Input: arr = [1,2], k = 3
Output: 9
Example 2:

Input: arr = [1,-2,1], k = 5
Output: 2
Example 3:

Input: arr = [-1,-2], k = 7
Output: 0
 

Constraints:

1 <= arr.length <= 10^5
1 <= k <= 10^5
-10^4 <= arr[i] <= 10^4
*/

#include <vector>

using std::vector;



class KConcatenationMaxSum {

    /*
        1191.K-Concatenation-Maximum-Sum
        假设我们有一段maxSum Subarray长得像这个样子：ATT...TTB，其中A是arr的末尾的一段，B是arr的开头的一段，中间有若干个完整的arr（写作T）。那么我们一定可以推论出T>0（也就是原始的arr的数组和必须大于零）。
        否则的话，T<0显然是个累赘，拖累了A+B，肯定不会满足ATT...TTB是maxSum Subarray的假设（因为比不过A+B）。反过来说，如果T>0，那么maxSum Subarray也一定是长得是ATT...TTB的模式（中间有k-2个T）。
        那么怎么确定A和B呢？其实只要将arr重复两次，在这个新数组arr2里面，AB是一段尾首相接的subarray，很容易找出最大的maxsum subarry。

        反之T<0的话，我们肯定不会让maxSum Subarray里面夹着任何完整的arr。所以maxSum Subarray就在arr2里面找就可以了。
    */
    long M = 1e9+7;
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) 
    {   
        if (k==1)
            return maxSubArrSum(arr)%M; 
        
        long arrSum = 0; 
        for (int i = 0; i < arr.size(); i++) 
        {
            arrSum += arr[i]; 
            arrSum %= M;
        }            
         
        int len = arr.size();
        for (int i=0; i<len; i++)
            arr.push_back(arr[i]);
        
        if (arrSum < 0)                     
            return maxSubArrSum(arr)%M;         
        else        
            return (maxSubArrSum(arr) + ((long)k - 2) * arrSum % M)%M;               
    }
    
    long maxSubArrSum(vector<int>arr) 
    { 
        long max_so_far = 0; 
        long max_ending_here = 0; 
  
        for (int i = 0; i < arr.size(); i++) 
        { 
            max_ending_here = max_ending_here + arr[i]; 
            max_ending_here %= M;
            if (max_ending_here < 0) 
                max_ending_here = 0; 
            if (max_so_far < max_ending_here) 
                max_so_far = max_ending_here;
        }
        return max_so_far; 
    }

public:
    
    /*
        Aggregate the entire array in a_sum.
        Find the maximum subbaray sum m_sum for 2-concatenated array (note the special case when k == 1). 
        if a_sum is a positive, m_sum will always span across two arrays.
        If a_sum > 0, add it k - 2 times to m_sum.
    */
    int doit_greedy(vector<int>& arr, int k) {

        int kMod = 1e9+7;
        int a_sum = 0, m_sum = 0, sz = arr.size();

        // calculate one or two array maximum subarray
        for (auto i = 0, sum = 0; i < std::min(2, k) * sz; ++i) {
        
            sum = std::max(sum + arr[i % sz], arr[i % sz]);
            m_sum = std::max(m_sum, sum);
            
            if (i < sz) a_sum += arr[i];
        }

        // if a_sum is a positive, m_sum will always span across two arrays.
        while (a_sum > 0 && --k >= 2)
            m_sum = (m_sum + a_sum) % kMod;

        return m_sum % kMod;
    }
};