package main

import (
	"container/ring"
	"fmt"
)

// Package ring implements operations on circular lists.

func Main_test_ring() {

	// create a ring with 6 objects
	r := ring.New(6)

	// ring's length
	n := r.Len()
	fmt.Printf("ring length is %d \n", n)

	// iterate each one
	fmt.Println("iterate the array")
	for i := 0; i < n; i++ {
		r.Value = i
		fmt.Printf("%d, ", r.Value)
		r = r.Next()
	}

	fmt.Println("\n reverse-iterate the array")
	for i := 0; i < n; i++ {
		r = r.Prev()
		fmt.Printf("%d, ", r.Value)
	}

	fmt.Println("\n move the iterate backward 3 steps")
	r.Move(-3)
	for i := 0; i < n; i++ {
		r.Value = i
		fmt.Printf("%d, ", r.Value)
		r = r.Next()
	}

	fmt.Println("\n move the iterate forward 3 steps")
	r.Move(3)
	for i := 0; i < n; i++ {
		r.Value = i
		fmt.Printf("%d, ", r.Value)
		r = r.Next()
	}

	// unlinke 3 elements from r.Next()
	fmt.Println("\n unlink 3 elements")
	r.Unlink(3)
	for i := 0; i < r.Len(); i++ {
		r.Value = i
		fmt.Printf("%d, ", r.Value)
		r = r.Next()
	}

	// iterate each one
	fmt.Println("\n iterate func Do")
	r.Do(func(p interface{}) {
		fmt.Printf("%d, ", p.(int))
	})

}

/*
func main() {
	Main_test_ring()
}
*/
