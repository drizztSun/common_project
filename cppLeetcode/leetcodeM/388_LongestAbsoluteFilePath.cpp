/*
388. Longest Absolute File Path

Suppose we have a file system that stores both files and directories. An example of one system is represented in the following picture:



Here, we have dir as the only directory in the root. dir contains two subdirectories, subdir1 and subdir2. subdir1 contains a file file1.ext and subdirectory subsubdir1. subdir2 contains a subdirectory subsubdir2, which contains a file file2.ext.

In text form, it looks like this (with ⟶ representing the tab character):

dir
⟶ subdir1
⟶ ⟶ file1.ext
⟶ ⟶ subsubdir1
⟶ subdir2
⟶ ⟶ subsubdir2
⟶ ⟶ ⟶ file2.ext
If we were to write this representation in code, it will look like this: "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext". Note that the '\n' and '\t' are the new-line and tab characters.

Every file and directory has a unique absolute path in the file system, which is the order of directories that must be opened to reach the file/directory itself, all concatenated by '/'s. Using the above example, the absolute path to file2.ext is "dir/subdir2/subsubdir2/file2.ext". Each directory name consists of letters, digits, and/or spaces. Each file name is of the form name.extension, where name and extension consist of letters, digits, and/or spaces.

Given a string input representing the file system in the explained format, return the length of the longest absolute path to a file in the abstracted file system. If there is no file in the system, return 0.

 

Example 1:


Input: input = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"
Output: 20
Explanation: We have only one file, and the absolute path is "dir/subdir2/file.ext" of length 20.
Example 2:


Input: input = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
Output: 32
Explanation: We have two files:
"dir/subdir1/file1.ext" of length 21
"dir/subdir2/subsubdir2/file2.ext" of length 32.
We return 32 since it is the longest absolute path to a file.
Example 3:

Input: input = "a"
Output: 0
Explanation: We do not have any files, just a single directory named "a".
Example 4:

Input: input = "file1.txt\nfile2.txt\nlongfile.txt"
Output: 12
Explanation: There are 3 files at the root directory.
Since the absolute path for anything at the root directory is just the name itself, the answer is "longfile.txt" with length 12.
 

Constraints:

1 <= input.length <= 104
input may contain lowercase or uppercase English letters, a new line character '\n', a tab character '\t', a dot '.', a space ' ', and digits.

*/

#include <vector>
#include <string>

using std::string;
using std::vector;


class LengthLongestPath {

    /*
        388.Longest-Absolute-File-Path
        特别注意：'\n'，'\t' 这种转义字符被认为是一个字符！

        首先，根据'\n'将字符串拆分。然后，根据每个子字串前的'\t'的数目来确定它是第几级的。设置一个vector<vector>dirs，比如第三级的字串就加入dirs[3]里面。

        如果遇到一个字串表示的是文件名，则往前推其第i级的目录名，就对应了dirs[i]里面的最后一个字串。
    */
    int lengthLongestPath(string input) 
    {
        vector<string>files;
        for (int i=0; i<input.size(); i++)
        {
            int i0=i;
            while (i<input.size() && input[i]!='\n')
                i++;
            files.push_back(input.substr(i0,i-i0));
        }
                
        vector<string>dir;
        int result = 0;
        
        for (string str:files)
        {
            int k=0;
            while (k<str.size() && str[k]=='\t')
                k++;
                  
            if (dir.size()<=k) dir.resize(k+1);      
            dir[k] = str.substr(k);
                        
            if (dir[k].find(".")!=-1)
            {
                int count = 0;
                for (int i=0; i<=k; i++)
                    count+=dir[i].size();
                count+=k;
                
                result = std::max(count,result);
            }
        }
        
        return result;
    }

public:
    
    int doit_str(string input) {

        vector<string> dir;
        int maxl = 0, cur = 0;

        for (int i = 0; i < input.size(); i++) {

            int s = i;
            while (i < input.size() && input[i] == '\t') i++;
            int level = i - s;

            int j = i;
            while (i < input.size() && input[i] != '\n') i++;

            while (level != dir.size()) {
                cur -= dir.back().size();
                dir.pop_back();
            }

            dir.push_back(input.substr(j, i - j));
            cur += dir.back().size();
            
            if (dir.back().find('.') != -1)
                maxl = std::max(int(cur + dir.size() - 1), maxl);

            if (i < input.size() && input[i] == '/n') i++;
        }

        return maxl;
    }
};