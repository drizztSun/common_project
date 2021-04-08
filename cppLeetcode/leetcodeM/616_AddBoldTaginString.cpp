/*
616. Add Bold Tag in String


Given a string s and a list of strings dict, you need to add a closed pair of bold tag <b> and </b> to wrap the substrings in s that exist in dict. 
If two such substrings overlap, you need to wrap them together by only one pair of closed bold tag. Also, if two substrings wrapped by bold tags are consecutive, you need to combine them.
Example 1:

Input: 
s = "abcxyz123"
dict = ["abc","123"]
Output:
"<b>abc</b>xyz<b>123</b>"
 

Example 2:

Input: 
s = "aaabbcc"
dict = ["aaa","aab","bc"]
Output:
"<b>aaabbc</b>c"
 

Constraints:

The given dict won't contain duplicates, and its length won't exceed 100.
All the strings in input have length in range [1, 1000].
Note: This question is the same as 758: https://leetcode.com/problems/bold-words-in-string/

*/

#include <vector>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;
using std::vector;


class AddBoldTag {

public:

    string addBoldTag(string s, vector<string>& dict) 
    {
        int N=s.size();
        vector<int>p(N,0);
        
        for (int i=0; i<dict.size(); i++)
        {
            int len=dict[i].size();
            string str=dict[i];
            for (int j=0; j<=N-len; j++)
            {
                if (s.substr(j,len)==str)
                {
                    for (int k=j; k<j+len; k++)
                        p[k]=1;
                }
            }
        }
        
        string result;
        int i=0;
        while (i<N)
        {
            while (i<N && p[i]==0)
            {
                result+=s[i];
                i++;
            }                
            
            if (i==N)            
                return result;
            else
            {
                result+="<b>";
                int i0=i;
                while (i<N && p[i]==1)
                    i++;
                result+=s.substr(i0,i-i0);
                result+="</b>";
            }
        }
        
        return result;
    }


public:

    struct TrieNode{
        bool isWord = false;
        unordered_map<char, TrieNode*>next;
    };

    string addBoldTag(string s, vector<string>& dict) {
        string t = "";
        buildTrie(dict);
        for(int i = 0; i < s.size(); i++){
            auto p = root;
            int j = i;
            while(j < s.size() && p->next.count(s[j]))
                p = p->next[s[j++]];
            if(p != root && p->isWord){
                int pos = j;
                for(int k = i + 1; k < pos; k++){
                    int l = k;
                    auto v = root;
                    while(l < s.size() && v->next.count(s[l]))
                        v = v->next[s[l++]];
                    pos = max(pos, l);
                }
                t += '(' + s.substr(i, pos - i) + ')';
                i = pos - 1;
            }
            else t.push_back(s[i]);
        }
        string res = "";
        for(int i = 0; i < t.size(); i++){
            if(i + 1 < t.size() && t[i] == ')' && t[i + 1] == '(') i += 2;
            (t[i] == '(') ? res += "<b>" : (t[i] == ')') ? res += "</b>" : res += t[i];
        }
        return res;
    }
    
private:
    TrieNode* root;
    void buildTrie(vector<string>& dict){
        root = new TrieNode();
        for(auto x: dict){
            auto p = root;
            for(auto c: x){
                if(!p->next.count(c))
                    p->next[c] = new TrieNode();
                p = p->next[c];
            }
            p->isWord = true;
        }
    }


}