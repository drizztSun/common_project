/*
 964. Least Operators to Express Number
 
 Given a single positive integer x, we will write an expression of the form x (op1) x (op2) x (op3) x ...
 where each operator op1, op2, etc. is either addition, subtraction, multiplication, or division (+, -, *, or /).
 For example, with x = 3, we might write 3 * 3 / 3 + 3 - 3 which is a value of 3.

 When writing such an expression, we adhere to the following conventions:

 The division operator (/) returns rational numbers.
 There are no parentheses placed anywhere.
 We use the usual order of operations: multiplication and division happens before addition and subtraction.
 It's not allowed to use the unary negation operator (-).  For example, "x - x" is a valid expression as it only uses subtraction, but "-x + x" is not because it uses negation.
 We would like to write an expression with the least number of operators such that the expression equals the given target.  Return the least number of operators used.

  

 Example 1:

 Input: x = 3, target = 19
 Output: 5
 Explanation: 3 * 3 + 3 * 3 + 3 / 3.  The expression contains 5 operations.
 Example 2:

 Input: x = 5, target = 501
 Output: 8
 Explanation: 5 * 5 * 5 * 5 - 5 * 5 * 5 + 5 / 5.  The expression contains 8 operations.
 Example 3:

 Input: x = 100, target = 100000000
 Output: 3
 Explanation: 100 * 100 * 100 * 100.  The expression contains 3 operations.
  

 Note:

 2 <= x <= 100
 1 <= target <= 2 * 10^8
 */
#include <set>
#include <unordered_set>
#include <queue>
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;
using std::set;
using std::unordered_set;
using std::priority_queue;



class LeastOpsExpressTarget {
    
public:
    /*
     Each step, we go two ways:
     1) t => x^(k+1) - t, cost = k+1
     2) t => t - x^k, cost = k
     
     k = log(t) / log(x)
     
     */
    
    int doit_dijstra(int x, int target) {
        
        std::set<std::pair<int, int>> q; // # x -> number
        unordered_set<int> s;
        q.emplace(0, target);
        
        while (!q.empty()) {
        
          const auto it = begin(q);
          const int c = it->first;
          const int t = it->second;
          q.erase(it);
          
          if (t == 0)
              return c - 1;
          
          if (s.count(t))
              continue;
          
          s.insert(t);
          int n = log(t) / log(x);
          int l = t - pow(x, n);
          
          q.emplace(c + (n == 0 ? 2 : n), l);
          int r = pow(x, n + 1) - t;
          q.emplace(c + n + 1, r);
        }
        return -1;
    }
    
    int doit_dijstra_1(int x, int target) {
      priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
      unordered_set<int> s;
      q.emplace(0, target);
        
      while (!q.empty()) {
        const int c = q.top().first;
        const int t = q.top().second;
        q.pop();
        if (t == 0)
            return c - 1;
        if (s.count(t))
            continue;
        s.insert(t);
        
        int n = log(t) / log(x);
        int l = t - pow(x, n);
        q.emplace(c + (n == 0 ? 2 : n), l);
        int r = pow(x, n + 1) - t;
        q.emplace(c + n + 1, r);
      }
      return -1;
    }
    
    /*
     dp (x, t) = min { dp(x, t - x^k) + k, dp(x, x^(k+1) -t) + (k+1), x^(k+1) - t < t}
        k = floor(logx(t))
        # Similiar to LC 818 Race Car
       # Only rely on smaller sub-problems
     
     E.g. dp(3, 13) = dp(3, 13-9) + 2, can't use dp(3, 27-13) = dp(3, 14 > 13)
     E.g. dp(3, 14) = min( dp(3, 14-9) + 2, dp(3, 27-14) +3)
     E.g. dp(4, 8) = dp(4, 8-4) + 1, can't use dp(4, 16-8) == dp(4, 8)
     
     Base case:
     1. t = 0, dp(x, t) = 0
     2. t < x, dp(x, t) = min(2*t-1, (x-t)*2) x/x + .. + x/x, or x - x/x + x/x
     3. t = x^k, dp(x, t) = k-1 # x*x*x
     
     Time: (logx(t))
     Space: (logx(t))
     */
    int doit_dp_dfs_(int x, int target) {
        
        unordered_map<int, int> m_;
       
        std::function<int(int, int)> dp = [&](int x, int t) {
          if (t == 0)
              return 0;
          if (t < x)
              return std::min(2 * t - 1, 2 * (x - t));
          
          if (m_.count(t))
              return m_.at(t);
            
          int k = log(t) / log(x);
          long p = pow(x, k);
          if (t == p)
              return m_[t] = k - 1;
          
          int ans = dp(x, t - p) + k; // t - p < t
          long left = p * x - t;
          
           if (left < t) // only rely on smaller sub-problems
              ans = std::min(ans, dp(x, left) + k + 1);
           return m_[t] = ans;
       };
        
       return dp(x, target);
    }


};
