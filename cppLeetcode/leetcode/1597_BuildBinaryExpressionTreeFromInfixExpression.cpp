/*
1597. Build Binary Expression Tree From Infix Expression

A binary expression tree is a kind of binary tree used to represent arithmetic expressions. Each node of a binary expression tree has either zero or two children. Leaf nodes (nodes with 0 children) correspond to operands (numbers), and internal nodes (nodes with 2 children) correspond to the operators '+' (addition), '-' (subtraction), '*' (multiplication), and '/' (division).

For each internal node with operator o, the infix expression that it represents is (A o B), where A is the expression the left subtree represents and B is the expression the right subtree represents.

You are given a string s, an infix expression containing operands, the operators described above, and parentheses '(' and ')'.

Return any valid binary expression tree, which its in-order traversal reproduces s after omitting the parenthesis from it (see examples below).

Please note that order of operations applies in s. That is, expressions in parentheses are evaluated first, and multiplication and division happen before addition and subtraction.

Operands must also appear in the same order in both s and the in-order traversal of the tree.

 

Example 1:


Input: s = "3*4-2*5"
Output: [-,*,*,3,4,2,5]
Explanation: The tree above is the only valid tree whose inorder traversal produces s.
Example 2:


Input: s = "2-3/(5*2)+1"
Output: [+,-,1,2,/,null,null,null,null,3,*,null,null,5,2]
Explanation: The inorder traversal of the tree above is 2-3/5*2+1 which is the same as s without the parenthesis. The tree also produces the correct result and its operands are in the same order as they appear in s.
The tree below is also a valid binary expression tree with the same inorder traversal as s, but it not a valid answer because it does not evaluate to the same value.

The third tree below is also not valid. Although it produces the same result and is equivalent to the above trees, its inorder traversal does not produce s and its operands are not in the same order as s.

Example 3:

Input: s = "1+2+3+4+5"
Output: [+,+,5,+,4,null,null,+,3,null,null,1,2]
Explanation: The tree [+,+,5,+,+,null,null,1,2,3,4] is also one of many other valid trees.
 

Constraints:

1 <= s.length <= 1000
s consists of digits and the characters '+', '-', '*', and '/'.
Operands in s are exactly 1 digit.
It is guaranteed that s is a valid expression.
*/

#include <vector>
#include <string>

using std::string;
using std::vector;


/**
 * Definition for a binary tree node.
 * struct Node {
 *     char val;
 *     Node *left;
 *     Node *right;
 *     Node() : val(' '), left(nullptr), right(nullptr) {}
 *     Node(char x) : val(x), left(nullptr), right(nullptr) {}
 *     Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {

    // Definition for a binary tree node.
    struct Node {
      char val;
      Node *left;
      Node *right;
      Node() : val(' '), left(nullptr), right(nullptr) {}
      Node(char x) : val(x), left(nullptr), right(nullptr) {}
      Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
    };

    /*
        1597.Build-Binary-Expression-Tree-From-Infix-Expression
        基本的思想就是递归处理。

        模拟运算的顺序，最high level必然是加减法。所以我们从后往前搜寻第一个不在括号内的加号或者减号。然后以该运算符为根节点，将整个字符串就分为前后两部分，分别递归生成它的左右节点。
        
        那么如何避免搜到包含在括号内的加减号呢？方法很显然，我们遇到第一个最外层的右括号的时候，就开启括号匹配模式。用一个计数器来统计未匹配的右括号，直至计数器恰好变为0，那么说明这一对最外层括号找齐了，那么从此之后恢复寻找第一个加减号的模式。

        以上的one pass结束之后如果没有进入下一层，说明表达式中没有括号外的加减号。那么重复上述的过程，目标改为从后往前搜寻第一个不在括号内的乘号或者除号。然后以该运算符为根节点，将整个字符串就分为前后两部分，分别递归生成它的左右节点。

        如果上面的one pass结束之后仍然没有进入下一层，那么就说明这个表达式本身就是被一对括号包裹着。那么我们将这对括号脱去，递归处理里面的字符串就行了。

        最后的边界条件就是表达式的长度为1，说明就是一个数字，那么直接以其建立叶子节点，返回即可。
    */
    Node* expTree(string s) 
    {
        if (s.size()==1)
        {
            Node* root = new Node(s[0]);
            return root;
        }
        
        for (int i=s.size()-1; i>=0; i--)
        {
            if (s[i]=='+' || s[i]=='-')
            {
                Node* root = new Node(s[i]);
                root->right = expTree(s.substr(i+1));
                root->left = expTree(s.substr(0,i));                
                return root;
            }            
            else if (s[i]==')')
            {
                int j = i-1;
                int count = 1;
                while (j>=0 && count>0)
                {
                    if (s[j]==')')
                        count++;
                    else if (s[j]=='(')
                        count--;
                    j--;
                }
                i = j+1;
            }
        }
        
        for (int i=s.size()-1; i>=0; i--)
        {
            if (s[i]=='*' || s[i]=='/')
            {
                Node* root = new Node(s[i]);
                root->right = expTree(s.substr(i+1));
                root->left = expTree(s.substr(0,i));                
                return root;
            }            
            else if (s[i]==')')
            {
                int j = i-1;
                int count = 1;
                while (j>=0 && count>0)
                {
                    if (s[j]==')')
                        count++;
                    else if (s[j]=='(')
                        count--;
                    j--;
                }
                i = j+1;
            }
        }
        
        if (s[0]=='(' && s.back()==')')
            return expTree(s.substr(1, s.size()-2));
        
        return NULL;
    }
};