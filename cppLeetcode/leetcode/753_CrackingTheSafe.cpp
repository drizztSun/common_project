/*

# 753. Cracking the Safe

# There is a box protected by a password. The password is n digits,
# where each letter can be one of the first k digits 0, 1, ..., k-1.

# You can keep inputting the password, the password will automatically be matched against the last n digits entered.

# For example, assuming the password is "345", I can open it when I type "012345", but I enter a total of 6 digits.

# Please return any string of minimum length that is guaranteed to open the box after the entire string is inputted.

# Example 1:
# Input: n = 1, k = 2
# Output: "01"
# Note: "10" will be accepted too.

# Example 2:
# Input: n = 2, k = 2
# Output: "00110"
# Note: "01100", "10011", "11001" will be accepted too.

# Note:
# n will be in the range [1, 4].
# k will be in the range [1, 10].
# k^n will be at most 4096.

*/

#include <string>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;


class CrackSafe {

public:
	string doit(int n, int k) {

		string ans(n, '0');

		unordered_set<string> visited;
		visited.insert(ans);

		for (auto i = 0; i < pow(k, n); i++) {
			string cur = ans.substr(ans.length() - (n - 1), n - 1);

			for (auto j = k-1; j >= 0; j--) {
				string tmp = cur + to_string(j);
				if (visited.find(tmp) == visited.end()) {
					visited.insert(tmp);
					ans += to_string(j);
					break;
				}
			}
		}
		return ans;
	}

	string doit1(int n, int k) {

		int postfixCount = (int) pow(k, n - 1);
		int total = (int) pow(k, n);
		std::vector<bool> visit(total);
		string result(n, '0');
		visit[0] = true;
		int cur = 0;

		for (int i = 1; i < total; i++)
		{
			// cur = d1 d2 ... d[k] => prefix = d2 d3 ... d[k] 0
			int prefix = (cur % postfixCount) * k;

			for (int j = k - 1; j >= 0; j--)
			
				if (visit[prefix + j] == false)
				{
					cur = prefix + j;
					visit[cur] = true;
					result += '0' + j;
					break;
				}
		}

		return result;
	}

};


void Test_753_CrackingTheSafe() {
    
    //vector<bool> a;

	auto res = CrackSafe().doit(1, 2);

	auto res1 = CrackSafe().doit(2, 2);

	return;
}
