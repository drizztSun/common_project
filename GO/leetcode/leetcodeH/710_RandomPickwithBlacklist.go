package leetcodeH

/*

710. Random Pick with Blacklist

Given a blacklist B containing unique integers from [0, N), write a function to return a uniform random integer from [0, N) which is NOT in B.

Optimize it such that it minimizes the call to system’s Math.random().

Note:

1 <= N <= 1000000000
0 <= B.length < min(100000, N)
[0, N) does NOT include N. See interval notation.
Example 1:

Input:
["Solution","pick","pick","pick"]
[[1,[]],[],[],[]]
Output: [null,0,0,0]
Example 2:

Input:
["Solution","pick","pick","pick"]
[[2,[]],[],[],[]]
Output: [null,1,1,1]
Example 3:

Input:
["Solution","pick","pick","pick"]
[[3,[1]],[],[],[]]
Output: [null,0,0,2]
Example 4:

Input:
["Solution","pick","pick","pick"]
[[4,[2]],[],[],[]]
Output: [null,1,3,1]
Explanation of Input Syntax:

The input is two lists: the subroutines called and their arguments. Solution's constructor has two arguments, N and the blacklist B. pick has no arguments. Arguments are always wrapped with a list, even if there aren't any.

*/
import (
	"math/rand"
)

type RandomPickWithBlackList struct {
	N         int
	NB        int
	blacklist map[int]int
}

func Constructor(N int, blacklist []int) RandomPickWithBlackList {
	a := RandomPickWithBlackList{N, len(blacklist), make(map[int]int)}
	for _, b := range blacklist {
		a.blacklist[b] = -1
	}

	currentWhite, bn := N-len(blacklist), len(blacklist)

	for _, v := range blacklist {
		if v < N-bn {
			_, ok := a.blacklist[currentWhite]
			for ok {
				currentWhite++
				_, ok = a.blacklist[currentWhite]
			}
			a.blacklist[v] = currentWhite
			currentWhite++
		}
	}

	return a
}

func (this *RandomPickWithBlackList) Pick() int {
	k := rand.Intn(this.N - this.NB)
	if val, ok := this.blacklist[k]; ok {
		return val
	} else {
		return k
	}
}
