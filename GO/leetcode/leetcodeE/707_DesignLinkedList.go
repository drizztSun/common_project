package leetcodeE

import "reflect"

/*

Design your implementation of the linked list. You can choose to use the singly linked list or the doubly linked list. A node in a singly linked list should have two attributes: val and next. val is the value of the current node, and next is a pointer/reference to the next node. If you want to use the doubly linked list, you will need one more attribute prev to indicate the previous node in the linked list. Assume all nodes in the linked list are 0-indexed.

Implement these functions in your linked list class:

get(index) : Get the value of the index-th node in the linked list. If the index is invalid, return -1.
addAtHead(val) : Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
addAtTail(val) : Append a node of value val to the last element of the linked list.
addAtIndex(index, val) : Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted.
deleteAtIndex(index) : Delete the index-th node in the linked list, if the index is valid.
Example:

MyLinkedList linkedList = new MyLinkedList();
linkedList.addAtHead(1);
linkedList.addAtTail(3);
linkedList.addAtIndex(1, 2);  // linked list becomes 1->2->3
linkedList.get(1);            // returns 2
linkedList.deleteAtIndex(1);  // now the linked list is 1->3
linkedList.get(1);            // returns 3

*/
// MyLinkedList Singly linked list.
type MyLinkedList struct {
	val  int
	next *MyLinkedList
}

// Constructor Initialize your data structure here.
func constructorMyLinkedList() MyLinkedList {
	return MyLinkedList{}
}

// Get the value of the index-th node in the linked list. If the index is invalid, return -1.
func (myLinkedList *MyLinkedList) Get(index int) int {
	linkedList := *myLinkedList
	for i := 0; i < index; i++ {
		if reflect.DeepEqual(linkedList, MyLinkedList{}) {
			return -1
		}
		linkedList = *linkedList.next
	}

	if reflect.DeepEqual(linkedList, MyLinkedList{}) {
		return -1
	}
	return linkedList.val
}

// AddAtHead Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
func (myLinkedList *MyLinkedList) AddAtHead(val int) {
	nextLinkedList := *myLinkedList
	*myLinkedList = MyLinkedList{val, &nextLinkedList}
}

// AddAtTail Append a node of value val to the last element of the linked list.
func (myLinkedList *MyLinkedList) AddAtTail(val int) {
	linkedList := *myLinkedList
	for !reflect.DeepEqual(*linkedList.next, MyLinkedList{}) {
		linkedList = *linkedList.next
	}

	*linkedList.next = MyLinkedList{val, &MyLinkedList{}}
}

// AddAtIndex Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted.
func (myLinkedList *MyLinkedList) AddAtIndex(index int, val int) {
	linkedListPtr := myLinkedList
	for i := 0; i < index; i++ {
		if reflect.DeepEqual(*linkedListPtr, MyLinkedList{}) {
			return
		}
		linkedListPtr = linkedListPtr.next
	}

	nextLinkedList := *linkedListPtr
	*linkedListPtr = MyLinkedList{val, &nextLinkedList}
}

// DeleteAtIndex Delete the index-th node in the linked list, if the index is valid.
func (myLinkedList *MyLinkedList) DeleteAtIndex(index int) {
	linkedListPtr := myLinkedList
	for i := 0; i < index; i++ {
		if (reflect.DeepEqual(*linkedListPtr, MyLinkedList{})) {
			return
		}
		linkedListPtr = linkedListPtr.next
	}

	if linkedListPtr.next == nil {
		*linkedListPtr = MyLinkedList{}
		return
	}
	*linkedListPtr = *linkedListPtr.next
}
