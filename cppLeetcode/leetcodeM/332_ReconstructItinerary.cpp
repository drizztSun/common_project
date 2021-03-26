/*
 332. Reconstruct Itinerary
 
 
 Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

 Note:

 If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
 All airports are represented by three capital letters (IATA code).
 You may assume all tickets form at least one valid itinerary.
 One must use all the tickets once and only once.
 Example 1:

 Input: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
 Output: ["JFK", "MUC", "LHR", "SFO", "SJC"]
 Example 2:

 Input: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
 Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
 Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"].
              But it is larger in lexical order.
 
 
 
 
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <deque>
#include <functional>
#include <algorithm>
#include <queue>

using std::queue;
using std::unordered_map;
using std::vector;
using std::string;
using std::deque;


class ReconstructItinerary {

    /*
        332.Reconstruct-Itinerary
        这是一道典型的DFS的题目。但是有两种不同的思路。

        方法一：无脑DFS
        相对直观的DFS的思路是：从起点出发，按字典顺序尝试每一个可以抵达的下一节点进行深度搜索，直至走到尽头。如果走到尽头的时候满足终止条件，即所有的机票都已经恰使用一次，那么就说明搜索成功了。否则，需要回溯到上一级搜索其他支线。

        这个方法有一个缺点。在本题中，题目保证最后的路径一定会使用到所有的机票。这就说明，如果尝试某一条支路的过程中走到了底没有成功（也就是说走到底的时候并没有用完所有的机票），虽然暂时失败了，但这条支路肯定会在之后的搜索中再走一遍（因为最终走成功路径一定会包括所有的机票）。这样，我们发现，这前一次没有成功的搜索其实被白白浪费了：明知道之后肯定会再走，但却没有带来任何帮助，效率低下。

        方法二：利用欧拉路径的性质
        本题保证了肯定有一个路径：所有的航程都会用到，并且每个航程只用一次。从有向图的角度来说，就是所给的图是一个欧拉路径。让你将这个路径打印出来。

        这题本质就是一个欧拉一笔画的问题。现在来回顾几个概念：

        欧拉路径：从一个点出发，到达另外一个点，所有的边都经过且只经过1次。

        欧拉回路：欧拉路径中，终点能回到起点。

        如果判断是否存在欧拉路径？

        1.无向图：(a) 如果只有两个点的度是奇数，其他的点的度都是偶数，则存在从一个奇数度点到另一个奇数度点的欧拉路径（不是回路）。(b) 如果所有的点的度都是偶数，那么就是欧拉回路。

        2.有向图：(a) 如果最多有一个点出度大于入度by1，且最多有一个点入度大于出度by1，那么就有一条从前者（如果没有则可以任意）到后者（如果没有则可以任意）的欧拉路径。(b) 如果所有的点的入度等于出度，那么就存在欧拉回路。

        因为本题保证了是这张图构成了欧拉路径，于是有一个非常好的性质：每条边都是必须遍历的，而且只需要遍历一次，因为它肯定是最终欧拉路径的一部分。所以对边的遍历，我们都不该浪费（某种意义上可以存着再利用）。探索欧拉路径的过程中，不像无脑DFS那样会有被“废弃”的支路。因此，构造欧拉路径的时间复杂度只需要o(E)。

        接下来我们讨论具体构造欧拉路径的算法。首先，我们先摆出这么一个结论。假设我们第一次到达B点，开始往后遍历，保证每条边只走一次。接下来只有两种可能：选择某条支路走遍了所有后续节点并走到了终点，完美地构建了B之后的所有欧拉路径。或者选择某条支路走到了终点，但没有遍历完所有后续节点；我们只好回溯走另外一条支路，一番探索之后最终返回B点（此时B点没有任何未走的出度）停止。

            -> D -> E
        A -> B <-> F       
        如上述的例子。最理想的情况是一次遍历走完所有想走的点 B->F->B->D->E. 但是我们在B的支路选择上不可能总是这么幸运，可能会走这样一条路 B->D->E，这样走到了尽头。但是B还有另一条支路->F没有走，如果我们尝试继续走那一条的话，就是 B->F->B，然后停止，因为此时B没有任何未走过的边了。

        那我们构造欧拉路径的思想是：B + path2 + path1，其中path1是从B点出发，选择任意支路并能够顺利走到终点的欧拉路径。path2是在path1走完之后，再从B点出发，最终走回B点的路径。注意，如果足够幸运，path1走遍了B后面的所有边，那么path2就不存在了。

        因为我们要最小化字典序，所以我们每次的分叉总会优先选择字典序较小的一支。如果这一支是类似上例中的"->D->E"这样直通到底的path1，那我们也无能为力，D注定是无法往前提的；否则的话我们就会先进入path2，从而更小化了整个欧拉路径的字典序。
    */

    unordered_map<string,queue<string>>Map;
    
public:
    vector<string> findItinerary(vector<vector<string>> tickets) 
    {
        sort(tickets.begin(),tickets.end());
        for (auto ticket: tickets)
            Map[ticket[0]].push(ticket[1]);
                
        return DFS("JFK");
    }
    
    vector<string> DFS(string start)
    {
        vector<vector<string>>paths;        
        while (Map[start].size()>0)
        {
            string nextStart = Map[start].front();
            Map[start].pop();
            paths.push_back(DFS(nextStart));
        }
        vector<string>ret({start});
        for (int i=paths.size()-1; i>=0; i--)
            for (auto t: paths[i])
                ret.push_back(t);
        return ret;
    }


    unordered_map<string,queue<string>>Map;
    
public:
    vector<string> findItinerary(vector<vector<string>> tickets) 
    {
        sort(tickets.begin(),tickets.end());
        for (auto ticket: tickets)
            Map[ticket[0]].push(ticket[1]);
        
        vector<string> path;
        DFS("JFK",path);
        reverse(path.begin(),path.end());
        return path;
    }
    
    void DFS(string start, vector<string>& path)
    {
        while (Map[start].size()>0)
        {
            string nextStart = Map[start].front();
            Map[start].pop();
            DFS(nextStart, path);
        }
        path.push_back(start);
    }


public:

    vector<string> doit_greedy_postorder(vector<vector<string>>& tickets) {
        
        unordered_map<string, deque<string>> graph;
        vector<string> trip;
        
        for (auto& c : tickets) {
            graph[c[0]].push_back(c[1]);
        }
        
        for (auto& c : graph) {
            auto& dests = c.second;
            std::sort(begin(dests), end(dests));
        }
        
        const string start = "JFK";
        
        std::function<void(const string& )> visit = [&](const string& city) {
            
            auto& next_cities = graph[city];
            
            while (!next_cities.empty()) {
                
                const string dest = next_cities.front();
                next_cities.pop_front();
                
                visit(dest);
            }
            
            trip.push_back(city);
        };
        
        
        visit("JFK");
        
        return vector<string>(trip.rbegin(), trip.rend());
    }

    /*
        There is gonna always having a path, one or multiple paths. we need to return the minimal paths by letters.

    */
    vector<string> findItinerary(vector<std::pair<string, string>> tickets) {

        // src -> {dst1, dest2, ..., destn}
        unordered_map<string, deque<string>> trips_;    
        // ans (reversed)
        vector<string> route_;

        route_.clear();
        trips_.clear();
        
        for(const auto& pair : tickets)
            trips_[pair.first].push_back(pair.second);
        
        for(auto& pair : trips_) {
            auto& dests = pair.second;
            std::sort(dests.begin(), dests.end());
        }
        
        const string kStart = "JFK";

        std::function<void(const string&)> visit = [&](const string& src) {
            auto& dests = trips_[src];
            while (!dests.empty()) {
                // Get the smallest dest
                const string dest = dests.front();
                // Remove the ticket
                dests.pop_front();
                // Visit dest
                visit(dest);
            }
            // Add current node to the route
            route_.push_back(src);
        };
        
        visit(kStart);
        
        return vector<string>(route_.crbegin(), route_.crend());
    }
};
