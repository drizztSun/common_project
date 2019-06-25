package main

import (
	"fmt"
	"bytes"
	"os"
	"encoding/base64"
	"io"
)

/*
Package bytes implements functions for the manipulation of byte slices. It is analogous to the facilities of the strings package.
*/

func test_basic_bytes() {

	{
		var b bytes.Buffer
		b.Write([]byte("Hello"))
		fmt.Fprintf(&b, " World!")
		b.WriteTo(os.Stdout)

		c := bytes.NewBuffer([]byte("Hello world!"))
		c.WriteTo(os.Stdout)
	}

	{
		buf := bytes.NewBufferString("R29waGVycyBydWxlIQ==")
		dec := base64.NewDecoder(base64.StdEncoding, buf)
		io.Copy(os.Stdout, dec)
	}


	{
		var b bytes.Buffer
		b.Grow(64)
		b.Write([]byte("Hello world!"))
		fmt.Println(b.Len(), b.Cap())


	}


}

func test_bytes() {

	test_basic_bytes()
}