/*
# 719. Find K-th Smallest Pair Distance


# Given an integer array, return the k-th smallest distance among all the pairs.
# The distance of a pair (A, B) is defined as the absolute difference between A and B.

# Example 1:
# Input:
# nums = [1,3,1]
# k = 1
# Output: 0
# Explanation:
# Here are all the pairs:
# (1,3) -> 2
# (1,1) -> 0
# (3,1) -> 2
# Then the 1st smallest distance pair is (1,1), and its distance is 0.

# Note:
# 2 <= len(nums) <= 10000.
# 0 <= nums[i] < 1000000.
# 1 <= k <= len(nums) * (len(nums) - 1) / 2.
*/




#include <vector>
#include <algorithm>
#include <queue>

using std::priority_queue;
using std::vector;


class KthSmallestPairDistance {

	/*
		719.Find-K-th-Smallest-Pair-Distance
		对于能够明显判断出上下界的题目，用二分法的思想往往非常巧妙。

		在本题中，将nums排序后，最大的差值是nums.back()-nums[0]；最小的差值必定存在于相邻的两个元素之间，也很容易算出来。于是相当于我们知道了差值的左边界left，右边界right，需要找一个居于中间的数mid，使得差值小于等于mid的pair数目正好是k个。

		对于二分法的外框架，容易知道，需要二分搜索的次数就是 log_2^(right-left)。对于给出的mid，如何得到差值小于等于mid的pair数目呢？也很简单，只要loop over 第一个数，那么第二个数的范围就可以通过upper_bound来确定。特别注意为什么是upper_bound.

		for (int i=0; i<nums.size(); i++)
		{
		auto pos=upper_bound(nums.begin(),nums.end(),nums[i]+mid); // 值大于nums[i]+mid的元素的指针
		count+= pos-1-(nums.begin()+i); // 值小于等于nums[i]+mid的元素的个数
		}
		用upper_bound()是 nlog(n)的复杂度。当然也可以通过双指针来做，就是o(n)的复杂度。

		PS:对于求Kth smallest的题目，用binary search by value的方法往往能有奇效。相似的题目有：

		668	Kth-Smallest-Number-in-Multiplication-Table
		373	Find K Pairs with Smallest Sums
		81	Search in Rotated Sorted Array II
		4	Median of Two Sorted Arrays
	*/
	int smallestDistancePair(vector<int>& nums, int k) 
    {
        sort(nums.begin(),nums.end());
        int N=nums.size();
        
        int left=nums[1]-nums[0];
        for (int i = 0; i <= N-2; ++i)
            left = std::min(left, nums[i+1] - nums[i]);
        
        int right=nums[N-1]-nums[0];
        int mid;
        
        while (left<right)
        {
            mid=left+(right-left)/2;
            int count=0;
            for (int i=0; i<N; i++)
            {
                auto pos=upper_bound(nums.begin(),nums.end(), nums[i]+mid);
                count+= pos-1-(nums.begin()+i);
            }
            if (count<k)
                left=mid+1;
            else
                right=mid;
        }
        
        return left;
    }

public:

	/*
		Intuition and Algorithm

		Sort the points. For every point with index i, the pairs with indexes (i, j) [by order of distance] are (i, i+1), (i, i+2), ..., (i, N-1).

		Let's keep a heap of pairs, initially heap = [(i, i+1) for all i], and ordered by distance (the distance of (i, j) is nums[j] - nums[i].) Whenever we use a pair (i, x) from our heap, we will add (i, x+1) to our heap when appropriate.


		Complexity Analysis

		Time Complexity: O((k+N)logN), where NN is the length of nums. As k = O(N^2) this is O(N^2*logN) in the worst case. 
		The complexity added by our heap operations is either O((k+N)logN) in the Java solution, or O(klogN+N) in the Python solution because the heapq.heapify operation is linear time. 
		Additionally, we add O(NlogN) complexity due to sorting.

		Space Complexity: O(N), the space used to store our heap of at most N-1 elements.
	*/
    int doit_heap(vector<int>& nums, int k) {
        
        std::sort(begin(nums), end(nums));
        int n = nums.size();
        
        priority_queue<std::pair<int, std::pair<int, int>>, vector<std::pair<int, std::pair<int, int>>>, std::greater<>> pq;
        
        for (int i = 0; i < nums.size()-1; i++)
            pq.push({abs(nums[i+1]-nums[i]), {i, i+1}});
        
        int d = 0;
        while (k--) {
            
            auto it = pq.top();
            d = it.first;
            int x = it.second.first, y = it.second.second;
            
            pq.pop();
            if (y+1 != nums.size())
                pq.push({abs(nums[x]-nums[y+1]), {x, y+1}});
        }
                        
        return d;
    }

	/*
		Approach #2: Binary Search + Prefix Sum [Accepted]
		Intuition

		Let's binary search for the answer. It's definitely in the range [0, W], where W = max(nums) - min(nums)].

		Let possible(guess) be true if and only if there are k or more pairs with distance less than or equal to guess. We will focus on evaluating our possible function quickly.

		Algorithm

		Let prefix[v] be the number of points in nums less than or equal to v. Also, let multiplicity[j] be the number of points i with i < j and nums[i] == nums[j]. We can record both of these with a simple linear scan.

		Now, for every point i, the number of points j with i < j and nums[j] - nums[i] <= guess is prefix[x+guess] - prefix[x] + (count[i] - multiplicity[i]), where count[i] is the number of ocurrences of nums[i] in nums. The sum of this over all i is the number of pairs with distance <= guess.

		Finally, because the sum of count[i] - multiplicity[i] is the same as the sum of multiplicity[i], we could just replace that term with multiplicity[i] without affecting the answer. (Actually, the sum of multiplicities in total will be a constant used in the answer, so we could precalculate it if we wanted.)

		In our Java solution, we computed possible = count >= k directly in the binary search instead of using a helper function.

		Complexity Analysis

		Time Complexity: O(W + NlogW + NlogN), where NN is the length of nums, and WW is equal to nums[nums.length - 1] - nums[0]. We do O(W) work to calculate prefix initially. 
		The logW factor comes from our binary search, and we do O(N) work inside our call to possible (or to calculate count in Java). The final O(NlogN) factor comes from sorting.

		Space Complexity: O(N+W), the space used to store multiplicity and prefix.
	*/
	int doit_binary_search_presum(vector<int>& nums, int k) {

        int n = nums.size();
        std::sort(begin(nums), end(nums));
        
        vector<int> multiplicity(n);
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i-1])
                multiplicity[i] = 1 + multiplicity[i-1];
        }
        
        int width = 2 * nums.back();
        vector<int> prefix(width);
        int left = 0;
        for (int i = 0; i < width; i++) {
            while (left < nums.size() && nums[left] == i) left++;
            prefix[i] = left;
        }
        
        int lo = 0, hi = nums.back() - nums[0];
        while (lo < hi) {
            
            int mid = (lo + hi) / 2;
            
            int count = 0;
            
            for (int i = 0; i < nums.size(); i++) {
                count += prefix[nums[i] + mid] - prefix[nums[i]] + multiplicity[i]; 
            }
            
            //
            if (count >= k)
                hi = mid;
            else
                lo = mid + 1;
        }
        
        return lo;
    }

	/*
		Approach #3: Binary Search + Sliding Window [Accepted]
		Intuition
		
		As in Approach #2, let's binary search for the answer, and we will focus on evaluating our possible function quickly.
		
		Algorithm
		
		We will use a sliding window approach to count the number of pairs with distance <= guess.
		
		For every possible right, we maintain the loop invariant: left is the smallest value such that nums[right] - nums[left] <= guess. 
		Then, the number of pairs with right as it's right-most endpoint is right - left, and we add all of these up.

		O(n*log(n))
	*/
	int doit_binary_search_slidingwindow(vector<int>&& nums, int k) {

		sort(nums.begin(), nums.end());
		int lo = 0, hi = nums.back() - nums[0];
		int N = nums.size();

		while (lo < hi) {

			int mid = lo + (hi - lo) / 2;
			int cnt = 0;

			for (int i = 0, j = 0; i < N; i++) {
				while (j < N && nums[j] - nums[i] <= mid)
					j++;
				cnt += j - i - 1;
			}

			if (cnt < k)
				lo = mid + 1;
			else
				hi = mid;
		}

		return lo;
	}

	int doit_binary_search(vector<int>& nums, int k) {
        
        sort(begin(nums), end(nums));
        
        int left = 0, right = nums.back() - nums.front();
        
        auto count = [&](int val) {
            
            int cnt = 0;
            
            for (int i = 0, j = 0; i < nums.size(); i++) {
                
                while (j <= i && nums[i] - nums[j] > val) j++;
                
                cnt += i - j;
                
            }

            return cnt;
        };
        
        while (left < right) {
            
            int mid = left + (right - left) / 2;
            
            if (count(mid) < k)
                left = mid + 1;
            else
                right = mid;
        }
        
        return left;
    }

	/*
	O(n^2)
	*/
	int doit1(vector<int>&& nums, int k) {
		int N = 10000000;
		vector<int> cnt(N, 0);
		int maxv = INT_MIN, minv = INT_MAX;
		for (int i = 0; i < nums.size(); i++) {
			for (int j = i + 1; j < nums.size(); j++) {
				int c = abs(nums[i] - nums[j]);
				cnt[c]++;
				maxv = std::max(maxv, c);
				minv = std::min(minv, c);
			}
		}

		int res = 0;
		for (auto i = minv; i < maxv; i++) {
			res += cnt[i];
			if (res >= k) {
				return i;
			}
		}
		return -1;
	}


};