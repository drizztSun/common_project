/*
327. Count of Range Sum

Given an integer array nums and two integers lower and upper, return the number of range sums that lie in [lower, upper] inclusive.

Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j inclusive, where i <= j.

 

Example 1:

Input: nums = [-2,5,-1], lower = -2, upper = 2
Output: 3
Explanation: The three ranges are: [0,0], [2,2], and [0,2] and their respective sums are: -2, -1, 2.
Example 2:

Input: nums = [0], lower = 0, upper = 0
Output: 1
 

Constraints:

1 <= nums.length <= 104
-231 <= nums[i] <= 231 - 1
-3 * 104 <= lower <= upper <= 3 * 104
 

Follow up: A naive algorithm of O(n2) is trivial, Could you do better than that?

*/
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <unordered_map>

using std::map;
using std::unordered_map;
using std::map;
using std::vector;

class CountRangeSum {

	/*
		327.Count-of-Range-Sum
		此题初看，立刻想到用累加和数组sums。任意某段区间(i,j)的和，等于sums[j]-sums[i-1]。不过即使这样，这道题仍需要o(n^2)的时间复杂度，因为要分别在sums中遍历符合要求的i,j两个元素。

		不过，这道题如果这样思考：确定了首元素i的位置，那么就需要在首元素之后在sums寻找一个尾元素j.如果i之后的sums数组已经是有序的，那么j元素就可以通过二分法o(log(n))的时间复杂度完成寻找。要想做到i之后的元素有序，那么分治/归并排序的组合套路就呼之欲出。
		
		这和 315.Count of Smaller Numbers After Self 是一个思路。

		我在分析315的时候介绍过：分治法的最常见的应用就是与归并排序相结合。将数组对半划分为左右两部分，两部分各自排序，然后将两部分整体归并，在归并的过程中就可以解决一些问题（利用一侧或者两个序列是有序的这个性质）。

		对于本题：在每一轮，序列start~end对半分为两部分，左序列区间从start到mid，右序列区间从mid+1到end。两个部分各自递归调用分治排序的函数后，都变得有序。此时，对于左序列的任意nums[i]，都可以轻易在有序的右序列中用lower_bound找到sums[i]+lower和sums[i]+upper的位置（或者亲自写二分查找的代码），这两者之间的元素都是符合要求的，将其数目加入总和中。

		本题的另一个训练点就是对C++的STL里lower_bound的考察。如何写自定义比较函数是关键。我们需要在右序列中找到下限的位置，希望找到的位置在原序列中是大于等于sums[i]+lower的，所以自定义函数里要写a<b。另一方面，我们需要在右序列中找到上限的位置，希望找到的位置在原序列中是大于sums[i]+upper的，所以自定义函数里要写a<=b。最终pos2-pos1表示原序列里处于[sums[i]+lower,sums[i]+upper]闭区间的个数。		
	*/
	int result;
    long temp[10001];

    int countRangeSum(vector<int>& A, int lower, int upper) 
    {
        int n = A.size();
        vector<long>nums(n+1);
        for (int i=0; i<n; i++)
            nums[i+1] = nums[i]+A[i];

		std::function<void(int, int, int, int)> DivideConque = [&](int a, int b, int lower, int upper)
		{
			if (a>=b)  return;
			int mid = a+(b-a)/2;
			DivideConque(a,mid,lower,upper);
			DivideConque(mid+1,b,lower,upper);
			
			for (int i=a; i<=mid; i++)
			{
				auto p1 = lower_bound(nums.begin()+mid+1,nums.begin()+b+1,nums[i]+lower);
				auto p2 = upper_bound(nums.begin()+mid+1,nums.begin()+b+1,nums[i]+upper);
				result+=p2-p1;            
			}
			
			int i=a, j=mid+1, p = 0;        
			while (i<=mid && j<=b)
			{
				if (nums[i]<=nums[j])
				{
					temp[p] = nums[i];
					i++;
				}                
				else
				{
					temp[p] = nums[j];
					j++;
				} 
				p++;
			}
			while (i<=mid)
			{
				temp[p] = nums[i];
				i++;
				p++;
			}
			while (j<=b)
			{
				temp[p] = nums[j];
				j++;
				p++;
			}
			for (int i=0; i<b-a+1; i++)
				nums[a+i] = temp[i];
		};

        DivideConque(0,n,lower,upper);
        return result;
    }


	// O(n^2)
	int doit_bruteforce(vector<int>& nums, int lower, int upper) {
        int ans = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            long long total = 0;
            for (int j = i; j < nums.size(); j++) {
                total += nums[j];       
                if (total >= lower && total <= upper) ans++;
            }
        }   
        return ans;
    }
    
	// better, O(n*logn) => O(n^2)
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        
        int n = nums.size();
        map<long long, long long> buf;
        buf.emplace(0, 1);
        long long total = 0, ans = 0;
        
        for (int i = 0; i < n; i++) {
            
            total += nums[i];
            
            for (int j = lower; j <= upper; j++) {
                ans += buf[total - j];
            }
            
            buf[total]++;
        }
        
        return ans;
    }

	// better O(n*k) k is range of (lower, upper)
	int doit_hashtable(vector<int>& nums, int lower, int upper) {
        
        int n = nums.size();
        unordered_map<long long, long long> buf;
        buf.emplace(0, 1);
        long long total = 0, ans = 0;
        
        for (int i = 0; i < n; i++) {
            
            total += nums[i];
            
            for (int j = lower; j <= upper; j++) {
                ans += buf[total - j];
            }
            
            buf[total]++;
        }
        
        return ans;
    }

public:

	int countSum(std::vector<int>&& nums, int lower, int upper) {

		std::vector<int> sums;
		sums.push_back(0);

		for (auto i : nums) {
			sums.push_back(sums.back() + i);
		}

		return search(sums, 0, sums.size(), lower, upper);
	}

	int search(std::vector<int>& sums, int start, int end, int lower, int upper) {

		int mid = (start + end) / 2;
		if (mid == start)
			return 0;

		int count = search(sums, start, mid, lower, upper) + search(sums, mid, end, lower, upper);
		int i = mid, j = mid;

		for (auto left = start; left < mid; left++) {

			while (i < end && sums[i] - sums[left] < lower)
				i++;
			while (j < end && sums[j] - sums[left] <= upper)
				j++;

			count += j - i;
		}
		
		std::sort(sums.begin() + start, sums.begin() + end);

		return count;
	}

	int mergeSort(std::vector<long>& sum, int lower, int upper, int low, int high)
	{
		if (high - low <= 1) return 0;
		int mid = (low + high) / 2, m = mid, n = mid, count = 0;
		count = mergeSort(sum, lower, upper, low, mid) + mergeSort(sum, lower, upper, mid, high);
		for (int i = low; i< mid; i++)
		{
			while (m < high && sum[m] - sum[i] < lower) m++;
			while (n < high && sum[n] - sum[i] <= upper) n++;
			count += n - m;
		}
		inplace_merge(sum.begin() + low, sum.begin() + mid, sum.begin() + high);
		return count;
	}

	int countRangeSum(std::vector<int>& nums, int lower, int upper) {
		int len = nums.size();
		std::vector<long> sum(len + 1, 0);
		for (int i = 0; i< len; i++) sum[i + 1] = sum[i] + nums[i];
		return mergeSort(sum, lower, upper, 0, len + 1);
	}
};