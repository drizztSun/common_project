/*
1728. Cat and Mouse II

A game is played by a cat and a mouse named Cat and Mouse.

The environment is represented by a grid of size rows x cols, where each element is a wall, floor, player (Cat, Mouse), or food.

Players are represented by the characters 'C'(Cat),'M'(Mouse).
Floors are represented by the character '.' and can be walked on.
Walls are represented by the character '#' and cannot be walked on.
Food is represented by the character 'F' and can be walked on.
There is only one of each character 'C', 'M', and 'F' in grid.
Mouse and Cat play according to the following rules:

Mouse moves first, then they take turns to move.
During each turn, Cat and Mouse can jump in one of the four directions (left, right, up, down). They cannot jump over the wall nor outside of the grid.
catJump, mouseJump are the maximum lengths Cat and Mouse can jump at a time, respectively. Cat and Mouse can jump less than the maximum length.
Staying in the same position is allowed.
Mouse can jump over Cat.
The game can end in 4 ways:

If Cat occupies the same position as Mouse, Cat wins.
If Cat reaches the food first, Cat wins.
If Mouse reaches the food first, Mouse wins.
If Mouse cannot get to the food within 1000 turns, Cat wins.
Given a rows x cols matrix grid and two integers catJump and mouseJump, return true if Mouse can win the game if both Cat and Mouse play optimally, otherwise return false.

 

Example 1:



Input: grid = ["####F","#C...","M...."], catJump = 1, mouseJump = 2
Output: true
Explanation: Cat cannot catch Mouse on its turn nor can it get the food before Mouse.
Example 2:



Input: grid = ["M.C...F"], catJump = 1, mouseJump = 4
Output: true
Example 3:

Input: grid = ["M.C...F"], catJump = 1, mouseJump = 3
Output: false
Example 4:

Input: grid = ["C...#","...#F","....#","M...."], catJump = 2, mouseJump = 5
Output: false
Example 5:

Input: grid = [".M...","..#..","#..#.","C#.#.","...#F"], catJump = 3, mouseJump = 1
Output: true
 

Constraints:

rows == grid.length
cols = grid[i].length
1 <= rows, cols <= 8
grid[i][j] consist only of characters 'C', 'M', 'F', '.', and '#'.
There is only one of each character 'C', 'M', and 'F' in grid.
1 <= catJump, mouseJump <= 8

*/

#include <vector>
#include <string>
#include <queue>
#include <array>


using std::queue;
using std::array;
using std::vector;
using std::string;
using std::pair;


class CatAndMouseII {


    const int dirs[5] = {-1, 0, 1, 0, -1};
    
public:
    
    bool canMouseWin(vector<string>& grid, int cj, int mj) {
        
        int m = grid.size(), n = grid[0].size();
// [cx, cy, mx, my, turn(cat 0, mouse 1), 
//   {
//       # of cat-win neighbors,
//	     # of mouse-win neighbors,
//       final state{0(unclear), 1(mouce win), 2(cat win)}
//    }
//  ]
        int states[9][9][9][9][2][3]{}; 
        int rs[2][9][9]{}; // number of reachable cells from current location for cat and mouse within catjump and mousejump
        
        vector<int> x(2), y(2), z(2);
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                
                if(grid[i][j] == '#') continue;
                if(grid[i][j] == 'C') x = {i, j};
                if(grid[i][j] == 'M') y = {i, j};
                if(grid[i][j] == 'F') z = {i, j};
                
                rs[0][i][j] = rs[1][i][j] = 1;

                for(int k = 0; k < 4; k++) {
                    for(int len = 1; len <= std::max(cj, mj); len++) {
                        int xx = i + len * dirs[k];
                        int yy = j + len * dirs[k + 1];
                        if(xx < 0 || xx >= m || yy < 0 || yy >= n || grid[xx][yy] == '#') break;
                        if(len <= cj) rs[0][i][j]++;
                        if(len <= mj) rs[1][i][j]++;
                    }
                }
            }
        }

		// bfs: a state will be added to the queue under 2 conditions:
		// 1. it has a neighbor which can help to achieve its goal
		// 2. all neighbors achieve opposite goal
        queue<vector<int>> knowns;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] != '#') {
                    if(i != z[0] || j != z[1]) {
                        knowns.push({i, j, z[0], z[1], 0});
                        knowns.push({i, j, z[0], z[1], 1});
                        knowns.push({z[0], z[1], i, j, 0});
                        knowns.push({z[0], z[1], i, j, 1});
                        knowns.push({i, j, i, j, 0});
                        knowns.push({i, j, i, j, 1});
                        // 0. mouse turn, 1. cat turn
                        // 1. mouse win, 2. cat win
                        states[i][j][z[0]][z[1]][0][2] = 1;
                        states[i][j][z[0]][z[1]][1][2] = 1;
                        states[z[0]][z[1]][i][j][0][2] = 2;
                        states[z[0]][z[1]][i][j][1][2] = 2;
                        states[i][j][i][j][0][2] = 2;
                        states[i][j][i][j][1][2] = 2;
                    }
                }
            }
        }
        
        int finals;
        while(!knowns.empty()) {
            auto h = knowns.front();
            knowns.pop();
			// update neighbor states and if possible, add new elements into the BFS queue
            if(h[4]) {
                // cat turns, 1
                for(int i = 0; i < 4; i++) {
                    for(int len = 0; len <= cj; len++) {
                        if(!len && i) continue;
                        int xx = h[0] + dirs[i] * len;
                        int yy = h[1] + dirs[i + 1] * len;
                        if(xx < 0 || xx >= m || yy < 0 || yy >= n || grid[xx][yy] == '#') break;
                        
                        // last step, mouse turns, cat win
                        finals = states[xx][yy][h[2]][h[3]][1 - h[4]][2]; // 2 is final state
                        if(finals) continue;

                        finals = states[h[0]][h[1]][h[2]][h[3]][h[4]][2];
                        // cur step, cat win or mouse turn and all states of mouse can reach. 
                        if(finals == 2 || ++states[xx][yy][h[2]][h[3]][1 - h[4]][2 - finals] == rs[0][xx][yy]) {
                            states[xx][yy][h[2]][h[3]][1 - h[4]][2] = finals;
                            knowns.push({xx, yy, h[2], h[3], 1 - h[4]});
                        }
                    }
                }
            }else{
                // mouse turns 0
                for(int i = 0; i < 4; i++) {
                    for(int len = 1; len <= mj; len++) {
                        if(!len && i) continue;
                        int xx = h[2] + dirs[i] * len;
                        int yy = h[3] + dirs[i + 1] * len;
                        if(xx < 0 || xx >= m || yy < 0 || yy >= n || grid[xx][yy] == '#') break;
                        
                        finals = states[h[0]][h[1]][xx][yy][1 - h[4]][2];
                        if(finals) continue;
                        finals = states[h[0]][h[1]][h[2]][h[3]][h[4]][2];
                        
                        if(finals == 1 || ++states[h[0]][h[1]][xx][yy][1 - h[4]][2 - finals] == rs[1][xx][yy]) {
                            states[h[0]][h[1]][xx][yy][1 - h[4]][2] = finals;
                            knowns.push({h[0], h[1], xx, yy, 1 - h[4]});
                        }
                    }
                }
            }
        }
        
        return states[x[0]][x[1]][y[0]][y[1]][1][2] == 1;
    }


    /*
        1728.Cat-and-Mouse-II
        此题是913.Cat-and-Mouse的一道延伸，基本思路是一致的，就是BFS。建议先仔细阅读913的题解和视频。

        对于这种策略型的问题，DFS的解法是错误的。为什么呢？这是因为有“和”的可能。我们回想一下如果用通常用递归来做决策问题时，我们的思路大致是：如果我当前轮的每一种决策，都会导致对手的胜利，那么我这一轮必败；如果我当前轮的某一种决策，会导致对手的失败，那么我这一轮必胜。

        但是本题中会有“和”的可能，比如说food被墙壁包围，但是猫永远抓不到老鼠（e.g.绕着圈跑）。这种“和”的决策是递归无法判断的，就目前所知，我们无法写出正确的递归决策表达式。

        另外，注意一点，本题也不是简单的判断“老鼠和猫哪个离food近”。猫可以离food更远，但是它可能离老鼠更近，或者可以堵住老鼠的出路而必杀老鼠。

        所以本题和913需要采用同样的策略，那就是设计决策状态，然后从最终状态通过BFS逆推最初状态！

        我们设计状态(m,c,t)表示当前老鼠在m的位置、猫在c的位置、此时谁先动（1表示老鼠，2表示猫）的状态，其值有三种，0（平局，老鼠和猫都到不了food且不能相遇）、1（老鼠必赢）、2（猫必赢）。

        我们先考察哪些状态是已知的，有下面几类：

        老鼠已经在food，猫在其他地方，无论turn是谁，老鼠已赢
        猫已经在food，老鼠在其他地方，无论turn是谁，猫已赢
        老鼠和猫在同一个地方，无论turn是谁，猫已赢
        我们将这些状态放入一个队列之中。我们尝试从这些已知的(c,m,t)的状态通过BFS外推出其他的状态的结论（赢或者输），直至得到(m0,c0,1)就是我们的答案，其中m0和c0就是老鼠和猫的初始位置。

        那么如何从某个已知的(c,m,t)，来推导另一个(c2,m2,t2)呢？这个决策机制比较神奇，需要好好体会：

        我们如何推出某个新状态是必赢的结论呢？如果(c,m,t)是老鼠轮、但结论是已知猫必赢，那么任何能够走向(c,m,t)的状态(c2,m2,t2)，必然也是猫必赢，因为t2是猫轮，猫必然会选择(c,m,t)这个状态。我称之为immediate win。类似地，反过来也成立： 如果(c,m,t)是猫轮、但结论是老鼠必赢，那么任何能够走向(c,m,t)的状态(c2,m2,t2)，必然也是老鼠必赢
        我们如何推出某个新状态是必输的结论呢？如果(c2,m2,t2)是老鼠轮、而且它下一步的所有猫的决策(c,m,t)都是已知老鼠输，那么(c2,m2,t2)就是老鼠必输，因为它没有任何能导致自己不输的手段。同理，反之，如果(c2,m2,t2)是猫轮、而且它下一步的所有老鼠的决策(c,m,t)都是已知猫输，那么(c2,m2,t2)就是猫必输，
        以上两点就是拓展新状态的输赢结论的方法，事实上其他任何情况下我们都无法推断某个状态的输赢。所以当BFS结束（队列为空的时候），其实会有很多(c,m,t)的结论位置，其实这些状态就意味着猫鼠游戏会是平局。

        注意本题里超过1000步、或者猫鼠永远不相遇，也都意味着老鼠输。所以返回结果是判断(c0,m0,t)==1.
    */
    int memo[9][9][9][9][3];
    pair<int,int>mouse;
    pair<int,int>cat;
    pair<int,int>food;    
    int catJump;
    int mouseJump;

public:

    /*
        Start with all the known final state => original state (m0, c0, 1) = ? 1: Mouse win, 2: Cat win, 0: draw

        (m, c, t) => (m2, c2, t2) => (m3, c3, t3)

        1. (m, foot, t) => cat wins
        2. (food, c, t) => mouse wins
        3. (p, p, t) => cat wins

        (m, c, t) <=> (m2, c2, t2)

        1. When (m2, c2, t2) must win? 
            if (m, c, t): mouse turn, cat wins => (m2, c2, t2) cat must win
            if (m, c, t): cat turn, mouse win => (m2, c2, t2) mouse must win
        2. When (m2, c2, t2) must lose?
            if all (mm, cc, tt): cat turn, cat wins, => (m2, c2, t2) mouse must lose(mouse turn) cat win
            if all (mm, cc, tt): mouse turn, mouse wins => (m2, c2, t2) cat must lose(cat turn), mouse win
    */


    
    bool doit_(vector<string>& grid, int catJump, int mouseJump) 
    {
        int m = grid.size();
        int n = grid[0].size();
        queue<array<int,5>>q;
        this->catJump = catJump;
        this->mouseJump = mouseJump;

        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
            {
                if (grid[i][j]=='M')
                    mouse = {i,j};
                if (grid[i][j]=='C')
                    cat = {i,j};
                if (grid[i][j]=='F')
                    food = {i,j};
            }
        
        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
            {
                if (grid[i][j]=='#') continue;
                if (i==food.first && j==food.second) continue;
                
                memo[food.first][food.second][i][j][1] = 1; // mouse win
                memo[food.first][food.second][i][j][2] = 1; // mouse win
                memo[i][j][food.first][food.second][1] = 2; // cat win                
                memo[i][j][food.first][food.second][2] = 2; // cat win

                q.push({food.first, food.second, i, j, 1}); 
                q.push({food.first, food.second, i, j, 2}); 
                q.push({i, j, food.first, food.second, 1});                   
                q.push({i, j, food.first, food.second, 2});  
            }
        
        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
            {
                if (grid[i][j]=='#') continue;
                memo[i][j][i][j][1] = 2; // cat win
                memo[i][j][i][j][2] = 2; // cat win                                
                q.push({i, j, i, j, 1}); 
                q.push({i, j, i, j, 2}); 
            }
        
        int step = 0;
        while (!q.empty())
        {            
            step++;
            if (step>2000) return false;
            int len = q.size();
            while (len--)
            {
                int mx = q.front()[0];
                int my = q.front()[1];
                int cx = q.front()[2];
                int cy = q.front()[3];
                int t = q.front()[4];   
                int status = memo[mx][my][cx][cy][t];
                q.pop();
                
                for (auto nextNode: findAllAdjacents(grid,mx,my,cx,cy,t))
                {
                    int mx2 = nextNode[0];
                    int my2 = nextNode[1];
                    int cx2 = nextNode[2];
                    int cy2 = nextNode[3];                                        
                    int t2 = nextNode[4];

                    if (memo[mx2][my2][cx2][cy2][t2]!=0) continue; // has been determined

                    if (t2==status)   // immediate win, (m2,c2,t2)->(m,c,t)
                    {
                        memo[mx2][my2][cx2][cy2][t2] = status;
                        q.push({mx2,my2,cx2,cy2,t2});
                    }
                    else if (allAdjacentsWin(grid, mx2,my2,cx2,cy2,t2))    // eventually lose
                    {
                        memo[mx2][my2][cx2][cy2][t2] = (t2==1)? 2:1;
                        q.push({mx2,my2,cx2,cy2,t2});              
                    }                
                }                
            }
        }
        
        return memo[mouse.first][mouse.second][cat.first][cat.second][1]==1;        
    }
    
    vector<vector<int>> findAllAdjacents(vector<string>& grid, int mx, int my, int cx, int cy, int t)
    {
        int m = grid.size();
        int n = grid[0].size();
        auto dir = vector<pair<int,int>>({{1,0},{-1,0},{0,1},{0,-1}});
        vector<vector<int>>neighbours;
        if (t==1)
        {
            for (int k=0; k<4; k++)
                for (int a = 0; a<=catJump; a++)
                {
                    int cx2 = cx+dir[k].first*a;
                    int cy2 = cy+dir[k].second*a;
                    if (cx2<0||cx2>=m||cy2<0||cy2>=n) break;
                    if (grid[cx2][cy2]=='#') break;
                    neighbours.push_back({mx,my,cx2,cy2,2});
                }
        }
        else
        {
            for (int k=0; k<4; k++)
                for (int a = 0; a<=mouseJump; a++)
                {
                    int mx2 = mx+dir[k].first*a;
                    int my2 = my+dir[k].second*a;
                    if (mx2<0||mx2>=m||my2<0||my2>=n) break;
                    if (grid[mx2][my2]=='#') break;
                    neighbours.push_back({mx2,my2,cx,cy,1});
                }
        }
        return neighbours;
    }
    
    bool allAdjacentsWin(vector<string>& grid, int mx, int my, int cx, int cy, int t)
    {
        int m = grid.size();
        int n = grid[0].size();
        auto dir = vector<pair<int,int>>({{1,0},{-1,0},{0,1},{0,-1}});
        
        if (t==1)
        {
            for (int k=0; k<4; k++)
                for (int a = 0; a<=mouseJump; a++)
                {
                    int mx2 = mx+dir[k].first*a;
                    int my2 = my+dir[k].second*a;
                    if (mx2<0||mx2>=m||my2<0||my2>=n) break;
                    if (grid[mx2][my2]=='#') break;
                    if (memo[mx2][my2][cx][cy][2]!=2)
                        return false;
                }                
        }
        else if (t==2)
        {
            for (int k=0; k<4; k++)
                for (int a = 0; a<=catJump; a++)
                {
                    int cx2 = cx+dir[k].first*a;
                    int cy2 = cy+dir[k].second*a;
                    if (cx2<0||cx2>=m||cy2<0||cy2>=n) break;
                    if (grid[cx2][cy2]=='#') break;
                    if (memo[mx][my][cx2][cy2][1]!=1)
                        return false;
                }
        }
        return true;
    } 
};