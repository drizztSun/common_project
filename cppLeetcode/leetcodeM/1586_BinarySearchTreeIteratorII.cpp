/*
1586. Binary Search Tree Iterator II

Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST):

. BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
. boolean hasNext() Returns true if there exists a number in the traversal to the right of the pointer, otherwise returns false.
. int next() Moves the pointer to the right, then returns the number at the pointer.
. boolean hasPrev() Returns true if there exists a number in the traversal to the left of the pointer, otherwise returns false.
. int prev() Moves the pointer to the left, then returns the number at the pointer.

Notice that by initializing the pointer to a non-existent smallest number, the first call to next() will return the smallest element in the BST.

You may assume that next() and prev() calls will always be valid. That is, there will be at least a next/previous number in the in-order traversal when next()/prev() is called.

 

Example 1:



Input
["BSTIterator", "next", "next", "prev", "next", "hasNext", "next", "next", "next", "hasNext", "hasPrev", "prev", "prev"]
[[[7, 3, 15, null, null, 9, 20]], [null], [null], [null], [null], [null], [null], [null], [null], [null], [null], [null], [null]]
Output
[null, 3, 7, 3, 7, true, 9, 15, 20, false, true, 15, 9]

Explanation
// The underlined element is where the pointer currently is.
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]); // state is   [3, 7, 9, 15, 20]
bSTIterator.next(); // state becomes [3, 7, 9, 15, 20], return 3
bSTIterator.next(); // state becomes [3, 7, 9, 15, 20], return 7
bSTIterator.prev(); // state becomes [3, 7, 9, 15, 20], return 3
bSTIterator.next(); // state becomes [3, 7, 9, 15, 20], return 7
bSTIterator.hasNext(); // return true
bSTIterator.next(); // state becomes [3, 7, 9, 15, 20], return 9
bSTIterator.next(); // state becomes [3, 7, 9, 15, 20], return 15
bSTIterator.next(); // state becomes [3, 7, 9, 15, 20], return 20
bSTIterator.hasNext(); // return false
bSTIterator.hasPrev(); // return true
bSTIterator.prev(); // state becomes [3, 7, 9, 15, 20], return 15
bSTIterator.prev(); // state becomes [3, 7, 9, 15, 20], return 9
 

Constraints:

The number of nodes in the tree is in the range [1, 105].
0 <= Node.val <= 106
At most 105 calls will be made to hasNext, next, hasPrev, and prev.
 

Follow up: Could you solve the problem without precalculating the values of the tree?

*/
#include <vector>
#include <stack>

using std::stack;
using std::vector;

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
class BSTIterator {

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

public:

    int cur;
    vector<int> buff;

    BSTIterator(TreeNode* root) {
        
        stack<TreeNode*> st;
        TreeNode* p = root;

        while (!st.empty() || p) {
            if (p) {
                st.push(p);
                p = p->left;
            } else {
                p = st.top();
                buff.push_back(p->val);
                st.pop();
                p = p->right;
            }
        }

        cur = -1;
    }
    
    bool hasNext() {
        return cur != buff.size()-1;
    }
    
    int next() {
        return buff[++cur];
    }
    
    bool hasPrev() {
        return cur > 0;
    }
    
    int prev() {
        return buff[--cur];
    }
};

/*
    1586.Binary-Search-Tree-Iterator-II
    本题的本质是 094.Binary Tree Inorder Traversal. 用栈可以实现单步的next()操作。具体的方法是维护一个栈(nexts)存放未来需要访问的节点。其中马上能访问的下一个节点next()就在这个栈顶。
    当我们需要调用next()时就只需要读取栈顶的元素，然后将其弹出。接下来，为了给之后的next()做准备，然后我们需要走到刚才访问的节点的右节点，然后一路向左把所有节点都压入栈内。此番操作之后，此时的栈顶元素保证就是next greater element.

    那么如何实现prev()呢？其实很"无赖"，只要把曾经访问过的所有节点都存入一个叫visited的栈里面。于是每次调用next()之后，visited就会新增一个元素。
    注意，我们调用prev()的时候，将visited的栈顶元素弹出，以便返回里面的“次”栈顶元素（因为visited的栈顶是刚访问过的，而prev()需要返回的是再早一次访问过的）。

    那么我们怎么处理和利用visited的栈顶元素呢，白白扔掉吗？这里有个非常巧妙的处理方法：将visited的栈顶元素取出来直接放入nexts里面。这样如果下一次调用next()，就直接从nexts里面取栈顶元素就行了。
    但是我们需要将这类已经访问过的、再次塞回nexts的节点做个标记以示区别，因为如果调用next()读取的是这些值的话我们并不需要额外的“访问右节点再一路向左”的操作。
    可以想象，你连续调用了多少次prev()，那么就有多少个这样的已经访问过的节点被“暂存”在了nexts里面，如果你的next()读取的是这类的节点，那么他们一定全部在nexts的栈顶等着你。

    另外一个细节是，hasPrev()的条件是visited.size()>1，因为返回的是visited的次栈顶元素。

*/
class BSTIterator {

    stack<std::pair<TreeNode*, bool>>nexts;
    stack<TreeNode*>visited;

public:
    BSTIterator(TreeNode* root) {

        while (root) {
            nexts.push({root,true});
            root = root->left;
        }
    }
    
    bool hasNext() 
    {
        return !nexts.empty();        
    }
    
    int next() 
    {
        auto [node, flag] = nexts.top();
        nexts.pop();
        
        if (flag == 1)
        {
            TreeNode* p = node->right;
            while (p)
            {
                nexts.push({p, true});
                p = p->left;
            }
        }
            
        visited.push(node);
        return node->val;
    }
    
    bool hasPrev() 
    {
        return visited.size() > 1;
    }
    
    int prev() 
    {
        nexts.push({visited.top(), false});
        visited.pop();
        
        return visited.top()->val;
    }
};
