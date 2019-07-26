package main

import (
	"log"
	"net/http"
	"fmt"
	"io"
	"strings"
)

func reportRequest(r * http.Request) {
	
	fmt.Println("Calling HandleDiag")

	fmt.Println("------- General Request ----------")
	fmt.Println("Method ", r.Method)
	fmt.Println("Proto : ", r.Proto, " Max: ", r.ProtoMajor, " Min: ", r.ProtoMinor)

	fmt.Println("Host : ", r.Host)
	fmt.Println("Remote Host : ", r.RemoteAddr)
	fmt.Println("RequestURI : ", r.RequestURI)
	fmt.Println("ContentLength : ", r.ContentLength)
	fmt.Println("TransferEncoding : ", r.TransferEncoding)

	fmt.Println("Refer : ", r.Refer())
	fmt.Println("UserAgent : ", r.UserAgent())

	fmt.Println("------Header---------")
	// map[string]string
	var header http.Header 
	header = r.Header
	for h, v := range header {
		fmt.Println(h, " = ", v)
	}
	fmt.Println("------Header---------")

	fmt.Println(" --- form --- ")
	var form http.Values
	form = r.Form
	for k, v := range form {
		fmt.Printf("%s : %v \n", k, v)
	}
	fmt.Println(" --- post form --- ")
	var postForm http.Values
	postForm = r.PostForm
	for k, v := range postForm {
		fmt.Println("%s : %v \n", k, v)
	}
	fmt.Println(" --- form end --- ")

	r.ParseMultipleForm()
}

// HandleDiag Handle diag call
func HandleDiag(w http.ResponseWriter, r * http.Request) {

	checkItem := r.URL.Query()
	fmt.Println("Check == ", checkItem["check"])
	fmt.Println("Check == ", checkItem.Get("check"))

	io.WriteString(w, fmt.Sprint("The check is ", strings.ToLower(checkItem.Get("check"))))
}

// HandleUpdate Handle update 
func HandleUpdate(w http.ResponseWriter, r * http.Request) {

	

}

// HandleForms Handle Forms
func HandleForms(w http.ResponseWriter, r * http.Request) {

	reportRequest(r)

	io.WriteString(w, fmt.Sprint("The check is ", strings.ToLower(checkItem.Get("request"))))
}

func main() {

	http.HandleFunc("/diagnostics/", HandleFunc)

	http.HandleFunc("/update", HandleUpdate)

	htt.HandleFunc("/forms", HandleForms)

	log.Fatal(http.ListenAndServe(":8080", nil))
}
