/*

128. Longest Consecutive Sequence

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.

*/

#include <stdlib.h>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

using namespace std;

class LongestConsecutiveSequence {

	/*
		128.Longest-Consecutive-Sequence
		解法１：　Union Find
		遍历nums，每读入一个数a，分别查看a+1和a-1是否已经收录。是的话就对这两个数尝试进行Union。

		最后用一个哈希表unordered_map<int,unordered_set>Map，把所有具有相同Father的数都收集在一个集合里。查看每个集合，找出元素最多的那个。

		解法2：　Set
		此题更加简洁，巧妙和高效的算法是如下．

		将所有的元素放入一个集合中．然后我们再遍历一下这个数组nums[i]，如果nums[i]-1不在这个集合中，说明nums[i]可能是一个连续序列的下限，那么我们就从这个下限顺着递增去查验，找到一个完整的递增序列．
		如果nums[i]-1在这个集合中，说明它有更小的下限，那么我们就不去查验这个递增序列，因为我们规定，只有遇到了下限才会去查验整个序列．于是遍历完整个数组后，对于集合的查验也就仅仅是o(n)次．
	*/
	unordered_map<int,int>Father;
    int longestConsecutive_disjoint(vector<int>& nums) 
	{
        if (nums.size()==0) return 0;

		for (int i=0; i<nums.size(); i++)
		{
			Father[nums[i]]=nums[i];
			if (Father.find(nums[i]-1)!=Father.end() && FindSet(nums[i]-1)!=FindSet(nums[i]))			
				Union(nums[i]-1,nums[i]);						
			if (Father.find(nums[i]+1)!=Father.end() && FindSet(nums[i]+1)!=FindSet(nums[i]))
				Union(nums[i]+1,nums[i]);			
		}
        
   		for (int i=0; i<nums.size(); i++)
        {
            Father[nums[i]]=FindSet(nums[i]);
        }
        
		unordered_map<int,unordered_set<int>>Map;
		for (auto a:Father)
			Map[a.second].insert(a.first);
		
		int result=0;
		for (auto a:Map)
		{
			int n=a.second.size();
            result=max(result,n);
		}
		return result;
    }

	int FindSet(int x)
	{
		if (Father[x]!=x)
			Father[x]=FindSet(Father[x]);
		return Father[x];
	}

	void Union(int x, int y)
	{
		x=Father[x];
		y=Father[y];
		if (x<=y)
			Father[y]=x;
		else
			Father[x]=y;
	}

	int longestConsecutive_hashtable(vector<int>& nums) 
    {
        unordered_set<int>Set;
        for (auto a:nums)
            Set.insert(a);
        
        int result = 0;
        for (int i=0; i<nums.size(); i++)
        {
            if (Set.find(nums[i]-1)!=Set.end())
                continue;
            int j = nums[i]+1;
            while (Set.find(j)!=Set.end())
                j++;
            
            result = max(result, j-nums[i]);
        }
        return result;
    }

public:

	int doit_hashtable_best(vector<int>& nums) {
		
		std::unordered_set<int>  recorder(nums.begin(), nums.end());
		int best = 0;

		for (auto c : recorder) {
			
			if (recorder.find(c - 1) == recorder.end()) {
				int s = c + 1;
				while (recorder.find(s) != recorder.end())
					s += 1;
				best = std::max(best, s - c);
			}
		}
			
		return best;
	}

	int doit_sweepline(vector<int>& nums) {

		unordered_map<int, int> keep;

		for (auto w : nums) {

			if (keep[w])
				continue;

			keep[w] = 1;
			int tmp_l = keep[w - 1];
			int tmp_r = keep[w + 1];

			keep[w + tmp_r] = keep[w - tmp_l] = 1 + tmp_l + tmp_r;
		}

		int res = 0;
		for (auto& c : keep) {
			res = std::max(res, c.second);
		}

		return res;
	}

	int doit_sort(vector<int>& nums) {
		
		sort(nums.begin(), nums.end());

		int max_sum = 0;
		int sum = 0;

		if (nums.size() <= 1) return nums.size();

		sum = 1;
		
		for (size_t i = 1; i < nums.size(); i++)
		{
			if ((nums[i] - nums[i - 1]) == 1 || (nums[i] - nums[i - 1]) == 0)
			{
				if ((nums[i] - nums[i - 1]) == 1)
					sum++;
			}
			else
			{
				max_sum = max(max_sum, sum);
				sum = 1;
			}
		}

		return max(max_sum, sum);
	}

	int doit2(vector<int>& nums) {

		if (nums.size() == 0)
			return 0;
		
		std::unordered_set<int> record(nums.begin(), nums.end());
		int best = 1;

		for (int c : nums) {

			if (record.find(c) == record.end())
				continue;

			record.erase(c);

			int prev = c - 1, next = c + 1;

			while (record.find(prev) != record.end()) 
				record.erase(prev--);
			
			while (record.find(next) != record.end())
				record.erase(next++);

			best = std::max(best, next - prev - 1);
		}

		return best;
	}

};
