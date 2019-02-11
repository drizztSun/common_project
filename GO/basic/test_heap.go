package main

import (
	"container/heap"
	"fmt"
)

/*
Package heap provides heap operations for any type that implements heap.Interface.
A heap is a tree with the property that each node is the minimum-valued node in its subtree.

The minimum element in the tree is the root, at index 0.

A heap is a common way to implement a priority queue.
To build a priority queue, implement the Heap interface with the (negative) priority as the ordering for the Less method, so Push adds items while Pop removes the highest-priority item from the queue.
The Examples include such an implementation; the file example_pq_test.go has the complete source.

GO <heap> <priority
*/

type IntHeap []int

func (h IntHeap) Len() int {
	return len(h)
}

func (h IntHeap) Less(i, j int) bool {
	return h[i] < h[j]
}

func (h IntHeap) Swap(i, j int) {
	h[i], h[j] = h[j], h[i]
}

func (h *IntHeap) Push(x interface{}) {
	*h = append(*h, x.(int))
}

func (h *IntHeap) Pop() interface{} {
	old := *h
	n := len(old)

	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func main_test_intheap() {
	fmt.Println("main_test_intheap")

	h := &IntHeap{1, 5, 2}

	heap.Init(h)
	heap.Push(h, 3)
	fmt.Println("minmum value is %d", (*h)[0])

	for h.Len() > 0 {
		fmt.Printf("%d, ", heap.Pop(h))
	}

	fmt.Println("")
}

type Item struct {
	value    string
	priority int
	index    int
}

type PriorityQueue []*Item

func (pq PriorityQueue) Len() int {
	return len(pq)
}

func (pq PriorityQueue) Less(i, j int) bool {
	return pq[i].priority > pq[j].priority
}

func (pq PriorityQueue) Swap(i, j int) {
	pq[i], pq[j] = pq[j], pq[i]
	pq[i].index = j
	pq[j].index = i
}

func (pq *PriorityQueue) Pop() interface{} {
	old := *pq
	n := len(old)
	x := old[n-1]
	x.index = -1
	*pq = old[:n-1]
	return x
}

func (pq *PriorityQueue) Push(i interface{}) {
	n := len(*pq)
	item := i.(Item)	
	item.index = n
	*pq = append(*pq, &item)
}

func (pq *PriorityQueue) update(item *Item, value string, priority int) {
	item.value = value
	item.priority = priority
	heap.Fix(pq, item.index)
}

func main_test_priorityQueue() {

	fmt.Println("main_test_priorityQueue")

	items := map[string]int{
		"banana": 3, "apple": 2, "pear": 4,
	}
	i := 0

	pq := make(PriorityQueue, len(items))
	for value, priority := range items {
		pq[i] = &Item{
			value, priority, i,
		}
		i++
	}

	heap.Init(&pq)

	item := Item{
		value:    "orange",
		priority: 1,
	}

	heap.Push(&pq, item)
	pq.update(&item, item.value, 5)

	for pq.Len() > 0 {
		item := heap.Pop(&pq).(*Item)
		fmt.Printf("%.2d:%s, ", item.priority, item.value)
	}

	fmt.Println("")
}

func Main_test_heap() {

	// IntHeap
	main_test_intheap()

	// PriorityQueue
	main_test_priorityQueue()
}

/*
func main() {
	Main_test_heap()
}
*/
