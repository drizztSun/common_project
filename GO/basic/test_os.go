package main

import (
	"bufio"
	"fmt"
	"io"
	"io/ioutil"
	"os"
	"os/signal"
	"syscall"
)

func test_os_read_file() {

	data, err := ioutil.ReadFile("/tmp/test")

	if err != nil {
		return
	}

	fmt.Println("content ", string(data))

	f, err := os.Open("tmp/test")
	if err != nil {
		return
	}

	b1 := make([]byte, 5)
	n1, err := f.Read(b1)
	if err != nil {
		return
	}

	fmt.Printf("%d bytes %s\n", n1, string(b1))

	o2, err := f.Seek(6, 0)
	if err != nil {
		return
	}
	b2 := make([]byte, 2)
	n2, err := f.Read(b2)
	if err != nil {
		return
	}

	fmt.Printf("%d bytes @ %d, %s\n", n2, o2, string(b2))

	o3, err := f.Seek(6, 0)
	if err != nil {
		return
	}
	b3 := make([]byte, 2)
	n3, err := io.ReadAtLeast(f, b3, 2)
	if err != nil {
		return
	}
	fmt.Printf("%d read @  %d, %s\n", n3, o3, string(b3))

	_, err = f.Seek(0, 0)
	if err != nil {
		return
	}

	r4 := bufio.NewReader(f)
	b4, err := r4.Peek(5)
	if err != nil {
		return
	}

	fmt.Printf("5 bytes %s \n", string(b4))

	dir, err := os.Getwd()
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(dir)
}

func test_parameters() {

	fmt.Println("Env, SYSTEMDRIVE : ", os.Getenv("SYSTEMDRIVE"))

	fmt.Println("Env, ProgramFile : ", os.Getenv("PROGRAMFILE"))

	os.Setenv("NAME", "gopher")
	os.Setenv("BURROW", "/usr/gopher")

	fmt.Printf("%s lives in %s \n", os.Getenv("NAME"), os.Getenv("BURROW"))

}

func test_signal() {

	{
		// Resigter a channel 'term', and signal.Notify register it listern to system event, defined in 'signals'.
		signals := []os.Signal{os.Interrupt, syscall.SIGTERM, syscall.SIGSEGV}
		term := make(chan os.Signal, len(signals))
		signal.Notify(term, signals...)

		// Listern to system signal
		s := <-term
		fmt.Println(s)
	}

	{
		// Set up channel on which to send signal notifications.
		// We must use a buffered channel or risk missing the signal
		// if we're not ready to receive when the signal is sent.
		c := make(chan os.Signal, 1)

		// Passing no signals to Notify means that
		// all signals will be sent to the channel.
		signal.Notify(c)

		// Block until any signal is received.
		s := <-c
		fmt.Println("Got signal:", s)
	}
}

func Test_os() {

	test_os_read_file()

	test_parameters()

	test_signal()
}
