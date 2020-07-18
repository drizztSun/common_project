package main

import (
	"context"
	"fmt"
	"os"
	"time"
)

// type RL RotateLogRedirector
var (
	ctx, logContextCancel = context.WithCancel(context.Background())
	stdout                = GetStdout(ctx)
	stderr                = GetStderr(ctx)
)

type replaceFunc func(*os.File)

type StdLocator struct {
	FileName string

	Replace replaceFunc

	Cur *os.File

	RotateNum int

	RotateSize int64

	RotateTotal int
}

func GetStdout(ctx context.Context) *StdLocator {
	interval := 20 * time.Millisecond
	r := NewRotateLogRedirector(func(r *os.File) {
		os.Stdout = r
	}, "stdout")
	go r.WatchFileRotation(ctx, interval) // 5 * time.Minute)
	return r
}

func GetStderr(ctx context.Context) *StdLocator {
	interval := 20 * time.Millisecond
	r := NewRotateLogRedirector(func(r *os.File) {
		os.Stderr = r
	}, "stderr")
	go r.WatchFileRotation(ctx, interval) // 5 * time.Minute)
	return r
}

func NewRotateLogRedirector(replace replaceFunc, name string) *StdLocator {

	f, err := os.OpenFile(name+".txt", os.O_RDWR|os.O_CREATE, 0755)
	if err != nil {
		return nil
	}

	res := &StdLocator{
		FileName:    name,
		Replace:     replace,
		Cur:         f,
		RotateNum:   1,
		RotateSize:  1024, // 5 * 1024 * 1024
		RotateTotal: 5,
	}

	res.Replace(res.Cur)

	return res
}

func (locator *StdLocator) WatchFileRotation(ctx context.Context, timeInterval time.Duration) {

	livenessTimer := time.NewTimer(timeInterval)
loop:
	for {

		select {
		case <-ctx.Done():
			fmt.Println("context is Done")
			break loop

		case <-livenessTimer.C:

			livenessTimer.Stop()
			livenessTimer.Reset(timeInterval)

			if info, err := locator.Cur.Stat(); err == nil && info.Size() > locator.RotateSize {

				locator.RotateNum += 1
				if locator.RotateNum > locator.RotateTotal {
					locator.RotateNum %= locator.RotateTotal
				}

				rotateFileName := fmt.Sprintf("%s.%d.txt", locator.FileName, locator.RotateNum)
				if info, err := os.Stat(rotateFileName); err != nil || info.Size() > 0 {
					os.Remove(rotateFileName)
				}

				curName := locator.FileName + ".txt"
				os.Rename(curName, rotateFileName)
				oldf := locator.Cur
				locator.Cur, err = os.OpenFile(curName, os.O_RDWR|os.O_CREATE, 0755)
				// locator.Src = locator.Cur
				locator.Replace(locator.Cur)
				oldf.Close()
			}
		}

	}
	fmt.Println(" --- End Watch file rotation ---")
}
