/*
1788. Maximize the Beauty of the Garden

There is a garden of n flowers, and each flower has an integer beauty value. The flowers are arranged in a line. You are given an integer array flowers of size n and each flowers[i] represents the beauty of the ith flower.

A garden is valid if it meets these conditions:

The garden has at least two flowers.
The first and the last flower of the garden have the same beauty value.
As the appointed gardener, you have the ability to remove any (possibly none) flowers from the garden. 
You want to remove flowers in a way that makes the remaining garden valid. The beauty of the garden is the sum of the beauty of all the remaining flowers.

Return the maximum possible beauty of some valid garden after you have removed any (possibly none) flowers.

 

Example 1:

Input: flowers = [1,2,3,1,2]
Output: 8
Explanation: You can produce the valid garden [2,3,1,2] to have a total beauty of 2 + 3 + 1 + 2 = 8.
Example 2:

Input: flowers = [100,1,1,-3,1]
Output: 3
Explanation: You can produce the valid garden [1,1,1] to have a total beauty of 1 + 1 + 1 = 3.
Example 3:

Input: flowers = [-1,-2,0,-1]
Output: -2
Explanation: You can produce the valid garden [-1,-1] to have a total beauty of -1 + -1 = -2.
 

Constraints:

2 <= flowers.length <= 105
-104 <= flowers[i] <= 104
It is possible to create a valid garden by removing some (possibly none) flowers.

*/

#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class MaximizeBeautyOfTheGarden {

    /*
        1788.Maximize-the-Beauty-of-the-Garden
        显然，我们会用hash表来记录每种花的所有位置。比如，令某种花的第一个位置a和最后一个位置b作为两端，那么我们就只能保留区间[a:b]里的花。

        那么本题是否就只是求一个区间和那么简单呢？其实不然，因为本题中的元素值可以是负数。显然[a+1:b-1]这个范围内的所有负数元素都是不合算的，我们也应当将其移除。特别注意，如果a和b两处的花也是负数，我们却不能移除，因为我们约定要以该花为两端。
        所以这种方案的总价值是：[a+1:b-1]区间内的所有非负数之和，再加上a和b两处的元素。

        如何求一个区间内的所有非负数之和呢？我们依然还是会用到前缀和的思想，但是处理的技巧是，在累加前缀和的时候，我们将所有的负数都变成0来处理。这样，用两处前缀和之差来计算区间和的时候，自动就忽略了所有的负数元素。
    */
    int maximumBeauty(vector<int>& flowers) 
    {
        unordered_map<int,vector<int>>Map;
        for (int i=0; i<flowers.size(); i++)
        {
            Map[flowers[i]].push_back(i);
        }
        
        int n = flowers.size();
        vector<int>presum(n);
        int sum = 0;
        for (int i=0; i<n; i++) {
            sum += (flowers[i]<0? 0:flowers[i]);
            presum[i] = sum;
        }
        
        int ret = INT_MIN;
        for (auto x: Map)
        {
            if (x.second.size()==1) continue;
            int beauty = x.first;            
            int a = x.second[0]+1, b = x.second.back()-1;            
            ret = std::max(ret, presum[b] - (a==0?0:presum[a-1]) + 2*beauty);
        }
        return ret;        
    }

public:

    int doit_greedy(vector<int>& flowers) {
        
        int n = flowers.size();
        unordered_map<int, std::pair<int, int>> pos;
        vector<int> presums(n+1, 0);
            
        for (int i = 0; i < flowers.size(); i++) {
            
            presums[i+1] = presums[i] + std::max(0, flowers[i]);
        
            if (pos.count(flowers[i]) == 0) {
                pos[flowers[i]] = {i, i};
            } else {
                pos[flowers[i]].second = i;
            }
        }

        int res = INT_MIN;
        for (auto it: pos) {
            auto [s, e] = it.second;
            if (s == e) continue;
            res = std::max(res, presums[e] - presums[s+1] + 2 * it.first);            
        }
        
        return res;
    }
}