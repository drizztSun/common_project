/*
 818. Race Car
 
 Your car starts at position 0 and speed +1 on an infinite number line.  (Your car can go into negative positions.)

 Your car drives automatically according to a sequence of instructions A (accelerate) and R (reverse).

 When you get an instruction "A", your car does the following: position += speed, speed *= 2.

 When you get an instruction "R", your car does the following: if your speed is positive then speed = -1 , otherwise speed = 1.  (Your position stays the same.)

 For example, after commands "AAR", your car goes to positions 0->1->3->3, and your speed goes to 1->2->4->-1.

 Now for some target position, say the length of the shortest sequence of instructions to get there.

 Example 1:
 Input:
 target = 3
 Output: 2
 
 Explanation:
 The shortest instruction sequence is "AA".
 Your position goes from 0->1->3.
 
 Example 2:
 Input:
 target = 6
 Output: 5
 
 Explanation:
 The shortest instruction sequence is "AAARA".
 Your position goes from 0->1->3->7->7->6.
 
 */

#include <stdio.h>

#include <deque>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

using std::queue;
using std::unordered_map;
using std::vector;
using std::deque;


class RaceCar {
    
public:
    
    using Pair = std::pair<int, int>;
    using Pairs = vector<Pair>;
    using Queue = queue<Pair>;
    using Seen = unordered_map<int, unordered_map<int, bool>>;
    
    /*
     Perform BFS on each state of {position, velocity} starting with position 0 and velocity 1.
     There are 2 use cases to consider when formulating the next depths' candidates from each of the k states in the q at the current depth:

     Case 1: accelerate in the same direction if and only if the acceleration is "productive", ie.
     if we want to reach the target T, then only accelerate towards T, do not accelerate away from T. Note: this pruning condition is necessary to avoid TLE.
     Case 2: reverse direction
     */
    
    int doit_bfs(int T, Seen seen = {}, int depth = 0) {
        Queue q{{{ 0, 1 }}};
        seen[0][1] = true;
        for (;;) {
            int k = q.size();
            while (k--) {
                auto [pos, vel] = q.front(); q.pop();
                if (pos == T)
                    return depth;  // 🎯 target T found
                Pairs cand;
                if (abs(T - (pos + vel)) < T)
                    cand.push_back({ pos + vel, 2 * vel});
                
                cand.push_back({ pos, vel < 0 ? 1 : -1 });
                for (auto [pos, vel]: cand)
                    if (!seen[pos][vel])
                        q.push({ pos, vel }), seen[pos][vel] = true;
            }
            ++depth;
        }
        return -1;
    }
    
    int doit_dp(int target) {
        
        vector<int> dp(target+3, INT_MAX);
        dp[0] = 0, dp[1] = 1, dp[2] = 4;
        
        if (target < 3)
            return dp[target];
        
        for (auto i = 3; i < dp.size(); i++) {
            int k = floor(log2(i)) + 1;
            
            if (pow(2, k) - 1 == i) {
                dp[i] = k;
                continue;
            }
            
            for (auto j = 0; j < k-1; j++) {
                dp[i] = std::min(dp[i], dp[i - pow(2, k-1) + pow(2, j)] + k - 1 + 2 + j);
            }
            
            if (pow(2, k) - 1 - i < i) {
                dp[i] = std::min(dp[i], dp[pow(2, k) - 1 - i] + k + 1);
            }
        }
        
        return dp[target];
    }
    
    int doit_bfs_1(int target) {
     
        deque<std::tuple<int, int, int>> pos;
        pos.push_back({0, 1, 0});
        int res = 2*31;
        
        while (!pos.empty()) {
            
            auto c = pos.front();
            auto position = std::get<0>(c), speed = std::get<1>(c), length = std::get<2>(c);
            pos.pop_front();
            
            if (length > res)
                continue;
            
            if (position == target) {
                res = std::min(res, length);
            }
            
            pos.push_back({position + speed, 2 * speed, length + 1});
            
            if ((position + speed > target && speed > 0) || (position + speed < target && speed < 0)) {
                pos.push_back({position, speed > 0 ? -1 : 1, length+1});
            }
        }
        
        return res;
    }

};

void test_818_racecar() {
    RaceCar().doit_dp(1);
}
