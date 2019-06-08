package main

import (
	"fmt"
)

type Animal struct {
	Name string
	Age int
}

type Player struct {
	PlayerName string
	Id string
}

type Cat struct {
	Animal
	Player // Name combat
	Color string
	Watched bool
}

func test_struct_basic() {
	
	cat := Cat{}

	cat.Name = "Cat"
	cat.Age = 16
	cat.Color = "Blue"
	cat.Watched = true

	cat.PlayerName = "PlayOne"
	cat.Id = "0000-0000" 

	fmt.Println(cat.Name)
	fmt.Println(cat.Age)

	fmt.Println(cat.Animal.Name)
	fmt.Println(cat.Animal.Age)


	//cat1 := Cat{
		//Animal.Name : "Dog",
		//Age : 21,
		//Color : "Red",
		//Watched : false,
		//PlayerName : "PlayTwo",
		//Id : "0000-0001",
	//}

	cat1 := new(Cat)
	cat1.Name = "Dog"
	cat1.Age = 31

	fmt.Println(cat1.Name)
	fmt.Println(cat1.Age)
}

func test_struct() {

	fmt.Println(" --- struct --- ")

	test_struct_basic()

	fmt.Println(" --- struct end --- ")
}