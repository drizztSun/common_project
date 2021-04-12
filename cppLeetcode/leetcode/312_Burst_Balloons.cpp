/*
 312. Burst Balloons
 
 Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. 
 If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

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

    /*
        312.Burst-Balloons
        此题的关键是找出递推关系式.从上往下的比较容易理解.

        令score[left,right]表示我们想消除[left,right]中所有元素能够得到的分数.消除所有元素的话,肯定有最后一枪:假设最后一枪是k,那么在打灭k之前,一定已经打灭了[left,k-1]和[k+1,right],
        这两部分的得分可以提前算出来,即score[left,k-1]和score[k+1,right].另外,最后打的K也会得分,分数是什么?注意,应该是nums[left-1]*nums[k]*nums[right+1],即涉及到[left,right]两端外的这两个元素.

        所以总的递推关系:

        for (k=left, k<=right; k++)
        score(left,right) = max(score(left,k-1)+nums[left-1]*nums[k]*nums[right+1]+score(k+1,right));
        这种关系可以由上往下通过递归实现,也可以由下而上写成动态规划的形式. 单纯递归的话可能会有重复的函数调用,采用记忆化存在dp数组的话就和动态规划完全一样了.
    */
    int maxCoins(vector<int>& nums) 
    {
        int N = nums.size();
        nums.insert(nums.begin(),1);
        nums.push_back(1);
        
        auto dp = vector<vector<int>>(N+2,vector<int>(N+2,0));
        
        for (int len=1; len<=N; len++)
            for (int i=1; i+len-1<=N; i++)
            {
                int j = i+len-1;
                for (int k=i; k<=j; k++)
                    dp[i][j] = max(dp[i][j], dp[i][k-1]+dp[k+1][j]+nums[i-1]*nums[k]*nums[j+1]);                
            }        
        
        return dp[1][N];
    }


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