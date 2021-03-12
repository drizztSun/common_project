/*
 # 1032. Stream of Characters

 # Implement the StreamChecker class as follows:

 # StreamChecker(words): Constructor, init the data structure with the given words.
 # query(letter): returns true if and only if for some k >= 1, the last k characters queried (in order from oldest to newest, including this letter just queried) spell one of the words in the given list.


 # Example:

 # StreamChecker streamChecker = new StreamChecker(["cd","f","kl"]); // init the dictionary.
 # streamChecker.query('a');          // return false
 # streamChecker.query('b');          // return false
 # streamChecker.query('c');          // return false
 # streamChecker.query('d');          // return true, because 'cd' is in the wordlist
 # streamChecker.query('e');          // return false
 # streamChecker.query('f');          // return true, because 'f' is in the wordlist
 # streamChecker.query('g');          // return false
 # streamChecker.query('h');          // return false
 # streamChecker.query('i');          // return false
 # streamChecker.query('j');          // return false
 # streamChecker.query('k');          // return false
 # streamChecker.query('l');          // return true, because 'kl' is in the wordlist


 # Note:

 # 1 <= words.length <= 2000
 # 1 <= words[i].length <= 2000
 # Words will only consist of lowercase English letters.
 # Queries will only consist of lowercase English letters.
 # The number of queries is at most 40000.

 
 */
#include <algorithm>
#include <vector>
#include <string>
#include <deque>

using std::deque;
using std::vector;
using std::string;



class StreamChecker {

    struct node {
        bool done = false;
        node* field[26];
        node() {
            for (size_t i = 0; i < 26; i++)
                this->field[i] = nullptr;
        }
    };

    size_t _max_length;
    node* _root;
    deque<char> _stream;
    
public:
    
    StreamChecker(vector<string>& words) : _max_length(0), _root(new node()){
        
        for (auto& word : words) {
            node* r = _root;
            _max_length = std::max(_max_length, word.length());
            
            for (int i = word.length()-1; i >= 0; i--) {
                int n = word[i] - 'a';
                if (r->field[n] == nullptr)
                    r->field[n] = new node();
                r = r->field[n];
            }
            r->done = true;
        }
    }
    
    bool query(char letter) {
        
        _stream.push_front(letter);
        
        if (_stream.size() > _max_length) {
            _stream.pop_back();
        }
        
        node * r = _root;
        
        for (size_t i = 0; i < _stream.size(); i++) {
            int c = _stream[i] - 'a';
            
            if (!r->field[c])
                return false;
            
            r = r->field[c];
            
            if (r->done)
                return true;
        }
        return false;
    }
    
    ~StreamChecker() {
        
        vector<node*> n;
        n.push_back(_root);
        
        while (!n.empty()) {
            node* r = n.back();
            n.pop_back();
            
            for (size_t i = 0; i < 26; i++) {
                if (r->field[i] != nullptr)
                    n.push_back(r->field[i]);
            }
            
            delete r;
        }
    }
};




class StreamChecker1 {


    struct node1{
        node1* arr[26];
        bool isWord = false;
    };

public:
  
    node1* root;
    string q;  //query string
  
    StreamChecker1(vector<string>& words){
        
        root = new node1();
        for (auto& s : words){
        auto cur = root;
        for (int i = s.length()-1; i >= 0; i--){
            if (!cur->arr[s[i]-'a'])
            cur->arr[s[i]-'a'] = new node1();
            cur = cur->arr[s[i]-'a'];
        }
        cur->isWord = true;
        }
    }
        
    bool query(char ch){
        q += ch;
        auto cur = root;
        for (int i = q.length()-1; i >=0; i--){
            cur = cur->arr[q[i]-'a'];
            if (!cur)
                return false;
            
            if (cur->isWord)
            return true;
        }
        return false;
    }
};