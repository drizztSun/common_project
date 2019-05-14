package main

import (
	"fmt"
	"io"
	"io/ioutil"
	"os"
	"log"
	"bytes"
	"strings"
	filepath "path/filepath"
)

func test_io_basic() {

	fmt.Println("---- test_io_basic start -----")

	r := strings.NewReader("some io.Reader stream to be reader\n")

	if _, err := io.Copy(os.Stdout, r); err != nil {
		log.Fatal(err)
	}

	r1 := strings.NewReader("first Reader \n")
	r2 := strings.NewReader("second Reader \n")
	buf := make([]byte, 8)

	// buf is used here
	if _, err := io.CopyBuffer(os.Stdout, r1, buf); err != nil {
		log.Fatal(err)
	}
	// reuse here also, don't need to reallocate an extra buff
	if _, err := io.CopyBuffer(os.Stdout, r2, buf); err != nil {
		log.Fatal(err)
	}

	// On return, written == n if and only if err == nil.
	if _, err := io.CopyN(os.Stdout, r, 5); err != nil {
		log.Fatal(err)
	}

	buf = make([]byte, 33)
	if _, err := io.ReadAtLeast(r, buf, 4); err != nil {
		log.Fatal(err)
	}
	fmt.Println(buf)

	// buf smaller than minimal read size
	shortBuf := make([]byte, 3)
	if _, err := io.ReadAtLeast(r, shortBuf, 4); err != nil {
		// Err : short buff
		fmt.Println("Err : %s", err)
	}

	// minimal read size bigger than io.Read stream
	longBuf := make([]byte, 64)
	if _, err := io.ReadAtLeast(r, longBuf, 64); err != nil {
		// Err : EOF
		fmt.Println("Err : %s", err)
	}

	buf = make([]byte, 4)
	if _, err := io.ReadFull(r, buf); err != nil {
		log.Fatal(err)
	}

	longBuf = make([]byte, 64)
	if _, err := io.ReadFull(r, longBuf); err != nil {
		// Err : unexpected EOF
		fmt.Println("Err : %s", err)
	}

	fmt.Println("")

	if _, err := io.WriteString(os.Stdout, "Hello world"); err != nil {
		log.Fatal(err)
	}


	lr := io.LimitReader(r, 4)
	if _, err := io.Copy(os.Stdout, lr); err != nil {
		log.Fatal(err)
	}

	r1a := strings.NewReader("first Reader")
	r2a := strings.NewReader("second Reader")
	r3a := strings.NewReader("third Reader")
	rall := io.MultiReader(r1a, r2a, r3a)
	if _, err := io.Copy(os.Stdout, rall); err != nil {
		log.Fatal(err)
	}

	var buf1 bytes.Buffer
	tee := io.TeeReader(r, &buf1)

	printall := func(r io.Reader) {
		b, e := ioutil.ReadAll(r)
		if e != nil {
			log.Fatal(e)
		}

		fmt.Printf("%s", b)
	}

	printall(tee)
	printall(&buf1)

	// SectionReader
	rsr := io.NewSectionReader(r, 5, 17)
	if _, err := io.Copy(os.Stdout, rsr); err != nil {
		log.Fatal(err)
	}

	buf = make([]byte, 6)
	if _, err := rsr.ReadAt(buf, 10); err != nil {
		log.Fatal(err)
	}
	// stream
	fmt.Printf("%s\n", buf)

	// seek new posion, 10 after header
	if _, err := rsr.Seek(10, io.SeekStart); err != nil {
		log.Fatal(err)
	}

	if _, err := rsr.Read(buf); err != nil {
		log.Fatal(err)
	}
	// stream
	fmt.Printf("%s\n", buf)


	fmt.Println(" ---- test_io_basic end ----")
}

func test_pipe() {
	r, w := io.Pipe()

	go func() {
		fmt.Fprint(w, "It is coming for  go routine\n")
		w.Close()
	} ()

	buf := new(bytes.Buffer)
	buf.ReadFrom(r)
	r.Close()
	fmt.Print(buf.String())
}

func test_io_util() {

	r := strings.NewReader("Go is a general-purpose language designed with systems programming in mind.")

	// ReadAll
	b, err := ioutil.ReadAll(r)
	if err != nil {
		log.Fatal(err)
	}
	// Go is a general-purpose language designed with systems programming in mind.
	fmt.Printf("%s\n", b)
	
	// ReadDir
	files, err := ioutil.ReadDir(".")
	if err != nil {
		log.Fatal(err)
	}

	for _, file := range files {
		fmt.Println(file.Name())
	}

	// ReadFile
	content, err := ioutil.ReadFile("./test_io.go")
	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("content : %s", content)

	// TempDir
	//content1 := []byte("temporary file content\n")
	tmpDir, err := ioutil.TempDir("", "tmpfile")
	if err != nil {
		log.Fatal(err)
	}

	defer os.RemoveAll(tmpDir) // clear up
	tmpFn := filepath.Join(tmpDir, "tmpFile")
	if err := ioutil.WriteFile(tmpFn, content, 0666); err != nil {
		log.Fatal(err)
	}

	// TmpFile
	content1 := []byte("temporary file content\n")
	tmpfile, err := ioutil.TempFile("", "example")
	if err != nil {
		log.Fatal(err)
	}

	defer os.Remove(tmpfile.Name()) // clear up

	if _, err := tmpfile.Write(content1); err != nil {
		log.Fatal(err)
	}

	if err := tmpfile.Close(); err != nil {
		log.Fatal(err)
	}


	// Write File
	message := []byte("Hello Gophers!")
	if err := ioutil.WriteFile("tmpfile/tempfile", message, 0644); err != nil {
		log.Fatal(err)
	}


}

func test_io() {

	test_io_basic()

	test_pipe()

	test_io_util()
}

