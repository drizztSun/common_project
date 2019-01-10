

/*



# 726. Number of Atoms

# Given a chemical formula (given as a string), return the count of each atom.

# An atomic element always starts with an uppercase character, then zero or more lowercase letters,
# representing the name.

# 1 or more digits representing the count of that element may follow if the count is greater than 1.
# If the count is 1, no digits will follow. For example, H2O and H2O2 are possible, but H1O2 is impossible.

# Two formulas concatenated together produce another formula. For example, H2O2He3Mg4 is also a formula.

# A formula placed in parentheses, and a count (optionally added) is also a formula.
# For example, (H2O2) and (H2O2)3 are formulas.

# Given a formula, output the count of all elements as a string in the following form:
# the first name (in sorted order), followed by its count (if that count is more than 1),
# followed by the second name (in sorted order), followed by its count (if that count is more than 1), and so on.


# Example 1:
# Input:
# formula = "H2O"
# Output: "H2O"
# Explanation:
# The count of elements are {'H': 2, 'O': 1}.

# Example 2:
# Input:
# formula = "Mg(OH)2"
# Output: "H2MgO2"
# Explanation:
# The count of elements are {'H': 2, 'Mg': 1, 'O': 2}.

# Example 3:
# Input:
# formula = "K4(ON(SO3)2)2"
# Output: "K4N2O14S4"
# Explanation:
# The count of elements are {'K': 4, 'N': 2, 'O': 14, 'S': 4}.


# Note:

# All atom names consist of lowercase letters, except for the first character which is uppercase.
# The length of formula will be in the range [1, 1000].
# formula will only consist of letters, digits, and round parentheses,
# and is a valid formula as defined in the problem.


*/

#include <vector>
#include <stack>
#include <string>
#include <set>
#include <unordered_map>

using namespace std;

class CountOfAtoms {

	typedef unordered_map<string, int> ElementCollector;

	void generate(ElementCollector& collector, string& content, int n) {

		for (auto c : collector) {
			collector[c.first] *= n;
		}

		string cur = "";
		string num = "";
		for (int i = 0; i <= content.size(); i++) {

			if (isupper(content[i]) || i == content.size()) {
				if (!cur.empty())
					collector[cur] += num.empty() ? n : stol(num) * n ;

				if (i < content.size())
					cur = content[i];
					num = "";
			}
			else if (isdigit(content[i])) {
				num += content[i];
			}
			else if (islower(content[i])) {
				cur += content[i];
			}
		}


	}
public:
	string doit(string formula) {

		formula = "(" + formula + ")";
		vector<string> layer;
		vector<ElementCollector> numbers;

		for (int i = 0; i < formula.size(); i++) {

			if (formula[i] == '(') {
				layer.push_back("");
				numbers.push_back(ElementCollector());
			}
			else if (formula[i] == ')') {
				int j = i + 1;
				while (j < formula.size() && formula[j] >= '0' && formula[j] <= '9')
					j++;

				int num = j == i + 1 ? 1 : stol(formula.substr(i + 1, j - i - 1));
				i = j-1;
				generate(numbers.back(), layer.back(), num);
				if (numbers.size() > 1) {
					for (auto c : numbers.back())
						numbers[numbers.size() - 2][c.first] += c.second;
					numbers.pop_back();
				}
				layer.pop_back();
			}
			else {
				layer[layer.size() - 1] += formula[i];
			}
		}

		string res = "";
		if (numbers.size() == 1) {
			set<string> keys;
			for (auto it = numbers[0].begin(); it != numbers[0].end(); it++) {
				keys.insert(it->first);
			}
			for (auto c : keys) 
				res += c + (numbers[0][c] > 1 ? to_string(numbers[0][c]) : "");
		}

		return res;
	};
		

	
};

void Test_726_NumberofAtoms() {

	string res0 = CountOfAtoms().doit("K4(ON(SO3)2)2");

	string res1 = CountOfAtoms().doit("((N42)24(OB40Li30CHe3O48LiNN26)33(C12Li48N30H13HBe31)21(BHN30Li26BCBe47N40)15(H5)16)14");

	string res2 = CountOfAtoms().doit("(((U42Se42Fe10Mc31Rh49Pu49Sb49)49V39Tm50Zr44Og6)33((W2Ga48Tm14Eu46Mt12)23(RuRnMn11)7(Yb15Lu34Ra19CuTb2)47(Md38BhCu48Db15Hf12Ir40)7CdNi21(Db40Zr24Tc27SrBk46Es41DsI37Np9Lu16)46(Zn49Ho19RhClF9Tb30SiCuYb16)15)37(Cr48(Ni31)25(La8Ti17Rn6Ce35)36(Sg42Ts32Ca)37Tl6Nb47Rh32NdGa18Cm10Pt49(Ar37RuSb30Cm32Rf28B39Re7F36In19Zn50)46)38(Rh19Md23No22PoTl35Pd35Hg)41)50");

}