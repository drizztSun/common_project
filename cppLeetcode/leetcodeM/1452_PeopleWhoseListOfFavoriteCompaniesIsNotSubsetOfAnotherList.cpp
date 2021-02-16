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
#include <bitset>

using std::bitset;
using std::unordered_map;
using std::vector;
using std::string;


class PeopleIndexes {

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
};