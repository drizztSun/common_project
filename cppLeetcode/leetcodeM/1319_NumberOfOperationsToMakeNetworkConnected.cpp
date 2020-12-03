/*
 1319. Number of Operations to Make Network Connected
 
 There are n computers numbered from 0 to n-1 connected by ethernet cables connections forming a network where connections[i] = [a, b]
 represents a connection between computers a and b. Any computer can reach any other computer directly or indirectly through the network.

 Given an initial computer network connections. You can extract certain cables between two directly connected computers,
 and place them between any pair of disconnected computers to make them directly connected. Return the minimum number of times
 you need to do this in order to make all the computers connected. If it's not possible, return -1.

  

 Example 1:



 Input: n = 4, connections = [[0,1],[0,2],[1,2]]
 Output: 1
 Explanation: Remove cable between computer 1 and 2 and place between computers 1 and 3.
 Example 2:



 Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
 Output: 2
 Example 3:

 Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
 Output: -1
 Explanation: There are not enough cables.
 Example 4:

 Input: n = 5, connections = [[0,1],[0,2],[3,4],[2,3]]
 Output: 0
  

 Constraints:

 1 <= n <= 10^5
 1 <= connections.length <= min(n*(n-1)/2, 10^5)
 connections[i].length == 2
 0 <= connections[i][0], connections[i][1] < n
 connections[i][0] != connections[i][1]
 There are no repeated connections.
 No two computers are connected by more than one cable.
 
 */
#include <vector>

using std::vector;

class NumberOfOperationsMakeNetworkConnected {
    
    class UnionFind{
        int num;
        int numComponents;
        vector<int> rank;
        vector<int> parent;
    
    public:
    
        UnionFind(int n){
            num = n;
            numComponents = n;
            rank = vector<int>(n, 0);
            parent = vector<int>(n);
            
            for(int i = 0; i<n; i++)
                 parent[i] = i;
        }
        
        int size(){return num;}
        
        int components(){return numComponents;}
        
        int find(int p){
            while(p != parent[p]){
                parent[p] = parent[parent[p]];
                p = parent[p];
            }
            return p;
        }
        
        void unionn(int p, int q){
            int rootp = find(p); int rootq = find(q);
            if(rootp == rootq)
                return;
            
            if(rank[rootp] < rank[rootq])
                parent[rootp] = rootq;
            else{
                parent[rootq] = rootp;
                if(rank[rootp] == rank[rootq]){rank[rootp]++;}
            }
            
            numComponents--;
        }
        
        int connected(int p, int q){
            return find(p) == find(q);
        }
        
    };
    
public:

    int doit_disjoint(int n, vector<vector<int>>& connections) {
        
        int redundant = 0, required = 0;
        UnionFind uf(n);
        
        for(int i = 0; i<connections.size(); i++) {
            if (uf.find(connections[i][0]) == uf.find(connections[i][1]))
                redundant++;
            else
                uf.unionn(connections[i][0], connections[i][1]);
        }
        
        return uf.components()-1 <= redundant ? uf.components()-1 : -1;
    }

};
