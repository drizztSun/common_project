package main

import (
	"errors"
	"fmt"
	"net/http"
)

func test_basic_http() {

	err := errors.New("place holder")
	for retry := 5; retry > 0 && err != nil; retry-- {
		resp, err := http.Get("http://www/google.com/")
		if err != nil {
			fmt.Println("Err : ", err)
			continue
		}
		fmt.Println("Resp code : ", resp.StatusCode)
	}


	
}

func test_http() {

	test_basic_http()

}