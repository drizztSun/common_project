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
using std::vector;

#include <unordered_map>
using std::unordered_map;

#include <unordered_set>
using std::unordered_set;

#include <map>
using std::map;

#include <set>
using std::set;

#include <limits>

#include <algorithm>

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
    int doit1(vector<vector<int>>&& points) {
        
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



void test_939_minimum_area_rectangle() {
    
    auto res1 = MinAreaRectI().doit1(vector<vector<int>>{{1,1},{1,3},{3,1},{3,3},{2,2}});
    
    auto res2 = MinAreaRectI().doit2(vector<vector<int>>{{1,1},{1,3},{3,1},{3,3},{4,1},{4,3}});
    
    return;
}
