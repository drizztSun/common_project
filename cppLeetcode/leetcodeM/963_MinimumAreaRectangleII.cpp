/*
 
 963. Minimum Area Rectangle II
 
 Given a set of points in the xy-plane, determine the minimum area of any rectangle formed from these points,
 with sides not necessarily parallel to the x and y axes.

 If there isn't any rectangle, return 0.

 Example 1:
 
 Input: [[1,2],[2,1],[1,0],[0,1]]
 Output: 2.00000
 Explanation: The minimum area rectangle occurs at [1,2],[2,1],[1,0],[0,1], with an area of 2.

Example 2:
 
 Input: [[0,1],[2,1],[1,1],[1,0],[2,0]]
 Output: 1.00000
 Explanation: The minimum area rectangle occurs at [1,0],[1,1],[2,1],[2,0], with an area of 1.
 
 Example 3:
 
 Input: [[0,3],[1,2],[3,1],[1,3],[2,1]]
 Output: 0
 Explanation: There is no possible rectangle to form from these points.
 
 Example 4:
 
  Input: [[3,1],[1,1],[0,1],[2,1],[3,3],[3,2],[0,2],[2,3]]
  Output: 2.00000
  Explanation: The minimum area rectangle occurs at [2,1],[2,3],[3,3],[3,1], with an area of 2.

 */

#include <vector>
using std::vector;

#include <unordered_set>
using std::unordered_set;

#include <unordered_map>
using std::unordered_map;

#include <cfloat>
#include <limits>

namespace std {
    template <> struct hash<std::pair<int, int>> {
        inline size_t operator()(const std::pair<int, int> &v) const {
            std::hash<int> int_hasher;
            return int_hasher(v.first) ^ int_hasher(v.second);
        }
    };
}

class MinAreaFreeRect {
    
public:
    
    double doit(vector<vector<int>>&& points) {
 
        unordered_set<std::pair<int, int>> ptset;
        for (auto& c: points) {
            ptset.insert({c[0], c[1]});
        }
        
        double res = DBL_MAX;
        for (int i = 0; i < points.size(); i++) {
            for (int j = i + 1; j < points.size(); j++) {
                for (int k = j + 1; k < points.size(); k++) {
                    std::pair<int, int> pt{points[k][0] + points[j][0] - points[i][0], points[k][1] + points[j][1] - points[i][1]};
                    if (ptset.count(pt)) {
                        int x1 = points[j][0] - points[i][0], y1 = points[j][1] - points[i][1];
                        int x2 = points[k][0] - points[i][0], y2 = points[k][1] - points[i][1];
                        
                        if (std::abs(x1 * x2 + y1 * y2) < 1e-7)
                            res = std::min(res, sqrt(double(x1*x1 + y1*y1) * double(x2*x2 + y2*y2)));
                    }
                }
            }
        }
        
        return res == DBL_MAX ? 0 : res;
    }
    
    /*
     
     Approach 2: Iterate Centers
     Intuition
     Consider opposite points AC and BD of a rectangle ABCD. They both have the same center O, which is the midpoint of AC and the midpoint of AB;
     and they both have the same radius dist(O, A) == dist(O, B) == dist(O, C) == dist(O, D).
     Notice that a necessary and sufficient condition to form a rectangle with two opposite pairs of points is that the points must have the same center and radius.
     Motivated by that result, let's classify each pair of points PQ by their center C = the midpoint of PQ, and the radius r = dist(P, C).
     Our strategy is to brute force on pairs of points with the same classification.

     Algorithm
     For each pair of points, classify them by center and radius.
     We only need to record one of the points P, since the other point is P' = 2 * center - P (using vector notation).
     For each center and radius, look at every possible rectangle (two pairs of points P, P', Q, Q').
     The area of this rectangle dist(P, Q) * dist(P, Q') is a candidate answer.

     Complexity Analysis

     Time Complexity: O(N^2 \log N), where N is the length of points.
     It can be shown that the number of pairs of points with the same classification is bounded by \log NlogN - see this link for more.

     Space Complexity: O(N).
     
     */
    
    
};


class Solution {

    bool isNormal(const vector<int> &pt1, const vector<int> &pt2, const vector<int> &pt3) {
        return (pt2[0]-pt1[0]) * (pt3[0]-pt1[0]) + (pt2[1]-pt1[1]) * (pt3[1]-pt1[1]) == 0;
    }
    uint64_t toKey(int x, int y) {
        return (((unsigned long)x) << 32) + (unsigned long)y;
    }
    uint64_t forthPoint(const vector<int> &pt1, const vector<int> &pt2, const vector<int> &pt3) {
        int x = pt2[0] + pt3[0] - pt1[0];
        int y = pt2[1] + pt3[1] - pt1[1];
        return toKey(x, y);
    }
    double area(const vector<int> &pt1, const vector<int> &pt2, const vector<int> &pt3) {
        long x1 = pt2[0] - pt1[0];
        long y1 = pt2[1] - pt1[1];
        long x2 = pt3[0] - pt1[0];
        long y2 = pt3[1] - pt1[1];
        return sqrt((double)((x1*x1 + y1*y1) * (x2*x2 + y2*y2)));
    }
    
public:
    
    double minAreaFreeRect(vector<vector<int>>& points) {
        int n = points.size();
        
        unordered_set<uint64_t> forthPoints;
        for (auto &pt : points)
            forthPoints.insert(toKey(pt[0], pt[1]));
        
        double minArea = DBL_MAX;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++) {
                    vector<int> &p1 = points[i], &p2 = points[j], &p3 = points[k];
                    if (isNormal(p1, p2, p3) && forthPoints.count(forthPoint(p1, p2, p3))) {
                        minArea = std::min(minArea, area(p1, p2, p3));
                    }
                }
        
        return minArea != DBL_MAX ? minArea : 0.0;
    }
};


void test_963_minimum_area_rectangle_ii() {
    
    auto res1 = MinAreaFreeRect().doit(vector<vector<int>>{{1,2},{2,1},{1,0},{0,1}});
    
    auto res2 = MinAreaFreeRect().doit(vector<vector<int>>{{0,1},{2,1},{1,1},{1,0},{2,0}});
    
    auto res3 = MinAreaFreeRect().doit(vector<vector<int>>{{0,3},{1,2},{3,1},{1,3},{2,1}});
    
    auto res4 = MinAreaFreeRect().doit(vector<vector<int>>{{3,1},{1,1},{0,1},{2,1},{3,3},{3,2},{0,2},{2,3}});
    
    return;
}
