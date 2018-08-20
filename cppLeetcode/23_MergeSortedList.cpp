/*

# 23. Merge k Sorted Lists

# Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

# Example:

# Input:
# [
#  1->4->5,
#  1->3->4,
#  2->6
# ]
# Output: 1->1->2->3->4->4->5->6

*/

#include <map>
#include <vector>
using namespace std;


//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class MergeKLists {
public:
	ListNode* doit(vector<ListNode*>& lists) {

		if (lists.empty())
			return nullptr;

		std::multimap<int, ListNode*> mapping;
		for (auto iter = lists.begin(); iter != lists.end(); iter++) {
			if (*iter)
				mapping.emplace((*iter)->val, *iter);
		}

		ListNode A(100);
		ListNode* res = &A;
		while (!mapping.empty()) {

			auto C = mapping.begin();
			ListNode* tmp = C->second;

			res->next = tmp;
			res = res->next;
			mapping.erase(C);
			tmp = tmp->next;

			if (tmp)
				mapping.emplace(tmp->val, tmp);
		}

		return A.next;
	}
};


class Solution {
private:
	ListNode *mergeLists(ListNode *l1, ListNode *l2) {
		ListNode *head = NULL, *node = NULL;

		while (l1 && l2) {
			if (l1->val <= l2->val) {
				head ? node->next = l1 : head = l1;
				node = l1;
				l1 = l1->next;
			}
			else {
				head ? node->next = l2 : head = l2;
				node = l2;
				l2 = l2->next;
			}
		}

		if (l1 || l2) {
			head ?
				node->next = l1 ? l1 : l2 :
				head = l1 ? l1 : l2;
		}

		return head;
	}

public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		ListNode *result = NULL;
		for (int i = 0; i < lists.size(); ++i) {
			result = mergeLists(result, lists[i]);
		}
		return result;
	}
};


class Solution1 {
private:
	static ListNode* mergeTwoLists(ListNode *l1, ListNode *l2) {
		if (l1 == nullptr) {
			return l2;
		}

		if (l2 == nullptr) {
			return l1;
		}

		if (l2->val < l1->val) {
			swap(l2, l1);
		}

		for (auto n = l1;;) {
			while (n->next != nullptr && n->next->val <= l2->val) {
				n = n->next;
			}

			if (n->next == nullptr) {
				n->next = l2;
				return l1;
			}

			swap(n->next, l2);
		}
	}
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		if (lists.empty()) {
			return nullptr;
		}

		while (lists.size() > 1) {
			auto len = lists.size();
			for (size_t i = 0; i < len / 2; ++i) {
				lists[i] = mergeTwoLists(lists[i], lists[len - i - 1]);
			}
			lists.resize((len + 1) / 2);
		}
		return lists[0];
	}
};


void Test_23_MergeSortedList() {

	vector<ListNode*> lists;
	ListNode* tmp = nullptr;
	tmp = new ListNode(1);
	tmp->next = new ListNode(4);
	tmp->next->next = new ListNode(5);

	lists.push_back(tmp);

	tmp = new ListNode(1);
	tmp->next = new ListNode(3);
	tmp->next->next = new ListNode(4);
	lists.push_back(tmp);


	tmp = new ListNode(2);
	tmp->next = new ListNode(6);
	lists.push_back(tmp);

	lists.push_back(new ListNode(3));

	ListNode* res = MergeKLists().doit(lists);

	for (auto it = res; it != nullptr; it = it->next)
		delete it;

	return;
}