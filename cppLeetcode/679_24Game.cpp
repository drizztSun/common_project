/*

# 679. 24 Game

# You have 4 cards each containing a number from 1 to 9.
# You need to judge whether they could operated through *, /, +, -, (, ) to get the value of 24.

# Example 1:
# Input: [4, 1, 8, 7]
# Output: True
# Explanation: (8-4) * (7-1) = 24

# Example 2:
# Input: [1, 2, 1, 2]
# Output: False

# Note:
# The division operator / represents real division, not integer division. For example, 4 / (1 - 2/3) = 12.
# Every operation done is between two numbers. In particular, we cannot use - as a unary operator.
# For example, with [1, 1, 1, 1] as input, the expression -1 - 1 - 1 - 1 is not allowed.
# You cannot concatenate numbers together. For example, if the input is [1, 2, 1, 2], we cannot write this as 12 + 12.


*/

#include <vector>
#include <algorithm>
using namespace std;


class JudgePoint24 {

	double elipson = pow(10, -5);
	vector<char> ops{ '+', '-', '*', '/' };

	bool find24(vector<double> num) {

		if (num.size() == 1) {
			return abs(num[0] - 24.0) <= elipson;
		}
		else {

			for (size_t i = 0; i < num.size(); i++) {
				for (size_t j = 0; j < num.size(); j++) {
					if (i == j)
						continue;

					vector<double> res;
					for (size_t k = 0; k < num.size(); k++)
						if (k != i && k != j)
							res.push_back(num[k]);
					
					for (auto c : ops) {

						if (c == '+' || c == '*')
							if (i > j) continue;

						if (num[j] == 0.0 && c == '/')
							continue;

						switch (c)
						{
						case '+': 
							res.push_back(num[i] + num[j]); 
							break;
						case '-':
							res.push_back(num[i] - num[j]);
							break;
						case '*':
							res.push_back(num[i] * num[j]);
							break;
						case '/':
							res.push_back(num[i] / num[j]);
							break;
						default:
							break;
						}

						if (find24(res))
							return true;

						res.pop_back();
					}
				}
			}

			return false;
		}
	}

public:

	bool doit(vector<int>& nums) {

		vector<double> num;
		for (auto c : nums) {
			num.push_back(c * 1.0);
		}

		return find24(num);
	}
};


void Test_679_24Game() {

	JudgePoint24 game;

	auto res = game.doit(vector<int>{4, 1, 8, 7});

	auto res1 = game.doit(vector<int>{1, 2, 1, 2});

	return;
}