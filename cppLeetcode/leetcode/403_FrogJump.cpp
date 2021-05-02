/*
 
403. Frog Jump

A frog is crossing a river. The river is divided into some number of units, and at each unit, there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.

Given a list of stones' positions (in units) in sorted ascending order, determine if the frog can cross the river by landing on the last stone. 
Initially, the frog is on the first stone and assumes the first jump must be 1 unit.

If the frog's last jump was k units, its next jump must be either k - 1, k, or k + 1 units. The frog can only jump in the forward direction.

Example 1:

Input: stones = [0,1,3,5,6,8,12,17]
Output: true
Explanation: The frog can jump to the last stone by jumping 1 unit to the 2nd stone, then 2 units to the 3rd stone, then 2 units to the 4th stone, then 3 units to the 6th stone, 
4 units to the 7th stone, and 5 units to the 8th stone.
Example 2:

Input: stones = [0,1,2,3,4,8,9,11]
Output: false
Explanation: There is no way to jump to the last stone as the gap between the 5th and 6th stone is too large.
 

Constraints:

2 <= stones.length <= 2000
0 <= stones[i] <= 231 - 1
stones[0] == 0
 
 */

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <set>
#include <functional>

using std::set;
using std::string;
using std::vector;
using std::unordered_set;
using std::unordered_map;

class CanCross {

    /*
        403.Frog-Jump
        比较直观的想法就是DFS搜索，层层递归下去。设计递归函数 bool DFS(pos,jump)表示当青蛙以jump的跨度跳到pos的石头上时，它能否跳到最后。显然，如果此刻的pos不是最后一块石头的话，
        那么就继续考察 DFS(pos+jump-1,jump-1), DFS(pos+jump,jump), DFS(pos+jump+1,jump+1)即可。

        需要注意的细节：1. 如果pos不是石头的位置，直接返回false，2. 下一步的跨度不能小于等于0，否则就死循环。

        以上的算法会LTE。如果思考进一步优化的算法，那显然就是记忆化，把每次搜索过的失败都记录下来。很容易想到，将已经探索过的{pos,jump}共同作为一个key存在一个集合FailureSet里，表明这个状态是失败的，以后DFS过程遇到这个状态就直接返回false。"
    */
    unordered_set<string> FailureSet;
    unordered_set<int> StoneSet;

    bool canCross(vector<int>& stones) 
    {        
        for (auto a:stones)
            StoneSet.insert(a);
        return DFS(stones.back(),1,1);
    }
    
    bool DFS(int dest, int pos, int jump)
    {       
        if (pos==dest)
            return true;
        
        if (StoneSet.find(pos)==StoneSet.end())
            return false;        
        
        string temp = std::to_string(pos) + "#" + std::to_string(jump);
        if (FailureSet.find(temp)!=FailureSet.end())
            return false;
        
        for (int k=std::max(1,jump-1); k<=jump+1; k++)
        {
            if (DFS(dest, pos+k, k))
                return true;            
        }
        
        FailureSet.insert(temp);
        return false;
    }

public:

    bool doit_topdown_dp(vector<int>& stones) {
        
        using ll = long long;
        unordered_set<string> failed;
        int n = stones.size();
        unordered_set<int> stoneSet(begin(stones), end(stones)); 
        
        std::function<bool(int, int)> dfs = [&](int pos, int skip) {
            
            if (pos == stones[n-1]) return true;
            if (stoneSet.count(pos) == 0) return false;
            string key = std::to_string(pos) + "#" + std::to_string(skip);
            if (failed.count(key) > 0) return false;
            
            vector<int> nextstep{skip-1, skip, skip+1};
            
            for (auto step: nextstep) {
                if (step > 0 && stoneSet.count(pos+step) && dfs(pos+step, step)) return true;
            }
            
            failed.insert(key);
            return false;
        };
        
        return dfs(1, 1);
    }

    unordered_set<int>stoneSet;
    set<std::pair<int,int>>failed;

    bool canCross(vector<int>& stones) 
    {
        for (auto x: stones)
            stoneSet.insert(x);
        return dfs(stones, 0, 0);        
    }
    
    bool dfs(vector<int>& stones, int pos, int jump)
    {
        if (pos == stones.back()) return true;
        if (stoneSet.find(pos)==stoneSet.end()) return false;
        if (failed.find({pos, jump})!=failed.end()) return false;
        
        if (jump>1 && dfs(stones, pos+jump-1, jump-1))
            return true;
        if (jump>0 && dfs(stones, pos+jump, jump))
            return true;
        if (dfs(stones, pos+jump+1, jump+1))
            return true;
        
        failed.insert({pos,jump});
        return false;        
    }

public:

    /*
        Approach #5 Using Dynamic Programming[Accepted]
        Algorithm

        In the DP Approach, we make use of a hashmap mapmap which contains key:valuekey:value pairs such that keykey refers to the position at which a stone is present and valuevalue is a set containing the jumpsizejumpsize 
        which can lead to the current stone position. We start by making a hashmap whose keykeys are all the positions at which a stone is present and the valuevalues are all empty except position 0 whose value contains 0. 
        Then, we start traversing the elements(positions) of the given stone array in sequential order. For the currentPositioncurrentPosition, for every possible jumpsizejumpsize in the valuevalue set, we check if currentPosition + newjumpsizecurrentPosition+newjumpsize exists in the mapmap, where newjumpsizenewjumpsize can be either jumpsize-1jumpsize−1, jumpsizejumpsize, jumpsize+1jumpsize+1. If so, we append the corresponding valuevalue set with newjumpsizenewjumpsize. We continue in the same manner. If at the end, the valuevalue set corresponding to the last position is non-empty, we conclude that reaching the end is possible, otherwise, it isn't.

        For more understanding see this animation-

        Current
        1 / 19

        Complexity Analysis
        
        Time complexity : O(n^2). Two nested loops are there.
        Space complexity : O(n^2). hashmaphashmap size can grow upto n^2
    */

    
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
    
    bool doit_dp_dfs(vector<int>&& stones) {

        auto hash_cord = [](const std::pair<int, int>& c) {
            return std::hash<int>()(c.first) ^ std::hash<int>()(c.second);
        };

        auto equal_cord = [](const std::pair<int, int>& a, const std::pair<int, int>& b){
            return a.first == b.first && a.second == b.second;
        };

        using pointset = unordered_set<std::pair<int, int>, decltype(hash_cord), decltype(equal_cord)>;

        std::function<bool(const unordered_set<int>&, int, int, int, pointset&)> search = [&](const unordered_set<int>& stones, int cur, int speed, int target, pointset& memo) {
        
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
            
            memo.insert({cur, speed});
            
            return false;
        };
        
        pointset memo(10, hash_cord, equal_cord);
        unordered_set<int> stones_set;
        
        for (auto c : stones) {
            stones_set.insert(c);
        }
        
        return search(stones_set, 1, 1, stones.back(), memo);
    }
};