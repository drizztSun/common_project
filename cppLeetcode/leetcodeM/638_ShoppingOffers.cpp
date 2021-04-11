/*
638. Shopping Offers

In LeetCode Store, there are some kinds of items to sell. Each item has a price.

However, there are some special offers, and a special offer consists of one or more different kinds of items with a sale price.

You are given the each item's price, a set of special offers, and the number we need to buy for each item. The job is to output the lowest price you have to pay for exactly certain items as given, where you could make optimal use of the special offers.

Each special offer is represented in the form of an array, the last number represents the price you need to pay for this special offer, other numbers represents how many specific items you could get if you buy this offer.

You could use any of special offers as many times as you want.

Example 1:
Input: [2,5], [[3,0,5],[1,2,10]], [3,2]
Output: 14
Explanation: 
There are two kinds of items, A and B. Their prices are $2 and $5 respectively. 
In special offer 1, you can pay $5 for 3A and 0B
In special offer 2, you can pay $10 for 1A and 2B. 
You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer #2), and $4 for 2A.
Example 2:
Input: [2,3,4], [[1,1,0,4],[2,2,1,9]], [1,2,1]
Output: 11
Explanation: 
The price of A is $2, and $3 for B, $4 for C. 
You may pay $4 for 1A and 1B, and $9 for 2A ,2B and 1C. 
You need to buy 1A ,2B and 1C, so you may pay $4 for 1A and 1B (special offer #1), and $3 for 1B, $4 for 1C. 
You cannot add more items, though only $9 for 2A ,2B and 1C.
Note:
There are at most 6 kinds of items, 100 special offers.
For each item, you need to buy at most 6 of them.
You are not allowed to buy more items than you want, even if that would lower the overall price.

*/
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

using std::string;
using std::unordered_map;
using std::vector;


class ShoppingOffers {

    /*
        638.Shopping-Offers
        设计递归函数dfs(state)，其中state表示还有哪些物品没有采购，返回的值表示采购完这些物品的最少代价。

        考虑到最多只有6件物品，每个物品最多6个。所以我们用18个bit的二进制数来表示状态。每3个bit可以表示该种物品的数量（从0到7）。

        在dfs(state)里，为我们尝试每一种合法的offer，将state更新后递归处理。我们取所有尝试中代价最小的结果，并记录在memo[state]里面。

        需要注意的细节：

        有些offer是不合算的，可以提前从special里排除掉；
        在dfs(state)里，除了尝试offer，还可以直接从prices里面按原价采购每一件物品。
    */


    unordered_map<string,int>Map;
    int N;
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) 
    {
        N=price.size();
        vector<vector<int>>specials;
        for (int i=0; i<special.size(); i++)
        {
            int sum=0;
            for (int j=0; j<N; j++)
                sum+=special[i][j]*price[j];
            if (sum>special[i].back())
                specials.push_back(special[i]);
        }
                
        string key;
        for (int i=0; i<N; i++)
            key+="0";
        Map[key]=0;
        
        return DFS(price,specials,needs);        
    }
    
    string getKey(vector<int>& needs)
    {
        string key;
        for (int i=0; i<needs.size(); i++)
            key += std::to_string(needs[i]);
        return key;
    }
    
    int DFS(vector<int>& price, vector<vector<int>>& specials, vector<int>& needs)
    {
        string key=getKey(needs);
        if (Map.find(key)!=Map.end())
            return Map[key];
        
        int result=INT_MAX;
        int special_used=0;
        for (int i=0; i<specials.size(); i++)
        {
            int flag=1;
            for (int j=0; j<N; j++)
            {
                if (specials[i][j]>needs[j])
                {
                    flag=0;
                    break;
                }
            }
            if (flag==1)
            {
                special_used=1;
                vector<int> needs_temp = needs;
                for (int j=0; j<N; j++)
                    needs_temp[j]=needs[j]-specials[i][j];                
                result = std::min(result,specials[i][N]+DFS(price,specials,needs_temp));
            }
        }
        if (special_used==0)
        {
            result=0;
            for (int i=0; i<N; i++)
                result+=price[i]*needs[i];
        }
        Map[key]=result;   
        
        return result;
    }

public:

    int memo[1<<18];
    int N;   

    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) 
    {
        N=price.size();
        vector<vector<int>>specials;
        for (int i=0; i<special.size(); i++)
        {
            int sum=0;
            for (int j=0; j<N; j++)
                sum+=special[i][j]*price[j];
            if (sum>special[i].back())
                specials.push_back(special[i]);
        }

        int state = 0;
        for (int i=0; i<N; i++)
            state += needs[i]<<(i*3);
                
        return dfs(state, price,specials);
    }
    
    int dfs(int state, vector<int>& price, vector<vector<int>>& specials)
    {        
        if (memo[state]!=0) return memo[state];

        int ret = 0;
        for (int i=0; i<N; i++)
            ret += (state>>(i*3))%8 * price[i];

        for (auto comb: specials)
        {
            int flag = 1;
            for (int i=0; i<N; i++)
            {
                if ((state>>(i*3))%8 < comb[i])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag==0) continue;

            int state2 = state;
            for (int i=0; i<N; i++)
                state2 -= comb[i]*(1<<(i*3));
            ret = min(ret, comb[N] + dfs(state2, price, specials));
        }

        memo[state] = ret;
        return ret;
    }    

public:

    int doit_dfs_dp(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {

        unordered_map<string, int> status;

        auto key = [](vector<int>& needs) {
            string res;
            for (auto c: needs)
                res += std::to_string(c) + "#";
            return res;
        };

        vector<int> zeros(needs.size(), 0);
        status[key(zeros)] = 0;

        std::function<int(vector<int>)> dfs = [&](vector<int> remains) {

            string keys = key(remains);

            if (status.count(keys) > 0) return status[keys];

            int nooffer = 0;
            for (int i = 0; i < remains.size(); i++) 
                nooffer += remains[i] * price[i];
            
            
            for (int i = 0; i < special.size(); i++) {
                
                int flag = 1;
                for (int j = 0; j < special[i].size()-1; j++) {

                    if (special[i][j] > remains[j]) {
                        flag = 0; 
                        break;
                    }
                }

                if (flag) {
                    vector<int> afteroffer(remains.size(), 0);
                    for (int k = 0; k < remains.size(); k++)
                        afteroffer[k] = remains[k] - special[i][k];
                    
                    nooffer = std::min(nooffer, special[i].back() + dfs(afteroffer));
                }
            }

            return status[keys] = nooffer;
        };

        return dfs(needs);
    }
};