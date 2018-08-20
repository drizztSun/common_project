#include <stdlib.h>
#include <vector>
#include <unordered_map>

using namespace std;


/*
# Fisher–Yates shuffle
# https://en.wikipedia.org/wiki/Fisher–Yates_shuffle
#
#
*/

class RandomFlipMatrix {
public:
	RandomFlipMatrix(int n_rows, int n_cols) {
		m = n_rows;
		n = n_cols;
		reset();
	}

	vector<int> flip() {

		int r = rand() % (index + 1);
		int val = r;
		if (d.count(r) != 0)
			val = d[r];

		if (d.count(index) == 0)
			d[r] = index;
		else
			d[r] = d[index];

		index -= 1;

		return { val / n, val % n };
	}

	void reset() {
		index = m * n - 1;
		d.clear();
	}

	int m, n;
	int index;
	unordered_map<int, int> d;
};


class Solution {

public:
	Solution(int n_rows, int n_cols) {
		m = n_rows;
		n = n_cols;
		reset();
	}

	vector<int> flip() {

		int r = rand() % (end - start + 1) + start;
		int val = r;
		if (d.count(r) != 0)
			val = d[r];

		if (d.count(start) == 0)
			d[r] = start;
		else
			d[r] = d[start];

		start += 1;
		return { val / n, val % n };
	}

	void reset() {
		start = 0;
		end = m * n - 1;
		d.clear();
	}

	int m, n;
	int start;
	int end;
	unordered_map<int, int> d;
};

void Test_519_RandomFlipMatrix() {

	RandomFlipMatrix obj(2, 2);

	for (auto i = 0; i < 3; i++) {
		obj.flip();
	}

	obj.reset();
}

