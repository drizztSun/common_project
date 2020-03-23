/*
 1000. Minimum Cost to Merge Stones
 
There are N piles of stones arranged in a row.  The i-th pile has stones[i] stones.

A move consists of merging exactly K consecutive piles into one pile, and the cost of this move is equal to the total number of stones in these K piles.

Find the minimum cost to merge all piles of stones into one pile.  If it is impossible, return -1.

Example 1:

Input: stones = [3,2,4,1], K = 2
Output: 20
Explanation:
We start with [3, 2, 4, 1].
We merge [3, 2] for a cost of 5, and we are left with [5, 4, 1].
We merge [4, 1] for a cost of 5, and we are left with [5, 5].
We merge [5, 5] for a cost of 10, and we are left with [10].
The total cost was 20, and this is the minimum possible.
Example 2:

Input: stones = [3,2,4,1], K = 3
Output: -1
Explanation: After any merge operation, there are 2 piles left, and we can't merge anymore.  So the task is impossible.
Example 3:

Input: stones = [3,5,1,2,6], K = 3
Output: 25
Explanation:
We start with [3, 5, 1, 2, 6].
We merge [5, 1, 2] for a cost of 8, and we are left with [3, 8, 6].
We merge [3, 8, 6] for a cost of 17, and we are left with [17].
The total cost was 25, and this is the minimum possible.
 
 */

#include <vector>
using std::vector;

class MergeStones {
public:
    int doit(vector<int>&& stones, int K) {
        
        int N = stones.size();
        if ((N-1) % (K-1) != 0)
            return -1;
        
        vector<int> sums(N+1, 0);
        for (int i = 1; i < N+1; i++)
            sums[i] = sums[i-1] + stones[i-1];
        
        vector<vector<int>> dp(N, vector<int>(N, 0));
        
        for (int length = K; length < N + 1; length++)
            for (int i = 0; i < N - length + 1; i++) {
                int j = i + length - 1;
                dp[i][j] = INT_MAX;
                
                for (int t = i; t < j; t += K-1) {
                    dp[i][j] = std::min(dp[i][j], dp[i][t] + dp[t+1][j]);
                }
                
                if ((length -1) % (K-1) == 0)
                    dp[i][j] += sums[j+1] - sums[i];
            }
        
        return dp[0][N-1];
    }
};

class MergeStonesI {
public:
    int doit(vector<int>& stones, int K) {
        int n=stones.size();
        if((n-1)%(K-1)!=0)
            return -1;
        this->K=K;
        prefix=vector<int>(n+1,0);
        for(int i=0;i<n;++i)
            prefix[i+1]=prefix[i]+stones[i];
        
        memo=vector<vector<int>>(n,vector<int>(n,-1));
        return dfs(stones,0,n-1);
    }
private:
    int K;
    vector<int> prefix;
    vector<vector<int>> memo;
    int dfs(vector<int>& stones,int i,int j){
        if(j==i) return 0;
        if(memo[i][j]!=-1) return memo[i][j];
        int res=INT_MAX;
        for(int p=i;p<j;p+=K-1){
            res=std::min(res,dfs(stones,i,p)+dfs(stones,p+1,j));
        }
        if((j-i)%(K-1)==0) res+=prefix[j+1]-prefix[i];
        return memo[i][j]=res;
    }
};

void test_1000_mininum_cost_to_merge_stons() {
    
    auto res1 = MergeStones().doit(vector<int>{3,2,4,1}, 2);
    
    auto res2 = MergeStones().doit(vector<int>{3,2,4,1}, 3);
    
    auto res3 = MergeStones().doit(vector<int>{3,5,1,2,6}, 3);
    
    return;
}
