package leetcodeH

/*
	Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

	The update(i, val) function modifies nums by updating the element at index i to val.

	Example:

	Given nums = [1, 3, 5]

	sumRange(0, 2) -> 9
	update(1, 2)
	sumRange(0, 2) -> 8
*/

type NumArray struct {
    nums, e []int
}


func Constructor(nums []int) NumArray {
    
    o := NumArray{}
    o.nums = make([]int, len(nums))
    for i := range o.nums {
        o.nums[i] = nums[i]
    }
    
    o.e = make([]int, len(nums) + 1)
    for i, n := range nums {
        i++
        for i < len(o.e) {
            o.e[i] += n
            i += (-i) & i
        }
    } 
    return o
}


func (this *NumArray) Update(i int, val int)  {
    diff := val - this.nums[i]
    this.nums[i] = val
    i++
    
    for i < len(this.e) {
        this.e[i] += diff
        i += (-i) & i
    } 
}


func (this *NumArray) SumRange(i int, j int) int {
    res := 0
    j++;
    
    for j > 0 {
        res += this.e[j]
        j -= (-j) & j
    }

    for i > 0 {
        res -= this.e[i]
        i -= (-i) & i
    }
    
    return res
}


func testRangeSumQueryMutable() {

	o = Constructor([]int{1, 3, 5})
	
	res = o.sumRange(0, 2)
	
	o.update(1, 2)
	
	res = o.sumRange(0, 2)
	
}