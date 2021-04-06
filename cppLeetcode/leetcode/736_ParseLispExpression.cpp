/*

# 736. Parse Lisp Expression

# You are given a string expression representing a Lisp-like expression to return the integer value of.

# The syntax for these expressions is given as follows.

# An expression is either an integer, a let-expression, an add-expression, a mult-expression, or an assigned
# variable. Expressions always evaluate to a single integer.

# (An integer could be positive or negative.)

# A let-expression takes the form (let v1 e1 v2 e2 ... vn en expr), where let is always the string "let",
# then there are 1 or more pairs of alternating variables and expressions, meaning that the first variable v1 is assigned the value of the expression e1, the second variable v2 is assigned the value of the expression e2, and so on sequentially; and then the value of this let-expression is the value of the expression expr.

# An add-expression takes the form (add e1 e2) where add is always the string "add", there are always two expressions e1, e2, and this expression evaluates to the addition of the evaluation of e1 and the evaluation of e2.

# A mult-expression takes the form (mult e1 e2) where mult is always the string "mult", there are always two expressions e1, e2, and this expression evaluates to the multiplication of the evaluation of e1 and the evaluation of e2.

# For the purposes of this question, we will use a smaller subset of variable names. A variable starts with a lowercase letter, then zero or more lowercase letters or digits. Additionally for your convenience, the names "add", "let", or "mult" are protected and will never be used as variable names.

# Finally, there is the concept of scope. When an expression of a variable name is evaluated, within the context of that evaluation, the innermost scope (in terms of parentheses) is checked first for the value of that variable, and then outer scopes are checked sequentially. It is guaranteed that every expression is legal. Please see the examples for more details on scope.


# Evaluation Examples:
# Input: (add 1 2)
# Output: 3

# Input: (mult 3 (add 2 3))
# Output: 15

# Input: (let x 2 (mult x 5))
# Output: 10

# Input: (let x 2 (mult x (let x 3 y 4 (add x y))))
# Output: 14

# Explanation: In the expression (add x y), when checking for the value of the variable x,
# we check from the innermost scope to the outermost in the context of the variable we are trying to evaluate.
# Since x = 3 is found first, the value of x is 3.

# Input: (let x 3 x 2 x)
# Output: 2
# Explanation: Assignment in let statements is processed sequentially.

# Input: (let x 1 y 2 x (add x y) (add x y))
# Output: 5
# Explanation: The first (add x y) evaluates as 3, and is assigned to x.
# The second (add x y) evaluates as 3+2 = 5.

# Input: (let x 2 (add (let x 3 (let x 4 x)) x))
# Output: 6
# Explanation: Even though (let x 4 x) has a deeper scope, it is outside the context
# of the final x in the add-expression.  That final x will equal 2.

# Input: (let a1 3 b2 (add a1 1) b2)
# Output 4
# Explanation: Variable names can contain digits after the first character.


*/

#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>
#include <deque>

using namespace std;


class ParseLispExpression {

	/*
		736.Parse-Lisp-Expression
		本题不难，有足够的耐心就能做出来。对于比较复杂的规则，我们用递归应该比用栈更容易。因为“括号”天然就提示了递归的层次，而且这种expression parse的题型，括号内外的规则都是完全一样的，非常适合用递归。

		注意一下对于let语句，后面会跟着总数为奇数个的参数。除了最后一个参数，第2k个参数一定是一个变量，第2k+1个参数则可以是变量/数值/递归式，这两种类型交替出现。而对于最后一个参数（注意它也是属于2k），
		则同样可能是变量/数值/递归式，这就需要额外进行判断。也就是说，在处理第2k个参数时，如果遇到了数值或者递归式，就意味着这个参数一定最后一个；如果遇到了变量但变量的结尾就是字符串的结尾，也意味着这个参数是最后一个。
	*/
	int evaluate(string expression) 
    {
        unordered_map<string,int>data;
        return helper(expression, 1, expression.size()-2, data);
    }
    
    int helper(string &s, int a, int b, unordered_map<string,int> data)
    {       
        if (a+3<=b && s.substr(a,3)=="add")
        {            
            vector<int>nums;
            
            for (int i=a+4; i<=b; i++)
            {
                if (s[i]=='(')
                {
                    int j = getRightParenthsis(s,i);
                    int next = helper(s,i+1, j-1, data);
                    nums.push_back(next);                    
                    i = j;
                }
                else if (isalpha(s[i]))
                {
                    int j = getVar(s,i);
                    string var = s.substr(i,j-i);
                    nums.push_back(data[var]);
                    i = j-1;
                }
                else if (isdigit(s[i])||s[i]=='-')
                {
                    int j= getDigit(s,i);
                    nums.push_back(stoi(s.substr(i,j-i)));
                    i = j-1;
                }
            }
            return nums[0]+nums[1];
        }
        
        else if (a+4<=b && s.substr(a,4)=="mult")
        {            
            vector<int>nums;
            
            for (int i=a+5; i<=b; i++)
            {
                if (s[i]=='(')
                {
                    int j = getRightParenthsis(s,i);
                    int next = helper(s,i+1, j-1, data);
                    nums.push_back(next);                    
                    i = j;
                }
                else if (isalpha(s[i]))
                {
                    int j = getVar(s,i);
                    string var = s.substr(i,j-i);
                    nums.push_back(data[var]);
                    i = j-1;
                }
                else if (isdigit(s[i])||s[i]=='-')
                {
                    int j= getDigit(s,i);
                    nums.push_back(stoi(s.substr(i,j-i)));
                    i = j-1;
                }
            }
            return nums[0]*nums[1];
        }
        
        else if (a+3<=b && s.substr(a,3)=="let")
        {
            int flag = 0;
            string var;
            int val;
            for (int i=a+4; i<=b; i++)
            {
                if (s[i]==' ') continue;
                                
                if (flag==0)
                {
                    if (s[i]=='(')
                    {
                        return helper(s,i+1,b-1,data);
                    }
                    else if (isdigit(s[i])||s[i]=='-')
                    {
                        int j = getDigit(s,i);
                        return stoi(s.substr(i,j-i));
                    }
                    
                    int j = getVar(s, i);
                    var = s.substr(i, j-i);   
                    i = j-1;
                    
                    if (j==b+1)
                        return data[var];                    
                }
                else 
                {
                    if (s[i] == '(')
                    {
                        int j = getRightParenthsis(s,i);
                        val = helper(s,i+1, j-1, data);
                        i = j;
                    }
                    else if (isdigit(s[i])||s[i]=='-')
                    {
                        int j = getDigit(s,i);
                        val = stoi(s.substr(i,j-i));
                        i = j-1;
                    }
                    else if (isalpha(s[i]))
                    {
                        int j = getVar(s,i);
                        val = data[s.substr(i,j-i)];
                        i = j-1;
                    }
                    data[var] = val;
                }
                                                
                flag = 1-flag;
                
            }
        }
        
        return -1;
        
        
    }
    
    int getVar(string &s, int i)
    {
        while (isdigit(s[i])||isalpha(s[i]))
            i++;
        return i;
    }
    
    int getDigit(string &s, int i)
    {
        while (isdigit(s[i])||s[i]=='-')
            i++;
        return i;
    }
    
    int getRightParenthsis(string &s, int i)
    {
        int level = 1;
        i++;
        while (level>0)
        {
                        
            level+=(s[i]=='(');                        
            level-=(s[i]==')');
            if (level==0)
                break;
            i++;
        }        
        return i;
    }


public:


	typedef unordered_map<string, string> VARS_CONTEXT;


	auto GetVal(VARS_CONTEXT& vargs, const string& key){
		if (vargs.find(key) == vargs.end()) {
			return key;
		}

		return vargs[key];
	};


	auto Evaluate(VARS_CONTEXT& vargs, const vector<string>& statement) {

		if (statement[0] == "mult" || statement[0] == "add") {
			int a = stol(GetVal(vargs, statement[1])), b = stol(GetVal(vargs, statement[2]));
			return to_string(statement[0] == "mult" ? a * b : a + b);
		}
		else {

			for (int i = 1; i < statement.size() - 1; i += 2) {
				if (!statement[i + 1].empty())
					vargs[statement[i]] = GetVal(vargs, statement[i + 1]);
			}

			return GetVal(vargs, statement.back());
		}
	};

	int evaluate(string expression) {

		typedef pair<vector<string>, VARS_CONTEXT> CONTEXT;
		
		vector<string> tokens(1, string(""));
		VARS_CONTEXT vargs;
		stack<CONTEXT> st;

		for (auto c : expression) {

			if (c == '(') {
				if (tokens[0] == "let")
					Evaluate(vargs, tokens);

				st.push(make_pair(tokens, vargs));
				tokens = vector<string>(1, string(""));
			}
			else if (c == ')') {
				auto vals = Evaluate(vargs, tokens);
				CONTEXT context = st.top();
				st.pop();

				vargs = context.second;
				tokens = context.first;

				*tokens.rbegin() += vals;
			}
			else if (c == ' ') {
				tokens.push_back("");
			}
			else {
				*tokens.rbegin() += c;
			}
		}

		return stol(tokens[0]);
	}
};






class Solution {
public:
	int evaluate(string expression) {
		scopes_.clear();
		int pos = 0;
		return eval(expression, pos);
	}
private:
	int eval(const string& s, int& pos) {
		scopes_.push_front(unordered_map<string, int>());
		int value = 0; // The return value of current expr        
		if (s[pos] == '(') ++pos;

		// command, variable or number
		const string token = getToken(s, pos);

		if (token == "add") {
			int v1 = eval(s, ++pos);
			int v2 = eval(s, ++pos);
			value = v1 + v2;
		}
		else if (token == "mult") {
			int v1 = eval(s, ++pos);
			int v2 = eval(s, ++pos);
			value = v1 * v2;
		}
		else if (token == "let") {
			string var;
			// expecting " var1 exp1 var2 exp2 ... last_expr)"
			while (s[pos] != ')') {
				++pos;
				// Must be last_expr
				if (s[pos] == '(') {
					value = eval(s, ++pos);
					break;
				}
				// Get a token, could be "x" or "-12" for last_expr
				var = getToken(s, pos);
				// End of let, var is last_expr
				if (s[pos] == ')') {
					if (isalpha(var[0]))
						value = getValue(var);
					else
						value = stoi(var);
					break;
				}
				// x -12 -> set x to -12 and store in the current scope and take it as the current return value
				value = scopes_.front()[var] = eval(s, ++pos);
			}
		}
		else if (isalpha(token[0])) {
			value = getValue(token); // symbol
		}
		else {
			value = std::stoi(token); // number
		}
		if (s[pos] == ')') ++pos;
		scopes_.pop_front();
		return value;
	}

	int getValue(const string& symbol) {
		for (const auto& scope : scopes_)
			if (scope.count(symbol)) return scope.at(symbol);
		return 0;
	}

	// Get a token from current pos.
	// "let x" -> "let"
	// "-12 (add x y)" -> "-12"
	string getToken(const string& s, int& pos) {
		string token;
		while (pos < s.length()) {
			if (s[pos] == ')' || s[pos] == ' ') break;
			token += s[pos++];
		}
		return token;
	}

	deque<unordered_map<string, int>> scopes_;
};



static int x = []() { std::ios::sync_with_stdio(false); std::cin.tie(NULL); return 0; }();
class Solution1 {

	int varVal(string varName, list<unordered_map<string, int>>&contexts) const {
		for (auto it = contexts.rbegin(); it != contexts.rend(); ++it) {
			auto itmap = it->find(varName);
			if (itmap != it->end()) { return itmap->second; }
		}
		return 0;
	};

	char*eval(char*ps, char*pe, int&val, list<unordered_map<string, int>>&contexts) const {
		val = 0;
		if (ps < pe) {
			if (*ps == '(') {
				++ps;
				while (ps < pe && *ps == ' ') { ++ps; }
				contexts.push_back(unordered_map<string, int>());
				ps = eval(ps, pe, val, contexts);
				contexts.pop_back();
				while (ps < pe && *ps == ' ') { ++ps; }
				if (ps < pe && *ps == ')') { ++ps; }
			}
			else if (isdigit(*ps) || *ps == '-') {
				int mult = 1;
				if (*ps == '-') { mult = -1; ++ps; }
				val = 0;
				while (ps < pe && isdigit(*ps)) { val = val * 10 + *ps++ - '0'; }
				val *= mult;
			}
			else {
				string varOrCmdName;
				while (ps < pe && isalnum(*ps)) { 
					varOrCmdName.push_back(*ps++); 
				}

				while (ps < pe && *ps == ' ') { 
					++ps; 
				}

				if (varOrCmdName == "let") {
					while (true) {
						string varName;
						if (isalpha(*ps)) {
							while (ps < pe && isalnum(*ps)) { varName.push_back(*ps++); }
							while (ps < pe && *ps == ' ') { ++ps; }
							if (ps < pe && *ps == ')') {
								val = varVal(varName, contexts);
								break;
							}
							else {
								int valVar;
								ps = eval(ps, pe, valVar, contexts);
								contexts.back()[varName] = valVar;
							}
						}
						else {
							ps = eval(ps, pe, val, contexts);
							break;
						}
					}
				}
				else if (varOrCmdName == "add") {

					int val1, val2;
					ps = eval(ps, pe, val1, contexts);
					ps = eval(ps, pe, val2, contexts);
					val = val1 + val2;
				}
				else if (varOrCmdName == "mult") {

					int val1, val2;
					ps = eval(ps, pe, val1, contexts);
					ps = eval(ps, pe, val2, contexts);
					val = val1 * val2;
				}
				else { 
					val = varVal(varOrCmdName, contexts); 
				}
			}
		}

		while (ps < pe && *ps == ' ') {
			++ps; 
		}

		return ps;
	};

public:
	int evaluate(string&expression) const 
	{
		int len = (int)expression.length();
		if (len) {

			list<unordered_map<string, int>>contexts;
			char *ps = &expression[0], *pe = ps + len;
			int val;
			eval(ps, pe, val, contexts);
			
			return val;
		}

		return 0;
	};
};




void Test_736_ParseLispExpression() {

	int res = 0;

	res = ParseLispExpression().evaluate("(add 1 2)");

	res = ParseLispExpression().evaluate("(mult 3 (add 2 3))"); 

	res = ParseLispExpression().evaluate("(let x 2 (mult x 5))"); 

	res = ParseLispExpression().evaluate("(let x 2 (mult x (let x 3 y 4 (add x y))))");

	res = ParseLispExpression().evaluate("(let x 3 x 2 x)");

	res = ParseLispExpression().evaluate("(let x 1 y 2 x (add x y) (add x y))");

	res = ParseLispExpression().evaluate("(let x 2 (add (let x 3 (let x 4 x)) x))");

	res = ParseLispExpression().evaluate("(let a1 3 b2 (add a1 1) b2)");

	return;
}
