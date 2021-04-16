/*
 1591. Strange Printer II
 
 
 There is a strange printer with the following two special requirements:

 1. On each turn, the printer will print a solid rectangular pattern of a single color on the grid. This will cover up the existing colors in the rectangle.
 2. Once the printer has used a color for the above operation, the same color cannot be used again.
 
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

    /*
        1591.Strange-Printer-II
        首先，我们解决一个问题：如果矩形里有色彩1，那么我们能知道选种色彩1的色块的形状和位置吗？这个不难做到，我们只要把所有呈现色彩1的格子都找出来，找到能覆盖它的最小的矩形框即可。举个例子：

        1 2 1
        2 1 3
        2 4 4
        我们把所有1的格子都找出来，就可以确定这个色块的上边界、下边界、左边界、右边界。由此我们可以发现色彩1的范围应该就是2x3。同理我们可以确定色块2的范围是左边3x2。

        这里可能会有一个疑问，为什么色块2的范围不能更大一些？其余部分可不可能被其他色彩覆盖了？诚然确实有这个可能，在超过左边3x2的部分，可能还会有被遮住的2。但是那些“多余的”2对我们来说并没有影响。
        我们可以认为它存在，也可以认为它不存在。因为它从来没有真正显现过，它的存在与否无从考证。如果它的存在影响了我们其他的结论，那么我们索性就认为它不存在。从后面的分析可知，索性认为它“不存在”会给我们带来更方便的分析。

        通过这样的分析，我们可以确定每一个色块的大小和位置。因此也就是说，对于每个格子而言，它被哪些色块覆盖过就都知道了。比如说(0,0)就被1,2填色过；(0,0)就被1,2填色过；(1,2)就被1,3填色过；(2,1)就被1,2,4填色过...

        由此，我们还可以有一个重要的发现。(0,0)就被1,2填色过，但最终显示的是颜色1，因此说明色块1应该出现在色块2之后（才能将其覆盖）；(1,2)就被1,3填色过，但最终显示的是颜色3，因此说明色块3应该出现在色块2之后（才能将其覆盖）；
        (1,2)就被1,2,4填色过，但最终显示的是颜色4，因此说明色块4应该出现在色块1和色块2之后（才能将其覆盖）...

        由此我们可以知道部分的色块填充顺序要求。如果我们能找到一种所有色块的填充顺序，满足这些要求，那就意味着这些格子都能被顺利填色，并且最终显示的的色彩一定就是我们看到的色彩。

        这样的色彩填充顺序有很多，我们不一定要真正写出来。我们只要判断是否存在即可。那么如果不存在的原因是什么呢？那就仅有一种：色彩的覆盖顺序出现了循环。比如说对于某个格子，我们发现要求色彩1覆盖色彩2；
        但是对于另外一个格子，我们发现要求色彩2覆盖色彩1。这样的话，我们是无法确定一种所有色彩的填充顺序的。其他任何情况，我们都可以设计出一种不与要求矛盾的色彩填充顺序。

        如果我们能够有这样的色彩填充顺序，那么就一定能实现最终呈现的色彩分布吗？是的，就是这样。我们可以想象堆砌房子，一个个不同颜色的矩形往上堆，从天空俯视到的每个格子的色彩，就是最终覆盖这个格子的色彩。
        只要堆砌顺序设计出来、并且满足最后堆砌的色彩就是现实的色彩，那么就说明实现了题目的要求。

        所以本题就是转化为了：构建一个有向图、判断是否有环。有环的话输出false，无环的话输出true。    
    */
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
                    if (i>=top[color] && i<=bottom[color] && j>=left[color] && j<=right[color])
                    {
                        if (color != targetGrid[i][j])
                            next[targetGrid[i][j]].push_back(color);
                    }
                }
            }

        numNodes = 61;
        return bfs();
    }
    
public:

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