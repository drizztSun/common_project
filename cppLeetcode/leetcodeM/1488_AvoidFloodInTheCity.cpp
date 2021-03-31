/*
1488. Avoid Flood in The City

Your country has an infinite number of lakes. Initially, all the lakes are empty, but when it rains over the nth lake, the nth lake becomes full of water. 
If it rains over a lake which is full of water, there will be a flood. Your goal is to avoid the flood in any lake.

Given an integer array rains where:

rains[i] > 0 means there will be rains over the rains[i] lake.
rains[i] == 0 means there are no rains this day and you can choose one lake this day and dry it.
Return an array ans where:

ans.length == rains.length
ans[i] == -1 if rains[i] > 0.
ans[i] is the lake you choose to dry in the ith day if rains[i] == 0.
If there are multiple valid answers return any of them. If it is impossible to avoid flood return an empty array.

Notice that if you chose to dry a full lake, it becomes empty, but if you chose to dry an empty lake, nothing changes. (see example 4)

 

Example 1:

Input: rains = [1,2,3,4]
Output: [-1,-1,-1,-1]
Explanation: After the first day full lakes are [1]
After the second day full lakes are [1,2]
After the third day full lakes are [1,2,3]
After the fourth day full lakes are [1,2,3,4]
There's no day to dry any lake and there is no flood in any lake.
Example 2:

Input: rains = [1,2,0,0,2,1]
Output: [-1,-1,2,1,-1,-1]
Explanation: After the first day full lakes are [1]
After the second day full lakes are [1,2]
After the third day, we dry lake 2. Full lakes are [1]
After the fourth day, we dry lake 1. There is no full lakes.
After the fifth day, full lakes are [2].
After the sixth day, full lakes are [1,2].
It is easy that this scenario is flood-free. [-1,-1,1,2,-1,-1] is another acceptable scenario.
Example 3:

Input: rains = [1,2,0,1,2]
Output: []
Explanation: After the second day, full lakes are  [1,2]. We have to dry one lake in the third day.
After that, it will rain over lakes [1,2]. It's easy to prove that no matter which lake you choose to dry in the 3rd day, the other one will flood.
Example 4:

Input: rains = [69,0,0,0,69]
Output: [-1,69,1,1,-1]
Explanation: Any solution on one of the forms [-1,69,x,y,-1], [-1,x,69,y,-1] or [-1,x,y,69,-1] is acceptable where 1 <= x,y <= 10^9
Example 5:

Input: rains = [10,20,20]
Output: []
Explanation: It will rain over lake 20 two consecutive days. There is no chance to dry any lake.
 

Constraints:

1 <= rains.length <= 10^5
0 <= rains[i] <= 10^9


*/
#include <vector>
#include <unordered_map>
#include <set>

using std::set;
using std::unordered_map;
using std::vector;

class AvoidFlood {

    /*
        1488.Avoid-Flood-in-The-City
        我们来分析一下贪心的策略会是什么。

        我们如果在第i天遇到一个晴天，那么我们肯定会利用它来抽干某个湖。但是抽干哪个湖最合算呢？其实我们这时候是不确定的。如果某个湖在以后的日子里再也不会被下雨，那么我们在当前的晴天取抽水，并没有任何意义。所以我们只有在日后某个雨天时发现，某个湖已经充满、但是又要被下雨的时候，才会“回溯性”地决策在之前的某个晴天提前把这个湖抽干。因此，在晴天的时候，我们暂时不会做任何事情，只是默默把当前的日子加入一个集合dryDays。以后发现需要确定抽水日的时候，就从里面选。

        我们如果在第i天遇到要对湖x下雨，我们必然会查看这个湖是否已经充满。

        如果尚未充满，我们就标记为充满fill[x]=i，但不着急做任何抽水的规划。
        如果湖x已经充满了，为了避免泛滥，我们一定要在第i天之前提前把湖x抽干。那么是哪一天最合适呢？首先，这一天一定是dryDays的集合中；其次一定要在fill[x]之后做（因为只有先充满了才能去抽干）。那么是否满足这两个条件的任意一天都可以呢？其实我们还希望越早越好。举个例子：
        fillDays:     x       y       x   y
        dryDays:          _       _
        第8天的时候湖x可能会泛滥，所以我们必须在第5天或者第7天的时候把湖x抽干。但是如果我们选择在第7天取抽干湖x的话，当第9天y要泛滥的时候，我们就没有dry day去抽干湖y了。这就说明了，要抽干得趁早。在敲定了第5天抽干湖x之后，就把dryDays里去掉这一天。同时要更新fill[x]=8,即当天的下雨日。
    */
    vector<int> avoidFlood(vector<int>& rains) 
    {
        unordered_map<int,int>fill; // fill[x] is the last day that rain filled lake x        
        set<int>dryDays;         // the days that are dry, i.e. when we can drain
        vector<int>rets(rains.size(),1);
        
        for (int i=0; i<rains.size(); i++)
        {
            int x = rains[i];
            if (x==0)            
                dryDays.insert(i);            
            else
            {
                rets[i] = -1;
                if (fill.find(x)!=fill.end())
                {
                    auto iter = dryDays.lower_bound(fill[x]);
                    if (iter==dryDays.end()) return {};                    
                    rets[*iter] = x;  
                    dryDays.erase(*iter);                    
                }
                fill[x] = i;
            }            
        }        
        return rets;        
    }
    
public:
    
    vector<int> doit_hashtable_greedy(vector<int>& rains) {
        
        int size = rains.size();
        vector<int> res(size, 1);
        unordered_map<int, int> lakefullday;
        set<int> days;

        for (int i = 0; i < rains.size(); i++) {

            if (rains[i] == 0) {
                days.insert(i);
                continue;
            }

            res[i] = -1;

            if (lakefullday.find(rains[i]) != lakefullday.end()) {
                
                set<int>::iterator it = days.upper_bound(lakefullday[rains[i]]);

                if (it == days.end())
                    return {};

                res[*it] = rains[i];
                days.erase(it);
            }

            lakefullday[rains[i]] = i;
        }

        return res;
    }
};