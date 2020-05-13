package main

/*
If a Go source file imports "C", it is using cgo.
The Go file will have access to anything appearing in the comment immediately preceding the line import "C",
and will be linked against all other cgo comments in other Go files, and all C files included in the build process.

Note that there must be no blank lines in between the cgo comment and the import statement.

To access a symbol originating from the C side, use the package name C. That is, if you want to call the C function printf() from Go code, you write C.printf().
*/

/*
#include <stdio.h>
#include <stdlib.h>

void myprint(char* s) {
	printf("%s\n", s);
}

extern void ACFunction();
*/
import (
	"C"
	"unsafe"

	"fmt"
)

/*
Calling Go functions from C
It is possible to call both top-level Go functions and function variables from C code invoked from Go code using cgo.

Global functions
Go makes its functions available to C code through use of a special //export comment.
Note: you can't define any C functions in preamble if you're using exports
*/

// export AGoFunction
func AGOFunction() {
	fmt.Println("AGoFunction example")
}

func test_call_c_functin() {
	C.ACFunction()
}

func test_c_call_basic() {
	cs := C.CString("Hello from studio\n")
	C.myprint(cs)
	C.free(unsafe.Pointer(cs))
}

func Test_cgo_call() {

	test_c_call_basic()

	test_call_c_functin()
}
