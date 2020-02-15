package main

import (
	"bytes"
	"encoding/json"
	"errors"
	"fmt"
	"io/ioutil"
	"net/http"
	"net/url"
	"time"
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
	body, err := ioutil.ReadAll(resp.Body)
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
		err  = errors.New("place holder")
		resp *http.Response
		host = "http://127.0.0.1:8080/"
	)

	if resp, err = http.Get(host); err != nil {
		fmt.Println("Error happened : ", err.Error())
	}

	reportResponse(resp)

	resp, err = http.PostForm(host+"forms?request=123", url.Values{"key": {"FormValue"}, "id": {"123"}})
	if err != nil {
		fmt.Println("Error happened : ", err.Error())
	}

	reportResponse(resp)

	// Post content

	info := &Payload{
		id:          "test-id",
		information: "test-info",
	}

	payload, err := json.Marshal(info)
	if err != nil {
		return
	}

	resp, err = http.Post("http://localhost:8080/", "application:json", bytes.NewReader(payload))
	defer resp.Body.Close()

	if err != nil {
		fmt.Println("Return error from post")
	}
}

type Payload struct {
	id          string `json:"id"`
	information string `json:"info"`
}

// RoundTripFunc Need a type to hang RoundTrip() off of
type RoundTripFunc func(req *http.Request) *http.Response

// RoundTrip Implement the RoundTripper interface used by http.Client()
//
// Client.Transport is actually RoundTripper, an interface, not http.Transport,
// an impl of that interface.
//
// Creating a RoundTripFunc from
func (f RoundTripFunc) RoundTrip(req *http.Request) (*http.Response, error) {
	return f(req), nil
}

func test_basic_cycle_network_request() {

	info := &Payload{
		id:          "test-id",
		information: "test-info",
	}

	payload, err := json.Marshal(info)
	if err != nil {
		return
	}

	uri := "http://www.text.com" + "/test.html"
	req, err := http.NewRequest("POST", uri, bytes.NewReader(payload))
	if err != nil {
		return
	}

	var transport http.RoundTripper = RoundTripFunc(func(req *http.Request) *http.Response {

		if req.URL.String() != "http://www.text.com/test.html" {
			return &http.Response{
				StatusCode: 401,
				Header:     make(http.Header),
			}
		}

		return &http.Response{
			StatusCode: 200,
			Body:       ioutil.NopCloser(bytes.NewBufferString("Content acccept")),
			Header:     make(http.Header),
		}
	})

	req.Header.Set("Content-Type", "application/json")
	req.Header.Set("X-Type", "user-defined field")

	client := &http.Client{
		Timeout:   time.Duration(5 * time.Hour),
		Transport: transport,
	}

	resp, err := client.Do(req)
	defer resp.Body.Close()

	if err != nil || resp.StatusCode != 200 {
		fmt.Printf("Return err %v \n", err)
	}

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		fmt.Println("Failed to parse the response content")
	}

	fmt.Println("Body : %s", body)
}

func test_httpclient() {

	// test_basic_http()

	// test_basic_cycle_network_request()

}
