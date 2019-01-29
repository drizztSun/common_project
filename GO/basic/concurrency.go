package main

import (
	"fmt"
	"sync"
	"time"
)

// *** Goroutines
// A goroutine is a lightweight thread managed by the Go runtime.

// go f(x, y, z)
// starts a new goroutine running

// f(x, y, z)
// The evaluation of f, x, y, and z happens in the current goroutine and the execution of f happens in the new goroutine.
// Goroutines run in the same address space, so access to shared memory must be synchronized.
// The sync package provides useful primitives, although you won't need them much in Go as there are other primitives. (See the next slide.)

func say(s string) {
	for i := 0; i < 5; i++ {
		fmt.Println(s)
	}
}

// *** Channels
// Channels are a typed conduit through which you can send and receive values with the channel operator, <-.

// ch <- v    // Send v to channel ch.
// v := <-ch  // Receive from ch, and
// assign value to v.
// (The data flows in the direction of the arrow.)
// Like maps and slices, channels must be created before use:

// ch := make(chan int)
// By default, sends and receives block until the other side is ready. This allows goroutines to synchronize without explicit locks or condition variables.
// The example code sums the numbers in a slice, distributing the work between two goroutines. Once both goroutines have completed their computation, it calculates the final result.

func sum(s []int, c chan int) {
	sum := 0
	for i := range s {
		sum += i
	}
	c <- sum // send sum to c
}

// *** Range and Close
// A sender can close a channel to indicate that no more values will be sent. Receivers can test whether a channel has been closed by assigning a second parameter to the receive expression: after

// v, ok := <-ch
// ok is false if there are no more values to receive and the channel is closed.

// The loop for i := range c receives values from the channel repeatedly until it is closed.
// Note: Only the sender should close a channel, never the receiver. Sending on a closed channel will cause a panic.
// Another note: Channels aren't like files; you don't usually need to close them. Closing is only necessary when the receiver must be told there are no more values coming, such as to terminate a range loop.

func fibonacci1(n int, c chan int) {
	x, y := 0, 1
	for i := 0; i < n; i++ {
		c <- x
		x, y = y, x+y
	}
	close(c)
}

// *** Select
// The select statement lets a goroutine wait on multiple communication operations.
// A select blocks until one of its cases can run, then it executes that case. It chooses one at random if multiple are ready.

func fibonacci_select(c, quit chan int) {
	x, y := 0, 1

	for {
		select {
		case c <- x:
			x, y = y, x+y
		case <-quit:
			fmt.Println("quite")
			return
		}
	}

}

// *** sync.Mutex
// We've seen how channels are great for communication among goroutines.

// But what if we don't need communication? What if we just want to make sure only one goroutine can access a variable at a time to avoid conflicts?

// This concept is called mutual exclusion, and the conventional name for the data structure that provides it is mutex.

// Go's standard library provides mutual exclusion with sync.Mutex and its two methods:

// Lock
// Unlock
// We can define a block of code to be executed in mutual exclusion by surrounding it with a call to Lock and Unlock as shown on the Inc method.

// We can also use defer to ensure the mutex will be unlocked as in the Value method.

type safeCounter struct {
	v   map[string]int
	mux sync.Mutex
}

func (c *safeCounter) Inc(key string) {
	c.mux.Lock()
	c.v[key]++
	c.mux.Unlock()
}

func (c *safeCounter) Value(key string) (int, error) {
	c.mux.Lock()
	defer c.mux.Unlock()
	return c.v[key], nil
}

func TestConcurrency() {

	// *** Goroutines
	// starts a new thread
	{
		go say("hello")

		say("world")
	}

	// *** channels
	{
		s := []int{7, 2, 8, -9, 4, 0}
		c := make(chan int)
		go sum(s[:len(s)/2], c)
		go sum(s[len(s)/2:], c)

		x, y := <-c, <-c // receive from c

		fmt.Println(x, y, x+y)
	}

	// Buffered Channels
	// Channels can be buffered. Provide the buffer length as the second argument to make to initialize a buffered channel:

	// ch := make(chan int, 100)
	// Sends to a buffered channel block only when the buffer is full. Receives block when the buffer is empty.
	// Modify the example to overfill the buffer and see what happens.
	{
		ch := make(chan int, 2)
		ch <- 1
		ch <- 2
		fmt.Println(<-ch)
		fmt.Println(<-ch)
	}

	// *** Range and Close
	{
		c := make(chan int, 10)
		go fibonacci1(cap(c), c)

		for i := range c {
			fmt.Println(i)
		}

	}

	// *** select
	{
		c := make(chan int)
		quit := make(chan int)

		go func() {
			for i := 0; i < 10; i++ {
				fmt.Println(<-c)
			}
			quit <- 0
		}()

		fibonacci_select(c, quit)
	}

	// *** Default Selection
	// The default case in a select is run if no other case is ready.
	// Use a default case to try a send or receive without blocking:

	// select {
	// case i := <-c:
	// use i
	// default:
	// receiving from c would block
	// }
	{
		tick := time.Tick(100 * time.Millisecond)
		boom := time.After(500 * time.Millisecond)

		for {
			select {
			case <-tick:
				fmt.Println("tick. ")
			case <-boom:
				fmt.Println("BOOM !")
			default:
				fmt.Println(".......")
				time.Sleep(50 * time.Microsecond)
			}
		}
	}

	// *** sync.Mutex
	{
		v := safeCounter{v: make(map[string]int)}
		for i := 0; i < 1000; i++ {
			go v.Inc("somekey")
		}

		time.Sleep(time.Second)
		fmt.Println(c.Value("somekey"))
	}

}
