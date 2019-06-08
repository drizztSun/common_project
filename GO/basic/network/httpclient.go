package main

import (
	"errors"
	"fmt"
	"net/http"
	"io/ioutil"
	//"encoding/json"
)

func test_basic_http() {

	var (
		err = errors.New("place holder")
		resp *http.Response
	)
	
	if resp, err = http.Get("https://www.google.com/"); err != nil {
		fmt.Println("Error happended : ", err.Error())
	}

	fmt.Println("responseCode : ", resp.StatusCode)
	fmt.Println("responseCode : ", resp.Status)
	fmt.Println("Protocol : ", resp.Proto)
	fmt.Printf("Major %d, Minor %d\n", resp.ProtoMajor, resp.ProtoMinor)

	fmt.Println("Content-Length : ", resp.ContentLength)
	fmt.Printf("TransferEncoding : %v", resp.TransferEncoding)
	fmt.Println("")

	fmt.Println(" --- headers --- ")
	for k, v := range resp.Header {
		fmt.Printf("Header : %s, Value: %v \n", k, v)
	}

	body, err := ioutil.ReadAll(resp.Body); 
	if err != nil {
		fmt.Println("Error : ", err)
	}

	fmt.Printf("content : %s", body)

	resp.Body.Close()
}

func test_basic_http_client() {

	//resp, err := http.Get("http://localhost:8080/") 
}

func test_httpclient() {

	test_basic_http()

}