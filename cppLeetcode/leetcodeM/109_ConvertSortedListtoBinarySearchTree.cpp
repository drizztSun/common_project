/*
109. Convert Sorted List to Binary Search Tree

Given the head of a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

 

Example 1:


Input: head = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: One possible answer is [0,-3,9,-10,null,5], which represents the shown height balanced BST.
Example 2:

Input: head = []
Output: []
Example 3:

Input: head = [0]
Output: [0]
Example 4:

Input: head = [1,3]
Output: [3,1]
 

Constraints:

The number of nodes in head is in the range [0, 2 * 104].
-10^5 <= Node.val <= 10^5

*/

#include <functional>


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
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
class SortedListToBST {

    
    // Definition for singly-linked list.
    struct ListNode {
         int val;
         ListNode *next;
         ListNode() : val(0), next(nullptr) {}
         ListNode(int x) : val(x), next(nullptr) {}
         ListNode(int x, ListNode *next) : val(x), next(next) {}
    };
    
    
    // Definition for a binary tree node.
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        109.Convert-Sorted-List-to-Binary-Search-Tree
        用快慢指针fast/slow的方法定位到链表的中点，即为根结点，然后把中点前的ListNode切断。这样根结点的左子树即可递归调用 sortedListToBST(head)，右子树即可递归调用 sortedListToBST(slow-next).

        细节：

        1. 为了能把中点前的ListNode切断，需要设置一个temp来保存慢指针的旧值。
        2. 注意递归的边界条件。首先 (head==NULL) 必然需要单独处理；其次 (head->next==NULL)也需要单独处理；最后 (head->next->next==NULL) 也需要单独处理，因为在这种情况下，快指针是无法前进的，无法定位链表的中点。
    */

    TreeNode* sortedListToBST(ListNode* head) 
    {
        if (head==NULL) return NULL;
        
        if (head->next==NULL)
        {
            TreeNode* root = new TreeNode(head->val);
            return root;
        }
        
        if (head->next->next==NULL)
        {
            TreeNode* root = new TreeNode(head->val);
            root->right = new TreeNode(head->next->val);
            return root;
        }
        
        ListNode* fast=head;
        ListNode* slow=head;
        ListNode* temp;
        while (fast->next!=NULL && fast->next->next!=NULL)
        {
            fast=fast->next->next;
            temp=slow;
            slow=slow->next;
        }
        temp->next=NULL;
        
        TreeNode* root=new TreeNode(slow->val);
        root->left=sortedListToBST(head);
        root->right=sortedListToBST(slow->next);
        
        return root;
        
    }


public:

    TreeNode* doit_link(ListNode* head) {

        int size = 0;
        ListNode* cur = head;
        while (cur) {
            size++;
            cur = cur->next;
        }

        std::function<TreeNode*(int, int)> dfs = [&](int l, int r) -> TreeNode* {

            if (l > r) return nullptr;

            int mid = (l + r) / 2;

            TreeNode* pleft = dfs(l, mid-1);

            TreeNode* center = new TreeNode(head->val);
            head = head->next;

            TreeNode* pright = dfs(mid+1, r);

            center->left = pleft;
            center->right = pright;

            return center;
        };
        
        return dfs(0, size-1);
    }
};