/*
588. Design In-Memory File System

Design an in-memory file system to simulate the following functions:

ls: Given a path in string format. If it is a file path, return a list that only contains this file's name. 
If it is a directory path, return the list of file and directory names in this directory. Your output (file and directory names together) should in lexicographic order.

mkdir: Given a directory path that does not exist, you should make a new directory according to the path. 
If the middle directories in the path don't exist either, you should create them as well. This function has void return type.

addContentToFile: Given a file path and file content in string format. If the file doesn't exist, you need to create that file containing given content. 
If the file already exists, you need to append given content to original content. This function has void return type.

readContentFromFile: Given a file path, return its content in string format.

 

Example:

Input: 
["FileSystem","ls","mkdir","addContentToFile","ls","readContentFromFile"]
[[],["/"],["/a/b/c"],["/a/b/c/d","hello"],["/"],["/a/b/c/d"]]

Output:
[null,[],null,null,["a"],"hello"]

Explanation:
filesystem
 

Note:

You can assume all file or directory paths are absolute paths which begin with / and do not end with / except that the path is just "/".
You can assume that all operations will be passed valid parameters and users will not attempt to retrieve file content or list a directory or file that does not exist.
You can assume that all directory names and file names only contain lower-case letters, and same names won't exist in the same directory.
*/
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

using std::map;
using std::unordered_map;
using std::string;
using std::vector;

/*
    588.Design-In-Memory-File-System
    这种明显带有层级结构、从上而下的搜索，提示了可以用典型的Trie数据结构。

    以前的Tire树，都是通过字符-若干字符的跨接。这里则是字符串-若干字符串的跨接。该怎么设计呢？答案是用哈希表。

    class TrieNode
    {
        public:
        map<string,TrieNode*>Map;
        bool isFile;
    };
    这样的话，从上到下的转移可以通过node = node->Map[str]来实现。
*/
class FileSystem {
    class TrieNode
    {
        public:
        map<string,TrieNode*>Map;
        bool isFile;
    };
    TrieNode* root;
    unordered_map<string,string>FileContents;
    
public:
    FileSystem() 
    {
        root=new TrieNode();
    }
    
    vector<string> ls(string path) 
    {
        TrieNode* node=root;
        string str;
        for (int i=1; i<path.size(); i++)
        {
            int i0=i;
            while (i<path.size() && path[i]!='/')
                i++;
            str=path.substr(i0,i-i0);
            node=node->Map[str];
        }
        
        if (node->isFile)
            return {str};
        else
        {
            vector<string>results;
            for (auto a:node->Map)
                results.push_back(a.first);
            return results;
        }
    }
    
    void mkdir(string path) 
    {
        TrieNode* node=root;
        for (int i=1; i<path.size(); i++)
        {
            int i0=i;
            while (i<path.size() && path[i]!='/')
                i++;
            string str=path.substr(i0,i-i0);
            if (node->Map.find(str)==node->Map.end())
                node->Map[str]=new TrieNode();                        
            node=node->Map[str];
        }
    }
    
    void addContentToFile(string filePath, string content) 
    {
        TrieNode* node=root;
        for (int i=1; i<filePath.size(); i++)
        {
            int i0=i;
            while (i<filePath.size() && filePath[i]!='/')
                i++;
            string str=filePath.substr(i0,i-i0);
            if (node->Map.find(str)==node->Map.end())
                node->Map[str]=new TrieNode();                        
            node=node->Map[str];
        }
        node->isFile=1;
        FileContents[filePath]+=content;
    }
    
    string readContentFromFile(string filePath) 
    {
        return FileContents[filePath];
    }
};


class FileSystem {

    struct FileNode {
        int status;
        string current;
        map<string, FileNode*> _children;
    
        FileNode(string name, int s) : current(name), status(s) {}
    };

    unordered_map<string, string> files;


    FileNode _root;

public:
    
    FileSystem(): _root("", 1) {}

    vector<string> ls(string path) {
        
        FileNode* p = &_root;

        for (int i = 0; i < path.length(); i++) {

            int j = i;
            while (j <path.length() && path[j] == '/') j++;

            int j1 = j;
            while (j1<path.length() && path[j1] != '/') j1++;

            if (j1 - j > 0) {

                string word = path.substr(j, j1-j);

                if (p->_children.count(word) == 0) return {};

                p = p->_children[word];
            }
            
            i = j1-1;
        }

        if (p->status == 0)
            return {p->current};

        vector<string> ans;
        for (auto k : p->_children)
            ans.push_back(k.first);
        return ans;
    }
    
    void mkdir(string path) {
        
        FileNode* p = &_root;

        for (int i = 0; i < path.length(); i++) {

            int j = i;
            while (j <path.length() && path[j] == '/') j++;

            int j1 = j;
            while (j1<path.length() && path[j1] != '/') j1++;

            if (j1 - j > 0) {

                string word = path.substr(j, j1-j);

                if (p->_children.count(word) == 0)
                    p->_children[word] = new FileNode(word, 1);

                p = p->_children[word];
            }
            
            i = j1-1;
        }
    }
    
    void addContentToFile(string path, string content) {
        
        FileNode* p = &_root;
        string word;

        for (int i = 0; i < path.length(); i++) {

            int j = i;
            while (j <path.length() && path[j] == '/') j++;

            int j1 = j;
            while (j1<path.length() && path[j1] != '/') j1++;

            if (j1 - j > 0) {

                word = path.substr(j, j1-j);

                if (p->_children.count(word) == 0)
                    p->_children[word] = new FileNode(word, 1);

                p = p->_children[word];
            }
            i = j1-1;
        }

        p->status = 0;
        p->current = word;
        files[path] += content;
    }
    
    string readContentFromFile(string filePath) {
        return files[filePath];
    }
};