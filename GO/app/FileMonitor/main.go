package main

import (
	"context"
	"fmt"
	"io/ioutil"
	//"os"
	"regexp"
	//"runtime"
	"strings"
	"time"
)

type FileMonitorListener struct {
	Listener

	FilePath string
	Mode     int
}

func (l FileMonitorListener) Listen(path string, mode int, data interface{}) {

	fmt.Println(path)
}

var (
	WaitEvent chan struct{}
)

func main() {
	fmt.Println("--- FileMonitor start ---")

	inifile := "./files/cfg.ini"
	readConfigini(inifile)

	w, err := NewFileMonitor()

	if err != nil {
		return
	}

	c := FileMonitorListener{
		FilePath: "/Users/yusun/version",
		Mode:     Create | Write | Remove | Rename,
	}

	c2 := FileMonitorListener{
		FilePath: "/Applications/Confer.app/version",
		Mode:     Create | Write | Remove | Rename,
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

func readConfigini(path string) error {

	data, err := ioutil.ReadFile(path)

	if err != nil {
		fmt.Printf("Err: file read  %s", err)
		return err
	}

	content := string(data)

	{
		rule, _ := regexp.Compile(`DeviceId=([a-z|0-9|A-Z]+)`)
		result := rule.FindAllString(content, -1)
		if len(result) != 0 {
			version := strings.TrimLeft(result[0], `DeviceId=`)
			if version != "b0514978e64e345f9bdbf180f4dc79f5499f0a5bb36dca4b5849fb8a3a210f17" {
				fmt.Println("Wrong")
			}
			fmt.Println("Version is : ", version)
		}
	}


	{
		rule, _ := regexp.Compile(`RegistrationId=([a-z|0-9|A-Z|-]+)`)
		result := rule.FindAllString(content, -1)
		if len(result) != 0 {
			RegId := strings.Split(strings.TrimLeft(result[0], `RegistrationId=`), `-`)
			if len(RegId) == 2 {
				fmt.Println("RegistrationId : ", RegId[1])
			}
		}
	}

	return nil
}

func readfile(path string) error {

	data, err := ioutil.ReadFile(path)

	if err != nil {
		fmt.Printf("Err: file read  %s", err)
		return err
	}

	fmt.Printf("file content : %s", string(data))

	content := string(data)

	rule, _ := regexp.Compile(`VERSION="([^\"]+)"`)
	result := rule.FindAllString(content, -1)
	if len(result) != 0 {
		//rule2, _ := regexp.Compile(`([^\"]+)`)
		//version := rule2.FindAllString(result[0], -1)[1]

		version := strings.TrimLeft(strings.TrimRight(result[0], `\"`), `VERSION=\"`)
		fmt.Println("Version is : ", version)
	}

	return nil
}
