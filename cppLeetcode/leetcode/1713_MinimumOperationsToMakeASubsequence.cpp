/*

1713. Minimum Operations to Make a Subsequence

You are given an array target that consists of distinct integers and another integer array arr that can have duplicates.

In one operation, you can insert any integer at any position in arr. For example, if arr = [1,4,1,2], you can add 3 in the middle and make it [1,4,3,1,2]. Note that you can insert the integer at the very beginning or end of the array.

Return the minimum number of operations needed to make target a subsequence of arr.

A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order. 
For example, [2,7,4] is a subsequence of [4,2,3,7,2,1,4] (the underlined elements), while [2,4,2] is not.

 

Example 1:

Input: target = [5,1,3], arr = [9,4,2,3,4]
Output: 2
Explanation: You can add 5 and 1 in such a way that makes arr = [5,9,4,1,2,3,4], then target will be a subsequence of arr.
Example 2:

Input: target = [6,4,8,1,3,2], arr = [4,7,6,2,3,8,6,1]
Output: 3
 

Constraints:

1 <= target.length, arr.length <= 105
1 <= target[i], arr[i] <= 109
target contains no duplicates.


*/
#include <vector>
#include <unordered_map>
#include <numeric>

using std::unordered_map;
using std::vector;


class MinimumOperationsToMakeSubsequence {

public:

    /*
    1713.Minimum-Operations-to-Make-a-Subsequence
    首先我们的目标是希望尽量多地在arr里面用到target已经存在的元素，并且这些元素在两个数组中都是subsequence（出现的先后顺序相同）。于是我们立刻就感觉本质就是求两个数组的longest common subsequence。这段LCS是arr所能利用的最大信息量，剩下的必须靠额外的插入了。

    传统的LCS的DP算法需要o(MN)，这已经是最优的算法了，但在这里会超时，为什么呢？我们注意到题目中强调了target的每个元素是unique的。这个条件很不寻常。此时我们如果把target的元素抽象成[a,b,c,d,e...]，一切就柳暗花明了。
    我们其实需要在arr中找的就是尽量长的递增字母序列！这就是longest increasing subsequence的问题，可以用o(NlogN)的复杂度来解决。

    所以此题的算法是，将target里面的所有元素顺次映射成1,2,3...，然后将target在arr里面的元素也都替换成对应的1,2,3...其他没有在target里出现的数字都忽略。于是我们可以计算target和arr的LIS。最终的答案就是target的长度减去LIS的长度。

    It seems problem for LCS (longest common subsequence), like [5, 1, 3], [9, 4, 2, 3, 4]. LCS is [3], so we have to add [5, 1]
    
        That will be: target=[X X a X b c] arr=[X a b X c X]. 
        Complexity: O(MN)
        dp[i][j]: LCS A[:i], B[:j]
        if A[i] == B[j]:
            dp[i][j] = dp[i-1][j-1] + 1
        else:
            dp[i][j] = max(dp[i-1][j], dp[i][j-1])

        But length is 10^5, only O(n*log(n)) can make it work.

        O(n*log(n))
    */
    int doit_dp(vector<int>& target, vector<int>& arr) 
    {
        unordered_map<int,int>Map;
        for (int i=0; i<target.size(); i++)
            Map[target[i]] = i;
        
        vector<int>q;
        for (int i=0; i<arr.size(); i++)
        {
            if (Map.find(arr[i])==Map.end())
                continue;
            int x = Map[arr[i]];
            if (q.empty() || q.back() < x)
                q.push_back(x);
            else
            {
                auto iter = lower_bound(q.begin(), q.end(), x);
                *iter = x;
            }
        }
        return target.size() - q.size();        
    }

    int doit_dp_LIS(vector<int>& target, vector<int>& arr) {

        unordered_map<int, int> map;
        for(int i = 0; i < target.size(); i++) {
            map[target[i]] = i;
        }

        vector<int> mapping_res;
        for(auto c: arr) {
            if (map.find(c) != map.end()) {
                mapping_res.push_back(map[c]);
            }
        }

        vector<int> LIS;
        for (auto c : mapping_res) {
            if (LIS.empty() || LIS.back() < c) {
                LIS.push_back(c);
                continue;
            }
            auto it = lower_bound(begin(LIS), end(LIS), c);
            *it = c;
        }

        return target.size() - LIS.size();
    }
};

