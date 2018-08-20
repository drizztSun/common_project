



class KthSmallestNum {

public:

	int doit(int m, int n, int k) {

		int lo = 1, hi = m * n;

		while (lo < hi) {

			int mid = lo + (hi - lo) / 2, num = 0;

			for (int i = 1; i <= m; i++) {
				num += (mid / i < n) ? mid / i : n;
			}

			if (num < k) {
				lo = mid + 1;
			}
			else {
				hi = mid;
			}
		}

		return lo;
	}
};


class Solution {

	int countor(int value, int m, int n) {
		int i = m, j = 1;
		int count = 0;
		while (i >= 1 && j <= n) {
			if (i * j <= value) {
				count += i;
				j++;
			}
			else {
				i--;
			}
		}
		return count;
	}

public:
	int findKthNumber(int m, int n, int k) {
		int left = 1 * 1;
		int right = m * n;
		while (left < right) {
			int mid = left + (right - left) / 2;
			int count = countor(mid, m, n);
			if (count < k) {
				left = mid + 1;
			}
			else {
				right = mid;
			}
		}
		return right;
	}

};


void Test_668_KthSmallestNunber() {

	int res = KthSmallestNum().doit(2, 3, 6);

	int res1 = KthSmallestNum().doit(3, 1, 3);

	return;
}