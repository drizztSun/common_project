package leetcodeH

/*
321. Create Maximum Number

Given two arrays of length m and n with digits 0-9 representing two numbers. Create the maximum number of length k <= m + n from digits of the two. The relative order of the digits from the same array must be preserved. Return an array of the k digits.

Note: You should try to optimize your time and space complexity.

Example 1:

Input:
nums1 = [3, 4, 6, 5]
nums2 = [9, 1, 2, 5, 8, 3]
k = 5
Output:
[9, 8, 6, 5, 3]
Example 2:

Input:
nums1 = [6, 7]
nums2 = [6, 0, 4]
k = 5
Output:
[6, 7, 6, 0, 4]
Example 3:

Input:
nums1 = [3, 9]
nums2 = [8, 9]
k = 3
Output:
[9, 8, 9]

*/

func MaxNumber(nums1, nums2 []int, k int)[]int{
	if k == 0{
	  return []int{}
	}
	var cm, nm, l, i, m int
	var res []int
	var q [][]int //q[i] = []int{max_val, itr of nums1, itr of nums2 }
	v := make([][][]bool, len(nums1)+1)
	a2 := make([][]int, len(nums2)+1)
	a1 := make([][]int, len(nums1)+1)
	v[len(nums1)] = make([][]bool, len(nums2)+1)
	a2[len(nums2)] = []int{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
	a1[len(nums1)] = []int{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
	for i = len(nums1)-1 ;i >= 0 ; i--{
	  v[i] = make([][]bool, len(nums2)+1)
	  a1[i] = make([]int, 10)
	  copy(a1[i], a1[i+1])
	  a1[i][nums1[i]] = i
	}
  
	for i = len(nums2)-1 ;i >= 0; i--{
	  a2[i] = make([]int, 10)
	  copy(a2[i], a2[i+1])
	  a2[i][nums2[i]] = i
	}
  
	q = append(q, []int{0, 0, 0})
	v[0][0] = make([]bool, k+1)
	f := func(a bool, x, y, e int){
	  if a{
		// finds max element in the range [x,e) in constant (O(10)) time
		for m = 9; m >= 0; m--{
		  if a1[x][m] != a1[e][m]{
			break
		  }
		}
		x = a1[x][m]+1
	  }else{
		for m = 9; m >= 0; m--{
		  if a2[y][m] != a2[e][m]{
			break
		  }
		}
		y = a2[y][m]+1
	  }
  
	  if m >= nm{
		nm = m
		if len(v[x][y]) == 0{
		  v[x][y] = make([]bool, k+1)
		}
		q = append(q, []int{m, x, y})
	  }
	}
	for ;k > 0; k-- {
	  res = append(res, cm)
	  l = len(q)
	  for i = 0; i < l; i++{
		if !v[q[i][1]][q[i][2]][k] && q[i][0] == cm{
		  if q[i][1] == len(nums1){
			f(false, q[i][1], q[i][2], len(nums2)-k+1)
		  }else if q[i][2] == len(nums2){
			f(true, q[i][1], q[i][2], len(nums1)-k+1)
		  }else{
			if len(nums2) > q[i][2] + k - 2 {//len(nums2)-q[i][2] >= k-1
			  f(true, q[i][1], q[i][2], len(nums1))
			}else{
			  f(true, q[i][1], q[i][2], len(nums1)-k+len(nums2)-q[i][2]+1)
			}
  
			if len(nums1) > q[i][1] + k - 2 {//len(nums1)-q[i][1] >= k-1
			  f(false, q[i][1], q[i][2], len(nums2))
			}else{
			  f(false, q[i][1], q[i][2], len(nums1)-k+len(nums2)-q[i][1]+1)
			}
		  }
		  v[q[i][1]][q[i][2]][k] = true
		}
	  }
	  q = q[l:]
	  cm = nm
	  nm = -1
	}
	return append(res, cm)[1:]
  }


func maxNumber_bfs(nums1 []int, nums2 []int, k int) []int {

	search := func(nums []int, s int) []int {

		if s == 0 {
			return []int{}
		}

		removed := len(nums) - s
		buf := []int{}

		for i := range nums {

			for len(buf) > 0 && removed > 0 && nums[i] > buf[len(buf)-1] {
				buf = buf[:len(buf)-1]
				removed--
			}

			buf = append(buf, nums[i])
		}

		return buf[:s]
	}

	res := []int{}

	for i := 0; i <= k; i++ {

		if i > len(nums1) || k-i > len(nums2) {
			continue
		}

		left := search(nums1, i)
		right := search(nums2, k-i)

		ans := make([]int, 0)
		l, r := 0, 0

		for l <= len(left) || r <= len(right) {

			if l >= len(left) {
				ans = append(ans, right[r:]...)
				break
			} else if r >= len(right) {
				ans = append(ans, left[l:]...)
				break
			} else {
				if left[l] > right[r] {
					ans = append(ans, left[l])
					l++
				} else if left[l] < right[r] {
					ans = append(ans, right[r])
					r++
				} else {
					l1, r1 := l, r
					for l1 < len(left) && r1 < len(right) && left[l1] == right[r1] {
						l1++
						r1++
					}

					if l1 != len(left) && r1 != len(right) {
						if left[l1] > right[r1] {
							ans = append(ans, left[l:l1]...)
							l = l1
						} else {
							ans = append(ans, right[r:r1]...)
							r = r1
						}
						continue
					} else if l1 == len(left) {
						for r1 < len(right) && right[r1] >= left[l] {
							r1++
						}

						ans = append(ans, right[r:r1]...)
						ans = append(ans, left[l:]...)
					} else if r1 == len(right) {
						for l1 < len(left) && left[l1] >= right[r] {
							l1++
						}

						ans = append(ans, left[l:l1]...)
						ans = append(ans, right[r:]...)
					}
					l, r = l1, r1
				}
			}
		}

		if len(res) < len(ans) {
			res = ans
			continue
		}

		for l := 0; l < len(ans); l++ {
			if ans[l] > res[l] {
				res = ans
				break
			}
			if ans[l] < res[l] {
				break
			}
		}
	}

	return res
}

func Test_321_create_maximum_number() {

	maxNumber_bfs([]int{3, 4, 8, 9, 3, 0}, []int{6, 1, 9, 1, 1, 2}, 6)

	maxNumber_bfs([]int{5, 6, 8}, []int{6, 4, 0}, 3)

	maxNumber_bfs([]int{6, 7}, []int{6, 0, 4}, 5)

	maxNumber_bfs([]int{3, 4, 6, 5}, []int{9, 1, 2, 5, 8, 3}, 5)
}
