package main

import (
	"net"
	"io"
	"fmt"
	"os"
	"time"
	"bytes"
	"encoding/binary"
	"crypto/tls"
)

func test_basic_sync_server() {

	// Writing down a synchrized model 
	l, err := net.Listen("tcp", "localhost:8080")
	if err != nil {
		fmt.Printf("Error on listen : %v", err)
		return
	}

	for {
		// wait any connection 
		conn, err := l.Accept()
		if err != nil {
			fmt.Printf("Error on accept : %v", err)
			continue
		}

		// because of only one gorountine, so working as synchronized model
		io.Copy(os.Stderr, conn)
		conn.Close()
	}
}


func test_basic_async_server() {

	l, err := net.Listen("tcp", "localhost:8087")
	if err != nil {
		fmt.Printf("Error on listen : %v \n", err)
	}

	for {
		conn, err := l.Accept()
		if err != nil {
			fmt.Printf("Error on accept : %v \n", err)
			continue
		}

		// for Async model, you have to creaet a go routine to handle this requirement,
		// then main rountine can go back to wait next requirement
		go copyToStderr(conn)

		// exsample for local proxuy
		go proxy(conn)

		//
	}
}

type prefixConn struct{
	net.Conn
	io.Reader
}

func (c prefixConn) Read(p []byte) (int, error) {
	// read from io.Reader
	return c.Reader.Read(p)
}

func ParseClientHello([]byte) (string, bool) {
	return "", true
}

// parsing TLS
func proxyit(conn net.Conn) {

	defer conn.Close()
	conn.SetReadDeadline(time.Now().Add(30 * time.Second))

	var buf bytes.Buffer
	if _, err := io.CopyN(&buf, conn, 1+2+2); err != nil {
		fmt.Println(err)
		return
	}

	length := binary.BigEndian.Uint16(buf.Bytes()[3:5])
	if _, err := io.CopyN(&buf, conn, int64(length)); err != nil {
		fmt.Println(err)
		return
	}

	ch, ok := ParseClientHello(buf.Bytes())
	if ok {
		fmt.Printf("Get the connection with SNI %s", ch)
	}

	c := prefixConn{
		Conn : conn,
		Reader : io.MultiReader(&buf, conn),
	}

	conn.SetReadDeadline(time.Time{})
	proxy(c)

	cert, err := tls.LoadX509KeyPair("localhost.pem", "localhost-key.pem")
	if err != nil {
		fmt.Println(err)
	}
	config := &tls.Config{Certificates : []tls.Certificate{cert}}
	tlsConn := tls.Server(c, config)
	copyToStderr(tlsConn)
}

/*
net package automatically uses the "splice system call" on linux, when copying data between TCP connections in TCPConn.ReadForm.
as called vy io.Copy The result is faster and eficient TCP proxying

splice(2) moves date between two file descriptors, without copying between kernel address space and user address address space
*/
func proxy(conn net.Conn) {
	defer conn.Close()

	remote, err := net.Dial("tcp", "gophercon.org:443")
	if err != nil {
		fmt.Printf("Finished with Err : %v", err)
		return
	}

	go io.Copy(remote, conn)
	io.Copy(conn, remote)
}

func copyToStderr(conn net.Conn) {

	// without timeout
	// n, err := io.Copy(os.Stderr, conn)
	// fmt.Printf("Copied %d bytes; finished with Err :%v \n", n, err)
	defer conn.Close()
	for {
		conn.SetReadDeadline(time.Now().Add(5 * time.Second))
		var buf [128]byte
		n, err := conn.Read(buf[:])
		if err != nil {
			fmt.Printf("Finished with Err : %v", err)
			return
		}
		os.Stderr.Read(buf[:n])
	}
}