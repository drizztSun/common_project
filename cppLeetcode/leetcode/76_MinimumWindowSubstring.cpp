#include <string>
#include <vector>

class MinimumWindowSubString {

public:

	std::string doit(std::string&& s, std::string&& t)
	{
		std::vector<int> nums(128);
		for (size_t i = 0; i < t.size(); i++) {
			nums[t[i]] += 1;
		}

		int i, j, I, J;
		j = i = 0;
		I = J = -1;
		int counter = t.length();

		while (j < s.length()) {

			if (nums[s[j]] > 0) {
				counter--;
			}

			nums[s[j]]--;

			if (counter <= 0) {

				while (i < j && nums[s[i]] < 0) {
					nums[s[i]]++;
					i++;
				}

				if (J == -1 || j - i < J - I) {
					J = j;
					I = i;
				}
			}

			j++;
		}
		
		return counter > 0 ? "" : s.substr(I, J - I + 1);
	}

	std::string doit2(std::string& s, std::string& t)
	{

		std::vector<int> nums(128);
		for (size_t i = 0; i < t.size(); i++) {
			nums[t[i]] += 1;
		}

		int i = -1;
		int j = 0;

		int min_len = s.size() + 1;
		int count = t.size();
		int imin = 0;

		while (i < (int)s.size() && j < (int)s.size()) {

			if (count > 0) {
				i++;

				nums[s[i]]--;
				if (nums[s[i]] >= 0) {
					count--;
				}
			}
			else {
				if (min_len > i - j + 1) {
					min_len = i - j + 1;
					imin = j;
				}

				nums[s[j]]++;
				if (nums[s[j]] > 0) {
					count += 1;
				}

				j++;
			}
		}

		return min_len == s.size() + 1 ? std::string("") : s.substr(imin, min_len);
	}

	std::string doit1(std::string& s, std::string t)
	{
		if (s.size() < t.size()) {
			return std::string("");
		}


		bool Have[128] = { false };
		int nums[128] = { 0 };

		for (size_t i = 0; i < t.size(); i++) {
			Have[t[i]] = true;
			nums[t[i]] += 1;
		}


		int i, j;
		i = -1;
		j = 0;

		int min_len = t.size() + 1;
		int count = t.size();
		int imin = -1;

		while (i < (int)s.size() && j < (int)s.size()) {

			if (count > 0) {
				i++;
				int c = s[i];
				nums[c] -= 1;
				if (Have[c] && nums[c] >= 0) {
					count -= 1;
				}

			}
			else {
				if (min_len > i - j + 1) {
					min_len = i - j + 1;
					imin = j;
				}

				int c = s[j];
				nums[c] += 1;
				if (Have[c] && nums[c] > 0) {
					count += 1;
				}

				j += 1;
			}
		}

		return imin == -1 ? "" : s.substr(imin, min_len);
	}

};




void minimum_window_substring() {

	std::string res;
	
	res = MinimumWindowSubString().doit(std::string("a"), std::string("b"));

	res = MinimumWindowSubString().doit(std::string("daaaebcfeaaaaaaaaaabc"), std::string("aabc"));

	res = MinimumWindowSubString().doit(std::string("a"), std::string("a"));

	res = MinimumWindowSubString().doit(std::string("ab"), std::string("a"));

	res = MinimumWindowSubString().doit(std::string("ADOBECODEBANC"), std::string("ABC"));

}
