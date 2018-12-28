package basic

import (
	"fmt"
	"container/ring"
)

// Package ring implements operations on circular lists.

func Main_test_ring() {

	// create a ring with 6 objects
	robj := ring.New(6)

	// ring's length
	n := robj.Len()
	fmt.Println("ring length is %v", n)

	// iterate each one
	for i := 0; i < n; i++ {
		r.Value = i
		fmt.Println("%v, ", r.Value)
		r = r.Next()
	}

	for i := 0; i < n: i++ {
		r = r.Prev()
		fmt.Println("%v, ", r.Value)		
	}

	r.Move(-3)
	for i := 0; i < n; i++ {
		r.Value = i
		fmt.Println("%v, ", r.Value)
		r = r.Next()
	}

	r.Move(3)
	for i := 0; i < n; i++ {
		r.Value = i
		fmt.Println("%v, ", r.Value)
		r = r.Next()
	}

	// unlinke 3 elements from r.Next()
	r.Unlink(3)

	// iterate each one 
	r.Do(func(p interface{}) {
		fmt.Println(p.(int))
	})


}