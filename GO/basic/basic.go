package main

import (
	"fmt"
	"math"
	"math/cmplx"
	"math/rand"
	"runtime"
	"strings"
	"time"
)

// Basic types
// Go's basic types are
//
// GO basic type
// bool string
// int  int8  int16  int32  int64
// uint uint8 uint16 uint32 uint64 uintptr
// byte // alias for uint8
// rune // alias for int32
// represents a Unicode code point
// float32 float64
// complex64 complex128

// Zero values
// Variables declared without an explicit initial value are given their zero value.

// The zero value is:

// 0 for numeric types,
// false for the boolean type, and
// "" (the empty string) for strings.

// 'var' to declare the varaible at functin or package level
var (
	ToBe   bool       = false                // exported
	MaxInt uint64     = 1<<64 - 1            // exported, because its first letter is upper one
	z      complex128 = cmplx.Sqrt(-5 + 12i) // non-exported, because of lower one
)

const PI = 3.14

func add(a int, b int) int {
	return a + b
}

func substract(a, b int) int {
	return a - b
}

// return multiple values
func swap(a, b string) (string, string) {
	return b, a
}

// Named return values
func split(sum int) (x, y int) {
	x = sum * 4 / 9
	y = sum - x
	return
}

func UsePointer() {
	// Points
	// Go has pointers. A pointer holds the memory address of a value.

	// The type *T is a pointer to a T value. Its zero value is nil.

	// var p *int
	// The & operator generates a pointer to its operand.

	// i := 42
	// p = &i
	// The * operator denotes the pointer's underlying value.

	// fmt.Println(*p) // read i through the pointer p
	// *p = 21         // set i through the pointer p
	// This is known as "dereferencing" or "indirecting".

	// Unlike C, Go has no pointer arithmetic.

	i, j := 42, 2701
	p := &i
	fmt.Println("p is ", *p)

	*p = 21
	fmt.Println("now P is ", *p)

	p = &j
	*p = *p / 37
	fmt.Println("J is ", *p)
}

/*
type Vertex struct {
	X int
	Y int
}

func UseStruct() {

	// using struct Vertex
	fmt.Println(Vertex{1, 2})

	v := Vertex{1, 2}
	v.X = 100
	fmt.Println(v)

	// Struct fields can be accessed through a struct pointer.
	// To access the field X of a struct when we have the struct pointer p we could write (*p).X. However, that notation is cumbersome,
	// so the language permits us instead to write just p.X, without the explicit dereference.
	p := &v
	p.X = 200
	fmt.Println(*p)

	// A struct literal denotes a newly allocated struct value by listing the values of its fields.
	// You can list just a subset of fields by using the Name: syntax. (And the order of named fields is irrelevant.)
	// The special prefix & returns a pointer to the struct value.
	var (
		v1 = Vertex{1, 2}  // has type Vertex
		v2 = Vertex{X: 1}  // Y:0 is implicit
		v3 = Vertex{}      // X:0 and Y:0
		p1 = &Vertex{1, 2} // has type *Vertex
	)

}
*/

func UseArrayAndSlice() {
	var a [2]string
	a[0] = "Hello"
	a[1] = "World"

	fmt.Println(a[0], a[1])
	fmt.Println(a)

	primes := [6]int{2, 3, 5, 7, 11, 13}
	fmt.Println(primes)

	// Slices
	// An array has a fixed size. A slice, on the other hand, is a dynamically-sized, flexible view into the elements of an array.
	// In practice, slices are much more common than arrays.

	// The type []T is a slice with elements of type T.
	// A slice is formed by specifying two indices, a low and high bound, separated by a colon:

	// a[low : high]
	// This selects a half-open range which includes the first element, but excludes the last one.
	// The following expression creates a slice which includes elements 1 through 3 of a:
	// a[1:4]
	fmt.Println(primes[1:3])

	// Slices are like references to arrays
	// A slice does not store any data, it just describes a section of an underlying array.

	// Changing the elements of a slice modifies the corresponding elements of its underlying array.

	// Other slices that share the same underlying array will see those changes.
	names := [4]string{
		"John",
		"Paul",
		"George",
		"Ringo",
	}
	fmt.Println(names)

	c := names[0:2]
	b := names[1:3]
	fmt.Println(a, c)

	c[0] = "XXX"
	fmt.Println(a, c)
	fmt.Println(names)

	// Slice literals
	// A slice literal is like an array literal without the length.

	// This is an array literal:
	// [3]bool{true, true, false}
	// And this creates the same array as above, then builds a slice that references it:
	// []bool{true, true, false}
	q := []int{2, 3, 5, 7, 11, 13}
	fmt.Println(q)

	r := []bool{true, false, true, true, false, true}
	fmt.Println(r)

	s1 := []struct {
		i int
		b bool
	}{
		{2, true},
		{3, false},
		{5, true},
		{7, true},
		{11, false},
		{13, true},
	}
	fmt.Println(s1)

	// Slice defaults
	// When slicing, you may omit the high or low bounds to use their defaults instead.

	// The default is zero for the low bound and the length of the slice for the high bound.

	// For the array

	// var a [10]int
	// these slice expressions are equivalent:

	// a[0:10]
	// a[:10]
	// a[0:]
	// a[:]
	s := []int{2, 3, 5, 7, 11, 13}

	s = s[1:4]
	fmt.Println(s)

	s = s[:2]
	fmt.Println(s)

	s = s[1:]
	fmt.Println(s)

	// Slice length and capacity
	// A slice has both a length and a capacity.

	// The length of a slice is the number of elements it contains.
	// The capacity of a slice is the number of elements in the underlying array, counting from the first element in the slice.
	// The length and capacity of a slice s can be obtained using the expressions len(s) and cap(s).
	// You can extend a slice's length by re-slicing it, provided it has sufficient capacity. Try changing one of the slice operations in the example program to extend it beyond its capacity and see what happens.
	fmt.Println("Len=%d , Cap=%d , s=%v ", len(s), cap(s))

	// Creating a slice with make
	// Slices can be created with the built-in make function; this is how you create dynamically-sized arrays.

	// The make function allocates a zeroed array and returns a slice that refers to that array:

	// a := make([]int, 5)  // len(a)=5
	// To specify a capacity, pass a third argument to make:

	// b := make([]int, 0, 5) // len(b)=0, cap(b)=5
	// b = b[:cap(b)] // len(b)=5, cap(b)=5
	// b = b[1:]      // len(b)=4, cap(b)=4

	a1 := make([]int, 5)
	a2 := make([]int, 0, 5)
	a3 := a2[:2]
	a4 := a3[2:5]

	// Create a tic-tac-toe board
	board := [][]string{
		[]string{"-", "-", "-"},
		[]string{"-", "-", "-"},
		[]string{"-", "-", "-"},
	}

	board[0][0] = "X"
	board[0][0] = "O"
	board[0][0] = "X"
	board[0][0] = "O"
	board[0][0] = "X"

	for i := 0; i < 3; i++ {
		fmt.Println("%s", strings.Join(board[i], " "))
	}

	// append
	{
		var s1 []int
		s1 = append(s1, 0)
		fmt.Println("len=%d, cap=%d, %v", len(s1), cap(s1), s1)

		s1 = append(s1, 1, 2, 3, 4)
		fmt.Println("len=%d, cap=%d, %v", len(s1), cap(s1), s1)

	}

	// range
	pow := []int{1, 2, 4, 8, 16, 32, 64}
	for i, v := range pow {
		fmt.Println(" 2 ** %d = %d", i, v)
	}

	pow = make([]int, 10)
	for i := range pow {
		pow[i] = 1 << uint(i)
	}

	for _, val := range pow {
		fmt.Printf("%d, ", val)
	}
	fmt.Printf("\n")

}

func UseMap() {
	// Maps
	// A map maps keys to values.

	// The zero value of a map is nil. A nil map has no keys, nor can keys be added.
	// The make function returns a map of the given type, initialized and ready for use.

	// var m map[string]Vertex // nil function should be initialized
	m := make(map[string]Vertex)

	m["Bell Labs"] = Vertex{40, -70}

	fmt.Println(m["Bell Labs"])

	// Map literals
	// Map literals are like struct literals, but the keys are require
	var m1 = map[string]Vertex{
		"Bell Labs": Vertex{
			30, 20,
		},
		"Google": Vertex{
			20, 30,
		},
	}

	// add
	m1["Amazon"] = Vertex{10, 10}

	// delete
	delete(m1, "Amazon")

	// retrieve element
	elem1 := m1["Amazon"]

	// Test value
	elem, ok := m1["Amazon"]
	// if "Amazon" is in m1, elem and ok is true. if not, ok is false
	// if ok is false, elem is zero value

	content := " I am not sure the detail of mapping "
	counter := make(map[string]int)
	words := strings.Fields(content)

	for i := 0; i < len(words); i++ {
		elem, ok := counter[words[i]]
		if ok {
			counter[words[i]] = elem + 1
		} else {
			counter[words[i]] = 1
		}
	}

}

// functions value
func compute(fn func(float64, float64) float64) float64 {
	return fn(3, 4)
}

func UseFunctionValues() {
	hypot := func(a, b float64) float64 {
		return math.Sqrt(a*a + b*b)
	}

	fmt.Println(hypot(5, 12))
	fmt.Println(compute(hypot))
	fmt.Println(compute(math.Pow))

}

// function closure
func adder() {
	sum := 0
	return func(a int) {
		sum += a
		return sum
	}
}

func caller2Adder() {

	pos, neg := adder(), adder()
	for i := 0; i < 10; i++ {
		fmt.Println(pos(i), neg(-2*i))
	}
}

func fibonacci() {
	last1, last2 := 0, 1

	return func() int {
		res := last1 + last2
		last1 = last2
		last2 = res
		return res
	}
}

func callfibonacci() {

	fino := fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Printf(fino(), ",")
	}
	fmt.Printf("\n")
}

/*
//* Interfaces
// An interface type is defined as a set of method signatures.
// A value of interface type can hold any value that implements those methods

// Interfaces are implemented implicitly
// A type implements an interface by implementing its methods. There is no explicit declaration of intent, no "implements" keyword.
// Implicit interfaces decouple the definition of an interface from its implementation, which could then appear in any package without prearrangement..
type Abser interface {
	Abs() float64
}

func (v *Vertex) Abs() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func (f MyFloat) Abs() float64 {
	if f < 0 {
		return float64(-f)
	}
	return math.Sqrt(f * f)
}

func callInterface() {
	var a Abser
	f := MyFloat(1)
	v := Vertex{1, 2}

	a = f  // MyFloat implement the Abser
	a = &v // *Vertex implement the Abser

	a = v // v is Vertex and *Vertex, not implement the Abs()

	fmt.Println(a.Abs())
}
*/
func main() {
	fmt.Printf("Hello World! \n")

	fmt.Println("Current time is ", time.Now())

	fmt.Println("My favorite number is", rand.Intn(10))

	fmt.Println("Type: %T Value: %V", ToBe, ToBe)
	fmt.Println("Type: %T Value: %V", MaxInt, MaxInt)
	fmt.Println("Type: %T Value： %V", z, z)

	fmt.Println("3 + 5 = ", add(3, 5))

	fmt.Println("Swap a and b will be %v, %v", swap("a", "b"))

	// with initializer, the 'type' could be ignored
	var c, python, java = true, false, "no!"

	// short variable declaration
	// Inside a function, the := short assignment statement can be used in place of a var declaration with implicit type.
	// Outside a function, every statement begins with a keyword (var, func, and so on) and so the := construct is not available.
	i, j, k := 1, 2, 3

	// Type conversions
	var x, y int = 3, 4
	f := float32(i) // var f float64 = math.Sqrt（float64(x*x) + float64(y*y))
	u := uint(i)    // var u uint = uint(f)

	// Type inference
	// When declaring a variable without specifying an explicit type (either by using the := syntax or var = expression syntax), the variable's type is inferred from the value on the right hand side.
	// When the right hand side of the declaration is typed, the new variable is of that same type

	// Constants
	// Constants are declared like variables, but with the const keyword.

	// Constants can be character, string, boolean, or numeric values.
	// Constants cannot be declared using the := syntax.

	const (
		// Create a huge number by shifting a 1 bit left 100 places.
		// In other words, the binary number that is 1 followed by 100 zeroes.
		Big = 1 << 100
		// Shift it right again 99 places, so we end up with 1<<1, or 2.
		Small = Big >> 99
	)

	// Zero values
	// Variables declared without an explicit initial value are given their zero value.

	// The zero value is:

	// 0 for numeric types,
	// false for the boolean type, and
	// "" (the empty string) for strings.
	var ni int
	var nf float64
	var nb bool
	var ns string
	fmt.Printf("%v %v %v %q\n", ni, nf, nb, ns)

	// For
	// Go has only one looping construct, the for loop.

	// The basic for loop has three components separated by semicolons:

	// the init statement: executed before the first iteration
	// the condition expression: evaluated before every iteration
	// the post statement: executed at the end of every iteration
	// The init statement will often be a short variable declaration, and the variables declared there are visible only in the scope of the for statement.

	// The loop will stop iterating once the boolean condition evaluates to false.
	// Note: Unlike other languages like C, Java, or JavaScript there are no parentheses surrounding the three components of the for statement and the braces { } are always required.
	sum := 0
	for i := 0; i < 10; i++ {
		sum += i
	}

	fmt.Println("sum ", sum)

	// If
	// Go's if statements are like its for loops; the expression need not be surrounded by parentheses ( ) but the braces { } are required.
	if x < 0 {
		fmt.Println("x < 0")
	} else {
		fmt.Println("x >= 0")
	}

	// If with a short statement
	// Like for, the if statement can start with a short statement to execute before the condition.

	// Variables declared by the statement are only in scope until the end of the if.
	// (Try using v in the last return statement.)
	xx := 3.0
	if v := math.Pow(xx, 3); v < 100 {
		fmt.Println("x < 100")
	} else {
		fmt.Println("x > 100")
	}

	// Switch
	// A switch statement is a shorter way to write a sequence of if - else statements.
	// It runs the first case whose value is equal to the condition expression.

	// Go's switch is like the one in C, C++, Java, JavaScript, and PHP, except that Go only runs the selected case, not all the cases that follow.
	// In effect, the break statement that is needed at the end of each case in those languages is provided automatically in Go.
	// Another important difference is that Go's switch cases need not be constants, and the values involved need not be integers.
	fmt.Print("Go runs on ")
	switch os := runtime.GOOS; os {
	case "darwin":
		fmt.Println("OS X.")
	case "linux":
		fmt.Println("Linux.")
	default:
		// freebsd, openbsd,
		// plan9, windows...
		fmt.Printf("%s.", os)
	}
	// switch without condiction
	t := time.Now()
	switch {
	case t.Hour() < 12:
		fmt.Println("Good Morning")
	case t.Hour() < 17:
		fmt.Println("Good afternoon")
	default:
		fmt.Println("Good Evening")
	}

	// Defer
	// A defer statement defers the execution of a function until the surrounding function returns.

	// The deferred call's arguments are evaluated immediately, but the function call is not executed until the surrounding function returns.
	defer fmt.Println("--- the end --- ")

	// Stacking defers
	// Deferred function calls are pushed onto a stack. When a function returns, its deferred calls are executed in last-in-first-out order.
	for i := 0; i < 10; i++ {
		defer fmt.Println(i)
	}
	fmt.Println(" Done !")

	caller2Adder()

	callfibonacci()
}
