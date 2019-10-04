package main

import (
	"context"
	"fmt"
	"io/ioutil"
	"os"
	"regexp"
	//"runtime"
	"strings"
	"time"
)

type FileMonitorListener struct {
	Listener

	FilePath string
	Mode     int

	callback func(path string, mode int, data interface{})
}

func (l FileMonitorListener) Listen(path string, mode int, data interface{}) {

	fmt.Printfln("path %s, mode %d", path, mode)

	if (l.callback != nil) {
		l.callback(path, mode, data)
	}
}

var (
	WaitEvent chan struct{}
)

type CarbonBlackAppMonitor struct {
	Listener

	AppPath string
	targetFile string	
	Mode int

	appMonitor, targetfileMonitor FileMonitorListener

	targetFileCallback func(string, int, interface{});
}

func NewAppMonitor(w Monitor, callback func(string, int, interface{})) *CarbonBlackAppMonitor {

	res := &CarbonBlackAppMonitor {
		AppPath: "/Users/yusun/src/common_project/GO/app/FileMonitor/files/Confer",
		targetFile: "/Users/yusun/src/common_project/GO/app/FileMonitor/files/Confer/cfg.ini",
		Mode: Create | Write | Remove | Rename,
		targetFileCallback: callback,	
	}

	res.targetfileMonitor = FileMonitorListener{FilePath: res.targetFile, Mode: res.Mode, callback: res.targetFileCallback}

	appCallback := func(path string, mode int, data interface{}) {
		if (path != res.AppPath) {
			return
		}

		if (mode & Create == Create) {
			w.AddListener(res.targetfileMonitor.FilePath, res.targetfileMonitor.Mode, res.targetfileMonitor)
		} else if (mode & Remove == Remove) {
			// w.RemoveListener(res.targetfileMonitor.FilePath, res.targetfileMonitor.Mode, res.targetfileMonitor)
		}
	}

	res.appMonitor = FileMonitorListener{FilePath: res.AppPath, Mode: res.Mode, callback: appCallback}

	w.AddListener(res.appMonitor.FilePath, res.appMonitor.Mode, res.appMonitor)

	if (res.targetFile != "") {

		if _, err := os.Stat(res.targetFile); !os.IsNotExist(err) {
			fmt.Println("File existed %s", res.targetFile)
			res.targetFileCallback(res.targetFile, Write, nil)
			w.AddListener(res.targetfileMonitor.FilePath, res.targetfileMonitor.Mode, res.targetfileMonitor)
		}
	}

	return res
}

func (l *CarbonBlackAppMonitor) Listen(path string, mode int, data interface{}) {
	fmt.Println("notified from: ", path)
}

func test() {
	
	fmt.Println("--- FileMonitor start ---")

	w, err := NewFileMonitor()
	if err != nil {
		return
	}

	carbonblack := NewAppMonitor(w, func(path string, mode int, data interface{}) {

		if mode & (Create | Write) != 0 {
			data, _ := ioutil.ReadFile(path)
			rule, _ := regexp.Compile(`RegistrationId=([a-z|0-9|A-Z|-]+)`)
			result := rule.FindAllString(string(data), -1)
			if len(result) != 0 {
				RegID := strings.Split(strings.TrimLeft(result[0], `RegistrationId=`), `-`)
				if len(RegID) == 2 {
					fmt.Println("CarbonBlack Registration ID : %s", RegID[1])
				}
			}
		}
	})

	fmt.Println("Target file %s", carbonblack.targetFile)
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

func main() {
	fmt.Println("--- FileMonitor start ---")

	inifolder := "/Users/yusun/src/common_project/GO/app/FileMonitor/files/Confer"
	// inifile := "/Users/yusun/src/common_project/GO/app/FileMonitor/files/Confer/cfg.ini"

	fmt.Println("inifolder ", inifolder)
	fmt.Println("inifile ", inifile)

	w, err := NewFileMonitor()

	if err != nil {
		return
	}

	
	c := FileMonitorListener{
		FilePath: inifolder,
		Mode:     Create | Write | Remove | Rename,
	}
	

	c2 := FileMonitorListener{
		FilePath: inifile,
		Mode:     Create | Write | Remove | Rename,
	}
	
	err = w.AddListener(c.FilePath, c.Mode, c)
	err = w.AddListener(c2.FilePath, c2.Mode, c2)

	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()
	w.StartMointor(ctx)

	select {
	case <-time.After(100 * time.Minute):
		fmt.Println("Time to quit")
	}

	fmt.Println("--- FileMonitor end ---")
}