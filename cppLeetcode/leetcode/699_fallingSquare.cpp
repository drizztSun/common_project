
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

	vector<int> doit1(vector<vector<int>>&& positions) {

        vector<int> ret;
        map<int, int> r2h; // right to height, this heigh until this right
        r2h[INT_MAX] = 0;
        int maxh = 0;

        for(auto &position: positions){
            int l=position[0], d=position[1];
            int r = l + d;
            auto iter = r2h.upper_bound(l);  // O(logn) operation for set
            int wh = iter->second;
            if(!r2h.count(l)) 
				r2h[l] = wh;
            
			while(iter->first < r){
                // Erase the interval that will be overlapped. Each interval will be erased at most once.
                iter = r2h.erase(iter);
                wh = max(wh, iter->second);
            }
            // update the height of current interval
            r2h[r] = wh + d;
            maxh = max(maxh, wh+d);
            ret.push_back(maxh);
        }
        return ret;
	}
};



void Test_699_FallingSquare() {

	auto res = FallingSquares().doit(vector<pair<int, int>>{ { 1, 2 }, { 2, 3 },{ 6, 1 } });
}