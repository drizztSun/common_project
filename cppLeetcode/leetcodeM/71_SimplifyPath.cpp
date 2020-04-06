/*
 
 
 71. Simplify Path
 Medium

 Add to List

 Share
 Given an absolute path for a file (Unix-style), simplify it. Or in other words, convert it to the canonical path.

 In a UNIX-style file system, a period . refers to the current directory. Furthermore, a double period .. moves the directory up a level.
 For more information, see: Absolute path vs relative path in Linux/Unix

 Note that the returned canonical path must always begin with a slash /, and there must be only a single slash / between two directory names.
 The last directory name (if it exists) must not end with a trailing /. Also, the canonical path must be the shortest string representing the absolute path.

  

 Example 1:

 Input: "/home/"
 Output: "/home"
 Explanation: Note that there is no trailing slash after the last directory name.
 Example 2:

 Input: "/../"
 Output: "/"
 Explanation: Going one level up from the root directory is a no-op, as the root level is the highest level you can go.
 Example 3:

 Input: "/home//foo/"
 Output: "/home/foo"
 Explanation: In the canonical path, multiple consecutive slashes are replaced by a single one.
 Example 4:

 Input: "/a/./b/../../c/"
 Output: "/c"
 Example 5:

 Input: "/a/../../b/../c//.//"
 Output: "/c"
 Example 6:

 Input: "/a//b////c/d//././/.."
 Output: "/a/b/c"
 
 
 */

#include <stack>
using std::stack;

#include <string>
using std::string;

#include <vector>
using std::vector;

class SimplifyPath {
    
public:
    
    string doit(string path) {
        
        vector<string> buf;
        int last = 0;
        
        for (int i = 0; i <= path.length(); i++) {
            
            if (i == path.length() || (i != last && path[i] == '/')) {
                
                string field = path.substr(last+1, i - last - 1);
                
                if (field == "..") {
                    if (!buf.empty())
                        buf.pop_back();
                } else if (!field.empty() && field != ".") {
                    buf.push_back(field);
                }
                last = i;
            }
        }
        
        string res;
        for (auto& c : buf) {
            res += "/" + c;
        }
        return res.length() ? res : "/";
    }
};


void test_71_simplify_path() {
    
    auto res1 = SimplifyPath().doit("/home/");
    
    auto res2 = SimplifyPath().doit("/../");
    
    auto res3 = SimplifyPath().doit("/home//foo/");
    
    auto res4 = SimplifyPath().doit("/a/./b/../../c/");
    
    auto res5 = SimplifyPath().doit("/a/../../b/../c//.//");
    
    auto res6 = SimplifyPath().doit("/a//b////c/d//././/..");
    
}