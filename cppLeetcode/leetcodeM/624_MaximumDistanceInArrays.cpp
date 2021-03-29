/*
624. Maximum Distance in Arrays


You are given m arrays, where each array is sorted in ascending order.

You can pick up two integers from two different arrays (each array picks one) and calculate the distance. We define the distance between two integers a and b to be their absolute difference |a - b|.

Return the maximum distance.

 

Example 1:

Input: arrays = [[1,2,3],[4,5],[1,2,3]]
Output: 4
Explanation: One way to reach the maximum distance 4 is to pick 1 in the first or third array and pick 5 in the second array.
Example 2:

Input: arrays = [[1],[1]]
Output: 0
Example 3:

Input: arrays = [[1],[2]]
Output: 1
Example 4:

Input: arrays = [[1,4],[0,5]]
Output: 4
 

Constraints:

m == arrays.length
2 <= m <= 105
1 <= arrays[i].length <= 500
-104 <= arrays[i][j] <= 104
arrays[i] is sorted in ascending order.
There will be at most 105 integers in all the arrays.

*/
#include <map>
#include <vector>
#include <algorithm>

using std::vector;
using std::multimap;

class MaxDistance {

    /*
        624.Maximum-Distance-in-Arrays
        最粗浅的最优策略就是，把每个数组的第一个元素挑出来组成Mins数组，每个数组的最后一个元素挑出来组成Maxs数组。理想情况下，Maxs.back()-Mins[0]就是最大的一对差值。

        当Maxs.back()和Mins[0]来自同一个数组怎么办？这时候考察Maxs[n-2]-Mins[0]以及Maxs.back()-Mins[1]，取其中较小的。而且这两对数字肯定不会是在同一个数组中的。
    */
    int maxDistance(vector<vector<int>>& arrays) 
    {
        vector<int>Mins;
        vector<int>Maxs;
        for (int i=0; i<arrays.size(); i++)
        {
            Mins.push_back(arrays[i][0]);
            Maxs.push_back(arrays[i].back());
        }
        
        std::sort(Mins.begin(),Mins.end());
        std::sort(Maxs.begin(),Maxs.end());
        
        int N=arrays.size();
        int flag=0;
        for (int i=0; i<arrays.size(); i++)
        {
            if (arrays[i][0]==Mins[0] && arrays[i].back()==Maxs.back() )
            {
                flag=1;
                break;                    
            }            
        }
        
        if (flag==0)
            return Maxs.back()-Mins[0];
        else
            return std::max(Maxs.back()-Mins[1],Maxs[N-2]-Mins[0]);
    }

public:
    
    int doit_greedy(vector<vector<int>>& arrays) {
        
        multimap<int, int> maximums, minimums;
        
        for (int i = 0; i < arrays.size(); i++) {
            maximums.emplace(arrays[i].back(), i);
            minimums.emplace(arrays[i].front(), i);
        }
        
        if (maximums.rbegin()->second != minimums.begin()->second) {
            return maximums.rbegin()->first - minimums.begin()->first;
        } else {
         
            return std::max(next(rbegin(maximums))->first - begin(minimums)->first, rbegin(maximums)->first - next(begin(minimums))->first); 
        }
    }
};