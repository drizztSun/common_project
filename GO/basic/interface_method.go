package main

import (
	"fmt"
	"io"
	"math"
	"os"
	"strings"
	"time"
)

//* Interfaces
// An interface type is defined as a set of method signatures.
// A value of interface type can hold any value that implements those methods

// Interfaces are implemented implicitly
// A type implements an interface by implementing its methods. There is no explicit declaration of intent, no "implements" keyword.
// Implicit interfaces decouple the definition of an interface from its implementation, which could then appear in any package without prearrangement..

type Vertex struct {
	X, Y int
}

type Myfloat float64

type Abser interface {
	Abs() float64
}

func (v *Vertex) Abs() float64 {
	return math.Sqrt(float64(v.X*v.X + v.Y*v.Y))
}

func (f Myfloat) Abs() float64 {
	if f < 0 {
		return float64(-f)
	}
	return math.Sqrt(float64(f * f))
}

// Pointers to Interfaces
// You almost never need a pointer to an interface. You should be passing interfaces as values—the underlying data can still be a pointer.

// An interface is two fields:

// 1) A pointer to some type-specific information. You can think of this as "type."
// 2) Data pointer. If the data stored is a pointer, it’s stored directly. If the data stored is a value, then a pointer to the value is stored.
// If you want interface methods to modify the underlying data, you must use a pointer.

// Receivers and Interfaces
// Methods with value receivers can be called on pointers as well as values.

type S struct {
	data string
}

func (s S) Read() string {
	return s.data
}

func (s *S) Write(str string) {
	s.data = str
}

type F interface {
	f()
}

type S1 struct{}

func (s S1) f() {}

type S2 struct{}

func (s *S2) f() {}

func test_interface_and_receivers() {

	// Receivers and Interfaces
	{
		//Methods with value receivers can be called on pointers as well as values.

		sVals := map[int]S{1: {"A"}}

		// You can only call Read using a value
		sVals[1].Read()

		// This will not compile:
		//  sVals[1].Write("test")

		sPtrs := map[int]*S{1: {"A"}}

		// You can call both Read and Write using a pointer
		sPtrs[1].Read()
		sPtrs[1].Write("test")
	}

	{
		// Similarly, an interface can be satisfied by a pointer, even if the method has a value receiver.
		s1Val := S1{}
		s1Ptr := &S1{}
		s2Val := S2{}
		s2Ptr := &S2{}

		var i F
		i = s1Val
		i = s1Ptr
		i = s2Ptr

		s2Val.f()

		// The following doesn't compile, since s2Val is a value, and there is no value receiver for f.
		//   i = s2Val
	}

}

// *** Stringers
// One of the most ubiquitous interfaces is Stringer defined by the fmt package.

// type Stringer interface {
//		String() string
// }
// A Stringer is a type that can describe itself as a string. The fmt package (and many others) look for this interface to print values.

type Person struct {
	Name string
	Age  int
}

func (p Person) String() string {
	var s string
	fmt.Sscanf(s, "%s (%d years)", p.Name, p.Age)
	return s
}

type IPAddr [4]byte

func (p IPAddr) String() string {
	return fmt.Sprintf("(%v, %v, %v, %v)", p[0], p[1], p[2], p[3])
}

// *** Errors
// Go programs express error state with error values.

//The error type is a built-in interface similar to fmt.Stringer:

// type error interface {
//     Error() string
//	}

//	Functions often return an error value, and calling code should handle errors by testing whether the error equals nil.

//	i, err := strconv.Atoi("42")
//	if err != nil {
//	    fmt.Printf("couldn't convert number: %v\n", err)
//	    return
//	}
//	fmt.Println("Converted integer:", i)
//	A nil error denotes success; a non-nil error denotes failure.

type MyError struct {
	When time.Time
	What string
}

func (e *MyError) Error() string {
	return fmt.Sprintf("at %v, %s", e.When, e.What)
}

func run(a int) (int, error) {

	if a%2 == 1 {

		return 1, nil
	} else {

		return 3, &MyError{
			time.Now(),
			"it didn't work",
		}
	}
}

// *** Readers
// The io package specifies the io.Reader interface, which represents the read end of a stream of data.
// The Go standard library contains many implementations of these interfaces, including files, network connections, compressors, ciphers, and others.
// The io.Reader interface has a Read method:

// func (T) Read(b []byte) (n int, err error)
// Read populates the given byte slice with data and returns the number of bytes populated and an error value. It returns an io.EOF error when the stream ends.
// The example code creates a strings.Reader and consumes its output 8 bytes at a time.
type MyReader struct{}

func (v MyReader) Read(s []byte) (n int, err error) {
	s = s[:cap(s)]
	for i := range s {
		s[i] = 'A'
	}
	return cap(s), nil
}

// go-exercices/8-exercise-rot-reader.go
type rot13Reader struct {
	r io.Reader
}

func (rot *rot13Reader) Read(b []byte) (n int, err error) {
	rot.r.Read(b)

	for i := range b {
		if (b[i] >= 'A' && b[i] <= 'M') || (b[i] >= 'a' && b[i] <= 'm') {
			b[i] += 13
		} else if (b[i] >= 'N' && b[i] <= 'Z') || (b[i] >= 'n' && b[i] <= 'z') {
			b[i] -= 13
		}
	}

	return n, err
}

func callInterface() {

	var a Abser
	f := Myfloat(1.0)
	v := Vertex{1, 2}

	a = f  // MyFloat implement the Abser
	a = &v // *Vertex implement the Abser

	//a = v // v is Vertex and *Vertex, not implement the Abs()

	fmt.Println(a.Abs())

	// a nil interface
	var i interface{}
	fmt.Println("v： %v. t: %T", i, i)

	// Type assertions
	// A type assertion provides access to an interface value's underlying concrete value.

	// t := i.(T)
	// This statement asserts that the interface value i holds the concrete type T and assigns the underlying T value to the variable t.

	// If i does not hold a T, the statement will trigger a panic.

	// To test whether an interface value holds a specific type, a type assertion can return two values: the underlying value and a boolean value that reports whether the assertion succeeded.

	// t, ok := i.(T)
	// If i holds a T, then t will be the underlying value and ok will be true.
	// If not, ok will be false and t will be the zero value of type T, and no panic occurs.
	// Note the similarity between this syntax and that of reading from a map.
	{
		var i interface{} = "hello"
		s := i.(string)
		fmt.Println(s) // hello

		s, ok := i.(string)
		fmt.Println(s, ok) // hello true

		// s, ok = i.(float64)
		fmt.Println(s, ok) // 0 false
	}

	// f = i.(float64) assert error

	// *** Type switches
	// A type switch is a construct that permits several type assertions in series.
	// A type switch is like a regular switch statement, but the cases in a type switch specify types (not values), and those values are compared against the type of the value held by the given interface value.

	// switch v := i.(type) {
	// case T:
	// here v has type T
	// case S:
	// here v has type S
	// default:
	// no match; here v has the same type as i
	// }
	// The declaration in a type switch has the same syntax as a type assertion i.(T), but the specific type T is replaced with the keyword type.
	// This switch statement tests whether the interface value i holds a value of type T or S. In each of the T and S cases, the variable v will be of type T or S respectively and hold the value held by i. In the default case (where there is no match), the variable v is of the same interface type and value as i.

	printtype := func(v interface{}) {

		switch i := v.(type) {
		case int:
			fmt.Println("Twice %v is %v", i, 2*i)
		case string:
			fmt.Println("%q is %v bytes long", i, len(i))
		default:
			fmt.Println("I don;t know about type %T", i)
		}
	}

	printtype(21)
	printtype("Hello world")
	printtype(true)

	// *** string
	{
		a := Person{"Arthur Dent", 42}
		b := Person{"Zaphod Beeblebrox", 9001}

		fmt.Println(a, z)
		fmt.Println(b)
		host := map[string]IPAddr{
			"loopback":  {127, 0, 0, 1},
			"googleDNS": {8, 8, 8, 8},
		}

		for name, ip := range host {
			fmt.Println("%V, %V", name, ip)
		}
	}

	// Error
	if i, err := run(3); err != nil {
		fmt.Println(err)
	} else {
		fmt.Println("succeed! : ", i)
	}

	{
		// Reader
		f := strings.NewReader("Hello, Reader!")
		b := make([]byte, 8)

		for {
			n, err := f.Read(b)

			fmt.Println("n=%v, err=%v b=%v", n, err, b)
			fmt.Println("b[:n] = %q", b[:n])

			if err == io.EOF {
				break
			}
		}
	}

	r := rot13Reader{strings.NewReader("Lbh penpxrq gur pbqr!")}
	io.Copy(os.Stdout, &r)

}
