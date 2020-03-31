package main

import (
	"fmt"
)

func test_basic_set() {

	{
		// MAP implematation
		// The idiomatic way to implement a set in Go is to use a map.

		// new empty set
		set := make(map[string]bool)

		// Add
		set["foo"] = true

		// Loop
		for k := range set {
			fmt.Println(k)
		}

		// Delete
		delete(set, "foo")

		// Size
		length := len(set)
		fmt.Printf("length, %d ", length)

		// membership
		exists := set["Foo"]

		fmt.Println(exists)
	}

	{
		// Alternative
		// If the memory used by the booleans is an issue, which seems unlikely,
		// you could replace them with empty structs. In Go, an empty struct typically doesn’t use any memory.

		// New empty set
		set := make(map[string]struct{})

		// Add
		set["Foo"] = struct{}{}

		// Loop
		for k := range set {
			fmt.Println(k)
		}

		// delete
		delete(set, "Foo")

		// size
		fmt.Println(len(set))

		// membership
		if v, exists := set["Foo"]; exists {
			fmt.Println(v)
		}
	}
}

func Test_set() {

	test_basic_set()
}
