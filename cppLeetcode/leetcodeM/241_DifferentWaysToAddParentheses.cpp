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
#include <funtional>

using std::unordered_map;
using std::vector;
using std::string;


class DiffWaysToCompute {

    /*
                241.Different-Ways-to-Add-Parentheses
        此题只要想到,任何多项式运算最终可以化简为最后的双目运算.只要确定这个双目运算符的位置,其前后两端用递归处理就行了.
    */
    vector<int> diffWaysToCompute(string input) 
    {
        vector<int>results;
        vector<int>vals1;
        vector<int>vals2;
        for (int i=0; i<input.size(); i++)
        {
            if (input[i]!='+' && input[i]!='-' && input[i]!='*')
                continue;
            vals1 = diffWaysToCompute(input.substr(0,i));
            vals2 = diffWaysToCompute(input.substr(i+1));
            for (int a : vals1)
                for (int b: vals2)
                {
                    if (input[i]=='+') results.push_back(a+b);
                    else if (input[i]=='-') results.push_back(a-b);
                    else if (input[i]=='*') results.push_back(a*b);
                }
        }
        if (results.empty())
            results.push_back(stoi(input));
        return results;
    }


public:
    
    vector<int> diffWaysToCompute(string expression) {
        
        std::function<vector<int>(int, int)> dfs = [&](int i, int j) {
          
            vector<int> ans;
            
            for (int s = i; s < j; s++) {
                
                if (!isdigit(expression[s])) {
                    
                    vector<int> tmp1 = dfs(i, s), tmp2 = dfs(s+1, j);
                    
                    for (auto t1: tmp1)
                        for (auto t2: tmp2) {
                            
                            if (expression[s] == '+')
                                ans.push_back(t1 + t2);
                            else if (expression[s] == '-')
                                ans.push_back(t1 - t2);
                            else if (expression[s] == '*')
                                ans.push_back(t1 * t2);
                        }
                }
            }
            
            if (ans.empty()) 
                ans.push_back(std::atoi(expression.substr(i, j-i).c_str()));
            
            return ans;
        };
        
        return dfs(0, expression.length());
    }

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