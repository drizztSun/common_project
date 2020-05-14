package main

/*
#include <stdio.h>
#include <stdlib.h>

void myprint(char* s) {
	printf("%s\n", s);
}

int a[20] = {1};

int* getThisArray() {
	return a;
}

int getThisArrayLength() {
	return sizeof(a);
}

*/
import "C"

import (
	"fmt"
	"unsafe"
)

func test_cgo_basic() {
	cs := C.CString("Hello from stdio\n")
	C.myprint(cs)
	C.free(unsafe.Pointer(cs))

	// Turning C arrays into Go slices
	// C arrays are typically either null-terminated or have a length kept elsewhere.

	// Go provides the following function to make a new Go byte slice from a C array:

	// 		func C.GoBytes(cArray unsafe.Pointer, length C.int) []byte
	// To create a Go slice backed by a C array (without copying the original data),
	// one needs to acquire this length at runtime and use a type conversion to a pointer to a very big array and then slice it to the length
	// that you want (also remember to set the cap if you're using Go 1.2 or later), for example (see http://play.golang.org/p/XuC0xqtAIC for a runnable example):

	// It is important to keep in mind that the Go garbage collector will not interact with this data, and that if it is freed from the C side of things,
	// the behavior of any Go code using the slice is nondeterministic.
	var i uint64 = 0xdeedbeef01020304
	slice := (*[1 << 30]byte)(unsafe.Pointer(&i))[:8:8]
	fmt.Println(slice)

	var theCArray *C.int = C.getThisArray()
	length := C.getThisArrayLength()
	whole_slice := (*[1 << 28]C.int)(unsafe.Pointer(theCArray))[:length:length]
	fmt.Println("%v", whole_slice)

}

/*
Go strings and C strings
Go strings and C strings are different. Go strings are the combination of a length and a pointer to the first character in the string.
C strings are just the pointer to the first character, and are terminated by the first instance of the null character, '\0'.

Go provides means to go from one to another in the form of the following three functions:

func C.CString(goString string) *C.char
func C.GoString(cString *C.char) string
func C.GoStringN(cString *C.char, length C.int) string

One important thing to remember is that C.CString() will allocate a new string of the appropriate length, and return it.
That means the C string is not going to be garbage collected and it is up to you to free it. A standard way to do this follows.

Of course, you aren't required to use defer to call C.free(). You can free the C string whenever you like, but it is your responsibility to make sure it happens.
*/


/*

Common Pitfalls
Struct Alignment Issues
As Go doesn't support packed struct (e.g., structs where maximum alignment is 1 byte), you can't use packed C struct in Go. Even if your program passes compilation, it won't do what you want. To use it, you have to read/write the struct as byte array/slice.

Another problem is that some types has lower alignment requirement than their counterpart in Go, and if that type happens to be aligned in C but not in Go rules, that struct simply can't be represented in Go. An example is this (issue 7560):

struct T {
    uint32_t pad;
    complex float x;
};
Go's complex64 has an alignment of 8-byte, where as C has only 4-byte (because C treats the complex float internally as a struct { float real; float imag; }, not a basic type), this T struct simply doesn't have a Go representation.
For this case, if you control the layout of the struct, move the complex float so that it is also aligned to 8-byte is better, and if you're not willing to move it, use this form will force it to align to 8-byte (and waste 4-byte):

struct T {
   uint32_t pad;
   __attribute__((align(8))) complex float x;
};
However, if you don't control the struct layout, you will have to define accessor C functions for that struct because cgo won't be able to translate that struct into equivalent Go struct.

//export and definition in preamble
If a Go source file uses any //export directives, then the C code in the comment may only include declarations (extern int f();), not definitions (int f() { return 1; } or int n;).
Note: you can use static inline trick to work around this restriction for tiny functions defined in the preamble (see above for a complete example).

Windows
In order to use cgo on Windows, you'll also need to first install a gcc compiler (for instance, mingw-w64) and have gcc.exe (etc.) in your PATH environment variable before compiling with cgo will work.

environmental variables
Go os.Getenv() doesn't see variables set by C.setenv()


*/