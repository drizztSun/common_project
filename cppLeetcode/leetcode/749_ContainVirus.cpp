/*
# 749. Contain Virus

# A virus is spreading rapidly, and your task is to quarantine the infected area by installing walls.

# The world is modeled as a 2-D array of cells, where 0 represents uninfected cells,
# and 1 represents cells contaminated with the virus.
# A wall (and only one wall) can be installed between any two 4-directionally adjacent cells, on the shared boundary.

# Every night, the virus spreads to all neighboring cells in all four directions unless blocked by a wall.
# Resources are limited. Each day, you can install walls around only one region
# -- the affected area (continuous block of infected cells)
# that threatens the most uninfected cells the following night. There will never be a tie.

# Can you save the day? If so, what is the number of walls required?
#  If not, and the world becomes fully infected, return the number of walls used.

# Example 1:
# Input: grid =
# [[0,1,0,0,0,0,0,1],
#  [0,1,0,0,0,0,0,1],
#  [0,0,0,0,0,0,0,1],
#  [0,0,0,0,0,0,0,0]]
# Output: 10
# Explanation:
# There are 2 contaminated regions.
# On the first day, add 5 walls to quarantine the viral region on the left. The board after the virus spreads is:


# [[0,1,0,0,0,0,1,1],
#  [0,1,0,0,0,0,1,1],
#  [0,0,0,0,0,0,1,1],
#  [0,0,0,0,0,0,0,1]]

# On the second day, add 5 walls to quarantine the viral region on the right. The virus is fully contained.

# Example 2:
# Input: grid =
# [[1,1,1],
#  [1,0,1],
#  [1,1,1]]
# Output: 4
# Explanation: Even though there is only one cell saved, there are 4 walls built.

# Notice that walls are only built on the shared boundary of two different cells.
# Example 3:
# Input: grid =
# [[1,1,1,0,0,0,0,0,0],
#  [1,0,1,0,1,1,1,1,1],
#  [1,1,1,0,0,0,0,0,0]]
# Output: 13
# Explanation: The region on the left only builds two new walls.


# Note:
# The number of rows and columns of grid will each be in the range [1, 50].
# Each grid[i][j] will be either 0 or 1.
# Throughout the described process, there is always a contiguous viral region
# that will infect strictly more uncontaminated squares in the next round.

*/

/*

To be able to use std::unordered_map (or one of the other unordered associative containers) with a user-defined key-type, you need to define two things:

A hash function; this must be a class that overrides operator() and calculates the hash value given an object of the key-type.
One particularly straight-forward way of doing this is to specialize the std::hash template for your key-type.

A comparison function for equality; this is required because the hash cannot rely on the fact
that the hash function will always provide a unique hash value for every distinct key (i.e., it needs to be able to deal with collisions),
so it needs a way to compare two given keys for an exact match. You can implement this either as a class that overrides operator(), 
or as a specialization of std::equal, or � easiest of all � by overloading operator==() for your key type (as you did already).

The difficulty with the hash function is that if your key type consists of several members, you will usually have the hash function calculate hash values for the individual members, and then somehow combine them into one hash value for the entire object. For good performance (i.e., few collisions) you should think carefully about how to combine the individual hash values to ensure you avoid getting the same output for different objects too often.

A fairly good starting point for a hash function is one that uses bit shifting and bitwise XOR to combine the individual hash values. For example, assuming a key-type like this:

*/

#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <functional>

using std::vector;
using std::set;
using std::unordered_set;
using std::unordered_map;


struct CORD {
	short x, y;
	CORD(int i, int j) :x(i), y(j) { }

	auto& operator = (const CORD& a) {
		this->x = a.x;
		this->y = a.y;
		return *this;
	};

	bool operator == (const CORD& c) const {
		return c.x == this->x && c.y == this->y;
	}

	auto operator + (const CORD& a) const {
		CORD rvt(0, 0);
		rvt.x = this->x + a.x;
		rvt.y = this->y + a.y;
		return rvt;
	}

};

namespace std {

	template<>
	struct hash<CORD> {

		auto operator()(const CORD& _cord) const {
			// return (long long(_cord.x) << 32) + _cord.y;
			return (int(_cord.x) << 16) + _cord.y;
		}
	};
}

class ContainVirus {

	typedef unordered_set<CORD> CORD_GROUP;
	typedef unordered_map<CORD, int> CORD_MAP;

public:

	void getGroups(vector<vector<int>>& grid, vector<CORD_GROUP>& groups) {

		int M = grid.size(), N = grid[0].size();
		CORD_GROUP visited;
		vector<CORD> distance{ {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

		for (auto i = 0; i < M; i++) {

			for (auto j = 0; j < N; j++) {
				CORD c(i, j);
				if (grid[i][j] != 1 || visited.find(c) != visited.end())
					continue;

				vector<CORD> queue;
				queue.push_back(c);
				CORD_GROUP group;

				while (!queue.empty()) {

					auto c = queue.back();
					queue.pop_back();

					group.insert(c);
					visited.insert(c);

					for (auto d : distance) {
						auto cord = c + d;
						if (0 <= cord.x && cord.x < M &&
							0 <= cord.y && cord.y < N &&
							grid[cord.x][cord.y] == 1 && visited.find(cord) == visited.end()) {
							
							visited.insert(cord);
							queue.push_back(cord);
						}

					}
				}

				groups.push_back(group);
			}
		}
	}


	void expand(vector<vector<int>>& grid, CORD_GROUP& group, CORD_MAP& counter) {
		int M = grid.size(), N = grid[0].size();
		vector<CORD> distance{ { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };

		for (auto c : group) {
			for (auto d : distance) {
				auto cord = c + d;
				if (cord.x >= 0 && cord.x < M && cord.y >= 0 && cord.y < N &&
					grid[cord.x][cord.y] == 0) {
					counter[cord] += 1;
				}
			}
		}
	}


	int doit(vector<vector<int>>& grid) {

		vector<CORD_GROUP> groups;
		getGroups(grid, groups);
		int nwalls = 0;


		while (!groups.empty()) {

			size_t idx = 0, maxv = 0;
			vector<CORD_MAP> counters;

			for (size_t i = 0; i < groups.size(); i++) {

				CORD_MAP counter;
				expand(grid, groups[i], counter);

				if (counter.size() > maxv) {
					idx = i;
					maxv = counter.size();
				}

				counters.push_back(counter);
			}

			for (auto c : groups[idx]) {
				grid[c.x][c.y] = 2;
			}

			
			maxv = 0;
			for (size_t i = 0; i < counters.size(); i++) {
				if (i != idx) {
					for (auto c : counters[i]) {
						auto cord = c.first;
						grid[cord.x][cord.y] = 1;
					}	
				}
				else {
					for (auto c : counters[i]) {
						maxv += c.second;
					}
				}
			}

			nwalls += maxv;

			groups.clear();
			getGroups(grid, groups);

		}

		return nwalls;
	}

};

class Solution {
public:
	int containVirus(vector<vector<int>>& grid) {
		const int m = grid.size();
		const int n = grid[0].size();
		const vector<Pos> steps = { { 1, 0 },{ -1, 0 },{ 0, 1 },{ 0, -1 } };
		int numTotalWalls = 0;

		while (true) {
			vector<vector<Pos>> vList;
			vector<vector<Pos>> cList;
			vector<int> nwList;
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					if (grid[i][j] == 1) {
						grid[i][j] = -1;
						vector<Pos> viruses;
						viruses.push_back({ i, j });
						vector<Pos> cells;
						int numWalls = 0;
						int k = 0;
						while (k != viruses.size()) {
							const auto cur = viruses[k];
							k++;
							for (const auto& step : steps) {
								const auto next = cur + step;
								const auto i = next.i;
								const auto j = next.j;
								if (!(i >= 0 && i < m && j >= 0 && j < n)) {
									continue;
								}
								if (grid[i][j] == 1) {
									grid[i][j] = -1;
									viruses.push_back({ i, j });
								}
								else if (grid[i][j] == 0) {
									grid[i][j] = 2;
									numWalls++;
									cells.push_back({ i, j });
								}
								else if (grid[i][j] == 2) {
									numWalls++;
								}
							}
						}
						for (const auto& p : cells) {
							grid[p.i][p.j] = 0;
						}
						vList.push_back(move(viruses));
						cList.push_back(move(cells));
						nwList.push_back(numWalls);
					}
				}
			}
			int maxNumCells = 0;
			int idx = -1;
			for (int i = 0; i < cList.size(); i++) {
				if (cList[i].size() > maxNumCells) {
					maxNumCells = cList[i].size();
					idx = i;
				}
			}
			if (maxNumCells == 0) {
				// no more cells need to save
				break;
			}
			for (int i = 0; i < cList.size(); i++) {
				if (i == idx) {
					numTotalWalls += nwList[i];
				}
				else {
					for (const auto& p : vList[i]) {
						// unquarantined
						grid[p.i][p.j] = 1;
					}
					for (const auto& p : cList[i]) {
						// contaminated
						grid[p.i][p.j] = 1;
					}
				}
			}
		}
		return numTotalWalls;
	}

private:
	struct Pos {
		int i;
		int j;
		Pos operator+(const Pos& p) const {
			return{ i + p.i, j + p.j };
		}
	};
};



void Test_749_ContainVirus() {

	vector<vector<int>> input
		{ {0, 1, 0, 0, 0, 0, 0, 1},
		{0, 1, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0} };
	
	int res = ContainVirus().doit(input);

	vector<vector<int>> input1 
		{
			{1, 1, 1 },
			{1, 0, 1 },
			{1, 1, 1}
		};

	int res1 = ContainVirus().doit(input1);

	vector<vector<int>> input2
	{ {1, 1, 1, 0, 0, 0, 0, 0, 0},
	{ 1, 0, 1, 0, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0 } };

	int res2 = ContainVirus().doit(input2);


	return;

}