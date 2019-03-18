package main

import (
	"container/list"
	"fmt"
)

// Package list implements a doubly linked list.

func output_list(l *list.List) {
	fmt.Println("iterate list")
	for e := l.Front(); e != nil; e = e.Next() {
		fmt.Printf("%d, ", e.Value)
	}
	fmt.Println()
}

func output_list_reverse(l *list.List) {
	fmt.Println("reverse iterate list")
	for b := l.Back(); b != nil; b = b.Prev() {
		fmt.Printf("%d, ", b.Value)
	}
	fmt.Println()
}

func Main_test_list() {

	l := list.New()

	e4 := l.PushBack(4)
	e1 := l.PushFront(1)

	l.InsertBefore(3, e4)
	l.InsertAfter(2, e1)

	fmt.Println("len is ", l.Len())

	output_list(l)
	output_list_reverse(l)

	fmt.Println("Font is ", l.Front().Value)
	fmt.Println("Back is ", l.Back().Value)

	l.MoveAfter(e1, e4)
	fmt.Println("MoveAfter(e1, e4)")
	output_list(l)
	output_list_reverse(l)

	l.MoveBefore(e1, e4)
	fmt.Println("MoveBefore(e1, e4)")
	output_list(l)
	output_list_reverse(l)

	l.MoveToBack(e4)
	l.MoveToFront(e1)
	fmt.Println("MoveToBack(e4) and MoveToFront(e1)")

	output_list(l)
	output_list_reverse(l)

	l.Remove(e1)
	l.Remove(e4)
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
