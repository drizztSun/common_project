/*
1074. Number of Submatrices That Sum to Target

Given a matrix and a target, return the number of non-empty submatrices that sum to target.

A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.

Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.

 

Example 1:


Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
Output: 4
Explanation: The four 1x1 submatrices that only contain 0.
Example 2:

Input: matrix = [[1,-1],[-1,1]], target = 0
Output: 5
Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, plus the 2x2 submatrix.
Example 3:

Input: matrix = [[904]], target = 0
Output: 0
 

Constraints:

1 <= matrix.length <= 100
1 <= matrix[0].length <= 100
-1000 <= matrix[i] <= 1000
-10^8 <= target <= 10^8
*/

#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;

class NumSubmatrixSumTarget {

    /*
        1074.Number-of-Submatrices-That-Sum-to-Target
        
        基本思想：固定上、下界的位置，在纵方向上累加每列，可以得到一个一维数组。然后从左到右逐个扫描求presum，并放入一个Hash表中。
        查看当前的presum-target是否已经在hash表中。存在的话就说明有submatrix的和等于target。
        
        时间复杂度：o(MMN*logN)
    */
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) 
    {
        int M = matrix.size();
        int N = matrix[0].size();
        int count = 0;

        auto helper = [](vector<int>&nums, int target)
        {
            int N = nums.size();
            int presum = 0;
            unordered_map<int,int>presumMap;
            presumMap[0] = 1;
            int count = 0;
            for (int j=0; j<N; j++)
            {
                presum += nums[j];
                if (presumMap.find(presum - target)!=presumMap.end())
                    count+=presumMap[presum - target];
                presumMap[presum]+=1;
            }
            return count;
        };

        for (int i=0; i<M; i++)
        {
            vector<int>temp(N,0);
            for (int j=i; j<M; j++)
            {
                for (int k=0; k<N; k++)
                    temp[k] += matrix[j][k];
                count += helper(temp,target);
            }
        }
        return count;                        
    }
    
public:

    /*
        Approach 1: Number of Subarrays that Sum to Target: Horizontal 1D Prefix Sum

        Algorithm

        Initialize the result: count = 0.

        Compute the number of rows: r = len(matrix) and number of columns: c = len(matrix[0]).

        Compute 2D prefix sum ps. To simplify the code, we allocate one more row and one more column, reserving row 0 and column 0 for zero values. This way, we avoid computing the first row and the first column separately.

        Iterate over the rows: r1 from 1 to r, and r2 from r1 to r:

        Inside this double loop, the left and right row boundaries are fixed. Now it's time to initialize a hashmap: 1D prefix sum -> number of matrices which use [r1, r2] rows and sum to this prefix sum. Sum of empty matrix is equal to zero: h[0] = 1.

        Iterate over the columns from 1 to c + 1. At each step:

        Compute current 1D prefix sum curr_sum using previously computed 2D prefix sum ps: curr_sum = ps[r2][col] - ps[r1 - 1][col].

        The number of times the sum curr_sum - target occurred, defines the number of matrices which use r1 ... r2 rows and sum to target. Increment the count: count += h[curr_sum - target].

        Add the current 1D prefix sum into hashmap.

        Return count.

        Implementation

        Current
        1 / 9
        
        Complexity Analysis
        
        Time complexity: O(R^2*C), where RR is the number of rows and CC is the number of columns.
        Space complexity: O(RC) to store 2D prefix sum.

    */
    int doit_dp(vector<vector<int>>& matrix, int target) {
        
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> presum(m+1, vector<int>(n+1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                presum[i][j] = matrix[i-1][j-1] + presum[i-1][j] + presum[i][j-1] - presum[i-1][j-1];
            }
        }
        
        int ans = 0;
        for (int i = 1; i <= m; i++) {
            for (int j = i; j <= m; j++) {
                
                unordered_map<int, int> counter;
                counter[0] = 1;
                for (int k = 1; k <= n; k++) {
                    
                    int t = presum[j][k] - presum[i-1][k];
                    ans += counter[t - target];
                    counter[t]++;
                }
            }
        }
        
        return ans;
    }

    /*
        Approach 2: Number of Subarrays that Sum to Target: Vertical 1D Prefix Sum
        In Approach 1, we were fixing two rows, and computing the "horizontal" 1D prefix sum. One could follow the same logic by fixing two columns, and computing the "vertical" 1D prefix sum.

        append

        Algorithm

        Initialize the result: count = 0.

        Compute the number of rows: r = len(matrix) and the number of columns: c = len(matrix[0]).

        Compute 2D prefix sum ps. To simplify the code, we allocate one more row and one more column, reserving row 0 and column 0 for zero values.

        Iterate over the columns: c1 from 1 to c, and c2 from c1 to c:

        Inside this double loop, the upper and lower column boundaries are fixed. Now it's time to initialize a hashmap: 1D prefix sum -> number of matrices which use [c1, c2] columns and sum to this prefix sum. Sum of empty matrix is equal to zero: h[0] = 1.

        Iterate over the rows from 1 to r + 1. At each step:

        Compute current 1D prefix sum curr_sum using previously computed 2D prefix sum ps: curr_sum = ps[row][c2] - ps[row][c1 - 1].

        The number of times the sum curr_sum - target occurred, defines the number of matrices which use c1 ... c2 rows and sum to target. Increment the count: count += h[curr_sum - target].

        Add the current 1D prefix sum into hashmap.

        Return count.

        Implementation


        Complexity Analysis

        Time complexity: O(R*C^2), where R is the number of rows and C is the number of columns.
        Space complexity: O(RC) to store 2D prefix sum.
    */
    int doit_dp_2(vector<vector<int>>& A, int target) {
        int res = 0, m = A.size(), n = A[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 1; j < n; j++)
                A[i][j] += A[i][j - 1];

        unordered_map<int, int> counter;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                counter = {{0,1}};
                int cur = 0;
                for (int k = 0; k < m; k++) {
                    cur += A[k][j] - (i > 0 ? A[k][i - 1] : 0);
                    res += counter.find(cur - target) != counter.end() ? counter[cur - target] : 0;
                    counter[cur]++;
                }
            }
        }
        return res;
    }


    int doit_best(vector<vector<int>>& matrix, int target) {

        int m = matrix.size(), n = matrix[0].size(), res = 0;

        auto cal = [](vector<int>& v, int t){
            
            int res = 0;
            int n = v.size();
            for(int i=0; i<n; i++){
                int sum = 0;
                for(int j=i; j<n; j++){
                    sum += v[j];
                    if(sum == t)
                        res++;
                }
            }
            return res;
        };

        for (int i = 0; i < m; ++i) {
            
            vector<int> arr(n, 0);

            for (int j = i; j < m; ++j) {

                for (int k = 0; k < n; ++k) arr[k] += matrix[j][k];

                res += cal(arr, target);
            }
        }
        return res;
    }


    /*
        Intuition
        Preaquis: 560. Subarray Sum Equals K
        Find the Subarray with Target Sum in linear time.


        Explanation
        For each row, calculate the prefix sum.
        For each pair of columns,
        calculate the accumulated sum of rows.
        Now this problem is same to, "Find the Subarray with Target Sum".


        Complexity
        Time O(mnn)
        Space O(m)

    */
    int numSubmatrixSumTarget(vector<vector<int>>& A, int target) {
        int res = 0, m = A.size(), n = A[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 1; j < n; j++)
                A[i][j] += A[i][j - 1];

        unordered_map<int, int> counter;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                counter = {{0,1}};
                int cur = 0;
                for (int k = 0; k < m; k++) {
                    cur += A[k][j] - (i > 0 ? A[k][i - 1] : 0);
                    res += counter.find(cur - target) != counter.end() ? counter[cur - target] : 0;
                    counter[cur]++;
                }
            }
        }
        return res;
    }
};
