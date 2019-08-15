package main

import (
	"fmt"
	"sync"
)

/*
Channels
Channels are a typed conduit through which you can send and receive values with the channel operator, <-.

ch <- v    // Send v to channel ch.
v := <-ch  // Receive from ch, and
		   // assign value to v.
*/
func getSums(s []int, c chan int) {
	total := 0
	for _, v := range s {
		total += v
	}
	c <- total
}

func test_chann() {
	nums := []int{1, 2, 3, 4, 5, 6}
	c := make(chan int)
	go getSums(nums[0:3], c)
	go getSums(nums[3:], c)
	x, y := <-c, <-c // read - write - read - ..., blocked between any two of them
	fmt.Println(x, y, x+y)
}

/*
 channel and select
*/
func test_chann_select() {
	quit := make(chan int)
	c := make(chan int)

	go func() {

		for i := 0; i < 10; i++ {
			fmt.Println(<-c)
		}
		quit <- 0 // quit signal
	}()

	x, y := 0, 1
	for {
		select {
		case c <- y:
			x, y = y, x+y
		case <-quit:
			fmt.Println("quit")
			return // only return, not break, can jump out for "for.. select ", or use break in for-loop
		}
	}
}

/*
Channels can be buffered. Provide the buffer length as the second argument to make to initialize a buffered channel:

ch := make(chan int, 100)
Sends to a buffered channel block only when the buffer is full. Receives block when the buffer is empty.

Modify the example to overfill the buffer and see what happens.
*/
func test_buffed_chann() {

	ch := make(chan int, 2)
	ch <- 1
	ch <- 2
	fmt.Println(<-ch)
	fmt.Println(<-ch)

	nums := []int{1, 2, 3, 4, 5, 6}
	N := 2
	parts := len(nums) / N
	c := make(chan int, N)

	for i := 0; i < N; i++ {
		go func(s, e int, c chan int) {
			sums := 0
			for s < e && s < len(nums) {
				sums += nums[s]
				s++
			}
			c <- sums
		}(i*parts, (i+1)*parts, c)
	}

	sums := 0
	for i := 0; i < N; i++ {
		sums += <-c
	}

	fmt.Println(sums)
}

/*
chann simulate semaphone
*/
func test_chann_semaphone() {

	N := 100
	c := make(chan int, 4)
	var wg sync.WaitGroup
	wg.Add(N)

	for i := 0; i < N; i++ {
		go func(i int) {
			defer wg.Done()
			c <- 1
			// chan buffer is 4, so only 4 threads can run thread in the same time. after 4, the rest will be block on this one.
			// it likes sem.inc
			fmt.Printf("it comes from thread %d\n", i)
			<-c
			// it like sem.dec
		}(i)
	}

	wg.Wait()
}

// The first stage, gen, is a function that converts a list of integers to a channel that emits the integers in the list. 
// The gen function starts a goroutine that sends the integers on the channel and closes the channel when all the values have been sent:
func gen(nums ...int) <- chan int {

	out := make(chan int)

	go func() {
		for _, v  := range nums {
			out <- v
		}
		close(out)
	}()

	return out
}

//The second stage, sq, receives integers from a channel and returns a channel that emits the square of each received integer. 
// After the inbound channel is closed and this stage has sent all the values downstream, it closes the outbound channel:
func sq(in <-chan int) <- chan int{
	out := make(chan int)

	go func() {
		for n := range in {
			out <- n * n
		}
		close(out)
	}()

	return out
}

func test_channel_single_direction_channel() {

	// The main function sets up the pipeline and runs the final stage: 
	// it receives values from the second stage and prints each one, until the channel is closed:
	c := gen(1, 2, 3, 4, 5, 6, 7, 8)
	out := sq(c)

	n := 0
	for {
		select {
		case n = <- out:
			fmt.Println(n)

		}

		if n == 64 {
			// Can't make sure Chan status, so have to use this way to jump
			break
		}
	}

	// Since sq has the same type for its inbound and outbound channels, we can compose it any number of times. 
	// We can also rewrite main as a range loop, like the other stages:
	for n := range sq(sq(gen(3, 4))) {
		fmt.Println(n)
	}

	
	fmt.Println("--end--")
}

func test_channel() {

	test_chann()

	test_chann_select()

	
}