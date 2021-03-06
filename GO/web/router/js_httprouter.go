package router

import (
	"fmt"
	"log"
	"net/http"

	"github.com/julienschmidt/httprouter"
)

// other way to implement the router, "julienschmidt/httprouter"
func index(w http.ResponseWriter, r *http.Request, _ httprouter.Params) {
	fmt.Fprint(w, "Welcome!\n")
}

func hello(w http.ResponseWriter, r *http.Request, ps httprouter.Params) {
	fmt.Fprintf(w, "hello, %s!\n", ps.ByName("name"))
}

// start router of julienSchmit http router
func JS_httpRouter() {
	router := httprouter.New()
	router.GET("/", index)
	router.GET("/hello/:name", hello)

	log.Fatal(http.ListenAndServe(":8080", router))
}
