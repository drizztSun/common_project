package main

import (
	"fmt"
	"time"
)

func fibonacci(c chan int, quit chan bool) {

	x, y := 1, 0

	for {
		select {
		case c <- x:
			x, y = x+y, x

		case <-quit:
			break
		}
	}
}

func select_chan() {

	c := make(chan int)
	quit := make(chan bool)

	go func() {
		for i := 0; i < 10; i++ {
			fmt.Println(<-c)
		}
		quit <- true
	}()

	fibonacci(c, quit)
}

func select_time() {

	tick := time.Tick(100 * time.Millisecond)
	boom := time.After(500 * time.Millisecond)

	for {
		select {
		case <-tick:
			fmt.Println("tick !")
		case <-boom:
			fmt.Println("boom !")
		default:
			fmt.Println("No time signal")
			time.Sleep(50 * time.Millisecond)
		}
	}
}

func test_select() {

	select_time()
}
