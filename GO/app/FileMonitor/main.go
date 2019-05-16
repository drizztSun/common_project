package main

import (
	"fmt"
	"time"
	"io/ioutil"
	"context"
)

type FileMonitorListener struct {
	Listener

	FilePath string
	Mode int

} 

func (l FileMonitorListener) Listen(path string, mode int, data interface{}) {

	fmt.Println(path)
}

var (
	WaitEvent chan struct{}
)

func main() {
	fmt.Println("--- FileMonitor start ---")

	readfile("/Applications/Confer.app/version")


	w, err := NewFileMonitor()
	if err != nil {
		return
	}

	c := FileMonitorListener{
		FilePath : "/Users/yusun/version",
		Mode :  Create|Write|Remove|Rename,
	}

	c2 := FileMonitorListener{
		FilePath : "/Applications/Confer.app/version",
		Mode :  Create|Write|Remove|Rename,
	}


	w.AddListener(c.FilePath, c.Mode, c)
	w.AddListener(c2.FilePath, c2.Mode, c2)


	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()
	w.StartMointor(ctx)

	select {
	case <-time.After(100 * time.Minute):
		fmt.Println("Time to quit")
	}

	fmt.Println("--- FileMonitor end ---")
} 

func readfile(path string) error {

	data, err := ioutil.ReadFile(path);

	if err != nil {
		fmt.Printf("Err: file read  %s", err)
		return err
	}

	fmt.Printf("file content : %s", data)

	return nil
}