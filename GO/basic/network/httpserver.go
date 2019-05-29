package main

import (
	//"net"
	"net/http"
	"fmt"
	"io"
)

func get(w http.ResponseWriter, r *http.Request) {
	fmt.Printf("M: %s A: %s", r.Method, r.URL.Path)
	io.WriteString(w, "Hello world!")
}

func post(w http.ResponseWriter, r *http.Request) {
	fmt.Printf("M: %s, A:%s", r.Method, r.URL.Path)
}

func put(w http.ResponseWriter, r *http.Request) {

}

func delete(w http.ResponseWriter, r *http.Request) {

}


func test_basic_server() {

	go func () {

		http.HandleFunc("/get", get)
		http.HandleFunc("/post", post)
		http.HandleFunc("/put", put)
		http.HandleFunc("/delete", delete)
		http.HandleFunc("/", get)

		http.ListenAndServe(":8080", nil)
	}()
}


func test_httpsever() {

	test_basic_server()
}