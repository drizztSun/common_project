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
#include <unordered_map>

using std::unordered_map;
using std::vector;

class NumberOfOperationsMakeNetworkConnected {

    /*
        1319.Number-of-Operations-to-Make-Network-Connected
        首先想到的是，属于同一组互联的多个计算机可能会有一些冗余的连接线。那么冗余多少呢？很简单，有N个计算机已经互联的话，那么只需要N-1条线就可以保证它们互联，多余的线其实都是可以拔掉的，我们可以改用它来连接不同局域网。

        接下来，我们知道，如果将M个不相连的局域网都互通，那么需要M-1条线。

        所以总体的算法是：用Union Find的方法来数一下有M个局域网；再计算每个局域网里有多少冗余的传输线并相加。如果所有冗余的传输线数目K>=M-1的话，那么就可以把所有的计算机都连接起来。
    */
     vector<int>Father;
public:
    int makeConnected(int n, vector<vector<int>>& connections) 
    {
        Father.resize(n);
        vector<int>edges(n,0);
        unordered_map<int,int>cables;
        unordered_map<int,int>elements;

        for (int i=0; i<n; i++)
            Father[i] = i;

        for (auto& edge: connections)
        {
            if (FindFather(edge[0])!=FindFather(edge[1]))
                Union(edge[0],edge[1]);
            edges[edge[0]]+=1;
            edges[edge[1]]+=1;
        }

        for (int i=0; i<n; i++)
        {
            Father[i] = FindFather(i);
            cables[Father[i]] += edges[i];
            elements[Father[i]] += 1;
        }

        int redundant = 0;
        int islands = cables.size();
        for (auto x: cables)
        {
            int root = x.first;
            redundant += cables[root]/2+1-elements[root];
        }

        if (redundant>=islands-1)
            return islands-1;
        else 
            return -1;        
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
        if (x<y)
            Father[y] = x;
        else
            Father[x] = y;
    }


    
    struct UnionFind{
        int num;
        int numComponents;
        vector<int> parent;
    
        UnionFind(int n){
            num = n;
            numComponents = n;
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
            int rootp = find(p), rootq = find(q);
            if(rootp == rootq) return;
            
            if(rootp < rootq)
                parent[rootq] = rootp;
            else
                parent[rootp] = rootq;
                
            numComponents--;
        }
    };
    
public:

    int makeConnected(int n, vector<vector<int>>& connections) {
        
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

public:
    
    struct UnionFind{
        int num;
        int numComponents;
        vector<int> rank;
        vector<int> parent;
    
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
            int rootp = find(p), rootq = find(q);
            if(rootp == rootq) return;
            
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
