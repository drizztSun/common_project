/*
475. Heaters

Winter is coming! During the contest, your first job is to design a standard heater with a fixed warm radius to warm all the houses.

Every house can be warmed, as long as the house is within the heater's warm radius range. 

Given the positions of houses and heaters on a horizontal line, return the minimum radius standard of heaters so that those heaters could cover all houses.

Notice that all the heaters follow your radius standard, and the warm radius will the same.

 

Example 1:

Input: houses = [1,2,3], heaters = [2]
Output: 1
Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
Example 2:

Input: houses = [1,2,3,4], heaters = [1,4]
Output: 1
Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard, then all the houses can be warmed.
Example 3:

Input: houses = [1,5], heaters = [2]
Output: 3
 

Constraints:

1 <= houses.length, heaters.length <= 3 * 10^4
1 <= houses[i], heaters[i] <= 10^9

*/


#include <vector>
#include <algorithm>

using std::vector;

class HeatersRadius {

    /*
        475.Heaters
        最佳的binary search方案是：遍历所有houses[i]，记录其位置pos，在有序的heaters序列里找到第一个大于（等于）pos的迭代器元素it，判断*it和*(it-1)与pos的距离，较小值就是该house[i]的最小供暖半径。  

        寻找it的方法用lower_bound函数。

        auto it = lower_bound(heaters.begin(),heaters.end(),pos);
        特别注意当it==heaters.begin()或it==heaters.end()时的特例。说明houses[i]在所有heaters的一边，所以只需要计算单边的半径距离。
    */

    int findRadius(vector<int>& houses, vector<int>& heaters) 
    {
        std::sort(heaters.begin(),heaters.end());
        int result=0;
        
        for (int i=0; i<houses.size(); i++)
        {
            int radius;
            
            auto pos= lower_bound(heaters.begin(),heaters.end(),houses[i]);
            
            if (pos==heaters.begin())
                radius = heaters[0]-houses[i];
            else if (pos==heaters.end())
                radius = houses[i]-heaters.back();
            else
                radius = std::min(*pos-houses[i], houses[i]-*(pos-1));
                
            result = std::max(result,radius);
        }
        
        return result;
    }
};