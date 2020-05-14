package main

/*
extern void go_callback_int(int foo, int p1);

// normally you will have to define function or variables
// in another separate C file to avoid the multiple definition
// errors, however, using "static inline" is a nice workaround
// for simple functions like this one.
static inline void CallMyFunction(int foo) {
	go_callback_int(foo, 5);
}
*/
import "C"
import (
	"fmt"
	"sync"
)

/*
Function variables
The following code shows an example of invoking a Go callback from C code.
Because of the pointer passing rules Go code can not pass a function value directly to C.
Instead it is necessary to use an indirection. This example uses a registry with a mutex,
but there are many other ways to map from a value that can be passed to C to a Go function.
*/

//export go_callback_int
func go_callback_int(foo C.int, p1 C.int) {
	fn := lookup(int(foo))
	fn(p1)
}

func MyCallback(x C.int) {
	fmt.Println("callback with", x)
}

func test_cgo_func() {
	i := register(MyCallback)
	C.CallMyFunction(C.int(i))
	unregister(i)
}

var mu sync.Mutex
var index int
var fns = make(map[int]func(C.int))

func register(fn func(C.int)) int {
	mu.Lock()
	defer mu.Unlock()
	index++
	for fns[index] != nil {
		index++
	}
	fns[index] = fn
	return index
}

func lookup(i int) func(C.int) {
	mu.Lock()
	defer mu.Unlock()
	return fns[i]
}

func unregister(i int) {
	mu.Lock()
	defer mu.Unlock()
	delete(fns, i)
}
