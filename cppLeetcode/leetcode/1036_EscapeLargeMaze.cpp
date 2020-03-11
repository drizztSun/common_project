/*
 
 # 1036. Escape a Large Maze

 # In a 1 million by 1 million grid, the coordinates of each grid square are (x, y) with 0 <= x, y < 10^6.

 # We start at the source square and want to reach the target square.
 # Each move, we can walk to a 4-directionally adjacent square in the grid that isn't in the given list of blocked squares.

 # Return true if and only if it is possible to reach the target square through a sequence of moves.


 # Example 1:

 # Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
 # Output: false
 # Explanation:
 # The target square is inaccessible starting from the source square, because we can't walk outside the grid.


 # Example 2:

 # Input: blocked = [], source = [0,0], target = [999999,999999]
 # Output: true
 # Explanation:
 # Because there are no blocked cells, it's possible to reach the target square.
 
 
 */


#include <vector>
using std::vector;

#include <deque>
using std::deque;

#include <unordered_set>
using std::unordered_set;

namespace std{

    template <> struct hash<pair<int, int>> {
        inline auto operator()(const std::pair<int, int> &v) const {
            std::hash<int> int_hasher;
            return int_hasher(v.first) ^ int_hasher(v.second);
        }
    };
}

class IsEscapePossible {
    
    bool bfs(vector<int> point, unordered_set<std::pair<int, int>>& blockedlist) {
        
        size_t N = 1e6;
        deque<std::pair<int, int>> queue;
        queue.push_back({point[0], point[1]});
        unordered_set<std::pair<int,int>> seen;
        seen.insert({point[0], point[1]});
        vector<std::pair<int, int>> directions{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
        
        while (!queue.empty()) {
            auto c = queue.front();
            queue.pop_front();
            
            if (seen.size() >= 19900)
                return true;
            
            for (auto n : directions) {
                int x = c.first + n.first, y = c.second + n.second;
                std::pair<int,int> s{x, y};
                if (x >= 0 && x < N && y >= 0 && y < N && blockedlist.count(s) == 0 && seen.count(s) == 0) {
                    queue.push_back(s);
                    seen.insert(s);
                }
            }
            
        }
        return false;
    }
    
public:
    bool doit(vector<vector<int>>&& blocked, vector<int>&& source, vector<int>&& target) {
        
        unordered_set<std::pair<int, int>> blockedlist;
        for (auto c : blocked)
            blockedlist.insert({c[0], c[1]});
        
        return bfs(source, blockedlist) ^ bfs(target, blockedlist);
    }
};

void test_1036_escape_large_maze() {
    
    auto res1 = IsEscapePossible().doit(vector<vector<int>>{{0,1}, {1,0}}, vector<int>{0, 0}, vector<int>{0, 2});
    
    auto res2 = IsEscapePossible().doit(vector<vector<int>>{}, vector<int>{0, 0}, vector<int>{99999, 99999});
    
    return;
}
