/*
1487. Making File Names Unique

Given an array of strings names of size n. You will create n folders in your file system such that, at the ith minute, you will create a folder with the name names[i].

Since two files cannot have the same name, if you enter a folder name which is previously used, the system will have a suffix addition to its name in the form of (k), 
where, k is the smallest positive integer such that the obtained name remains unique.

Return an array of strings of length n where ans[i] is the actual name the system will assign to the ith folder when you create it.

 

Example 1:

Input: names = ["pes","fifa","gta","pes(2019)"]
Output: ["pes","fifa","gta","pes(2019)"]
Explanation: Let's see how the file system creates folder names:
"pes" --> not assigned before, remains "pes"
"fifa" --> not assigned before, remains "fifa"
"gta" --> not assigned before, remains "gta"
"pes(2019)" --> not assigned before, remains "pes(2019)"
Example 2:

Input: names = ["gta","gta(1)","gta","avalon"]
Output: ["gta","gta(1)","gta(2)","avalon"]
Explanation: Let's see how the file system creates folder names:
"gta" --> not assigned before, remains "gta"
"gta(1)" --> not assigned before, remains "gta(1)"
"gta" --> the name is reserved, system adds (k), since "gta(1)" is also reserved, systems put k = 2. it becomes "gta(2)"
"avalon" --> not assigned before, remains "avalon"
Example 3:

Input: names = ["onepiece","onepiece(1)","onepiece(2)","onepiece(3)","onepiece"]
Output: ["onepiece","onepiece(1)","onepiece(2)","onepiece(3)","onepiece(4)"]
Explanation: When the last folder is created, the smallest positive valid k is 4, and it becomes "onepiece(4)".
Example 4:

Input: names = ["wano","wano","wano","wano"]
Output: ["wano","wano(1)","wano(2)","wano(3)"]
Explanation: Just increase the value of k each time you create folder "wano".
Example 5:

Input: names = ["kaido","kaido(1)","kaido","kaido(1)"]
Output: ["kaido","kaido(1)","kaido(2)","kaido(1)(1)"]
Explanation: Please note that system adds the suffix (k) to current name even it contained the same suffix before.
 

Constraints:

1 <= names.length <= 5 * 10^4
1 <= names[i].length <= 20
names[i] consists of lower case English letters, digits and/or round brackets.
*/


#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;
using std::unordered_set;


class MakingFileNamesUnique {

    /*
        1487.Making-File-Names-Unique
        基本的策略是：对于当前的name，我们首先查看name是否以前出现过。如果没出现过，那么就直接加入。同时更新Map[name]=1，表示以后如果有与name相同的文件加入，则需要“至少”加上后缀1.

        如果name出现过的话，我们需要查看name(1)是否出现过，再看name(2)是否出现过...以此类推，直到name(k)没有出现过，就以其作为最终的名字。我们需要的数据结构非常简单，
        就是以name为key建立的一个Hash表，value就是1,2,...（注意不会有零）。当确定新的文件名是name(k)之后，记得要更新Map[name]+=1，以及Map[name(k)]=1。

        这种解法虽然依旧把所有的文件名都存入了Map，空间上并没有优势，但是在查找name(i)的时候可以更快速地定位，时间上会有优势。
    
    */
    vector<string> getFolderNames(vector<string>& names) 
    {
        unordered_map<string,int>Map;
        vector<string>rets;
        
        for (auto name: names)
        {
            if (Map.find(name)!=Map.end())            
            {                
                while (Map.find(name + "(" + std::to_string(Map[name]) + ")")!=Map.end())
                    Map[name] += 1;
                string new_name = name + "(" + std::to_string(Map[name]) + ")";                
                rets.push_back(new_name);                
                Map[name]+=1;
                Map[new_name] = 1;
            }
            else            
            {
                rets.push_back(name);                
                Map[name] = 1;
            }
                
        }
        return rets;
    }

public:
    
    vector<string> doit_hashtable(vector<string>& names) {

        vector<string> ans;
        unordered_map<string, int> nameext;

        for (auto name: names) {
    
            if (nameext.count(name) == 0) {
                nameext[name] = 0;
                ans.push_back(name);
                continue;
            } 

            string newname = name + "(" + std::to_string(++nameext[name]) + ")";
            while (nameext.count(newname)) {
                newname = name + "(" + std::to_string(++nameext[name]) + ")";
            }
            nameext[newname] = 0;
            ans.push_back(newname);
        }

        return ans;
    }
};