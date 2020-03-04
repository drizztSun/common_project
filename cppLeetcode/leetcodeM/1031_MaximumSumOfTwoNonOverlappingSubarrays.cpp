/*
 
 
 # 1031. Maximum Sum of Two Non-Overlapping Subarrays

 # Given an array A of non-negative integers, return the maximum sum of elements in two non-overlapping (contiguous) subarrays,
 # which have lengths L and M.  (For clarification, the L-length subarray could occur before or after the M-length subarray.)

 # Formally, return the largest V for which V = (A[i] + A[i+1] + ... + A[i+L-1]) + (A[j] + A[j+1] + ... + A[j+M-1]) and either:

 # 0 <= i < i + L - 1 < j < j + M - 1 < A.length, or
 # 0 <= j < j + M - 1 < i < i + L - 1 < A.length.


 # Example 1:

 # Input: A = [0, 6, 5, 2, 2, 5, 1, 9, 4], L = 1, M = 2
 # Output: 20
 # Explanation: One choice of subarrays is [9] with length 1, and [6, 5] with length 2.

 # Example 2:

 # Input: A = [3, 8, 1, 3, 2, 1, 8, 9, 0], L = 3, M = 2
 # Output: 29
 # Explanation: One choice of subarrays is [3, 8, 1] with length 3, and [8, 9] with length 2.

 # Example 3:

 # Input: A = [2, 1, 5, 6, 0, 9, 5, 0, 3, 8], L = 4, M = 3
 # Output: 31
 # Explanation: One choice of subarrays is [5, 6, 0, 9] with length 4, and [3, 8] with length 3.


 # Note:

 # L >= 1
 # M >= 1
 # L + M <= A.length <= 1000
 # 0 <= A[i] <= 1000
 
 
 */

#include <vector>

using std::vector;


class MaxSumTwoNoOverlap {
    
public:
    
    int doit(vector<int>&& A, int L, int M) {
        
        vector<vector<int>> lArr(A.size(), {0, 0});
        vector<vector<int>> mArr(A.size(), {0, 0});
        int lwnd = 0, mwnd = 0;
        
        for (int i = 0; i < A.size(); i++) {
            
            lwnd += A[i];
            if (i - L >= -1) {
                lArr[i][0] = lwnd;
                if (i - L >= 0)
                    lArr[i-L][1] = lwnd;
                lwnd -= A[i-L+1];
            }
            
            mwnd += A[i];
            if (i - M >= -1) {
                mArr[i][0] = mwnd;
                if (i - M >= 0)
                    mArr[i-M][1] = mwnd;
                mwnd -= A[i-M+1];
            }
        }
        
        for (size_t i = 1; i < lArr.size(); i++) {
            lArr[i][0] = std::max(lArr[i][0], lArr[i-1][0]);
            mArr[i][0] = std::max(mArr[i][0], mArr[i-1][0]);
        }
        
        for (size_t i = lArr.size() - 2; i > -1; i--) {
            lArr[i][1] = std::max(lArr[i][1], lArr[i+1][1]);
            mArr[i][1] = std::max(mArr[i][1], mArr[i+1][1]);
        }
        
        int ans = 0;
        for (size_t i = 0; i < lArr.size(); i++) {
            ans = std::max(ans, std::max(lArr[i][0] + mArr[i][1], mArr[i][0] + lArr[i][1]));
        }
        
        return ans;
    }
    
    int doit1(vector<int>& A, int L, int M) {
        
        int N = A.size();
        vector<int> preSum(N+1, 0);
        vector<int> firstL(preSum), firstM(preSum), lastL(preSum), lastM(preSum);
        
        for(int i = 1; i <= N; i++)
            preSum[i] = preSum[i-1] + A[i-1];
        
        //[0,i) [i,N)
        for(int i = L; i <= N; i++)
            firstL[i] = std::max(firstL[i-1], preSum[i]-preSum[i-L]);
        
        for(int i = N-M; i >= 0; i--)
            lastM[i] = std::max(lastM[i+1], preSum[i+M]-preSum[i]);
        
        for(int i = M; i <= N; i++)
            firstM[i] = std::max(firstM[i-1], preSum[i]-preSum[i-M]);
        
        for(int i = N-L; i >= 0; i--)
            lastL[i] = std::max(lastL[i+1], preSum[i+L]-preSum[i]);
        
        int res = 0;
        for(int i = 0; i <= N; i++){
            res = std::max(res, firstL[i]+lastM[i]);
            res = std::max(res, firstM[i]+lastL[i]);
        }
        return res;
    }
};


void test_1031_Maximum_Sum_of_Two_Non_Overlapping_Subarrays() {
    
    
    auto res1 = MaxSumTwoNoOverlap().doit(vector<int>{0, 6, 5, 2, 2, 5, 1, 9, 4}, 1, 2);
    
    auto res2 = MaxSumTwoNoOverlap().doit(vector<int>{3, 8, 1, 3, 2, 1, 8, 9, 0}, 3, 2);
    
    auto res3 = MaxSumTwoNoOverlap().doit(vector<int>{2, 1, 5, 6, 0, 9, 5, 0, 3, 8}, 4, 3);
    
    return;
}
