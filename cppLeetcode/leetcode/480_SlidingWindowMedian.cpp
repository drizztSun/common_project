/*
480. Sliding Window Median

Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

Examples:
[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. 
Each time the sliding window moves right by one position. Your job is to output the median array for each window in the original array.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Median
---------------               -----
[1  3  -1] -3  5  3  6  7       1
 1 [3  -1  -3] 5  3  6  7       -1
 1  3 [-1  -3  5] 3  6  7       -1
 1  3  -1 [-3  5  3] 6  7       3
 1  3  -1  -3 [5  3  6] 7       5
 1  3  -1  -3  5 [3  6  7]      6
Therefore, return the median sliding window as [1,-1,-1,3,5,6].

Note:
You may assume k is always valid, ie: k is always smaller than input array's size for non-empty array.
Answers within 10^-5 of the actual value will be accepted as correct.
*/
#include <stdlib.h>
#include <vector>
#include <set>
#include <queue>
#include <unordered_map>

using namespace std;

class MedianSlidingWindow {

public:

	vector<double> doit_best(vector<int>& nums, int k) {

		vector<double> medians;
		multiset<int> window(nums.begin(), nums.begin() + k);
		auto median = next(window.begin(), k/2);

		for (auto i = k; i <= nums.size(); i++) {

			medians.push_back( (double(*median) + *prev(median, 1 - k%2)) / 2);

			if (i == nums.size())
				break;

			window.insert(nums[i]);

			// Brilliant solution.
			// Just a simple note : "in C++11, newly inserted elements follow their equivalents
			// already in the container."
			// Thus, when nums[i] == *mid, we do not need to decrease mid, since nums[i] will inserted after mid.

			// c++11 same value will be inserted after existing ones
			// mid always points to the leftmost one of them
		
			// StefanPochmann 21814  Jan 11, 2017, 6:14 PMLink CopiedShare
			//	@singku Like I said, I just keep it pointing to �index� k / 2. So when I insert something before it(i.e., something smaller),
			//	my pointer then points at �index� k / 2 + 1 and I�ll have to subtract 1 to fix that.Similar for erasing.
			//	And no, there won�t be an error, because I increase the iterator before erasing, which avoids erasing the element my iterator points to.
			if (nums[i] < *median)
				median--;

			if (nums[i - k] <= *median)
				median++;

			window.erase(window.lower_bound(nums[i - k]));
		}
        return medians;
	}

	vector<double> doit_heap(vector<int>& nums, int k) {

		vector<double> medians;
		multiset<int> window(nums.begin(), nums.begin() + k);
		auto mid = next(window.begin(), k / 2);

		for (auto i = k; i <= nums.size(); i++) {
			medians.push_back( (double(*mid) + *prev(mid, 1 - k % 2)) / 2);
			if (i == nums.size())
				break;

			window.erase(window.lower_bound(nums[i - k]));
			window.insert(nums[i]);
			mid = next(window.begin(), k / 2);
		}

		return medians;
	}

	/*
		480.Sliding-Window-Median
		希望能够自动排序的容器，首选set或者multiset。对于这类非线性的容器，不能用+k或-k来实现迭代器的移动，必须用for循环不断++/--，或者使用next或prev。例如

		set<int>::iterator pos = next(Set.begin(),k); //从Set.begin()开始后移k个
		set<int>::iterator pos = prev(Set.end(),k);  //从Set.end()开始前移k个
		本题里设置一个multiset，初始化时用next命令把pos定位到最中间（Set容量为奇数）、或者中间靠右（Set容量为偶数）的那个迭代器。

		每次一进一出的操作如下。对于k奇偶性通用的代码比较难理解，那就索性分别讨论容易理清思路。

				for (int i=k; i<=nums.size(); i++)
				{
					if (k%2==1) results.push_back(*pos);
					else results.push_back(*pos/2.0+*prev(pos,1)/2.0);
					
					if (i==nums.size()) break;
					
					Set.insert(nums[i]);
					
					if (k%2==1)   // 当k为奇数时，Set内的排列为 OXO，X为pos指针
					{
						if (nums[i]>=*pos)
							pos++;
										
						// 加入一个元素后，此时阵型为 OOXO
						if (nums[i-k]>*pos)
							pos--;
						else if (nums[i-k]<*pos)
							;
						else if (nums[i-k]==*pos && *prev(pos,1)!=*pos)  
							// 如果X左边是个重复元素，则无需改动；如果X左边不是重复元素，则X会被删除，指针需左移
							pos--;                
					}
					else    // 当k为偶数时，Set内的排列为 OOXO，X为pos指针
					{
						if (nums[i]<*pos)
							pos--;
						
						// 加入一个元素后，此时阵型为 OOXOO
						if (nums[i-k]<*pos)
							pos++;
						else if (nums[i-k]>*pos)
							;
						else if (nums[i-k]==*pos)
							// 如果X左边是个重复元素，则会删除那个O；如果X左边不是重复元素，则会删除X。两种情况下指针都需右移
							pos++;
					}
					
					Set.erase(Set.lower_bound(nums[i-k]));     
				}

		每次内循环之后，pos的定义不变（最中间或者最中间靠右的迭代器。
	*/
	vector<double> doit_heap_1(vector<int>& nums, int k) 
    {
        multiset<int>Set;
        for (int i=0; i<k; i++)        
            Set.insert(nums[i]);
        
        auto pos=Set.begin();
        for (int i=0; i<k/2; i++)
            pos=next(pos,1);
        
        vector<double>results;
        
        for (int i=k; i<=nums.size(); i++)
        {
            if (k%2==1)
                results.push_back(*pos);
            else
                results.push_back(*pos/2.0+*prev(pos,1)/2.0);
            
            if (i==nums.size()) break;
            
            Set.insert(nums[i]);
            
            if (k%2==1)   // OXO
            {
                if (nums[i]>=*pos)
                    pos++;
                                
                // OOXO
                if (nums[i-k]>*pos)
                    pos--;
                else if (nums[i-k]<*pos)
                    ;
                else if (nums[i-k]==*pos && *prev(pos,1)!=*pos)  
                    // 如果X左边是个重复元素，则无需改动；如果X左边不是重复元素，则X会被删除，指针需左移
                    pos--;
            }
            else    // OOXO
            {
                if (nums[i]<*pos)
                    pos--;
                
                // OOXOO
                if (nums[i-k]<*pos)
                    pos++;
                else if (nums[i-k]>*pos)
                    ;
                else if (nums[i-k]==*pos)
                    // 如果X左边是个重复元素，则会删除那个O；如果X左边不是重复元素，则会删除X。两种情况下指针都需右移
                    pos++;
            }
            
            Set.erase(Set.lower_bound(nums[i-k]));     
        }
        
        return results;
    }

	vector<double> doit_2(vector<int>& nums, int k) {

		priority_queue<int> low;
		priority_queue<int, vector<int>, std::greater<>> high; 

		for (int i = 0; i < k; i++) {
			high.push(nums[i]);
		}
        
        while (high.size() - low.size() > 1) {
            low.push(high.top()); 
            high.pop();
        }

		vector<double> ans;
		ans.push_back( k % 2 == 1 ? static_cast<double>(high.top()): (static_cast<double>(high.top()) + static_cast<double>(low.top())) / 2.0);

		unordered_map<int, int> removedlist;

		for (int i = k; i < nums.size(); i++) {
			high.push(nums[i]);
			low.push(high.top()); high.pop();

			int old = nums[i-k];

			if (old > low.top()) {
				high.push(low.top()); 
                low.pop();
            }

			removedlist[old]++;

			while (!low.empty() && removedlist[low.top()]) {
				removedlist[low.top()]--;
				low.pop();
			} 

			while (!high.empty() && removedlist[high.top()]) {
				removedlist[high.top()]--;
				high.pop();
			}

			ans.push_back( k % 2 == 1 ? static_cast<double>(high.top()): (static_cast<double>(high.top()) + static_cast<double>(low.top())) / 2.0);
		}

		return ans;
    }

	vector<double> doit2(vector<int>& nums, int k) {

		int size = nums.size(), median_pos = k - k / 2 - 1;
		vector<double> res(size - k + 1);
		multiset<int> s(nums.begin(), nums.begin() + k);
		auto it = next(s.begin(), median_pos);

		for (auto i = k; i <= size; ++i)
		{
			res[i - k] = ((double)*it + (k % 2 != 0 ? *it : *next(it))) / 2;
			if (i < size)
			{
				// magic numbers (instead of enum) for brevity. INT_MAX means to retrace the iterator from the beginning.
				int repos_it = INT_MAX;
				if (k > 2)
				{
					// if inserted or removed item equals to the current median, we need to retrace.
					// we do not know which exact element will be removed/inserted, and we cannot compare multiset iterators.
					// otherwise, we can keep or increment/decrement the current median iterator.
					if ((nums[i - k] < *it && nums[i] < *it) || (nums[i - k] > *it && nums[i] > *it)) repos_it = 0;
					else if (nums[i - k] < *it && nums[i] > *it) repos_it = 1; // advance forward.
					else if (nums[i - k] > *it && nums[i] < *it) repos_it = -1; // advance backward.
				}
				s.insert(nums[i]);
				s.erase(s.find(nums[i - k]));

				if (repos_it == INT_MAX) it = next(s.begin(), median_pos);
				else if (repos_it == 1) ++it;
				else if (repos_it == -1) --it;
			}
		}
		return res;
	}
};