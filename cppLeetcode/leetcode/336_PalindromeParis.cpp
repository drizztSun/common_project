

#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

class PalindromePairs {
public:
	vector<vector<int>> doit(vector<string>& words) {

		unordered_map<string, int> dict;
		for (auto i = 0; i < words.size(); i++) {
			dict[words[i]] = i;
		}

		vector<vector<int>> res;
		for (auto i = 0; i < words.size(); i++) {

			for (auto j = 0; j < words[i].length() + 1; j++) {

				if (isPalindrome(words[i], j, words[i].length() - 1)) {
					string suffix = words[i].substr(0, j);
					reverse(suffix.begin(), suffix.end());
					if (dict.find(suffix) != dict.end() && dict[suffix] != i) {
						res.push_back({ i, dict[suffix] });
					}
				}
				
				if (j > 0 && isPalindrome(words[i], 0, j-1)) {
					string prefix = words[i].substr(j);
					reverse(prefix.begin(), prefix.end());
					if (dict.find(prefix) != dict.end() && dict[prefix] != i) {
						res.push_back({dict[prefix], i});
					}
				}

			}
		}

		return res;
	}

	bool isPalindrome(string& word, int s, int e) {
		while (s <= e && word[s] == word[e])
			s++, e--;
		return s > e;
	}
};



void Test_336_PalindromePairs() {

	PalindromePairs A;

	vector<string> a = {"a", ""};

	auto res = A.doit(a);


	a = { "bat", "tab", "cat" };

	res = A.doit(a);

	a = { "abcd", "dcba", "lls", "s", "sssll" };

	res = A.doit(a);

	return;
}
