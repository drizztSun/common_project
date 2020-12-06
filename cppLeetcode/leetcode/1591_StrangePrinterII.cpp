/*
 1591. Strange Printer II
 
 
 There is a strange printer with the following two special requirements:

 On each turn, the printer will print a solid rectangular pattern of a single color on the grid. This will cover up the existing colors in the rectangle.
 Once the printer has used a color for the above operation, the same color cannot be used again.
 You are given a m x n matrix targetGrid, where targetGrid[row][col] is the color in the position (row, col) of the grid.

 Return true if it is possible to print the matrix targetGrid, otherwise, return false.



 Example 1:



 Input: targetGrid = [[1,1,1,1],[1,2,2,1],[1,2,2,1],[1,1,1,1]]
 Output: true
 Example 2:



 Input: targetGrid = [[1,1,1,1],[1,1,3,3],[1,1,3,4],[5,5,1,4]]
 Output: true
 Example 3:

 Input: targetGrid = [[1,2,1],[2,1,2],[1,2,1]]
 Output: false
 Explanation: It is impossible to form targetGrid because it is not allowed to print the same color in different turns.
 Example 4:

 Input: targetGrid = [[1,1,1],[3,1,3]]
 Output: false


 Constraints:

 m == targetGrid.length
 n == targetGrid[i].length
 1 <= m, n <= 60
 1 <= targetGrid[row][col] <= 60
 
 
 */
#include <vector>
#include <set>
#include <queue>

using std::vector;
using std::set;
using std::queue;


class StrangePrinterII {
    
    int numNodes;
    vector<vector<int>>next;
        
    bool bfs()
    {
        queue<int>q;
        int count = 0;

        vector<int>InDegree(numNodes,0);
        for (int i=0; i<numNodes; i++)
            for (int j: next[i])
                InDegree[j]++;

        for (int i=0; i<numNodes; i++)
        {
            if (InDegree[i]==0)
            {
                q.push(i);
                count++;
            }
        }
                    
        while (!q.empty())
        {
            int curCourse = q.front();
            q.pop();
            for (auto child: next[curCourse])
            {
                InDegree[child]--;
                if (InDegree[child]==0)
                {
                    q.push(child);
                    count++;
                }
            }
        }
        
        return count==numNodes;
    }
        
public:
    bool isPrintable(vector<vector<int>>&& targetGrid)
    {
        int m = targetGrid.size();
        int n = targetGrid[0].size();
        vector<int>left(61, n);
        vector<int>right(61, -1);
        vector<int>top(61, m);
        vector<int>bottom(61, -1);
        
        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
            {
                int color = targetGrid[i][j];
                left[color] = std::min(left[color], j);
                right[color] = std::max(right[color], j);
                top[color] = std::min(top[color], i);
                bottom[color] = std::max(bottom[color], i);
            }
        
        next.resize(61);
        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
            {
                for (int color=1; color<=60; color++)
                {
                    if (i>=top[color]&&i<=bottom[color]&&j>=left[color]&&j<=right[color])
                    {
                        if (color!=targetGrid[i][j])
                            next[targetGrid[i][j]].push_back(color);
                    }
                }
            }

        numNodes = 61;
        return bfs();
    }
    
    
    bool doit_topsort(vector<vector<int>>&& grid) {
        
        int m = grid.size(), n = grid[0].size();
        vector<int>left(61, n);
        vector<int>right(61, -1);
        vector<int>top(61, m);
        vector<int>bottom(61, -1);
        int maxcolor = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int color = grid[i][j];
                left[color] = std::min(left[color], j);
                right[color] = std::max(right[color], j);
                top[color] = std::min(top[color], i);
                bottom[color] = std::max(bottom[color], i);
                maxcolor = std::max(maxcolor, color);
            }
        }
        
        vector<set<int>> next(maxcolor+1);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int c = 1; c <= maxcolor; c++) {
                    if (i >= top[c] && i <= bottom[c] && j >= left[c] && j <= right[c]) {
                        if (c != grid[i][j])
                            next[grid[i][j]].insert(c);
                    }
                }
            }
        }
        
        
        vector<int> indegree(maxcolor+1, 0);
        for (int i = 1; i <= maxcolor; i++) {
            for (auto c : next[i])
                indegree[c]++;
        }
        
        queue<int> q;
        int count = 0;
        for (int i = 1; i <= maxcolor; i++) {
            if (indegree[i] == 0) {
                q.push(i);
                count++;
            }
        }
        
        while (!q.empty()) {
            
            int course = q.front();
            q.pop();
            
            for (auto child: next[course]) {
                indegree[child]--;
                
                if (indegree[child] == 0) {
                    q.push(child);
                    count++;
                }
            }
        }
        
        return count == maxcolor;
    }
};

void test_1591_strange_printer() {
    
    StrangePrinterII().doit_topsort(vector<vector<int>>{{1, 1, 1, 1}, {1, 1, 3, 3}, {1, 1, 3, 4}, {5, 5, 1, 4}});
    
}

