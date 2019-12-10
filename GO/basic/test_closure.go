package main

import (
	"fmt"
)

// function closure
func c_adder() func(int) int {
	sum := 0
	return func(a int) int {
		sum = sum + a
		return sum
	}
}

func c_caller2Adder() {

	pos, neg := c_adder(), c_adder()
	for i := 0; i < 10; i++ {
		fmt.Println(pos(i), neg(-2*i))
	}
}

func c_fibonacci() func() int {
	last1, last2 := 0, 1

	return func() int {
		res := last1 + last2
		last1 = last2
		last2 = res
		return res
	}
}

func c_callfibonacci() {

	fino := c_fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Printf("%d, ", fino())
	}
	fmt.Printf("\n")
}

func test_closure() {

	fmt.Println("--- test closure ---")

	c_caller2Adder()

	c_callfibonacci()
}
