package main

import (
	"fmt"
	"io"
	"os"
	"runtime"
	"sync"
)

/*
Splitting the input
While buffering I/O reads is critical to improving performance, calling ReadByte() and checking for errors in a loop introduces a lot of unnecessary overhead.
We can avoid this by manually buffering our read calls, rather than relying on bufio.Reader.

To do this, we will split our input into buffered chunks that can be processed individually.
Fortunately, to process a chunk, the only thing we need to know about the previous chunk (as we saw earlier) is if its last character was whitespace.

Let's write a few utility functions:
*/
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

	filePath := "./wc-test.txt"
	if len(os.Args) > 1 {
		filePath = os.Args[1]
	}

	bufferReader := NewFileBufferReader(filePath)
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

	fmt.Println("total")
}
