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
#include <unordered_map>
#include <unordered_set>
#include <map>

using std::map;
using std::unordered_set;
using std::unordered_map;
using std::queue;
using std::vector;


class MatrixRankTransform {


    /*
        1632.Rank-Transform-of-a-Matrix
        
        解法1：拓扑排序
        拓扑排序是比较容易想到的方法。对于同一行（列）而言，如果把所有数字从小到大排列，那么较大的数字num[i]应该比它前面的数字num[i-1]的rank大，所以我们可以将构造一条从num[i-1]指向num[i]的路径。得到所有路径之后，我们就得到一张图。
        此时所有入度为0的这批点（即最外围的点）没有任何约束关系（意思是没有rank必须必它们小的其他点），故他们的rank就可以赋值为1. 将这批点剥离之后，剩下的所有入度为0的点，他们的rank可以赋值为2，以此类推。

        但是有一种情况，就是同一行（列）中，如果有相同的数字，那么他们必须有相同的rank，因此在拓扑排序中需要把它们当做同一个点来处理。事实上，需要当做同一个点来处理的点可能有多个（而且会分布在不同的row或col里）。这就需要用union find来将这些点归并到同一个group里。同一个group的点在拓扑排序中只被处理一次，赋值相同的rank。

        如果用拓扑排序来做，此题比较棘手的地方就是在于处理indegree。我们知道，拓扑排序的每个回合，我们剥离入度为0的点。在这里，我们需要将所有属于同一个group的点的入度要累加在一块儿计算。当整个group的入度为0的时候，我们才将其加入队列；当它弹出队列的时候，该group的所有点都赋予相同的rank。
        然后这些点的剥离会给各自next的点减少一个入度，但注意，这些入度的自减也必须都统计在整个group上。

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
        
        int m = matrix.size(), n = matrix[0].size();
        Father.resize(m*n);
        
        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
                Father[i*n+j] = i*n+j;
                
        vector<vector<int>> next(m*n);
        vector<int> inDegree(m*n,0);
        
        // go each rows
        for (int i = 0; i < m; i++)
        {
            vector<std::pair<int,int>> temp;
            for (int j = 0; j < n; j++)
                temp.push_back({matrix[i][j], i*n+j});
            
            sort(temp.begin(), temp.end());
            for (int j = 1; j < n; j++)
            {
                if (temp[j].first > temp[j-1].first)
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
        
        // go each lines
        for (int j = 0; j < n; j++)
        {
            vector<std::pair<int,int>>temp;
            for (int i=0; i<m; i++)
                temp.push_back({matrix[i][j], i*n+j});

            sort(temp.begin(), temp.end());
            for (int i=1; i<m; i++)
            {
                if (temp[i].first > temp[i-1].first)
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
                        
        vector<vector<int>> group(m*n);
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
                if (Father[i*n+j]==i*n+j && inDegree[i*n+j]==0) q.push(i*n+j);
        
        int idx = 1;
        vector<vector<int>> rets(m,vector<int>(n,-1));

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
    vector<vector<int>> doit_topsort_disjoint_1(vector<vector<int>>& matrix) {

        vector<int>Father;
        int m = matrix.size();
        int n = matrix[0].size();
        Father.resize(m*n);
        
        std::function<int(int)> FindFather = [&](int x) {
            if (Father[x]!=x)
                Father[x] = FindFather(Father[x]);
            return Father[x];
        };
        
        std::function<void(int, int)> Union = [&](int x, int y) {
            x = Father[x];
            y = Father[y];
            if (x<y)
                Father[y] = x;
            else
                Father[x] = y;
        };

        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
                Father[i*n+j] = i*n+j;
                        
        for (int i=0; i<m; i++)
        {
            vector<std::pair<int,int>>temp;
            for (int j=0; j<n; j++)
                temp.push_back({matrix[i][j], i*n+j});
            sort(temp.begin(), temp.end());
            for (int j=1; j<n; j++)
            {
                if (temp[j].first == temp[j-1].first)
                {
                    if (FindFather(temp[j-1].second)!=FindFather(temp[j].second))
                        Union(temp[j-1].second, temp[j].second);
                }                    
            }
        }
        
        for (int j=0; j<n; j++)
        {
            vector<std::pair<int,int>>temp;
            for (int i=0; i<m; i++)
                temp.push_back({matrix[i][j], i*n+j});
            sort(temp.begin(), temp.end());
            for (int i=1; i<m; i++)
            {  
                if (temp[i].first==temp[i-1].first)
                {
                    if (FindFather(temp[i-1].second)!=FindFather(temp[i].second))
                        Union(temp[i-1].second, temp[i].second);
                }                    
            }
        }

        vector<std::pair<int,int>>nums;                
        vector<vector<int>>group(m*n);

        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
            {
                int root = FindFather(i*n+j);
                group[root].push_back(i*n+j);
                nums.push_back({matrix[i][j], i*n+j});
            }
        sort(nums.begin(), nums.end());

        vector<int>rowRank(m,0);
        vector<int>colRank(m,0);
        vector<vector<int>> rets(m, vector<int>(n));

        for (auto p: nums)
        {
            int val = p.first;
            int x = p.second/n;
            int y = p.second%n;
            if (rets[x][y]!=0) continue; 
            
            int r = 0;            
            for (auto p: group[Father[x*n+y]])
            {
                r = std::max(r, rowRank[p/n]);
                r = std::max(r, colRank[p%n]);
            }

            for (auto p: group[Father[x*n+y]])
            {
                rowRank[p/n] = r+1;
                colRank[p%n] = r+1;
                rets[p/n][p%n] = r+1;
            }
        }
        return rets;        
    }

    /*
        Approach 1: Sorting + BFS
        Intuition

        Let's recall the method used in the original Rank Transform of an Array. The idea is simple: sort the values in the array, and arrange the ranks from the lowest value to the highest value.

        It's natural to consider applying the same thing to our matrix: sort the values in the matrix, and arrange the ranks from the lowest one to the highest one.

        However, this method does not work. In this problem, we are only required to rank values according to row and column, and not to the whole matrix. The condition is looser.

        If we arrange the ranks according to the whole matrix, the resulting rank will be huger than what we want.

        For example, consider this case:


        Complexity Analysis

        Let MM be the number of rows in matrix and NN be the number of columns in matrix.

        Time Complexity: O(NMlog(NM)).

        We need \mathcal{O}(NM)O(NM) to iterate matrix to build graphs.
        We need \mathcal{O}(NM)O(NM) to iterate matrix to build value2index. We only visit points at most twice, since we skip points visited in BFS.
        We need \mathcal{O}(NM\log(NM))O(NMlog(NM)) to sort the keys in value2index, since there are at most \mathcal{O}(NM)O(NM) different keys.
        We need \mathcal{O}(NM)O(NM) to iterate value2index to build answer.
        Adding together, the time we needed is \mathcal{O}(NM\log(NM))O(NMlog(NM)).
        Space Complexity: \mathcal{O}(NM)O(NM).

        For graphs, we store \mathcal{O}(NM)O(NM) edges (viewing each point as an edge).
        For value2index, we store \mathcal{O}(NM)O(NM) points.
        For rowMax and columnMax, they have size of \mathcal{O}(M)O(M) and \mathcal{O}(N)O(N), respectively.
        In total, the size we needed is \mathcal{O}(NM)O(NM).
    */
    vector<vector<int>> doit_sort_bfs(vector<vector<int>>& matrix) {

        int m = matrix.size();
        int n = matrix[0].size();

        // link row to col, and link col to row
        unordered_map<int, unordered_map<int, vector<int>>> graphs;

        // graphs[v]: the connection graph of value v
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int v = matrix[i][j];
                auto& graph = graphs[v];

                // link i to j, and link j to i
                graph[i].push_back(~j);
                graph[~j].push_back(i);
            }
        }

        // put points into `value2index` dict, grouped by connection
        // use ordered map to help us sort the key automatically
        map<int, vector<vector<pair<int, int>>>> value2index;
        // mark whether put into `value2index` or not
        vector<vector<int>> seen(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (seen[i][j] == 1) {
                    continue;
                }
                seen[i][j] = 1;
                int v = matrix[i][j];
                auto graph = graphs[v];
                // store visited row and col
                unordered_set<int> rowcols{i, ~j};
                // start bfs
                queue<int> q;
                q.push(i);
                q.push(~j);
                while (!q.empty()) {
                    auto node = q.front();
                    q.pop();
                    for (int rowcol : graph[node]) {
                        if (rowcols.count(rowcol) == 0) {
                            rowcols.insert(rowcol);
                            q.push(rowcol);
                        }
                    }
                }
                // transform rowcols into points
                vector<pair<int, int>> points;
                for (auto rowcol : rowcols) {
                    for (auto k : graph[rowcol]) {
                        if (k >= 0) {
                            points.push_back({k, ~rowcol});
                            seen[k][~rowcol] = 1;
                        } else {
                            points.push_back({rowcol, ~k});
                            seen[rowcol][~k] = 1;
                        }
                    }
                }
                value2index[v].push_back(points);
            }
        }

        // the required rank matrix
        vector<vector<int>> answer(m, vector<int>(n));
        vector<int> rowMax(m);  // rowMax[i]: the max rank in i row
        vector<int> colMax(n);  // colMax[j]: the max rank in j col
        for (auto v : value2index) {
            // update by connected points with same value
            for (auto points : v.second) {
                int rank = 1;
                for (auto point : points) {
                    rank =
                        max(rank,
                            max(rowMax[point.first], colMax[point.second]) + 1);
                }
                for (auto point : points) {
                    answer[point.first][point.second] = rank;
                    // update rowMax and colMax
                    rowMax[point.first] = max(rowMax[point.first], rank);
                    colMax[point.second] = max(colMax[point.second], rank);
                }
            }
        }
        return answer;
    }

    /*
        Approach 2: Sorting + DFS

        Intuition

        DFS is similar to BFS but differs in the order of searching. In most cases, when the search space is not huge, you can replace BFS with DFS.

        In approach 1, we used BFS to find out the connected parts of each point. Now, we use DFS instead.

        Algorithm

        Step 1: Initialize graphs for different values. Iterate matrix and link the rows and columns in the corresponding graph.

        Step 2: Initialize a value2index map to store connected parts.

        This map will contain the value - index mapping. In the index part, separate points to put the connected points in the same array, and to put non-connected points in different arrays. (one array represents a connected part.)
        Therefore, value2index should be in this form: {v1: [[point1, point2, ...], [point11, point12, ...], ...], v2: ...}, where point1, point2, ... are connected, and point11, point21, ... are also connected, but none of the points from different array are connected.
        Step 3: Fill in value2index map by iterating over the matrix again.

        For each point, use DFS to find out all the other connected points. Put all of them into value2index as an array.
        Remember to mark those points visited to avoid duplicate additions.
        Step 4: Sort the keys in value2index (i.e., all values in matrix).

        Step 5: Initialize our answer matrix. Iterate value2index in the order of sorted keys to fill in answer.

        For a given key (i.e., a value in matrix), we fill in answer by connected parts (i.e., one array).
        Note that for points in the same connected part, they share the same rank.
        For a connected part, Find out the minimum possible rank and update that rank.
        To reduce the time for searching the minimum possible rank, we need two arrays to record the maximum rank of each row and each column, respectively.
        Step 6: Return answer.
    */
    void dfs(int node, unordered_map<int, vector<int>>& graph, unordered_set<int>& rowcols) {
        // the dfs function to find connected parts
        // we send a result vector `points` as input to avoid return copy
        rowcols.insert(node);
        for (auto rowcol : graph[node]) {
            if (rowcols.count(rowcol) == 0) {
                dfs(rowcol, graph, rowcols);
            }
        }
    }

    vector<vector<int>> doit_sort_dfs(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        // link row to col, and link col to row
        unordered_map<int, unordered_map<int, vector<int>>> graphs;
        // graphs[v]: the connection graph of value v
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int v = matrix[i][j];
                auto& graph = graphs[v];
                // link i to j, and link j to i
                graph[i].push_back(~j);
                graph[~j].push_back(i);
            }
        }

        // put points into `value2index` dict, grouped by connection
        // use ordered map to help us sort the key automatically
        map<int, vector<vector<pair<int, int>>>> value2index;
        // mark whether put into `value2index` or not
        vector<vector<int>> seen(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (seen[i][j] == 1) {
                    continue;
                }
                seen[i][j] = 1;
                int v = matrix[i][j];
                auto graph = graphs[v];
                // use dfs to find the connected parts
                // store visited row and col
                unordered_set<int> rowcols;
                dfs(i, graph, rowcols);
                dfs(~j, graph, rowcols);
                // transform rowcols into points
                vector<pair<int, int>> points;
                for (auto rowcol : rowcols) {
                    for (auto k : graph[rowcol]) {
                        if (k >= 0) {
                            points.push_back({k, ~rowcol});
                            seen[k][~rowcol] = 1;
                        } else {
                            points.push_back({rowcol, ~k});
                            seen[rowcol][~k] = 1;
                        }
                    }
                }
                value2index[v].push_back(points);
            }
        }

        // the required rank matrix
        vector<vector<int>> answer(m, vector<int>(n));
        vector<int> rowMax(m);  // rowMax[i]: the max rank in i row
        vector<int> colMax(n);  // colMax[j]: the max rank in j col
        for (auto v : value2index) {
            // update by connected points with same value
            for (auto points : v.second) {
                int rank = 1;
                for (auto point : points) {
                    rank =
                        max(rank,
                            max(rowMax[point.first], colMax[point.second]) + 1);
                }
                for (auto point : points) {
                    answer[point.first][point.second] = rank;
                    // update rowMax and colMax
                    rowMax[point.first] = max(rowMax[point.first], rank);
                    colMax[point.second] = max(colMax[point.second], rank);
                }
            }
        }
        return answer;
    }

    /*
        Approach 3: Sorting + Union-Find
        Intuition

        As we mentioned in approach 1, Union-Find (or UF, Disjoint Set) can be applied to find the connected parts.

        Since Union-Find is not the essence of this problem (and considering the length of the article), we will not provide a very detailed explanation of Union-Find here. 
        You can find some tutorials on other problems that require Union-Find, such as Redundant Connection or Most Stones Removed with Same Row or Column.

        Now, we will have a quick review of Union-Find, and explain how we can use Union-Find to find the connected parts.

        Similar to approach 1, we view the matrix points as edges that connect rows and columns.

        As we know, we can view Union-Find as a forest-like structure (forest represents many trees). For example:

        Algorithm

        Step 1: Implement find and union for Union-Find.
        find receives an integer and returns the "root" of that integer.
        union accepts two integers and merges them into the same union.
    
        Step 2: Initialize Union-Finds (UFs) for different values. Iterate matrix and union the rows and columns in the corresponding Union-Find.

        Step 3: Initialize a value2index map to store connected parts.
        This map will contain the value - index mapping. In the index part, separate points to put the connected points in the same array, and to put non-connected points in different arrays. (one array represents a connected part.)
        We mark those array by the "root" of points in Union-Find (so value2index is actually a nested map).
        Therefore, value2index should be in this form: {v1: {root1: [point1, point2, ...], root2: [point11, point12, ...], ...}, v2: ...}, where point1, point2, ... are connected, and point11, point21, ... are also connected, but none of points from different set are connected.
    
        Step 4: Fill in value2index map by iterate matrix again. For a point, use find to calculate its "root". Put the point in the corresponding set.
    
        Step 5: Sort the keys in value2index (i.e., all values in matrix).

        Step 6: Initialize our answer matrix. Iterate value2index in the order of sorted keys to fill in answer.

        For a given key (i.e., a value in matrix), we fill in answer by connected parts (i.e., one array).
        Note that for points in the same connected part, they share the same rank.
        For a connected part, Find out the minimum possible rank and update that rank.
        To reduce the time for searching the minimum possible rank, we need two arrays to record the maximum rank of each row and each column, respectively.
    
        Step 7: Return answer.
    */
    
    // implement find and union
    int find(unordered_map<int, int> &UF, int x) {
        if (x != UF[x]) {
            UF[x] = find(UF, UF[x]);
        }
        return UF[x];
    }

    // the name "merge" is used here since "union" is a reserved type in c++
    void merge(unordered_map<int, int> &UF, int x, int y) {
        if (UF.count(x) == 0) {
            UF[x] = x;
        }
        if (UF.count(y) == 0) {
            UF[y] = y;
        }
        UF[find(UF, x)] = find(UF, y);
    }

    vector<vector<int>> doit_sort_disjoint(vector<vector<int>>& matrix) {
        
        int m = matrix.size(), n = matrix[0].size();

        // link row and col together
        unordered_map<int, unordered_map<int, int>> UFs;

        //  UFs[v]: the Union-Find of value v
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int v = matrix[i][j];
                // union i to j
                merge(UFs[v], i, ~j);
            }
        }

        // put points into `value2index` dict, grouped by connection
        map<int, unordered_map<int, vector<std::pair<int, int>>>> value2index;
        // use ordered map to help us sort the key automatically
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int v = matrix[i][j];
                int f = find(UFs[v], i);
                value2index[v][f].push_back({i, j});
            }
        }

        // the required rank matrix
        vector<vector<int>> answer(m, vector<int>(n));
        vector<int> rowMax(m);  // rowMax[i]: the max rank in i row
        vector<int> colMax(n);  // colMax[j]: the max rank in j col

        for (auto v : value2index) {
            // update by connected points with same value
            for (auto entries : v.second) {

                auto points = entries.second;
                int rank = 1;

                for (auto point : points)
                    rank = std::max(rank, std::max(rowMax[point.first], colMax[point.second]) + 1);

                for (auto point : points) {
                    answer[point.first][point.second] = rank;
                    // update rowMax and colMax
                    rowMax[point.first] = std::max(rowMax[point.first], rank);
                    colMax[point.second] = std::max(colMax[point.second], rank);
                }
            }
        }

        return answer;
    }
};