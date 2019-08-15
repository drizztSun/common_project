package main

import (
	"fmt"
	//"sync"
)
/*
Channels can be buffered. Provide the buffer length as the second argument to make to initialize a buffered channel:

ch := make(chan int, 100)
Sends to a buffered channel block only when the buffer is full. Receives block when the buffer is empty.

Modify the example to overfill the buffer and see what happens.
*/

func test_basic_bufferchannel() {

	// Only bufferchannel's read-write is able to work in the same go-routine.
	// if unbufferchannel, it will be deadlock.
	c := make(chan int, 10)

	for i := 0; i < 10; i++ {
		c <- i
	}

	for i := 0; i < 10; i++ {
		fmt.Println(<-c)
	}
}

func test_routine_bufferchannel() {

	/*
	r := make(chan int, 3)
	w := make(chan int, 3)
	quit := make(chan int)

	go func() {
		for (
			select {
				case w <- 
			}

		)
	} ()
	*/
}

func test_bufferchannel() {

	test_basic_bufferchannel()

	test_routine_bufferchannel()
}