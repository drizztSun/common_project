/*
1627. Graph Connectivity With Threshold

We have n cities labeled from 1 to n. Two different cities with labels x and y are directly connected by a bidirectional road 
if and only if x and y share a common divisor strictly greater than some threshold. More formally, cities with labels x and y have a road between them if there exists an integer z such that all of the following are true:

x % z == 0,
y % z == 0, and
z > threshold.
Given the two integers, n and threshold, and an array of queries, you must determine for each queries[i] = [ai, bi] if cities ai and bi are connected (i.e. there is some path between them).

Return an array answer, where answer.length == queries.length and answer[i] is true if for the ith query, there is a path between ai and bi, or answer[i] is false if there is no path.

 

Example 1:


Input: n = 6, threshold = 2, queries = [[1,4],[2,5],[3,6]]
Output: [false,false,true]
Explanation: The divisors for each number:
1:   1
2:   1, 2
3:   1, 3
4:   1, 2, 4
5:   1, 5
6:   1, 2, 3, 6
Using the underlined divisors above the threshold, only cities 3 and 6 share a common divisor, so they are the
only ones directly connected. The result of each query:
[1,4]   1 is not connected to 4
[2,5]   2 is not connected to 5
[3,6]   3 is connected to 6 through path 3--6
Example 2:


Input: n = 6, threshold = 0, queries = [[4,5],[3,4],[3,2],[2,6],[1,3]]
Output: [true,true,true,true,true]
Explanation: The divisors for each number are the same as the previous example. However, since the threshold is 0,
all divisors can be used. Since all numbers share 1 as a divisor, all cities are connected.
Example 3:


Input: n = 5, threshold = 1, queries = [[4,5],[4,5],[3,2],[2,3],[3,4]]
Output: [false,false,false,false,false]
Explanation: Only cities 2 and 4 share a common divisor 2 which is strictly greater than the threshold 1, so they are the only ones directly connected.
Please notice that there can be multiple queries for the same pair of nodes [x, y], and that the query [x, y] is equivalent to the query [y, x].
 

Constraints:

2 <= n <= 104
0 <= threshold <= n
1 <= queries.length <= 10^5
queries[i].length == 2
1 <= ai, bi <= cities
ai != bi

*/
#include <vector>
#include <numeric>

using std::vector;

class GraphConnecttivityWithThreshold {

    /*
        1627.Graph-Connectivity-With-Threshold
        本题考查的是如何高效地选择两个数进行Union.如果是遍历数字A、遍历数字B，再判断是否有大于threshold的公约数，时间复杂度会非常高。

        一个自然的想法是，遍历大于threshold的公约数x，然后查看x的倍数有哪些。所有关于x的倍数必然都是应该Union的。时间复杂度大概是1*n+2*n/2+3*n/3+...+n*n/n = n*(1/1+1/2+1/3+...+1/n)，后者是一个调和级数，增长的趋势近似于logN。所以总的时间复杂度是O(NlogN)。当然关于Union的操作我们得另算，我们可以近似认为均摊后是o(1)，本质上是一个关于n的常数。

        再进一步的改进是，我们不用遍历所有大于threshold的数作为公约数。我们如果已经考察过x作为公约数之后，所有的x的倍数都不用再考察作为公约数了。这等价于埃拉托斯特尼筛法。时间复杂度是O(NloglogN).
    */
    vector<int>Father;

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
        if (x<y)
            Father[y] = x;
        else
            Father[x] = y;
    }
    
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) 
    {
        Father.resize(n+1);
        for (int i=1; i<=n; i++)
            Father[i] = i;
        
        for (int k = threshold + 1; k <= n; k++) 
        {
            for (int x = 2 * k; x <= n; x += k) 
            {
                if (FindFather(x)!=FindFather(k))
                    Union(x, k);
            }
        }
        
        vector<bool>rets;
        for (auto query: queries)
            rets.push_back(FindFather(query[0])==FindFather(query[1]));
        return rets;
        
    }

public:
    
    vector<int>Father;

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
        if (x<y)
            Father[y] = x;
        else
            Father[x] = y;
    }
    
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) 
    {
        Father.resize(n+1);
        for (int i=1; i<=n; i++)
            Father[i] = i;
        
        vector<int>visited(n+1,0);
        for (int k = threshold + 1; k <= n; k++) 
        {
            if (visited[k]==1) continue;
            for (int x = 2 * k; x <= n; x += k) 
            {
                visited[x] = 1;
                if (FindFather(x)!=FindFather(k))
                    Union(x, k);
            }
        }
        
        vector<bool>rets;
        for (auto query: queries)
            rets.push_back(FindFather(query[0])==FindFather(query[1]));
        return rets;
        
    }

public:

    vector<bool> doit_disjoint(int n, int threshold, vector<vector<int>>& queries) {

        vector<int> parent(n+1);
        std::iota(begin(parent), end(parent), 0);

        auto find = [&](int x) -> int {
            while (x != parent[x]) {
                parent[x] = parent[parent[x]];
                x = parent[x];
            }
            return x;
        };

        for (int i = threshold + 1; i <= n; i++) {
            for (int j = 2; j*i <= n; j++) {

                int pa = find(i);
                int pb = find(i * j);

                if (pa != pb)
                    parent[pb] = pa;
            }
        }

        vector<bool> ans(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            ans[i] = (find(queries[i][0]) == find(queries[i][1]);
        }

        return ans;
    }
};