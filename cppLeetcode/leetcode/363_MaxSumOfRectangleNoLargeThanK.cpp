/*
 363. Max Sum of Rectangle No Larger Than K
 
 Given a non-empty 2D matrix matrix and an integer k, find the max sum of a rectangle in the matrix such that its sum is no larger than k.

 Example:

 Input: matrix = [[1,0,1],[0,-2,3]], k = 2
 Output: 2
 Explanation: Because the sum of rectangle [[0, 1], [-2, 3]] is 2, and 2 is the max number no larger than k (k = 2).
 
 */
#include <vector>
#include <set>

using std::set;
using std::vector;

class MaxSumOfRectThanK {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        
        if(matrix.size() == 0)
            return 0;
        
        auto m = matrix.size();
        auto n = matrix[0].size();
        int res = INT_MIN;
        
        for(int i = 0; i < n; i++) {  // the number of columns is smaller
            
            vector<int> sums(m,0);
            for(int j = i; j < n; j++) {
                
                for(int row = 0; row < m; row++) {
                    sums[row] += matrix[row][j];
                }
                int ms = maxSumArray(sums, k);
                
                if (ms == k)
                    return ms;
                
                if (res < ms && ms < k)
                    res = ms;

            }
        }
        return res;
    }

    int maxSumArray(vector<int> & arr, int k) {
        int sum = 0, maxS = INT_MIN;
        for (int i = 0; i < arr.size(); i++) {  //it's a trick. Maybe O(n) to solve this problem
            sum += arr[i];
            maxS = std::max(sum, maxS);
            if (sum == k )
                return sum;
            if (sum < 0)
                sum = 0;
        }
        
        if (maxS <= k)
            return maxS;
        
        maxS= INT_MIN;
        set<int>sums;
        sum = 0;
        sums.insert(0);
        
        for (int i = 0; i < arr.size(); i++) {
            sum += arr[i];
            auto it = sums.lower_bound(sum - k);
            if (it != sums.end())
                maxS = std::max(sum - *it, maxS);
            sums.insert(sum);
        }
        return maxS;
    }
};
