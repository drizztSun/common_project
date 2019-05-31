package main

import (
	//"net"
	"net/http"
	"fmt"
	//"io"
	"encoding/json"
)

type Data struct {
	Title	string `json:"title"`
	Data 	string `json:"data"`
}

func get(w http.ResponseWriter, r *http.Request) {
	fmt.Printf("M: %s A: %s", r.Method, r.URL.Path)

	data, _ := json.Marshal(Data {
		Title : "get",
		Data : "Hello world",
	})

	w.WriteHeader(http.StatusOK)
	w.Header().Add("Content-Type", "apllication/json")	
	//io.WriteString(w, data)
	w.Write(data)
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