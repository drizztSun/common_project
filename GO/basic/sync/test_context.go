package main

import (
	"fmt"
	"time"
	"context"

	"golang.org/x/sync/errgroup"
)

// When should you use context.Context?
// 1) Every RPC call should have an ability to time out
// 2) This is just reasonable API design
// 3) Not just timeout, since you also need to be able to end an RPC call early if the result is not longer needed.
// 4) context.Context is the Go standard solution
// 5) Any function that can block or take a long time to finish should have a context.Context

// How to create context
// Use context.Background() at the beginning of an RPC call.
// If you don't have a context, and need to call a context function, use context.TODO().
// Give sub requests their own sub context if they need other timeouts.

// Where to put a context
// Think of a context flowing through your program, like water in a river
// Ideally. context live with calll stack
// Do not store the context in a struct
// Ony exepction is when the struct is a request struct(http.Request)
// Request strcuts should end with a request
// Context instance should be unreferenced when the RPC call is finished
// Context dies when the request dies

// Context package cavets
// Create pattern of closing contexts
// Especially timeout contexts
// if a conext GCs, and isn't canceled, you probably did something wrong

// When to cancel a context early
// When you don;t caere about spaened logic
// golang.org/x/sync/errgroup as example
// errgroup uses context to create an RPC cancellation abstraction
// Great deep dive into ideal context usage

func test_basic_context() {

	ctx := context.Background()
	ctx2, cancel := context.WithCancel(ctx)
	defer cancel()

	ctx3, _ := context.WithTimeout(ctx2, time.Second * 5)
	ctx4, _ := context.WithTimeout(ctx3, time.Second * 3)
	ctx5, _ := context.WithTimeout(ctx3, time.Second * 6)
	ctx6 := context.WithValue(ctx5, "UserID", 12)

	ctx6.Done()
	ctx4.Done()
}


// Package context defines the Context type, which carries deadlines, cancelation signals, 
// and other request-scoped values across API boundaries and between processes.

// Incoming requests to a server should create a Context, and outgoing calls to servers should accept a Context. 
// The chain of function calls between them must propagate the Context, 
// optionally replacing it with a derived Context created using WithCancel, WithDeadline, WithTimeout, or WithValue.
// When a Context is canceled, all Contexts derived from it are also canceled.
func test_basic_context_cancel() {
	// gen generates integers in a separate goroutine and
	// sends them to the returned channel.
	// The callers of gen need to cancel the context once
	// they are done consuming generated integers not to leak
	// the internal goroutine started by gen.
	gen := func(ctx context.Context) <- chan int {
		dst := make(chan int)
		n := 1
		go func() {
			for {
				select {
				case <- ctx.Done():
						return // returning not to leak the goroutine
				case dst<-n:
					n++
				}				
			}
		}()
		return dst
	}

	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()
	for n := range gen(ctx){
		fmt.Println(n)
		if n == 5 {
			break
		}
	}
}

func test_basic_context_deadline() {

	d := time.Now().Add(50 * time.Millisecond)
	ctx, cancel := context.WithDeadline(context.Background(), d)
	defer cancel()


	// Even though ctx will be expired, it is good practice to call its
	// cancelation function in any case. Failure to do so may keep the
	// context and its parent alive longer than necessary.
	select {
	case <- time.After(1 * time.Second):
		fmt.Println("overslept")
	case <- ctx.Done():
		fmt.Println("Err : %s", ctx.Err()) //context deadline exceeded
	}
}

func test_basic_context_timeout() {
	// Pass a context with a timeout to tell a blocking function that it
	// should abandon its work after the timeout elapses.
	ctx, cancel := context.WithTimeout(context.Background(), 50 * time.Millisecond)
	defer cancel()

	select {
	case <-time.After(1 * time.Second):
		fmt.Println("overslept")
	case <-ctx.Done():
		fmt.Println("Err : %s", ctx.Err()) //context deadline exceeded
	}
}

func test_basic_context_withValue() {
	type contextKey string
	f := func(ctx context.Context, key contextKey) {
		if v := ctx.Value(key); v != nil {
			fmt.Println("found value: ", v)
		}
		fmt.Println("key not found: ", key)
	} 

	k := contextKey("language")
	ctx := context.WithValue(context.Background(), k, "GO")

	f(ctx, k)
	f(ctx, contextKey("letter"))
}


func test_context() {

	fmt.Println("--- test_context ---")
}