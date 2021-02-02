/*
1171. Remove Zero Sum Consecutive Nodes from Linked List



Given the head of a linked list, we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.

After doing so, return the head of the final linked list.  You may return any such answer.

 

(Note that in the examples below, all sequences are serializations of ListNode objects.)

Example 1:

Input: head = [1,2,-3,3,1]
Output: [3,1]
Note: The answer [1,2,1] would also be accepted.
Example 2:

Input: head = [1,2,3,-3,4]
Output: [1,2,4]
Example 3:

Input: head = [1,2,3,-3,-2]
Output: [1]
 

Constraints:

The given linked list will contain between 1 and 1000 nodes.
Each node in the linked list has -1000 <= node.val <= 1000.


*/
#include <map>
#include <unordered_map>

using std::unordered_map;
using std::map;

class RemoveZeroSumSublists {



 // Definition for singly-linked list.
 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 

public:


    /*
        Intuition
        Assume the input is an array.
        Do you know how to solve it?
        Scan from the left, and calculate the prefix sum.
        Whenever meet the seen prefix,
        remove all elements of the subarray between them.


        Solution 1
        Because the head ListNode can be removed in the end,
        I create a dummy ListNode and set it as a previous node of head.
        prefix calculates the prefix sum from the first node to the current cur node.

        Next step, we need an important hashmap m (no good name for it),
        It takes a prefix sum as key, and the related node as the value.

        Then we scan the linked list, accumulate the node's value as prefix sum.

        If it's a prefix that we've never seen, we set m[prefix] = cur.
        If we have seen this prefix, m[prefix] is the node we achieve this prefix sum.
        We want to skip all nodes between m[prefix] and cur.next (exclusive).
        So we simplely do m[prefix].next = cur.next.
        We keep doing these and it's done.


        Complexity
        Time O(N), one pass
        SpaceO(N), for hashmap
    */

    ListNode* doit_1(ListNode* head) {
        ListNode* dummy = new ListNode(0), *cur = dummy;
        dummy->next = head;
        int prefix = 0;
        map<int, ListNode*> m;
        while (cur) {
            prefix += cur->val;
            if (m.count(prefix)) {
                cur =  m[prefix]->next;
                int p = prefix + cur->val;
                while (p != prefix) {
                    m.erase(p);
                    cur = cur->next;
                    p += cur->val;
                }
                m[prefix]->next = cur->next;
            } else {
                m[prefix] = cur;
            }
            cur = cur->next;
        }
        return dummy->next;
    }

    /*
        Improvement
        I think that's the best part of my post.
        It's a great discuss in the leetcode's discuss.

        People are willing to read my article and help me improve it.
        To be honest, I think I take good responsiblilty to maintain my solution.
        (Though the case I don't have prime membership and canot even read my own post in locked problem)

        Thanks to @alexjst inspired me the follwing solution.


        Soluiton 2: Two Passes
        The story is that,
        I wrote the really concise solution,
        it got accepted but actully it's wrong.
        I fixed it by adding another while loop.
        That is the Solution 1.

        If we don't insist on one pass,
        we can find the two passes is actually really neat.

        That turned back to the intuition that I mentioned:
        Assume the input is an array.
        How will you solve the problem?

        Iterate for the first time,
        calculate the prefix sum,
        and save the it to seen[prefix]

        Iterate for the second time,
        calculate the prefix sum,
        and directly skip to last occurrence of this prefix
    */
    ListNode* doit_2(ListNode* head) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        int prefix = 0;
        unordered_map<int, ListNode*> seen;
        for (ListNode* i = dummy; i; i = i->next) {
            seen[prefix += i->val] = i;
        }
        prefix = 0;
        for (ListNode* i = dummy; i; i = i->next) {
            i->next = seen[prefix += i->val]->next;
        }
        return dummy->next;
    }
}