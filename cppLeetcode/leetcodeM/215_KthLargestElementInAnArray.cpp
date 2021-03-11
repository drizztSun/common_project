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
#include <algorithm>
#include <functional>

using std::vector;


class KthLargest {
    /*
        215.Kth-Largest-Element-in-an-Array
        此题比较简单的方法就是用priority_queue,遍历整个数组,每次只保留最大的K个值.

        另外还有一个理论上o(N)的算法，就是二分搜值，猜测这个数是t。如果发现nums里大于等于t的个数大于等于k，那么我们可以猜测更大的t（注意t可能是答案），将下界上调为t；反之我们可以猜测更小的t（注意t不可能是答案），将上界下调至t-1。

        最后上下界收敛的结果一定就是答案。
    */
    int findKthLargest(vector<int>& nums, int k) 
    {
        long left = INT_MIN, right = INT_MAX;
        while (left<right)
        {
            int mid = right-(right-left)/2;
            if (count(nums,mid) >=k)            
                left = mid;
            else
                right = mid-1;
        }  
        return left;
    }

    int count(vector<int>&nums, int t)
    {
        int ret = 0;
        for (auto x: nums)
            ret += (x>=t);
        return ret;
    }

public:


    int doit_binary_search(vector<int>& nums, int k) {
        
        int low = *min_element(begin(nums), end(nums)), high = *max_element(begin(nums), end(nums));
        
        while (low < high) {

            int mid = high - (high - low) / 2;
            
            int cnt = 0;
            for (auto c : nums)
                if (c >= mid) cnt++;
            
            if (cnt >= k)
                low = mid;
            else
                high = mid - 1;
        }
        
        return low;
    }

    /*
        Problem: We have to find Kth Largest element in an array.

        Intuition: Say we found the Kth Largest element, then we can say that
        in a sorted array, on the right of this element there is K-1 element which is greater than it and left there is N-K elements smaller. 
        Can we not use Binary search if we have search space between min_element and max_element?
        where N is size of the array.
    */
    int doit_binary_search(vector<int>& A, int k) {

        int lo = *min_element(A.begin(), A.end()), hi = *max_element(A.begin(), A.end());
        int m = A.size();

        while(lo < hi){
        
            int mid = lo + (hi-lo)/2;
            /// now check how many elements are lesser than mid
            int count = 0;
            for(int i=0;i<m;i++){
                count += (A[i] <= mid);
            }

            if(count < m-k+1) 
                lo = mid+1; /// mid is also included
            else 
                hi = mid;
        }
        return lo;
    }
    
    /*
        Approach 2: Quickselect
        This textbook algorthm has \mathcal{O}(N)O(N) average time complexity. Like quicksort, it was developed by Tony Hoare, and is also known as Hoare's selection algorithm.

        The approach is basically the same as for quicksort. For simplicity let's notice that kth largest element is the same as N - kth smallest element, hence one could implement kth smallest algorithm for this problem.

        First one chooses a pivot, and defines its position in a sorted array in a linear time. This could be done with the help of partition algorithm.

        To implement partition one moves along an array, compares each element with a pivot, and moves all elements smaller than pivot to the left of the pivot.

        As an output we have an array where pivot is on its perfect position in the ascending sorted array, all elements on the left of the pivot are smaller than pivot, and all elements on the right of the pivot are larger or equal to pivot.

        Hence the array is now split into two parts. If that would be a quicksort algorithm, one would proceed recursively to use quicksort for the both parts that would result in \mathcal{O}(N \log N)O(NlogN) time complexity. Here there is no need to deal with both parts since now one knows in which part to search for N - kth smallest element, and that reduces average time complexity to \mathcal{O}(N)O(N).

        Finally the overall algorithm is quite straightforward :

        Choose a random pivot.

        Use a partition algorithm to place the pivot into its perfect position pos in the sorted array, move smaller elements to the left of pivot, and larger or equal ones - to the right.

        Compare pos and N - k to choose the side of array to proceed recursively.

        ! Please notice that this algorithm works well even for arrays with duplicates.

        quickselect


        Time complexity : O(N) in the average case, O(N^2) in the worst case.
        Space complexity : O(1).
    */
    int doit_quickselect(vector<int>& nums, int k) {
        int n = nums.size();
        std::nth_element(begin(nums), begin(nums) + n - k, end(nums));
        return nums[n-k];
    }
    
    int doit_partition_sort(vector<int>& nums, int k) {
        int n = nums.size();

        auto partition = [&](int l , int h)
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
        };
        
        auto randomPart = [&](int l , int r)
        {
            int n = l + rand()%( r-l+1);
            std::swap( nums[n] , nums[r]);
            return partition(l , r);
        };
        
        std::function<int(int, int, int)> findKthLargestUtil = [&](int k ,int l ,int h)
        {
            if( l <= h)
            {
                if( l == h)
                    return nums[l];
                
                int p = randomPart(l, h);
                
                if( p == k) return nums[p];
                
                if( p > k)
                    return findKthLargestUtil(k, l , p-1);

                return findKthLargestUtil(k-p, p+1 , h);
            }
            return -1;
        };
    
        return findKthLargestUtil(n-k, 0, n-1);    
    }
};