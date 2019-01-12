package leetcodeE
// Basic Ideas: BFS pruning
// Observation:
//  avg(A) == avg(B) == avg(C)
//  We only need to check combination which has no more than len(A)/2 items.
//          Apparently max(len(B), len(C)) <= len(A)/2 
//  Avoid duplicated caculation by using a hashmap
//  If we sort A, once avg(B) >= avg(A), we can't add any more item which is bigger than avg(A)
//  
// Complexity:
import "sort"

type Entity struct {
	count, sum int
}

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
