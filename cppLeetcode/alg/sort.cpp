#include <vector>

using std::vector;



class FindKthLargest {
public:
	int findKthLargest(vector<int>& nums, int k) {
		int left = 0, right = nums.size() - 1, kth;
		while (true) {
			int idx = partition(nums, left, right);
			if (idx == k - 1) {
				kth = nums[idx];
				break;
			}
			if (idx < k - 1) {
				left = idx + 1;
			}
			else {
				right = idx - 1;
			}
		}
		return kth;
	}
private:
	int partition(vector<int>& nums, int left, int right) {
		int pivot = nums[left], l = left + 1, r = right;
		while (l <= r) {
			if (nums[l] < pivot && nums[r] > pivot) {
				std::swap(nums[l++], nums[r--]);
			}
			if (nums[l] >= pivot) {
				l++;
			}
			if (nums[r] <= pivot) {
				r--;
			}
		}
		std::swap(nums[left], nums[r]);
		return r;
	}
};


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