package main

import (
	"errors"
	"fmt"
	"time"
)

func test_basic_time() {

	fmt.Println("--- start test_basic_time ---")

	done := make(chan struct{})

	go func() {
		t1 := time.Now()

		fmt.Println("start a routine and sleep 1 minutes")

		// current routine will sleep 30 seconds
		time.Sleep(time.Second * 30)

		fmt.Println("wait up after 30 seconds")

		done <- struct{}{}

		t2 := time.Now()
		fmt.Println("Running time is ", t2.Sub(t1))
	}()

	for {
		select {
		case <-time.After(10 * time.Second):
			fmt.Println("time routine output per 5 seconds")
			continue
		case <-done:
			fmt.Println("another routin is done")
		}
		break
	}

	t := time.NewTimer(50 * time.Second)
	for n := range time.Tick(10 * time.Second) {
		// Tick is a convenience wrapper for NewTicker providing access to the ticking channel only.
		// While Tick is useful for clients that have no need to shut down the Ticker,
		// be aware that without a way to shut it down the underlying Ticker cannot be recovered by the garbage collector;
		// it "leaks". Unlike NewTicker, Tick will return nil if d <= 0.
		select {
		case <-t.C:
			fmt.Printf("Timer C is on %v\n", t.C)
			break
			// A "break" statement terminates execution of the innermost "for", "switch", or "select" statement within the same function.
		default:
			fmt.Printf("Get update %v\n", n)
			continue
			// A "continue" statement begins the next iteration of the innermost "for" loop at its post statement.
			// The "for" loop must be within the same function.
		}
		break // break from for-loop
	}

	t1 := time.NewTimer(30 * time.Second)
	for n := range time.Tick(5 * time.Second) {
		select {
		case <-t1.C:
			fmt.Println("Time C is on %v\n", t.C)
			break
		case <-time.After(20 * time.Second):
			if !t1.Stop() {
				r := <-t1.C
				fmt.Println("stopped the timer %d", r)
			}
		default:
			fmt.Printf("Get update %v\n", n)
			continue
		}
		break
	}

	fmt.Println("--- end test_basic_time ---")
}

func test_advanced_timer() {

	fmt.Println("--- test_advanced_timer ---")

	s := make(chan struct{})
	t := time.AfterFunc(20*time.Second, func() {
		fmt.Println("starting the goroutine of function")

		s <- struct{}{}
	})

	for n := range time.Tick(5 * time.Second) {

		select {
		case <-s:
			fmt.Printf("timeup for on %v\n", t.C)
			break
		default:
			fmt.Printf("get update %v\n", n)
			continue
		}
		break
	}

	t1 := time.AfterFunc(30*time.Second, func() {
		fmt.Println("Starting the goroutine after 30 seconds")
		s <- struct{}{}
	})
	for n := range time.Tick((5 * time.Second)) {

		select {
		case <-s:
			fmt.Println("timeout on %v\n", t1.C)
			break
		case <-time.After(10 * time.Second):
			fmt.Println("time up to stop timer t1")
			if t1.Stop() == true {
				fmt.Print("Stop the timer after func")
			}
			break
		default:
			fmt.Println("get update %d \n", n)
			continue
		}
		break
	}

	fmt.Println("--- end test_advanced_timer ---")
}

func test_stopped_timer() {

	var (
		err        error
		statusCode int
	)

	fmt.Printf("Error: %v, code: %d\n", err, statusCode)

	err = errors.New("Something")
	statusCode = 100

	fmt.Printf("Error: %v, code: %d\n", err, statusCode)

	t1 := time.NewTimer(0)
	t1.Stop()

	Wrapper := func(a *time.Timer) <-chan time.Time {
		return a.C
	}

	t2 := time.NewTimer(5 * time.Second)

	select {
	case <-Wrapper(t1):
		fmt.Println("Wait t1 stopped timer")

	case <-Wrapper(t2):
		fmt.Println("Wait t2 triggered")

	case <-time.After(10 * time.Second):
		fmt.Println("after 10 seconds")
	}
}

func test_time() {

	test_basic_time()

	test_stopped_timer()

	test_advanced_timer()
}
