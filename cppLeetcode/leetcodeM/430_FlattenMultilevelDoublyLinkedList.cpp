/*
430. Flatten a Multilevel Doubly Linked List

You are given a doubly linked list which in addition to the next and previous pointers, it could have a child pointer, which may or may not point to a separate doubly linked list. 
These child lists may have one or more children of their own, and so on, to produce a multilevel data structure, as shown in the example below.

Flatten the list so that all the nodes appear in a single-level, doubly linked list. You are given the head of the first level of the list.



Example 1:

Input: head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
Output: [1,2,3,7,8,11,12,9,10,4,5,6]
Explanation:

The multilevel linked list in the input is as follows:



After flattening the multilevel linked list it becomes:


Example 2:

Input: head = [1,2,null,3]
Output: [1,3,2]
Explanation:

The input multilevel linked list is as follows:

  1---2---NULL
  |
  3---NULL
Example 3:

Input: head = []
Output: []
 

How multilevel linked list is represented in test case:

We use the multilevel linked list from Example 1 above:

 1---2---3---4---5---6--NULL
         |
         7---8---9---10--NULL
             |
             11--12--NULL
The serialization of each level is as follows:

[1,2,3,4,5,6,null]
[7,8,9,10,null]
[11,12,null]
To serialize all levels together we will add nulls in each level to signify no node connects to the upper node of the previous level. The serialization becomes:

[1,2,3,4,5,6,null]
[null,null,7,8,9,10,null]
[null,11,12,null]
Merging the serialization of each level and removing trailing nulls we obtain:

[1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
 

Constraints:

The number of Nodes will not exceed 1000.
1 <= Node.val <= 10^5
*/
#include <stack>

using stack;


// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};


class FlatternMultilevelDoubleLinked {

public:
    Node* doit_search(Node* head) {

        std::function<std::pair<Node*, Node*>(Node*)> build = [&](Node* current) {
        
            Node *head = current, *last = nullptr, *tail = nullptr;
            
            while (current) {
                
                if (current->child) {
                    
                    auto [h, t] = build(current->child);
                    
                    current->child = nullptr;
                    Node *next_node = current->next;
                    current->next = h;
                    h->prev = current;
                    
                    if (next_node) {
                        t->next = next_node;
                        next_node->prev = t;
                    }
                    current = t;
                }

                tail = current;
                current = current->next;
            }
            
            return make_pair(head, tail);
        };
        
        return build(head).first;
    }

    Node* doit_iterate(Node* head) {

        Node* cur = head;

        while (cur) {

            if (cur->child) {

                Node* curnext = cur->next;

                cur->next = cur->child;
                cur->child->prev = cur;
                cur->child = nullptr;

                Node *tail = cur;
                while (tail->next)
                    tail = tail->next;

                tail->next = curnext;
                if (curnext) {
                    curnext->prev = tail;
                }
            }
            cur = cur->next;
        }
        return head;
    }

    Node* doit_iterate(Node* node) {

        stack<Node*> st;
        st.push(node);
        Node *cur = node;
        Node *prehead = node;

        while (st) {

            if (cur->child) {

                


            }


        }

        return prehead;
    }
};