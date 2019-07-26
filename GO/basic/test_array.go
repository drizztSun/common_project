package main

import (
	"fmt"
	"strings"
)

func slice_literals() {

	q := []int{2, 3, 5, 7, 11, 13}
	fmt.Println(q)

	r := []bool{true, false, true, true, false, true}
	fmt.Println(r)

	s := []struct {
		i int
		b bool
	}{
		{2, true},
		{3, false},
		{5, true},
		{7, true},
		{11, false},
		{13, true},
	}

	fmt.Println(s)
}

func test_2darray() {

	board := [][]string{
		[]string{"_", "_", "_"},
		[]string{"_", "_", "_"},
		[]string{"_", "_", "_"},
	}

	board[0][0] = "X"
	board[2][2] = "O"
	board[1][2] = "X"
	board[1][0] = "O"
	board[0][2] = "X"

	for i := 0; i < len(board); i++ {
		fmt.Printf("%s\n", strings.Join(board[i], " "))
	}
}

func test_array() {

	// define an array

	var array1 []int  // empty array
	var array2 [2]int // emptry array with 2 int elements

	array3 := []int{1, 2, 3, 4, 5, 6} // define a array
	array4 := make([]int, 3, 5)       // define an array with length and capacity

	for i := range array4 {
		array4[i] = i
	}

	fmt.Println(array1)
	fmt.Println(array2)

	// iterate an array
	for i, v := range array3 {
		fmt.Printf("i: %d, v:%d v:%d ", i, array3[i], v)
	}
	fmt.Println()

	// length and capacity
	fmt.Printf("Array4 has cap= %d, len= %d , %v \n", cap(array4), len(array4), array4)
	fmt.Printf("Array3 has cap= %d, len= %d , %v \n", cap(array3), len(array3), array3)

	// slice array[low: high] like array[1:4]
	fmt.Println("array3[:] ", array3[:])
	fmt.Println("array3[1:] ", array3[1:])
	fmt.Println("array3[:4] ", array3[:4])

	// string array
	names := [4]string{
		"John",
		"Paul",
		"George",
		"Ringo",
	}
	fmt.Println(names)

	// slice doesn't create a new array. it is just a snapshot of orignal array.
	// if your change this orignal array, it will show the change in any slice
	a := names[0:2]
	b := names[1:3]
	fmt.Println(a, b)

	b[0] = "XXX"
	fmt.Println(a, b)
	fmt.Println(names)

	slice_literals()

	// append an element to its tail
	array1 = append(array1, 1)
	array1 = append(array1, 3, 4, 5) // add multiple ones in ont time
	fmt.Println(array1)

	// append an element to its head
	array1 = append([]int{0}, array1[:]...)
	fmt.Println(array1)

	// insert an element like 2, into index i, like 2
	array1 = append(array1[:2], append([]int{2}, array1[2:]...)...)
	fmt.Println(array1)

	// remove an element at index 2
	array1 = append(array1[:2], array1[3:]...)
	fmt.Println(array1)

	// remove an element at tail
	array1 = array1[:len(array1)-1]
	fmt.Println(array1)

	// remove an element at head
	array1 = array1[1:]
	fmt.Println(array1)

	// array10 combine to arrays
	array10 := append(array1, array2...)

	test_2darray()
}
