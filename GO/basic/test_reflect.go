// Package reflect implements run-time reflection, allowing a program to manipulate objects with arbitrary types. 
// The typical use is to take a value with static type interface{} and extract its dynamic type information by calling TypeOf, which returns a Type.

// A call to ValueOf returns a Value representing the run-time data. Zero takes a Type and returns a Value representing a zero value for that type.
// See "The Laws of Reflection" for an introduction to reflection in Go: https://golang.org/doc/articles/laws_of_reflection.html

package main

import (
	"fmt"
	"reflect"
	"io"
	"os"
	"bytes"
	"encoding/json"
)

/*
Conclusion
Here again are the laws of reflection:

Reflection goes from interface value to reflection object.
Reflection goes from reflection object to interface value.
To modify a reflection object, the value must be settable.
Once you understand these laws reflection in Go becomes much easier to use, although it remains subtle. 
It's a powerful tool that should be used with care and avoided unless strictly necessary.

There's plenty more to reflection that we haven't covered — sending and receiving on channels, allocating memory, using slices and maps, 
calling methods and functions — but this post is long enough. We'll cover some of those topics in a later article.

*/

func test_basic_reflect() {

	/*
	1. Reflection goes from interface value to reflection object.
	At the basic level, reflection is just a mechanism to examine the type and value pair stored inside an interface variable. 
	To get started, there are two types we need to know about in package reflect: Type and Value. 
	Those two types give access to the contents of an interface variable, and two simple functions, 
	called reflect.TypeOf and reflect.ValueOf, retrieve reflect.Type and reflect.Value pieces out of an interface value. 
	(Also, from the reflect.Value it's easy to get to the reflect.Type, but let's keep the Value and Type concepts separate for now.)
	*/

	var x float64 = 3.4
    fmt.Println("type:", reflect.TypeOf(x)) // type: float64
	fmt.Println("value:", reflect.ValueOf(x)) // value: 3.4
	
	fmt.Println("value: ", reflect.ValueOf(x).String()) // <float64 Value>

	/*
	Both reflect.Type and reflect.Value have lots of methods to let us examine and manipulate them. 
	One important example is that Value has a Type method that returns the Type of a reflect.Value. 
	Another is that both Type and Value have a Kind method that returns a constant indicating what sort of item is stored: 
	Uint, Float64, Slice, and so on. Also methods on Value with names like Int and Float let us grab values (as int64 and float64) stored inside:
	*/

	V := reflect.ValueOf(x)
	fmt.Println("type: ", V.Type()) //type: float64
	fmt.Println("Kind is float64: ", V.Kind() == reflect.Float64) // kind is float64: true
	fmt.Println("Value: ", V.Float()) // value: 3.4

	/*
	The reflection library has a couple of properties worth singling out. 
	First, to keep the API simple, the "getter" and "setter" methods of Value operate on the largest type that can hold the value: 
	int64 for all the signed integers, for instance. That is, the Int method of Value returns an int64 and the SetInt value takes an int64; 
	it may be necessary to convert to the actual type involved:
	*/
	{
		var x uint8 = 'x'
		v := reflect.ValueOf(x)
		fmt.Println("type:", v.Type())                            // uint8.
		fmt.Println("kind is uint8: ", v.Kind() == reflect.Uint8) // true.
		x = uint8(v.Uint())                                       // v.Uint returns a uint64.
	}

	{
		// The second property is that the Kind of a reflection object describes the underlying type, not the static type. 
		// If a reflection object contains a value of a user-defined integer type, as in
		type MyInt int
		var x MyInt = 7
		v := reflect.ValueOf(x)
		fmt.Println(v)
		// the Kind of v is still reflect.Int, even though the static type of x is MyInt, not int. 
		// In other words, the Kind cannot discriminate an int from a MyInt even though the Type can.
	}	

	/*
	The second law of reflection
	2. Reflection goes from reflection object to interface value.
	Like physical reflection, reflection in Go generates its own inverse.

	Given a reflect.Value we can recover an interface value using the Interface method; 
	in effect the method packs the type and value information back into an interface representation and returns the result:
	// Interface returns v's value as an interface{}.
		func (v Value) Interface() interface{}
	*/
	{
		var V float64 = 3.4
		v := reflect.ValueOf(V)
		y := v.Interface().(float64)
		fmt.Println(y)
	
	/*
	We can do even better, though. The arguments to fmt.Println, fmt.Printf and so on are all passed as empty interface values, 
	which are then unpacked by the fmt package internally just as we have been doing in the previous examples. 
	Therefore all it takes to print the contents of a reflect.Value correctly is to pass the result of the Interface method to the formatted print routine:
	*/
		fmt.Println(v.Interface())

	/*
	(Why not fmt.Println(v)? Because v is a reflect.Value; we want the concrete value it holds.) Since our value is a float64, 
	we can even use a floating-point format if we want:
	*/
		fmt.Printf("value is %7.1e\n", v.Interface())
	/*
	Again, there's no need to type-assert the result of v.Interface() to float64; the empty interface value has the concrete value's type information inside and Printf will recover it.
	In short, the Interface method is the inverse of the ValueOf function, except that its result is always of static type interface{}.
	Reiterating: Reflection goes from interface values to reflection objects and back again.
	*/
	}

	{
		/*
		The third law of reflection
		3. To modify a reflection object, the value must be settable.
		The third law is the most subtle and confusing, but it's easy enough to understand if we start from first principles.
		Here is some code that does not work, but is worth studying. */

		var x float64 = 3.4
		v := reflect.ValueOf(x)
		fmt.Println("settability of v:", v.CanSet()) // settability of v: false
		if v.CanSet() {
			v.SetFloat(7.1) // Error: will panic.
			/*
			If you run this code, it will panic with the cryptic message

			panic: reflect.Value.SetFloat using unaddressable value
			The problem is not that the value 7.1 is not addressable; it's that v is not settable. Settability is a property of a reflection Value, 
			and not all reflection Values have it.

			The CanSet method of Value reports the settability of a Value; in our case,
			*/
		}
	}

	{
		/*
		Settability is a bit like addressability, but stricter. 
		It's the property that a reflection object can modify the actual storage that was used to create the reflection object. 
		Settability is determined by whether the reflection object holds the original item. When we say
		*/
		var x float64 = 3.4
		v := reflect.ValueOf(x)
		// we pass a copy of x to reflect.ValueOf, 
		// so the interface value created as the argument to reflect.ValueOf is a copy of x, not x itself. Thus, if the statement
		v.SetFloat(7.1)

		/*
		The reflection object p isn't settable, but it's not p we want to set, it's (in effect) *p. 
		To get to what p points to, we call the Elem method of Value, which indirects through the pointer, 
		and save the result in a reflection Value called v:
		*/


		p := reflect.ValueOf(&x)
		fmt.Println("Type: ", p.Type()) // Type: &float64
		fmt.Println("settability of v: ", p.CanSet()) // Can set: false

		/*
		The reflection object p isn't settable, but it's not p we want to set, it's (in effect) *p. 
		To get to what p points to, we call the Elem method of Value, which indirects through the pointer, 
		and save the result in a reflection Value called v:		
		*/
		v = p.Elem()
		fmt.Println("settability of v: ", v.CanSet())
		if v.CanSet() {
			v.SetFloat(7.1)
			fmt.Println(v.Interface())
			fmt.Println(x)
		}

		/*
		Reflection can be hard to understand but it's doing exactly what the language does, 
		albeit through reflection Types and Values that can disguise what's going on. Just keep in mind 
		that reflection Values need the address of something in order to modify what they represent.		
		*/
	}

	{
		/*
		Structs
		In our previous example v wasn't a pointer itself, it was just derived from one. 
		A common way for this situation to arise is when using reflection to modify the fields of a structure. 
		As long as we have the address of the structure, we can modify its fields.		
		*/

		type T struct {
			A int
			B string
		}

		t := T{1, "Number"}
		p := reflect.ValueOf(&t).Elem()
		typeofT := p.Type()
		for i := 0; i < p.NumField(); i++ {
			f := p.Field(i)
			fmt.Printf("%d, %s, %s = %v \n", i, 
				typeofT.Field(i).Name, f.Type(), f.Interface())
		}

		// 0: A int = 23
		// 1: B string = skidoo


		/*
		There's one more point about settability introduced in passing here: the field names of T are upper case (exported) because only exported fields of a struct are settable.
		Because s contains a settable reflection object, we can modify the fields of the structure.
		*/
		p.Field(0).SetInt(77)
		p.Field(1).SetString("Sunset Strip")
		fmt.Println("t is now", t) // t is now {77 Sunset Strip}

		// If we modified the program so that s was created from t, not &t, 
		// the calls to SetInt and SetString would fail as the fields of t would not be settable.
	}
} 

func test_basic_reflect_Kind() {

	// Kind and Valueof
	for _, v := range []interface{}{"hi", 12, func(){}} {

		switch V := reflect.ValueOf(v); V.Kind() {
		case reflect.String:
			fmt.Println(V.String())
		case reflect.Int, reflect.Int8, reflect.Int16, reflect.Int32, reflect.Int64:
			fmt.Println(V.String())
		default:
			fmt.Printf("unhandle kind %s", V.Kind())
		}
	}
}

func test_basic_reflect_makefunc() {
	/*
	MakeFunc returns a new function of the given Type that wraps the function fn. When called, that new function does the following:

	- converts its arguments to a slice of Values.
	- runs results := fn(args).
	- returns the results as a slice of Values, one per formal result.
	*/

	// swap is the implementation passed to MakeFunc.
	// It must work in terms of reflect.Values so that it is possible
	// to write code without knowing beforehand what the types
	// will be.
	swap := func(in []reflect.Value) []reflect.Value{
		return []reflect.Value{in[1], in[0]}
	}

	// makeSwap expects fptr to be a pointer to a nil function.
	// It sets that pointer to a new function created with MakeFunc.
	// When the function is invoked, reflect turns the arguments
	// into Values, calls swap, and then turns swap's result slice
	// into the values returned by the new function.
	makeSwap := func(fptr interface{}) {

		fn := reflect.ValueOf(fptr).Elem()

		v := reflect.MakeFunc(fn.Type(), swap)
		
		fn.Set(v)
	}

	// Make and call a swap function for ints
	var intSwap func(int, int) (int, int)
	makeSwap(&intSwap)
	fmt.Println(intSwap(1, 2))

	// Make and call a swap function for floats
	var floatSwap func(float64, float64) (float64, float64)
	makeSwap(&floatSwap)
	fmt.Println(floatSwap(2.2, 1.1))
}

func test_reflect_TypeOf() {

	writer := reflect.TypeOf((*io.Writer)(nil)).Elem()

	fileType := reflect.TypeOf((*os.File)(nil)).Elem()

	// true
	fmt.Println(fileType.Implements(writer))
}

func test_reflect_StructOf() {

	/*
	StructOf returns the struct type containing fields. The Offset and Index fields are ignored and computed as they would be by the compiler.

	StructOf currently does not generate wrapper methods for embedded fields and panics if passed unexported StructFields. 
	These limitations may be lifted in a future version.
	*/

	t1 := reflect.StructOf([]reflect.StructField{
			{
				Name: "Height",
				Type: reflect.TypeOf(float64(0)),
				Tag: `json:"height"`,
			},
			{
				Name: "Age",
				Type: reflect.TypeOf(int(0)),
				Tag: `json:"age"`,
			},
		})

	v := reflect.New(t1).Elem()
	v.Field(0).SetFloat(0.4)
	v.Field(1).SetInt(2)
	s := v.Addr().Interface()

	w := new(bytes.Buffer)
	if err := json.NewEncoder(w).Encode(s); err != nil {
		return
	}

	fmt.Printf("Value: %v\n", s)
	fmt.Printf("json: %s\n", w.Bytes())

	r := bytes.NewReader([]byte(`{"height":1.5,"age":10}`))
	if err := json.NewDecoder(r).Decode(s); err != nil {
		return
	}
	fmt.Printf("value: %+v\n", s)
}

func test_reflect_StructTag() {
	type S struct {
		F string `species:"gopher" color:"blue"`
	}

	s := S{}
	st := reflect.TypeOf(s)
	field := st.Field(0)

	fmt.Println(field.Tag.Get("color"), field.Tag.Get("species"))
}

func test_reflect() {

	test_basic_reflect()

}