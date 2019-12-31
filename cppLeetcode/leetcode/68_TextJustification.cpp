/*

# 68 Text Justification

	Given an array of words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.

	You should pack your words in a greedy approach; that is, pack as many words as you can in each line. 
	
	Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.

	Extra spaces between words should be distributed as evenly as possible. 
	
	If the number of spaces on a line do not divide evenly between words, 
	
	the empty slots on the left will be assigned more spaces than the slots on the right.

	For the last line of text, it should be left justified and no extra space is inserted between words.

	Note:

	A word is defined as a character sequence consisting of non-space characters only.
	Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
	The input array words contains at least one word.
	Example 1:

	Input:
	words = ["This", "is", "an", "example", "of", "text", "justification."]
	maxWidth = 16
	Output:
	[
	"This    is    an",
	"example  of text",
	"justification.  "
	]
	Example 2:

	Input:
	words = ["What","must","be","acknowledgment","shall","be"]
	maxWidth = 16
	Output:
	[
	"What   must   be",
	"acknowledgment  ",
	"shall be        "
	]
	Explanation: Note that the last line is "shall be    " instead of "shall     be",
	because the last line must be left-justified instead of fully-justified.
	Note that the second line is also left-justified becase it contains only one word.
	Example 3:

	Input:
	words = ["Science","is","what","we","understand","well","enough","to","explain",
	"to","a","computer.","Art","is","everything","else","we","do"]
	maxWidth = 20
	Output:
	[
	"Science  is  what we",
	"understand      well",
	"enough to explain to",
	"a  computer.  Art is",
	"everything  else  we",
	"do                  "
	]


*/
#include <vector>
#include <string>

using namespace std;

class FullJustify {

	bool dfs(const vector<string>& words, int idx, int maxWidth, vector<string>& res) {
        return false;
	}


public:
	vector<string> doit1(vector<string>& words, int maxWidth) {


		return vector<string>{};
	}

	vector<string> doit(vector<string>&& words, int maxWidth) {

		vector<string> res;
		int amount = 0;
		vector<string> cur;


		for (auto& w : words) {

			if (w.length() + amount + cur.size() > maxWidth) {
				if (cur.size() == 1) {
					string s(maxWidth - amount, ' ');
					cur[0].append(s);
				}
				else {
					string a;
					a = ' ';
					for (auto i = 0; i < maxWidth - amount; i++) {
						cur[i % (cur.size() - 1)].append(a);
					}
				}

				string r;
				for (auto& u : cur) {
					r += u;
				}
				res.push_back(r);

				cur.clear();
				amount = 0;
			}

			cur.push_back(w);
			amount += w.size();
		}

		string r;
		for (auto i = 0; i < cur.size(); i++) {
			r += cur[i] + (i == cur.size() - 1 ? "" : " ");
		}
		

		res.push_back(r + string(maxWidth - r.length(), ' '));

		return res;
	}


	string get_space(int num) {
		string now;
		while (num--) {
			now += ' ';
		}
		return now;
	}

	vector<string> fullJustify(vector<string>& words, int maxWidth) {
		vector<string> ans;
		if (words.size() == 0) return ans;

		int i = 0, j = 0, k;
		while (i < words.size()) {
			int now = words[i].size();
			for (j = i + 1; j < words.size(); j++) {
				if (now + 1 + words[j].size() > maxWidth)
					break;
				now = now + 1 + words[j].size();
			}
			int space = 0, extra = 0;
			string res;

			if (j == i + 1 || j == words.size()) {
				res = words[i];
				for (k = i + 1; k < j; k++) {
					res = res + " " + words[k];
				}
				space = maxWidth - now;
				res += get_space(space);
			}
			else {
				int spaceSlot = j - i - 1;
				space = (maxWidth - now) / spaceSlot + 1;
				extra = (maxWidth - now) % spaceSlot;

				for (k = i; k < j - 1; k++) {
					res += words[k];
					res += get_space(space);
					if (extra > 0) {
						res += ' ';
						extra--;
					}
				}

				res += words[k];
			}
			i = j;
			ans.push_back(res);
		}
		return ans;
	}
};


void Test_68_TextJustification() {

	auto res1 = FullJustify().doit(vector<string>{"This", "is", "an", "example", "of", "text", "justification."}, 16);

	auto res2 = FullJustify().doit(vector<string>{"What", "must", "be", "acknowledgment", "shall", "be"}, 16);

	auto res3 = FullJustify().doit(vector<string>{"Science", "is", "what", "we", "understand", "well", "enough", "to", "explain", "to", "a", "computer.", "Art", "is", "everything", "else", "we", "do"}, 20);

	auto res4 = FullJustify().doit(vector<string> {"ask", "not", "what", "your", "country", "can", "do", "for", "you", "ask", "what", "you", "can", "do", "for", "your", "country"}, 16);


}
