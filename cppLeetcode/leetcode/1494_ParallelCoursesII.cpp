/*
 
 1494 Parallel Courses II
 
 Given the integer n representing the number of courses at some university labeled from 1 to n, and the array dependencies where dependencies[i] = [xi, yi]
 represents a prerequisite relationship, that is, the course xi must be taken before the course yi.  Also, you are given the integer k.

 In one semester you can take at most k courses as long as you have taken all the prerequisites for the courses you are taking.

 Return the minimum number of semesters to take all courses. It is guaranteed that you can take all courses in some way.

  

 Example 1:



 Input: n = 4, dependencies = [[2,1],[3,1],[1,4]], k = 2
 Output: 3
 Explanation: The figure above represents the given graph. In this case we can take courses 2 and 3 in the first semester, then take course 1 in the second semester and finally take course 4 in the third semester.
 Example 2:



 Input: n = 5, dependencies = [[2,1],[3,1],[4,1],[1,5]], k = 2
 Output: 4
 Explanation: The figure above represents the given graph. In this case one optimal way to take all courses is: take courses 2 and 3 in the first semester and take course 4 in the second semester,
 then take course 1 in the third semester and finally take course 5 in the fourth semester.
 Example 3:

 Input: n = 11, dependencies = [], k = 2
 Output: 6
  

 Constraints:

 1 <= n <= 15
 1 <= k <= n
 0 <= dependencies.length <= n * (n-1) / 2
 dependencies[i].length == 2
 1 <= xi, yi <= n
 xi != yi
 All prerequisite relationships are distinct, that is, dependencies[i] != dependencies[j].
 The given graph is a directed acyclic graph.

 
 
 
 */
#include <stdio.h>
#include <vector>


using std::vector;


class ParallelCourseII {
public:
    
    /*
     1494.Parallel-Courses-II
     此题乍看贪心法可解。如果想要得到一个合法的课程顺序，必然利用拓扑排序的手段，首先完成那些入度为0的课程。但是本题特别之处在于，如果入度为0的课程多余k个，那么第一轮该优先选取哪k个，才能保证最终用最少的轮数完成所有课程？
     事实上，并没有任何有效的贪心策略能够帮助挑选这k个课程。优先有序节点总数多的课程，或者优先后续节点深度多的课程，都是没有道理的。

     事实上这是一道NP问题，并没有多项式时间的解法。所以只好用暴力的方法去解决。状态压缩DP就是比较“高效”的暴力方法。事实上，题目给出n<=15的条件，就暗示了应该用这种方法。

     我们用整形变量state的各个bit位来代表是否完成了某门课程，比如说第i个bit位是1就表示完成了第i门课程。dp[state]表示完成对应的这些课程需要最少多少轮。显然，我们需要考虑前一轮的状态prevState是什么？显然我们找一个最小的dp[prevState]然后加1，就可以得到最优的dp[state]。

     我们知道prevState必然是state的子集。我们可以用暴力搜索所有它的子集，这里有一个比较高效的循环语句值得收藏：

     for (int subset=state; subset>0; subset=(subset-1)&state)
     这样得到的subset是比较高效的。

     那么接下来我们就要判断这个subset对应的状态，是否能够通过新一轮的课程学习，达到state对应的状态。这里需要几个条件：

     state的课程数目不能比subset的课程数目多余k。这可以用C++的内置函数来实现：
     __builtin_popcount(state) - __builtin_popcount(subset) <= k
     state的课程的先修课程，必须全部囊括在subset里面。也就是说，subset必须是state先修课程的超集。我们需要提前计算出state的先修课程集合prevState[state]，然后判断是否
     prevState[state] & subset == prevState[state]
     满足这两个条件的话，那么就说明subset是可以转移到state的。故有dp[state]=dp[subset]+1

     此外，我们可以提前处理数据，计算所有状态的prevState。这个不难做到，只要将state的每一门课程的先修课程取并集即可。
     
     
     */
    int doit_dp_bitmask(int n, vector<vector<int>>& dependencies, int k) {
        
        int total = 1 << n;
        vector<int> dp(total, INT_MAX/2);
        vector<int> preCourses(n, 0);
        
        for (auto& c : dependencies) {
            preCourses[c[1]-1] |= 1 <<(c[0]-1);
        }
        
        vector<int> prereq(total, 0);
        for (int state = 0; state < total; state++) {
            for (int i = 0; i < n; i++) {
                if (state >> i & 1) {
                    prereq[state] |= preCourses[i];
                }
            }
        }
        
        /*
          preState -> state
         1.preState is a subset of state
         2. countOne(state) - countOne(subset) <= k
         3. preState must contain prerequisites of state, subset(10011) > prereq[state](10010)
         
         */
        dp[0] = 0;
        for (int state = 0; state < total; state++) {
            
            for (int subset = state; subset >= 0; subset = (subset - 1)&state) {
                
                if (__builtin_popcount(state) - __builtin_popcount(subset) <= k && (subset & prereq[state]) == prereq[state]) {
                    
                    dp[state] = std::min(dp[state], dp[subset] + 1);
                }
                
                if (subset == 0)
                    break;
            }
        }
        
        
        return dp[total - 1];
    }
};


class DirectedGraph
{
public:
    DirectedGraph(int n)
    {
        _adj.resize(n);
        _indegrees.resize(n, 0);
    }
    
    void addEdge(int u, int v)
    {
        _adj[u].push_back(v);
        _indegrees[v]++;
    }
    
    const vector<int>& indegrees() const
    {
        return _indegrees;
    }
    
    const vector<int>& neighbors(int v) const
    {
        return _adj[v];
    }
    
private:
    vector<int> _indegrees;
    vector<vector<int>> _adj;
};

class ParallelCourseII_backtracking {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& dependencies, int k) {
        
        DirectedGraph graph(n);
        
        for (auto &edge: dependencies)
            graph.addEdge(edge[0] - 1, edge[1] - 1);
        
        _indegrees = graph.indegrees();
        _mark.resize(n, false);
        
        return backtrack(graph, k);
    }
    
private:
    int backtrack(DirectedGraph &g, int k)
    {
        int candidates = 0; // Bit representation of courses can take at this time

        
        // These two variables are used to deal with the worst case as below:
        // 15
        // [[2,1]]
        // 2
        // For this case, blind backtracking will take O(n!)
        //
        // We are lucky the test case suite doesn't contain another edge worst case:
        // 15
        // [[1,10],[2,10],[3,10],[4,10],[5,10],[6,10],[7,10],[8,10],[9,10],[11,10],[12,10],[13,10],[14,10],[15,10]]
        // 3
        // for this case, our approach will take O(n!)
        //
        // Without special handling for the worst case, our code could be much simpler:
        
        // for (int i = 0; i < _indegrees.size(); i++)
        //     if (!_mark[i] && _indegrees[i] == 0) {
        //         candidates |= (1 << i);
        //     }
        int remaining = 0;
        int nZeroOutDegrees = 0;
        
        for (int i = 0; i < _indegrees.size(); i++)
            if (!_mark[i]) {
                remaining++;
                if (_indegrees[i] == 0) {
                    if (g.neighbors(i).empty()) {
                        nZeroOutDegrees++;
                        if (nZeroOutDegrees == 1 || __builtin_popcount(candidates) < k)
                            candidates |= (1 << i);
                    } else {
                        candidates |= (1 << i);
                    }
                }
            }
        
        // base case, no more courses to take
        if (candidates == 0)
            return 0;
              
        if (nZeroOutDegrees == remaining)
            return (remaining + k - 1) / k;
        
        int ncandidates = __builtin_popcount(candidates);
        // Generates subsets that can take among the candidate courses
        if (ncandidates <= k) {
            // take all of them
            cut(g, candidates);
            int semesters = backtrack(g, k) + 1;
            restore(g, candidates);
            
            return semesters;
        } else {
            int semesters = INT_MAX;
            for (int s = candidates; s; s = (s-1) & candidates)
                if (__builtin_popcount(s) == k) {
                    // now s is a subset with k courses
                    cut(g, s);
                    semesters = std::min(backtrack(g, k), semesters);
                    restore(g, s);
                }
            
            return semesters + 1;
        }
    }
    
    // Remove candidate vertices from graph by marking as visted and decreasing indegrees of target vertices
    void cut(DirectedGraph &g, int candidates)
    {
        for (int i = 0; i < 16; i++)
            if (candidates & (1 << i)) {
                _mark[i] = true;
                for (auto w: g.neighbors(i))
                    _indegrees[w]--;
            }
    }
    
    // Restore candidate vertices to graph by marking as unvisited and increasing indegrees of target vertices
    void restore(DirectedGraph &g, int candidates)
    {
        for (int i = 0; i < 16; i++)
            if (candidates & (1 << i)) {
                _mark[i] = false;
                for (auto w: g.neighbors(i))
                    _indegrees[w]++;
            }
    }
    
private:
    vector<bool> _mark;
    vector<int> _indegrees;
};
