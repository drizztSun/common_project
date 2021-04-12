/*
425. Word Squares

Given an array of unique strings words, return all the word squares you can build from words. You can return the answer in any order.

A sequence of strings forms a valid word square if the kth row and column read the same string, where 0 <= k < max(numRows, numColumns).

.For example, the word sequence ["ball","area","lead","lady"] forms a word square because each word reads the same both horizontally and vertically.
 

 ball
 area
 lead
 lady

Example 1:

Input: words = ["area","lead","wall","lady","ball"]
Output: [["ball","area","lead","lady"],["wall","area","lead","lady"]]

wall
area
lead
lady


Explanation:
The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
Example 2:

Input: words = ["abat","baba","atan","atal"]
Output: [["baba","abat","baba","atal"],["baba","abat","baba","atan"]]
Explanation:
The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
 

Constraints:

1 <= words.length <= 1000
1 <= words[i].length <= 5
All words[i] have the same length.
words[i] consists of only lowercase English letters.
All words[i] are unique.

*/

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

using std::unordered_map;
using std::vector;
using std::string;

class WordSquares {

    /*
        425.Word-Squares
        此题本质是一个DFS，我们试图逐行递归填充单词。假设我们已经合法地填充了前i-1行的单词，那么第i行单词s的选择其实有个约束：s的前i-1个字母必须和方块中第i列的前i-1个字母完全相同。例如：

        a b c d e
        b c f g h
        c f x x x
        d g x
        e h x
        我们已经填充了前两行（即前两列），在填充第三行的时候，发现要求前两个字母的前缀必须固定为cf，故可选择填充的单词范围就很小了。

        那么如何高效地列出符合前缀条件的单词，而不用尝试所有的300个单词呢？我们提前建立hash表，将所有单词的所有前缀（最长不超过4）作为key，映射到对应的单词。如上面的例子，我们只需要在hash["cf"]所对应的单词里面寻找一个就可以填充进第三行。如果不存在的话，那么就提前返回。

        当dfs深入到所有的行都填充完毕，此时的盘面就是一个答案。
    */
    vector<vector<string>>rets;
    unordered_map<string, vector<string>>Map;
    int n;

    vector<vector<string>> wordSquares(vector<string>& words) 
    {
        this->n = words[0].size();
        for (auto& word: words)
        {
            for (int i=0; i<n; i++)
                Map[word.substr(0, i)].push_back(word);
        }
        vector<string>ret;
        dfs(0, ret, words);
        return rets;
    }
    
    void dfs(int row, vector<string>&ret, vector<string>& words)
    {
        if (row==n)
        {    
            rets.push_back(ret);
            return;
        }
        
        string prefix;
        for (int i=0; i<row; i++)
            prefix.push_back(ret[i][row]);
        
        for (auto& word: Map[prefix])
        {
            ret.push_back(word);                                
            dfs(row+1, ret, words);
            ret.pop_back();                
        }
    }

public:

    vector<vector<string>> doit_dfs(vector<string>& words) {

        int m = words.size(), n = words[0].size();
        
        unordered_map<string, vector<int>> prefixMap;
        
        for (int k = 0; k < words.size(); k++) {
            for (int i = 0; i < words[k].length(); i++) {
                prefixMap[words[k].substr(0, i)].push_back(k);
            }
        }
        
        vector<vector<string>> ans;
        vector<string> word;

        std::function<void(int, vector<string>&)> dfs = [&](int row, vector<string>& path) {
          
            if (row == n) {
                ans.push_back(path);
                return;
            }
            
            string prefix = "";
            for (int i = 0; i < path.size(); i++)
                prefix.push_back(path[i][row]);
            
            if (prefixMap.count(prefix) > 0) {
                
                for (auto c: prefixMap[prefix]) {    
                    path.push_back(words[c]);
                    dfs(row+1, path);
                    path.pop_back();
                }
            }
        };
        
        dfs(0, word);
        return ans;
    }
};