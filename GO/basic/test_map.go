package main

import (
	"fmt"
	"sync"
)

func Test_map_func() {

}

func test_basic_map() {

	// Map types are reference types, like pointers or slices, and so the value of m above is nil; it doesn't point to an initialized map.
	// A nil map behaves like an empty map when reading, but attempts to write to a nil map will cause a runtime panic;
	// don't do that. To initialize a map, use the built in make function:
	// map[KeyType]ValueType
	var n map[string]int // declare a map

	// The make function allocates and initializes a hash map data structure and returns a map value that points to it.
	// The specifics of that data structure are an implementation detail of the runtime and are not specified by the language itself.
	// In this article we will focus on the use of maps, not their implementation.
	n = make(map[string]int)
	fmt.Println("n length is ", len(n))

	m := map[string]int{
		"rsc": 3711,
		"r":   2138,
		"gri": 1908,
		"adg": 912,
	}

	// To initialize a map with some data, use a map literal:

	// Go provides a familiar syntax for working with maps. This statement sets the key "route" to the value 66:
	m["route"] = 66

	// This statement retrieves the value stored under the key "route" and assigns it to a new variable i:
	i := m["route"]
	fmt.Println(i)

	// If the requested key doesn't exist, we get the value type's zero value. In this case the value type is int, so the zero value is 0:
	j := m["root"]
	fmt.Println("j must be ", j)

	// The built in len function returns on the number of items in a map:
	fmt.Println("m's length is ", len(m))

	// The built in delete function removes an entry from the map:
	delete(m, "route")

	// A two-value assignment tests for the existence of a key:
	// In this statement, the first value (i) is assigned the value stored under the key "route".
	// If that key doesn't exist, i is the value type's zero value (0). The second value (ok) is a bool that is true if the key exists in the map, and false if not.
	if i, ok := m["route"]; ok {
		fmt.Println("There is no 'route' so ok is ", ok, " so i will be ", i)
	}

	// To test for a key without retrieving the value, use an underscore in place of the first value:
	_, ok := m["route"]
	if !ok {
		fmt.Println("route is gone? ", !ok)
	}

	// To iterate over the contents of a map, use the range keyword:
	for key, value := range m {
		fmt.Println("key : ", key, " value : ", value)
	}

}

// Exploiting zero values
// It can be convenient that a map retrieval yields a zero value when the key is not present.

// For instance, a map of boolean values can be used as a set-like data structure (recall that the zero value for the boolean type is false).
// This example traverses a linked list of Nodes and prints their values. It uses a map of Node pointers to detect cycles in the list.

type Node struct {
	Next  *Node
	Value interface{}
}

type Personal struct {
	Name  string
	Likes []string
}

func test_map_zerovalues() {

	var first *Node

	visited := make(map[*Node]bool)
	for n := first; n != nil; n = n.Next {
		if visited[n] {
			fmt.Println("cycle detected")
			break
		}
		visited[n] = true
		fmt.Println(n.Value)
	}

	// The expression visited[n] is true if n has been visited, or false if n is not present.
	// There's no need to use the two-value form to test for the presence of n in the map; the zero value default does it for us.

	// Another instance of helpful zero values is a map of slices. Appending to a nil slice just allocates a new slice,
	// so it's a one-liner to append a value to a map of slices; there's no need to check if the key exists. In the following example,
	// the slice people is populated with Person values. Each Person has a Name and a slice of Likes.
	// The example creates a map to associate each like with a slice of people that like it.
	var people []*Personal

	likes := make(map[string][]*Personal)
	for _, p := range people {
		for _, l := range p.Likes {
			likes[l] = append(likes[l], p)
		}
	}

	// To print a list of people who like cheese:
	for _, p := range likes["cheese"] {
		fmt.Println(p.Name, "likes cheese.")
	}

	// To print the number of people who like bacon:
	fmt.Println(len(likes["bacon"]), "people like bacon.")

}

type Key struct {
	Path, Country string
}

func test_key_types() {

	// Key types
	// As mentioned earlier, map keys may be of any type that is comparable. The language spec defines this precisely,
	// but in short, comparable types are boolean, numeric, string, pointer, channel, and interface types, and structs or arrays that contain only those types.
	// Notably absent from the list are slices, maps, and functions; these types cannot be compared using ==, and may not be used as map keys.

	// It's obvious that strings, ints, and other basic types should be available as map keys, but perhaps unexpected are struct keys.
	// Struct can be used to key data by multiple dimensions. For example, this map of maps could be used to tally web page hits by country:
	hits := make(map[string]map[string]int)

	addkeymap := func(m map[string]map[string]int, path, country string) {
		mm, ok := m[path]
		if !ok {
			mm = make(map[string]int)
			m[path] = mm
		}
		mm[country]++
	}

	addkeymap(hits, "/doc/", "au")

	// On the other hand, a design that uses a single map with a struct key does away with all that complexity:
	hits1 := make(map[Key]int)

	hits1[Key{"/", "vn"}]++

	n := hits1[Key{"/ref/spec", "ch"}]

	fmt.Println(n)

}

func test_map_concurrency() {

	var counter = struct {
		sync.RWMutex
		m map[string]int
	}{m: make(map[string]int)}

	// write
	counter.Lock()
	counter.m["some_key"]++
	counter.Unlock()

	// read
	counter.RLock()
	n := counter.m["some_key"]
	counter.RUnlock()

	fmt.Println("some_key: ", n)
}
