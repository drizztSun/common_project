
#include <algorithm>
#include <vector>
using std::vector;

class MinSwap {
public:
	int doit1(vector<int>&& A, vector<int>&& B) {
		int n = 0;
		int s = 1;
		// n: natural, s: swapped
		for (size_t i = 1; i < A.size(); i++) {

			int n2 = INT_MAX;
			int s2 = INT_MAX;

			if (A[i] > A[i - 1] && B[i] > B[i - 1]) {
				n2 = std::min(n2, n);
				s2 = std::min(s2, s + 1);
			}

			if (A[i - 1] < B[i] && B[i - 1] < A[i]) {
				n2 = std::min(n2, s);
				s2 = std::min(s2, n + 1);
			}

			n = n2;
			s = s2;
		}

		return std::min(n, s);
	}

	int doit(vector<int>&& A, vector<int>&& B) {

		if (A.size() < 2) {
			return 0;
		}

		vector<int> not_swapped(A.size(), INT_MAX), swapped(A.size(), INT_MAX);
		not_swapped[0] = 0, swapped[0] = 1;

		for (int i = 1; i < not_swapped.size(); i++) {
			if (A[i] > A[i - 1] && B[i] > B[i - 1]) {
				not_swapped[i] = std::min(not_swapped[i], not_swapped[i - 1]);
				swapped[i] = std::min(swapped[i], swapped[i - 1] + 1);
			}

			if (A[i] > B[i - 1] && B[i] > A[i - 1]) {
				not_swapped[i] = std::min(not_swapped[i], swapped[i - 1]);
				swapped[i] = std::min(swapped[i], not_swapped[i - 1] + 1);
			}
		}

		return std::min(not_swapped.back(), swapped.back());
	}
};


void Test_801_MinimumSwaps() {

	int res = MinSwap().doit1(vector<int>{1, 3, 5, 4}, vector<int>{1, 2, 3, 7});

	res = 0;
}