/*
 1483. Kth Ancestor of a Tree Node
 
 You are given a tree with n nodes numbered from 0 to n-1 in the form of a parent array where parent[i] is the parent of node i. The root of the tree is node 0.

 Implement the function getKthAncestor(int node, int k) to return the k-th ancestor of the given node. If there is no such ancestor, return -1.

 The k-th ancestor of a tree node is the k-th node in the path from that node to the root.

 Example:

 Input:
 ["TreeAncestor","getKthAncestor","getKthAncestor","getKthAncestor"]
 [[7,[-1,0,0,1,1,2,2]],[3,1],[5,2],[6,3]]

 Output:
 [null,1,0,-1]

 Explanation:
 TreeAncestor treeAncestor = new TreeAncestor(7, [-1, 0, 0, 1, 1, 2, 2]);

 treeAncestor.getKthAncestor(3, 1);  // returns 1 which is the parent of 3
 treeAncestor.getKthAncestor(5, 2);  // returns 0 which is the grandparent of 5
 treeAncestor.getKthAncestor(6, 3);  // returns -1 because there is no such ancestor
  

 Constraints:

 1 <= k <= n <= 5*10^4
 parent[0] == -1 indicating that 0 is the root node.
 0 <= parent[i] < n for all 0 < i < n
 0 <= node < n
 There will be at most 5*10^4 queries.
 
 
 */
#include <stdio.h>
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class TreeAncestor {
    
    vector<unordered_map<int, int> > _skip;
    int _depth;
    
public:
    TreeAncestor(int n, vector<int>& parent) {
        
        _depth = 15;
        
        unordered_map<int, int> tmp;
        for (auto i = 0; i < n; i++) {
            tmp.insert({i, parent[i]});
        }
        _skip.push_back(tmp);
        
        for (auto i = 1; i <= 15; i++) {
            
            unordered_map<int, int> tmp;
            for (auto& key : _skip[i-1]) {
                auto [k, v] = key;
                
                if (_skip[i-1].count(v) != 0) {
                    tmp[k] = _skip[i-1][v];
                }
            }
            _skip.push_back(tmp);
        }
    }
    
    int getKthAncestor(int node, int k) {
        
        auto step = _depth;
        
        while (k > 0) {
            auto base = 1 << step;
            if (k >= base) {
                if (_skip[step].count(node) == 0) {
                    return -1;
                }
                node = _skip[step][node];
                k -= base;
            } else {
                step -= 1;
            }
        }
        
        return node;
    }
};


class TreeAncestor2 {
    
public:
    
    TreeAncestor2(int n, vector<int>& parent) {
        int m = ceil(log(n) / log(2)) + 1;
        parents.resize(m, vector<int>(n));
        swap(parents[0], parent);
        for (int i = 1; i < m; i++) {
            auto& cur = parents[i];
            auto& pre = parents[i - 1];
            for (int j = 0; j < n; j++) {
                cur[j] = pre[pre[j] == -1 ? 0 : pre[j]];
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        for (int m = 1, i = 0; k > 0 && node > -1 && i < parents.size(); m <<= 1, i++) {
            if (k & m) {
                node = parents[i][node];
                k ^= m;
            }
        }
        return k > 0 ? -1 : node;
    }
    
private:
    vector<vector<int>> parents;
};

class TreeAncestor_DP {
    
public:
    vector <int> tpar;
    int nnode;
    int dp[100000][20];
    int max;
    
    TreeAncestor_DP(int n, vector<int>& parent) {
      nnode = n;
      tpar = parent;
      max = ceil(log2(nnode));
      memset(dp, -1, sizeof dp);
      
      //create dp
      for(int i = 1; i < nnode; i++){
        dp[i][0] = parent[i];
          
        for(int j = 1; j <= max; j++){
          dp[i][j] = dp[dp[i][j-1]][j-1];
            
          if(dp[i][j] == -1)
              break;
        }
      }
    }
    
    int getKthAncestor(int node, int k) {
        
        if(node >= nnode)
            return -1;
        
        for(int i = 0; i <= max; i++){
          if(k & 1 << i)
            node = dp[node][i];
            if(node == -1)
              return -1;
        }
      
        return node;
    }
};
