package main



import (
	"fmt"
)

// similar as (void*) in C, could refer to any type
type empty_iface interface {
}

func myfunc(i interface{}) {
	fmt.Println(i)
}

func myfuncn(i ...interface{}) {
	for _, iface := range i {
		fmt.Printf("Type: %T, Value: %v\n", iface, iface)
	}
}

func myfuncType(i interface{}) {

	switch i.(type) {
	case int:
		fmt.Println("int")
	case string:
		fmt.Println("string")
	}
}

func Test_null_interface() {

	var i interface{} // interface{} could store any type, like void*, just point
	fmt.Printf("Type: %T, Value: %v\n", i, i) // Type:<nil>, Value:<nil>

	// interface{} could be assigned by any Type Value, 
	i = 1
	fmt.Printf("Type: %T, Value: %v\n", i, i)

	i = "hello"
	fmt.Printf("Type: %T, Value: %v\n", i, i)

	i = false
	fmt.Printf("Type: %T, Value: %v\n", i, i)

	a := 10
	b := "hello"
	c := true

	myfunc(a)
	myfunc(b)
	myfunc(c)


	// interface{} array, 
	array := make([]interface{}, 5)
	array[0] = 11
	array[1] = "hell0"
	array[2] = true
	array[3] = []int{1, 2, 3}
	array[4] = make(map[int]int, 3)

	for _, a := range array {
		fmt.Printf("Type: %T, Value: %v\n", a, a)
	}

	// can't assign interface{} back to Type
	{
		var a int = 1
		var i interface{} = a //ok, assign T to interface{}
		var b = i // error, cannot use i (type interface {}) as type int in assignment: need type assertion. if you remove 'int', let compiler deduce, it is ok.
		fmt.Println(b)
	}

	{
		sli := []int{2, 3, 5, 7, 11, 13}

		var i interface{}
		i = sli
		fmt.Println(i)
		// g := i[1:3]  // error, cannot slice i (type interface {})
		// fmt.Println(g)
	}

	{
		a, b := 10, "Hello"
		myfuncType(a)
		myfuncType(b)
	}

}