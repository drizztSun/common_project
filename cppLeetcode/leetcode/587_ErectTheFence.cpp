

/*

# 587. Erect the Fence

# There are some trees, where each tree is represented by (x,y) coordinate in a two-dimensional garden.
# Your job is to fence the entire garden using the minimum length of rope as it is expensive.
# The garden is well fenced only if all the trees are enclosed.
# Your task is to help find the coordinates of trees which are exactly located on the fence perimeter.

# Example 1:
# Input: [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
# Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
# Explanation:

# Example 2:
# Input: [[1,2],[2,2],[4,2]]
# Output: [[1,2],[2,2],[4,2]]
# Explanation:


# Note:

# All trees should be enclosed together. You cannot cut the rope to enclose trees that will separate them
# in more than one group.
# All input integers will range from 0 to 100.
# The garden has at least one tree.
# All coordinates are distinct.
# Input points have NO order. No order required for output.

*/

#include <algorithm>
#include <vector>
using namespace std;

// Definition for a point.
struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

class OuterTrees {

	//bool cross(const Point& o, const Point& a, const Point& b) {
	//	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
	//}

	typedef long long coord2_t;  // must be big enough to hold 2*max(|coordinate|)^2
								 // 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross
								 // product. Returns a positive value, if OAB makes a counter-clockwise turn,
								 // negative for clockwise turn, and zero if the points are collinear.
	coord2_t cross(const Point &O, const Point &A, const Point &B) {
		return (A.x - O.x) * (coord2_t)(B.y - O.y) -
			(A.y - O.y) * (coord2_t)(B.x - O.x);
	}

public:
	vector<Point> doit(vector<Point>& points) {

		if (points.size() < 2)
			return points;

		std::sort(points.begin(), points.end(), [](auto a, auto b) {
			return a.x < b.x || (a.x == b.x && a.y < b.y);
		});

		vector<Point> lowerHull, upperHull;

		for (auto it = points.begin(); it != points.end(); it++) {
			while (lowerHull.size() >= 2 && cross(lowerHull[lowerHull.size()-2], lowerHull[lowerHull.size()-1], *it) < 0) {
				lowerHull.pop_back();
			}
			lowerHull.push_back(*it);
		}

		for (auto it = points.rbegin(); it != points.rend(); it++) {
			while (upperHull.size() >= 2 && cross(upperHull[upperHull.size()-2], upperHull[upperHull.size()-1], *it) < 0) {
				upperHull.pop_back();
			}
			upperHull.push_back(*it);
		}

		lowerHull.pop_back();
		upperHull.pop_back();
		lowerHull.insert(lowerHull.end(), upperHull.begin(), upperHull.end());

		std::sort(lowerHull.begin(), lowerHull.end(), [](auto a, auto b) {
			return a.x < b.x || (a.x == b.x && a.y < b.y);
		});
		lowerHull.erase(unique(lowerHull.begin(), lowerHull.end(), [](auto a, auto b) {
			return a.x == b.x && a.y == b.y;
		}), lowerHull.end());

		return lowerHull;
	}
};

// Ref: http://www.algorithmist.com/index.php/Monotone_Chain_Convex_Hull.cpp
class Solution {
public:
	typedef int coord_t;  // coordinate type
	typedef long long coord2_t;  // must be big enough to hold 2*max(|coordinate|)^2
								 // 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross
								 // product. Returns a positive value, if OAB makes a counter-clockwise turn,
								 // negative for clockwise turn, and zero if the points are collinear.
	coord2_t cross(const Point &O, const Point &A, const Point &B) {
		return (A.x - O.x) * (coord2_t)(B.y - O.y) -
			(A.y - O.y) * (coord2_t)(B.x - O.x);
	}

	static bool cmp(Point &p1, Point &p2) {
		return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
	}

	static bool equ(Point &p1, Point &p2) { return p1.x == p2.x && p1.y == p2.y; }
	// Returns a list of points on the convex hull in counter-clockwise order.
	// Note: the last point in the returned list is the same as the first one.
	vector<Point> outerTrees(vector<Point> &P) {
		int n = P.size(), k = 0;
		vector<Point> H(2 * n);

		// Sort points lexicographically
		sort(P.begin(), P.end(), cmp);

		// Build lower hull
		for (int i = 0; i < n; i++) {
			while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) < 0)
				k--;

			H[k++] = P[i];
		}

		// Build upper hull
		for (int i = n - 2, t = k + 1; i >= 0; i--) {
			while (k >= t && cross(H[k - 2], H[k - 1], P[i]) < 0)
				k--;

			H[k++] = P[i];
		}

		// Remove duplicates
		H.resize(k);
		sort(H.begin(), H.end(), cmp);
		H.erase(unique(H.begin(), H.end(), equ), H.end());
		return H;
	}
};



void Test_587_ErectTheFence() {

	vector<Point> input = { Point(1,1), Point(2,2), Point(2, 0), Point(2, 4), Point(3, 3), Point(4, 2) };

	auto output = Solution().outerTrees(input);
	
	vector<Point> input1 = { Point(1,1), Point(2,2), Point(2, 0), Point(2, 4), Point(3, 3), Point(4, 2) };

	auto output1 = OuterTrees().doit(input1);

	vector<Point> input2 = { Point(0,0), Point(0, 100), Point(100, 100), Point(100, 0), Point(50, 50) };

	auto output2 = OuterTrees().doit(input2);

	vector<Point> input3 = { Point(0,0), Point(0, 100), Point(100, 100), Point(100, 0), Point(50, 50) };

	auto output3 = Solution().outerTrees(input3);


	return;
}

