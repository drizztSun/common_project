/*
745. Prefix and Suffix Search


Design a special dictionary which has some words and allows you to search the words in it by a prefix and a suffix.

Implement the WordFilter class:

WordFilter(string[] words) Initializes the object with the words in the dictionary.
f(string prefix, string suffix) Returns the index of the word in the dictionary which has the prefix prefix and the suffix suffix. 
If there is more than one valid index, return the largest of them. If there is no such word in the dictionary, return -1.
 

Example 1:

Input
["WordFilter", "f"]
[[["apple"]], ["a", "e"]]
Output
[null, 0]

Explanation
WordFilter wordFilter = new WordFilter(["apple"]);
wordFilter.f("a", "e"); // return 0, because the word at index 0 has prefix = "a" and suffix = 'e".
 

Constraints:

1 <= words.length <= 15000
1 <= words[i].length <= 10
1 <= prefix.length, suffix.length <= 10
words[i], prefix and suffix consist of lower-case English letters only.
At most 15000 calls will be made to the function f.


*/
#include <vector>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::vector;
using std::string;



class WordFilter {

    unordered_map<string, vector<int>> prefix_;
	unordered_map<string, vector<int>> suffix_;

public:

	WordFilter(vector<string> words) {

		for (int i = 0; i < words.size(); i++) {
			int length = words[i].length();
			for (int j = 0; j <= length; j++) {
				prefix_[words[i].substr(0, j - 0)].push_back(i);
				suffix_[words[i].substr(j, length - j)].push_back(i);
			}
		}
	}

	int f(string prefix, string suffix) {

		auto pre = prefix_.find(prefix);
		auto suf = suffix_.find(suffix);

		if (pre == prefix_.end() || suf == suffix_.end()) return -1;

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


/*
    745.Prefix-and-Suffix-Search
    此题仍然考察基本的TrieNode的数据结构，但是需要稍微设计一下。

    如果根据前缀和后缀的双重信息来在字典树里找到一个单词呢？一个巧妙的设计就是把后缀加在单词前面，中间用"{"分隔，拼成一个新的单词，将这种新的单词加入字典树中，
    并在querry的时候查找。需要注意的是，一个正常的单词可能有k种后缀，k就是单词的长度，所以我们需要把这些所有的变化都加进字典树里。

    为什么要用“{”做分隔符呢？因为它在ASCII中的位置恰好就在'z'后面，所以我们直接在每个TrieNode里开27个TrieNode*数组就行了。

    如何快速查找weight呢？其实只要在加入字符串的时候，在每个node都标记该单词的id，而且后来的字符串id可以覆盖前面的，因为后面的认为是更大的weight。
*/
class WordFilter {

    class TrieNode
    {
    public:
        bool isEnd;
        TrieNode* next[27];
        vector<int>ids;

        TrieNode() {
            isEnd = false;
            for (int i=0; i<27; i++)
                next[i] = NULL;
        }
        
    };
    
    TrieNode* root;
    
public:
    
    void buildTree(TrieNode* root, string S, int id)
    {
        TrieNode* node = root;
        for (char ch:S)
        {
            if (node->next[ch-'a']==NULL)
                node->next[ch-'a'] = new TrieNode();
            node = node->next[ch-'a'];
            node->ids.push_back(id);
        }
    }    
    
    WordFilter(vector<string> words) 
    {
        root = new TrieNode();
        for (int i=0; i<words.size(); i++)
        {
            string word = words[i];
            string rWord;
            for (int j=0; j<word.size(); j++)
            {
                rWord = word.substr(j);
                reverse(rWord.begin(),rWord.end());
                buildTree(root, rWord+"{"+word,i);
            }
            buildTree(root, "{"+word,i);
        }
    }
    
    int f(string prefix, string suffix) 
    {
        reverse(suffix.begin(),suffix.end());
        string S = suffix+"{"+prefix;
        TrieNode* node = root;
        for (char ch:S)
        {
            if (node->next[ch-'a']==NULL)
                return -1;
            else
                node = node->next[ch-'a'];
        }
        return node->ids.back();
    }
};