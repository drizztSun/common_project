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

class FindConcatedWords {

	/*
		472.Concatenated-Words
		此题就是LC 140.Word-Break-II的翻版。

		我们将所有单词按照长度从小到大排序，然后依次加入字典树里。当我们考察一个新单词word时，就查看已有的字典树里是否有单词能够是word的前缀。如果存在的话，就把前缀刨掉，递归处理，
		继续查看字典树立是否有单词能match此时word的前缀，直至把整个word恰好都匹配完。
	*/
	class TrieNode
    {
        public:
        TrieNode* next[26];
        bool isEnd;
        TrieNode()
        {
            for (int i=0; i<26; i++)
                next[i] = NULL;
            isEnd = false;
        }
    };
    TrieNode* root;

    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) 
    {       
        sort(words.begin(), words.end(), [](string&a, string&b){return a.size()<b.size();});
        root = new TrieNode();

        vector<string>rets;
        for (auto word: words)
        {
            if (word!="" && check(word, root))
                rets.push_back(word);

            TrieNode* node = root;
            for (auto ch:word)
            {
                if (node->next[ch-'a']==NULL)
                    node->next[ch-'a'] = new TrieNode();
                node = node->next[ch-'a'];
            }
            node->isEnd = true;
        }
        return rets;
    }

    bool check(string& word, TrieNode* root)
    {
        int n = word.size();
        vector<int>visited(n,0);
        return dfs(word, 0, visited);
    }

    bool dfs(string& word, int cur, vector<int>&visited)
    {
        if (cur==word.size()) return true;

        if (visited[cur]==1) return false;

        TrieNode* node = root;

        for (int i=cur; i<word.size(); i++)
        {
            if (node->next[word[i]-'a']!=NULL)
            {
                node = node->next[word[i]-'a'];
                if (node->isEnd && dfs(word, i+1, visited))
                    return true;                
            } 
            else
            {
                break;
            }
        }

        visited[cur] = 1;
        return false;
    }

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

	vector<string> doit(vector<string>&& words) {

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


	vector<string> doit_dp(vector<string>& words) {
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
	vector<string> doit_dp_1(vector<string>& words) {
		unordered_set<string> s(words.begin(), words.end());
		vector<string> res;

		for (auto w : words) {

			auto n = w.size();
			vector<int> dp(n + 1);
			dp[0] = 1;

			for (int i = 0; i < n; i++) {
				if (dp[i] == 0) 
					continue;

				for (int j = i + 1; j <= n; j++) {
					if (j - i < n && s.count(w.substr(i, j - i)))
                        dp[j] = 1;
				}

				if (dp[n]) { 
					res.push_back(w); 
					break; 
				}
			}
		}
		return res;
	}


typedef struct _trie_node {
    uint16_t child[26];
    bool isWord;
} TrieNode;


public:
    int tmp;
    uint16_t num_node = 0;
    TrieNode n[50000];
    
    int dfs(const char *s, int i) {
        int node = 0, concat_num = 0, maxc = -1;
        
        while(s[i] != '\0') {
            tmp = s[i] - 'a';
            if(n[node].child[tmp] == 0)
                goto exit;

            node = n[node].child[tmp];
            if(n[node].isWord == true) {
                if(s[i+1] != '\0')
                    concat_num = dfs(s, i + 1);
                else
                    concat_num = 0;
                
                if(concat_num != -1) {
                    ++concat_num;
                    maxc = max(maxc, concat_num);
                    // if rest parts are complete words,
                    // we don't need to search again.
                    goto exit;  // improvement of this line from TLE -> 172 ms
                }
            }
            ++i;
        }
exit:
        return maxc;
    }
    
    vector<string> doit_dfs_trie(vector<string>& words) {
        uint32_t node = 0;
        vector<string> result;
        
        // build trie
        for(auto &w: words) {
            for(int i = 0; i < w.length(); ++i) {
                tmp = w[i] - 'a';
                if(n[node].child[tmp] == 0)
                    n[node].child[tmp] = ++num_node;
                node = n[node].child[tmp];
            }
            n[node].isWord = true;
            node = 0;
        }
        
        for(auto &w: words) {
            if(w.length() == 0) continue;
            
            const char *cstr = w.c_str();

            if(dfs(cstr, 0) >= 2)
                result.push_back(w);
        }
        return result;
    }


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
	vector<string> doit_dfs_3(vector<string>& words) {
		std::sort(words.begin(), words.end(), [](const string &lhs, const string &rhs) {
			return lhs.size() < rhs.size(); });

		min_len = std::max({ static_cast<size_t>(1), words.front().length()});
		
		for (int i = 0; i < words.size(); dict.insert(words[i++]))
			if (words[i].size() >= min_len * 2 && isConcatenated(words[i]))
				results.push_back(words[i]);
		return results;
	}
};