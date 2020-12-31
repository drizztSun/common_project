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

using std::map;
using std::vector;



class BestTimeScore {
public:

    /*
    O(n*log(n))
    */
    int doit_(vector<int>& scores, vector<int>& ages) {
        const int n = scores.size();
        vector<int> ind(n);
        for (int i = 0; i < n; ++i) {
            ind[i] = i;
        }
        
        sort(ind.begin(), ind.end(), [&](const int &x, const int &y) {
            return std::make_pair(ages[x], scores[x]) < std::make_pair(ages[y], scores[y]);
        });

        map<int, int> dp = {{0, 0}}; // mapping from player's score to team's score
        for (int i = 0; i < n; ++i) {
            
            auto t = dp.upper_bound(scores[ind[i]]);
            const int may = (--t)->second + scores[ind[i]];
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
    Time complexity: O(n * n), space complexity: O(n)
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