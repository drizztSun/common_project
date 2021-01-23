/*
1721. Swapping Nodes in a Linked List


You are given the head of a linked list, and an integer k.

Return the head of the linked list after swapping the values of the kth node from the beginning and the kth node from the end (the list is 1-indexed).

 

Example 1:


Input: head = [1,2,3,4,5], k = 2
Output: [1,4,3,2,5]
Example 2:

Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
Output: [7,9,6,6,8,7,3,0,9,5]
Example 3:

Input: head = [1], k = 1
Output: [1]
Example 4:

Input: head = [1,2], k = 1
Output: [2,1]
Example 5:

Input: head = [1,2,3], k = 2
Output: [1,2,3]
 

Constraints:

The number of nodes in the list is n.
1 <= k <= n <= 105
0 <= Node.val <= 100

*/
#include <stdlib.h>



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
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class SwapNodes {

public:

    ListNode* doit_(ListNode* head, int k) {
        int listLength = 0;
        ListNode* currentNode = head;
        // find the length of linked list
        while (currentNode) {
            listLength++;
            currentNode = currentNode->next;
        }
        // set the front node at kth node
        ListNode* frontNode = head;
        for (int i = 1; i < k; i++) {
            frontNode = frontNode->next;
        }
        // set the end node at (listLength - k)th node
        ListNode* endNode = head;
        for (int i = 1; i <= listLength - k; i++) {
            endNode = endNode->next;
        }
        // swap the values of front node and end node
        std::swap(frontNode->val, endNode->val);
        return head;
    }

    ListNode* swapNodes(ListNode* head, int k) {
        int listLength = 0;
        ListNode* frontNode;
        ListNode* endNode;
        ListNode* currentNode = head;
        while (currentNode) {
            listLength++;
            if (listLength == k) {
                frontNode = currentNode;
            }
            currentNode = currentNode->next;
        }
        endNode = head;
        for (int i = 1; i <= listLength - k; i++) {
            endNode = endNode->next;
        }
        // swap front node and end node values
        std::swap(frontNode->val, endNode->val);
        return head;
    }

    /*
        Approach 3: Single Pass Approach
        Intuition

        Can we implement the problem in a single pass? The problem is that to find the position of endNode we must know the length of the Linked List. And to find the length of the Linked List we must have iterated over the list before at least once.

        However, we could use a trick to find the position of the pointer endNode in a single pass. The trick is:

        If endNode is k positions behind a certain node currentNode, when currentNode reaches the end of linked list i.e at n^{th}n 
        th
        node , the endNode would be at the n - k^{th}n−k 
        th
        node.

        A similar trick is used in a few other Linked List problems like Remove Nth Node From the End of List and the Fast and Slow Pointer Approach in Find The Middle Of Linked List.

        The following figure illustrates the idea.

        img

        Let's see how we can implement this approach.

        Algorithm

        The problem can be implemented in a single pass using the following steps,

        Start iterating from the head of the Linked List until the end using a pointer currentNode.

        Keep track of the number of nodes traversed so far using the variable listLength. The listLength is incremented by 11 as each node is traversed.

        If listLength is equal to k, we know that currentNode is pointing to the k^{th}k 
        th
        node from the beginning. Set frontNode to point to the k^{th}k 
        th
        node. Also, at this point, initialize endNode to point at the head of the linked list. Now we know that endNode is k nodes behind the head node.

        If endNode is not null, we know that it is positioned k nodes behind the currentNode and so we increment endNode in addition to currentNode. When currentNode reaches the end of the list, endNode would be pointing at a node which is k nodes behind the last node.

        Swap the values of frontNode and endNode using temporary variable temp.

        Return the head node.

        Implementation


        Complexity Analysis

        Time Complexity : \mathcal{O}(n)O(n), where nn is the size of Linked List. We are iterating over the entire Linked List once.

        Space Complexity: \mathcal{O}(1)O(1), as we are using constant extra space to maintain list node pointers frontNode, endNode and currentNode.
    */
    ListNode* swapNodes(ListNode* head, int k) {
        int listLength = 0;
        ListNode* frontNode = nullptr;
        ListNode* endNode = nullptr;
        ListNode* currentNode = head;
        // set the front node and end node in single pass
        while (currentNode) {
            listLength++;
             if(endNode != NULL) {
                endNode = endNode->next;
             }
            // check if we have reached kth node
            if (listLength == k) {
                frontNode = currentNode;
                endNode = head;
            }          
            currentNode = currentNode->next;
        }
        // swap the values of front node and end node
        std::swap(frontNode->val, endNode->val);
        return head;
    }
};