/*
 1125. Smallest Sufficient Team
 
 
 In a project, you have a list of required skills req_skills, and a list of people.  The i-th person people[i] contains a list of skills that person has.

 Consider a sufficient team: a set of people such that for every required skill in req_skills, there is at least one person in the team who has that skill.
 We can represent these teams by the index of each person: for example, team = [0, 1, 3] represents the people with skills people[0], people[1], and people[3].

 Return any sufficient team of the smallest possible size, represented by the index of each person.

 You may return the answer in any order.  It is guaranteed an answer exists.



 Example 1:

 Input: req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]
 Output: [0,2]
 Example 2:

 Input: req_skills = ["algorithms","math","java","reactjs","csharp","aws"], people = [["algorithms","math","java"],
 ["algorithms","math","reactjs"],["java","csharp","aws"],["reactjs","csharp"],["csharp","math"],["aws","java"]]
 Output: [1,2]


 Constraints:

 1 <= req_skills.length <= 16
 1 <= people.length <= 60
 1 <= people[i].length, req_skills[i].length, people[i][j].length <= 16
 Elements of req_skills and people[i] are (respectively) distinct.
 req_skills[i][j], people[i][j][k] are lowercase English letters.
 Every skill in people[i] is a skill in req_skills.
 It is guaranteed a sufficient team exists.
 
 
 */
#include <vector>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::vector;
using std::string;


class SmallestSufficientTeam {
    
public:
    
    vector<int> doit_dp_bitmask(vector<string>&& req_skills, vector<vector<string>>&& people) {

        vector<int> skills;
        for (auto& p : people) {
            int mask = 0;
            for (auto& skill : p)
                mask |= (1 << std::find(req_skills.begin(), req_skills.end(), skill) - begin(req_skills));
            skills.push_back(mask);
        }
        
        auto N = req_skills.size();
        // dp[i, j] i is first i persons, value is bitmask for all reqired skills, so it could be used and bit ops in requied skills.
        vector<int> dp(1<<N, INT_MAX/2);
        dp[0] = 0;
        
        // parents array to move back from the path
        vector<std::pair<int,int>> parents(1<<N);
        int target = (1<<N) - 1;
        
        for (int p = 0; p < people.size(); p++) {
            const int k = skills[p];
            if (k == 0)
                continue;
            
            for (auto i = target; i >= 0; i--) {
                
                if (dp[i|k] > dp[i] + 1) {
                    dp[i|k] = dp[i] + 1;
                    parents[i|k] = {i, p};
                }
            }
        }
        
        int t = target;
        vector<int> ans;
        while (t) {
            ans.push_back(parents[t].second);
            t = parents[t].first;
        }
        
        return ans;
    }
    
    vector<int> doit_dp_bitmask_2(vector<string>&& req_skills, vector<vector<string>>&& people) {
        
        const int n = req_skills.size();
        
        vector<int> skills;
        for (const auto& p : people) {
          int mask = 0;
          for (const string& s: p)
            mask |= (1 << find(begin(req_skills), end(req_skills), s) - begin(req_skills));
          skills.push_back(mask);
        }
        
        unordered_map<int, vector<int>> dp;
        dp[0] = {};
                
        for (int i = 0; i < people.size(); ++i) {
          unordered_map<int, vector<int>> tmp(dp);
          for (const auto& kv : dp) {
            int k = kv.first | skills[i];
            if (!tmp.count(k) || kv.second.size() + 1 < tmp[k].size()) {
              tmp[k] = kv.second;
              tmp[k].push_back(i);
            }
          }
          tmp.swap(dp);
        }
          
        return dp[(1 << n) - 1];
    }
    
    
    
};


void test_1125_smallest_sufficient_team() {
    
    SmallestSufficientTeam().doit_dp_bitmask_2(vector<string>{"java","nodejs","reactjs"}, vector<vector<string>>{{"java"}, {"nodejs"}, {"nodejs","reactjs"}});
    
}
