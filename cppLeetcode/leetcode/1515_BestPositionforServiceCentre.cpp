/*
1515. Best Position for a Service Centre

A delivery company wants to build a new service centre in a new city. The company knows the positions of all the customers in this city on a 2D-Map 
and wants to build the new centre in a position such that the sum of the euclidean distances to all customers is minimum.

Given an array positions where positions[i] = [xi, yi] is the position of the ith customer on the map, return the minimum sum of the euclidean distances to all customers.

In other words, you need to choose the position of the service centre [xcentre, ycentre] such that the following formula is minimized:


Answers within 10^-5 of the actual value will be accepted.

 

Example 1:


Input: positions = [[0,1],[1,0],[1,2],[2,1]]
Output: 4.00000
Explanation: As shown, you can see that choosing [xcentre, ycentre] = [1, 1] will make the distance to each customer = 1, the sum of all distances is 4 which is the minimum possible we can achieve.
Example 2:


Input: positions = [[1,1],[3,3]]
Output: 2.82843
Explanation: The minimum possible sum of distances = sqrt(2) + sqrt(2) = 2.82843
Example 3:

Input: positions = [[1,1]]
Output: 0.00000
Example 4:

Input: positions = [[1,1],[0,0],[2,0]]
Output: 2.73205
Explanation: At the first glance, you may think that locating the centre at [1, 0] will achieve the minimum sum, but locating it at [1, 0] will make the sum of distances = 3.
Try to locate the centre at [1.0, 0.5773502711] you will see that the sum of distances is 2.73205.
Be careful with the precision!
Example 5:

Input: positions = [[0,1],[3,2],[4,5],[7,6],[8,9],[11,1],[2,12]]
Output: 32.94036
Explanation: You can use [4.3460852395, 4.9813795505] as the position of the centre.
 

Constraints:

1 <= positions.length <= 50
positions[i].length == 2
0 <= positions[i][0], positions[i][1] <= 100



*/
#include <vector>


using std::vector;


class BestPosForServiceCenter {

public:
    
    double doit_math(vector<vector<int>>& positions) {
        int n = positions.size();
        double cx = 0, cy = 0;
        for (const auto& c: positions) {
            cx += c[0]; 
            cy += c[1];
        }

        auto distance = [&](double x, double y) -> double {
            double ans = 0.0;
            for (auto c: positions) {
                ans += sqrt((c[0] - x) * (c[0] - x) + (c[1] - y) * (c[1] - y));
            }
            return ans;
        };

        cx /= n;
        cy /= n;
        double step = 1.0;
        double minimum_distance = distance(cx, cy);

        while (step > 1e-6) {
            bool trim = true;
            for (const auto& c : vector<vector<double>>{{0, step}, {0, -step}, {step, 0}, {-step, 0}}) {
                double tmp = distance(cx + c[0], cy + c[1]);
                if (tmp < minimum_distance) {
                    cx = cx + c[0];
                    cy = cy + c[1];
                    minimum_distance = tmp;
                    trim = false;
                }
            }
            if (trim)
                step *= 0.1;
        }

        return minimum_distance;
    }

    template<typename T1, typename T2>
    double dist(const vector<T1>& a, const vector<T2>& b) {
        return sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]));
    };

    double doit_math_1(vector<vector<int>>& positions) {
        constexpr double kDelta = 1e-7;
        constexpr double kEpsilon = 1e-15;
        vector<double> c{-1, -1};
        double ans = 0;
        while (true) {
            ans = 0;
            double nx = 0, ny = 0;
            double denominator = 0;
            for (const auto& p : positions) {
                double d = dist(c, p) + kEpsilon;
                ans += d;
                nx += p[0] / d;
                ny += p[1] / d;
                denominator += 1.0 / d;
            }
            vector<double> t{nx / denominator, ny / denominator};
            if (dist(c, t) < kDelta) return ans;
            c = t;
        }
        return -1;
    }
};