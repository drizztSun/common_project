/*
1744. Can You Eat Your Favorite Candy on Your Favorite Day?

You are given a (0-indexed) array of positive integers candiesCount where candiesCount[i] represents the number of candies of the ith type you have. 
You are also given a 2D array queries where queries[i] = [favoriteTypei, favoriteDayi, dailyCapi].

You play a game with the following rules:

You start eating candies on day 0.
You cannot eat any candy of type i unless you have eaten all candies of type i - 1.
You must eat at least one candy per day until you have eaten all the candies.
Construct a boolean array answer such that answer.length == queries.length and answer[i] is true if you can eat a candy of type favoriteTypei 
on day favoriteDayi without eating more than dailyCapi candies on any day, and false otherwise. Note that you can eat different types of candy on the same day, provided that you follow rule 2.

Return the constructed array answer.

 

Example 1:

Input: candiesCount = [7,4,5,3,8], queries = [[0,2,2],[4,2,4],[2,13,1000000000]]
Output: [true,false,true]
Explanation:
1- If you eat 2 candies (type 0) on day 0 and 2 candies (type 0) on day 1, you will eat a candy of type 0 on day 2.
2- You can eat at most 4 candies each day.
   If you eat 4 candies every day, you will eat 4 candies (type 0) on day 0 and 4 candies (type 0 and type 1) on day 1.
   On day 2, you can only eat 4 candies (type 1 and type 2), so you cannot eat a candy of type 4 on day 2.
3- If you eat 1 candy each day, you will eat a candy of type 2 on day 13.
Example 2:

Input: candiesCount = [5,2,6,4,1], queries = [[3,1,2],[4,10,3],[3,10,100],[4,100,30],[1,3,1]]
Output: [false,true,true,false,false]
 

Constraints:

1 <= candiesCount.length <= 105
1 <= candiesCount[i] <= 105
1 <= queries.length <= 105
queries[i].length == 3
0 <= favoriteTypei < candiesCount.length
0 <= favoriteDayi <= 109
1 <= dailyCapi <= 109

*/
#include <vector>

using std::vector;
typedef long long ll;

class CanEatFavoritCandy {

public:

    /*
    
        1744.Can-You-Eat-Your-Favorite-Candy-on-Your-Favorite-Day

        本题就是简单的贪心法。我们令每个query对应的天数为d，糖的种类为t，每日吃糖的极限是cap。

        如果我们慢到极限，每天只吃一颗糖，经过d-1天时就已经把前t种的糖都吃掉了，那么在第d天肯定就吃不到第t种糖。

        反之，如果我们每天吃到极限cap，经过d天后时，仍然还没有吃到第t种糖（最多只吃完了前t-1种糖），那么也宣告失败。

        其余情况下，我们都可以调节每天吃糖的数量在1~cap之间，使得在第d天的时候有机会吃到第t种糖。
    
    */
    
    vector<bool> doit_greedy(vector<int>& candiesCount, vector<vector<int>>& queries) {

        int n = candiesCount.size();
        candiesCount.insert(candiesCount.begin(),0);
        vector<ll>presum(n+1);
        for (int i=1; i<=n; i++)
            presum[i] = presum[i-1]+candiesCount[i];
        
        vector<bool>rets;
        for (auto q: queries)
        {
            ll type = q[0]+1;
            ll day = q[1]+1;
            ll cap = q[2];
                                    
            if (1*(day-1) >= presum[type])            
                rets.push_back(false);                            
            else if (day*cap <= presum[type-1])            
                rets.push_back(false);                            
            else
                rets.push_back(true);            
        }
        return rets;
    }

public:

    /*
        Explanation
        Accumulate the prefix sum A of candiesCount.
        The total number of candies with type < i is A[i].

        On the A[type] / cap day, you must already have ths type of candy.
        On the A[t + 1] - 1 day, you must already have finished ths type of candy.
        So if you want to eat your favorite candy on your favorite day,
        this A[t] // c <= d < A[t + 1] must be True.


        Complexity
        Time O(n)
        Space O(n)
    */
    vector<bool> doit_greedy(vector<int>& candiesCount, vector<vector<int>>& queries) {
        using ll = long long;
        
        vector<ll> presums{0};
        int n = candiesCount.size();
        
        for (auto c : candiesCount)
            presums.push_back(presums.back() + c);

        vector<bool> ans;

        for (const auto& c: queries) {

            ll type = c[0]+1, days = c[1], caps = c[2];

            ans.push_back(days < presums[type] && days >= presums[type-1] /caps);
        }

        return ans;
    }


    vector<bool> doit_greedy(vector<int>& candiesCount, vector<vector<int>>& queries) {
        using ll = long long;
        
        vector<ll> presums{0};
        int n = candiesCount.size();
        
        for (auto c : candiesCount)
            presums.push_back(presums.back() + c);
        
        vector<bool> ans;
        
        for (const auto& c : queries) {
            ll type = c[0]+1, days = c[1]+1, caps = c[2];
            
            if ((days-1) >= presums[type] || caps * days <= presums[type-1])
                ans.push_back(false);
            else
                ans.push_back(true);
        }
        
        return ans;
    }
};