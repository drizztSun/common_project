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
using std::vector;


class NumIslands2 {
    
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
};
