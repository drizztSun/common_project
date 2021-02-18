/*
1674.Minimum-Moves-to-Make-Array-Complementary

You are given an integer array nums of even length n and an integer limit. In one move, you can replace any integer from nums with another integer between 1 and limit, inclusive.

The array nums is complementary if for all indices i (0-indexed), nums[i] + nums[n - 1 - i] equals the same number. For example, the array [1,2,3,4] is complementary because for all indices i, nums[i] + nums[n - 1 - i] = 5.

Return the minimum number of moves required to make nums complementary.

 

Example 1:

Input: nums = [1,2,4,3], limit = 4
Output: 1
Explanation: In 1 move, you can change nums to [1,2,2,3] (underlined elements are changed).
nums[0] + nums[3] = 1 + 3 = 4.
nums[1] + nums[2] = 2 + 2 = 4.
nums[2] + nums[1] = 2 + 2 = 4.
nums[3] + nums[0] = 3 + 1 = 4.
Therefore, nums[i] + nums[n-1-i] = 4 for every i, so nums is complementary.
Example 2:

Input: nums = [1,2,2,1], limit = 2
Output: 2
Explanation: In 2 moves, you can change nums to [2,2,2,2]. You cannot change any number to 3 since 3 > limit.
Example 3:

Input: nums = [1,2,1,2], limit = 2
Output: 0
Explanation: nums is already complementary.
 

Constraints:

n == nums.length
2 <= n <= 105
1 <= nums[i] <= limit <= 105
n is even.
*/

#include <vector>
#include <map>
#include <set>

using std::multiset;
using std::map;
using std::vector;


class MinimumMovesMakeArrayComplementary {


    /*
        1674.Minimum-Moves-to-Make-Array-Complementary
        我们任意挑出一对数nums[i]和nums[n-1-i]，将其中较小的数记做a，较大的数记做b。

        如果我们不做任何操作，它们的和一定就是a+b。

        如果我们允许操作一次将其中一个数变大，那么它们的和的范围可以是[a+b+1,limit+b].如果我们还想将和变得更大，只能操作两次，使得和的范围达到[limit+b+1,2*limit].

        如果我们允许操作一次将其中一个数变小，那么它们的和的范围可以是[a+1,a+b].如果我们还想将和变得更小，只能操作两次，使得和的范围达到[2,a+b-1].

        所以我们在整个[2,2*limit]的区间上，可以画出“操作次数/pair-sum”的函数曲线：

        -----
        2  a+1       a+b a+b+1    limit+b+1       2*limit
        ____                      ________________
            |_________   _________|
                        |_|
        也就是说，我们对于nums[i]和nums[n-1-i]，想要这对pair sum处于[2,a]时，至少需要两次操作（将两个数都变小）；想要pair sum处于[a+1, a+b-1]时，至少需要一次操作（将其中的b变小）；想要pair sum等于a+b时，不需要操作；想要pair sum处于[a+b+1,limit+b]时，至少需要一次操作（将其中的a变大）；
        想要pair sum处于[limit+b+1, 2*limit]时，至少需要两次操作（将两个数都变大）。

        如果我们将所有的函数曲线叠加，就可以得到一个新的函数曲线：如果令所有的pair sum都相同，那么从这个曲线的纵坐标上就可以读出总共需要多少次操作。

        我们接下来需要做的就是扫一遍这个叠加的函数曲线，找到它的最小值。

        我们如何叠加这么多的单个曲线呢？首先，对于单个曲线而言，我们不需要描述出每个位置的操作次数。因为每条单个曲线都是五段的分段函数，我们只需要记录下每处拐点和差分值即可。当x=0的时候，y=0；当x=2的时候，diff[x]=2，也就是说经过这个位置之后相应的操作次数变动为 y+=2. 
        当x=a+1的时候，diff[x]=-1，也就是说经过这个位置之后需要的操作次数变成 y-=1. 同理，我们会设置diff[a+b]=-1, diff[a+b+1]=+1, diff[limit+b+1]=+1, diff[2*limit]=+1. 其他的位置diff[x]都等于0.

        最终计算每处x对应的y值（需要的最少操作数）时，只需要更新y+=diff[x]即可。
    */
    int doit_sweeplines(vector<int>& nums, int limit) {

        int N = nums.size();

        vector<int> sweeplines(2*limit + 2);

        for (int i = 0; i < nums.size()/2; i++) {

            int a = nums[i], b = nums[N-1-i];

            sweeplines[std::min(a+1, b+1)] -= 1;

            sweeplines[a+b] -= 1;
            sweeplines[a+b+1] += 1;

            sweeplines[std::max(a+limit, b+limit) + 1] += 1;
        }

        int res = N;
        for (int i = 0; i < 2*limit + 2; i++) {
            N += sweeplines[i];
            res = std::min(res, N);
        }

        return res;
    }

    int diff[200002];

public:

    int doit_sweepline(vector<int>& nums, int limit) 
    {        
        int n = nums.size();
        for (int i=0; i<n/2; i++)
        {            
            int a = std::min(nums[i],nums[n-1-i]);
            int b = std::max(nums[i],nums[n-1-i]);

            diff[2]+=2;
            diff[1+a]-=1;
            diff[a+b]-=1;
            diff[a+b+1]+=1;
            diff[limit+b+1]+=1;
        }

        int ret = INT_MAX;
        int count = 0;
        for (int i=2; i<=limit*2; i++)
        {
            count += diff[i];
            ret = std::min(ret, count);
        }
        return ret;
    }

    int doit_sweepline(vector<int>& nums, int limit) 
    {
        map<int,int>diff;
        int n = nums.size();
        for (int i=0; i<n/2; i++)
        {            
            int a = std::min(nums[i],nums[n-1-i]);
            int b = std::max(nums[i],nums[n-1-i]);

            diff[2]+=2;
            diff[1+a]-=1;
            diff[a+b]-=1;
            diff[a+b+1]+=1;
            diff[limit+b+1]+=1;
        }

        int ret = INT_MAX;
        int count = 0;
        for (auto x: diff)
        {
            count += x.second;
            ret = std::min(ret, count);
        }
        return ret;
    }


      static bool cmp(pair<int,int>&a, pair<int,int>&b)
    {
        return a.first+a.second<b.first+b.second;
    }
public:
    int minMoves(vector<int>& nums, int limit) 
    {
        int n = nums.size()/2;
        std::vector<pair<int,int>>p;
        for (int i=0; i<n; i++)
            p.push_back({min(nums[i],nums[2*n-1-i]), max(nums[i],nums[2*n-1-i])});
        
        sort(p.begin(), p.end(), cmp);
        
        vector<int>left(n);
        vector<int>right(n);
        multiset<int>Set;
        int count = 0;
        int same = 0;
        
        for (int i=0; i<n; i++)
        {
            int sum = p[i].first+p[i].second;
            if (i>0 && sum==p[i-1].first+p[i-1].second)
                same++;
            else
                same = 0;
            
            while (!Set.empty() && *Set.begin() < sum)
            {
                Set.erase(Set.begin());
                count++;
            }
            left[i] = i-count-same + count*2;
            Set.insert(p[i].second+limit);
        }
        
        Set.clear();
        count = 0;
        same = 0;
        
        for (int i=n-1; i>=0; i--)
        {
            int sum = p[i].first+p[i].second;
            if (i<n-1 && sum==p[i+1].first+p[i+1].second)
                same++;
            else
                same = 0;
            
            while (!Set.empty() && *Set.rbegin() > sum)
            {
                auto iter = Set.end();
                Set.erase(prev(iter));
                count++;
            }
            right[i] = n-1-i-count-same + count*2;
            Set.insert(p[i].first+1);
        }
        
        int ret = INT_MAX;
        for (int i=0; i<n; i++)
            ret = min(ret, left[i]+right[i]);
        return ret;
        
    }
};