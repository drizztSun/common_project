#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

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

class FindKthLargest {

public :

	// This problem needs to use partial sorting. In STL, there are two built-in functions (nth_element and partial_sort) for this.
	int doit(vector<int>& nums, int k) {

		nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), greater<int>());
		return nums[k - 1];
	}

	int doit2(vector<int>& nums, int k) {
		partial_sort(nums.begin(), nums.begin() + k, nums.end(), greater<int>());
		return nums[k - 1];
	}

	// Note the off - by - 1 difference in the second argument of the two built - in functions.
	// We may also use a heap to solve this problem.We can maintain the largest k elements in a heap with the smallest among them 
	// at the top.Or we can add all the elements to a heap, with the largest at the top, and then pop the heap for k - 1 times, 
	// then the one on the top is our target.The first one is min - heap and the second one is max - heap.
	// In STL, both priority_queue and multiset can be used as a min / max - heap.
	
	// min-heap using priority_queue
	int doit1(vector<int>& nums, int k) {

		priority_queue<int, vector<int>, greater<int>> pq;

		for (int n : nums) {
			pq.push(n);
			if (pq.size() > k) {
				pq.pop();
			}
		}
		return pq.top();
	}

	// max-heap using priority_queue
	int doit3(vector<int>& nums, int k) {

		priority_queue<int> pq(nums.begin(), nums.end());

		while (k > 1) {
			pq.pop();
			k--;
		}
		return pq.top();
	}

};

class Solution {
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
				swap(nums[l++], nums[r--]);
			}
			if (nums[l] >= pivot) {
				l++;
			}
			if (nums[r] <= pivot) {
				r--;
			}
		}
		swap(nums[left], nums[r]);
		return r;
	}
};