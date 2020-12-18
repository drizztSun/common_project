/*

1601. Maximum Number of Achievable Transfer Requests

We have n buildings numbered from 0 to n - 1. Each building has a number of employees. It's transfer season, and some employees want to change the building they reside in.

You are given an array requests where requests[i] = [fromi, toi] represents an employee's request to transfer from building fromi to building toi.

All buildings are full, so a list of requests is achievable only if for each building, the net change in employee transfers is zero. This means the number of employees leaving is equal to the number of employees moving in. For example if n = 3 and two employees are leaving building 0, one is leaving building 1, and one is leaving building 2, there should be two employees moving to building 0, one employee moving to building 1, and one employee moving to building 2.

Return the maximum number of achievable requests.

 

Example 1:


Input: n = 5, requests = [[0,1],[1,0],[0,1],[1,2],[2,0],[3,4]]
Output: 5
Explantion: Let's see the requests:
From building 0 we have employees x and y and both want to move to building 1.
From building 1 we have employees a and b and they want to move to buildings 2 and 0 respectively.
From building 2 we have employee z and they want to move to building 0.
From building 3 we have employee c and they want to move to building 4.
From building 4 we don't have any requests.
We can achieve the requests of users x and b by swapping their places.
We can achieve the requests of users y, a and z by swapping the places in the 3 buildings.
Example 2:


Input: n = 3, requests = [[0,0],[1,2],[2,1]]
Output: 3
Explantion: Let's see the requests:
From building 0 we have employee x and they want to stay in the same building 0.
From building 1 we have employee y and they want to move to building 2.
From building 2 we have employee z and they want to move to building 1.
We can achieve all the requests. 
Example 3:

Input: n = 4, requests = [[0,3],[3,1],[1,2],[2,0]]
Output: 4
 

Constraints:

1 <= n <= 20
1 <= requests.length <= 16
requests[i].length == 2
0 <= fromi, toi < n

*/
#include <vector>
#include <queue>


using std::queue;
using std::vector;

class MaximumRequests {

public:

    int doit_dfe_backtracking(int n, vector<vector<int>>& requests) {
        
        int N = requests.size();
        vector<int> indegree(n);
        int ans = 0;
        
        std::function<void(int, int)> backtracking = [&](int i, int cnt){
            
            if (i == N) {
                for (auto c : indegree) {
                    if (c != 0)
                        return;
                }
                
                ans = std::max(ans, cnt);
            } else {
                
                int c1 = requests[i][0], c2 = requests[i][1];
                indegree[c1]--;
                indegree[c2]++;
                backtracking(i+1, cnt+1);
                indegree[c1]++;
                indegree[c2]--;
                
                backtracking(i+1, cnt);
            }
        };
        
        backtracking(0, 0);
        return ans;
    }

    struct Edge{
      int v, w, sw, rev;
      constexpr Edge(int v, int w, int sw, int rev) noexcept: v(v), w(w), sw(sw), rev(rev){}
   };
public:
   int maximumRequests(int n, vector<vector<int>> &req) const{
      vector<vector<Edge>> g(n);
      int ans = 0;
      for(auto const &e: req){
         int u = e[0], v = e[1];
         if(u == v){
            ++ans; continue;
         }
         g[u].emplace_back(v, 1, 1, g[v].size());
         g[v].emplace_back(u, -1, 0, g[u].size()-1);
      }

      while(1){
         vector<int> d(n), pv(n), pe(n), cnt(n);
         queue<int> bf;
         for(int i=0; i<n; ++i){
            bf.push(i);
         }
         vector<bool> inq(n, true);
         int ncv = -1;
         while(!bf.empty()){
            int u = bf.front(); bf.pop(); inq[u] = false;
            for(size_t i=0; i<g[u].size(); ++i){
               auto [v, w, sw, _] = g[u][i];
               if(!sw || d[v]>=d[u]+w) continue;
               d[v] = d[u]+w;
               pv[v] = u; pe[v] = i;
               if(!inq[v]){
                  if(++cnt[v] == n){
                     ncv = v;
                     goto after_bf;
                  }
                  bf.push(v); inq[v] = true;
               }
            }
         }
         after_bf:
         if(ncv == -1) break;
         vector<bool> vis(n);
         for(; !vis[ncv]; ncv=pv[ncv]){
            vis[ncv] = true;
         }
         int u = ncv;
         do{
            int p = pv[u], i = pe[u];
            ans += g[p][i].w;
            g[p][i].sw = 0;
            g[u][g[p][i].rev].sw = 1;
            u = p;
         }while(u != ncv);
      }
      
      return ans;
   }
};