package main

import (
	"errors"
	"fmt"
	"net/http"
	"encoding/json"
)

func test_basic_http() {

	var (
		err = errors.New("place holder")
		resp *http.Response
	)
	
	if resp, err = http.Get("http://localhost:8080/get"); err != nil {
		fmt.Println("Error happended : ", err.Error())
	}



	resp.Body.Close()
}

func test_httpclient() {

	test_basic_http()

}