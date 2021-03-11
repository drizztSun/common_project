#include <vector>
#include <numeric>
#include <algorithm>

using std::vector;


int binary_search_1(vector<int>& nums, int target) {

    int left = 0, right = nums.size();

    // [left, right] scope, 
    while (left < right) { // left <= right

        // if left and right are all so big number, it is gonna be overflow.
        int mid = left + (right - left) / 2;

        if (nums[mid] >= target)
            // mid is correct target, so right needs tp include target. 
            // right = mid + 1;
            right = mid;
        else
            // mid is not correct, so left needs not to include target.
            left = mid + 1; 
    }

    return left;
}


int doit_binary_search(vector<int>& nums, int threshold) {
    
    int left = 1, right = *max_element(begin(nums), end(nums));
    
    while (left <= right) {
        
        int mid = left + (right - left) / 2;
        
        int total = 0;
        for (auto c : nums)
            total += c / mid + (c % mid == 0 ? 0 : 1);
        
        if (total > threshold)
            left = mid + 1;
        else 
            right = mid - 1;
    }
    
    return left;
}

// 1539 Missing number
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

// 215 find kth larget 
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

// right side gets closed.
int maxDistance(vector<int>& position, int m) 
    {
        sort(position.begin(), position.end());
        int left = 1, right = position.back()-position[0];


        auto isOK = [&](int len, int m)
        {
            int j=0;
            int count = 1;
            
            for (int i=0; i<position.size(); )
            {
                j = i;
                while (j<position.size() && position[j]-position[i]<len)
                    j++;
                            
                if (j==position.size()) 
                    break;
                else
                {
                    count++;                
                    i=j;
                }
                if (count==m) return true;
                
            }
            return false;
        };

        // [left, right]
        while (left < right) // left < right, left == right is always equal to right, or left<= right, left = right + 1.
        {
            int mid = right-(right-left)/2;

            // Old code is left + (right-left) / 2, but need to double check. 
            // if left, right 0, 1, mid is 0, then left is 0 again. it is dead-loop.
            // New code, for left, right is 0, 1, then mid is 1, it will be good.
            if (isOK(mid, m))
                left = mid; // we wannt push the value bigger, so mid is a valid one.
            else
                // mid needs to be dropped, because it is not legal for rule.
                right = mid-1;
        }
        return left; // we don't check, because there is always a value.   if it is possible no answer, we need to run isOK(left) to check.
    }