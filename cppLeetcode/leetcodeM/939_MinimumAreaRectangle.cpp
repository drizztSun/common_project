/*
 
 939. Minimum Area Rectangle
 
 Given a set of points in the xy-plane, determine the minimum area of a rectangle formed from these points, with sides parallel to the x and y axes.

 If there isn't any rectangle, return 0.

  

 Example 1:

 Input: [[1,1],[1,3],[3,1],[3,3],[2,2]]
 Output: 4
 Example 2:

 Input: [[1,1],[1,3],[3,1],[3,3],[4,1],[4,3]]
 Output: 2
 
 
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <limits>
#include <algorithm>


using std::vector;
using std::unordered_map;
using std::unordered_set;
using std::map;
using std::set;

namespace std{
    template <> struct hash<std::pair<int, int>> {
        inline size_t operator()(const std::pair<int, int>& v) const {
            std::hash<int> int_hasher;
            return int_hasher(v.first) ^ int_hasher(v.second);
        }
    };
}

struct Hash {
    size_t operator()(const std::pair<int,int>&x)const{
        return std::hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
    }
};

class MinAreaRectI {

    /*
        939.Minimum-Area-Rectangle
        对于“横平竖直”的矩阵而言，只需要给定对角线的两个点，就能完全确定一个矩形。所以最外层的两个大循环来遍历点A和点B，这是显而易见的。固定A和B之后，另外一条对角线的两个点C和D，其坐标也就能确定下来。那么如何在一个集合中快速查找到C和D呢？

        因为每个点的坐标包括两个分量，所以你想做查找的话，无非两个思路：1.把所有二维坐标哈希化成字符串，放入一个无序集合中，但额外的哈希化很耗时。2.直接把二维向量放入一个有序集合中，但这涉及红黑树的插入，也是效率很低的。

        这里提供一个用空间换时间的方法。那就是设计一个这样的数据结构unordered_map<int, unordered_set<int>>Map。其中key是横坐标的值，value是纵坐标的值的集合。
        初始化时将所有的点按照横坐标的位置来这样归类。这样，后期我们考察(x,y)是否存在的时候，只需要考察Map[x]里面是否存在y就可以了。这样既避免了哈希化，也只用到了无序容器从而省去了排序的时间。    
    */
    int minAreaRect_best(vector<vector<int>>& points) 
    {
        unordered_map<int, unordered_set<int>>Map;
        for (auto p: points)
            Map[p[0]].insert(p[1]);
        
        int ret = INT_MAX;
        for (int i=0; i<points.size(); i++)
            for (int j=i+1; j<points.size(); j++)
            {
                int x1 = points[i][0];
                int y1 = points[i][1];
                int x2 = points[j][0];
                int y2 = points[j][1];
                
                if (x1==x2 || y1==y2) continue;
                
                int x3 = x2;
                int y3 = y1;
                int x4 = x1;
                int y4 = y2;
                
                if (Map[x3].find(y3)==Map[x3].end())
                    continue;
                if (Map[x4].find(y4)==Map[x4].end())
                    continue;
                
                ret = std::min(ret, abs(x2-x1)*abs(y1-y2));
            }
        
        return ret==INT_MAX? 0:ret;
    }
    
    int minAreaRect(vector<vector<int>>& points) {
        set<std::pair<int, int>> pts;
        for (auto& c : points)
            pts.insert({c[0], c[1]});
        
        int ans = INT_MAX;
        for (int i = 0; i < points.size(); i++)
            for (int j = 0; j < i; j++) {
                
                if (points[i][0] != points[j][0] && points[i][1] != points[j][1] && pts.count({points[i][0], points[j][1]}) > 0 && pts.count({points[j][0], points[i][1]})) {
                    ans = std::min(ans, abs(points[i][0] - points[j][0]) * abs(points[i][1] - points[j][1]));
                }
            }
        
        return ans == INT_MAX ? 0 : ans;
    }
    
    int doit_hashtable(vector<vector<int>>& points) {
        
        unordered_map<int, unordered_set<int>> xlines;
        
        for (auto& c: points) {
            xlines[c[0]].insert(c[1]);
        }
        
        int res = INT_MAX;
        for (int i = 0; i < points.size(); i++) {
            for (int j = i+1; j < points.size(); j++) {
                
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];

                if (x1 == x2 || y1 == y2) continue;
                
                
                if (xlines[x1].count(y2) == 0 || xlines[x2].count(y1) == 0) continue;
                
                res = std::min(res, abs(x2-x1) * abs(y1-y2));
                
            }
        }
        
        
        return res == INT_MAX ? 0 : res;
    }

public:
    
    /*
     """
     Approach 1: Sort by Column
     Intuition

     Count each rectangle by right-most edge.

     Algorithm

     Group the points by x coordinates, so that we have columns of points. Then, for every pair of points in a column (with coordinates (x,y1) and (x,y2)),
     check for the smallest rectangle with this pair of points as the rightmost edge. We can do this by keeping memory of what pairs of points we've seen before.

     Complexity Analysis

     Time Complexity: O(N^2) where NN is the length of points.

     Space Complexity: O(N).
     """
    */
    int doit_hashtable(vector<vector<int>>&& points) {
        
        // unordered_map<int, vector<int>> ylines;
        map<int, vector<int>> ylines;
        set<int> xs;
        for (auto&c : points) {
            ylines[c[0]].push_back(c[1]);
            xs.insert(c[0]);
        }
        
        int ans = INT_MAX;
        // unordered_map<std::pair<int, int>, int> seen;
        map<std::pair<int, int>, int> seen;
        for (auto x : xs) {
            
            std::sort(ylines[x].begin(), ylines[x].end());
            
            for (int i = 0; i < ylines[x].size(); i++) {
                for (int j = i+1; j < ylines[x].size(); j++) {
                    int y1 = ylines[x][i], y2 = ylines[x][j];
                    if (seen.count({y1, y2}) > 0) {
                        ans = std::min(ans, (y2 - y1) * (x - seen[{y1, y2}]));
                    }
                    seen[{y1, y2}] = x;
                }
            }
        }
        
        return ans == INT_MAX ? 0 : ans;
    }
    
    /*
     Approach 2: Count by Diagonal
     Intuition

     For each pair of points in the array, consider them to be the long diagonal of a potential rectangle.
     We can check if all 4 points are there using a Set.

     For example, if the points are (1, 1) and (5, 5), we check if we also have (1, 5) and (5, 1).
     If we do, we have a candidate rectangle.

     Algorithm

     Put all the points in a set. For each pair of points, if the associated rectangle are 4 distinct points all in the set,
     then take the area of this rectangle as a candidate answer.
     */
    
    int doit(vector<vector<int>>&& points) {

        auto hash_cord = [](const std::pair<int, int>& c) {
            return hash<int>()(c.first) ^ hash<int>()(c.second);
        };
        
        auto equal_cord = [](const std::pair<int, int>& a, const std::pair<int, int>& b){
            return a.first == b.first && a.second == b.second;
        };
        
        unordered_set<std::pair<int, int>, decltype(hash_cord), decltype(equal_cord)> pts;
        // set<std::pair<int, int>> pts;
        for (auto& c : points)
            pts.insert({c[0], c[1]});
        
        int ans = INT_MAX;
        for (int i = 0; i < points.size(); i++)
            for (int j = 0; j < i; j++) {
                
                if (points[i][0] != points[j][0] && points[i][1] != points[j][1] && pts.count({points[i][0], points[j][1]}) > 0 && pts.count({points[j][0], points[i][1]})) {
                    ans = std::min(ans, abs(points[i][0] - points[j][0]) * abs(points[i][1] - points[j][1]));
                }
            }
        
        return ans == INT_MAX ? 0 : ans;
    }
    
    // Solution 2
    std::pair<int,int> count(vector<vector<int>>& points) {
      unordered_set<int> xs, ys;
      for (auto& p : points) {
        xs.insert(p[0]);
        ys.insert(p[1]);
      }
      return {xs.size(), ys.size()};
    }
    
    int doit2(vector<vector<int>>&& points) {
        // optimization - count distinct x and y
         const auto&[nx, ny] = count(points);
         if (nx == 0 || ny == 0)
             return 0; // gives -20ms
         
         // this optimization gives total runtime improvement x10
         map<int, vector<int>> x2y;
         if (nx > ny)
           for (auto& p : points)
             x2y[p[0]].emplace_back(p[1]);
         else
           for (auto& p : points)
             x2y[p[1]].emplace_back(p[0]);
         
         unordered_map<std::pair<int,int>, int, Hash> seenPairsOfY2X;
         int res = std::numeric_limits<int>::max();
         for (auto&[x, ys] : x2y) {
             std::sort(ys.begin(), ys.end());
             for (int i = 0; i < ys.size(); ++i)
                 for (int j = 0; j < i; ++j) {
                     int y1 = ys[j], y2 = ys[i]; // y2 > y1
                     if (seenPairsOfY2X.count({y1,y2})) {
                         int x1 = seenPairsOfY2X[{y1,y2}];
                         int x2 = x;
                         int area = (y2 - y1) * (x2 - x1);
                         res = std::min(res, area);
                     }
                     seenPairsOfY2X[{y1,y2}] = x;
                 }
         }
         return res == std::numeric_limits<int>::max() ? 0 : res;
    }
};