/*
 
 1697. Checking Existence of Edge Length Limited Paths
 
 
 An undirected graph of n nodes is defined by edgeList, where edgeList[i] = [ui, vi, disi] denotes an edge between nodes ui and vi with distance disi. Note that there may be multiple edges between two nodes.

 Given an array queries, where queries[j] = [pj, qj, limitj], your task is to determine for each queries[j] whether there is a path between pj and qj such that each edge on the path has a distance strictly less than limitj .

 Return a boolean array answer, where answer.length == queries.length and the jth value of answer is true if there is a path for queries[j] is true, and false otherwise.

  

 Example 1:


 Input: n = 3, edgeList = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries = [[0,1,2],[0,2,5]]
 Output: [false,true]
 Explanation: The above figure shows the given graph. Note that there are two overlapping edges between 0 and 1 with distances 2 and 16.
 For the first query, between 0 and 1 there is no path where each distance is less than 2, thus we return false for this query.
 For the second query, there is a path (0 -> 1 -> 2) of two edges with distances less than 5, thus we return true for this query.
 Example 2:


 Input: n = 5, edgeList = [[0,1,10],[1,2,5],[2,3,9],[3,4,13]], queries = [[0,4,14],[1,4,13]]
 Output: [true,false]
 Exaplanation: The above figure shows the given graph.
  

 Constraints:

 2 <= n <= 105
 1 <= edgeList.length, queries.length <= 105
 edgeList[i].length == 3
 queries[j].length == 3
 0 <= ui, vi, pj, qj <= n - 1
 ui != vi
 pj != qj
 1 <= disi, limitj <= 109
 There may be multiple edges between two nodes.
 
 
 
 */

#include <stdio.h>
#include <vector>
#include <numeric>


using std::vector;


class CheckingExistenceEdgeLengthLimitedPath {
        
public:

    /*
     
     1697.Checking-Existence-of-Edge-Length-Limited-Paths
     我们考虑一下如果只有一个query的话我们会怎么做？显然，我们只要考虑所有权重小于limit的那些edges，看看这些edges能否把query的两个node连接在一起。这是一个典型的Union Find的解法，时间复杂度近似为o(E).

     但是本题有多个queries，如果对于每个query都独立解决的话，时间复杂度大致是o(QE)，这样来看是会TLE的。

     解决方案很简单。我们优先解决limit低的query，因为它所能用到的edge数目更少，我们只需要查看少量的edges看它是否能够成query两点的连通图。然后我们再解决limit较高的query，此时只需要在已经构建的图里面再添加若干个新edge即可（因为放宽了对权重的要求），
     再判断query的两点是否联通...可见，如果我们将所有的queries按照limit从小到大排列进行处理，那么相应地我们只需要按照权重从小到大地添加边就行了。在构建联通图的过程中，每条边只需要处理一遍。

     所以本题的时间复杂度可以近似认为是o(ElogE)，瓶颈在于对所有edges的排序。
    */
    int Father[100005];
    
    static bool cmp(vector<int>&a, vector<int>&b)
    {
        return a[2]<b[2];
    }

    int FindFather(int x)
    {
        if (Father[x]!=x)
            Father[x] = FindFather(Father[x]);
        return Father[x];
    }
    
    void Union(int x, int y)
    {
        x = Father[x];
        y = Father[y];
        if (x<y) Father[y] = x;
        else Father[x] = y;
    }
    
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) 
    {
        for (int i=0; i<n; i++)
            Father[i] = i;
        
        for (int i=0; i<queries.size(); i++)
            queries[i].push_back(i);
        
        sort(queries.begin(), queries.end(), cmp);        
        sort(edgeList.begin(), edgeList.end(), cmp);
        
        int i = 0;
        vector<bool>ret(queries.size(),0);
        for (auto& q: queries)
        {
            while (i<edgeList.size() && edgeList[i][2] < q[2])
            {
                int a = edgeList[i][0];
                int b = edgeList[i][1];
                if (FindFather(a)!=FindFather(b))
                    Union(a,b);
                i++;
            }
            int idx = q[3];
            ret[idx] = (FindFather(q[0])==FindFather(q[1]));
        }
        return ret;        
    }

public:    
    
    vector<bool> doit_disjoint(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        
        auto cmp = [](vector<int>& a, vector<int>& b) {
            return a[2] < b[2];
        };
        
        vector<bool> res(queries.size(), 0);
        for (int i = 0; i < queries.size(); i++)
            queries[i].push_back(i);
        
        std::sort(begin(edgeList), end(edgeList), cmp);
        std::sort(begin(queries), end(queries), cmp);
        
        vector<int> father(n, 0);
        std::iota(begin(father), end(father), 0);
        
        auto Find = [&](int a) {
            while (father[a] != a) {
                father[a] = father[father[a]];
                a = father[a];
            }
            return father[a];
        };
        
        auto Union = [&](int a, int b) {
            int pa = Find(a), pb = Find(b);
            if (pa > pb)
                father[pa] = pb;
            else if (pa < pb)
                father[pb] = pa;
        };
        
        
        int i = 0;
        for (auto& c : queries)
        {
            while (i < edgeList.size() && c[2] > edgeList[i][2]) {
                
                int a = edgeList[i][0], b = edgeList[i][1];
                
                if (Find(a) != Find(b)) {
                    Union(a, b);
                }
                i++;
            }          
            res[c[3]] = (Find(c[0]) == Find(c[1]));
        }
        
        return res;
    }
    
    
    vector<int> p;
    
    void init(int n) {
        p = vector<int>(n);
        for (int i=0;i<n;++i) p[i] = i;
    }
    
    int find(int x) {
        if (p[x] != x) return p[x] = find(p[x]);
        return x;
    }
    
    void merge(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;
        p[rx] = ry;
    }
    
    vector<bool> weightLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        if (n == 1) return vector<bool>();
        vector<bool> result(queries.size(), false);
        auto func = [&](const vector<int>& a, const vector<int>& b) { return a[2] < b[2]; };
        for (int i=0;i<queries.size();++i) queries[i].push_back(i);
        
        std::sort(edgeList.begin(), edgeList.end(), func);
        std::sort(queries.begin(), queries.end(), func);
        
        init(n);
        int e = 0;
        for (auto& q : queries) {
            while (e < edgeList.size() && edgeList[e][2] < q[2]) {
                auto& E = edgeList[e++];
                merge(E[0], E[1]);
            }
            result[q[3]] = find(q[0]) == find(q[1]);
        }
        return result;
    }
};
