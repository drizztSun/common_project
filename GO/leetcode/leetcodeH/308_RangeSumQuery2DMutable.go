package leetcodeH

/*
308 Range Sum Query 2D Mutable


            [3, 0, 1, 4, 2],
            [5, 6, 3, 2, 1],
            [1, 2, 0, 1, 5],
            [4, 1, 0, 1, 7],
            [1, 0, 3, 0, 5]


*/

import (
	"fmt"
)

type NumArray2D struct {
	nums, e [][]int
}

func constructor_NumArray2D(num [][]int) NumArray2D {

	o := NumArray2D{}

	o.nums = make([][]int, len(num))
	for i := range o.nums {
		o.nums[i] = make([]int, len(num[0]))
		for j := range o.nums[i] {
			o.nums[i][j] = num[i][j]
		}
	}

	o.e = make([][]int, len(num))
	for i := range o.e {
		o.e[i] = make([]int, len(num[0])+1)

		for j := range o.e[i] {
			o.e[i][j] = 0
		}

		for j := range o.nums[i] {
			k := j + 1
			for k < len(o.e[i]) {
				o.e[i][k] += o.nums[i][j]
				k += (-k) & k
			}
		}
	}

	return o
}

func (this *NumArray2D) update(i, j, val int) {
	diff := val - this.nums[i][j]
	this.nums[i][j] = val

	for k := j + 1; k < len(this.e[i]); {
		this.e[i][k] += diff
		k += (-k) & k
	}
}

func (this *NumArray2D) sumRange(i, j, k, z int) int {

	res := 0

	for ; i <= k; i++ {
		h, l := z+1, j

		for h > 0 {
			res += this.e[i][h]
			h -= (-h) & h
		}

		for l > 0 {
			res -= this.e[i][l]
			l -= (-l) & l
		}
	}

	return res
}

func main() {

	o := constructor_NumArray2D([][]int{
		{3, 0, 1, 4, 2},
		{5, 6, 3, 2, 1},
		{1, 2, 0, 1, 5},
		{4, 1, 0, 1, 7},
		{1, 0, 3, 0, 5},
	})

	res := o.sumRange(2, 1, 4, 3) // 8

	fmt.Println(res)

	o.update(3, 2, 2)

	res = o.sumRange(2, 1, 4, 3) // 10

	res = 0
}
