/*
 312. Burst Balloons
 
 Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

 Find the maximum coins you can collect by bursting the balloons wisely.

 Note:

 You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
 Example:

 Input: [3,1,5,8]
 Output: 167
 Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
              coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167

 */
#include <vector>

using std::vector;

class MaxCoins {
public:
    int doit_dp(vector<int>&& nums) {
        
        nums.push_back(1);
        nums.insert(nums.begin(), 1);
        auto M = nums.size();
        vector<vector<int>> dp(M, vector<int>(M, 0));
        
        for (auto s = 0; s < M-2; s++) {
            
            for (auto j = 1; j < M-1-s; j++) {
                
                for (auto k = j, e = j + s; k <= e; k++) {
                    
                    dp[j][e] = std::max(dp[j][e], nums[k] * nums[j-1] * nums[e+1] + dp[j][k-1] + dp[k+1][e]);
                    
                }
            }
            
        }
        
        return dp[1][M-2];
    }
    
    int doit_dp_2(vector<int>&& nums) {
        
        nums.push_back(1);
        nums.insert(nums.begin(), 1);
        auto M = nums.size();
        vector<vector<int>> dp(M, vector<int>(M, 0));
        
        for (auto s = 1; s < M-1; s++) {
            
            for (auto j = 1; j < M-s; j++) {
                
                for (auto k = j, e = j + s - 1; k <= e; k++) {
                    
                    dp[j][e] = std::max(dp[j][e], nums[k] * nums[j-1] * nums[e+1] + dp[j][k-1] + dp[k+1][e]);
                    
                }
            }
            
        }
        
        return dp[1][M-2];
    }
    
    int doit_dp_1(vector<int>& nums) {
          
         if (nums.empty()) return 0 ;
         int dp[nums.size()][nums.size()] ;
        
         
         memset(dp, 0, sizeof(dp));
         
         for (int i = 0 ; i < nums.size(); i++) {
             int left  = i== 0 ? 1 : nums[i-1];
             int right = i== nums.size()-1 ? 1 : nums[i+1];
             dp[i][i] = left * nums[i]*right;
         }
         
         for (int k = 1 ; k < nums.size() ; k++){
             for (int i = 0; i <nums.size() -k ; i++ ){
                 int curr = 0 ;
                 int ind = -1 ;
                 int j = i+ k ;
                 int subL = i> 0 ? nums[i-1] : 1 ;
                 int subR = j < nums.size()-1 ? nums[j+1] : 1 ;
                 for (int l  = i ; l <= i+ k ; l++){
                     int left = (l-1 >= i) ? dp[i][l-1] : 0  ;
                     int right = (l+1 < nums.size()) ? dp[l+1][j] : 0  ;
                     
                     if (curr < (left + right + subL*subR*nums[l])){
                         curr = left + right + subL*subR*nums[l] ;
                         ind =l ;
                     }
                 }
                 dp[i][i+k] = curr ;
             }
         }

         
         return dp[0][nums.size()-1] ;
     }
};

void test_312_burst_balloons() {
    
    MaxCoins().doit_dp(vector<int>{3, 1, 5, 8});
    
}
