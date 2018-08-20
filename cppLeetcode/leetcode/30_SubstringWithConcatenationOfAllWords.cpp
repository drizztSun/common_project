#include <stdlib.h>


#include <vector>
#include <string>

#include <unordered_map>

using namespace std;

// 30. Substring with Concatenation of All Words
// travel all the words combinations to maintain a window
// there are wl(word len) times travel
// each time, n/wl words, mostly 2 times travel for each word
// one left side of the window, the other right side of the window
// so, time complexity O(wl * 2 * N/wl) = O(2N)

class SubstringWConcatenationOfAllWords {

public:

	std::vector<int> doit(const std::string& s, std::vector<std::string>& words) {

		auto wl = words[0].size();
		auto strlen = s.size();
		auto amount = words.size();
		std::vector<int> ans;

		if (strlen < wl * amount) {
			return ans;
		}


		std::unordered_map<std::string, int> gDict;
		for (auto it = words.begin(); it != words.end(); it++) {
			gDict[*it]++;
		}


		for (auto i = 0; i < wl; i++) {
			auto left = i;
			int count = 0;

			std::unordered_map<std::string, int> tDict;
			for (auto j = i; j <= strlen - wl; j += wl) {

				std::string sub_str = s.substr(j, wl);
				if (gDict.count(sub_str) == 1) {
					tDict[sub_str]++;

					if (tDict[sub_str] <= gDict[sub_str]) {
						count++;
					}
					else {
						while (tDict[sub_str] > gDict[sub_str]) {
							auto tmp = s.substr(left, wl);
							
							tDict[tmp]--;
							if (tDict[tmp] < gDict[tmp]) {
								count--;
							}
							left += wl;
						}
					}

					if (amount == count) {
						ans.push_back(left);
						count--;
						tDict[s.substr(left, wl)]--;
						left += wl;
					}
				}
				else {
					count = 0;
					tDict.clear();
					left = j + wl;
				}
			}
		}
		return ans;
	}


	vector<string> doit1(const string& s, vector<string>& words) {
		
		return vector<string>();
	}

};


void substring_with_concatenation_of_all_words() {

	std::vector<int> ans;

	std::vector<std::string> words;
	words.push_back("foo");
	words.push_back("bar");

	ans = SubstringWConcatenationOfAllWords().doit(std::string("barfoothefoobarman"), words);



	words.clear();
	words.push_back("bar");
	words.push_back("foo");
	words.push_back("the");

	ans = SubstringWConcatenationOfAllWords().doit("barfoofoobarthefoobarman", words);

}