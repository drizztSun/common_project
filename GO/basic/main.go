package main

import (
	"fmt"
)

func search_beautiful_array(n int, memo map[int][]int) []int {

	if c, ok := memo[n]; ok {
		return c
	}

	odd := search_beautiful_array((n+1)/2, memo)
	even := search_beautiful_array(n/2, memo)

	res := make([]int, len(odd) + len(even))

	b := 0
	for i := range odd {
		res[b] = 2 * odd[i] - 1
		b++
	}

	for j := range even {
		res[b] = 2 * even[j]
		b++
	}

	memo[n] = res
	return res
}

func beautifulArray(N int) []int {

	memo := map[int][]int{1: []int{1}}

	return search_beautiful_array(N, memo)

}

func main() {
	fmt.Println("--- basic main function ---")

	beautifulArray(4)

	// Test_null_interface()

	// Test_set()

	// test_hmac_hex()

	// basic()

	// test_closure()

	// test_json()

	// test_gzip()

	// test_sort()

	// test_struct()

	//Main_test_list()

	// test_array()

	//Test_str()

	//Test_strings()

	// test_uri()

	// test_time()

	// Test_io()

	// Test_strconver()

	// test_json()

	// test_reflect()

	// Test_os()

	// test_json()

	fmt.Println(" --- basic main function end --- ")
}
