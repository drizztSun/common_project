/*
1738. Find Kth Largest XOR Coordinate Value


You are given a 2D matrix of size m x n, consisting of non-negative integers. You are also given an integer k.

The value of coordinate (a, b) of the matrix is the XOR of all matrix[i][j] where 0 <= i <= a < m and 0 <= j <= b < n (0-indexed).

Find the kth largest value (1-indexed) of all the coordinates of matrix.

 

Example 1:

Input: matrix = [[5,2],[1,6]], k = 1
Output: 7
Explanation: The value of coordinate (0,1) is 5 XOR 2 = 7, which is the largest value.
Example 2:

Input: matrix = [[5,2],[1,6]], k = 2
Output: 5
Explanation: The value of coordinate (0,0) is 5 = 5, which is the 2nd largest value.
Example 3:

Input: matrix = [[5,2],[1,6]], k = 3
Output: 4
Explanation: The value of coordinate (1,0) is 5 XOR 1 = 4, which is the 3rd largest value.
Example 4:

Input: matrix = [[5,2],[1,6]], k = 4
Output: 0
Explanation: The value of coordinate (1,1) is 5 XOR 2 XOR 1 XOR 6 = 0, which is the 4th largest value.
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 1000
0 <= matrix[i][j] <= 106
1 <= k <= m * n

*/
#include <vector>
#include <algorithm>

using std::vector;

class KthLargestValue {

    /*
        1738.Find-Kth-Largest-XOR-Coordinate-Value
        和二维矩阵前缀和的思路类似，我们可以用o(1)的时间求出每个网格位置的值：a[i][j] = a[i-1][j]^a[i][j-1]^a[i-1][j-1]^matrix[i][j].

        然后是常见的二分搜值的方法求出第k大的value，类似于215.Kth-Largest-Element-in-an-Array。每次猜测一个值x，然后遍历全局矩阵，统计有多少个元素大于等于x，如果count小于k，那么x肯定不可能是答案，我们将猜测的上界下调至x-1；否则，我们就将猜测的下界调整至x。
    */

public:
    int doit_binary_search(vector<vector<int>>& matrix, int k) 
    {
        int a[1000][1000];
        int m,n;

        m = matrix.size();
        n = matrix[0].size();
        
        a[0][0] = matrix[0][0];
        for (int i = 1; i < m; i++)
            a[i][0] = a[i-1][0]^matrix[i][0];
        for (int j = 1; j < n; j++)
            a[0][j] = a[0][j-1]^matrix[0][j];
        
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                a[i][j] = a[i-1][j] ^ a[i][j-1] ^ a[i-1][j-1] ^ matrix[i][j];

        auto count = [&] (int th)
        {
            int count = 0;
            for (int i=0; i<m; i++)
                for (int j=0; j<n; j++)
                    if (a[i][j]>=th)
                        count++;
            return count;
        };

        int left = 0, right = INT_MAX;
        while (left < right)
        {
            int mid = right-(right-left)/2;
            if (count(mid) < k)
                right = mid-1;
            else
                left = mid;
                
        }        
        return left;
    }
    
public:
    
    int doit_sort(vector<vector<int>>& matrix, int k) {
        
        int m = matrix.size(), n = matrix[0].size();
        vector<int> presum(m*n, 0);

        for (int i = 0; i < m; i++) {

            int local = 0;
            for (int j = 0; j < n; j++) {

                local ^= matrix[i][j];

                presum[i * n + j] = local;

                if (i > 0)
                    presum[i *n + j] ^= presum[(i-1)*n + j];
            }
        }
        
        std::sort(begin(presum), end(presum));
        return presum[m*n - k];
    }

    int doit_quickselect(vector<vector<int>>& matrix, int k) {
        
        int m = matrix.size(), n = matrix[0].size();
        vector<int> presum(m*n, 0);

        for (int i = 0; i < m; i++) {

            int local = 0;
            for (int j = 0; j < n; j++) {

                local ^= matrix[i][j];

                presum[i * n + j] = local;

                if (i > 0)
                    presum[i *n + j] ^= presum[(i-1)*n + j];
            }
        }
        
        std::nth_element(begin(presum), end(presum)-k, end(presum));
        //std::sort(end(presum)-k, end(presum));
        return presum[m*n-k];
    }
};