package main

import (
	"fmt"
	"sync"
)

/*
	Once is an object that will perform exactly one action.
	func (*Once) Do
	func (o *Once) Do(f func())
	Do calls the function f if and only if Do is being called for the first time for this instance of Once. In other words, given

	var once Once
	if once.Do(f) is called multiple times, only the first call will invoke f, even if f has a different value in each invocation. A new instance of Once is required for each function to execute.

	Do is intended for initialization that must be run exactly once. Since f is niladic, it may be necessary to use a function literal to capture the arguments to a function to be invoked by Do:

	config.once.Do(func() { config.init(filename) })
	Because no call to Do returns until the one call to f returns, if f causes Do to be called, it will deadlock.

	If f panics, Do considers it to have returned; future calls of Do return without calling f.
*/
func test_once() {

	var one sync.Once

	onceBody := func() {
		fmt.Println("Only once")
	}

	done := make(chan bool)

	for i := 0; i < 10; i++ {
		go func() {

			// Do calls the function f if and only if Do is being called for the first time for this instance of Once.
			// In other words, given
			one.Do(onceBody)
			done <- true
		}()
	}

	for i := 0; i < 10; i++ {
		<-done
	}
}
