package main

import (
	"encoding/json"
	"fmt"
	"time"
	"bytes"
)

type TestJsonC struct {
	Title string `json:"title"`
	Name string `json:productname`
	Time time.Time `json:time`
}

func test_json_basic() {

	d := TestJsonC {
		Title : "test_name",
		Name : "common_project",
		Time : time.Now(),
	}

	// Marshal
	data, err := json.Marshal(d)
	if err != nil {
		fmt.Println("Json Marshal err : ", err)
		return
	}
	fmt.Printf("Content : \n %s \n", data)
	d2 := TestJsonC{}

	// Unmarshal 
	if err := json.Unmarshal(data, &d2); err != nil {
		fmt.Println("Josn Unmarshal err : ", err)
		return
	}

	fmt.Printf("Title : %s = %s \n", d.Title, d2.Title)
	fmt.Printf("Name : %s = %s \n", d.Name, d2.Name)
	fmt.Printf("Time : %v = %v \n", d.Time, d2.Time)

	// MarshalIndent
	data2, err := json.MarshalIndent(d, "<prefix>", "<indent>")
	if err != nil {
		fmt.Println("Json MarhsalIndent err ", err)
		return
	}
	
	fmt.Printf("Marshal Indent Content : \n %s \n", data2)

	// Validate
	goodJSON := `{"example": 1}`
	badJSON := `{"example":2:]}}`

	fmt.Println(json.Valid([]byte(goodJSON)), json.Valid([]byte(badJSON)))

	// HTMLEscape
	var htmlout bytes.Buffer
	json.HTMLEscape(&htmlout, data2)
	fmt.Printf("HTMLEscape content : \n %s \n", htmlout)

	// Compact
	var compactOut bytes.Buffer
	if err := json.Compact(&compactOut, data); err != nil {
		fmt.Println("Json Compact err ", err)
		return
	}
	fmt.Printf("Compact content: \n %s \n", compactOut)

	// Indent
	var out bytes.Buffer
	if err := json.Indent(&out, data, "=", "\t"); err != nil {
		fmt.Println("Json Indent err ", err)
		return
	}
	fmt.Printf("Indent Content : \n %s \n", out)


}

func test_json() {

	fmt.Println(" --- JSON Sta --- ")

	test_json_basic()

	fmt.Println(" --- JSON End --- ")
}