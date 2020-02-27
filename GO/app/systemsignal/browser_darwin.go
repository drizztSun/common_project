package main

import (
	"bytes"
	"fmt"
	"sort"
	"strings"
)

const (
	browserChrome           string = "Chrome"
	browserEdge                    = "Edge"
	browserFirefox                 = "Firefox"
	browserInternetExplorer        = "Internet Explorer"
	browserOpera                   = "Opera"
	browserSafari                  = "Safari"

	CFBundleShortVersionString string = "CFBundleShortVersionString"
	CFBundleVersion            string = "CFBundleVersion"
)

var browserBundleIDs = map[string][]string{
	"com.google.Chrome":       []string{browserChrome, CFBundleShortVersionString},
	"org.mozilla.firefox":     []string{browserFirefox, CFBundleShortVersionString},
	"com.operasoftware.Opera": []string{browserOpera, CFBundleVersion},
	"com.apple.Safari":        []string{browserSafari, CFBundleShortVersionString},
}

// Browser browser struct
type Browser struct {
	Name    string `json:"name"`
	Version string `json:"version"`
}

// This function will use the defaults code to read the bundle ID, and return true if its a browser.
func isBrowser(path string) (val bool, name string, field string) {
	stdout := &bytes.Buffer{}
	stderr := &bytes.Buffer{}
	defer stdout.Reset()
	defer stderr.Reset()
	err := run(stdout, stderr, "", "/usr/bin/defaults", "read", path, "CFBundleIdentifier")
	if err == nil {
		value := strings.TrimSpace(stdout.String())
		if val, ok := browserBundleIDs[value]; ok {
			// Found a browser
			return true, val[0], val[1]
		}
	} else {
		fmt.Printf("Unable to read the defaults for %s, %s", path, err.Error())
		return false, "", ""
	}

	return false, "", ""
}

func getVersion(path, field string) (version string) {
	stdout := &bytes.Buffer{}
	stderr := &bytes.Buffer{}
	defer stdout.Reset()
	defer stderr.Reset()
	version = ""
	//err := run(stdout, stderr, "", "/usr/bin/defaults", "read", path, "CFBundleShortVersionString")
	// err := run(stdout, stderr, "", "/usr/bin/defaults", "read", path, "CFBundleVersion")
	err := run(stdout, stderr, "", "/usr/bin/defaults", "read", path, field)
	if err == nil {
		version = strings.TrimSpace(stdout.String())
	}
	return version
}

func GetBrowsers() []*Browser {

	newBrowsers := []*Browser{}

	browserVersionMap := make(map[string][]string)

	InfoPath := "/Contents/Info.plist"
	apps := GetMacBrowserLocations()
	for _, app := range apps {
		fullpath := fmt.Sprintf("%s/%s", app, InfoPath)
		browser, browserName, field := isBrowser(fullpath)
		if browser {
			version := getVersion(fullpath, field)
			if version == "" {
				fmt.Printf("Unable to get version for - %s", browserName)
			}
			browserVersionMap[browserName] = append(browserVersionMap[browserName], version)
		}
	}

	// Get list of keys, then sort them, go through those in order, and then insert them into the slice.
	keys := make([]string, len(browserVersionMap))
	i := 0
	for k := range browserVersionMap {
		keys[i] = k
		i++
	}

	sort.Strings(keys)

	for _, k := range keys {
		v := browserVersionMap[k]
		for _, version := range v {
			newBrowsers = append(newBrowsers, &Browser{Name: k, Version: version})
		}
	}

	return newBrowsers
}
