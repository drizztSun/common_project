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

/*
        1483.Kth-Ancestor-of-a-Tree-Node
    假设parent[node][0]标记了每个node的1代祖先，所以如果想知道node的7代祖先，可以将node=parent[node][0]执行7次。

    假设我们额外知道每个node的2代祖先，记做p[node][1]，那么我们对node的7代祖先只要做4次操作：（7=2^0+2^1+2^1+2^1）

    node = parent[node][0], node = p[node][1], node = p[node][1], node = p[node][1]
    假设我们额外知道每个node的4代祖先，记做p[node][2]，那么我们对node的7代祖先只要做3次操作：（7=2^0+2^1+2^2）

    node = p[node][0], node = p[node][1], node = p[node][2]
    由此可知，如果我们预先知道每个node的2^i代祖先parent[node][i]，那么我们就能减少query的次数。这样能减少多少呢？对于node的k代祖先，只需要将k做二进制分解，
    有多少个为1的bit，就做多少次query。考虑到k<=5*10^4，最多只需要20次query，就能够实现查询任意k代祖先。

            for (int i=0; i<20; i++)
            {
                if ((k>>i)&1)
                {
                    node = p[node][i];
                    if (node == -1) break;
                }                
            }
            return node;
    接下来我们考虑如何构建p[node][j].

    我们知道node的4代祖先p[node][2]，可以通过两次2代祖先的query来实现，即node=p[node][1], node=p[node][1]。
    于是我们可以发现，如果知道了p[node][j-1]，就可以推出p[node][j]。即p[node][j] = p[p[node][j-1]][j-1]。所以我们设置两层循环，外循环从小到大确定j，内循环设置node，就可以设置所有的p[node][j]了。

    这种思想叫做binary lifting.
*/
class TreeAncestor {
    vector<vector<int>>p;
public:
    TreeAncestor(int n, vector<int>& parent) 
    {
        vector<vector<int>>p(n, vector<int>(20, -1));  // p[i][j] means the 2^j-th ancestor for node i
        for (int i=0; i<n; i++)
            p[i][0] = parent[i];

        for (int j=1; j<20; j++)
            for (int i=0; i<n; i++)
            {
                if (p[i][j-1]!=-1)
                    p[i][j] = p[p[i][j-1]][j-1];
            }
        this->p = p;     
    }
    
    int getKthAncestor(int node, int k) 
    {
        for (int i=0; i<20; i++)
        {
            if ((k>>i)&1)
            {
                node = p[node][i];
                if (node == -1) break;
            }                
        }
        return node;
    }
};


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
