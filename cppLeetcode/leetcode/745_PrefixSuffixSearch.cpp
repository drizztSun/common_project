


/*

# 745. Prefix and Suffix Search

# Given many words, words[i] has weight i.

# Design a class WordFilter that supports one function, WordFilter.f(String prefix, String suffix).
# It will return the word with given prefix and suffix with maximum weight.If no word exists, return -1.

# Examples:
# Input :
	# WordFilter(["apple"])
	# WordFilter.f("a", "e") // returns 0
	# WordFilter.f("b", "") // returns -1


	# Note:
# words has length in range[1, 15000].
# For each test case, up to words.length queries WordFilter.f may be made.
# words[i] has length in range[1, 10].
# prefix, suffix have lengths in range[0, 10].
# words[i] and prefix, suffix queries consist of lowercase letters only.

*/

#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>

using namespace std;


class WordFilter1 {

	typedef unordered_map<string, unordered_set<string>> FIX_UNIT;
	unordered_map<string, unordered_set<string>> prefix_;
	unordered_map<string, unordered_set<string>> suffix_;

	unordered_map<string, int> weight_;

public:
	WordFilter1(vector<string> words) {

		for (auto i = 0; i < words.size(); i++) {

			for (auto j = 0; j <= words[i].size(); j++) {
				prefix_[words[i].substr(0, j - 0)].insert(words[i]);
			}

			for (auto j = words[i].size(); j >= 0; j--) {
				suffix_[words[i].substr(j, words[i].size() - j)].insert(words[i]);
			}

			weight_[words[i]] = i;
		}

	}

	int f(string prefix, string suffix) {
		unordered_set<int> prefixWeight, suffixWeight;

		for (auto c : prefix_[prefix]) {
			prefixWeight.insert(weight_[c]);
		}

		int r = -1;
		for (auto c : suffix_[suffix]) {
			if (prefixWeight.find(weight_[c]) != prefixWeight.end()) {
				r = max(r, weight_[c]);
			}
		}
		return r;
	}
};


class WordFilter {

	unordered_map<string, vector<int>> prefix_;
	unordered_map<string, vector<int>> suffix_;


public:

	WordFilter(vector<string> words) {

		for (auto i = 0; i < words.size(); i++) {
			int length = words[i].length();
			for (auto j = 0; j <= length; j++) {
				prefix_[words[i].substr(0, j - 0)].push_back(i);
				suffix_[words[i].substr(j, length - j)].push_back(i);
			}
		}

	}

	int f(string prefix, string suffix) {

		auto pre = prefix_.find(prefix);
		auto suf = suffix_.find(suffix);

		if (pre == prefix_.end() || suf == suffix_.end())
			return -1;

		vector<int>& vP = pre->second, vS = suf->second;
		auto i = vP.rbegin(), j = vS.rbegin();

		while (i != vP.rend() && j != vS.rend()) {

			if (*i == *j) {
				return *i;
			}
			else if (*i < *j)
				j++;
			else
				i++;
		}

		return -1;
	}

};




class WordFilter3 {
public:
	vector<string> words_;
	map<string, vector<int>> byPrefix;
	map<string, vector<int>> bySuffix;

	WordFilter3(vector<string> words) {
		words_ = words;

		for (int word_index = words.size() - 1; word_index >= 0; word_index--) {
			string word = words[word_index];
			for (int i = 0; i <= word.size(); i++) {
				string prefix = word.substr(0, i);
				byPrefix[prefix].push_back(word_index);
			}
			for (int i = 0; i <= word.size(); i++) {
				string suffix = word.substr(word.size() - i, i);
				bySuffix[suffix].push_back(word_index);
			}
		}
	}

	int firstDoubleMatch(vector<int>& A, vector<int>& B) {
		int iA = 0;
		int iB = 0;
		while (iA < A.size() && iB < B.size()) {
			if (A[iA] == B[iB]) {
				return A[iA];
			}
			else if (A[iA] < B[iB]) {
				iB++;
			}
			else {
				iA++;
			}
		}
		return -1;
	}

	int f(string prefix, string suffix) {
		auto matchedPrefix = byPrefix[prefix];
		auto matchedSuffix = bySuffix[suffix];
		/*
		cout << "pref "; for (auto x: matchedPrefix) {
		cout << x << " ";
		} cout << endl;
		cout << "suf "; for (auto x: matchedSuffix) {
		cout << x << " ";
		} cout << endl;    */
		return firstDoubleMatch(matchedPrefix, matchedSuffix);
	}
};

struct TrieNode {
	vector<int> words;
	vector<TrieNode*> children;
	TrieNode() {
		words = vector<int>(0);
		children = vector<TrieNode*>(26, NULL);
	}
};

class WordFilter2 {

	TrieNode *prefix_root, *suffix_root;

public:
	WordFilter2(vector<string> words) {
		prefix_root = new TrieNode();
		suffix_root = new TrieNode();
		
		for (int i = 0; i < (int)words.size(); i++) {
			TrieNode *p = prefix_root, *q = suffix_root;
			p->words.push_back(i);
			q->words.push_back(i);
			for (int j = 0; j < (int)words[i].length(); j++) {
				if (!p->children[words[i][j] - 97])
					p->children[words[i][j] - 97] = new TrieNode();
				
				if (!q->children[words[i][words[i].length() - 1 - j] - 97]) 
					q->children[words[i][words[i].length() - 1 - j] - 97] = new TrieNode();

				p = p->children[words[i][j] - 97];
				q = q->children[words[i][words[i].length() - 1 - j] - 97];

				p->words.push_back(i);
				q->words.push_back(i);
			}
		}
	}

	int f(string prefix, string suffix) {

		TrieNode *p = prefix_root, *q = suffix_root;
		int i = 0, j = 0;
		
		while (i < prefix.length() || j < suffix.length()) {
			if (i < prefix.length()) {
				if (!p->children[prefix[i] - 97]) return -1;
				p = p->children[prefix[i++] - 97];
			}
			if (j < suffix.length()) {
				if (!q->children[suffix[suffix.length() - 1 - j] - 97]) return -1;
				q = q->children[suffix[suffix.length() - 1 - j++] - 97];
			}
		}

		i = p->words.size() - 1, j = q->words.size() - 1;
		while (i >= 0 && j >= 0) {
			if (p->words[i] == q->words[j]) 
				return p->words[i];
			
			if (p->words[i] > q->words[j]) 
				i--;
			else 
				j--;
		}

		return -1;
	}
};

/**
* Your WordFilter object will be instantiated and called as such:
* WordFilter obj = new WordFilter(words);
* int param_1 = obj.f(prefix,suffix);
*/


void Test_745_PrefixSuffixSearch() {


	vector<string> input{ "apple" };
	
	WordFilter obj(input);

	int res = obj.f("a", "");

	int res1 = obj.f("b", "");


	return;
}