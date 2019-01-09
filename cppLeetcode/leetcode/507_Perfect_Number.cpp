/*

# 507. Perfect Number

# We define the Perfect Number is a positive integer that is equal to the sum of all its positive divisors except itself.

# Now, given an integer n, write a function that returns true when it is a perfect number and false when it is not.

# Example:
# Input: 28
# Output: True
# Explanation: 28 = 1 + 2 + 4 + 7 + 14
# Note: The input number n will not exceed 100,000,000. (1e8)



*/

#include <vector>
#include <unordered_set>
using namespace std;

class PerfectNumber {
	
public:

	bool doit(int num) {

		if (num < 6)
			return false;

		int i = 0;
		for (; (num & i) == 0; i++)
			num >>= 1;

		for (; i != 0; i--) {
			if ((num & i) == 0)
				return false;

			num >>= 1;
		}

		return num == 1;
	}


	bool doit1(int n) {

		if (n == 1)
			return false;

		int num = n;
		vector<int> primes;
		for (int i = 2; i*i <= n; i++) {
			while (num > 1 && num%i == 0) {
				primes.push_back(i);
				num /= i;
			}
		}

		unordered_set<int> st;
		int x, sum = 0, j;
		for (int i = 0; i < primes.size(); i++) {
			if (i > 0 && primes[i] == primes[i - 1])
				continue;
			x = 1;
			j = i;
			while (j < primes.size()) {
				x *= primes[j];
				if (st.find(x) == st.end()) {
					sum += x;
					st.insert(x);
				}

				if (st.find(n / x) == st.end()) {
					sum += (n / x);
					st.insert(n / x);
				}
				j++;
			}
		}
		return sum + 1 == n;
	}
};

void Test_507_PerfectNumber() {

	auto res = PerfectNumber().doit(28);

}