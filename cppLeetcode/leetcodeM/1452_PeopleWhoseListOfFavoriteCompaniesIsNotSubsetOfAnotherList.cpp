/*
1452. People Whose List of Favorite Companies Is Not a Subset of Another List

Given the array favoriteCompanies where favoriteCompanies[i] is the list of favorites companies for the ith person (indexed from 0).

Return the indices of people whose list of favorite companies is not a subset of any other list of favorites companies. You must return the indices in increasing order.

 

Example 1:

Input: favoriteCompanies = [["leetcode","google","facebook"],["google","microsoft"],["google","facebook"],["google"],["amazon"]]
Output: [0,1,4] 
Explanation: 
Person with index=2 has favoriteCompanies[2]=["google","facebook"] which is a subset of favoriteCompanies[0]=["leetcode","google","facebook"] corresponding to the person with index 0. 
Person with index=3 has favoriteCompanies[3]=["google"] which is a subset of favoriteCompanies[0]=["leetcode","google","facebook"] and favoriteCompanies[1]=["google","microsoft"]. 
Other lists of favorite companies are not a subset of another list, therefore, the answer is [0,1,4].
Example 2:

Input: favoriteCompanies = [["leetcode","google","facebook"],["leetcode","amazon"],["facebook","google"]]
Output: [0,1] 
Explanation: In this case favoriteCompanies[2]=["facebook","google"] is a subset of favoriteCompanies[0]=["leetcode","google","facebook"], therefore, the answer is [0,1].
Example 3:

Input: favoriteCompanies = [["leetcode"],["google"],["facebook"],["amazon"]]
Output: [0,1,2,3]
 

Constraints:

1 <= favoriteCompanies.length <= 100
1 <= favoriteCompanies[i].length <= 500
1 <= favoriteCompanies[i][j].length <= 20
All strings in favoriteCompanies[i] are distinct.
All lists of favorite companies are distinct, that is, If we sort alphabetically each list then favoriteCompanies[i] != favoriteCompanies[j].
All strings consist of lowercase English letters only.


*/
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <bitset>

using std::bitset;
using std::unordered_map;
using std::unordered_set;
using std::vector;
using std::string;


class PeopleIndexes {

    /*
        1452.People-Whose-List-of-Favorite-Companies-Is-Not-a-Subset-of-Another-List
        解法1：暴力验证
        我们建立每个人的公司列表转化为集合。对于每个人i，我们查看那些公司列表比i更长的那些人j，看i的公司列表是不是j的公司列表的子集。如果i是j的子集的话，那么i就不是答案，终止对i的考察。如果i不是任何j的子集，那么就把i放入答案。

        解法2：bitmask
        以上解法有一个可以显著优化的地方。对于第i个人而言，不需要考察所有其他人j。我们令c2p[c]表示喜欢公司c的人的集合。我们只要考察i喜欢的所有公司的c2p集合的交集。最终留在交集里的人，就是和i一样喜欢相同公司的人。显然如果这个交集除了i之外还有其他人的话，就说明i的公司列表就是这些人的公司列表的子集。

        数据结构上如何来存储c2p[c]呢？当然可以用一个set。只不过set之间做交集的运算写起来有点麻烦。更方便的数据结构是bitset<100>，用每个bit表示这个人是否喜欢这家公司。这样c2p[x]&c2p[y]就能表达哪些人同时喜欢x和y两家公司，交集的操作非常方便。
    */
    vector<int> doit_(vector<vector<string>>& favoriteCompanies) {
        vector<unordered_set<string>>arr; 
        for (int i=0; i<favoriteCompanies.size(); i++)
        {
            unordered_set<string>Set(favoriteCompanies[i].begin(),favoriteCompanies[i].end());
            arr.push_back(Set);
        }

        vector<int>rets;
        for (int i=0; i<arr.size(); i++)
        {
            int flag = 1;
            for (int j=0; j<arr.size(); j++)            
            {                
                if (i==j) continue;
                bool include = 1;  // check if i-th set is included in j-th set
                for (auto c: arr[i])
                {
                    if (arr[j].find(c)==arr[j].end())
                    {            
                        include = 0;            
                        break;
                    }
                }
                if (include == 1) // If included, disqualification
                {
                    flag = 0;
                    break;
                }
            }
            if (flag==1) rets.push_back(i);
        }

        return rets;
    }

    vector<int> doit_(vector<vector<string>>& favoriteCompanies) 
    {
        int n = favoriteCompanies.size();
        unordered_map<string, bitset<100>>c2p;
        for (int i=0; i<n; i++)
            for (int j=0; j<favoriteCompanies[i].size(); j++)
                c2p[favoriteCompanies[i][j]][i]=1;
        
        vector<int>ret;
        for (int i=0; i<n; i++)
        {
            bitset<100>bs;
            bs.set();
            
            for (string c: favoriteCompanies[i])
            {
                bs &= c2p[c];
            }
            if (bs.count()==1)
                ret.push_back(i);
        }
        return ret;        
    }

public:
    
    vector<int> doit_(vector<vector<string>>& favs) {

        for (auto &comps : favs)
            std::sort(begin(comps), end(comps));
        
        vector<int> res;
        
        for (auto i = 0; i < favs.size(); ++i) {
            bool notSubset = true;
            for (auto j = 0; j < favs.size() && notSubset; ++j) {
                if (i == j)
                    continue;
                notSubset = !std::includes(begin(favs[j]), end(favs[j]), begin(favs[i]), end(favs[i]));
            }
            if (notSubset)
                res.push_back(i);
        }
        return res;
    }

    vector<int> doit_bitmask(vector<vector<string>>& favoriteCompanies) {

		unordered_map<string, bitset<512>> nmap;
		vector<int> ret;
		
        // set word in what lists, 1, 3, 5, ... bit
        for (int i = 0; i < favoriteCompanies.size(); ++i)
			for (auto &word : favoriteCompanies[i])
        		nmap[word].set(i);

        //
		for (int i = 0; i < favoriteCompanies.size(); ++i) {
            // for each word list, genenrate a bitset, 
            auto bits = nmap[favoriteCompanies[i][0]];
			
            for (int j = 1; j < favoriteCompanies[i].size(); ++j)
				bits &= nmap[favoriteCompanies[i][j]];
			
            // using &, if all are in two or more word list, the result count should be more than 1.
            if (bits.count() <= 1) ret.push_back(i);
		}
		return ret;
	}

    vector<int> doit_bitmask(vector<vector<string>>& favoriteCompanies) {

        const int N = 2048;
        int base = 0, n = favoriteCompanies.size();
        unordered_map<string, int> company2Idx;
        vector<bitset<N>> bits(n);


        for (int i = 0; i < n; i++) {
            
            bitset<N> tmp;
            for (auto& company: favoriteCompanies[i]) {

                if (company2Idx.count(company) == 0) {
                    company2Idx[company] = base;
                    base++;
                }
                tmp.set(company2Idx[company]);
            }
            bits[i] = tmp;
        }

        vector<int> ans;

        for (int i = 0; i < n; i++) {

            bool done = false;
            for (int j = 0; j < n; j++) {

                if (i != j && (bits[i] & bits[j]) == bits[i]) {
                    done = true;
                    break;
                } 

            }

            if (!done) ans.push_back(i);
        }

        return ans;
    }

};