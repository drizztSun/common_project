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

using std::unordered_map;
using std::string;
using std::vector;


class EvaluateDivision {
    
public:
    
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


void test_339_evaluate_division() {
    
    // EvaluateDivision().doit_disjoint( vector<vector<string>>{{"a","b"},{"b","c"}}, vector<double>{2.0,3.0}, vector<vector<string>>{{"a","c"},{"b","a"},{"a","e"},{"a","a"},{"x","x"}});
    
    EvaluateDivision().doit_disjoint( vector<vector<string>>{{"a","b"},{"b","c"}, {"bc", "cd"}}, vector<double>{1.5, 2.5, 5.0}, vector<vector<string>>{{"a","c"},{"c","b"},{"bc","cd"},{"cd","bc"}});
}
