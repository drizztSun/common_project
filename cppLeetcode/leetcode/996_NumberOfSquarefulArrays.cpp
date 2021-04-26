/*

996. Number of Squareful Arrays
 
Given an array A of non-negative integers, the array is squareful if for every pair of adjacent elements, their sum is a perfect square.

Return the number of permutations of A that are squareful.  Two permutations A1 and A2 differ if and only if there is some index i such that A1[i] != A2[i].

 

Example 1:

Input: [1,17,8]
Output: 2
Explanation: 
[1,8,17] and [17,8,1] are the valid permutations.
Example 2:

Input: [2,2,2]
Output: 1
 

Note:

1 <= A.length <= 12
0 <= A[i] <= 1e9
 
 */

#include <vector>
#include <cmath>
#include <unordered_map>
#include <functional>
#include <algorithm>

using std::vector;
using std::unordered_map;


class NumSquarefulPerms {

    /*
        996.Number-of-Squareful-Arrays
        此题可以理解成一张图的路径搜索问题。我们提前处理所有的pair，对于相加是平方数的两个元素，我们就认为它们之间有一条边。我们的任务就是找出所有的路径，能够走遍所有的点。

        考虑到题目需要穷举所有的路径，并且数据规模异常得小，大概率这是一个NP问题，可以用暴力的深度搜索，和473，698都很相似。这类题目都需要用visited来记录已经访问过的元素来避免重复。

        特别注意的是，本题要求避免“长得一样”的重复路径，需要有剪支的操作。比如对于数列1,2,2,2,3,4,我们想取不重复的permutation。当我们考察完1,2,X,X,X,X之后，需要回溯考虑第二个元素的其他候选。
        我们发现，如果第二个位置再选其他的“2”，就会又完全重复之前的搜索。尽管是两个不同的“2”，但这样的两条路径被认为是重复。为了剪枝，我们在从cur开始寻找下一层深度的节点时，可以将所有的候选节点事先排个序，如果候选节点B和它之前考察过的候选节点A相同，那么我们就略过对候选节点B的考察。

        另外一个细节就是如何判断一个数是否是平方数？正确的做法是if (sqrt(x)==(int)sqrt(x))
    */
    vector<vector<int>>next;
    vector<int>visited;
    int n;
    int ret = 0;

    int numSquarefulPerms(vector<int>& A) 
    {
        n = A.size();
        next.resize(n);
        visited.resize(n);
        std::sort(A.begin(), A.end());
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
            {
                if (i==j) continue;
                if (sqrt(A[i]+A[j])==(int)sqrt(A[i]+A[j]))
                    next[i].push_back(j);
            }
        for (int i=0; i<n; i++)
        {
            if (i>0 && A[i]==A[i-1]) continue;
            visited[i] = 1;
            dfs(A, i, 1);
            visited[i] = 0;
        }
        return ret;
    }

    void dfs(vector<int>&A, int cur, int count)
    {
        if (count==n)
        {
            ret++;
            return;
        }

        int last = -1;
        for (auto i: next[cur])
        {
            if (visited[i]==1) continue;
            if (A[i]==last) continue;
            visited[i] = 1;
            last = A[i];
            dfs(A, i, count+1);
            visited[i] = 0;
        }
    }


public:

    int doit_dfs_backtracking_2(vector<int>& A) 
    {
        
        int n = A.size();
        int ret = 0;

        vector<vector<int>>next(n);
        vector<int>visited(n);
        std::sort(A.begin(), A.end());

        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
            {
                if (i==j) continue;
                if (sqrt(A[i]+A[j])==(int)sqrt(A[i]+A[j]))
                    next[i].push_back(j);
            }

        std::function<void(int, int)> dfs = [&](int cur, int count)
        {
            if (count==n){
                ret++;
                return;
            }

            int last = -1;
            for (auto i: next[cur])
            {
                if (visited[i]==1) continue;
                if (A[i]==last) continue;
                visited[i] = 1;
                last = A[i];
                dfs(i, count+1);
                visited[i] = 0;
            }
        };

        for (int i=0; i<n; i++)
        {
            if (i>0 && A[i]==A[i-1]) continue;
            visited[i] = 1;
            dfs(i, 1);
            visited[i] = 0;
        }

        return ret;
    }


    int numSquarefulPerms(vector<int>& A) {
        
        int n = A.size();
        vector<vector<int>> pairs(n);
        vector<int> visible(n, 0);
        std::sort(begin(A), end(A));
        
        for(int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (sqrt(A[i]+A[j]) == int(sqrt(A[i]+A[j])))
                    pairs[i].push_back(j);
            }
        }
        
        int ans = 0;
        
        std::function<void(int, int)> dfs = [&](int index, int count) {
            
            if (count == n) {
                ans++;
                return;
            }
            
            int last = -1;
            for (auto i: pairs[index]) {
                
                if (visible[i] == 1) continue;
                if (last == A[i]) continue;
                
                last = A[i];
                visible[i] = 1;
                
                dfs(i, count+1);
                
                visible[i] = 0;
                
            }
            
            
        };
        
        for (int i = 0; i < A.size(); i++) {
            if (i == 0 || A[i] != A[i-1]) {
                visible[i] = 1;
                dfs(i, 1);
                visible[i] = 0;
            }
        }
        
        return ans;
    }
    
public:

    int doit_dfs_backtracking(vector<int>&& A) {
        
        unordered_map<int, int> cnt;
        for (auto c: A)
            cnt[c]++;
        
        unordered_map<int, vector<int>> graph;
        for (auto x : cnt)
            for (auto y : cnt) {
                int x1 = x.first, y1 = y.first;
                if (pow(int(pow(x1 + y1, 0.5) + 0.5), 2) == x1 + y1)
                    graph[x1].push_back(y1);
            }
        
        
        std::function<int(int, int)> search= [&](int x, int steps) {
                
            cnt[x]--;
            int ans = 1;
            if (steps != 0) {
                ans = 0;
                for (auto y : graph[x])
                    if (cnt[y])
                        ans += search(y, steps - 1);
            }
            cnt[x]++;
            return ans;
        };
        
        int ans = 0;
        for (auto c : cnt) {
            ans += search(c.first, A.size() - 1);
        }
        
        return ans;
    }
};

/*
 The most important point in the solution to this problem is that there are at most 2 edges to try for deletion.

 If there is a vertex with 2 parents, we have to erase one of the 2 edges pointing towards this vertex:
 We try to erase the second, if we found later an inconsistency we search back the first one.
 If there is also a cycle we have to eliminate the (last) one that belongs to the cycle.
 else, we return the last edge encountered in the cycle.
 */
class Solution {
public:
    int find(vector<int>& par, int i){
        return (i == par[i]) ? i : (par[i]=find(par, par[i]));
    }
    bool test(vector<int>& edge, vector<vector<int>>& edges){
        vector<int> par(edges.size());
        // iota(par.begin(), par.end(), 0);
        for(auto& e: edges){
            if(e[0] == edge[0] && e[1] == edge[1])
                continue;
            int a = find(par, e[0]-1), b = find(par, e[1]-1);
            if(a == b)
                return false;
            par[b] = a;
        }
        int p = find(par, 0);
        for(int i = 1; i < par.size(); ++i){
            if(p != find(par, i))
                return false;
        }
        return true;
    }
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        if(edges.size() == 0)
            return vector<int>();
        vector<int> par(edges.size()), anc(edges.size());
        // iota(par.begin(), par.end(), 0);
        // iota(anc.begin(), anc.end(), 0);
        
        vector<int> res;
        for(auto& edge: edges){
            if(par[edge[1]-1] != edge[1] - 1){
                // parent occursion: [par[edge[1]-1]+1, edge[1]] or edge
                if(test(edge, edges))
                    return edge;
                else
                    return vector<int>{par[edge[1]-1]+1, edge[1]};
            }
            
            int a = find(anc, edge[0]-1), b = find(anc, edge[1]-1);
            if(a == b){
                res = edge;
            }
            else{
                par[edge[1]-1] = edge[0]-1;
                anc[b] = a;
            }
        }
        return res;
    }
};