/*
 
 1202. Smallest String With Swaps
 
 You are given a string s, and an array of pairs of indices in the string pairs where pairs[i] = [a, b] indicates 2 indices(0-indexed) of the string.

 You can swap the characters at any pair of indices in the given pairs any number of times.

 Return the lexicographically smallest string that s can be changed to after using the swaps.

  

 Example 1:

 Input: s = "dcab", pairs = [[0,3],[1,2]]
 Output: "bacd"
 Explaination:
 Swap s[0] and s[3], s = "bcad"
 Swap s[1] and s[2], s = "bacd"
 Example 2:

 Input: s = "dcab", pairs = [[0,3],[1,2],[0,2]]
 Output: "abcd"
 Explaination:
 Swap s[0] and s[3], s = "bcad"
 Swap s[0] and s[2], s = "acbd"
 Swap s[1] and s[2], s = "abcd"
 Example 3:

 Input: s = "cba", pairs = [[0,1],[1,2]]
 Output: "abc"
 Explaination:
 Swap s[0] and s[1], s = "bca"
 Swap s[1] and s[2], s = "bac"
 Swap s[0] and s[1], s = "abc"
  

 Constraints:

 1 <= s.length <= 10^5
 0 <= pairs.length <= 10^5
 0 <= pairs[i][0], pairs[i][1] < s.length
 s only contains lower case English letters.

 
*/

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <functional>
#include <set>

using std::set;
using std::unordered_set;
using std::vector;
using std::string;
using std::unordered_map;


class SmallestStringWithSwaps {

    /*
        1202.Smallest-String-With-Swaps
      很显然，将所有有联通关系的index都union成一个连通图，那么这些index对应的字符其实就可以任意调换顺序，想像成“冒泡法”就不难理解了。

      将一个连通分量内的字符串抽取出来按照字典序重新排列，然后再依次放回这些index的位置，就是答案。
    */
    vector<int>Father;

    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int N = s.size();
        Father.resize(N);
        for (int i=0; i<N; i++)
            Father[i] = i;
        
        for (auto& p :pairs)
        {
            int a = p[0];
            int b = p[1];
            if (FindFather(a)!=FindFather(b))
                Union(a,b);
        }
        
        unordered_map<int, vector<int>>Map; // root idx -> all indexes
        for (int i=0; i<N; i++)
        {
            Map[FindFather(i)].push_back(i);
        }
        
        for (auto x: Map)
        {
            string temp;
            for (auto idx : x.second)
                temp.push_back(s[idx]);

            std::sort(temp.begin(),temp.end());
            int k = 0;
            for (auto idx : x.second)
            {
                s[idx] = temp[k];
                k++;
            }
        }
        
        return s;
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

public:
    
    string doit_dfs(string s, vector<vector<int>>& pairs) {
        
        unordered_map<int, vector<int>> graph;
        unordered_set<int> seen;
        vector<char> tmp;
        vector<int> idx;
        
        for (auto& c : pairs) {
            graph[c[0]].push_back(c[1]);
            graph[c[1]].push_back(c[0]);
        }
        
        std::function<void(int)> dfs = [&](int i) {
          
            if (seen.count(i)) return;
            
            tmp.push_back(s[i]);
            idx.push_back(i);
            seen.insert(i);
            
            for (auto j : graph[i])
                dfs(j);
        };
        
        
        for (int i = 0; i < s.length(); i++) {
            
            if (graph.find(i) == graph.end() || seen.count(i) > 0)
                continue;
            idx.clear();
            tmp.clear();
            dfs(i);
            
            std::sort(begin(idx), end(idx));
            std::sort(begin(tmp), end(tmp));
            
            for (auto j = 0; j < idx.size(); j++) {
                s[idx[j]] = tmp[j];
            }
        }
        
        return s;
    }
    
    
    string doit_disjoint(string s, vector<vector<int>>&& pairs) {
      int n = s.length();
      vector<int> p(n);
      std::iota(begin(p), end(p), 0); // p = {0, 1, 2, ... n - 1}
      
      std::function<int(int)> find = [&](int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
      };
      
      for (const auto& e : pairs)
        p[find(e[0])] = find(e[1]); // union
      
      vector<vector<int>> idx(n);
      vector<string> ss(n);
      
      for (int i = 0; i < s.length(); ++i) {
        int id = find(i);
        idx[id].push_back(i); // already sorted
        ss[id].push_back(s[i]);
      }
      
      for (int i = 0; i < n; ++i) {
        sort(begin(ss[i]), end(ss[i]));
        for (int k = 0; k < idx[i].size(); ++k)
          s[idx[i][k]] = ss[i][k];
      }
      
      return s;
    }


    string doit_disjoint(string s, vector<vector<int>>& pairs) {
      
      int n = s.length();
      vector<int> parent(n, -1);
      
      for (int i = 0; i < n; i++)
          parent[i] = i;
      
      auto find = [&](int n) {
          while (parent[n] != n) {
              parent[n] = parent[parent[n]];
              n = parent[n];
          }
          return n;
      };
      
      auto merge = [&](int a, int b) {
          int pa = find(a), pb = find(b);
          if (pa < pb)
              parent[pb] = pa;
          else
              parent[pa] = pb;
      };
      
      
      for (const auto& c: pairs) {
          merge(c[0], c[1]);
      }
      
      unordered_map<int, set<int>> groups;
      
      for (int i = 0; i < n; i++) {
          groups[find(i)].insert(i);
      }
      
      string result;
      result.resize(n);
      
      for(auto it: groups) {
          
          vector<char> tmp;
          for (auto c: it.second) tmp.push_back(s[c]);
          
          std::sort(begin(tmp), end(tmp));
          
          int i = 0;
          for (auto c: it.second) result[c] = tmp[i++];
      }
      
      return result;
    }
};