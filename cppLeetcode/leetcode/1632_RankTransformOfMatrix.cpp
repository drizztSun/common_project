/*

1632. Rank Transform of a Matrix

Given an m x n matrix, return a new matrix answer where answer[row][col] is the rank of matrix[row][col].

The rank is an integer that represents how large an element is compared to other elements. It is calculated using the following rules:

The rank is an integer starting from 1.
If two elements p and q are in the same row or column, then:
    If p < q then rank(p) < rank(q)
    If p == q then rank(p) == rank(q)
    If p > q then rank(p) > rank(q)
The rank should be as small as possible.
It is guaranteed that answer is unique under the given rules.

 

Example 1:


Input: matrix = [[1,2],[3,4]]
Output: [[1,2],[2,3]]
Explanation:
The rank of matrix[0][0] is 1 because it is the smallest integer in its row and column.
The rank of matrix[0][1] is 2 because matrix[0][1] > matrix[0][0] and matrix[0][0] is rank 1.
The rank of matrix[1][0] is 2 because matrix[1][0] > matrix[0][0] and matrix[0][0] is rank 1.
The rank of matrix[1][1] is 3 because matrix[1][1] > matrix[0][1], matrix[1][1] > matrix[1][0], and both matrix[0][1] and matrix[1][0] are rank 2.
Example 2:


Input: matrix = [[7,7],[7,7]]
Output: [[1,1],[1,1]]
Example 3:


Input: matrix = [[20,-21,14],[-19,4,19],[22,-47,24],[-19,4,19]]
Output: [[4,2,3],[1,3,4],[5,1,6],[1,3,4]]
Example 4:


Input: matrix = [[7,3,6],[1,4,5],[9,8,2]]
Output: [[5,1,4],[1,2,3],[6,3,1]]
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 500
-10^9 <= matrix[row][col] <= 10^9

*/
#include <vector>
#include <queue>
#include <numeric>

using std::queue;
using std::vector;


class MatrixRankTransform {


    /*
    1632.Rank-Transform-of-a-Matrix
    解法1：拓扑排序
    拓扑排序是比较容易想到的方法。对于同一行（列）而言，如果把所有数字从小到大排列，那么较大的数字num[i]应该比它前面的数字num[i-1]的rank大，所以我们可以将构造一条从num[i-1]指向num[i]的路径。得到所有路径之后，我们就得到一张图。此时所有入度为0的这批点（即最外围的点）没有任何约束关系（意思是没有rank必须必它们小的其他点），故他们的rank就可以赋值为1. 将这批点剥离之后，剩下的所有入度为0的点，他们的rank可以赋值为2，以此类推。

    但是有一种情况，就是同一行（列）中，如果有相同的数字，那么他们必须有相同的rank，因此在拓扑排序中需要把它们当做同一个点来处理。事实上，需要当做同一个点来处理的点可能有多个（而且会分布在不同的row或col里）。这就需要用union find来将这些点归并到同一个group里。同一个group的点在拓扑排序中只被处理一次，赋值相同的rank。

    如果用拓扑排序来做，此题比较棘手的地方就是在于处理indegree。我们知道，拓扑排序的每个回合，我们剥离入度为0的点。在这里，我们需要将所有属于同一个group的点的入度要累加在一块儿计算。当整个group的入度为0的时候，我们才将其加入队列；当它弹出队列的时候，该group的所有点都赋予相同的rank。然后这些点的剥离会给各自next的点减少一个入度，但注意，这些入度的自减也必须都统计在整个group上。

        解法2：贪心
    我们将所有的点从到大排个序。全局最小点自然rank是1，并且对于该点所在行和列的其他数字，它们的rank必然要从2开始。

    更general地，我们从小到大依次处理每个数字的时候，应该如何给它定rank呢？其实只要查看它所在的行、列各自已经赋值的rank。比如说，该行已经有其他数字被rank为3，该列已经有其他数字被rank为4，那么显然这个数字只能被rank为5.接下来，记得要把这个数字所在的行和列，都更新标记，因为它们已经赋值的rank变成了5. 根据这个规则我们就可以把所有数字都rank一遍。

    同样，有一种情况需要处理，就是前面所说的，可能有一批数字必须有相同的rank。所以如果想要rank某个数，必须考察所有同属一个group的数（的行与列），才能确定这个rank。然后给它们赋值相同的rank，然后更新它们的行/列的已rank信息。 
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

public:
    
    vector<vector<int>> doit_topsort_disjoint(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        Father.resize(m*n);
        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
                Father[i*n+j] = i*n+j;
                
        vector<vector<int>>next(m*n);        
        vector<int>inDegree(m*n,0);        
        
        for (int i=0; i<m; i++)
        {
            vector<pair<int,int>>temp;
            for (int j=0; j<n; j++)
                temp.push_back({matrix[i][j], i*n+j});
            sort(temp.begin(), temp.end());
            for (int j=1; j<n; j++)
            {
                if (temp[j].first>temp[j-1].first)
                {
                    next[temp[j-1].second].push_back(temp[j].second);
                    inDegree[temp[j].second]++;
                }                    
                else
                {
                    if (FindFather(temp[j-1].second)!=FindFather(temp[j].second))
                        Union(temp[j-1].second, temp[j].second);
                }                    
            }
        }
        
        for (int j=0; j<n; j++)
        {
            vector<pair<int,int>>temp;
            for (int i=0; i<m; i++)
                temp.push_back({matrix[i][j], i*n+j});
            sort(temp.begin(), temp.end());
            for (int i=1; i<m; i++)
            {
                if (temp[i].first>temp[i-1].first)
                {
                    next[temp[i-1].second].push_back(temp[i].second);
                    inDegree[temp[i].second]++;
                }                    
                else
                {
                    if (FindFather(temp[i-1].second)!=FindFather(temp[i].second))
                        Union(temp[i-1].second, temp[i].second);
                }                    
            }
        }
                        
        vector<vector<int>>group(m*n);
        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
            {
                int root = FindFather(i*n+j);
                group[root].push_back(i*n+j);
                if (root!=i*n+j)
                    inDegree[root]+=inDegree[i*n+j];
            }
        
        queue<int>q;
        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
            {
                if (Father[i*n+j]==i*n+j && inDegree[i*n+j]==0)
                    q.push(i*n+j);
            }
        
        int idx = 1;
        auto rets = vector<vector<int>>(m,vector<int>(n,-1));
        while (!q.empty())
        {
            int len = q.size();
            while (len--)
            {
                int cur = q.front();
                q.pop();
                
                for (auto connect: group[cur])
                    rets[connect/n][connect%n] = idx;
                                        
                for (auto connect: group[cur])
                    for (auto nxt: next[connect])
                    {
                        inDegree[Father[nxt]]--;
                        if (inDegree[Father[nxt]]==0)
                            q.push(Father[nxt]);
                    }                        
            }
            idx++;            
        }        
        return rets;
    }



    /*
    解法2：贪心
    我们将所有的点从到大排个序。全局最小点自然rank是1，并且对于该点所在行和列的其他数字，它们的rank必然要从2开始。
    
    更general地，我们从小到大依次处理每个数字的时候，应该如何给它定rank呢？其实只要查看它所在的行、列各自已经赋值的rank。比如说，该行已经有其他数字被rank为3，该列已经有其他数字被rank为4，那么显然这个数字只能被rank为5.接下来，记得要把这个数字所在的行和列，都更新标记，因为它们已经赋值的rank变成了5. 根据这个规则我们就可以把所有数字都rank一遍。

    同样，有一种情况需要处理，就是前面所说的，可能有一批数字必须有相同的rank。所以如果想要rank某个数，必须考察所有同属一个group的数（的行与列），才能确定这个rank。然后给它们赋值相同的rank，然后更新它们的行/列的已rank信息。
    */
    vector<vector<int>> doit_topsort_disjoint(vector<vector<int>>& matrix) {
        
        int m = matrix.size(), n = matrix[0].size();

        vector<int> parent(n*m);
        //std::iota(begin(parent), end(parent), 0);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                parent[i*n+j] = i*n+j; 
        
        
        auto find = [&](int x) {
            while (parent[x] != x) {
                parent[x] = parent[parent[x]];
                x = parent[x];
            }
            return x;
        };

        auto merge = [&](int a, int b) {
            int pa = find(a), pb = find(b);
            if (pa != pb) {
                if (pa < pb)
                    parent[pb] = pa;
                else
                    parent[pa] = pb;
            }
        };

        vector<vector<int>> next(m*n);
        vector<int> indegree(m*n, 0);

        for (int i = 0; i < m; i++) {

            vector<std::pair<int, int>> tmp;
            for (int j = 0; j < n; j++) {
                tmp.push_back({matrix[i][j], i * n + j});
            }

            std::sort(begin(tmp), end(tmp));

            for(int k = 0; k < n-1; k++) {
                if (tmp[k].first == tmp[k+1].first) {
                    merge(tmp[k].second, tmp[k+1].second);
                } else {
                    next[tmp[k].second].push_back(tmp[k+1].second);
                    indegree[tmp[k+1].second]++;
                }
            } 
        }

        for (int j = 0; j < n; j++) {

            vector<std::pair<int, int>> tmp;
            for (int i = 0; i < m; i++) {
                tmp.push_back({matrix[i][j], i*n+j});
            }

            std::sort(begin(tmp), end(tmp));

            for (int k = 0; k < m-1; k++) {
                if (tmp[k] == tmp[k+1]) {
                    merge(tmp[k].second, tmp[k+1].second);
                } else {
                    next[tmp[k].second].push_back(tmp[k+1].second);
                    indegree[tmp[k+1].second]++;
                }
            }
        }

        vector<vector<int>> group(n*m);

        for (int i = 0; i < m; i++) 
            for (int j = 0; j < n; j++) {
                int root = find(i*n + j); 
                group[root].push_back(i*n+j);
                if (root != i*n + j)
                    indegree[root] += indegree[i*n+j];
            }

        
        queue<int> qu;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (parent[i*n+j] == i*n+j && indegree[i*n+j] == 0)
                    qu.push(i*n+j);
            }

        int idx = 1;
        vector<vector<int>> ans(m, vector<int>(n, -1));

        while (!qu.empty()) {

            int size = qu.size();

            while (size--) {

                int cur = qu.front();
                qu.pop();
                
                for (auto member: group[cur])
                    ans[member/n][member%n] = idx;

                for (auto connect: group[cur]) {
                    for (auto c : next[connect]) {
                        int root = find(c);
                        indegree[root]--;
                        if (indegree[root] == 0) {
                            qu.push(root);
                        }
                    }
                }
            }
            idx++;
        }

        return ans;
    }
};

void test_1632_rank_transform() {

    vector<vector<int>> dl{{7, 7}, {7, 7}};

    MatrixRankTransform obj;

    auto res = obj.doit_topsort_disjoint(dl);

}