package main

import (
	"bytes"
	"fmt"
	"io"
	"io/ioutil"
	"os"
	"runtime"
	"time"
)

var (
	LogFiles = []string{"./stdout.1.txt", "./stdout.2.txt", "./stdout.3.txt", "./stdout.4.txt"}
	index    = 0
)

func test_redirect() {

	fmt.Println("Output test_redirect")
	old := os.Stdout // keep backup of the real stdout
	r, w, _ := os.Pipe()
	os.Stdout = w

	print()

	outC := make(chan string)
	// copy the output in a separate goroutine so printing can't block indefinitely
	go func() {
		var buf bytes.Buffer
		io.Copy(&buf, r)
		outC <- buf.String()
	}()

	// back to normal state
	w.Close()
	os.Stdout = old // restoring the real stdout
	out := <-outC

	// reading our temp stdout
	fmt.Println("previous output:")
	fmt.Print(out)
}

func print() {
	fmt.Println("output")
}

func test_redirect_to_file() {

	// setting stdout to a file
	// fname := filepath.Join(os.TempDir(), "stdout")
	fname := "./stdout.txt"
	fmt.Println("stdout is now set to", fname)
	old := os.Stdout            // keep backup of the real stdout
	temp, _ := os.Create(fname) // create temp file
	os.Stdout = temp

	print()

	// back to normal state
	temp.Close()
	os.Stdout = old // restoring the real stdout

	// reading our temp stdout
	fmt.Println("previous output:")
	out, _ := ioutil.ReadFile(fname)
	fmt.Print(string(out))
}

func watchFileSize() {

	var (
		timeInterval  = 30 * time.Second
		livenessTimer = time.NewTimer(timeInterval)
		logfile       = "stdout.txt"
		stop          = make(chan struct{})
		stopWritting  = make(chan struct{})
	)

	f, err := os.OpenFile(logfile, os.O_RDWR|os.O_CREATE, 0755)
	if err != nil {
		return
	}

	rescueH := os.Stdout
	//old := os.Stdout
	os.Stdout = f

	go func(stopWritting chan struct{}) {
		fmt.Println("--- start writing routine ---")
		for {

			beginWritting := time.NewTimer(20 * time.Millisecond)

			select {
			case <-stopWritting:
				break
			case <-beginWritting.C:
				fmt.Fprintln(f, "This is Helllo world check")
				fmt.Fprintln(rescueH, "This is Hello world from rescue")
			}
		}
		fmt.Println("--- end writing routine ---")
	}(stopWritting)

	times := 10
	i := 0

	for times > 0 {
		select {
		case <-livenessTimer.C:

			fmt.Println("--- wakeup check file ---")
			if err != nil {
				return
			}

			info, err := f.Stat()
			if err == nil {
				if info.Size() > 1024 {

					i += 1
					if i >= len(LogFiles) {
						i %= len(LogFiles)
					}

					os.Rename(logfile, LogFiles[i])
					oldf := f
					f, err = os.OpenFile(logfile, os.O_RDWR|os.O_CREATE, 0755)
					oldf.Close()

				}
			}

			livenessTimer.Stop()
			livenessTimer.Reset(timeInterval)

			times -= 1

		case <-stop:
			break
		}
	}

	stopWritting <- struct{}{}
	f.Close()
	fmt.Println("--- end watch file size ---")
}

func useRotateLog() {

	var (
		stopWritting = make(chan struct{})
		totalWait    = time.NewTimer(1 * time.Minute)
	)

	fmt.Println("--- start writing routine ---")

	//out := stdout.Cur
	//err := stderr.Cur

loop:
	for {

		beginWritting := time.NewTimer(20 * time.Millisecond)

		select {
		case <-stopWritting:
			break
		case <-beginWritting.C:
			fmt.Println("--output--")
			fmt.Fprintln(stdout.Cur, "This is Helllo world check")
			fmt.Fprintln(stderr.Cur, "This is Hello world from rescue")
			// fmt.Fprintln(out, "This is Helllo world check")
			// fmt.Fprintln(err, "This is Hello world from rescue")
		case <-totalWait.C:
			break loop
		}
	}
	logContextCancel()
	fmt.Println("--- end writing routine ---")
}

func main() {

	fmt.Println("--- start --- ")

	a := runtime.GOOS
	fmt.Printf("Current OS version: %s\n", a)

	// test_redirect()

	// test_redirect_to_file()

	// watchFileSize()

	useRotateLog()
}
