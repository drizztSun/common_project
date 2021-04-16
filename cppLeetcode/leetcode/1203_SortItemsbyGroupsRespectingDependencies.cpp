/*
1203. Sort Items by Groups Respecting Dependencies


There are n items each belonging to zero or one of m groups where group[i] is the group that the i-th item belongs to and it's equal to -1 if the i-th item belongs to no group. 
The items and the groups are zero indexed. A group can have no item belonging to it.

Return a sorted list of the items such that:

    . The items that belong to the same group are next to each other in the sorted list.
    . There are some relations between these items where beforeItems[i] is a list containing all the items that should come before the i-th item in the sorted array (to the left of the i-th item).
Return any solution if there is more than one solution and return an empty list if there is no solution.

 

Example 1:



Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]
Output: [6,3,4,1,5,2,0,7]
Example 2:

Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3],[],[4],[]]
Output: []
Explanation: This is the same as example 1 except that 4 needs to be before 6 in the sorted list.
 

Constraints:

1 <= m <= n <= 3 * 104
group.length == beforeItems.length == n
-1 <= group[i] <= m - 1
0 <= beforeItems[i].length <= n - 1
0 <= beforeItems[i][j] <= n - 1
i != beforeItems[i][j]
beforeItems[i] does not contain duplicates elements.
*/

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using std::queue;
using std::unordered_set;
using std::unordered_map;
using std::vector;


class SortItemsbyGroupsRespectingDependencies {

    /*
        1203.Sort-Items-by-Groups-Respecting-Dependencies
        本题本质是两遍拓扑排序。

        首先，我们收集每个group内的节点关系，在每个组内进行拓扑排序。

        其次，对于任何跨组的一对节点的先后顺序，本质上反映的就是两个组的先后顺序。因此收集完所有的组间顺序的要求后，可以重复利用拓扑排序的代码，对组进行排序。

        最终，安排两层循环，大循环按照已经排好的组的顺序、小循环按照已经排好的组内节点的顺序，依次输出所有的节点，就是答案。
    */
     vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) 
    {
        unordered_map<int, unordered_set<int>>groupItems;
        int nextGroupId = m;

        for (int i=0; i<n; i++)
        {
            if (group[i]==-1)
            {
                group[i] = nextGroupId;
                nextGroupId += 1;
            }
            groupItems[group[i]].insert(i);
        }

        // build graph inside each group
        unordered_map<int, unordered_set<int>>next;
        unordered_map<int, int>inDegree;
        for (int i=0; i<n; i++)        
            for (int j: beforeItems[i])
            {
                if (group[i]!=group[j]) continue;
                if (next[j].find(i)==next[j].end())                
                {
                    next[j].insert(i);
                    inDegree[i] += 1;
                }
            }
        // sort nodes inside each group
        unordered_map<int, vector<int>>groupItemsOrdered;
        for (auto x: groupItems)
        {
            int groupId = x.first;
            groupItemsOrdered[groupId] = topologySort(groupItems[groupId], next, inDegree);
            if (groupItemsOrdered[groupId].size() != groupItems[groupId].size())
                return {};
        }

        // build graph among groups
        next.clear();
        inDegree.clear();
        for (int i=0; i<n; i++)        
            for (int j: beforeItems[i])
            {
                if (group[i]==group[j]) continue;
                if (next[group[j]].find(group[i])==next[group[j]].end())                
                {
                    next[group[j]].insert(group[i]);
                    inDegree[group[i]] += 1;
                }
            }
        // sort groups
        unordered_set<int>groups;
        for (int i=0; i<n; i++) groups.insert(group[i]);
        vector<int>groupOrdered = topologySort(groups, next, inDegree);

        vector<int>rets;
        for (int groupId: groupOrdered)
        {
            for (auto node: groupItemsOrdered[groupId])
                rets.push_back(node);
        }
        return rets;
    }

    vector<int> topologySort (unordered_set<int>&nodes, unordered_map<int, unordered_set<int>>&next, unordered_map<int, int>&inDegree)
    {
        queue<int>q;
        vector<int>ret;
        for (auto node: nodes)
        {
            if (inDegree[node]==0)
                q.push(node);
        }
         while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            ret.push_back(cur);            
            for (auto next: next[cur] )
            {
                inDegree[next] -= 1;
                if (inDegree[next] == 0)
                    q.push(next);
            }
        }
        
        return ret.size()==nodes.size() ? ret : vector<int>{};
    }

public:

    vector<int> doit_topsort(int n, int m, vector<int>&& group, vector<vector<int>>&& beforeItems) {

        vector<vector<int>> next(n);
        vector<int> degree(n, 0);

        for (int i = 0; i < group.size(); i++) {
            if (group[i] == -1) {
                group[i] = m;
                m++;
            }
        }

        vector<unordered_set<int>> nextgroup(m);
        vector<int> groupDegree(m, 0);
        vector<vector<int>> groupMap(m);

        for (int i = 0; i < group.size(); i++) {

            groupMap[group[i]].push_back(i);

            for (auto c : beforeItems[i]) {

                if (group[i] != group[c]) {
                    if (nextgroup[group[c]].count(group[i]) == 0)
                        groupDegree[group[i]]++;
                    nextgroup[group[c]].insert(group[i]);
                }
                else {
                    next[c].push_back(i);
                    degree[i]++;
                }
            }
        }

        queue<int> qu;
        unordered_set<int> visitedgroup;

        for (int i = 0; i < groupDegree.size(); i++) {
            if (groupDegree[i] == 0)
                qu.push(i);
        }

        vector<int> ans;

        while (!qu.empty()) {

            int curgroup = qu.front(); qu.pop();

            queue<int> que;
            for (auto t : groupMap[curgroup]) {
                if (degree[t] == 0) que.push(t);
            }

            while (!que.empty()) {

                int curitem = que.front(); que.pop();

                ans.push_back(curitem);

                for (auto child : next[curitem]) {

                    degree[child]--;
                    if (degree[child] == 0 && group[child] == curgroup) {
                        que.push(child);
                    }
                }
            }

            for (auto childgroup : nextgroup[curgroup]) {

                groupDegree[childgroup]--;
                if (groupDegree[childgroup] == 0)
                    qu.push(childgroup);
            }

        }

        return ans.size() == n ? ans : vector<int>{};
    }
};