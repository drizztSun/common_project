/*
148. Sort List


Given the head of a linked list, return the list after sorting it in ascending order.

Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?

 

Example 1:


Input: head = [4,2,1,3]
Output: [1,2,3,4]
Example 2:


Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]
Example 3:

Input: head = []
Output: []
 

Constraints:

The number of nodes in the list is in the range [0, 5 * 104].
-105 <= Node.val <= 105


Solution
Overview
The problem is to sort the linked list in \mathcal{O}(n \log n)O(nlogn) time and using only constant extra space. 
If we look at various sorting algorithms, Merge Sort is one of the efficient sorting algorithms that is popularly used for sorting the linked list. 
The merge sort algorithm runs in \mathcal{O}(n \log n)O(nlogn) time in all the cases. Let's discuss approaches to sort linked list using merge sort.

Quicksort is also one of the efficient algorithms with the average time complexity of \mathcal{O}(n \log n)O(nlogn). But the worst-case time complexity is O(n^2). 
Also, variations of the quick sort like randomized quicksort are not efficient for the linked list because unlike arrays, random access in the linked list is not possible in \mathcal{O}(1)O(1) time. 
If we sort the linked list using quicksort, we would end up using the head as a pivot element which may not be efficient in all scenarios.

*/
#include <functional>


// Definition for singly-linked list.
struct ListNode {
    
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class SortList {

public:
    /*
        Approach 1: Top Down Merge Sort
        Intuition

        Merge sort is a popularly known algorithm that follows the Divide and Conquer Strategy. The divide and conquer strategy can be split into 2 phases:

        Divide phase: Divide the problem into subproblems.

        Conquer phase: Repeatedly solve each subproblem independently and combine the result to form the original problem.

        The Top Down approach for merge sort recursively splits the original list into sublists of equal sizes, sorts each sublist independently, and eventually merge the sorted lists. Let's look at the algorithm to implement merge sort in Top Down Fashion.

        Algorithm

        Recursively split the original list into two halves. The split continues until there is only one node in the linked list (Divide phase). To split the list into two halves, we find the middle of the linked list using the Fast and Slow pointer approach as mentioned in Find Middle Of Linked List.

        Recursively sort each sublist and combine it into a single sorted list. (Merge Phase). This is similar to the problem Merge two sorted linked lists

        The process continues until we get the original list in sorted order.

        For the linked list = [10,1,60,30,5], the following figure illustrates the merge sort process using a top down approach.


        Complexity Analysis

        Time Complexity: \mathcal{O}(n \log n)O(nlogn), where nn is the number of nodes in linked list. The algorithm can be split into 2 phases, Split and Merge.
    */
    ListNode* sortList_topdown_sort(ListNode* head) {
        if (!head || !head->next)
            return head;

        std::function<ListNode*(ListNode*, ListNode*)> merge = [&](ListNode* list1, ListNode* list2) {
            ListNode dummyHead(0);
            ListNode* ptr = &dummyHead;
            while (list1 && list2) {
                if (list1->val < list2->val) {
                    ptr->next = list1;
                    list1 = list1->next;
                } else {
                    ptr->next = list2;
                    list2 = list2->next;
                }
                ptr = ptr->next;
            }
            if(list1) ptr->next = list1;
            else ptr->next = list2;

            return dummyHead.next;
        };

        auto getMid = [](ListNode* head) -> ListNode* {
            ListNode* midPrev = nullptr;
            while (head && head->next) {
                midPrev = (midPrev == nullptr) ? head : midPrev->next;
                head = head->next->next;
            }
            ListNode* mid = midPrev->next;
            midPrev->next = nullptr;
            return mid;
        };

        std::function<ListNode*(ListNode*)> sortList = [&](ListNode* head) {
            ListNode* mid = getMid(head);
            ListNode* left = sortList(head);
            ListNode* right = sortList(mid);
            return merge(left, right);
        };

        return sortList(head);
    }

    /*
        Approach 2: Bottom Up Merge Sort
        Intuition

        The Top Down Approach for merge sort uses \mathcal{O}(\log n)O(logn) extra space due to recursive call stack. Let's understand how we can implement merge sort using constant extra space using Bottom Up Approach.

        The Bottom Up approach for merge sort starts by splitting the problem into the smallest subproblem and iteratively merge the result to solve the original problem.

        First, the list is split into sublists of size 1 and merged iteratively in sorted order. The merged list is solved similarly.

        The process continues until we sort the entire list.

        This approach is solved iteratively and can be implemented using constant extra space. Let's look at the algorithm to implement merge sort in Bottom Up Fashion.

        Algorithm

        Assume, nn is the number of nodes in the linked list.

        Start with splitting the list into sublists of size 11. Each adjacent pair of sublists of size 11 is merged in sorted order. After the first iteration, we get the sorted lists of size 22. A similar process is repeated for a sublist of size 22. In this way, we iteratively split the list into sublists of size 1,2,4,8 ..1,2,4,8.. and so on until we reach nn.

        To split the list into two sublists of given \text{size}size beginning from \text{start}start, we use two pointers, \text{mid}mid and \text{end}end that references to the start and end of second linked list respectively. The split process finds the middle of linked lists for the given \text{size}size.

        Merge the lists in sorted order as discussed in Approach 1

        As we iteratively split the list and merge, we have to keep track of the previous merged list using pointer \text{tail}tail and the next sublist to be sorted using pointer \text{nextSubList}nextSubList.

        For the linked list = [10,1,30,2,5], the following figure illustrates the merge sort process using a Bottom Up approach.

        Complexity Analysis

        Time Complexity: O(nlogn), where nn is the number of nodes in linked list. Let's analyze the time complexity of each step:
        Count Nodes - Get the count of number nodes in the linked list requires \mathcal{O}(n)O(n) time.

        Split and Merge - This operation is similar to Approach 1 and takes O(nlogn) time. For n = 16, the split and merge operation in Bottom Up fashion can be visualized as follows

        This gives us total time complexity as \mathcal{O}(n) + \mathcal{O}(n \log n) = \mathcal{O}(n \log n)O(n)+O(nlogn)=O(nlogn)

        Space Complexity: \mathcal{O}(1)O(1) We use only constant space for storing the reference pointers \text{tail}tail , \text{nextSubList}nextSubList etc.

    */
    ListNode* tail = new ListNode();
    ListNode* nextSubList = new ListNode();

    ListNode* sortList_bottomup(ListNode* head) {
        if (!head || !head -> next)
            return head;
        int n = getCount(head);
        ListNode* start = head;
        ListNode dummyHead(0);
        for (int size = 1; size < n; size = size * 2) {
            tail = &dummyHead;
            while (start) {
                if (!start->next) {
                    tail->next = start;
                    break;
                }
                ListNode* mid = split(start, size);
                merge(start, mid);
                start = nextSubList;
            }
            start = dummyHead.next;
        }
        return dummyHead.next;
    }

    ListNode* split(ListNode* start, int size) {
        ListNode* midPrev = start;
        ListNode* end = start->next;
        //use fast and slow approach to find middle and end of second linked list
        for (int index = 1; index < size && (midPrev->next || end->next); index++) {
            if (end->next) {
                end = (end->next->next) ? end->next->next : end->next;
            }
            if (midPrev->next) {
                midPrev = midPrev->next;
            }
        }
        ListNode* mid = midPrev->next;
        nextSubList = end->next;
        midPrev->next = nullptr;
        end->next = nullptr;
        // return the start of second linked list
        return mid;
    }

    void merge(ListNode* list1, ListNode* list2) {
        ListNode dummyHead(0);
        ListNode* newTail = &dummyHead;
        while (list1 && list2) {
            if (list1->val < list2->val) {
                newTail->next = list1;
                list1 = list1->next;
                newTail = newTail->next;
            } else {
                newTail->next = list2;
                list2 = list2->next;
                newTail = newTail->next;
            }
        }
        newTail->next = (list1) ? list1 : list2;
        // traverse till the end of merged list to get the newTail
        while (newTail->next) {
            newTail = newTail->next;
        }
        // link the old tail with the head of merged list
        tail->next = dummyHead.next;
        // update the old tail with the new tail of merged list
        tail = newTail;
    }

    int getCount(ListNode* head) {
        int cnt = 0;
        ListNode* ptr = head;
        while (ptr) {
            ptr = ptr->next;
            cnt++;
        }
        return cnt;
    }

};