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
#include <algorithm>
#include <functional>

using std::stack;


// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

/*
    430.Flatten-a-Multilevel-Doubly-Linked-List
    本题的基本思想是，对于一个节点h，我们需要依次拼接h本身、遍历h->child得到的链表，遍历h->next得到的链表。考虑到第三部分要接在第二部分的末尾，所以这个“遍历”的递归函数的返回值应该是整个链表的最后一个节点。

    所以，当h的next和child都存在的时候，大致的思路应该是这样的：

    Node* dfs(Node* h)
    {
    child = h->child;
    next = h->next;
    Node* childEnd = dfs(child);
    Node* nextEnd = dfs(next);

    h->next = child;   // h和child拼接
    child->prev = h;
    childEnd->next = next;  //childEnd与next拼接
    next->prev = childEnd;

    return nextEnd;
    }  
    但是在实际处理的时候，考虑当child和next各自是否为NULL时，具体的代码写法会不一样。

    child和next都为空：直接返回h
    child不为空，next为空：将h与child拼接后，返回的是childEnd
    child为空，next不为空：返回的是nextEnd.
*/

class FlatternLink {
public:
    Node* flatten(Node* head) 
    {
        findEnd(head);
        return head;
    }

    Node* findEnd(Node* h)
    {   
        if (h==NULL) return NULL;

        Node* next = h->next;
        Node* child = h->child;
        h->child = NULL;

        if (child==NULL && next==NULL)
            return h;
        else if (child!=NULL && next==NULL)
        {
            h->next = child;
            child->prev = h;
            Node* childEnd = findEnd(child);
            return childEnd;
        }
        else if (child==NULL && next!=NULL)
        {
            Node* nextEnd = findEnd(next);
            return nextEnd;
        }
        else
        {
            h->next = child;
            child->prev = h;
            Node* childEnd = findEnd(child);            
            childEnd->next = next;
            next->prev = childEnd;
            return findEnd(next);
        }
    }
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
            
            return {head, tail};
        };
        
        return build(head).first;
    }

    Node* doit_iterate_link(Node* head) {

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
};