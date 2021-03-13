/*
76. Minimum Window Substring

Given two strings s and t, return the minimum window in s which will contain all the characters in t. If there is no such window in s that covers all characters in t, return the empty string "".

Note that If there is such a window, it is guaranteed that there will always be only one unique minimum window in s.

 

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Example 2:

Input: s = "a", t = "a"
Output: "a"
 

Constraints:

1 <= s.length, t.length <= 105
s and t consist of English letters.
 

Follow up: Could you find an algorithm that runs in O(n) time?
*/

#include <string>
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::string;

class MinimumWindowSubString {

	/*
		76. Minimum-Window-Substring
		典型的双指针题型。

		对于每个新加入的元素s[j]，首先更新该字符出现次数的Map[s[i]]++。如果更新后，Map[s[i]]等于需要出现的次数Table[s[i]]，则计数器count++，说明有一个字符满足了出现次数的要求．

		当count等于t中的字符类型数COUNT时，说明任务已经实现。此时，让左指针不断右移，相应的Map[s[i]]就要自减，一旦Map[s[i] < Table[s[i]]，则count需要自减1从而不再满足COUNT，说明需要继续加入新元素才能满足任务. 从而j才可以右移继续遍历。

		在这个过程中如果满足条件count==COUNT，都需要不断更新和记录结果。
	
	*/
	string minWindow(string s, string t) 
    {
        unordered_map<char,int>Table;
        for (int i=0; i<t.size(); i++)
            Table[t[i]]++;
        int M = Table.size();
        
        unordered_map<char,int>Map;
        int i=0;
        int Len = INT_MAX;
        string result;
        int count = 0;
        for (int j=0; j<s.size(); j++)
        {
            Map[s[j]]++;
            if (Map[s[j]]==Table[s[j]])
                count++;
            while (count==M)
            {
                if (Len>j-i+1)
                {
                    Len = j-i+1;
                    result = s.substr(i,Len);
                }
                Map[s[i]]--;
                if (Map[s[i]]==Table[s[i]]-1)
                    count--;
                i++;
            }
        }
        return result;
    }

public:


    std::string doit_twopointers(string s, string t) 
    {
        unordered_map<char,int>Table;
        for (auto c: s) Table[c]++;
        int M = Table.size();
        
        unordered_map<char,int>Map;
        int i=0;
        int Len = INT_MAX;
        string result;
        int count = 0;
		
        for (int j = 0; j < s.size(); j++)
        {
            Map[s[j]]++;

            if (Map[s[j]]==Table[s[j]])
                count++;
            
			while (count==M)
            {
                if (Len > j-i+1)
                {
                    Len = j-i+1;
                    result = s.substr(i,Len);
                }

                Map[s[i]]--;

                if (Map[s[i]] == Table[s[i]]-1)
                    count--;
                i++;
            }
        }
        return result;
    }

	std::string doit_slidingwindow(std::string&& s, std::string&& t)
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