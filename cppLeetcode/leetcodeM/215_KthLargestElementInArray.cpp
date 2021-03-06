/*
215. Kth Largest Element in an Array

Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

Example 1:

Input: [3,2,1,5,6,4] and k = 2
Output: 5
Example 2:

Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4

*/
#include <vector>
#include <algorithm>
#include <queue>

using std::priority_queue;
using std::vector;


class FindKthLargest {


	int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums,0,nums.size()-1,nums.size()-k);
    }
    
    int quickSelect(vector<int>& nums, int low, int high, int k){
        int tar = nums[low], i = low, j = high;
        while(i < j){
            while(i<j && nums[j] >= tar)
                j--;
            if(i<j)
                nums[i++] = nums[j];
            while(i<j && nums[i] <= tar)
                i++;
            if(i<j)
                nums[j--] = nums[i];
        }
        nums[i] = tar;
        if(i == k)
            return tar;
        else if(i > k)
            return quickSelect(nums,low,i-1,k);
        else
            return quickSelect(nums,i+1,high,k);
    }

	/*
		215.Kth-Largest-Element-in-an-Array
		此题比较简单的方法就是用priority_queue,遍历整个数组,每次只保留最大的K个值.

		另外还有一个理论上o(N)的算法，就是二分搜值，猜测这个数是t。如果发现nums里大于等于t的个数大于等于k，那么我们可以猜测更大的t（注意t可能是答案），将下界上调为t；反之我们可以猜测更小的t（注意t不可能是答案），将上界下调至t-1。

		最后上下界收敛的结果一定就是答案。
	
	*/
 	int doit_binary_search(vector<int>& nums, int k) 
    {
        long left = INT_MIN, right = INT_MAX;

		auto count = [&](int t)
		{
			int ret = 0;
			for (auto x: nums)
				ret += (x>=t);
			return ret;
		};

        while (left<right)
        {
            int mid = right-(right-left)/2;
            if (count(mid) >=k)            
                left = mid;
            else
                right = mid-1;
        }  
        return left;
    }

public :

	// This problem needs to use partial sorting. In STL, there are two built-in functions (nth_element and partial_sort) for this.
	int doit(vector<int>& nums, int k) {
		// O(n + k*log(k))
		nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), std::greater<int>());
		return nums[k - 1];
	}

	int doit2(vector<int>& nums, int k) {
		partial_sort(nums.begin(), nums.begin() + k, nums.end(), std::greater<int>());
		return nums[k - 1];
	}

	// Note the off - by - 1 difference in the second argument of the two built - in functions.
	// We may also use a heap to solve this problem.We can maintain the largest k elements in a heap with the smallest among them 
	// at the top.Or we can add all the elements to a heap, with the largest at the top, and then pop the heap for k - 1 times, 
	// then the one on the top is our target.The first one is min - heap and the second one is max - heap.
	// In STL, both priority_queue and multiset can be used as a min / max - heap.
	
	// min-heap using priority_queue
	int doit_heapmin(vector<int>& nums, int k) {

		priority_queue<int, vector<int>, std::greater<int>> pq;

		for (int n : nums) {
			pq.push(n);
			if (pq.size() > k) {
				pq.pop();
			}
		}
		return pq.top();
	}

	// max-heap using priority_queue
	int doit_heapmax(vector<int>& nums, int k) {

		priority_queue<int> pq(nums.begin(), nums.end());

		while (k > 1) {
			pq.pop();
			k--;
		}
		return pq.top();
	}

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