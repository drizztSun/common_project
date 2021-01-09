/*
1233. Remove Sub-Folders from the Filesystem

Given a list of folders, remove all sub-folders in those folders and return in any order the folders after removing.

If a folder[i] is located within another folder[j], it is called a sub-folder of it.

The format of a path is one or more concatenated strings of the form: / followed by one or more lowercase English letters. For example, /leetcode and /leetcode/problems are valid paths while an empty string and / are not.

 

Example 1:

Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
Output: ["/a","/c/d","/c/f"]
Explanation: Folders "/a/b/" is a subfolder of "/a" and "/c/d/e" is inside of folder "/c/d" in our filesystem.
Example 2:

Input: folder = ["/a","/a/b/c","/a/b/d"]
Output: ["/a"]
Explanation: Folders "/a/b/c" and "/a/b/d/" will be removed because they are subfolders of "/a".
Example 3:

Input: folder = ["/a/b/c","/a/b/ca","/a/b/d"]
Output: ["/a/b/c","/a/b/ca","/a/b/d"]
 

Constraints:

1 <= folder.length <= 4 * 10^4
2 <= folder[i].length <= 100
folder[i] contains only lowercase letters and '/'
folder[i] always starts with character '/'
Each folder name is unique.

*/
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

using std::unordered_map;
using std::string;
using std::vector;

class RemoveSubfolders {


    struct Trie {
        unordered_map<string, Trie*> _children;
        bool _done;
    };
public:

    vector<string> doit_prefix_hashtable(vector<string>& folder) {
        vector<string> res;
        std::sort(folder.begin(), folder.end());
        string cur = folder.at(0);
        res.push_back(cur);
        int pos;
        
        for(int idx = 1; idx < folder.size(); idx++){
            pos = folder.at(idx).find(cur);
            if(pos == std::string::npos || folder.at(idx).at(cur.size()) != '/'){
                res.push_back(folder.at(idx));
                cur = folder.at(idx);
            }
        }
        return res;
    }

    vector<string> doit_trie(vector<string>& folder) {
        Trie *_root = new Trie();

        std::function<void(string)> insert = [&](const string& target) {

            Trie *node = _root;
            int i = 1; 
            string child;

            while (i < target.size() + 1) {

                if (i == target.size() || target[i] == '/') {
                    
                    if (node->_children.find(child) == node->_children.end()) {
                        node->_children[child] = new Trie();
                    }
                    node = node->_children[child];
                    child = "";
                    if (node->_done) return;
                } else {
                    child += target[i];
                }
                i++;
            }
            node->_done = true;
        };

        vector<string> ans;
        std::function<void(Trie*, string)> find = [&](Trie* p, string path){
            
            if (p->_done) {
                ans.push_back(path);
                return;
            }

            for (auto c: p->_children) {
                find(c.second, path + '/' + c.first);
            }
        };

        for (auto w: folder)
            insert(w);

        find(_root, "");

        return ans;
    }
};