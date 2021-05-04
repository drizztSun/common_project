/*
 920. Number of Music Playlists
 
 Your music player contains N different songs and she wants to listen to L (not necessarily different) songs during your trip.  You create a playlist so that:

 Every song is played at least once
 A song can only be played again only if K other songs have been played
 Return the number of possible playlists.  As the answer can be very large, return it modulo 10^9 + 7.

  

 Example 1:

 Input: N = 3, L = 3, K = 1
 Output: 6
 Explanation: There are 6 possible playlists. [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1].
 Example 2:

 Input: N = 2, L = 3, K = 0
 Output: 6
 Explanation: There are 6 possible playlists. [1, 1, 2], [1, 2, 1], [2, 1, 1], [2, 2, 1], [2, 1, 2], [1, 2, 2]
 Example 3:

 Input: N = 2, L = 3, K = 1
 Output: 2
 Explanation: There are 2 possible playlists. [1, 2, 1], [2, 1, 2]
 
 */

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::unordered_map;
using std::vector;

namespace std{

    template<> struct hash<std::pair<int, int>> {
        
        inline size_t operator()(const std::pair<int, int>& a) const {
            
            return std::hash<int>()(a.first) ^ std::hash<int>()(a.second);
        }
    };
}

class NumMusicPlaylists {

    /*
        920.Number-of-Music-Playlists
        此题看到结果需要mod 1e9+7,毫无疑问就需要用到DP.怎么定义状态呢?如果没有任何思路的话,不妨就先顺着题目的意思来.题目里说求L个播放器位置播放N首歌的方法,那么就令dp[i][j]表示有i个播放位置,总共用了j首歌的方案总数.
        注意,这里的"方案"意思是,每相同的两首歌之间至少要有m个间隔.并且"用了j首歌"的意思是,肯定j首歌每首至少用到了一次.

        那么dp[i][j]的状态怎么转移呢?一般而言,我们都会考察dp[i-1][j],dp[i][j-1],dp[i-1][j-1]这些旧状态,看看能否通过它们导出新状态.

        1) 我们先考虑dp[i-1][j],也就是说在第i-1个位置的时候,已经用了j首歌.那么在考虑dp[i][j]时,第i个位置上,我们依旧只需要从这j首歌里找,只要满足间隔条件就行.那么可供选择的歌的数目就是j-K.当然这里要求j>K才行.

        2) 然后我们考虑dp[i-1][j-1],也就是说在第i-1个位置的时候,才用了j-1首歌.那么在考虑dp[i][j]时,在第i个位置上,我们必须用新歌.那么可供选择的歌的数目就是N-(j-1).当然,这里要求N>(j-1).

        至于其他的dp[i][j-1],我们无法从这个状态转移到dp[i][j].

        所以转移方程为:

        if (j>K)
        dp[i][j] += dp[i-1][j]*(j-K)
        if (N>j-1)
        dp[i][j] += dp[i-1][j-1]*(N-j+1)
        那么边界条件是什么呢？其实非常简单，就是dp[1][1]=N. 只有一个播放位置,并且只能放一首歌,自然有N种选择.

        回过头来看一看上面的方程,发现确实很巧妙,任何不符合逻辑的dp[i][j]都不会被赋值。
    */
    int numMusicPlaylists(int N, int L, int K) 
    {
        auto dp = vector<vector<long>>(L+1,vector<long>(N+1,0));
        dp[1][1] = N;
        long MOD = 1e9+7;
        
        for (int i=2; i<=L; i++) {
            for (int j=1; j<=std::min(N,i); j++)
            {
                if (j>K) dp[i][j] += dp[i-1][j]*(j-K);
                dp[i][j]%=MOD;
                if (N>j-1) dp[i][j] += dp[i-1][j-1]*(N-j+1);
                dp[i][j]%=MOD;                
            }
        }
        
        return dp[L][N];
    }

    
    long long int dp(int i, int j, int K, int N, unordered_map<std::pair<int,int>, int>& memo) {
        
        if (i == 0)
            return j == 0 ? 1 : 0;
        
        if (memo.count({i, j}) != 0)
            return memo[{i, j}];
        
        int l = 1000000007;
        
        long long int ans = dp(i-1, j-1, K, N, memo) * (N - j + 1);
        if (j > K) {
            ans += dp(i-1, j, K, N, memo) * (j - K);
        }
        memo[{i, j}] = ans%l;
        return ans%l;
    }
    
    
public:
    int doit2(int N, int L, int K) {
        unordered_map<std::pair<int, int>, int> memo;
        return dp(L, N, K, N, memo);
    }
    
    // [DP] best
    /*
     Let's call dp(n,l,k) the solution of the problem. Notice that any slice of the playlist of length not greater than k+1 must contain only distinct elements.

     Let l⩾1.
     Think about the last l elements of a playlist of length l+1; There are 2 possibilities:

     1） They contain all n elements at least once.
     2） They contain exactly n-1 elements at least once: the first element of the length l+1 list is not included.
     
     1） In the first kind, The suffix of a l+1 list of the first kind is itself （a valid playlist of l elements chosen from n: there are dp(n,l,k) ways to chose it）.
     Then the first element may be chosen arbitrarily to be any of n-k elements not belonging to the first k elements of the suffix. Thus there are (n-k)×dp(n,l,k) lists of the first kind.

     2） Then to the second kind: chose the first element arbitrarily, there are n choices.
     The suffix of a l+1 list of the second kind is itself a valid playlist of l elements chosen from the remaining n-1 elements:
     there are dp(n-1,l,k) ways to chose it. Thus there are n×dp(n-1,l,k) lists of the second kind.

     The recurrence is then
     dp(n,l+1,k) = (n-k)×dp(n,l,k) + n×dp(n-1,l,k)
     */
    int doit_dp_best(int n, int l, int k) {
        const int modulo = 1000000007;
        std::vector<std::vector<long int>> dp(2,std::vector<long int>((l-n+1),0));
        // dp[g][0], without deplcate number, How many possible result we can have, from i elements.
        // g used to be i, i-1. switch back and forth.
        // second index is How many number we can repeat, most is [L-n]
        
        int g(0);
        long int fk(1);
        
        // kf is the basic line, contruct non-deplicate value from i numbers
        for(int i=1; i<=k; ++i){ // not greater then k, we only calculate the base
            fk = (fk*i)%modulo;
        }

        for(int i=k+1; i<=n; ++i){ // DP i from k+1 -> n elements,
            fk = (fk*i)%modulo;
            g ^= 1; // swtich i, i -1
             
            dp[g][0] = fk;
                
            for(int t=i+1; t<=l-(n-i); ++t){ // when i > k, what we gonna reuse elements
                //  dp(n,l+1,k) = (n-k)×dp(n,l,k) + n×dp(n-1,l,k)
                dp[g][t-i] = (((i-k)*dp[g][t-1-i])%modulo + i*dp[g^1][t-i])%modulo;
            }

        }
        
        return dp[g][l-n];
    }  
};