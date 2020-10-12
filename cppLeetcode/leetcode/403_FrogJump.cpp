/*
 
 403. Frog Jump
 
 A frog is crossing a river. The river is divided into x units and at each unit there may or may not exist a stone.
 The frog can jump on a stone, but it must not jump into the water.

 Given a list of stones' positions (in units) in sorted ascending order, determine if the frog is able to cross the river by landing on the last stone.
 Initially, the frog is on the first stone and assume the first jump must be 1 unit.

 If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units. Note that the frog can only jump in the forward direction.

 Note:

 The number of stones is ≥ 2 and is < 1,100.
 Each stone's position will be a non-negative integer < 231.
 The first stone's position is always 0.
 Example 1:

 [0,1,3,5,6,8,12,17]

 There are a total of 8 stones.
 The first stone at the 0th unit, second stone at the 1st unit,
 third stone at the 3rd unit, and so on...
 The last stone at the 17th unit.

 Return true. The frog can jump to the last stone by jumping
 1 unit to the 2nd stone, then 2 units to the 3rd stone, then
 2 units to the 4th stone, then 3 units to the 6th stone,
 4 units to the 7th stone, and 5 units to the 8th stone.
 Example 2:

 [0,1,2,3,4,8,9,11]

 Return false. There is no way to jump to the last stone as
 the gap between the 5th and 6th stone is too large.

 
 */

#include <vector>
#include <unordered_set>
#include <unordered_map>

using std::vector;
using std::unordered_set;
using std::unordered_map;

auto hash_cord = [](const std::pair<int, int>& c) {
    return std::hash<int>()(c.first) ^ std::hash<int>()(c.second);
};

auto equal_cord = [](const std::pair<int, int>& a, const std::pair<int, int>& b){
    return a.first == b.first && a.second == b.second;
};

using pointset =  unordered_set<std::pair<int, int>, decltype(hash_cord), decltype(equal_cord)>;

class CanCross {

public:
    
    bool doit_dp(vector<int>& stones) {
        unordered_map<int, unordered_set<int>> dp;
        dp.clear();
        int u = 0, v = 0, w = 0;
        unordered_set<int> st;
        unordered_set<int>::iterator it;
        dp[0].insert(1);
        
        for(int i = 0; i < stones.size(); ++ i)
            st.insert(stones[i]);
        
        for(int i = 0; i < stones.size(); ++ i){
            u = stones[i];
            
            if(dp.find(u) == dp.end())
                continue;
            
            if(u == stones[stones.size() - 1])
                break;
        
            for(it = dp[u].begin(); it != dp[u].end(); ++ it){
                w = *it;
                v = u + w;
                if(st.find(v) != st.end() && v > u){
                    dp[v].insert(w - 1);
                    dp[v].insert(w);
                    dp[v].insert(w + 1);
                }
            }
        }
        return dp.find(u) != dp.end() && dp[u].size() > 0;
    }
    
    bool search(const unordered_set<int>& stones, int cur, int speed, int target, pointset& memo) {
        
        if (memo.count({cur, speed}))
            return false;
        
        if (cur == target)
            return true;
        
        if (cur > target || cur < 0 || speed <= 0 || stones.count(cur) == 0)
            return false;
        
        for (auto c : vector<int>{speed-1, speed, speed+1}) {
            if (stones.count(cur+c) > 0 && search(stones, cur+c, c, target, memo))
                return true;
        }
        
        memo.insert(std::make_pair(cur, speed));
        return false;
    }
    
    bool doit_dp_dfs(vector<int>&& stones) {
        
        pointset memo(10, hash_cord, equal_cord);
        unordered_set<int> stones_set;
        
        for (auto c : stones) {
            stones_set.insert(c);
        }
        
        return search(stones_set, 1, 1, stones.back(), memo);
    }
};


void test_403_frog_jump() {
    CanCross().doit_dp_dfs(vector<int>{0,1,3,4,5,7,9,10,12});
}

