/*
 1106. Parsing A Boolean Expression
 
 Return the result of evaluating a given boolean expression, represented as a string.

 An expression can either be:

 "t", evaluating to True;
 "f", evaluating to False;
 "!(expr)", evaluating to the logical NOT of the inner expression expr;
 "&(expr1,expr2,...)", evaluating to the logical AND of 2 or more inner expressions expr1, expr2, ...;
 "|(expr1,expr2,...)", evaluating to the logical OR of 2 or more inner expressions expr1, expr2, ...


 Example 1:

 Input: expression = "!(f)"
 Output: true
 Example 2:

 Input: expression = "|(f,t)"
 Output: true
 Example 3:

 Input: expression = "&(t,f)"
 Output: false
 Example 4:

 Input: expression = "|(&(t,f,t),!(t))"
 Output: false


 Constraints:

 1 <= expression.length <= 20000
 expression[i] consists of characters in {'(', ')', '&', '|', '!', 't', 'f', ','}.
 expression is a valid expression representing a boolean, as given in the description.
 
 
 */
#include <stdio.h>

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using std::vector;
using std::string;
using std::unordered_map;


class ParseBoolExpr {
public:
    
    bool doit_(string expression) {
        
        vector<char> buff;
        
        auto And = [](vector<bool>& c) {
            return std::all_of(begin(c), end(c), [](bool a){ return a; });
        };
        
        auto Or = [](vector<bool>& c) {
            return std::any_of(begin(c), end(c), [](bool a){return a; });
        };
        
        auto Not = [](vector<bool>& c) {
            return !c[0];
        };
        
        unordered_map<char, std::function<bool(vector<bool>&)>> func;
        func.insert({'&', And});
        func.insert({'|', Or});
        func.insert({'!', Not});
        
        for (auto c : expression) {
            
            if (c == ')') {
                
                vector<bool> tmp;
                while (not buff.empty() && buff.back() != '(') {
                    tmp.push_back(buff.back() == 't' ? true : false);
                    buff.pop_back();
                }
                
                buff.pop_back();
                char c = buff.back();
                buff.pop_back();
                buff.push_back(func[c](tmp) ? 't' : 'f');
                
            } else {
                if (c != ',')
                    buff.push_back(c);
            }
        }
        
        return buff[0] == 't';
    }
    
    bool parseBoolExpr(string expression) {
            if (expression[0] == 't')
                return true;
            if (expression[0] == 'f')
                return false;
        
            char const op = expression[0];
            int const end = expression.length() - 1;  // remove ')'
            int begin = 2;  // remove '#('
            if (op == '!')
                return !parseBoolExpr(expression.substr(begin, end - begin));
            int cnt = 0;  // count of unpaired brakets
            bool ans = (op == '&') ? true : false;\
            for (int pos = begin; pos <= end; ++pos) {
                if (pos == end || (expression[pos] == ',' && cnt == 0)) {
                    bool const b = parseBoolExpr(expression.substr(begin, pos - begin));
                    if (op == '&') {
                        ans = ans && b;
                        if (!ans) return false;
                    } else {
                        ans = ans || b;
                        if (ans) return true;
                    }
                    begin = pos + 1;
                } else if (expression[pos] == '(') {
                    ++cnt;
                } else if (expression[pos] == ')') {
                    --cnt;
                }
            }
            return ans;
        }
};
