/*

708. Insert into a Sorted Circular Linked List


Given a node from a Circular Linked List which is sorted in ascending order, write a function to insert a value insertVal into the list such that it remains a sorted circular list.
The given node can be a reference to any single node in the list, and may not be necessarily the smallest value in the circular list.

If there are multiple suitable places for insertion, you may choose any place to insert the new value. After the insertion, the circular list should remain sorted.

If the list is empty (i.e., given node is null), you should create a new single circular list and return the reference to that single node. Otherwise, you should return the original given node.

 

Example 1:


 
Input: head = [3,4,1], insertVal = 2
Output: [3,4,1,2]
Explanation: In the figure above, there is a sorted circular list of three elements. You are given a reference to the node with value 3, and we need to insert 2 into the list. 
The new node should be inserted between node 1 and node 3. After the insertion, the list should look like this, and we should still return node 3.



Example 2:

Input: head = [], insertVal = 1
Output: [1]
Explanation: The list is empty (given head is null). We create a new single circular list and return the reference to that single node.
Example 3:

Input: head = [1], insertVal = 0
Output: [1,0]
 

Constraints:

0 <= Number of Nodes <= 5 * 10^4
-10^6 <= Node.val <= 10^6
-10^6 <= insertVal <= 10^6

*/




/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/

class InsertIntoSortedCircle {

    class Node {
    public:
        int val;
        Node* next;

        Node() {}

        Node(int _val) {
            val = _val;
            next = nullptr;
        }

        Node(int _val, Node* _next) {
            val = _val;
            next = _next;
        }
    };

    /*
        
        708.Insert-into-a-Cyclic-Sorted-List
        本题的一个能简化思维的方法就是，提前找到这个链表中的最小值的节点．这样的话，后续的插入就会很方便．

        Node* h = head->next;
        Node* pre = head;
        while (h!=head && pre->val<=h->val)
        {
        h = h->next;
        pre = pre->next;
        }
        这样，得到的h就是整个链表中最小的节点了．于是，容易找到一个合适的插入位置：

        Node* NewHead = h;        
        while (h->next!=NewHead && !(h->val<=insertVal && h->next->val>=insertVal))
            h = h->next;
    */
    Node* insert(Node* head, int insertVal) 
    {
        if (head==nullptr)
        {
            Node* h = new Node(insertVal);
            h->next = h;
            return h;
        }
        
        Node* h = head->next;
        Node* pre = head;

        while (h!=head)
        {
            if (h->val >= pre->val )
            {
                h = h->next;
                pre = pre->next;
            }
            else                
                break;
        }
        
        Node* NewHead = h;        
        while (h->next!=NewHead && !(h->val<=insertVal && h->next->val>=insertVal))
            h = h->next;
        
        Node* temp = h->next;
        h->next = new Node(insertVal);
        h = h->next;
        h->next = temp;
        
        return head;
    }

public:
    
    Node* doit_(Node* head, int insertVal) {
        
        Node *nd = new Node(insertVal);
        
        if (!head) {
            nd->next = nd;
            return nd;
        }
        
        if (head && head->next == head) {
            head->next = nd;
            nd->next = head;
            return head;
        }
        
        Node *cur = head;
        
        do {    
            if ((cur->val < cur->next->val && insertVal <= cur->next->val && insertVal >= cur->val) || cur->val > cur->next->val && (insertVal >= cur->val || insertVal <= cur->next->val)) {
                nd->next = cur->next;
                cur->next = nd;
                return head;
            }
            cur = cur->next;
        } while (cur != head);
        
        nd->next = head->next;
        head->next = nd;
        
        return head;
    }
};