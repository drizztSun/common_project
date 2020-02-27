// +build darwin

package main

import (
	"strings"
	"unsafe"
)

/*
#cgo CFLAGS: -x objective-c
#cgo LDFLAGS: -framework Foundation -framework CoreServices
#include "mac_browser.h"
*/
import "C"

func cstring(s *C.NSString) *C.char { return C.nsstring2cstring(s) }

func gostring(s *C.NSString) string { return C.GoString(cstring(s)) }

func nsarraylen(arr *C.NSArray) uint { return uint(C.nsarraylen(arr)) }

func nsarrayitem(arr *C.NSArray, i uint) unsafe.Pointer {
	return C.nsarrayitem(arr, C.ulong(i))
}

func cleanPaths(arr *C.NSArray) []string {
	var result []string
	length := nsarraylen(arr)

	for i := uint(0); i < length; i++ {
		nsPath := (*C.NSString)(nsarrayitem(arr, i))
		u := gostring(nsPath)
		u = strings.TrimPrefix(u, "file://")
		result = append(result, u)
	}

	return result
}

// GetMacBrowserLocations returns list of locations of browsers on 64 bit OS
// on 32 bit OS, we return all Apps.
func GetMacBrowserLocations() []string {
	return cleanPaths(C.getBrowsersLocation())
}
