package leetcodeE

import (
	"fmt"
)

func multiplyStrings(num1 string, num2 string) string {
	
	if len(num1) == 0 || len(num2) == 0 || num1 == "0" || num2 == "0" {
		return string("0")
	} 


	res := make([]uint16, len(num1) + len(num2))
	base := uint16('0')

	for i := len(num1) - 1; i >= 0; i-- {

		for j := len(num2) - 1; j >= 0; j-- {

			// res[length - 1 - (i + j) - 1] += (uint8(num1[i]) - base) * (uint8(num2[j]) - base)
			res[i+j + 1] += (uint16(num1[i]) - base) * (uint16(num2[j]) - base)
		}
	}

	for i := len(num1) + len(num2) - 1; i >0 ; i-- {
		r := res[i] / 10
		c := res[i] % 10

		res[i] = c + base
		res[i-1] += r
	}

	if res[0] == 0 {
		res = res[1:]
	} else {
		res[0] += base
	}

	datas := make([]byte, len(res))
	for i := 0; i < len(datas); i++ {
		datas[i] = byte(res[i])
	}

	return string(datas)
}

func Test_43_multiply_strings() {

	fmt.Println(multiplyStrings("123", "72")) // 8856

	fmt.Println(multiplyStrings("2", "3")) // 6

	fmt.Println(multiplyStrings("999", "999")) // 99801

	fmt.Println(multiplyStrings("999", "0"))

}
