package main

import (
	"bytes"
	"fmt"
	"io"
	"os"
	"os/exec"
	"strings"
	"time"
)

const (
	amESET   = "ESET"
	amComodo = "Comodo AntiVirus"
	amSophos = "Sophos"
	amClamAV = "Clam AV"

	statusPoor = "poor"
	statusNone = "none"
	statusGood = "good"
)

var antiMalwareToService = map[string]string{
	amESET:   "esets.service",
	amSophos: "sav-protect.service",
	amClamAV: "clamav-freshclam.service",
	amComodo: "cmdavd.service",
}

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

// This function monitors status of a given service.
// The return values are as follows
// StatusGood - if service is active
// Status Poor - if service is installed and not running, or an error occurs when looking for it
// StatusNone - Service is not installed
func GetStatusOfService(serviceName string) (status string) {
	stdout := &bytes.Buffer{}
	stderr := &bytes.Buffer{}

	err := run(stdout, stderr, "", "systemctl", "is-active", serviceName)
	if err != nil {
		fmt.Printf("Unable to get status of %s, error: %s, err detail: %s, out: %s", serviceName, err.Error(), stderr, stdout)
		return statusPoor
	} else {
		lines := strings.TrimSpace(stdout.String())
		if lines == "active" {
			return statusGood
		} else {
			// This command returns inactive for s/w that's not installed too.
			stdout.Reset()
			stderr.Reset()
			err = run(stdout, stderr, "", "systemctl", "status", serviceName)
			if err != nil {
				fmt.Printf("Unable to get status of service %s, error: %s", serviceName, err.Error())
				return statusPoor
			} else {
				lines := strings.TrimSpace(stdout.String())
				if strings.Contains(lines, "could not be found") {
					return statusNone
				} else {
					return statusPoor
				}
			}
		}
	}
}

var antimalwareFailCounter int
var firewallFailCounter int

func setAntiMalware() {

	for _, service := range antiMalwareToService {
		serviceStatus := GetStatusOfService(service)
		fmt.Println("status ", serviceStatus)
	}

}

func setFirewall() {
	stdout := &bytes.Buffer{}
	stderr := &bytes.Buffer{}
	defer stdout.Reset()
	defer stderr.Reset()

	err := run(stdout, stderr, "", "/usr/sbin/ufw", "status")
	if err == nil {
		firewallFailCounter = 1

		value := strings.TrimSpace(strings.Split(stdout.String(), ":")[1])
		if value == "active" {
			fmt.Println("Ubuntu firewall is on")
		}
	} else {
		fmt.Printf("Unable to read the firewall status - %v", err)
		return
	}
}

func main() {

	setAntiMalware()
}
