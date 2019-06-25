package main

import (
	"fmt"
	"runtime"
	"strings"
)

func test_basic_runtime(){

}

func test_basic_frames() {

	c := func() {
		// Frames may be used to get function/file/line information for a slice of PC values returned by Callers.
		pc := make([]uintptr, 10)
		n := runtime.Callers(0, pc)
		if n == 0 {
			// No pcs available. Stop now.
			// This can happen if the first argument to runtime.Callers is large.
			fmt.Println("No PC available")
			return
		}
	
		pc = pc[:n] // pass only valid pcs to runtime.CallersFrames
		frames := runtime.CallersFrames(pc)

		// Loop to get frames.
		// A fixed number of pcs can expand to an indefinite number of Frames.
		for {
			frame, more := frames.Next()
			// To keep this example's output stable
			// even if there are changes in the testing package,
			// stop unwinding when we leave package runtime.
			if !strings.Contains(frame.File, "runtime/") {
				break
			}

			// Frame
			fmt.Println("-more: %v | F: %s F: %s, L: %d\n", more, frame.File, frame.Function, frame.Line)

			// Func
			funcEntry := frame.Func
			fmt.Println("Entry Address : %d, Name : %s, FileName: ", funcEntry.Entry(), funcEntry.Name())//, funcEntry.FileLine(100))


			if !more {
				break
			}
		}
	}

	b := func() { c() }
	a := func() { b() }
	a()
}

func test_runtime() {

	test_basic_runtime()
}