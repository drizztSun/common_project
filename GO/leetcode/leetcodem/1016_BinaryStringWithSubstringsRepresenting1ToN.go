package leetcodem

/*

1016. Binary String With Substrings Representing 1 To N


Given a binary string S (a string consisting only of '0' and '1's) and a positive integer N,
return true if and only if for every integer X from 1 to N, the binary representation of X is a substring of S.

 

Example 1:

Input: S = "0110", N = 3
Output: true
Example 2:

Input: S = "0110", N = 4
Output: false
*/

import "strings"

func queryString(S string, N int) bool {

	parts := "0"

    for i := 1; i < N + 1; i++ {

        for j := len(parts) - 1; j >= -1; j-- {

            if j == -1 {
                parts = "1" + parts
            } else if parts[j] == '1' {
				parts = parts[:j] + "0" + parts[j+1:]
			} else if parts[j] == '0' {
				parts = parts[:j] + "1" + parts[j+1:]
				break
			}
		}

		if strings.Index(S, parts) == -1 {
			return false
		}
	}

	return true
}