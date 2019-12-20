package main

import (
	"crypto/hmac"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"os"
)

/*
Package hmac implements the Keyed-Hash Message Authentication Code (HMAC) as defined in U.S. Federal Information Processing Standards Publication 198. An HMAC is a cryptographic hash that uses a key to sign a message. The receiver verifies the hash by recomputing it using the same key.

Receivers should be careful to use Equal to compare MACs in order to avoid timing side-channels:

// ValidMAC reports whether messageMAC is a valid HMAC tag for message.
func ValidMAC(message, messageMAC, key []byte) bool {
	mac := hmac.New(sha256.New, key)
	mac.Write(message)
	expectedMAC := mac.Sum(nil)
	return hmac.Equal(messageMAC, expectedMAC)
}
*/

func test_hmac_basic() {

	{
		key := []byte("123456")
		fmt.Println("hex key : ", hex.EncodeToString(key))

		mac := hmac.New(sha256.New, key)

		lines := []string{
			"Testing content for unit-test",
			"	\n ",
			"use it for eaaclient functional",
		}

		for _, line := range lines {
			mac.Write([]byte(line))
		}

		out := mac.Sum(nil)
		fmt.Println("hmac res: %s", out)

		checksum := hex.EncodeToString(out)
		fmt.Println("checksum : ", checksum)

		c, err := hex.DecodeString(checksum)
		if err != nil {
			fmt.Println("hex decode err, ", err)
		}

		if !hmac.Equal(out, c) {
			fmt.Println("hmac equal gets not-equal result")
		}
	}

}

/*
hex implements hexadecimal encoding and decoding.
*/
func test_hex_basic() {

	{
		src := []byte("Hello Gopher")
		dst := make([]byte, hex.EncodedLen(len(src)))

		n := hex.Encode(dst, src)
		if n == len(dst) {
			fmt.Println("encoding good")
		}

		res := make([]byte, hex.DecodedLen(len(dst)))
		m, err := hex.Decode(res, dst)
		if err == nil || m != len(src) {
			fmt.Println("Decode error")
		}
	}

	{
		encodedstr := hex.EncodeToString([]byte("Hello Gopher"))

		if res, err := hex.DecodeString(encodedstr); err != nil {
			fmt.Println("decode res %s", res)
		}
	}

	{
		// Dumper
		// Dumper returns a WriteCloser that writes a hex dump of all written data to w.
		// The format of the dump matches the output of `hexdump -C` on the command line.

		lines := []string{
			"Go is an open source programming language.",
			"\n",
			"We encourage all Go users to subscribe to golang-announce.",
		}

		stdoutdumper := hex.Dumper(os.Stdout)

		defer stdoutdumper.Close()

		for _, line := range lines {
			stdoutdumper.Write([]byte(line))
		}
	}

	{
		// Dump
		// Dump returns a string that contains a hex dump of the given data.
		// The format of the hex dump matches the output of `hexdump -C` on the command line.
		content := []byte("Go is an open source programming language.")

		fmt.Printf("%s", hex.Dump(content))
	}
}

func test_hmac_hex() {

	test_hmac_basic()

	test_hex_basic()
}
