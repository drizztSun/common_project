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

#include <set>
using std::set;

#include <unordered_map>
using std::unordered_map;

namespace std{

    template <> struct hash<pair<int, int>> {
        inline auto operator()(const std::pair<int, int> &v) const {
            std::hash<int> int_hasher;
            return int_hasher(v.first) ^ int_hasher(v.second);
        }
    };
}

class IsEscapePossible {
    
    
    
public:
    bool doit1(vector<vector<int>>&& blocked, vector<int>&& source, vector<int>&& target) {
        
        auto bfs = [](vector<int> point, unordered_set<std::pair<int, int>>& blockedlist) {
            
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
        };
        
        unordered_set<std::pair<int, int>> blockedlist;
        for (auto c : blocked)
            blockedlist.insert({c[0], c[1]});
        
        return bfs(source, blockedlist) ^ bfs(target, blockedlist);
    }
    
    
    bool doit(vector<vector<int>>&& blocked, vector<int>&& source, vector<int>&& target) {
        
        
        auto bfs = [](unordered_set<std::pair<int, int>>& blockedset, std::pair<int, int> src, std::pair<int, int> target){
            unordered_set<std::pair<int, int>> seen_blocked;
            deque<std::pair<int, int>> buf;
            unordered_set<std::pair<int, int>> visited;
            buf.push_back(src);
            visited.insert(src);
            
            while (!buf.empty()) {
                
                int N = buf.size();
                for (int i = 0; i < N; i++) {
                    auto c = buf.front();
                    if (c == target)
                        return true;
                    
                    for (auto n : vector<vector<int>>{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}) {
                        int x = c.first + n[0], y = c.second + n[1];
                        if (blockedset.count({x, y}) == 1) {
                            seen_blocked.insert({x, y});
                            continue;
                        }
                        
                        if (x >= 0 && y >= 0 && visited.count({x, y}) == 0) {
                            visited.insert({x, y});
                            buf.push_back({x, y});
                        }
                    }
                    buf.pop_front();
                }
                
                if (buf.size() > blockedset.size() - seen_blocked.size()) {
                    return true;
                }
            }
            
            return false;
        };
        
        unordered_set<std::pair<int, int>> blockedset;
        for (auto& c: blocked)
            blockedset.insert({c[0], c[1]});
        
        std::pair<int, int> src{source[0], source[1]};
        std::pair<int, int> tgrt{target[0], target[1]};

        
        if (blockedset.count(src) != 0 || blockedset.count(tgrt) != 0)
            return false;
        
        return bfs(blockedset, src, tgrt) && bfs(blockedset, tgrt, src);
    }
    
    
    
    
    
};



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


class Solution {
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
};


class IsEscapePossible1 {
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


void test_1036_escape_large_maze() {
    
    auto res1 = IsEscapePossible().doit(vector<vector<int>>{{0,1}, {1,0}}, vector<int>{0, 0}, vector<int>{0, 2});
    
    auto res2 = IsEscapePossible().doit(vector<vector<int>>{}, vector<int>{0, 0}, vector<int>{99999, 99999});
    
    auto res3 = IsEscapePossible1().doit(vector<vector<int>>{{0,3}, {1,0}, {1,1}, {1,2}, {1,3}}, vector<int>{0,0}, vector<int>{0,2});
    
    return;
}
