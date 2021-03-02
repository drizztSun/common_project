/*
173. Binary Search Tree Iterator


Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST):

BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
boolean hasNext() Returns true if there exists a number in the traversal to the right of the pointer, otherwise returns false.
int next() Moves the pointer to the right, then returns the number at the pointer.
Notice that by initializing the pointer to a non-existent smallest number, the first call to next() will return the smallest element in the BST.

You may assume that next() calls will always be valid. That is, there will be at least a next number in the in-order traversal when next() is called.

 

Example 1:


Input
["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
[[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
Output
[null, 3, 7, true, 9, true, 15, true, 20, false]

Explanation
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
bSTIterator.next();    // return 3
bSTIterator.next();    // return 7
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 9
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 15
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 20
bSTIterator.hasNext(); // return False
 

Constraints:

The number of nodes in the tree is in the range [1, 105].
0 <= Node.val <= 106
At most 105 calls will be made to hasNext, and next.
 

Follow up:

Could you implement next() and hasNext() to run in average O(1) time and use O(h) memory, where h is the height of the tree?
*/

#include <stack>

using std::stack;



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

/*
    173.Binary-Search-Tree-Iterator
    此题本质上是用迭代法（栈实现）来进行BST的中序遍历（也就是从小到大）。所以是94题的衍生。

    所以该类的data member需要一个stackStack. 具体要点如下：

    初始化时，就将栈塞满到最小节点。（不断将左节点推入栈中）
    while (root!=NULL)
    {
        Stack.push(root);
        root=root->left;
    }
    只要栈非空，就说明hasNext是true。
    输出next即输出当前栈顶元素。然后栈顶元素退栈，加入该元素的右节点并追溯到最底层。
    TreeNode* node=Stack.top();
    int result=node->val; // 当前栈顶元素
    Stack.pop();  // 退栈
    node=node->right;  // 加入新的元素直至到当前最小值。
    while (node!=NULL)
    {
        Stack.push(node);
        node=node->left;
    }

*/
class TreeNode;

class BSTIterator {

    stack<TreeNode*>Stack;
    
public:
    BSTIterator(TreeNode *root) 
    {
        while (root!=NULL)
        {
            Stack.push(root);
            root = root->left;
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() 
    {
        return !Stack.empty();
    }

    /** @return the next smallest number */
    int next() 
    {
        TreeNode* node = Stack.top();
        int result = node->val;
        Stack.pop();
        node = node->right;
        while (node!=NULL)
        {
            Stack.push(node);
            node = node->left;
        }
        
        return result;
        
    }
};