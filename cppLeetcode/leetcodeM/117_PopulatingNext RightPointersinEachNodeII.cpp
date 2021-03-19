/*
117. Populating Next Right Pointers in Each Node II

Given a binary tree

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



Input: root = [1,2,3,4,5,null,7]
Output: [1,#,2,3,#,4,5,7,#]
Explanation: Given the above binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B. 
The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.
 

Constraints:

The number of nodes in the given tree is less than 6000.
-100 <= node.val <= 100

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

class PopulatingNextRightPointersII {



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

    /*
        117.Populating-Next-Right-Pointers-in-Each-Node-II
        此题的难点在于如何只用constant extra space实现树的level order traversal。对于一般的树结构,这是无法做到的,但本题的特点是:这里定义的TreeNode的数据结构允许一个横向的链接next,为我们的level-order-tranversal提供了便利.

        我们定义三个指针now,head,tail。初始状态now=root; head=tail=NULL。Now是用来指向正在遍历的当前层的节点，head和tail指向下一层的头节点和尾节点。

        我们在横向遍历now指针的时候，考察now->left和now->right，根据情况,不断更新head和tail. head只有一种情况需要更新,那就是如果head==NULL的话.对于tail的更新原则,永远就是让tail->next指向now的子节点(也就是引入新的tail),然后自己也右移一位。

        当now==NULL时，说明当前层已经遍历完毕，然后怎么办呢?精彩的地方来了!就让now指向head即可，因为head就是下一层的头指针.然后将head和tail清空（指向NULL）,就重复了上面一段的操作.
    */
    void connect(Node *root) 
    {
        Node* now=root;
        Node* head=NULL;
        Node* tail=NULL;
        
        while (now!=NULL)
        {
            if (now->left!=NULL)
            {
                if (head==NULL) head=now->left;
                if (tail==NULL) 
                    tail=now->left;
                else
                {
                    tail->next = now->left;
                    tail=tail->next;
                }
            }
            if (now->right!=NULL)
            {
                if (head==NULL) head=now->right;
                if (tail==NULL) 
                    tail=now->right;
                else
                {
                    tail->next = now->right;
                    tail=tail->next;
                }
            }            
            now=now->next;
            if (now==NULL)
            {
                now=head;
                head=NULL;
                tail=NULL;
            }
        }
    }


public:

    Node* connect(Node* root) {
        
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
    
    Node * connect(Node *root) 
    {
        Node *prev, *leftmost;
        
        if (root == NULL) {
            return root;
        }
        
        auto processChild = [&](Node* childNode) {
        
            if (childNode != NULL) {

                // If the "prev" pointer is alread set i.e. if we
                // already found atleast one node on the next level,
                // setup its next pointer
                if (prev != NULL) {
                    prev->next = childNode;

                } else {

                    // Else it means this child node is the first node
                    // we have encountered on the next level, so, we
                    // set the leftmost pointer
                    leftmost = childNode;
                }    

                prev = childNode; 
            }
        };
        
        // The root node is the only node on the first level
        // and hence its the leftmost node for that level
        leftmost = root;
        
        // Variable to keep track of leading node on the "current" level
        Node *curr = leftmost;
        
        // We have no idea about the structure of the tree,
        // so, we keep going until we do find the last level.
        // the nodes on the last level won't have any children
        while (leftmost != NULL) {
            
            // "prev" tracks the latest node on the "next" level
            // while "curr" tracks the latest node on the current
            // level.
            prev = NULL;
            curr = leftmost;
            
            // We reset this so that we can re-assign it to the leftmost
            // node of the next level. Also, if there isn't one, this
            // would help break us out of the outermost loop.
            leftmost = NULL;
            
            // Iterate on the nodes in the current level using
            // the next pointers already established.
            while (curr != NULL) {
                
                // Process both the children and update the prev
                // and leftmost pointers as necessary.
                processChild(curr->left);
                processChild(curr->right);
                
                // Move onto the next node.
                curr = curr->next;
            }
        }
                
        return root;
    }
};