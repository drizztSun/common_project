package main

import (
	"fmt"
	"time"
	"errors"
)

func test_basic_time() {

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
	}();

	for {
		select {
		case <- time.After(10 * time.Second):
			fmt.Println("time routine output per 5 seconds")
			continue
		case <- done:
			fmt.Println("another routin is done")
		}
		break
	}


	t := time.NewTimer(50 * time.Second)
	for n := range time.Tick(10 * time.Second) {
		select {
		case <- t.C:
			continue
		default:
			fmt.Printf("Get update %v\n", n)
		}
		break
	}
	
}

func test_stopped_timer() {

	var (
		err error
		statusCode int
	)

	fmt.Printf("Error: %v, code: %d\n", err, statusCode)

	err = errors.New("Something")
	statusCode = 100

	fmt.Printf("Error: %v, code: %d\n", err, statusCode)

	t1 := time.NewTimer(0)
	t1.Stop()

	Wrapper := func (a *time.Timer) <-chan time.Time {
		return a.C
	}


	t2 := time.NewTimer(5 * time.Second)

	select {
	case <-Wrapper(t1):
		fmt.Println("Wait t1 stopped timer")

	case <-Wrapper(t2):
		fmt.Println("Wait t2 triggered")

	case <- time.After(10 * time.Second):
		fmt.Println("after 10 seconds")
	}
}

func test_time() {

	//test_basic_time()

	test_stopped_timer()
}