/*
 305. Number of Islands II
 
 A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land.
 Given a list of positions to operate, count the number of islands after each addLand operation.
 An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
 You may assume all four edges of the grid are all surrounded by water.

 Example:

 Input: m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]]
 Output: [1,1,2,3]
 Explanation:

 Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

 0 0 0
 0 0 0
 0 0 0
 Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

 1 0 0
 0 0 0   Number of islands = 1
 0 0 0
 Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

 1 1 0
 0 0 0   Number of islands = 1
 0 0 0
 Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

 1 1 0
 0 0 1   Number of islands = 2
 0 0 0
 Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

 1 1 0
 0 0 1   Number of islands = 3
 0 1 0
 Follow up:

 Can you do it in time complexity O(k log mn), where k is the length of the positions?
 */
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::unordered_set;
using std::unordered_map;
using std::vector;


class NumIslands2 {

    /*
        305.Number-of-Islands-II
        设置所有点的初始Father为-1，表示海洋。

        然后依次遍历每一块新陆地，最开始标记它的Root为自身，然后count++。依次考察这个新陆地相邻的四块：如果相邻的是陆地，并且新陆地和老陆地的Root不同，那么说明这是需要合并的两个集合，于是count--，并且将新陆地与旧陆地进行Union。
        最终实时输出count。

        有一个corner case是，positions里面可能会包含重复的同一块陆地。所以每遍历一块新陆地的时候，得先看看是否已经访问过了，已经访问过了就不要再重新标记Root，否则会出错。
    */
    vector<int>Father;
    
    int FindSet(int x)
    {
        if (x!=Father[x])
            Father[x]=FindSet(Father[x]);
        return Father[x];
    }
    
    void Union(int x, int y)
    {
        x=Father[x];
        y=Father[y];
        
        if (x<y)
            Father[y]=x;
        else
            Father[x]=y;        
    }

    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) 
    {
        Father.resize(m*n);
        for (int i=0; i<m*n; i++)         
             Father[i]=-1;
        
        vector<std::pair<int,int>> dir = {{1,0},{-1,0},{0,1},{0,-1}};
        int count=0;
        vector<int> result;
        
        for (int i=0; i<positions.size(); i++)
        {
            int x=positions[i][0];
            int y=positions[i][1];
            if (Father[x*n+y]!=-1)
            {
                result.push_back(result.back());
                continue;
            }
            
            Father[x*n+y]=x*n+y;
            count+=1;
            
            for (int k=0; k<4; k++)
            {
                int a=x+dir[k].first;
                int b=y+dir[k].second;
                if (a<0||a>=m||b<0||b>=n)
                    continue;
                if (Father[a*n+b]==-1)
                    continue;
                if (FindSet(a*n+b)!=FindSet(x*n+y))
                {
                    count--;
                    Union(a*n+b,x*n+y);
                }
            }
            result.push_back(count);
        }
        
        return result;
    }

public:
    
    /*
     
     Approach #3: Union Find (aka Disjoint Set) [Accepted]
     Intuition

     Treat the 2d grid map as an undirected graph (formatted as adjacency matrix) and there is an edge between two horizontally or vertically adjacent nodes of value 1,
     then the problem reduces to finding the number of connected components in the graph after each addLand operation.

     Algorithm

     Make use of a Union Find data structure of size m*n to store all the nodes in the graph and initially each node's parent value is set to -1 to represent an empty graph.
     Our goal is to update Union Find with lands added by addLand operation and union lands belong to the same island.

     For each addLand operation at position (row, col), union it with its adjacent neighbors if they belongs to some islands, if none of its neighbors belong to any islands,
     then initialize the new position as a new island (set parent value to itself) within Union Find.

     For detailed description of Union Find (implemented with path compression and union by rank), you can refer to this
     
     
     */
    
    vector<int> doit_disjoint(int m, int n, vector<vector<int>>& positions) {
        
        vector<int> parent(m*n, -1);
        vector<int> res;
        int land = 0;
        
        auto find = [&parent](int id) {
            while (parent[id] != id) {
                parent[id] = parent[parent[id]];
                id = parent[id];
            }
            return id;
        };
        

        for (auto& c: positions) {
            
            int x = c[0], y = c[1];
            int id = x * n + y;
            
            parent[id] = id;
            land++;
            
            for (auto delta : vector<vector<int>>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
                
                int x1 = x + delta[0], y1 = y + delta[1];
                int nid = x1 * n + y1;
                if (x1 >= 0 && x1 < m && y1 >= 0 && y1 < n && parent[nid] != -1) {
                    
                    int rootid = find(nid);
                    if (rootid != id) {
                        parent[rootid] = id;
                        land--;
                    }
                }
            }
            res.push_back(land);
        }
        
        return res;
    }

    vector<short> parent;
    vector<short> rank;
    int m_count;
    
    int find(int i) {
        if (i != parent[i])
            parent[i] = find(parent[i]);
        return parent[i];
    }
    
    void union_find(int a, int b) {
        //std::cout << "union a " << a << " b " << b << std::endl;
        int root_a = find(a);
        int root_b = find(b);
        //std::cout << "root " << root_a << " " << root_b << std::endl;
        if (root_a != root_b) {
            if (rank[root_a] > rank[root_b]) {
                parent[root_b] = root_a;
            } else if (rank[root_a] < rank[root_b]) {
                parent[root_a] = root_b;
            } else {
                parent[root_b] = root_a;
                rank[root_a]++;
            }
            m_count--;
            //std::cout << "mcount " << m_count << std::endl;
        }
    }
    
    vector<int> doit_disjoint_1(int m, int n, vector<vector<int>>& positions) {
        parent.resize(m*n, -1);
        rank.resize(m*n, 0);
        vector<int> ret;
        m_count = 0;
        
        for (auto & position : positions) {
            int r = position[0];
            int c = position[1];
            int id = r*n + c;
            if (parent[id] != -1) {
                ret.push_back(m_count);
                continue;
            }
            
            m_count++;
            parent[id] = id;
            
            // left
            int left_id = r*n + (c-1);
            if (c > 0 && parent[left_id] != -1)
                union_find(id, left_id);
            
            // right
            int right_id = r*n + (c+1);
            if (c < n-1 && parent[right_id] != -1)
                union_find(id, right_id);
            
            // up
            int up_id = (r-1)*n + (c);
            if (r > 0 && parent[up_id] != -1)
                union_find(id, up_id);
            
            // down
            int down_id = (r+1)*n + (c);
            if (r < m-1 && parent[down_id] != -1)
                union_find(id, down_id);
            
            ret.push_back(m_count);
        }
        
        return ret;
    }

    /*
        Approach #2: (Ad hoc) [Accepted]
        Algorithm

        Use a HashMap to map index of a land to its island_ID (starting from 0). For each addLand operation at position (row, col), 
        check if its adjacent neighbors are in the HashMap or not and put the island_ID of identified neighbors into a set (where each element is unique):

        if the set is empty, then the new land at position (row, col) forms a new island (monotonically increasing island_ID by 1);

        if the set contains only one island_ID, then the new land belongs to an existing island and island_ID remains unchanged;

        if the set contains more than one island_ID, then the new land bridges these separate islands into one island, we need to iterate through the HashMap to update this information (time consuming!)
         and decrease the number of island appropriately.


        Complexity Analysis

        Time complexity : O(L^2)O(L 
        2
        ), for each operation, we have to traverse the entire HashMap to update island id and the number of operations is LL.

        Space complexity : O(L)O(L) for the HashMap.

        P.S. C++ solution was accepted with 1409 ms runtime, but Java solution got an TLE (Time Limit Exceeded).
    */
    vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
        vector<int> ans;
        unordered_map<int, int> land2id; // land index : island ID
        int num_islands = 0;
        int island_id = 0;
        for (auto pos : positions) {
        int r = pos.first;
        int c = pos.second;
        // check pos's neighbors to see if they are in the existing islands or not
        unordered_set<int> overlap; // how many existing islands overlap with 'pos'
        if (r - 1 >= 0 && land2id.count((r-1) * n + c)) overlap.insert(land2id[(r-1) * n + c]);
        if (r + 1 < m && land2id.count((r+1) * n + c)) overlap.insert(land2id[(r+1) * n + c]);
        if (c - 1 >= 0 && land2id.count(r * n + c - 1)) overlap.insert(land2id[r * n + c - 1]);
        if (c + 1 < n && land2id.count(r * n + c + 1)) overlap.insert(land2id[r * n + c + 1]);

        if (overlap.empty()) { // no overlap
            ++num_islands;
            land2id[r * n + c] = island_id++; // new island
        } else if (overlap.size() == 1) { // one overlap, just append
            auto it = overlap.begin();
            land2id[r * n + c] = *it;
        } else { // more than 1 overlaps, merge
            auto it = overlap.begin();
            int root_id = *it;
            for (auto& kv : land2id) { // update island id
            if (overlap.count(kv.second)) kv.second = root_id;
            }
            land2id[r * n + c] = root_id;
            num_islands -= (overlap.size() - 1);
        }

        ans.push_back(num_islands);
        }

        return ans;
    }
};
