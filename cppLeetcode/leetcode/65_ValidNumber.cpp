/*

65. Valid Number

Validate if a given string is numeric.
Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true

*/

#include <ctype.h>
#include <string>
#include <vector>

#include <unordered_map>
using namespace std;


class isNumber {

public:

	bool doit(string s) {
		int i = 0;
		while (i < s.size() && s[i] == ' ') i++;

		int j = s.size() - 1;
		while (j < s.size() && s[j] == ' ') j--;

		s = s.substr(i, j - i + 1);
		if (s.empty())
			return false;


		bool hasNum = false, afterE = true, hasDot = false, hasE = false;

		for (int i = 0; i < s.length(); i++) {

			if (s[i] >= '0' && s[i] <= '9') {
				hasNum = true;
				afterE = true;
			}
			else if (s[i] == 'e') {
				if (hasE || !hasNum)
					return false;
				hasE = true;
				afterE = false;
			}
			else if (s[i] == '.') {
				if (hasDot || hasE)
					return false;
				hasDot = true;
			}
			else if (s[i] == '+' || s[i] == '-') {
				if (i > 0 && s[i - 1] != 'e')
					return false;
			}
			else {
				return false;
			}
		}

		return hasNum && afterE;
	}

	bool doit1(string s) {

		typedef unordered_map<string, int> dfa_node;

		vector<dfa_node> dfa;

		dfa.push_back(dfa_node());

		dfa.push_back(dfa_node{ {"blank", 1}, {"sign", 2}, {".", 4} });

		dfa.push_back(dfa_node{ {"digit", 3}, {".", 4 } });

		dfa.push_back(dfa_node{ {"digit", 3}, {".", 5}, {"e", 6}, {"blank", 9} });

		dfa.push_back(dfa_node{ {"digit", 5} });

		dfa.push_back(dfa_node{ {"digit", 5}, {"e", 6}, {"blank", 9} });

		dfa.push_back(dfa_node{ {"sign", 7}, {"digit", 8} });

		dfa.push_back(dfa_node{ {"digit", 8} });

		dfa.push_back(dfa_node{ {"digit", 8 }, {"blank", 9} });

		dfa.push_back(dfa_node{ {"blank", 9} });

		int status = 0;
		for (auto c : s) {
			string id;
			if (c >= '0' && c <= '9') {
				id = "digit";
			}
			else if (c == ' ') {
				id = "blank";
			}
			else if (c == '+' || c == '-') {
				id = 'sign';
			}
			else {
				id = c;
			}

			if (dfa[status].count(id) == 0) {
				return false;
			}

			status = dfa[status][id];
		}

		return status == 3 || status == 5 || status == 8 || status == 9;
	}

};


void Test_65_ValidNumber() {


	bool res1 = isNumber().doit("0");

	bool res2 = isNumber().doit(" 0.1 ");

	bool res3 = isNumber().doit("abc");

	bool res4 = isNumber().doit("1 a");

	bool res5 = isNumber().doit("2e10");

	bool res6 = isNumber().doit(".");

	bool res7 = isNumber().doit("  ");

	bool res8 = isNumber().doit("-1.");

	bool res9 = isNumber().doit("+1.");

	bool res10 = isNumber().doit("-1.");

	bool res11 = isNumber().doit("-1.");

	bool res12 = isNumber().doit("6+1"); // False

	bool res13 = isNumber().doit(" 005047e+6"); // True

	bool res15 = isNumber().doit(" 005047e-6"); // True

}
