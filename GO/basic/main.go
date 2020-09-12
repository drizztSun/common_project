package main

import (
	"fmt"
)

func maximalSquare_dp(matrix [][]byte) int {

	minInt := func(a, b int) int {
		if a > b {
			return b
		}
		return a
	}

	m, n := len(matrix), len(matrix[0])
	dp := make([][]int, m)
	res := 0

	for i := range dp {
		dp[i] = make([]int, n)
	}

	for i := range dp {
		for j := range dp[i] {

			if (i == 0 || j == 0) && matrix[i][j] == '1' {
				dp[i][j] = 1
			} else if matrix[i][j] == '1' {
				dp[i][j] = 1 + minInt(minInt(dp[i-1][j-1], dp[i-1][j]), minInt(dp[i-1][j-1], dp[i][j-1]))
			} else {
				dp[i][j] = 0
			}

			if res < dp[i][j] {
				res = dp[i][j]
			}
		}
	}

	return res * res
}

func main() {
	fmt.Println("--- basic main function ---")

	maximalSquare_dp([][]byte{{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}})

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
