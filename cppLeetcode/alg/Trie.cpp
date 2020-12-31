#include <vector>
#include <string>

using std::string;
using std::vector;


class WordDictionary_Trie {

    struct Trie {

        vector<Trie*> children;
        bool done;
        Trie(): children(26), done(false) {}

    };

    Trie _root;

public:

    /** Initialize your data structure here. */
    WordDictionary_Trie() {}

    ~WordDictionary_Trie() {

        std::function<void(Trie*)> dfs = [](Trie* node) {
            if (!node) return;

            for (Trie* c: node->children) {
                if(c) {
                    dfs(c);
                    delete c;
                }
            }
        };
        dfs(&_root);
    }

    void _build(const string& word) {
        
        Trie *node = &_root;

        for (auto w: word) {
            int index = w - 'a';
            if (node->children[index] == nullptr)
                node->children[index] = new Trie();
            node = node->children[index];
        }

        node->done = true;
    }

    bool _query(const string& word) {

        std::function<bool(int, Trie*)> dfs = [&](int i, Trie* node) {
            
            if (!node)
                return false;

            if (i == word.length())
                return node->done;

            if (word[i] == '.') {
                for (auto c : node->children)
                    if (c && dfs(i+1, c))
                        return true;
                return false;
            } else {
                return dfs(i+1, node->children[word[i]-'a']);
            }
        };

        return dfs(0, &_root);
    }


    
    void addWord(string word) {
        _build(word);
    }
    
    bool search(string word) {
        return _query(word);
    }
};
