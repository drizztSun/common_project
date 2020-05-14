package main

/*
#cgo CFLAGS: -I .
#cgo LDFLAGS: -L . -lclibrary

#include "clibrary.h"

int callOnMeGo_cgo(int in); // Forward declaration.
*/
import "C"

import (
	"fmt"
	"unsafe"
)

//export callOnMeGo
func callOnMeGo(in int) int {
	fmt.Printf("Go.callOnMeGo(): called with arg = %d\n", in)
	return in + 1
}

func test_goprog() {
	fmt.Printf("Go.main(): calling C function with callback to us\n")
	C.some_c_func((C.callback_fcn)(unsafe.Pointer(C.callOnMeGo_cgo)))
}

/*

Function pointer callbacks
C code can call exported Go functions with their explicit name. But if a C-program wants a function pointer, a gateway function has to be written.
This is because we can't take the address of a Go function and give that to C-code since the cgo tool will generate a stub in C that should be called.
The following example shows how to integrate with C code wanting a function pointer of a give type.

Place these source files under $GOPATH/src/ccallbacks/. Compile and run with:



$ gcc -c clibrary.c
$ ar cru libclibrary.a clibrary.o
$ go build
$ ./ccallbacks
*/
