/*
 864. Shortest Path to Get All Keys
 
 We are given a 2-dimensional grid. "." is an empty cell, "#" is a wall, "@" is the starting point, ("a", "b", ...) are keys, and ("A", "B", ...) are locks.

 We start at the starting point, and one move consists of walking one space in one of the 4 cardinal directions.  We cannot walk outside the grid, or walk into a wall.
 If we walk over a key, we pick it up.  We can't walk over a lock unless we have the corresponding key.

 For some 1 <= K <= 6, there is exactly one lowercase and one uppercase letter of the first K letters of the English alphabet in the grid.
 This means that there is exactly one key for each lock, and one lock for each key; and also that the letters used to represent the keys and locks were chosen in the same order as the English alphabet.

 Return the lowest number of moves to acquire all keys.  If it's impossible, return -1.

  

 Example 1:

 Input: ["@.a.#","###.#","b.A.B"]
 Output: 8
 Example 2:

 Input: ["@..aA","..B#.","....b"]
 Output: 6
  

 Note:

 1 <= grid.length <= 30
 1 <= grid[0].length <= 30
 grid[i][j] contains only '.', '#', '@', 'a'-'f' and 'A'-'F'
 The number of keys is in [1, 6].  Each key has a different letter and opens exactly one lock.

 
 */

#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

using std::unordered_set;
using std::deque;
using std::vector;
using std::string;
using std::priority_queue;
using std::unordered_map;
using std::queue;


class ShortestPathAllKeys {

    /*
        864.Shortest-Path-to-Get-All-Keys
        传统的BFS是不允许重复访问相同的节点的，否则重复的元素会不停地加入队列，造成爆炸。但明显可以看出，这道题的解可能需要多次访问一个grid。怎么处理呢？

        其实同一个grid被重复走过并不要紧，只要它所携带的“状态”不同即可。什么是“状态”呢？就是可以理解为身上带有了几把钥匙。我第一次经过A点的时候一把钥匙都没有；
        但第二次经过A点的时候，身上多了一把钥匙，这是完全合理的：比如说第一次经过A点是为了进一个死胡同取钥匙，现在再走回头路，是为了出来取解对应的某个锁。相反，如果经过同一个点的时候，“状态”一点都没变的话，显然第二次的路过是完全没有意义的，所以就不会加入队列。

        这道题和847.Shortest Path Visiting All Nodes的解法非常相似。在那题中，相同的node可以在BFS的过程中重复经过，只要对应的（已经访问过的节点）“状态”不一样即可。这两题可以一起体会。
    */
    int shortestPathAllKeys(vector<string>& grid) 
    {
        int m = grid.size();
        int n = grid[0].size();
        
        auto visited = vector<vector<unordered_set<int>>>(m,vector<unordered_set<int>>(n));
        
        queue<vector<int>>q;  // {x,y,state}
        int count = 0;
        
        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
            {
                if (grid[i][j]=='@')
                {
                    q.push({i,j,0});
                    visited[i][j].insert(0);
                }
                    
                else if (grid[i][j]>='a' && grid[i][j]<='f')
                    count++;
            }
        
        int finalState = 0;
        for (int i=0; i<count; i++)
            finalState |= (1<<i);
        
        int step = -1;
        auto dir = vector<std::pair<int,int>>({{1,0},{-1,0},{0,1},{0,-1}});
        
        
        while (!q.empty())
        {
            step++;
            
            int len = q.size();            
            while (len--)
            {
                int x = q.front()[0];
                int y = q.front()[1];
                int state = q.front()[2];
                q.pop();
                
                for (int k=0; k<4; k++)
                {
                    int i = x + dir[k].first;
                    int j = y + dir[k].second;
                    int newState = state;
                    
                    if (i<0||i>=m||j<0||j>=n) continue;

                    if (grid[i][j]=='#') continue;
                    
                    if (grid[i][j]>='A' && grid[i][j]<='F' && ((state>>(grid[i][j]-'A'))&1)==0) continue;
                    
                    if (grid[i][j]>='a' && grid[i][j]<='f')
                        newState |= (1<<(grid[i][j]-'a'));
                    
                    if (visited[i][j].find(newState)!=visited[i][j].end())
                        continue;
                    
                    if (newState == finalState)
                        return step+1;
                    
                    q.push({i,j,newState});
                    visited[i][j].insert(newState);
                
                }
            }
            
        }
        
        return -1;
    }

    
public:
    
    bool isValid(int x, int y, int m, int n){
        return x>=0 && x<m && y>=0 && y<n;
    }
    
    int doit_dijkstra_heap_1(vector<string>& grid) {
        
        int m = grid.size(), n = grid[0].size();
        if(m == 0 || n == 0) return 0;
        
        vector<vector<char>> mat(m, vector<char>(n, '.'));
        int x = 0, y = 0;
        int K = 0;
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++){
                mat[i][j] = grid[i][j];
                if(mat[i][j] == '@'){
                    x = i;
                    y = j;
                }
                if(mat[i][j] >= 'a' && mat[i][j] <= 'f')
                    K++;
            }
        
        
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        
        vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(64, false)));
        visited[x][y][0] = true;
        queue<std::pair<int, std::pair<int, int>>> q;
        q.push({0, {x, y}});
        int count = 0;
        while(!q.empty()){
            int size = q.size();
            for(int i=0;i<size;i++){
                int carry = q.front().first;
                int x = q.front().second.first;
                int y = q.front().second.second;
                q.pop();
                if(carry == ((1 << K) -1 ) )
                   return count;
                for(int i=0;i<4;i++){
                    int k = carry;
                    int x1 = x + dx[i];
                    int y1 = y + dy[i];
                    if(!isValid(x1, y1, m, n) || mat[x1][y1] == '#')
                        continue;
                    if(mat[x1][y1] >= 'a' && mat[x1][y1] <= 'f')
                        k = carry | (1 << (mat[x1][y1] - 'a')  );
                    if(mat[x1][y1] >= 'A' && mat[x1][y1] <= 'F')
                        if(  !(carry &  (1 << (mat[x1][y1] - 'A')   ) ) )
                            continue;
                    if(! visited[x1][y1][k]){
                        visited[x1][y1][k] = true;
                        q.push({k, {x1, y1}});
                    }
                    
                }
            }
            count++;
        }
        return -1;
        
    }
    
    
    int doit_dijkstra_heap(vector<string>& grid) {
        auto M = grid.size(), N = grid[0].size();
        unordered_map<char, int> location;
        
        for (auto i = 0; i < M; i++)
            for (auto j = 0; j < N; j++)
                if (grid[i][j] != '#' && grid[i][j] != '.')
                    location[grid[i][j]] = i * N + j;
       
        auto neighbor = [&](char p) {
            vector<vector<bool>> seen(M, vector<bool>(N, false));
            unordered_map<char, int> distances;
            deque<std::pair<int,int>> buf;
            buf.push_back({location[p], 0});
            seen[location[p]/N][location[p]%N] = true;
            vector<std::pair<int, int>> dir{{-1,0}, {0, 1}, {1, 0}, {0, -1}};
            
            while (!buf.empty()) {
                
                auto c = buf.front();
                int x = c.first / N, y = c.first % N, d = c.second;
                buf.pop_front();
                
                if (grid[x][y] != '.') {
                    distances[grid[x][y]] = d;
                    continue;
                }

                for (auto c : dir) {
                    int xx = c.first + x, yy = c.second + y;
                    if (xx >= 0 && xx < M && yy >= 0 && yy < N && !seen[xx][yy] && grid[xx][yy] != '#') {
                        buf.push_back({xx * N + yy, d + 1});
                        seen[xx][yy] = true;
                    }
                }
            }
            return distances;
        };
        
        unordered_map<char, unordered_map<char, int>> dists;
        double target_state = 0;
        for (auto c : location){
            dists[c.first] = neighbor(c.first);
            if (c.first > 'Z')
                target_state ++;
        }
        target_state = std::pow(2, target_state) - 1;
        
        // Dijksta
        std::priority_queue<std::tuple<int, char, int>> hp;
        hp.push({0, '@', 0});
        unordered_map<char, unordered_map<int, int>> final_dist;
        final_dist['@'][0] = 0;
        
        while (hp.size()) {
            
            auto c = hp.top();
            auto d = std::get<0>(c);
            char t = std::get<1>(c);
            auto stat2 = std::get<2>(c);
            hp.pop();
            
            if (final_dist[d][t] < d)
                continue;
                
            if (stat2 == target_state)
                return d;
            
            for (auto c : dists[t]) {
                auto stat = stat2;
                
                if (c.first > 'Z') {
                    stat |= 1 << (c.first - 'a');
                } else if (c.first <= 'a' && !(stat & (1 << (c.first - 'a') )))
                    continue;
                
                if (c.second + d < final_dist[c.first][stat]) {
                    final_dist[c.first][stat] = c.second + d;
                    hp.push({-c.second + d, c.first, stat});
                }
            }
        }
        
        return 1;
    }
};
