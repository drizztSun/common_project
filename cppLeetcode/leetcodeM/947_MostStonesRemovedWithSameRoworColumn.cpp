/*
947. Most Stones Removed with Same Row or Column

On a 2D plane, we place n stones at some integer coordinate points. Each coordinate point may have at most one stone.

A stone can be removed if it shares either the same row or the same column as another stone that has not been removed.

Given an array stones of length n where stones[i] = [xi, yi] represents the location of the ith stone, return the largest possible number of stones that can be removed.

 

Example 1:

Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5
Explanation: One way to remove 5 stones is as follows:
1. Remove stone [2,2] because it shares the same row as [2,1].
2. Remove stone [2,1] because it shares the same column as [0,1].
3. Remove stone [1,2] because it shares the same row as [1,0].
4. Remove stone [1,0] because it shares the same column as [0,0].
5. Remove stone [0,1] because it shares the same row as [0,0].
Stone [0,0] cannot be removed since it does not share a row/column with another stone still on the plane.
Example 2:

Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
Output: 3
Explanation: One way to make 3 moves is as follows:
1. Remove stone [2,2] because it shares the same row as [2,0].
2. Remove stone [2,0] because it shares the same column as [0,0].
3. Remove stone [0,2] because it shares the same row as [0,0].
Stones [0,0] and [1,1] cannot be removed since they do not share a row/column with another stone still on the plane.
Example 3:

Input: stones = [[0,0]]
Output: 0
Explanation: [0,0] is the only stone on the plane, so you cannot remove it.
 

Constraints:

1 <= stones.length <= 1000
0 <= xi, yi <= 104
No two stones are at the same coordinate point.

*/
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;

class RemoveStones {

    /*
                947.Most-Stones-Removed-with-Same-Row-or-Column
        本题的核心就是找出这样的规律：将所有同行或者同列关系的石头两两归并，最终都融为一个group。在这一个group里面，依次取度为1的石头（即同行或同列还有剩余的石头），按照规则可以一直取到整个组只剩下一个为止。

        因为每个group都只剩一个石头，所以可以移走的石头数目，就等于总共的石头数目减去group的数目。
    */
    unordered_map<int,int>Father;
    unordered_map<int,vector<int>>MapX;
    unordered_map<int,vector<int>>MapY;
    int N = 10000;
public:
    int removeStones(vector<vector<int>>& stones) 
    {
        for (auto x:stones)
        {
            int i = x[0];
            int j = x[1];
            int id = i*N+j;
            Father[id] = id;
            MapX[i].push_back(id);
            MapY[j].push_back(id);
        }
        
        for (auto a: MapX)
        {
            int id0 = a.second[0];
            for (int i=1; i<a.second.size(); i++)
            {
                int id = a.second[i];
                if (FindFather(id0)!=FindFather(id))
                    Union(id0, id);                
            }
        }
        
        for (auto a: MapY)
        {
            int id0 = a.second[0];
            for (int i=1; i<a.second.size(); i++)
            {
                int id = a.second[i];
                if (FindFather(id0)!=FindFather(id))
                    Union(id0, id);                
            }
        }
        
        unordered_set<int>Set;
        for (auto x: stones)
        {
            int id = x[0]*N+x[1];
            int id0 = FindFather(id);
            Set.insert(id0);
        }
        
        return stones.size() - Set.size();
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
        if (x<=y)
            Father[y] = x;
        else
            Father[x] = y;
     }

public:

    /*
        Approach 2: Union-Find
        Intuition

        As in Approach 1, we will need to consider components of an underlying graph. A "Disjoint Set Union" (DSU) data structure is ideal for this.

        We will skip the explanation of how a DSU structure is implemented. Please refer to https://leetcode.com/problems/redundant-connection/solution/ for a tutorial on DSU.

        Algorithm

        Let's connect row i to column j, which will be represented by j+10000. The answer is the number of components after making all the connections.

        Note that for brevity, our DSU implementation does not use union-by-rank. This makes the asymptotic time complexity larger.


        Complexity Analysis

        Time Complexity: O(NlogN), where N is the length of stones. (If we used union-by-rank, this can be O(N * \alpha(N))O(N∗α(N)), where \alphaα is the Inverse-Ackermann function.)

        Space Complexity: O(N).
    */
    int doit_disjoint(vector<vector<int>>& stones) {
        
        int n = stones.size();
        vector<int> parent(20000, 0);
        
        for (int i = 0; i < 20000; i++)
            parent[i] = i;
        
        auto find = [&](int node) {
            while (parent[node] != node) {
                parent[node] = parent[parent[node]];
                node = parent[node];
            }
            return node;
        };
        
        auto merge = [&](int a, int b) {
            int pa = find(a), pb = find(b);
            if (pa < pb)
                parent[pb] = pa;
            else
                parent[pa] = pb;
        };
        
        for (const auto& c: stones) {
            merge(c[0], c[1] + 10000);
        }
        
        unordered_set<int> ones;
        for (const auto& c: stones) {
            ones.insert(find(c[0]));
        }
        
        return n - ones.size();
    }

    // O(n^2)
    int doit_disjoint(vector<vector<int>>& stones) {

        int n = stones.size();
        vector<int> parent(n, 0);
        
        for (int i = 0; i < stones.size(); i++)
            parent[i] = i;
        
        auto find = [&](int node) {
            while (parent[node] != node) {
                parent[node] = parent[parent[node]];
                node = parent[node];
            }
            return node;
        };
        
        auto merge = [&](int a, int b) {
            int pa = find(a), pb = find(b);
            if (pa < pb)
                parent[pb] = pa;
            else
                parent[pa] = pb;
        };
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++) {
                if (stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1])
                    merge(i, j);
            }
        
        unordered_map<int, int> sizes;
        for (int i = 0; i < n; i++) {
            sizes[find(i)]++;
        }
        
        int ans = 0;
        for (auto c: sizes) {
            if (c.second > 1) ans += c.second-1;
        }
        
        return ans;
    }    
}