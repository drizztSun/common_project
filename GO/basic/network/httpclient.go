package main

import (
	"errors"
	"fmt"
	"net/http"
	"io/ioutil"
	//"encoding/json"
)

func reportResponse(resp *http.Response) {

	fmt.Println("-------- General Info of Response --------")

	fmt.Println("responseCode : ", resp.StatusCode)
	fmt.Println("responseCode : ", resp.Status)
	fmt.Println("Protocol : ", resp.Proto)
	fmt.Printf("Major %d, Minor %d\n", resp.ProtoMajor, resp.ProtoMinor)

	fmt.Println("Content-Length : ", resp.ContentLength)
	fmt.Printf("TransferEncoding : %v \n", resp.TransferEncoding)
	fmt.Println("Uncompressed : ", resp.Uncompressed)

	fmt.Println(" --- headers --- ")
	var header http.Header
	header = resp.Header
	for k, v := range header {
		fmt.Printf(" %s = %s \n", k, v)
	}

	fmt.Println(" --- trailer header --- ")
	var headerTrailer http.Header
	headerTrailer = resp.Trailer
	for k, v := range headerTrailer {
		fmt.Printf(" %s = %s \n", k, v)
	}

	fmt.Println(" --- headers --- ")

	fmt.Println(" --- body --- ")
	body, err := ioutil.ReadAll(resp.Body); 
	if err != nil {
		fmt.Println("Error : ", err)
		return
	}

	fmt.Printf("content : %s", body)

	resp.Body.Close()
	fmt.Println(" --- body --- ")
}

func test_basic_http() {

	var (
		err = errors.New("place holder")
		resp *http.Response
		host = "http://127.0.0.1:8080/"
	)
	
	if resp, err = http.Get(host); err != nil {
		fmt.Println("Error happened : ", err.Error())
	}

	reportResponse(resp)

	resp, err = http.PostForm(host + "forms?request=123", url.Value{"key": {"FormValue"}, "id": {"123"}})
	if err != nil {
		fmt.Println("Error happened : ", err.Error())
	}

	reportResponse(resp)
}

func test_basic_http_client() {

	resp, err := http.Post("http://localhost:8080/", "application:json")
}

func test_httpclient() {

	test_basic_http()

}