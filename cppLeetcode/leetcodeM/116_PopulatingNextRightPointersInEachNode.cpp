/*
116. Populating Next Right Pointers in Each Node

You are given a perfect binary tree where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

 

Follow up:

You may only use constant extra space.
Recursive approach is fine, you may assume implicit stack space does not count as extra space for this problem.
 

Example 1:



Input: root = [1,2,3,4,5,6,7]
Output: [1,#,2,3,#,4,5,6,7,#]
Explanation: Given the above perfect binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B. The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.
 

Constraints:

The number of nodes in the given tree is less than 4096.
-1000 <= node.val <= 1000
*/

#include <functional>

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

#include <queue>
using std::queue;

class PopulatingNextRightPointers {

    class Node {
    public:
        int val;
        Node* left;
        Node* right;
        Node* next;

        Node() : val(0), left(NULL), right(NULL), next(NULL) {}

        Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

        Node(int _val, Node* _left, Node* _right, Node* _next)
            : val(_val), left(_left), right(_right), next(_next) {}
    };


    Node* connect_best(Node* root) {
        
        Node *cur = root, *leftmost = NULL, *last = NULL;
        
        auto connect = [&](Node* child) {
            
            if (!child) return;
            
            if (!leftmost) {
                leftmost = child;
                last = child;
            } else {
                last->next = child;
                last = child;
            }
        };
        
        
        while (cur) {
            
            leftmost = NULL;
            last = NULL;
            
            
            while (cur) {
                
                connect(cur->left);
                connect(cur->right);
                
                cur = cur->next;
            }
            
            cur = leftmost;
        }
        
        return root;
    }

public:

    /*
        Follow up:
        You may only use constant extra space.
        Recursive approach is fine, you may assume implicit stack space does not count as extra space for this problem.
    */
    Node* connect_best(Node* root) {
        
        std::function<void(Node*)> dfs = [&](Node* p) {
            
            if (!p) return;
            
            if (p->left) p->left->next = p->right;
            if (p->right) p->right->next = p->next ? p->next->left : NULL;
            
            dfs(p->left);
            dfs(p->right);
        };
        
        dfs(root);
        return root;
    }

    Node* connect(Node* root) {

        if (!root) return root;

        queue<Node*> buf;
        buf.push(root);


        while (!buf.empty()) {

            int size = buf.size();
            Node* last = nullptr;

            while(size--) {

                Node* cur = buf.front();
                buf.pop();

                if (last) last->next = cur;

                if (cur->left) buf.push(cur->left);
                if (cur->right) buf.push(cur->right);

                last = cur;
            }

        }

        return root;
    }
};