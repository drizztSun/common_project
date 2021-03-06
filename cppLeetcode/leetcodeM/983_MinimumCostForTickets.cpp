/*
 
 983. Minimum Cost For Tickets
 
 In a country popular for train travel, you have planned some train travelling one year in advance.
 The days of the year that you will travel is given as an array days.  Each day is an integer from 1 to 365.

 Train tickets are sold in 3 different ways:

 a 1-day pass is sold for costs[0] dollars;
 a 7-day pass is sold for costs[1] dollars;
 a 30-day pass is sold for costs[2] dollars.
 The passes allow that many days of consecutive travel.
 
 For example, if we get a 7-day pass on day 2, then we can travel for 7 days: day 2, 3, 4, 5, 6, 7, and 8.

 Return the minimum number of dollars you need to travel every day in the given list of days.

  

 Example 1:

 Input: days = [1,4,6,7,8,20], costs = [2,7,15]
 Output: 11
 Explanation:
 For example, here is one way to buy passes that lets you travel your travel plan:
 On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
 On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4, ..., 9.
 On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
 In total you spent $11 and covered all the days of your travel.
 
 Example 2:

 Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
 Output: 17
 Explanation:
 For example, here is one way to buy passes that lets you travel your travel plan:
 On day 1, you bought a 30-day pass for costs[2] = $15 which covered days 1, 2, ..., 30.
 On day 31, you bought a 1-day pass for costs[0] = $2 which covered day 31.
 In total you spent $17 and covered all the days of your travel.
  

 Note:

 1 <= days.length <= 365
 1 <= days[i] <= 365
 days is in strictly increasing order.
 costs.length == 3
 1 <= costs[i] <= 1000
 */

#include <vector>
using std::vector;

#include <unordered_set>
using std::unordered_set;

#include <unordered_map>
using std::unordered_map;

class MincostTickets {

public:

    /*
        Approach 1: Dynamic Programming (Day Variant)
        
        Intuition and Algorithm

        For each day, if you don't have to travel today, then it's strictly better to wait to buy a pass. If you have to travel today, you have up to 3 choices: you must buy either a 1-day, 7-day, or 30-day pass.

        We can express those choices as a recursion and use dynamic programming. Let's say dp(i) is the cost to fulfill your travel plan from day i to the end of the plan. Then, if you have to travel today, your cost is:

        \text{dp}(i) = \min(\text{dp}(i+1) + \text{costs}[0], \text{dp}(i+7) + \text{costs}[1], \text{dp}(i+30) + \text{costs}[2])dp(i)=min(dp(i+1)+costs[0],dp(i+7)+costs[1],dp(i+30)+costs[2])

        Complexity Analysis

        Time Complexity: O(W), where W = 365 is the maximum numbered day in your travel plan.

        Space Complexity: O(W).
    */
    int doit_dp_topdown(vector<int>&& days, vector<int>&& costs) {

        unordered_set<int> dates(days.begin(), days.end());
        vector<int> spent(365 + 30, -1);

        std::function<int(int)> search = [&](int i) {
        
            if (i > 365) return 0;
            
            if (spent[i] != -1) return spent[i];
            
            if (dates.count(i) > 0) {
                int ans = INT_MAX;
                vector<int> days{1, 7, 30};
                for(int d = 1; d < 4; d++)
                    ans = std::min(ans, search(i + days[d-1]) + costs[d-1]);
                spent[i] = ans;
            } else {
                spent[i] = search(i+1);
            }
            return spent[i];
        };
        
        return search(1);
    }

    int doit_topdown(vector<int> days, vector<int> costs) {

        vector<int> duration{1, 7, 30};
        vector<int> spent(days.size(), -1);

        std::function<int(int)> search = [&](int index) {

            if (index >= days.size()) return 0;

            if (spent[index] != -1) return spent[index];

            int ans = INT_MAX;
            int j = index;
            for (int i = 0; i < 3; i++) {
                int d = duration[i], c = costs[i];
                while (j < days.size() && days[j] - days[index] < d) {
                    j++;
                }
                ans = std::min(ans, c + search(j));
            }
            return spent[index] = ans;
        };

        return search(0);
    }
    
    int doit_dp_bottomup(vector<int>& days, vector<int>& costs) {
        
        vector<int> dp(366,0);
        vector<int> vis(366,0);
        
        for(int i = 0; i < days.size(); i++){
           vis[days[i]] = 1;
        }
        
        for(int i = 1; i <= 365; i++)
        {
            if(!vis[i]) {
                dp[i] = dp[i-1];
                continue;
            }
            
            int minn = costs[0] + dp[i-1];
            
            minn = std::min(minn, costs[1] + (i >= 7 ? dp[i-7] : 0));
            
            minn = std::min(minn, costs[2] + (i >= 30 ? dp[i-30] : 0));
            
            dp[i] = minn;
        }
        return dp[365];
    }
    
    int doit_dp_bottonup_2(vector<int>& days, vector<int>& cost) {
        vector<int> dp(366, 0);
        unordered_set<int> daysSet(days.begin(), days.end());
        
        for (int i = 1; i < dp.size(); i++) {
            
            if (daysSet.count(i) == 0) {
                dp[i] = dp[i-1];
            } else {
                
                int ans = dp[i-1] + cost[0];
                
                ans = std::min(ans, cost[1] + (i >= 7 ? dp[i-7] : 0));
                ans = std::min(ans, cost[2] + (i >= 30 ? dp[i-30] : 0));
                
                dp[i] = ans;
            }
        }
        return dp[365];
    }
};


void test_983_minimum_cost_for_tickets() {
    
    auto res1 = MincostTickets().doit(vector<int>{1,4,6,7,8,20}, vector<int>{2,7,15});
    
    auto res2 = MincostTickets().doit(vector<int>{1,2,3,4,5,6,7,8,9,10,30,31}, vector<int>{2,7,15});

    return;
}
