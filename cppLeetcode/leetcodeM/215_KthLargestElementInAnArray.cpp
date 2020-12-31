/*

215. Kth Largest Element in an Array

Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

Example 1:

Input: [3,2,1,5,6,4] and k = 2
Output: 5
Example 2:

Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4
Note:
You may assume k is always valid, 1 ≤ k ≤ array's length.


*/
#include <vector>

using std::vector;


class findKthLargest {
public:
    
    int partition(vector<int>& nums , int l , int h)
    {
        int pivot = h;
        int j = l-1;
        
        for(int i = l ; i<=h ;i++)
        {
            if( nums[i] < nums[pivot])
            {
                j++;
                std::swap(nums[j] , nums[i]);
            }
        }
        
        j++;
        std::swap( nums[j] , nums[pivot]);
        return j;
    }
    
    int randomPart( vector<int>& nums , int l , int r)
    {
        int n = l + rand()%( r-l+1);
        std::swap( nums[n] , nums[r]);
        return partition( nums, l , r);
    }
    
    int findKthLargestUtil( vector<int>& nums, int k ,int l ,int h)
    {
        if( l <= h)
        {
            if( l == h)
                return nums[l];
            
            int p = randomPart( nums, l , h);
            
            if( p == k)
                return nums[p];
            else if( p > k)
            {
                return findKthLargestUtil(nums,k, l , p-1);
            }
            return findKthLargestUtil(nums,k, p+1 , h);
        }
        return -1;
    }
    
    int doit_partition_sort(vector<int>& nums, int k) {
        int n = nums.size();
        return findKthLargestUtil(nums, n-k, 0 , n-1 );        
        
    }
};