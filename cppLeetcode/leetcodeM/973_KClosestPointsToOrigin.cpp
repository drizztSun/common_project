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


    vector<vector<int>> doit_partition_1(vector<vector<int>>& points, int K) {

        auto distance = [&](int i) {
           return points[i][0] * points[i][0] + points[i][1] * points[i][1];   
        };

        auto swap = [&](int i, int j) {
            if (i == j) return;
            int a0 = points[i][0], a1 = points[i][1];
            points[i][0] = points[j][0], points[i][1] = points[j][1];
            points[j][0] = a0, points[j][1] = a1;
        };

        auto partition = [&](int i, int j) {

            int kk = i;
            int base = distance(kk);
            for (int k = i; k <= j; k++) {

                if (distance(k) < base) {
                    kk += 1;
                    swap(k, kk);
                }
            }

            swap(i, kk);
            return kk;
        };

        std::function<void(int, int, int)> partition_sort = [&](int i, int j, int nth) {

            if (i >= j)
                return;

            int mid = partition(i, j);

            if (nth > mid - i + 1) {
                partition_sort(mid+1, j, nth - (mid - i + 1));
            } else if (nth < mid - i + 1) {
                partition_sort(i, mid-1, nth);
            }
        };

        partition_sort(0, points.size()-1, K);
        return vector<vector<int>>(begin(points), begin(points) + K);
    }


    /*
     O(n)
    */
    vector<vector<int>> doit_partition(vector<vector<int>>&& points, int K) {
        nth_element(points.begin(), points.begin()+K, points.end(), [](auto& a, auto& b) {
            return (a[0] * a[0] + a[1] * a[1]) < (b[0] * b[0] + b[1] * b[1]);
        });
        
        vector<vector<int>>::iterator st = points.begin();
        vector<vector<int>>::iterator en = points.begin() + K;
        return vector<vector<int>>(st,en);
    }
    /*
        O(n*log(n))
    */
    vector<vector<int>> doit_heap(vector<vector<int>>&& points, int K) {
                
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
};

void test_973_kclosest_points_to_origin() {
    
    auto res1 = KClosest().doit_partition(vector<vector<int>>{{3, 3}, {5, -1}, {-2, 4}}, 2);
    
    auto res2 = KClosest().doit_partition(vector<vector<int>>{{1, 3}, {-2, 2}}, 1);
    
    return;
}
