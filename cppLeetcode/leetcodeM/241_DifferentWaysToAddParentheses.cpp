/*
241. Different Ways to Add Parentheses

Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. 
The valid operators are +, - and *.

Example 1:

Input: "2-1-1"
Output: [0, 2]
Explanation: 
((2-1)-1) = 0 
(2-(1-1)) = 2
Example 2:

Input: "2*3-4*5"
Output: [-34, -14, -10, -10, 10]
Explanation: 
(2*(3-(4*5))) = -34 
((2*3)-(4*5)) = -14 
((2*(3-4))*5) = -10 
(2*((3-4)*5)) = -10 
(((2*3)-4)*5) = 10

*/
#include <string>
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;
using std::string;


class DiffWaysToCompute {

public:
    
    vector<int> doit_devide_and_conquer(string input) {

        unordered_map<string, vector<int>> dp;

        std::function<vector<int>(string)> search = [&](string formula) {

            if (dp.find(formula) != dp.end())
                return dp[formula];

            vector<int> ans;
            bool not_number = false;
            int num = 0;
            for (int i = 0; i < formula.size(); i++) {

                if (formula[i] == '+' || formula[i] == '-' || formula[i] == '*') {
                    
                    not_number = true;

                    for (auto c1 : search(formula.substr(0, i))) {

                        for (auto c2 : search(formula.substr(i+1, formula.size() - i - 1))) {

                            int tmp = 0;
                            if (formula[i] == '+')
                                tmp = c1 + c2;
                            else if (formula[i] == '-')
                                tmp = c1 - c2;
                            else if (formula[i] == '*')
                                tmp = c1 * c2;

                            ans.push_back(tmp);
                        }
                    }
                    num = 0;
                } else {
                    num = num * 10 + int(formula[i] - '0');
                }
            }

            if (!not_number)
                ans.push_back(num);

            dp.insert({formula, ans});
            return ans;
        };

        return search(input);
    }
};