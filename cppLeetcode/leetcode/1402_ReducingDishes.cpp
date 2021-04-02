/*
1402. Reducing Dishes

A chef has collected data on the satisfaction level of his n dishes. Chef can cook any dish in 1 unit of time.

Like-time coefficient of a dish is defined as the time taken to cook that dish including previous dishes multiplied by its satisfaction level  i.e.  time[i]*satisfaction[i]

Return the maximum sum of Like-time coefficient that the chef can obtain after dishes preparation.

Dishes can be prepared in any order and the chef can discard some dishes to get this maximum value.

 

Example 1:

Input: satisfaction = [-1,-8,0,5,-9]
Output: 14
Explanation: After Removing the second and last dish, the maximum total Like-time coefficient will be equal to (-1*1 + 0*2 + 5*3 = 14). Each dish is prepared in one unit of time.
Example 2:

Input: satisfaction = [4,3,2]
Output: 20
Explanation: Dishes can be prepared in any order, (2*1 + 3*2 + 4*3 = 20)
Example 3:

Input: satisfaction = [-1,-4,-5]
Output: 0
Explanation: People don't like the dishes. No dish is prepared.
Example 4:

Input: satisfaction = [-2,5,-1,0,3,-3]
Output: 35
 

Constraints:

n == satisfaction.length
1 <= n <= 500
-10^3 <= satisfaction[i] <= 10^3

*/

#include <vector>
#include <algorithm>

using std::vector;


class MaxSatisfaction {

    /*
                1402.Reducing-Dishes
        两个突破点。首先我们肯定会把dishes按照满意度排序，满意度高的肯定放在后面做。其次，我们肯定会取若干个满意度最高的，关键就是取多少个而已。

        于是我们就是要尝试取最高的1个，或者2个，或者3个,...,直至n个满意度最高的dishes，计算最后总得分，取最大值。

        根据计算公式，显然每增加一道菜（按照满意度从高到底是第i个），总得分total就会增加的分值就是前i个菜的presum。
    */
    int maxSatisfaction(vector<int>& satisfaction) 
    {
        int n = satisfaction.size();
        sort(satisfaction.begin(),satisfaction.end());
        reverse(satisfaction.begin(),satisfaction.end());
        
        int total = 0, presum = 0;
        int ret = INT_MIN;
        for (int i=0; i<n; i++)
        {
            presum += satisfaction[i];
            total += presum;
            ret = max(ret, total);
        }
        return max(0,ret);
        
    }

public:

    int doit_greedy(vector<int>& satisfaction) {
        
        std::sort(begin(satisfaction), end(satisfaction));
        std::reverse(begin(satisfaction), end(satisfaction));
        
        int res = 0, total = 0, presum = 0;
        
        for (auto c : satisfaction) {
            
            presum += c;
            total += presum;
                
            res = std::max(res, total);
        }
        
        return res;
    }
};