package main

import (
	"fmt"
	"io"
	"os"
	"runtime"
	"sync"
)

type Counter struct {
	WordCount int32
	LineCount int32
}

type FileBufferReader struct {
	mtx             sync.Mutex
	File            *os.File
	LastCharIsSpace bool
}

type ChunkBuffer struct {
	Buffer          []byte
	LastCharIsSpace bool
}

func isSpace(b byte) bool {
	return b == ' ' || b == '\t' || b == '\n' || b == '\v' || b == '\f'
}

func NewFileBufferReader(path string) *FileBufferReader {

	file, err := os.Open(path)
	if err != nil {
		panic(err)
	}

	return &FileBufferReader{File: file, LastCharIsSpace: true}
}

func (c *FileBufferReader) ReadChunk() (*ChunkBuffer, error) {
	c.mtx.Lock()
	defer c.mtx.Unlock()

	buffer := make([]byte, 1024)
	cnt, err := c.File.Read(buffer)
	if err != nil {
		return nil, err
	}

	chunk := ChunkBuffer{Buffer: buffer[:cnt], LastCharIsSpace: c.LastCharIsSpace}
	c.LastCharIsSpace = isSpace(buffer[cnt-1])

	return &chunk, nil
}

func ReadFileStatistics(file *FileBufferReader, counter chan Counter) {

	cnt := Counter{}
	preCharIsSpace := false

	for {
		chunk, err := file.ReadChunk()
		if err != nil {
			if err == io.EOF {
				fmt.Println(err)
				break
			} else {
				panic(err)
			}
		}

		for _, b := range chunk.Buffer {

			switch b {
			case '\n':
				cnt.LineCount++
				preCharIsSpace = true
			case ' ', '\t', '\r', '\v', '\f':
				preCharIsSpace = true
			default:
				if preCharIsSpace {
					cnt.WordCount++
					preCharIsSpace = false
				}
			}
		}
	}

	counter <- cnt
}

func main() {

	if len(os.Args) < 2 {
		panic("No file specified")
	}

	bufferReader := NewFileBufferReader(os.Args[1])
	workers := runtime.NumCPU()
	buff := make(chan Counter)

	for i := 0; i < workers; i++ {
		go ReadFileStatistics(bufferReader, buff)
	}

	totalResult := Counter{}
	for i := 0; i < workers; i++ {
		cnt := <-buff
		totalResult.LineCount += cnt.LineCount
		totalResult.WordCount += cnt.WordCount
	}

}
