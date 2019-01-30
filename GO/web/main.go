package main

import (
	"fmt"

	"./router"
)

func main() {

	fmt.Println("--- Start golang web service demo  ---")
	localhost := "localhost"

	router.Standard_router(localhost)
}
