#include <stdlib.h>

#include <vector>
#include <string>
#include <math.h>
using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// Leetcode 23. Merge k Sorted Lists
class Solution {
public:
	ListNode* mergeKLists(std::vector<ListNode*>& lists) {
		ListNode** index = new ListNode*[lists.size()];
		const size_t len = lists.size();
		for (size_t i = 0; i < lists.size(); i++) {
			index[i] = lists[i];
		}


		int i = 0;
		ListNode* result = new ListNode(0);
		ListNode* v = result;
		bool done = false;

		while (!done) {
			int val = 0;
			ListNode* ref = 0;
			int pos = -1;
			done = true;
			int min = INT_MAX;

			for (size_t j = 0; j < len; j++) {
				if (index[j] != NULL && index[j]->val < min) {
					val = index[j]->val;
					min = val;
					pos = j;
					done = false;
				}
			}

			if (done)
				continue;

			v->next = new ListNode(index[pos]->val);
			index[pos] = index[pos]->next;
			v = v->next;
		}

		ListNode* a = result;
		result = result->next;
		delete a;
		delete[] index;

		return result;
	}
};

class Match {
public:
	bool isMatch(string& s, string& p) {
		int  slen = s.size(), plen = p.size(), i, j, iStar = -1, jStar = -1;

		for (i = 0, j = 0; i<slen; ++i, ++j)
		{
			if (p[j] == '*')
			{ //meet a new '*', update traceback i/j info
				iStar = i;
				jStar = j;
				--i;
			}
			else
			{
				if (p[j] != s[i] && p[j] != '?')
				{  // mismatch happens
					if (iStar >= 0)
					{ // met a '*' before, then do traceback
						i = iStar++;
						j = jStar;
					}
					else return false; // otherwise fail
				}
			}
		}
		while (p[j] == '*') ++j;
		return j == plen;
	}

	bool isMatchRecursion(std::string s, std::string p)
	{
		return dfs(s, p, 0, 0) > 1;
	}

private:
	//return value:
	//0: reach the end of s but unmatched
	//1: unmatched without reaching the end of s
	//2: matched
	int dfs(string& s, string& p, int si, int pi) 
	{
		if (si == s.size() && pi == p.size()) return 2;
		if (si == s.size() && p[pi] != '*') return 0;
		if (pi == p.size()) return 1;

		if (p[pi] == '*') {
			if (pi + 1 < p.size() && p[pi + 1] == '*')
				return dfs(s, p, si, pi + 1); // skip duplicate '*'
			for (int i = 0; i <= s.size() - si; ++i) {
				int ret = dfs(s, p, si + i, pi + 1);
				if (ret == 0 || ret == 2) return ret;
			}
		}

		if (p[pi] == '?' || s[si] == p[pi])
			return dfs(s, p, si + 1, pi + 1);

		return 1;
	}

};

void LeetCodeDrive()
{
	Match a;
	a.isMatch(std::string("aa"), std::string("a"));

	a.isMatch(std::string("aa"), std::string("*"));

}