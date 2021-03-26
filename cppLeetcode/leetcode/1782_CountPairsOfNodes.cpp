/*
1782. Count Pairs Of Nodes

You are given an undirected graph represented by an integer n, which is the number of nodes, and edges, 
where edges[i] = [ui, vi] which indicates that there is an undirected edge between ui and vi. You are also given an integer array queries.

The answer to the jth query is the number of pairs of nodes (a, b) that satisfy the following conditions:

    . a < b
    . cnt is strictly greater than queries[j], where cnt is the number of edges incident to a or b.

Return an array answers such that answers.length == queries.length and answers[j] is the answer of the jth query.

Note that there can be repeated edges.

 

Example 1:


Input: n = 4, edges = [[1,2],[2,4],[1,3],[2,3],[2,1]], queries = [2,3]
Output: [6,5]
Explanation: The number of edges incident to at least one of each pair is shown above.
Example 2:

Input: n = 5, edges = [[1,5],[1,5],[3,4],[2,5],[1,3],[5,1],[2,3],[2,5]], queries = [1,2,3,4,5]
Output: [10,10,9,8,6]
 

Constraints:

2 <= n <= 2 * 104
1 <= edges.length <= 105
1 <= ui, vi <= n
ui != vi
1 <= queries.length <= 20
0 <= queries[j] < edges.length

*/


#include <vector>
#include <unordered_map>
#include <algorithm>

using std::unordered_map;
using std::vector;


class CountPairs {

    /*
        1782.Count-Pairs-Of-Nodes
        我们可以很容易地求出每个节点的边的数目count[i]. 那么属于一个节点{a,b}的边的数目就是count[a]+count[b]-num[a][b]，其中num[a][b]就是从a到b的边的数目（因为可能会有重复的边）。
        减去的这部分，是因为“a-b”这条边被两个节点共享，所以count[a]和count[b]重复计算了两次，需要减去。注意我们主要减去一次num[a][b]，而不用再减去num[b][a]。

        假设query的数值是x，那么我们需要寻找有多少个点对{a,b}，满足count[a]+count[b]-num[a][b] > x。暴力枚举{a,b}的话，那需要o(N^2)的时间，显然会TLE。

        我们发现，如果不考虑num[a][b]这部分，那么点对{a,b}的数目其实可以用o(VlogV)的时间复杂度计算。
        将count排序后，如果固定a指针，那么b指针相应地从后往前移动直到不满足count[a]+count[b]>x为止，那么说明以a为第一个点时，b有n-b-1种选择。这样我们依次遍历所有的a，就可以累加得到所有{a,b}的点对数目count。

        以上的count其实是一个被高估的数目。因为很多点对不满足count[a]+count[b]-num[a][b] > x。那么如何排除掉这些不满足条件的点对呢？难道还是要枚举a和b呢？其实这里有一个巧妙的视角。
        满足count[a]+count[b] > x但是不满足count[a]+count[b]-num[a][b] > x的点对，一定是有边互联的点对。所以我们只需要遍历所有的边，查看这条边所连接的两个节点是否属于被“误判”的点对。是的话，从count里面减去就行了。

        这里需要注意的是，因为有重复的边，所以我们只能遍历所有unique的边。否则被“误判”的点对可能会被删除多次。为了标记unique的边，我们可以用边的两个端点a和b编码成一个index=a*M+b，其中a<b。这样连接同一对点的边都会有独一无二的index。
    */
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) 
    {
        vector<int>count(n);
        unordered_map<long, int>edgeCount;             
        long M = 20001;
        
        for (auto edge: edges)
        {
            int a = std::min(edge[0]-1, edge[1]-1);
            int b = std::max(edge[0]-1, edge[1]-1);
            count[a]++;
            count[b]++;
            edgeCount[a*M+b]++;
        }
               
        auto count2 = count;
        sort(count2.begin(), count2.end());
        
        vector<int>rets;
        for (int q: queries)
        {
            int sum = 0;
            int j = n-1;
            for (int i=0; i<n; i++)
            {
                if (i>=j)
                {
                    sum += n-i-1;
                }
                else
                {
                    while (i<j && count2[i]+count2[j] > q)
                        j--;
                    sum += n-j-1;                    
                }                
            }
                        
            for (auto [edgeIdx, cnt]:edgeCount)
            {
                int a = edgeIdx/M;
                int b = edgeIdx%M;
                if (count[a]+count[b]>q && count[a]+count[b]-cnt<=q)
                {
                    sum--;
                }
            }
            rets.push_back(sum);
        }        
        
        return rets;
    }

public:
    
    vector<int> doit_(int n, vector<vector<int>>& edges, vector<int>& queries) {

    }
};
