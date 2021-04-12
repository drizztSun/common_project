/*
 399. Evaluate Division
 
 You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.

 You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.

 Return the answers to all queries. If a single answer cannot be determined, return -1.0.

 Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.

  

 Example 1:

 Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
 Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
 Explanation:
 Given: a / b = 2.0, b / c = 3.0
 queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
 return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
 Example 2:

 Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
 Output: [3.75000,0.40000,5.00000,0.20000]
 Example 3:

 Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
 Output: [0.50000,2.00000,-1.00000,-1.00000]
  

 Constraints:

 1 <= equations.length <= 20
 equations[i].length == 2
 1 <= Ai.length, Bi.length <= 5
 values.length == equations.length
 0.0 < values[i] <= 20.0
 1 <= queries.length <= 20
 queries[i].length == 2
 1 <= Cj.length, Dj.length <= 5
 Ai, Bi, Cj, Dj consist of lower case English letters and digits.
 
 
 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <functional>

using std::unordered_set;
using std::unordered_map;
using std::string;
using std::vector;


class EvaluateDivision {
    
    /*
                
        399.Evaluate-Division
        本题网上有很多提示用图和Floyd算法。本人觉得用图的话，会把所有节点之间的路径都算一遍，没有必要。而且似乎本题用C++实现Floyd有些麻烦，网上的图算法都是用的phyton。所以我这里还是用万能的DFS大法。

        基本思想很明确。要算两个节点的a/b，没有现成的数据怎么办，就把所有的中间节点走一遍，查看(a/c,c/b),(a/d,d/b),(a/e,e/b)...如果a/c有现成的，就把锅甩给DFS函数去递归考虑 c/b 怎么算，算出来c/b有解的话，a/b就大功告成。
        因为题目保证不会有冲突，所以那么多第三方节点c,d,e,...只要成功了一个就行。

        首选，为了方便DFS的遍历，需要构造一个检索容易的数据结构。因为a,b,c,d这些字符串比较麻烦。所以用字符串的映射就是很自然的想法：

                unordered_map<string, vector<pair<string, double>>> graph; //存储图的数据结构
                for (int i=0; i<equations.size(); i++)
                {
                    auto it = equations[i];
                    graph[it.first].push_back({it.second,values[i]});
                    graph[it.second].push_back({it.first,1.0/values[i]});
                }
                //构造完整的双向图
        构造DFS函数，包括起点start，终点end，和经过的节点集合visited

            double DFS(string start, string end, unordered_set<string>visited)
        根据上述的思想，在graph[start]遍历所有可以从start到达的第三方节点mid。忽略已经走过的那些节点，剩下的调用DFS(mid,end,visited)来查看mid到end是否走得通就行。

                for (auto a:graph[start]) //遍历start所能通向的所有位置
                {
                    string mid = a.first;  // 选取一个位置叫mid
                    if (visited.find(mid)!=visited.end()) continue;  //如果这个位置已经访问过了，就不要再考虑
                    double temp2 = DFS(mid,end,visited); //剩下的就交给DFS去算从mid到end的距离。
                    if (temp2!=-1.0)
                    {
                        temp = a.second*temp2;  //只要从mid到end可行的话，就算找到从start到end的解了（因为题目保证没有其他mid能造成冲突）
                        break;
                    }
                }    
    */
    unordered_map<string, vector<std::pair<string, double>>> graph; //存储图的数据结构
    
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) 
    {
        vector<double>results;
        
        for (int i=0; i<equations.size(); i++)
        {
            auto it = equations[i];
            graph[it.first].push_back({it.second,values[i]});
            graph[it.second].push_back({it.first,1.0/values[i]});
        }
        //构造完整的双向图
        
        for (int i=0; i<queries.size(); i++) //遍历所有的query
        {
            auto it = queries[i];
            if (graph.find(it.first)==graph.end() || graph.find(it.second)==graph.end())
                results.push_back(-1.0);  //提前处理：图中不存在的点
            else if (it.first==it.second)
                results.push_back(1.0);   //提前处理：起讫位置相同的情况
            else
            {
                unordered_set<string>visited;
                double temp = DFS(it.first,it.second,visited); //剩下的都扔给DFS
                results.push_back(temp);
            }
        }
        return results;
    }
    
    double DFS(string start, string end, unordered_set<string>visited)
    {
        if (start==end) return 1.0;
        
        visited.insert(start);
        double temp = -1.0;
        
        for (auto a:graph[start]) //遍历start所能通向的所有位置
        {
            string mid = a.first;  // 选取一个位置叫mid
            if (visited.find(mid)!=visited.end()) continue;  //如果这个位置已经访问过了，就不要再考虑
            double temp2 = DFS(mid,end,visited); //剩下的就交给DFS去算从mid到end的距离。
            if (temp2!=-1.0)
            {
                temp = a.second*temp2;  //只要从mid到end可行的话，就算找到从start到end的解了（因为题目保证没有其他mid能造成冲突）
                break;
            }
        }
        
        return temp;
    }

public:

    unordered_map<string,vector<string>>next;
    unordered_map<string,double>value;
    unordered_map<string,int>visited;

    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) 
    {
        for (int i=0; i<equations.size(); i++)
        {
            next[equations[i].first].push_back(equations[i].second);
            value[equations[i].first+":"+equations[i].second]=values[i];
            next[equations[i].second].push_back(equations[i].first);
            value[equations[i].second+":"+equations[i].first]=1.0/values[i];
            visited[equations[i].first]=0;
            visited[equations[i].second]=0;
        }
        
        vector<double>results;
        
        for (int i=0; i<queries.size(); i++)
        {
            for (auto a:visited)
                visited[a.first]=0;            
            results.push_back(DFS(queries[i].second,queries[i].first));
        }        
        
        return results;
    }
    
    double DFS(string start, string end)
    {
        if (next.find(start)==next.end())
            return -1.0;
        
        if (start==end) 
            return 1.0;
        
        for (auto b: next[start])
        {
            if (visited[b]==1) continue;
         
            visited[b]=1;            
            double temp = DFS(b, end);
            if (temp!=-1.0)             
                return value[b+":"+start] * temp;                            
            visited[b]=0;
        }
        
        return -1.0;
    }

public:

    /*
    Solution1: Graph + DFS

    A/B = 2
    g[A][B] = 2 | g[B][A] = 1.0/2

    Time complexity: O(e + q*e)
    Space complexity: O(e)
    */
    vector<double> calcEquation(vector<vector<string>> equations, vector<double>& values, vector<vector<string>> queries) {
            // g[A][B] = k -> A / B = k
        unordered_map<string, unordered_map<string, double>> g;

        for (int i = 0; i < equations.size(); ++i) {
            const string& A = equations[i][0];
            const string& B = equations[i][1];
            const double k = values[i];
            g[A][B] = k;
            g[B][A] = 1.0 / k;
        }

                // get result of A / B
        std::function<double(const string&, const string&)> divide = [&](const string& A, const string& B) {        
            if (A == B) return 1.0;
            visited.insert(A);
            
            for (const auto& pair : g[A]) {
                const string& C = pair.first;
                if (visited.count(C)) 
                    continue;
                double d = divide(C, B); // d = C / B
                // A / B = C / B * A / C
                if (d > 0) 
                    return d * g[A][C];
            }        
            return -1.0;
        };
        
        vector<double> ans;
        for (const auto& pair : queries) {
            const string& X = pair[0];
            const string& Y = pair[1];
            if (!g.count(X) || !g.count(Y)) {
                ans.push_back(-1.0);
                continue;
            }
            unordered_set<string> visited;            
            ans.push_back(divide(X, Y));
        }
        return ans;
    }

    /*
    Solution 2: Union Find

    A / B = 2 -> Parent[A] = {B, 2} Parent[B] = {B, 1.0}

    B / C = 3 -> Parent[C] = {B, 1/3.0}

    A / C? p[A].key == p[C].ley == B
    = p[A].val / p[C].val = 2/ (1/3.0) = 6

    Time complexity: O(e + q)
    Space complexity: O(e)
    */
    
    vector<double> doit_disjoint(vector<vector<string>>&& equations, vector<double>&& values, vector<vector<string>>&& queries) {
        
        unordered_map<string, std::pair<string, double>> parent;
        
        std::function<std::pair<string, double>(string)> find = [&](string id) -> std::pair<string, double> {
            
            if (parent.count(id) == 0) {
                parent[id] = {id, 1};
            }
            
            auto [pid, weight] = parent[id];
            if (pid != id) {
                auto [nid, w] = find(pid);
                parent[id] = {nid, w * weight};
            }
            
            return parent[id];
        };

        std::function<void(string, string, double)> Union = [&](string x, string y, double value) -> void {
            
            auto [px, wx] = find(x);
            auto [py, wy] = find(y);
            
            if (px != py) {
                parent[px] = {py, wy * value / wx};
            }
        };
        
        for (auto i = 0; i < equations.size(); i++) {
            Union(equations[i][0], equations[i][1], values[i]);
        }
        
        vector<double> res;
        for (auto i = 0; i < queries.size(); i++) {
            
            string x = queries[i][0], y = queries[i][1];
            if (parent.count(x) == 0 || parent.count(y) == 0) {
                res.push_back(-1);
                continue;
            }
            
            auto [px, wx] = find(x);
            auto [py, wy] = find(y);
            
            if (px != py) {
                res.push_back(-1);
            } else {
                res.push_back(wx / wy);
            }
        }
        
        return res;
    }

};