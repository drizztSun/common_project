package main

import (
	"bufio"
	"fmt"
	"net"
)

/*
Package net provides a portable interface for network I/O, including TCP/IP, UDP, domain name resolution, and Unix domain sockets.

Although the package provides access to low-level networking primitives, most clients will need only the basic interface provided by the Dial,

Listen, and Accept functions and the associated Conn and Listener interfaces. The crypto/tls package uses the same interfaces and similar Dial and Listen functions.

The Dial function connects to a server:
*/

func test_basic_tcp_client() {

	conn, err := net.Dial("tcp", "golang.org:8080")

	if err != nil {
		fmt.Println("Failed to connect to golang.org")
		return
	}

	fmt.Fprintf(conn, "GET / HTTP/1.0 \r\n\r\n")

	status, err := bufio.NewReader(conn).ReadString('\n')

	if err != nil {
		fmt.Println("Failed to read response")
		return
	}

	fmt.Println("Status %d", status)
}

func test_basic_tcp_server() {

	ln, err := net.Listen("tcp", ":8080")

	if err != nil {
		fmt.Println("Failed to listen to the port")
	}

	for {
		conn, err := ln.Accept()

		if err != nil {
			fmt.Printf("Failed to accept %v", err)
			return
		}

		go handlerConnection(conn)
	}
}

func handlerConnection(conn *net.Conn) {

	request, err := bufio.NewReader(conn).ReadString('\n')

	if err != nil {
		fmt.Printf("Failed to read request %v", err)
	}

	fmt.Print("Request is %s \n", request)
}
