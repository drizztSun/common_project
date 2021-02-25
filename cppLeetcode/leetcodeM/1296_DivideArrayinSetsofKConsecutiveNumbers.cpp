/*
1296. Divide Array in Sets of K Consecutive Numbers

Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into sets of k consecutive numbers
Return True if it is possible. Otherwise, return False.

 

Example 1:

Input: nums = [1,2,3,3,4,4,5,6], k = 4
Output: true
Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].
Example 2:

Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
Output: true
Explanation: Array can be divided into [1,2,3] , [2,3,4] , [3,4,5] and [9,10,11].
Example 3:

Input: nums = [3,3,2,2,1,1], k = 3
Output: true
Example 4:

Input: nums = [1,2,3,4], k = 3
Output: false
Explanation: Each array should be divided in subarrays of size 3.
 

Constraints:

1 <= k <= nums.length <= 105
1 <= nums[i] <= 109
 

Note: This question is the same as 846: https://leetcode.com/problems/hand-of-straights/

*/
#include <vector>
#include <string>
#include <unordered_map> 
#include <map>
#include <queue>
#include <set>

using std::multiset;
using std::queue;
using std::map;
using std::vector;
using std::unordered_map;
using std::string;


class PossibleDivide {

public:



    bool doit_best(vector<int>& nums, int k) {
    
        if(!nums.size()) return true;
        
        sort(nums.begin(),nums.end());
        int sum=0,prev=nums[0],last=nums[0]-1,running_sum=1;
        unordered_map<int,int> mp;
        
        for(int i=1;i<nums.size();i++)
        {
            if(nums[i]==prev)
            {
                running_sum++;
            }
            else
            {
                if(sum>0&&prev!=last+1)
                    return false;
                if(running_sum>sum)
                {
                    mp[prev+k-1]=-(running_sum-sum);
                    sum=running_sum;
                }
                else if(sum>running_sum)
                    return false;
                running_sum=1;
                if(mp.find(prev)!=mp.end())
                {
                    sum+=mp[prev];
                    mp.erase(prev);
                }
                last=prev;
                prev=nums[i];
            }
        }
        
        return mp.size()==1&&sum==running_sum&&mp.find(prev)!=mp.end()&&prev==last+1;
        
    }

    /*
        Intuition
        Exactly same as 846. Hand of Straights


        Solution 1
        Count number of different cards to a map c
        Loop from the smallest card number.
        Everytime we meet a new card i, we cut off i - i + k - 1 from the counter.

        Complexity:
        Time O(MlogM + MK), where M is the number of different cards.
        In Cpp and Java it's O(NlogM), which can also be improved.
    */
    bool doit_heap(vector<int> A, int k) {
        map<int, int> c;
        for (int i : A) c[i]++;
        for (auto it : c)
            if (c[it.first] > 0)
                for (int i = k - 1; i >= 0; --i)
                    if ((c[it.first + i] -= c[it.first]) < 0)
                        return false;
        return true;
    }

    /*
        Follow Up
        We just got lucky AC solution. Because k <= 10000.
        What if k is huge, should we cut off card on by one?


        Solution 2
        Count number of different cards to a map c
        Cur represent current open straight groups.
        In a deque start, we record the number of opened a straight group.
        Loop from the smallest card number.
        For example, A = [1,2,3,2,3,4], k = 3
        We meet one 1:
        opened = 0, we open a new straight groups starting at 1, push (1,1) to start.
        We meet two 2:
        opened = 1, we need open another straight groups starting at 1, push (2,1) to start.
        We meet two 3:
        opened = 2, it match current opened groups.
        We open one group at 1, now we close it. opened = opened - 1 = 1
        We meet one 4:
        opened = 1, it match current opened groups.
        We open one group at 2, now we close it. opened = opened - 1 = 0

        return if no more open groups.

        Complexity
        O(N+MlogM), where M is the number of different cards.
        Because I count and sort cards.
        In Cpp and Java it's O(NlogM), which can also be improved.

    */
    bool doit_heap(vector<int> A, int k) {
        map<int, int> c;
        for (int i : A) c[i]++;
        queue<int> start;
        int last_checked = -1, opened = 0;

        for (auto it : c) {
            int i = it.first;
            if (opened > 0 && i > last_checked + 1 || opened > c[i]) return false;
            
            start.push(c[i] - opened);
            last_checked = i, opened = c[i];
            
            if (start.size() == k) {
                opened -= start.front();
                start.pop();
            }
        }
        return opened == 0;
    }


    /*
        1296.Divide-Array-in-Sets-of-K-Consecutive-Numbers
        
        假设这个数组的元素满足条件，那么对于全局最小的元素a而言，它必然也是某个连续k序列的最小元素，即 a, a+1, a+2, ... a+k-1 这k个数必须都要在数组中存在。
        
        所以我们将这k个元素拿走之后，可以重复之前的操作：即此时全局最小元素a，
        
        必然也是某个连续k序列的最小元素，我们再将它们拿走...直至全部元素都归类完毕。如果某次删除k序列的操作不能恰好完成，那么就返回false。

        为了方便“删除”操作，C++我们选择multiset这个数据结构，它可以盛装重复的元素，同时是自动保持有序的。每次的全局最小元素可以直接从Set.begin()里面读就行。
    */
    bool doit_heap_1(vector<int>& nums, int k) {

        multiset<int> Set(nums.begin(),nums.end());
        
        while (Set.size()>0)
        {
            int a = *(Set.begin());
            for (int i=0; i<k; i++)
            {
                if (Set.find(a+i) == Set.end())
                    return false;

                Set.erase(Set.lower_bound(a+i));
            }            
        }
        return true;
    }
};