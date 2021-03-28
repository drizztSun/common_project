/*
642. Design Search Autocomplete System

Design a search autocomplete system for a search engine. Users may input a sentence (at least one word and end with a special character '#'). 
For each character they type except '#', you need to return the top 3 historical hot sentences that have prefix the same as the part of sentence already typed. Here are the specific rules:

The hot degree for a sentence is defined as the number of times a user typed the exactly same sentence before.
The returned top 3 hot sentences should be sorted by hot degree (The first is the hottest one). If several sentences have the same degree of hot, you need to use ASCII-code order (smaller one appears first).
If less than 3 hot sentences exist, then just return as many as you can.
When the input is a special character, it means the sentence ends, and in this case, you need to return an empty list.
Your job is to implement the following functions:

The constructor function:

AutocompleteSystem(String[] sentences, int[] times): This is the constructor. The input is historical data. Sentences is a string array consists of previously typed sentences. 
Times is the corresponding times a sentence has been typed. Your system should record these historical data.

Now, the user wants to input a new sentence. The following function will provide the next character the user types:

List<String> input(char c): The input c is the next character typed by the user. The character will only be lower-case letters ('a' to 'z'), blank space (' ') or a special character ('#'). 
Also, the previously typed sentence should be recorded in your system. The output will be the top 3 historical hot sentences that have prefix the same as the part of sentence already typed.

 
Example:
Operation: AutocompleteSystem(["i love you", "island","ironman", "i love leetcode"], [5,3,2,2])
The system have already tracked down the following sentences and their corresponding times:
"i love you" : 5 times
"island" : 3 times
"ironman" : 2 times
"i love leetcode" : 2 times
Now, the user begins another search:

Operation: input('i')
Output: ["i love you", "island","i love leetcode"]
Explanation:
There are four sentences that have prefix "i". Among them, "ironman" and "i love leetcode" have same hot degree. Since ' ' has ASCII code 32 and 'r' has ASCII code 114, "i love leetcode" should be in front of "ironman". 
Also we only need to output top 3 hot sentences, so "ironman" will be ignored.

Operation: input(' ')
Output: ["i love you","i love leetcode"]
Explanation:
There are only two sentences that have prefix "i ".

Operation: input('a')
Output: []
Explanation:
There are no sentences that have prefix "i a".

Operation: input('#')
Output: []
Explanation:
The user finished the input, the sentence "i a" should be saved as a historical sentence in system. And the following input will be counted as a new search.

 
Note:

The input sentence will always start with a letter and end with '#', and only one blank space will exist between two words.
The number of complete sentences that to be searched won't exceed 100. The length of each sentence including those in the historical data won't exceed 100.
Please use double-quote instead of single-quote when you write test cases even for a character input.
Please remember to RESET your class variables declared in class AutocompleteSystem, as static/class variables are persisted across multiple test cases. Please see here for more details.

*/
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using std::priority_queue;
using std::unordered_map;
using std::vector;
using std::string;


class AutocompleteSystem {

    /*
        Using unordered_map to create a Trie (if you are sure that there are only lower letters, can use vector)
        Instead of a priority_queue, we use 3 variables to track the result. In this case, we can set the history in O(1)
    */

    class Node {

            unordered_map<char, Node*> charList;
            std::pair<int, string> hot1;
            std::pair<int, string> hot2;
            std::pair<int, string> hot3;
        
        public:
            Node() : hot1({0, ""}), hot2({0, ""}), hot3({0, ""}) {}
        
            Node* insertLetter(char c) {
                Node* nextNode = NULL;
                if(!charList.count(c)) {
                    nextNode = new Node();
                    charList[c] = nextNode;
                } else {
                    nextNode = charList[c];
                }
                return nextNode;
            }
        
            void setHistory(string &s, int num) {
                if(s == hot1.second) {
                    hot1 = hot2;
                    hot2 = hot3;
                    hot3 = {0, ""};
                } else if(s == hot2.second) {
                    hot2 = hot3;
                    hot3 = {0, ""};
                } else if(s == hot3.second) {
                    hot3 = {0, ""};
                }
                
                if(num > hot1.first || (num == hot1.first && s <= hot1.second)) {
                    hot3 = hot2;
                    hot2 = hot1;
                    hot1 = {num, s};
                } else if(num > hot2.first || (num == hot2.first && s <= hot2.second)) {
                    hot3 = hot2;
                    hot2 = {num, s};
                } else if(num > hot3.first || (num == hot3.first && s <= hot3.second)) {
                    hot3 = {num, s};
                }
            }
        
            Node* searchLetter(char c) {
                if(!charList.count(c))
                    return NULL;
                return charList[c];
            } 
        
            vector<string> getHistory() {
                vector<string> result;
                if(hot1.second.size())
                    result.push_back(hot1.second);
                if(hot2.second.size())
                    result.push_back(hot2.second);
                if(hot3.second.size())
                    result.push_back(hot3.second);
                return result;
            }
        
    };
    
    Node* root;
    Node* ptr;
    unordered_map<string, int> count;
    string inputS;
    
public:

    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        root = new Node();
        ptr = root;
        for(int i = 0; i < sentences.size(); ++i) {
            Node* tmp = root;
            count[sentences[i]] = times[i];
            insertSentence(sentences[i]);
        }
    }
    
    vector<string> input(char c) {
        if(c == '#') {
            ptr = root;
            ++count[inputS];
            insertSentence(inputS);
            inputS = "";
            return vector<string> ();
        }

        inputS.push_back(c);
        if(ptr == NULL) {
            return vector<string> ();
        }
        
        ptr = ptr -> searchLetter(c);
        
        if(ptr == NULL) {
            return vector<string> ();
        }
        
        return ptr -> getHistory();
    }
    
    void insertSentence(string &s) {
        Node *p = root;
        for(int i = 0; i < s.size(); ++i) {
            p = p -> insertLetter(s[i]);
            p -> setHistory(s, count[s]);
        }
    }
};


/*
    642.Design-Search-Autocomplete-System

    如果不用trie来做的话，可以比较简单地用priority_queue来实现对所有候选语句的排序，选择最终未被弹出的三个字符串。

    核心代码非常简单：

        struct cmp
        {
            bool operator()(pair<string,int>a, pair<string,int>b)
            {
                if (a.second==b.second)
                    return a.first<b.first;
                else
                    return a.second>b.second;
            }
        };
        priority_queue<pair<string,int>,vector<pair<string,int>>,cmp>pq;              
        for (auto x:Map)
        {
            string a=x.first;
            if (match(data,a))
            {                
                pq.push({a,Map[a]});
                if (pq.size()>3) pq.pop();
            }
        } 
*/


class AutocompleteSystem {

    unordered_map<string,int>Map;
    string data;
    
    struct cmp
    {
        bool operator()(std::pair<string,int> a, std::pair<string,int> b)
        {
            if (a.second==b.second)
                return a.first<b.first;
            else
                return a.second>b.second;
        }
    };

public:
    AutocompleteSystem(vector<string> sentences, vector<int> times) 
    {
        for (int i=0; i<sentences.size(); i++)
            Map[sentences[i]]=times[i];
        data.clear();
    }
    
    vector<string> input(char c) 
    {
        if (c=='#')
        {
            Map[data]++;
            data.clear();
            return {};
        }
        
        data.push_back(c);
        priority_queue<std::pair<string,int>, vector<std::pair<string,int>>, cmp> pq;        
        
        for (auto x: Map)
        {
            string a=x.first;
            if (match(data,a))
            {                
                pq.push({a,Map[a]});
                if (pq.size()>3) pq.pop();
            }
        }
        
        vector<string>results;
        while (!pq.empty())
        {
            results.push_back(pq.top().first);
            pq.pop();
        }
        reverse(results.begin(),results.end());
        return results;
    }
    
    bool match(string a, string b)
    {
        for (int i=0; i<a.size(); i++)
        {
            if (i>=b.size() || a[i]!=b[i])
                return false;
        }
        return true;
    }
};