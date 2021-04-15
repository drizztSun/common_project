/*
 
1036. Escape a Large Maze

There is a 1 million by 1 million grid on an XY-plane, and the coordinates of each grid square are (x, y).

We start at the source = [sx, sy] square and want to reach the target = [tx, ty] square. 

There is also an array of blocked squares, where each blocked[i] = [xi, yi] represents a blocked square with coordinates (xi, yi).

Each move, we can walk one square north, east, south, or west if the square is not in the array of blocked squares. We are also not allowed to walk outside of the grid.

Return true if and only if it is possible to reach the target square from the source square through a sequence of valid moves.

 

Example 1:

Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
Output: false
Explanation: The target square is inaccessible starting from the source square because we cannot move.
We cannot move north or east because those squares are blocked.
We cannot move south or west because we cannot go outside of the grid.
Example 2:

Input: blocked = [], source = [0,0], target = [999999,999999]
Output: true
Explanation: Because there are no blocked cells, it is possible to reach the target square.
 

Constraints:

0 <= blocked.length <= 200
blocked[i].length == 2
0 <= xi, yi < 106
source.length == target.length == 2
0 <= sx, sy, tx, ty < 106
source != target
It is guaranteed that source and target are not blocked.

*/

#include <vector>
#include <deque>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <string>
#include <queue>

using std::queue;
using std::string;
using std::vector;
using std::deque;
using std::unordered_set;
using std::set;
using std::unordered_map;


class IsEscapePossible {
    
    /*
        1036.Escape-a-Large-Maze
        首先，对于1M by 1M的网格内，想要进行任意两点间的寻路几乎是不可能的。本题的关键在于blocked的位置最多只有200个。

        正常情况下，200个元素可以围成最大的区域面积是多少呢？肯定是一个中心对称的图形。我们如果从起点走一步，可以发现能走到的范围是一个边长是2、倾斜了45度的正方形。走两步的话，能覆盖的范围是一个边长是3、倾斜了45度的正方形。依次类推，考虑总周长为200的正方形，说明其边长是50，也就是从起点最多走49步。这种正方形最紧凑，是固定周长的条件下能够覆盖的最大的面积（2500）。

        于是我们换个角度想：如果从起点出发向外扩散，并且最终可以扩展到超过2500个元素的区域（且没有遇到终点），这说明什么？因为根本没有周长是200的图形可以封闭住这么的面积，所以blocked对于这个起点而言是无效的。也就是说，blocked并不能完全围住起点。

        同理，如果我们又发现blocked也不能围住终点的话，那么说明起点和终点势必会相遇。

        所以这是一个BFS题，只要从一个点出发开始发散，当visited的网格数目（也就是覆盖的面积）大于2500的时候，就说明这个点并没有被封闭。

        有了这个基本思路后，我们需要注意，其实200的周长最大能封闭的面积可以是19900，而不是2500.原因是这200个点可以以45度倾斜地围住一个角。因此0+1+2+...+199 = 19900才是最大的封闭面积。只有发散的区域超过了这个面积，才能保证不被封闭。
    */
    
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) 
    {
        if (blocked.size()<=1) return true;
        unordered_set<string>blocks;
        for (auto b:blocked)
            blocks.insert(std::to_string(b[0])+"#"+std::to_string(b[1]));
        
        if (enclose(source,target,blocks) || enclose(target,source,blocks))
            return false;
        else
            return true;
    }
    
    bool enclose(vector<int>& source, vector<int>& target, unordered_set<string>& blocks)
    {
        auto dir = vector<std::pair<int,int>>({{1,0},{-1,0},{0,1},{0,-1}});
        queue<std::pair<int,int>>q;
        unordered_set<string>visited;
        
        q.push({source[0],source[1]});
        visited.insert(std::to_string(source[0])+"#"+std::to_string(source[1]));
        
        while (!q.empty() && visited.size()<=19900)
        {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            
            for (int k=0; k<4; k++)
            {
                int i = x+dir[k].first;
                int j = y+dir[k].second;
                
                if (i<0||i>=1e6||j<0||j>=1e6)
                    continue;
                if (i==target[0] && j==target[1])
                    return false;
                
                string encode = std::to_string(i)+"#"+std::to_string(j);
                if (blocks.find(encode)!=blocks.end())
                    continue;
                if (visited.find(encode)!=visited.end())
                    continue;
                
                visited.insert(encode);
                q.push({i,j});
            }
        }
        
        if (q.empty()) 
            return true;
        else
            return false;
    }

public:

    /*
        Notice that the dimension of the grid is 10^6 which is very large so that we will get TLE if we do BFS directly. 
        Also notice that the number of blocked cell is at most 200, which means that most of the cells in the grid is empty and basically useless.

        To solve the aforementioned issue, we need to compress the large grid into a smaller one by observing which cells are meaningful.

        We use a set to storage every x cooredinate of blocked[i], source, and target. Then, we re-index the numbers in the set. 
        We leave an empty index for the spaces between any two adjacent numbers in the set except for the case that the two adjacent numbers are different by one.

        Notice that we also need to be careful about the edge cases to prevent the correspondence from going wrong.

        For example:

        set     =   { 5,    60,     102,      103,      992,    999999}
        new index = { 1,     3,       5,        6,        8,        10}
        --> new grid has n = 11
        (index 0 represents the whole range of 0 ~ 4,
        index 2 represents the whole range of 61 ~ 101, and so on)
        %---------------------------------------------------------------
        set     =   { 0,    60,     102,      103,       1000}
        new index = { 0,     2,       4,        5,          7}
        (index 8 represents the whole range of 1001 ~ 999999)
        --> new grid has n = 9
        After that, we can just do a simple BFS since the dimension now is smaller than 500.
    */
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        
        set<int> sx, sy;
        for (vector<int>& b : blocked) 
            sx.insert(b[0]), sy.insert(b[1]);
        
        sx.insert(source[0]), sy.insert(source[1]);
        sx.insert(target[0]), sy.insert(target[1]);
        
        int n = -1, m = -1, last = -1;
        unordered_map<int, int> xm, ym;
        for (auto it = sx.begin(); it != sx.end(); it++)
        {
            if (*it == last + 1) n++;
            else n += 2;
            xm[*it] = n;
            last = *it;
        }
        
        if (last != 999999) n++;
        
        n++;
        last = -1;
        for (auto it = sy.begin(); it != sy.end(); it++)
        {
            if (*it == last + 1) m++;
            else m += 2;
            ym[*it] = m;
            last = *it;
        }
        
        if (last != 999999) m++;
        m++;
        
        vector<vector<bool>> v(n, vector<bool>(m, true));
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        
        for (vector<int>& b : blocked) v[xm[b[0]]][ym[b[1]]] = false;
        
        int x = xm[source[0]], y = ym[source[1]];
        int tx = xm[target[0]], ty = ym[target[1]];
        
        queue<int> que;
        que.push(x << 16 | y);
        vis[x][y] = true;
        vector<vector<int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};

        while (!que.empty())
        {
            int p = que.front(), q = p & 0xFFFF;
            p >>= 16;
            que.pop();
            for (vector<int>& d : dirs)
            {
                int tmpp = p + d[0], tmpq = q + d[1];
                if (tmpp < 0 || tmpp >= n || tmpq < 0 || tmpq >= m || !v[tmpp][tmpq] || vis[tmpp][tmpq]) continue;
                if (tmpp == tx && tmpq == ty) return true;
                vis[tmpp][tmpq] = true;
                que.push(tmpp << 16 | tmpq);
            }
        }
        return false;
    }

    // _best
    unordered_set<long long> blckd;
    bool reachedTarget;
    
    bool isEscapePossible(vector<int>& source, vector<int>& target) {
        int m = 1000000;
        int n = 1000000;
        int d = blckd.size(); // distance to be reached in cardinal direction
        
        // direction right,down,left,up
        int dirX[] = {0,1,0,-1};
        int dirY[] = {1,0,-1,0};
                
        // BFS
        unordered_set<long long> seen;
        queue<std::pair<int,int>> q;
        q.push({source[0],source[1]});
        seen.insert((long long)source[0]*1000000 +source[1]);
        int x,y,x_new,y_new;
        unordered_set<long long>::iterator be = blckd.end();
        
        while(!q.empty()) {
            x = q.front().first;
            y = q.front().second;
            q.pop();
            
            // explore in all 4 directions
            for(int i = 0; i < 4; ++i) {
                
                x_new = x + dirX[i];
                if( x_new < 0 || x_new == m )
                    continue;
                
                y_new = y + dirY[i];
                if( y_new < 0 || y_new == n )
                    continue;                
                
                // blocked?
                if( blckd.find((long long)x_new*1000000 + y_new) != be )
                    continue;
                
                // seen?
                if( seen.find((long long)x_new*1000000 + y_new) != seen.end() )
                    continue;
                
                // target?
                if( x_new == target[0] && y_new == target[1] ) {
                    // cout << "reached target" << endl;
                    reachedTarget = true;
                    return true;
                }
                
                // far enough away?
                if( source[0]+(d-1) == x_new || source[0]-(d-1) == x_new ||
                    source[1]+(d-1) == y_new || source[1]-(d-1) == y_new ) {
                    // cout << x_new << " " << y_new << endl;
                    return true;
                }
                
                seen.insert((long long)x_new*1000000 + y_new);
                q.push({x_new,y_new});
                
            }
            // if our queue has more entries or equal number than there are blocked cells, 
            // then it cannot be stopped
            if( q.size() >= d ) return true;
        }
        return false;
    }

    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        // idea: for both source and target, if we can reach a point in the matrix, that is
        //       sx + blocked.size()-1 = px OR sx - blocked.size()-1 = px OR
        //       sy + blocked.size()-1 = py OR sy - blocked.size()-1 = py OR
        //       tx + blocked.size()-1 = px OR tx - blocked.size()-1 = px OR
        //       ty + blocked.size()-1 = py OR ty - blocked.size()-1 = py
        // then the answer is true
        
        for(int i = 0; i < blocked.size(); ++i)
            blckd.insert((long long)blocked[i][0]*1000000 + blocked[i][1]);
        
        reachedTarget = false;
        
        bool s2t = isEscapePossible(source, target);
        if( !s2t ) return false;
        if( reachedTarget ) return true;
        
        return isEscapePossible(target, source);
    }
    

// 结合一个具体的情况说明代码。
//
//  //////////////////
//  ///|      BB
//  ///| [S]--BB----
//  ///|    BBB     | --- 从 S 到 T 的一条路径
//  ///|BBBBB       |
//  ///|           [T]
//
//  [S] - 源点 [T] - 目标点 B - 障碍物
//
//  上面说 "沿着从 S 到 T 的一条路径" 走，不是说就直接“选一条路径，然后沿着走”，肯定超时。
//  而是想象一条虚拟的路径（如上图，先从 S 走到 T 的上方，然后再走到 T。）
//  然后，把所有障碍物点按照坐标顺序排序。（先 x 从小到大，相等时 y 从小到大）
//  再从头遍历所有的障碍物点（B）。从图上走一遍，看哪个 B 先与“虚拟路线”相遇。
//  看出来了吗，这样第一个和“虚拟路线”相遇的点一定是从 S 到 T 所遇到的第一个障碍物。
//
//  然后，从这个相遇的 B 出发, 向两侧进发。看总共穿越了多少次“虚拟路线”。
//  如下图所示，搜索的就是这条线(下图标 X 的位置)
//
//  //////////////////
//  ///|      XB
//  ///| [S]--XB----
//  ///|    XXB     |
//  ///|XXXXB       |
//  ///|           [T]
//
//  那么，如果判断搜索路线穿越了“虚拟路线”? 首先，将整个地图按照 “虚拟路线” 分成两个区域：
//
//  //////////////////
//  ///|          AREA-B
//  ///| [S]--------
//  ///|  . . . . . |
//  ///|  . AREA-A. |
//  ///|  . . . . .[T]
//
//  AREA-A 为虚拟路线“左下方”的部分，AREA-B 为其余部分(不包括虚拟路线）。
//  [判断区域归属由宏 AREA 负责]。
//  一条穿越了“虚拟路线”的搜索路线如下图所示：
//
//        X
//        X   AREA-B
//   [S]--X------------[T]
//       X   AREA-A
//
//  可见，搜索路线必有 1 个点在 A 区，另 1 个点在 B 区，还有 1 个点在“虚拟路线”上。
//  就这个例子来说，我们从在 “虚拟路径”上的 "X" 开始搜索。首先向上，然后向下，
//  发现两个点在不同区域，并且搜索开始的点就在“虚拟路径”上，满足上述条件。
//  这样，穿越次数 + 1。
//  [判断点是否在 “虚拟路线” 上由宏 INPATH 负责]。
//
//  下面完整地叙述程序的运行情况：
//
//  A. 就是上面的例子。
//     程序从 @ 处开始搜索，X为搜索路线。向上到边，向下到边，总共 1 次穿越。封锁成功。
//  //////////////////
//  ///|      XB
//  ///| [S]--@B----
//  ///|    XXB     |
//  ///|XXXXB       |
//  ///|           [T]
//
//  B. 程序从 @ 处开始搜索，X为搜索路线。从图上走一遍，向上搜索，向下搜索都到达同一个
//     边界。总共 2 次穿越。封锁失败。
//     另外, 由于搜索过后，包在 “X” 中的 “B” 再也没有用了（不能封锁），后续的搜索，
//     选择横坐标在 “extidxx” 之后的点开始即可。“extidxy” 作用类似。
//  //////////////////
//  ///|           extidxx
//  ///|             |
//  ///|         XXX |
//  ///| [S]----@BBBXX-----
//  ///|       XBBBBBX     |
//  ///|     XXXXXXXX      |
//  ///| XXXX             [T]
//
//
//链接：https://leetcode-cn.com/problems/escape-a-large-maze/solution/cong-zhang-ai-wu-dian-blockedru-shou-de-kuai-su-su/

public:
    class Point
    {
        public:
        int x;
        int y;
        bool operator< (const Point& right) const
        {
            if(this->x < right.x)
                return true;
            else if(this->x == right.x)
                return this->y < right.y;
            else
                return false;
        }
        Point(const int x,const int y)
        {
            this->x = x;
            this->y = y;
        }
    };

    int x1,y1,x2,y2,minx,maxx,miny,maxy,l,r;
    int extidxx, extidxy;
    set<Point> pts;

    // (x1,y1)            (x2,y2)
    // S--------  |          T
    //         |  |          |
    //         |  |          |
    //         T  | S---------
    //     (x2,y2)  (x1,y1)
    #define INPATH(x,y) (((x) == (x2) && (y) <= maxy && (y) >= miny) || ((y) == (y1) && (x) >= minx && (x) <= maxx))
    #define AREA(x,y) (((x) > maxx) || ((y2 > y1)? ((y) < miny) : ((y) > maxy)))
    #define INBOARD(x,y) ((x) >= l && (x) <= r && (y) >= l && (y) <= r)

    void updateExt(const Point& pt)
    {
        extidxx = std::max(pt.x, extidxx);
        if(y2 < y1) extidxy = std::min(pt.y, extidxy);
        else extidxy = std::max(pt.y, extidxy);
    }

    bool notSearched(const Point& pt)
    {
        if(pt.x > extidxx)
            return true;
        if(y2 < y1 && pt.y < extidxy)
            return true;
        if(y2 > y1 && pt.y > extidxy)
            return true;
        return false;
    }

    enum SEARCHRES
    {
        LOCKED = 0,
        UNLOCKED = 1,
        REACHEDGE = 2
    };

    SEARCHRES search(
        Point cpt, // 搜索起始点
        int rotate, // 旋转方向
        int lastarea, // 第一次搜索时应为 0, 第二次为 outarea
        int & crosses, // 穿越数, 初始化值为 0
        int & outarea // 首次穿出的区域, 初始化值为 0
    )
    {
        const int xoffs[] = {0,1,1, 1, 0,-1,-1,-1};
        const int yoffs[] = {1,1,0,-1,-1,-1, 0, 1};
        const int oppomove[] = {4,5,6,7,0,1,2,3};

        Point firstpt = cpt;

        // 搜索起始方向, 当 y == y1 时应为 6(←), 否则若 y2 < y1 应为 0(↓); 若 y2 > y1 应为 4(↑).
        int currmove = (cpt.y == y1) ? 6 : ((y2 < y1)? 0 : 4);

        // 上次搜索的点是否在线内
        bool lastIn = true;

        for(;;)
        {
            // 找到搜索起始方向 = 前一个方向的对向
            bool foundNew = false;

            // 八联通方向搜索(四联通移动,八联通即可封锁)
            for(int i = 0; i < 8; ++i)
            {
                currmove += rotate;
                if(currmove >= 8)
                    currmove -= 8;
                else if(currmove <= 0)
                    currmove += 8;

                Point npt(cpt.x + xoffs[currmove], cpt.y + yoffs[currmove]);

                if(npt.x == firstpt.x && npt.y == firstpt.y)
                {
                    // 返回了初始点，绕了回来
                    // 如果出的方向与进的方向不同, 则算作一次穿越
                    if(abs(lastarea - outarea) == 2)
                        crosses += 1;
                    if((crosses & 1) == 0) // 偶数次, 没包起来
                        return UNLOCKED;
                    else // 奇数次, 把原点 or 目标点 包了起来
                        return LOCKED;
                }
                else if(!INBOARD(npt.x,npt.y))
                {
                    int currArea = AREA(npt.x,npt.y) ? 1 : -1;
                    if(abs(lastarea - currArea) == 2 && lastIn)
                        crosses += 1; // 两次在不同半区且经过原始路线算作穿越
                    lastarea = currArea;
                    if(outarea == 0)
                        outarea = currArea;
                    lastIn = false;
                    return REACHEDGE;
                }
                else
                {
                    set<Point>::iterator it = pts.find(npt);
                    if(it != pts.end())
                    {
                        foundNew = true;

                        if((!INPATH(it->x,it->y)))
                        {
                            int currArea = AREA(it->x,it->y) ? 1 : -1;
                            if(abs(currArea - lastarea) == 2 && lastIn)
                                crosses += 1; // 两次在不同半区且经过原始路线算作穿越
                            lastarea = currArea;
                            if(outarea == 0)
                                outarea = currArea;
                            lastIn = false;
                        }
                        else
                        {
                            lastIn = true;
                            updateExt(npt);
                        }
                        
                        cpt = *it;
                        currmove = oppomove[currmove] + rotate;
                        break;
                    }
                }
            }

            if(!foundNew)
                return UNLOCKED; // 孤点, 不能起到封锁作用
        }
    }

    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        l = 0, r = 1e6 - 1;
        x1 = source[0], y1 = source[1], x2 = target[0], y2 = target[1];
        minx = std::min(x1,x2), maxx = std::max(x1,x2), miny = std::min(y1,y2), maxy = std::max(y1,y2);

        if(x2 < x1)
        {
            // 交换 source 和 target
            int tmp = x1; x1 = x2; x2 = tmp;
            tmp = y1; y1 = y2; y2 = tmp;
        }

        extidxx = x1, extidxy = y1;

        this->pts.clear();
        for(vector<int> b :blocked)
        {
            if(pts.find(Point(b[0],b[1])) == pts.end())
                pts.insert(Point(b[0],b[1]));
        }

        set<Point>::iterator it = pts.begin();
        set<Point>::reverse_iterator rit = pts.rbegin();

        for(;;)
        {
            // 在初始路径上找到起始点
            Point cpt(0,0);

            // 当 y2 < y1 且 x 走到 x2 时, y 应当沿着 y减小 的方向走
            if(extidxx == x2 && y2 < y1)
            {
                for(;; ++rit)
                {
                    if(rit == pts.rend())
                        return true;
                    if(INPATH(rit->x, rit->y) && notSearched(*rit))
                    {
                        updateExt(*rit);
                        cpt = *rit;
                        break;
                    }
                }
            }
            else // 否则应沿着 x 增大 或 y 增大 的方向走
            {
                for(;; ++it)
                {
                    if(it == pts.end())
                        return true;
                    if(INPATH(it->x, it->y) && notSearched(*it))
                    {
                        updateExt(*it);
                        cpt = *it;
                        break;
                    }
                }
            }

            int crosses = 0, outarea = 0, t = 0;

            // 正向搜索
            SEARCHRES res = search(cpt,1,0,crosses,outarea);

            if(res == UNLOCKED)
                continue;
            else if(res == LOCKED)
                return false;
            
            //REACHEDGE,则再进行反向搜索
            res = search(cpt,-1,outarea,crosses,t);

            if(res == UNLOCKED)
                continue;
            else if(res == LOCKED)
                return false;
            
            if(crosses & 1)
                return false;
        }

        return true;
    }

public:
    
    struct hash{
        long operator()(const std::pair<int, int> &x) const{
            long hash = (long)(x.first) * 1000007 +  (long)(x.second);
            return hash;
        }
    };
    
    bool go(int x, int y, int source_x, int source_y, int target_x, int target_y, int limit, int color, unordered_map<std::pair<int, int>, int, hash> & map) {
        
        if(x < 0 || x >= 1000000 || y < 0 || y >= 1000000) {
            return false;
        }
        if(map.find(std::pair<int,int>(x,y)) != map.end() && (map[std::pair<int,int>(x,y)] == -1 || map[std::pair<int,int>(x,y)] == color)) {
            return false;
        }
        
        map[std::pair<int,int>(x,y)] = 1;
        
        if(x == target_x && y == target_y) {
            return true;
        }
        
        if(abs(x-source_x) + abs(y-source_y) >= limit) {
            return true;
        }
        if(go(x-1, y, source_x, source_y, target_x, target_y, limit, color, map)) {
            return true;
        }
        if(go(x+1, y, source_x, source_y, target_x, target_y, limit, color, map)) {
            return true;
        }
        if(go(x, y-1, source_x, source_y, target_x, target_y, limit, color, map)) {
            return true;
        }
        if(go(x, y+1, source_x, source_y, target_x, target_y, limit, color, map)) {
            return true;
        }
        return false;
    }
    
    bool doit(vector<vector<int>>&& blocked, vector<int>&& source, vector<int>&& target) {
        unordered_map<std::pair<int, int>, int, hash> map;
        for(int i = 0; i < blocked.size(); ++i) {
            map[std::pair<int,int>(blocked[i][0], blocked[i][1])] = -1;
        }
        
        std::pair<int,int> source_pair(source[0], source[1]);
        std::pair<int,int> target_pair(target[0], target[1]);
        
        if(go(source[0], source[1], source[0], source[1], target[0], target[1], blocked.size(), 1, map) == false) {
            return false;
        }
        
        if(go(target[0], target[1], target[0], target[1], source[0], source[1], blocked.size(), 2, map) == false) {
            return false;
        }
        
        return true;
    }
};