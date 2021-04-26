/*

1626. Best Team With No Conflicts


You are the manager of a basketball team. For the upcoming tournament, you want to choose the team with the highest overall score. The score of the team is the sum of scores of all the players in the team.

However, the basketball team is not allowed to have conflicts. A conflict exists if a younger player has a strictly higher score than an older player. A conflict does not occur between players of the same age.

Given two lists, scores and ages, where each scores[i] and ages[i] represents the score and age of the ith player, respectively, return the highest overall score of all possible basketball teams.

 

Example 1:

Input: scores = [1,3,5,10,15], ages = [1,2,3,4,5]
Output: 34
Explanation: You can choose all the players.
Example 2:

Input: scores = [4,5,6,5], ages = [2,1,2,1]
Output: 16
Explanation: It is best to choose the last 3 players. Notice that you are allowed to choose multiple people of the same age.
Example 3:

Input: scores = [1,2,3,5], ages = [8,9,10,1]
Output: 6
Explanation: It is best to choose the first 3 players. 
 

Constraints:

1 <= scores.length, ages.length <= 1000
scores.length == ages.length
1 <= scores[i] <= 106
1 <= ages[i] <= 1000

*/
#include <vector>
#include <map>
#include <functional>
#include <algorithm>

using std::map;
using std::vector;



class BestTimeScore {


public:

    /*
        1626. Best Team With No Conflicts
        将所有的队员按照年纪排序之后，我们很容易发现，所选的队员需要按照能力值呈现一个递增的序列。这就和longest increasing subsequence非常相似。只不过我们的objective不是长度，而是sum。

        状态转移方程如下：

        dp[i] = max{dp[j]+score[i]} for all j s.t. age[j]<=age[i]
    */

    int bestTeamScore(vector<int>& scores, vector<int>& ages) 
    {
        int n = scores.size();
        vector<std::pair<int,int>>players(n);

        vector<int> dp(1000);

        for (int i=0; i<n; i++)
            players[i] = {ages[i], scores[i]};

        sort(players.begin(), players.end());
        dp[0] = players[0].second;

        for (int i=1; i<n; i++)
        {          
            dp[i] = players[i].second;
            for (int j=0; j<i; j++)
            {
                if ((players[j].first < players[i].first && players[j].second <= players[i].second) || players[j].first == players[i].first)
                    dp[i] = std::max(dp[i], dp[j]+players[i].second);
            }                
        }
        
        int ret = 0;
        for (int i=0; i<n; i++)
            ret = std::max(ret, dp[i]);
        
        return ret;
    }

    int doit_best(vector<int>& scores, vector<int>& ages) {
        
        int n = scores.size();
        vector<int> ind(n, 0);
        std::iota(begin(ind), end(ind), 0);
        
        std:sort(begin(ind), end(ind), [&](const int a, const int b) {
            return std::make_pair(ages[a], scores[a]) < std::make_pair(ages[b], scores[b]);
        });
        
        map<int, int> dp {{0, 0}};
        
        for (auto id: ind) {
            
            auto it1 = dp.upper_bound(scores[id]);
            
            const int may = prev(it1)->second + scores[id];
            
            for (auto it2 = dp.lower_bound(scores[id]); it2 != end(dp) && it2->second <= may; it2 = dp.erase(it2));
            
            dp[scores[id]] = may;
        }
        
        return dp.rbegin()->second;
    }

    /*
        O(n*log(n))
    */
    int doit_best(vector<int>& scores, vector<int>& ages) {
        const int n = scores.size();
        vector<int> ind(n);
        for (int i = 0; i < n; ++i) {
            ind[i] = i;
        }
        
        std::sort(ind.begin(), ind.end(), [&](const int &x, const int &y) {
            return std::make_pair(ages[x], scores[x]) < std::make_pair(ages[y], scores[y]);
        });

        map<int, int> dp = {{0, 0}}; // mapping from player's score to team's score

        for (int i = 0; i < n; ++i) {
            // dp is map, or arry with binary_search solution
            // log(n) to locate the upper_boumd, then right side is conflict one, because of less age and higher score
            auto t = dp.upper_bound(scores[ind[i]]);

            // take the left one, score less than current, and age younger or equal.
            // plus the score, it is basic one
            const int may = (--t)->second + scores[ind[i]];

            // 
            t = dp.lower_bound(scores[ind[i]]);

            // Every team's score below "may" are suboptimal and can be deleted.
            for (; t != dp.end() && t->second <= may; dp.erase(t++));

            dp[scores[ind[i]]] = may;
        }
        return dp.rbegin()->second;
    }

    /*
        Actually, this problem is to find the maximum sum of increasing subsequence.
        Very similiar with 300.Longest Increasing Subsequence

        This problem want both age and score are increasing.
        We can sort by age and do DP for scores.
        Sum up, 3 key points:

        Create another arr by {age[i], socres[i]} and sorted by age.
        For each loop, goes back and find maximum for current DP value to it maintain a increasing subsequence.
        The answer could in any place of the dp array.

        Time complexity: O(n^2), 
        space complexity: O(n)
    */
    int doit_dp(vector<int>& scores, vector<int>& ages) {
        const int n = scores.size();
        vector<int> dp(n, 0);
        // first: age
        // second: scores
        vector<std::pair<int, int>> arr(n, {0, 0});
        
        for(int i = 0; i < n; ++i){
            arr[i].first = ages[i];
            arr[i].second = scores[i];
        }

        sort(arr.begin(), arr.end());
        
        int team_score = 0;
        for(int i = 0; i < n; ++i){
            dp[i] = arr[i].second;
            for(int j = i - 1; j >= 0; --j){
                // arr sorted by age, latter element has to have high score to maintain increasing susequence
                if(arr[i].second >= arr[j].second){
                    // update each status
                    dp[i] = std::max(dp[i], dp[j] + arr[i].second); 
                }
            }
            // maximum value could in any place
            team_score = std::max(team_score, dp[i]); 
        }
        return team_score;
    }
};