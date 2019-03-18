package main

import "fmt"

func test_lambda() {

	test1 := func() bool {
		return true
	}

	fmt.Println(test1())

	test2 := func(x, y int) int {
		return 3*x + y
	}

	fmt.Println(test2(1, 2))

	test3 := func(x, y bool) bool {
		return !x && y
	}

	fmt.Println(test3(false, true))
}
