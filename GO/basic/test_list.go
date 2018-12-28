package basic

import (
	"container/list"
	"fmt"
)

// Package list implements a doubly linked list.

func output_list(l *List) {
	for e := l.Front(); e != nil; e = e.Next() {
		fmt.Print(e.Value)
		fmt.Print(', ')
	}
	fmt.Println()
}

func output_list_reverse(l *List) {
	for be := l.Back(); be != nil; be = be.Prev() {
		fmt.Print(be.Value)
		fmt.Print(', ')
	}
	fmt.Println()
}

func Main_test_list() {

	l := list.New()

	e4 := l.PushBack(4)
	e1 := l.PushFront(1)

	l.InsertBefore(3, e4)
	l.InsertAfter(2, e1)

	fmt.Println("len is %v", l.Len())

	output_list(l)
	output_list_reverse(l)

	l.MoveAfter(e1, e4)
	fmt.Println("MoveAfter(e1, e4)")
	output_list(l)
	output_list_reverse(l)

	l.MoveBefore(e4, e1)
	fmt.Println("MoveBack(e4, e1)")
	output_list(l)
	output_list_reverse(l)

	l.MoveToBack(e4)
	l.MoveToFront(e1)
	fmt.Println("MoveToBack and MoveToFront")

	output_list(l)
	output_list_reverse(l)

	l.remove(e1)
	l.remove(e4)
	fmt.Println("remove(e1) and remove(e4)")
	output_list(l)
	output_list_reverse(l)

	lb := list.New()
	lb.PushFront(0)
	lb.PushFront(-1)

	la := list.New()
	la.PushBack(5)
	la.PushBack(6)

	l.PushBackList(la)
	l.PushFrontList(lb)
	fmt.Println("PushBackList and PushFrontList")
	output_list(l)
	output_list_reverse(l)

}

func main() {
	Main_test_list()
}