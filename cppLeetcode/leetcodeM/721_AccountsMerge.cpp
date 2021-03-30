/*
721. Accounts Merge


Given a list of accounts where each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some common email to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.

 

Example 1:

Input: accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
Explanation:
The first and third John's are the same person as they have the common email "johnsmith@mail.com".
The second John and Mary are different people as none of their email addresses are used by other accounts.
We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
Example 2:

Input: accounts = [["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"],["Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"],["Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"],["Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"],["Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]]
Output: [["Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"],["Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"],["Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"],["Kevin","Kevin0@m.co","Kevin3@m.co","Kevin5@m.co"],["Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"]]
 

Constraints:

1 <= accounts.length <= 1000
2 <= accounts[i].length <= 10
1 <= accounts[i][j] <= 30
accounts[i][0] consists of English letters.
accounts[i][j] (for j > 0) is a valid email.


*/
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>

using std::set;
using std::unordered_map;
using std::unordered_set;
using std::vector;
using std::string;




class AccountsMerge {

    /*
        721.Accounts-Merge
        此题是accounts的聚类，本质就是Union Find，不要被owner的名字所干扰。

        初始化时，每个account的Father都是本身。对于一组account里的所有邮箱怎么做归并：完全等价于线性地处理每两个相邻邮箱的归并。每个group的Father可以定义为字典序最小的那个。

        归并完之后，再遍历一次所有的邮箱，按照其Father分类就是答案所要求的分类。每个分类对应的人名，就是Father account对应的人名。
    */
    unordered_map<string,string>Father;
    unordered_map<string,string>Owner;
    unordered_map<string,set<string>>Group;
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) 
    {
        for (int i=0; i<accounts.size(); i++)
            for (int j=1; j<accounts[i].size(); j++)
            {
                Father[accounts[i][j]]=accounts[i][j];
                Owner[accounts[i][j]]=accounts[i][0];
            }
             
        
        for (int i=0; i<accounts.size(); i++)
        {
            for (int j=2; j<accounts[i].size(); j++)
            {
                if (FindSet(accounts[i][j])!=FindSet(accounts[i][j-1]))
                    Union(accounts[i][j],accounts[i][j-1]);
            }
        }
        
        for (int i=0; i<accounts.size(); i++)
         for (int j=1; j<accounts[i].size(); j++)
         {
             string parent = FindSet(accounts[i][j]);
             Group[parent].insert(accounts[i][j]);
         }
        
        vector<vector<string>>result;
        for (auto a:Group)
        {
            vector<string> temp;
            temp.push_back(Owner[a.first]);
            for (auto b:a.second)
                temp.push_back(b);
            result.push_back(temp);
        }
        return result;
    }
    
    string FindSet(string x)
    {
        if (x!=Father[x])
            Father[x]=FindSet(Father[x]);
        return Father[x];
    }
    
    void Union(string x, string y)
    {
        x=Father[x];
        y=Father[y];
        if (x<y)
            Father[y]=x;
        else
            Father[x]=y;
    }

public:

    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {

        unordered_map<string, string> owner;
        unordered_map<string, string> parents;
        unordered_map<string, unordered_set<string>> group;
        
        auto find = [&](string email) {
            while (parents[email] != email) {
                parents[email] = parents[parents[email]];
                email = parents[email];
            } 
            return email;
        };
        
        auto merge = [&](string a, string b) {
            string pa = find(a);
            string pb = find(b);
            
            if (pa == pb) return;
            
            if (pa < pb) {
                parents[pb] = pa;
            } else
                parents[pa] = pb;
        };
        
        for (const auto& account: accounts) {
            for (int i = 1; i < account.size(); i++) {
                owner[account[i]] = account[0];
                parents[account[i]] = account[i];
            }
        }
        
        for (const auto& account: accounts) {
            for (int i = 2; i < account.size(); i++) {
                merge(account[i], account[i-1]);
            }
        }
        
        for (const auto& account: accounts) {
            for (int i = 1; i < account.size(); i++)
                group[find(account[i])].insert(account[i]);
        }
        
        vector<vector<string>> result;
        
        for (auto it: group) {
            
            vector<string> tmp;

            for (auto& email: it.second) tmp.push_back(email);
            
            std::sort(begin(tmp), end(tmp));

            tmp.insert(begin(tmp), owner[it.first]);

            result.emplace_back(begin(tmp), end(tmp));
        } 
        
        return result;
    }

};