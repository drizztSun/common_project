/*
1727. Largest Submatrix With Rearrangements

You are given a binary matrix matrix of size m x n, and you are allowed to rearrange the columns of the matrix in any order.

Return the area of the largest submatrix within matrix where every element of the submatrix is 1 after reordering the columns optimally.

 

Example 1:



Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
Output: 4
Explanation: You can rearrange the columns as shown above.
The largest submatrix of 1s, in bold, has an area of 4.
Example 2:



Input: matrix = [[1,0,1,0,1]]
Output: 3
Explanation: You can rearrange the columns as shown above.
The largest submatrix of 1s, in bold, has an area of 3.
Example 3:

Input: matrix = [[1,1,0],[1,0,1]]
Output: 2
Explanation: Notice that you must rearrange entire columns, and there is no way to make a submatrix of 1s larger than an area of 2.
Example 4:

Input: matrix = [[0,0],[0,0]]
Output: 0
Explanation: As there are no 1s, no submatrix of 1s can be formed and the area is 0.
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m * n <= 105
matrix[i][j] is 0 or 1.

*/

#include <vector>
#include <algorithm>

using std::vector;


class LargestSubmatrix {

    /*
        1727.Largest-Submatrix-With-Rearrangements
        此题和085.Maximal-Rectangle的框架很相似，就是枚举一个维度，然后将问题划归为另一个以为问题来求解。

        我们遍历每行row，考虑如果以i-th row为底边，我们所能构建的最大矩形是什么？此时我们眼中所看到的就是以i-th row为底边的一个histogram，和LC85不同的是，我们可以调整histogram中各条bar的顺序，来拼凑最大的矩形。
        为了更高效地构建矩形，我们显然会贪心地将高度相近的bar放在一起，也就是将这些bar按照高度从大到小排序。随着矩形的底边越长，代价就是高度越矮。我们横向遍历一遍后，就可以找到最大的矩形面积（宽乘以高）。

        本题的答案就是遍历所有底边后，全局最大的矩形。
    */
    int largestSubmatrix(vector<vector<int>>& matrix) 
    {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int>a(n,0);
        int ret = 0;
        for (int i=0; i<m; i++)
        {
            for (int j=0; j<n; j++)
            {
                if (matrix[i][j]==1)
                    a[j] = a[j]+1;
                else
                    a[j] = 0;                    
            }
            auto b = a;
            sort(b.begin(), b.end());
            reverse(b.begin(), b.end());
            int h = INT_MAX;
            for (int j=0; j<n; j++)
            {
                h = std::min(h, b[j]);
                ret = std::max(ret, h*(j+1));
            }
        }
        return ret;        
    }

public:

    int doit_greedy(vector<vector<int>>& matrix) {
        
        int m = matrix.size(), n = matrix[0].size();
        int ans = 0;
        
        vector<int> heights(n, 0);
        
        
        for (int i = 0; i < matrix.size(); i++) {
            
            
            for (int j = 0; j < n; j++)
                heights[j] = matrix[i][j] == 0 ? 0 : (heights[j] + 1);
            
            vector<int> tmp = heights;
            std::sort(begin(tmp), end(tmp));
            
            for (int i = 0; i < n; i++) {
                
                ans = std::max(ans, tmp[i] * (n-i));
            }
        }
        
        return ans;
    }
};