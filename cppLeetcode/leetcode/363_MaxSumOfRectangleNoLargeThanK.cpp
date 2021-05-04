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
#include <functional>

using std::set;
using std::vector;

class MaxSumOfRectThanK {

public:

    /*
        363.Max-Sum-of-Rectangle-No-Larger-Than-K
        Brutal Force的时间复杂度是o(m*m*n*n)，肯定不明智。

        一个很自然的想法是：选定任意两行之后，可以利用列方向上的累加和数组转化为一维的问题： max sum of subarray No larger than K，时间复杂度可以降为o(m*m*n*logn)。

        1.对于这个一维问题，首先构造横方向上的累加和数组sum，但注意累加和数组sum不会是单调增的，所以不能用数组的二分搜索！

        2.然后，问题已经简化为对于一个数组sum，找到两个位置i和j，使其差不大于k。什么思路？ 从前往后遍历j，搜索在j之前的元素是否有i满足条件 sum[j]-sum[i]<k，更新结果，并将j元素也加入累加和的序列中。

        3.怎么样高效搜索j之前的sum元素呢？希望累加和元素的排练是有序的！但不能是数组，否则每次加入新元素并重排的耗时很长。快速保持有序序列的数据结构可以用顺序集合set，利用函数Set.lower_bound(val)对其迭代器进行二分查找。
        注意，用 auto it = lower_bound(Set.begin(),Set.end(),val) 虽然等价但会耗时非常长。

                        set<int>Set;
                        Set.insert(0);
                        int CurSum=0;
                        for (int j=0; j<N; j++)
                        {
                            CurSum+=sum[j];
                            
                            auto it = Set.lower_bound(CurSum-k); // 返回第一个大于等于CurSum-k的迭代器
                            if (it!=Set.end()) 
                                result = max(result,CurSum-*it);
                            Set.insert(CurSum);
                        }
        4.如果矩阵的行数远远大于列数，一定需要将矩阵转置以后再算，否则超时。
    */
    int doit_heap(vector<vector<int>>& matrix, int k) 
    {
        int M = matrix.size();
        if (M==0) return 0;
        int N = matrix[0].size();

        std::function<int(vector<int>&, int)> helper = [](vector<int>& row,int k)
        {
            set<int>Set({0});
            int preSum = 0;
            int result = INT_MIN;
            for (int i=0; i < row.size(); i++)
            {
                preSum+=row[i];
                auto iter = Set.lower_bound(preSum-k);
                if (iter != Set.end()) 
                    result = std::max(result,preSum-*iter);
                Set.insert(preSum);
            }
            return result;
        };
        
        if (M>N)
        {
            vector<vector<int>>matrix2(N,vector<int>(M,0));
            for (int i=0; i<M; i++)
                for (int j=0; j<N; j++)
                    matrix2[j][i]=matrix[i][j];
            return doit_heap(matrix2,k);
        }
        
        int result = INT_MIN;
        
        for (int i=0; i<M; i++)        
        {
            vector<int>row(N,0);
            for (int j=i; j<M; j++)
            {
                for (int k=0; k<N; k++)
                    row[k]+=matrix[j][k];
                result = std::max(result, helper(row,k));
            }
        }        
        return result;
    }
    
    int doit_dp(vector<vector<int>>& matrix, int k) {
        
        if(matrix.size() == 0) return 0;
        
        int m = matrix.size(), n = matrix[0].size();
        int res = INT_MIN;
        
        std::function<int(vector<int> &, int)> maxSumArray = [](vector<int> & arr, int k) {
            int sum = 0, maxS = INT_MIN;
            for (int i = 0; i < arr.size(); i++) {  
                //it's a trick. Maybe O(n) to solve this problem
                sum += arr[i];
                maxS = std::max(sum, maxS);
                if (sum == k ) return sum;
                if (sum < 0) sum = 0;
            }
            
            if (maxS <= k) return maxS;
            
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
        };

        for(int i = 0; i < n; i++) {  // the number of columns is smaller
            
            vector<int> sums(m,0);

            for(int j = i; j < n; j++) {
                
                for(int row = 0; row < m; row++) {
                    sums[row] += matrix[row][j];
                }

                int ms = maxSumArray(sums, k);
                
                if (ms == k) return ms;
                
                if (res < ms && ms < k) res = ms;

            }
        }
        return res;
    }
};
