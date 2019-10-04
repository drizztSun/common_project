package main

import (
	"fmt"
	"sync"
	"context"
	//"time"
	"github.com/fsnotify/fsnotify"
)

// File mode status 
const (
	Create = int(fsnotify.Create)
	Write = int(fsnotify.Write)
	Remove = int(fsnotify.Remove)
	Rename = int(fsnotify.Rename)
	Chmod = int(fsnotify.Chmod)
)

// Listener to file change
type Listener interface {
	Listen(target string, event int, data interface{})
}

// Monitor to 
type Monitor interface {
	StartMointor(ctx context.Context)
	AddListener(path string, mode int, listener Listener) error
	RemoveListener(path string, mode int, listener Listener) error
}

type item struct {
	mode int

	listener Listener
}

// FileMonitor help to monitor file status, and call listener func to notify, if file status get changed.
type FileMonitor struct {

	Monitor

	wFsNotifier *fsnotify.Watcher

	mtx sync.Mutex

	Targets map[string][]item
}

// NewFileMonitor create an instance of this monitor
//func NewFileMonitor(ctx context.Context) (Monitor, error) {
func NewFileMonitor() (Monitor, error) {
	fs, err := fsnotify.NewWatcher()
	if err != nil {
		return nil, err
	}

	w := &FileMonitor{
		wFsNotifier : fs,
		Targets : make(map[string][]item),
		//Ctx : ctx,
	}

	//go w.StartMointor()

	return w, nil
}

// StartMointor should be a goroutine start function.
func (mon *FileMonitor) StartMointor(ctx context.Context) {

	fmt.Println("-- startMonitor --- ")
	
	go func () {
		for{
			select {
			case event := <- mon.wFsNotifier.Events:
				mon.mtx.Lock()
				fmt.Println("Event ", event)
				if items, ok := mon.Targets[event.Name]; ok {
	
					for _, c := range items {
						if c.mode & int(event.Op) != 0 {
							c.listener.Listen(event.Name, int(event.Op), nil)
						}
					}
				}
				mon.mtx.Unlock()
			case err := <- mon.wFsNotifier.Errors:
				fmt.Printf("Err : %s\n", err)
			//case <-mon.Ctx.Done(): 
			case <-ctx.Done():
				fmt.Println("Cancel and exit")
			}
		}
	} ()
}

// AddListener put a new item into monitor listener array
func (mon *FileMonitor) AddListener(path string, mode int, listener Listener) error {

	mon.mtx.Lock()
	defer mon.mtx.Unlock()

	if _, ok := mon.Targets[path]; !ok {
		if err := mon.wFsNotifier.Add(path); err != nil {
			fmt.Printf("Err : %s\n", err)
			return err
		}
		mon.Targets[path] = make([]item, 0)
	}

	mon.Targets[path] = append(mon.Targets[path], item{mode, listener})

	return nil
}

// RemoveListener remove the existing item from monitor listen array
func (mon *FileMonitor) RemoveListener(path string, mode int, listener Listener) error {

	mon.mtx.Lock()
	defer mon.mtx.Unlock()
	
	if _, ok := mon.Targets[path]; !ok {
		return nil
	}

	for i, c := range mon.Targets[path] {
		if c.mode == mode && c.listener == listener {
			mon.Targets[path] = append(mon.Targets[path][:i], mon.Targets[path][i+1:]...)
			break
		}		
	}
	return nil
}