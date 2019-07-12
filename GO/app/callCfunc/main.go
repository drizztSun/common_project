package main

/*
The import "C" line allows us to interface with C code through our go program. 
The comments above it is actual C code that can be consumed by the rest of the code. 
We include stdlib.h so that we can call malloc and free; and greeter.h for our greeter function. 
In addition to this, we can add directives for cgo to use. For instance, 
adding the line // #cgo CFLAGS: -g -Wall compiles the C files with the gcc options -g(enable debug symbols) 
and -Wall(enable all warnings) enabled. Notice how the line for importing C is outside the import block.
Without performing the imports this way, the includes and other directives won’t be considered.
*/

// #cgo CFLAGS: -g -Wall
// #include <stdlib.h>
// #include "func.h"

import "C"
import (
	"fmt"
	"unsafe"
)

/*
Go provides a pseudo package called “C” to interface with C libraries. 
Its not very straightforward how to do this though. In this tutorial, we’ll go over creating a simple C function,
 and calling it from go. After that, we’ll move on to a slightly more complex example involving C structs.

Keep in mind that using cgo is not always best the course to take. You’ll be losing many of the type safety 
benefits and cross-compilation targets that go provides. It should be used as a last resort: 
when you’re absolutely sure that it is not possible to achieve your objective in native go code.

We will be creating a C library that generates a greeting message, and interfacing to it through go.
*/

func main() {

	fmt.Println("--- start call C func ---")

	/*
	C.CString is a cgo function that takes a go string and returns a pointer to a C char, ie: *C.char. 
	This allows us to pass strings to C code. Note that this function uses malloc to create the space for the string, 
	so we need to call the C function free once we are done with the string to prevent memory leaks. 
	We use C.int to create an integer that can be passed to C code.
	*/
	name := C.CString("Gopher")
	defer C.free(unsafe.Pointer(name))

	year := C.int(2018)


	/*
	The function C.malloc returns an object of type unsafe.Pointer. 
	An unsafe pointer can be cast to a pointer of any type. 
	We’ll be casting it to a pointer to char before passing it to our greet function.
	*/
	ptr := C.malloc(C.sizeof_char * 1024)
	defer C.free(unsafe.Pointer(ptr))

	/*
	Here, we call the greet function from our C code. 
	We pass the the name, the year, and the pointer to the output buffer(cast to *C.char since 
	that is what out library function expects). Our function returns the size of the greeting message.
	*/
	size := C.greet(name, year, (*C.char)(ptr))


	/*
	Here, we convert the C buffer to a go []byte object. 
	The cgo function C.GoBytes does this for us, using the pointer and the size of the written data. 
	The byte slice returned does not share memory with the bytes we allocated using malloc. 
	We can safely call free on ptr and continue to use the byte slice returned by C.GoBytes.
	*/
	b := C.GoBytes(ptr, size)
	fmt.Println(string(b))


	fmt.Println(" --- call struct --- ")

	/**
	The only differences are in how we created a struct, and how we called the function. 
	We can access any C struct using C.struct_ followed by the name of the struct. 
	We can then initialize the members as we would in a normal go struct. 
	In this case, we set up the name and year arguments.
	*/
	g := C.struct_Greeter {
		name: name,
		year: year,
	}

	name := C.CString("Gppher")
	defer C.free(unsafe.Pointer(name))

	year = C.int(2019)

	size = C.greet_s(&g, (*C.char)(ptr))

	b = C.GoBytes(ptr, size)
	fmt.Println(string(b))


	fmt.Println("--- end call C func ---")
}

/*
Always keep in mind: you may not need cgo. Evaluate all your options, and try sticking with a pure go implementation. 
If you decide that you do need to use cgo, and you need more information, the cgo documentation is a good place to look.
*/