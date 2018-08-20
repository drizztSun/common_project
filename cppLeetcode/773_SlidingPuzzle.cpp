/*

# 773. Sliding Puzzle


# On a 2x3 board, there are 5 tiles represented by the integers 1 through 5, and an empty square represented by 0.

# A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.

# The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].

# Given a puzzle board, return the least number of moves required so that the state of the board is solved.
# If it is impossible for the state of the board to be solved, return -1.

# Examples:

# Input: board = [[1,2,3],[4,0,5]]
# Output: 1
# Explanation: Swap the 0 and the 5 in one move.

# Input: board = [[1,2,3],[5,4,0]]
# Output: -1
# Explanation: No number of moves will make the board solved.

# Input: board = [[4,1,2],[5,0,3]]
# Output: 5
# Explanation: 5 is the smallest number of moves that solves the board.

# An example path:

# After move 0: [[4,1,2],[5,0,3]]
# After move 1: [[4,1,2],[0,5,3]]
# After move 2: [[0,1,2],[4,5,3]]
# After move 3: [[1,0,2],[4,5,3]]
# After move 4: [[1,2,0],[4,5,3]]
# After move 5: [[1,2,3],[4,5,0]]

# Input: board = [[3,2,4],[1,5,0]]
# Output: 14
# Note:

# board will be a 2 x 3 array as described above.
# board[i][j] will be a permutation of [0, 1, 2, 3, 4, 5].


*/

#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;


class SlidingPuzzle {


	

public:

	void dfs(string path, unordered_map<string, int >& cache, unordered_map<int, vector<int>>& moves, int steps, int& min_moves) {

		if (path == "123450")
			min_moves = std::min(min_moves, steps);

		if (steps >= min_moves)
			return;

		if (cache[path] == 0 || cache[path] > steps) {

			cache[path] = steps;
			int index = path.find('0');

			for (auto c : moves[index]) {
				string next = path;
				swap(next[c], next[index]);
				dfs(next, cache, moves, steps + 1, min_moves);
			}
		}
	}


	// <DFS>
	int doit(vector<vector<int>>& board) {
		
		unordered_map<int, vector<int>> moves{ { 0,{ 1, 3 } },{ 1,{ 0, 2, 4 } },{ 2,{ 1, 5 } },{ 3,{ 0, 4 } },{ 4,{ 3, 5, 1 } },{ 5,{ 4, 2 } } };
		unordered_map<string, int> cache;

		string current = to_string(board[0][0]) + to_string(board[0][1]) + to_string(board[0][2]) +
							to_string(board[1][0]) + to_string(board[1][1]) + to_string(board[1][2]);

		int min_moves = INT_MAX;
		
		dfs(current, cache, moves, 0, min_moves);

		return min_moves != INT_MAX ? min_moves : -1;
	}




	int doit2(vector<vector<int>>& board) {
		unordered_map<int, vector<int>> moves{ {0, {1, 3}}, {1, {0, 2, 4}}, {2, {1, 5}}, {3, {0, 4}}, {4, {3, 5, 1}}, {5, {4, 2}} };
		string current = to_string(board[0][0]) + to_string(board[0][1]) + to_string(board[0][2]) +
			to_string(board[1][0]) + to_string(board[1][1]) + to_string(board[1][2]);
		
		queue<pair<string, int>> q({ {current, current.find('0')} });
		unordered_map<string, int> m({ {current, 0} });

		for (; !q.empty() && q.front().first != "123450"; q.pop()) {
			
			for (auto c : moves[q.front().second]) {
				string next = q.front().first;
				swap(next[q.front().second], next[c]);

				if (m.insert({next, m[q.front().first] + 1}).second)
					q.push(make_pair(next, c));

			}
		}
		
		return q.empty() ? -1 : m[q.front().first];
	}


	// <BFS>
	int doit3(vector<vector<int>>& board) {

		string goal = "123450";
		string current = to_string(board[0][0]) + to_string(board[0][1]) + to_string(board[0][2]) +
			to_string(board[1][0]) + to_string(board[1][1]) + to_string(board[1][2]);

		vector<pair<int, int>> direct{ {0, -1}, {0, 1}, {1, 0}, {-1, 0} };
		unordered_set<string> visited;
		deque<pair<string, int>> queue;
		queue.push_back(make_pair(current, 0));


		while (!queue.empty()) {

			auto cur = queue.front();
			queue.pop_front();

			if (cur.first == goal) {
				return cur.second;
			}

			auto index = cur.first.find('0');
			int x = index / 3, y = index % 3;
			visited.insert(cur.first);

			for (auto c : direct) {
				int xx = x + c.first, yy = y + c.second;
				if (xx >= 0 && xx < 2 && yy >= 0 && yy < 3) {
					string next = cur.first;
					swap(next[xx * 3 + yy], next[index]);
					if (visited.find(next) == visited.end()) {
						queue.push_back(make_pair(next, cur.second + 1));
					}
				}

			}
		}

		return -1;
	}
};


void Test_773_SlidingPuzzle() {

	vector<vector<int>> input{ { 1, 2, 3 },{ 4, 0, 5 } };
	auto res = SlidingPuzzle().doit(input);

	vector<vector<int>> input1{ { 1, 2, 3 },{ 5, 4, 0 } };
	auto res1 = SlidingPuzzle().doit(input1);

	vector<vector<int>> input2{ { 4, 1, 2 },{ 5, 0, 3 } };
	auto res2 = SlidingPuzzle().doit(input2);

	vector<vector<int>> input3{ { 3, 2, 4 },{ 1, 5, 0 } };
	auto res3 = SlidingPuzzle().doit(input3);

	return;
}