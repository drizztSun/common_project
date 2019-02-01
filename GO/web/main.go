package main

import (
	"fmt"

	"./redis"
	"./router"
)

func main() {

	fmt.Println("--- Start golang web service demo  ---")
	localhost := "localhost"

	//router.Standard_router(localhost)

	redis.Test_redis()

	router.GorillaMux_httpRouter(localhost)
}
