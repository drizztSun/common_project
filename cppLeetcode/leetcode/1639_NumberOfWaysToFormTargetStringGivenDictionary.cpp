//
//  1639_NumberOfWaysToFormTargetStringGivenDictionary.cpp
//  cppleetcode
//
//  Created by yuxin on 12/17/20.
//  Copyright © 2020 Yuxin Sun. All rights reserved.
//

#include <stdio.h>

#include <vector>
#include <string>
#include <unordered_map>
#include <array>


using std::array;
using std::unordered_map;
using std::vector;
using std::string;


class NumberOfWaysToFromTargetString {


public:
    
    int doit_(vector<string>& words, string target) {
            
        int n = words.size(),i,j,k,mod=1e9+7;
        int m = words[0].length();
        int len = target.length();
        long long ans=0,ch=0,sum=0;
        
        int cnt[26][m+1];
        memset(cnt,0,sizeof(cnt));
        
        for(int j=1;j<=m;j++)
        {
            for(int i=0;i<n;i++)
                cnt[words[i][j-1]-'a'][j]++;
        }
        
        int dp[len+1][m+1];
        memset(dp,0,sizeof(dp));
        
        dp[0][0]=1;
        
        for(i=1;i<=len;i++)
        {
            for(j=i;j<=m-(len-i);j++)
            {
                ch = cnt[target[i-1]-'a'][j];
                sum = 0;
                
                for(k=j-1;k>=i-1;k--)
                    sum += dp[i-1][k];
                
                dp[i][j] = (sum*ch)%mod;
            }
        }
        
        for(i=0;i<=m;i++)
            ans = (ans+dp[len][i])%mod;
        
        return (int)ans;
    }
    

    /*
    1639.Number-of-Ways-to-Form-a-Target-String-Given-a-Dictionary
    此题有点类似1621的感觉。令dp[i][k]表示我们只构建构建target[0:i]，并且最多用到dictionary里面（所有词）的第k个字母，有多少种方案。根据套路，突破口依然是target的第i个字母、词库里的第k个字母。

    首先，第一种情况是，target[0:i]的选择根本不考虑词库里的第k个字母，完全靠第0~k-1个字母来构造，那么就有dp[i][k] = dp[i][k-1]。

    第二种情况是，如果词库里有一些单词的第k个字母与target[i]相同，那么我们可以考虑target[i]用它们来构造，因此有额外的方案dp[i][k] += dp[i-1][k-1]*count[k]，其中count[k]表示词库里有多少单词的第k个字母与target[i]相同。

    最终的答案就是dp[n][m]. 其中n是target的长度，m是词库里最长的单词长度。

     
     word     x x [k] x k' x x x
     target   Y Y [i] Y i' Y Y Y
     
     dp[i][k] : how many ways to form target[0:i] using word[0:k]
     
     1.  we do not use word[k] to form target[i]
     dp[i][k] = dp[i][k-1]
     
     2. we use word[k] to form target[i]
     if (can do that)
        dp[i][k] = dp[i-1][k-1] * count(how many word[k] == target[i])
     
     n, m = target.length(), word.length()
     
     return dp[n][m]
    */
    int doit_dp(vector<string>&& words, string target) {

        int M = words[0].length(), N = target.length();
        int kMod = 1e9 + 7;

        vector<unordered_map<int, int>> counter(M+1);
        //vector<array<int, 127>> counter(M+1);

        for (const auto& w : words) {
            for (int i = 1; i <= M; i++)
                counter[i][w[i-1] - 'a']++;
        }

        vector<vector<long>> dp(M+1, vector<long>(N+1));
        target = "#" + target;

        for (int i = 0; i <= M; i++)
            dp[i][0] = 1;

        for (int i = 1; i <= M; i++) {

            for (int j = 1; j <= N; j++) {

                dp[i][j] = dp[i-1][j];

                //if (counter[i][target[j] - 'a'] > 0)
                if (counter[i].count(target[j] - 'a') > 0)
                    dp[i][j] = (dp[i][j] + dp[i-1][j-1] * counter[i][target[j]-'a']) % kMod;
            }
        }
        return dp[M][N];
    }
};


void test_1639_() {
    
    NumberOfWaysToFromTargetString().doit_dp(vector<string>{"acca","bbbb","caca"}, "aba");
}
