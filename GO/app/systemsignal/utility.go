package main

import (
	"fmt"
	"io"
	"os"
	"os/exec"
	"strings"
	"time"
)

// infoChange log signal change
func infoChange(name, currentValue, newValue string) {
	if currentValue == "" {
		fmt.Println("%s set to %s", name, newValue)
	} else {
		fmt.Println("%s changed from %s to %s", name, currentValue, newValue)
	}
}

// run execute the command
func run(stdout, stderr io.Writer, input string, cmd string, args ...string) error {
	c := exec.Command(cmd, args...)
	if input != "" {
		c.Stdin = strings.NewReader(input)
	} else {
		c.Stdin = os.Stdin
	}
	c.Stdout = stdout
	c.Stderr = stderr
	return c.Run()
}

// ISO8601 iso format
func ISO8601(t time.Time) *string {
	utcFormat := t.UTC().Format("2006-01-02T15:04:05.999999999Z0700")
	return &utcFormat
}
