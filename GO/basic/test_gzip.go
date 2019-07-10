package main

import (
	"bytes"
	"io/ioutil"
	"compress/gzip"
	"fmt"
	"os"
	"time"
	"log"
	"io"
)

func test_gzip_basic() {
	var buf bytes.Buffer
	zw := gzip.NewWriter(&buf)

	// Setting the Header fields is optional.
	zw.Name = "a-new-hope.txt"
	zw.Comment = "an epic space opera by George Lucas"
	zw.ModTime = time.Date(1977, time.May, 25, 0, 0, 0, 0, time.UTC)

	_, err := zw.Write([]byte("A long time ago in a galaxy far, far away..."))
	if err != nil {
		log.Fatal(err)
	}

	// VERY BE CAREFUL OF THIS. IT ONLY WRITES THE GZIP CONTNET BACK TO BUFF, ONLY AFTER YOU CALL CLOSE()
	if err := zw.Close(); err != nil {
		log.Fatal(err)
	}

	zr, err := gzip.NewReader(&buf)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("Name: %s\nComment: %s\nModTime: %s\n\n", zr.Name, zr.Comment, zr.ModTime.UTC())

	if _, err := io.Copy(os.Stdout, zr); err != nil {
		log.Fatal(err)
	}

	if err := zr.Close(); err != nil {
		log.Fatal(err)
	}
}

func test_gzip_basic_file() {

	var (
		buf bytes.Buffer
		b []byte
		err error
	)

	if b, err = ioutil.ReadFile("./main.go"); err != nil {
		fmt.Println("err : read file ", err.Error())
		return
	}

	zw := gzip.NewWriter(&buf)
	//zw.Name = "test.txt"
	if _, err = zw.Write([]byte(b)); err != nil {
		return
	}

	if err = zw.Close(); err != nil {
		fmt.Println("err : gzip content ", err.Error())
		return 
	}

	if file, err := os.Create("./main.gz"); err != nil {
		fmt.Println("err : ", err.Error())
		return
	}

	defer file.Close()
	file.Write(buf.Bytes())

	return
}

func test_gzip_basic_file12() ([]byte, error) {
	
	fi, err := os.Open("./basic.go")
    if err != nil {
        return nil, err
    }
    defer fi.Close()

    fz, err := gzip.NewReader(fi)
    if err != nil {
        return nil, err
    }
    defer fz.Close()

    s, err := ioutil.ReadAll(fz)
    if err != nil {
        return nil, err
	}

	file, err := os.Create("./basic.gz")
	if err != nil {
		fmt.Println("err : ", err.Error())
		return s, nil
	}

	file.Write(s)
	file.Close()

	return s, nil
}


func test_gzip_basic_file1() {

	{
		original := "bird and frog"

		// Open a file for writing.
		f, _ := os.Create("./basic1.gz")

		// Create gzip writer.
		w := gzip.NewWriter(f)

		// Write bytes in compressed form to the file.
		w.Write([]byte(original))

		// Close the file.
		w.Close()

		fmt.Println("DONE")
	}

	{
	    // Open the gzip file.
		f, _ := os.Open("./basic1.gz")

		// Create new reader to decompress gzip.
		reader, _ := gzip.NewReader(f)
	
		// Empty byte slice.
		result := make([]byte, 100)
	
		// Read in data.
		count, _ := reader.Read(result)
	
		// Print our decompressed data.
		fmt.Println(count)
		fmt.Println(string(result))		
	}

}

func test_gzip() {

	test_gzip_basic()

	test_gzip_basic_file() 

	test_gzip_basic_file1()

	//test_gzip_basic_file2()
}