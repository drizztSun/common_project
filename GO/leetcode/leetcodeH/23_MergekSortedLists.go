package leetcodeH

import "container/heap"

/*
23. Merge k Sorted Lists


Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

Example:

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6
*/

// * Definition for singly-linked list.
type ListNode struct {
	Val  int
	Next *ListNode
}

type heaqpos []*ListNode

func (obj heaqpos) Len() int {
	return len(obj)
}

func (obj heaqpos) Less(i, j int) bool {
	//return obj[i].node.Val < obj[j].node.Val
	return obj[i].Val < obj[j].Val
}

func (obj heaqpos) Swap(i, j int) {
	obj[i], obj[j] = obj[j], obj[i]
}

func (obj *heaqpos) Push(i interface{}) {
	//*obj = append(*obj, i.(*Node))
	*obj = append(*obj, i.(*ListNode))
}

func (obj *heaqpos) Pop() interface{} {
	old, n := *obj, len(*obj)
	res := old[n-1]

	*obj = old[:n-1]
	return res
}

func mergeKLists(lists []*ListNode) *ListNode {
	var res *ListNode = &ListNode{100, nil}
	var buff heaqpos
	var node *ListNode = res

	heap.Init(&buff)

	for i := range lists {
		if lists[i] != nil {
			heap.Push(&buff, lists[i])
		}
	}

	for buff.Len() > 0 {
		item := heap.Pop(&buff).(*ListNode)
		node.Next = item
		if item.Next != nil {
			heap.Push(&buff, item.Next)

		}
		node = node.Next
	}

	return res.Next
}
