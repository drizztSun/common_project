//
//  1074_NumberOfSubmatricesThatSunToTarget.cpp
//  cppleetcode
//
//  Created by yuxin on 12/12/20.
//  Copyright © 2020 Yuxin Sun. All rights reserved.
//

#include <stdio.h>

#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;

class NumSubmatrixSumTarget {
    
public:
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


    int cal(vector<int>& v, int t){
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
    }
        
public:
    
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {

        int m = matrix.size(), n = matrix[0].size(), res = 0;
        for (int i = 0; i < m; ++i) {
            vector<int> arr(n, 0);
            for (int j = i; j < m; ++j) {
                for (int k = 0; k < n; ++k)
                    arr[k] += matrix[j][k];
                res += cal(arr, target);
                //res += numSubmatrixSumTarget1D(arr, target);
            }
        }
        return res;
    }

};
