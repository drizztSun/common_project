"""
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


"""


class PeopleIndexes:

    def doit_(self, favoriteCompanies: list) -> list:

        from collections import defaultdict
        base = 1
        city2index = defaultdict(int)
        allstatus = []
        
        for person in favoriteCompanies:
            status = 0
            
            for company in person:
                if company not in city2index:
                    city2index[company] = (1 << base)
                    base += 1
                    
                status |= city2index[company]
            allstatus.append(status)
            
        ans = []
        for i, status in enumerate(allstatus):
            
            for j, c in enumerate(allstatus):
                if i != j and status & c == status:
                    break   
            else:
                ans.append(i)
                
        return ans


if __name__ == '__main__':

    PeopleIndexes().doit_([["leetcode","google","facebook"],["google","microsoft"],["google","facebook"],["google"],["amazon"]])
        