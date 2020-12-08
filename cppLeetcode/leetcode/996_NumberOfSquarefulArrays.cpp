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
 
 
 
 */

#include <stdlib.h>

#include <vector>
using std::vector;

#include <cmath>


#include <unordered_map>
using std::unordered_map;


class NumSquarefulPerms {
    

    
public:
    int doit(vector<int>&& A) {
        
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
void test_996_number_of_squareful_array() {
    
    auto res1 = NumSquarefulPerms().doit(vector<int>{1,17,8});
    
    auto res2 = NumSquarefulPerms().doit(vector<int>{2,2,2});
    
    return;
}

