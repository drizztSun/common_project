package main

import (
	"fmt"
	"mime"
	"io"
	"io/ioutil"
	"bytes"
)

func test_basic_mime() {


}

func test_basic_decode() {
	dec := new(mime.WordDecoder)
	header, err := dec.Decode("=?utf-8?q?=C2=A1Hola,_se=C3=B1or!?=")
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(header)

	dec.CharsetReader = func(charset string, input io.Reader) (io.Reader, error) {
		switch charset {
		case "x-case":
			content, err := ioutil.ReadAll(input)
			if err != nil {
				fmt.Println(err)
				return nil, err
			}
			return bytes.NewReader(bytes.ToUpper(content)), nil
		default:
			return nil, fmt.Errorf("unhandled charset %q", charset)
		}
	}

	header, err = dec.Decode("=?x-case?q?hello!?=")
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(header)
}

func test_basic_decodeHeader() {

	dec := new(mime.WordDecoder)
	header, err := dec.DecodeHeader("=?utf-8?q?=C3=89ric?= <eric@example.org>, =?utf-8?q?Ana=C3=AFs?= <anais@example.org>")
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(header)

	header, err = dec.DecodeHeader("=?utf-8?q?=C2=A1Hola,?= =?utf-8?q?_se=C3=B1or!?=")
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(header)

	dec.CharsetReader = func(charset string, input io.Reader) (io.Reader, error) {
		switch charset {
		case "x-case":
			content, err := ioutil.ReadAll(input)
			if err != nil {
				return nil, err
			}
			return bytes.NewReader(bytes.ToUpper(content)), nil
		default:
			return nil, fmt.Errorf("unhandled charset %q", charset)
		}
	}

	header, err = dec.DecodeHeader("=?x-case?q?hello_?= =?x-case?q?world!?=")
	if err != nil {
		fmt.Println(err)
	}

	fmt.Println(header)
}

func test_basic_encode() {
	fmt.Println(mime.QEncoding.Encode("utf-8", "¡Hola, señor!")) // =?utf-8?q?=C2=A1Hola,_se=C3=B1or!?=
	fmt.Println(mime.QEncoding.Encode("utf-8", "Hello!")) // Hello!
	fmt.Println(mime.BEncoding.Encode("UTF-8", "¡Hola, señor!")) // =?UTF-8?b?wqFIb2xhLCBzZcOxb3Ih?=
	fmt.Println(mime.QEncoding.Encode("ISO-8859-1", "Caf\xE9")) // =?ISO-8859-1?q?Caf=E9?=
}

func test_mime() {

	test_basic_mime()

	test_basic_decode()
	
}