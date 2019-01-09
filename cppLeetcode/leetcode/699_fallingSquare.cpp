
/*



# 699. Falling Squares

# On an infinite number line (x-axis), we drop given squares in the order they are given.

# The i-th square dropped (positions[i] = (left, side_length)) is a square with the left-most point
# being positions[i][0] and sidelength positions[i][1].

# The square is dropped with the bottom edge parallel to the number line, and from a higher height than
# all currently landed squares. We wait for each square to stick before dropping the next.

# The squares are infinitely sticky on their bottom edge, and will remain fixed to any positive length surface
# they touch (either the number line or another square).
# Squares dropped adjacent to each other will not stick together prematurely.


# Return a list ans of heights. Each height ans[i] represents the current highest height of any square we have dropped,
# after dropping squares represented by positions[0], positions[1], ..., positions[i].

# Example 1:
# Input: [[1, 2], [2, 3], [6, 1]]
# Output: [2, 5, 5]
# Explanation:

# After the first drop of positions[0] = [1, 2]:
# _aa
# _aa
# -------
# The maximum height of any square is 2.


# After the second drop of positions[1] = [2, 3]:
# __aaa
# __aaa
# __aaa
# _aa__
# _aa__
# --------------
# The maximum height of any square is 5.
# The larger square stays on top of the smaller square despite where its center
# of gravity is, because squares are infinitely sticky on their bottom edge.


# After the third drop of positions[1] = [6, 1]:
# __aaa
# __aaa
# __aaa
# _aa
# _aa___a
# --------------
# The maximum height of any square is still 5.

# Thus, we return an answer of [2, 5, 5].


# Example 2:
# Input: [[100, 100], [200, 100]]
# Output: [100, 100]
# Explanation: Adjacent squares don't get stuck prematurely - only their bottom edge can stick to surfaces.

# Note:

# 1 <= positions.length <= 1000.
# 1 <= positions[i][0] <= 10^8.
# 1 <= positions[i][1] <= 10^6.


*/

#include <vector>
#include <map>
#include <algorithm>
using namespace std;

/*
	Similar to skyline concept, going from left to right the path is decomposed to consecutive segments, and each segment has a height.
	Each time we drop a new square, then update the level map by erasing & creating some new segments with possibly new height.
	There are at most 2n segments that are created / removed throughout the process,
	and the time complexity for each add/remove operation is O(log(n)).
*/

class FallingSquares {

public:

	vector<int> doit1(vector<pair<int, int>>& positions) {

		vector<int> res;
		map<pair<int, int>, int> heights;
		heights[{0, INT_MAX}] = 0;



		for (auto& c : positions) {

			int left = c.first, right = c.first + c.second;
			int high = c.second;
			int max_height = 0;

			auto it = heights.upper_bound(make_pair(left, left));

			if (it != heights.begin() && (--it)->first.second <= left)
				it++;

			while (it != heights.end() && it->first.first > right) {

				

				max_height = std::max(max_height, it->second);

				it = heights.erase(it);
			}

			heights[pair<int, int>(left, right)] = max_height;

			max_height += max_height;

			if (res.size() > 0)
				max_height = std::max(max_height, res[res.size() - 1]);
			
			res.push_back(max_height);
		}

		return res;
	}


	vector<int> doit(vector<pair<int, int>>& positions) {

		map<int, int> heights;
		heights[0] = 0;
		vector<int> res;

		for (auto& c : positions) {

			int left = c.first, right = c.first + c.second;

			auto l = heights.lower_bound(left);
			auto r = heights.upper_bound(right);
			int height = 0, lastheight = 0;

			while (l != r) {
				height = std::max(height, l->second);
				lastheight = l->second;
				l = heights.erase(l);
			}

			heights[left] = height + c.second;
			heights[right] = lastheight;

			res.push_back(height);
		}
		
		return res;
	}
};



void Test_699_FallingSquare() {


	vector<pair<int, int>> input{ { 1, 2 }, { 2, 3 },{ 6, 1 } };
	
	auto res = FallingSquares().doit(input);


	return;
}