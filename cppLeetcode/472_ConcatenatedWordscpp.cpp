

/*
	472. Concatenated Words


	Given a list of words (without duplicates), please write a program that returns all concatenated words in the given list of words.
	A concatenated word is defined as a string that is comprised entirely of at least two shorter words in the given array.

	Example:
	Input: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]

	Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]

	Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats";
	"dogcatsdog" can be concatenated by "dog", "cats" and "dog";
	"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
	Note:
	The number of elements of the given array will not exceed 10,000
	The length sum of elements in the given array will not exceed 600,000.
	All the input string will only include lower case letters.
	The returned elements order does not matter.

*/

#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class findConcatedWords {
public:
	// <dfs>
	bool helper(unordered_set<string>& wordsmap, const string& word, int cur, int length) {
		if (word.size() == cur) {
			return length > 1;
		}

		for (auto i = cur + 1; i <= word.size(); i++) {

			if (wordsmap.count(word.substr(cur, i - cur)) != 0 && helper(wordsmap, word, i, length + 1))
				return true;
		}

		return false;
	}

	vector<string> doit(vector<string>& words) {

		unordered_set<string> wordsmap;
		vector<string> ans;

		for (auto c : words) {
			wordsmap.insert(c);
		}

		for (auto w : words) {
			if (helper(wordsmap, w, 0, 0))
				ans.push_back(w);
		}

		return ans;
	}



	//For any qualified word, there must be at least 3 indexes(at least 1 besides 0 and n - 1 which n is the length of the word), which can be used to split the whole string to at least two sub strings and all sub strings can be found in words.
	//	E.g.input["cat", "cats", "dog", "sdog", "dogcatsdog"], for word dogcatsdog, there are 2 sets of numbers : [0, 3, 6, 10] and [0, 3, 7, 10] which can be formed by concatenating[dog, cat, sdog] and [dog, cats, dog] respectively.
	//	So, we can use a vector<int> dp(n + 1) to store if w.substr(0, i) can be formed by existing words.Once i reach to n and it is not the word itself, we put the word to results.


	vector<string> doit1(vector<string>& words) {
		unordered_set<string> words_map(words.begin(), words.end());
		vector<string> ans;

		for (auto word : words) {

			int length = word.size();
			vector<int> dp(length + 1);
			dp[0] = 1;
			
			for (auto i = 0; i < length; i++) {
				if (dp[i] == 0)
					continue;

				for (auto j = i + 1; j <= length; j++)
					if (j - i < length && words_map.count(word.substr(i, j - i)))
						dp[j] = 1;

				if (dp[length] == 1) {
					ans.push_back(word);
					break;
				}
			}
		}

		return ans;
	}

	// <DP>
	vector<string> doit3(vector<string>& words) {
		unordered_set<string> s(words.begin(), words.end());
		vector<string> res;

		for (auto w : words) {

			int n = w.size();
			vector<int> dp(n + 1);
			dp[0] = 1;

			for (int i = 0; i < n; i++) {
				if (dp[i] == 0) 
					continue;

				for (int j = i + 1; j <= n; j++) {
					if (j - i < n && s.count(w.substr(i, j - i))) dp[j] = 1;
				}

				if (dp[n]) { 
					res.push_back(w); 
					break; 
				}
			}
		}
		return res;
	}


};



class Solution {

	vector<string> results;
	unordered_set<string> dict;
	int min_len = 1;

	bool isConcatenated(string const & word)
	{
		if (dict.count(word)) return true;
		for (int i = min_len; i < word.size() - min_len + 1; ++i)
			if (dict.count(word.substr(0, i)) > 0 && isConcatenated(word.substr(i, word.size() - i)))
				return true;
		return false;
	}

public:
	vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
		std::sort(words.begin(), words.end(), [](const string &lhs, const string &rhs) {
			return lhs.size() < rhs.size(); });

		min_len = std::max({ static_cast<size_t>(1), words.front().length()});
		
		for (int i = 0; i < words.size(); dict.insert(words[i++]))
			if (words[i].size() >= min_len * 2 && isConcatenated(words[i]))
				results.push_back(words[i]);
		return results;
	}
};

void Test_472_ConcatenatedWords() {

	vector<string> input{ "cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat" };

	findConcatedWords A;

	auto res = A.doit1(input);

	res = A.doit1(vector<string>());

	return;
}