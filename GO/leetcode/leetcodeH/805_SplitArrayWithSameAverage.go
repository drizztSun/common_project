package leetcodeH

// Basic Ideas: BFS pruning
// Observation:
//  avg(A) == avg(B) == avg(C)
//  We only need to check combination which has no more than len(A)/2 items.
//          Apparently max(len(B), len(C)) <= len(A)/2
//  Avoid duplicated caculation by using a hashmap
//  If we sort A, once avg(B) >= avg(A), we can't add any more item which is bigger than avg(A)
//
// Complexity:
import (
	"fmt"
	"math"
)

type Entity struct {
	count, sum int
}

/*
func splitArraySameAverage(A []int) bool {

	if len(A) < 2 {
		return false
	}

	sum_a := 0
	for _, v := range A { sum_a += v }
	visited := map[Entity]bool {}
	queue := [][]int

	sort.Ints(A)
	for _, v := range A {

		if v * len(A) == sum_a {
			return true
		}

		en := Entity{1, v}
		if visited[en] == false {
			queue = append(queue, []int{1, v})
			visited[en] = true
		}

		list := [][]int
		for _, item := range queue {

			v1, v2 := (item[1] + v) * len(A), (item[0] + 1) * sum_a
			if v1 == v2 {
				return true
			} else {
				if v1 < v2 {

					entity = Entity{item[0] + 1, item[1] + v}
					if visited[entity] == false{
						list = append(list, []int{item[0]+1, item[1] + v})
						visited[entity] = true
					}
				}
			}
		}

		for _, v := range list {
			queue = append(queue, v)
		}

	}

	return false
}
*/

type key struct {
	target, cnt int
}

func _search(notFound map[key]int, val []int, target, amount, s int) bool {

	k := key{target, amount}
	if val, ok := notFound[k]; ok && val <= s {
		return false
	}

	if amount == 0 {
		return target == 0
	}

	if amount+s > len(val) {
		return false
	}

	res := _search(notFound, val, target-val[s], amount-1, s+1) || _search(notFound, val, target, amount, s+1)

	if !res {
		if v, ok := notFound[k]; ok {
			notFound[k] = int(math.Min(float64(s), float64(v)))
		} else {
			notFound[k] = int(math.Min(float64(s), float64(len(val))))
		}
	}

	return res
}

func splitArraySameAverage(val []int) bool {

	notFound := make(map[key]int)

	sumA, length := 0, len(val)
	for i := range val {
		sumA += val[i]
	}

	for i := 1; i < int(length/2)+1; i++ {
		if sumA*i%length == 0 && _search(notFound, val, sumA*i/length, i, 0) {
			return true
		}
	}

	return false
}

func Test_805SplitArrayWithSameAverage() {

	res := false

	res = splitArraySameAverage([]int{1, 2, 3, 4, 5, 6, 7, 8})

	fmt.Println("res : ", res)
}
