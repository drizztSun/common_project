/*
536. Construct Binary Tree from String


You need to construct a binary tree from a string consisting of parenthesis and integers.

The whole input represents a binary tree. It contains an integer followed by zero, one or two pairs of parenthesis. 

The integer represents the root's value and a pair of parenthesis contains a child binary tree with the same structure.

You always start to construct the left child node of the parent first if it exists.

 

Example 1:


Input: s = "4(2(3)(1))(6(5))"
Output: [4,2,6,3,1,5]
Example 2:

Input: s = "4(2(3)(1))(6(5)(7))"
Output: [4,2,6,3,1,5,7]
Example 3:

Input: s = "-4(2(3)(1))(6(5)(7))"
Output: [-4,2,6,3,1,5,7]
 

Constraints:

0 <= s.length <= 3 * 104
s consists of digits, '(', ')', and '-' only.
*/
#include <stack>

using std::stack;


class BuildBinaryTree {

    /*
        536.Construct-Binary-Tree-from-String
        典型的栈的应用。创建 stack<TreeNode*>Stack.

        遇到左括号就把current入栈；

        遇到右括号就退栈一个元素作为current的父节点：根据规则，current优先作为左子节点，如果父节点已经有左子节点，则current作为它的右子节点。然后更新current为此时的那个父节点。

        遇到数字串，则开辟新节点current并赋值。注意负号。
    */

public:

    TreeNode* doit_stack(string s) 
    {
        if (s=="") return NULL;
        
        stack<TreeNode*>Stack;
        TreeNode* current=NULL;
        
        for (int i=0; i<s.size(); i++)
        {
            if (s[i]=='(')
            {
                Stack.push(current);
                current=NULL;
            }
            else if (s[i]==')')
            {
                if (Stack.top()->left==NULL)
                    Stack.top()->left=current;
                else
                    Stack.top()->right=current;
                current = Stack.top();
                Stack.pop();
            }
            else
            {
                int i0=i;
                while (s[i]!='(' && s[i]!=')') i++;
                current = new TreeNode(stoi(s.substr(i0,i-i0)));
                i--;
            }
        }
        
        return current;
    }


    TreeNode* str2tree(string s) {
        
        std::function<TreeNode*(int&)> dfs = [&](int& pos) -> TreeNode*{
            
            int i = pos;
            while (i < s.length() && s[i] != '(' && s[i] != ')') i++;
            int num = std::stoi(s.substr(pos, i - pos));
            
            TreeNode* node = new TreeNode(num);
            
            if (s[i] == ')') {
                pos = i+1;
                return node;
            }
            
            i++;
            node->left = dfs(i);
            
            if (i == s.length()) {
                pos = i;
                return node;
            }
                
            node->right = dfs(i);
            pos = i;
            return node;
        };
        
        int pos = 0;
        return dfs(pos);
    }
};