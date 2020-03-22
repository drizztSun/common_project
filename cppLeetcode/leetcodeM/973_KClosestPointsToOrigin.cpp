/*
 
 
 973. K Closest Points to Origin
 
 
 We have a list of points on the plane.  Find the K closest points to the origin (0, 0).

 (Here, the distance between two points on a plane is the Euclidean distance.)

 You may return the answer in any order.  The answer is guaranteed to be unique (except for the order that it is in.)

  

 Example 1:

 Input: points = [[1,3],[-2,2]], K = 1
 Output: [[-2,2]]
 Explanation:
 The distance between (1, 3) and the origin is sqrt(10).
 The distance between (-2, 2) and the origin is sqrt(8).
 Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
 We only want the closest K = 1 points from the origin, so the answer is just [[-2,2]].
 
 Example 2:

 Input: points = [[3,3],[5,-1],[-2,4]], K = 2
 Output: [[3,3],[-2,4]]
 (The answer [[-2,4],[3,3]] would also be accepted.)
 
 */

#include <vector>
using std::vector;

#include <queue>
using std::priority_queue;

#include <algorithm>
#include <numeric>

class KClosest {
    
public:
    vector<vector<int>> doit(vector<vector<int>>&& points, int K) {
                
        priority_queue<std::pair<int, vector<int>*>> pq;
        for (auto& c: points) {
            pq.push({ -(c[0] * c[0] + c[1]*c[1]), &c});
        }
        
        vector<vector<int>> res;
        while (K > 0 && !pq.empty()) {
            auto c = pq.top();
            res.push_back(*c.second);
            pq.pop();
            K--;
        }
        
        return res;
    }
    
    vector<vector<int>> doit1(vector<vector<int>>&& points, int K) {
        
        std::sort(points.begin(), points.end(), [](auto& a, auto& b) {
            return (a[0] * a[0] + a[1] * a[1]) < (b[0] * b[0] + b[1] * b[1]);
        });
        
        vector<vector<int>> res;
        for (int i = 0; i < std::min(K, static_cast<int>(points.size())); i++)
            res.push_back(points[i]);
        return res;
    }
    
    vector<vector<int>> doit3(vector<vector<int>>&& points, int K) {
        
        std::sort(points.begin(), points.end(), [](auto& a, auto& b) {
            return (a[0] * a[0] + a[1] * a[1]) < (b[0] * b[0] + b[1] * b[1]);
        });
        
        int k = std::min(K, static_cast<int>(points.size()));
        vector<vector<int>> res(points.begin(), points.begin() + k);
        return res;
    }
    
    vector<vector<int>> doit2(vector<vector<int>>&& points, int K) {
        nth_element(points.begin(), points.begin()+K, points.end(), [](auto& a, auto& b) {
            return (a[0] * a[0] + a[1] * a[1]) < (b[0] * b[0] + b[1] * b[1]);
        });
        
        vector<vector<int>>::iterator st = points.begin();
        vector<vector<int>>::iterator en = points.begin() + K;
        return vector<vector<int>>(st,en);
    }
    
    
};

void test_973_kclosest_points_to_origin() {
    
    auto res1 = KClosest().doit(vector<vector<int>>{{3, 3}, {5, -1}, {-2, 4}}, 2);
    
    auto res2 = KClosest().doit(vector<vector<int>>{{1, 3}, {-2, 2}}, 1);
    
    return;
}
