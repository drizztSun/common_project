package leetcodeH

/*
514. Freedom Trail

In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring", and use the dial to spell a specific keyword in order to open the door.

Given a string ring, which represents the code engraved on the outer ring and another string key, which represents the keyword needs to be spelled. You need to find the minimum number of steps in order to spell all the characters in the keyword.

Initially, the first character of the ring is aligned at 12:00 direction. You need to spell all the characters in the string key one by one by rotating the ring clockwise or anticlockwise to make each character of the string key aligned at 12:00 direction and then by pressing the center button.

At the stage of rotating the ring to spell the key character key[i]:

You can rotate the ring clockwise or anticlockwise one place, which counts as 1 step. The final purpose of the rotation is to align one of the string ring's characters at the 12:00 direction, where this character must equal to the character key[i].
If the character key[i] has been aligned at the 12:00 direction, you need to press the center button to spell, which also counts as 1 step. After the pressing, you could begin to spell the next character in the key (next stage), otherwise, you've finished all the spelling.
Example:

Input: ring = "godding", key = "gd"
Output: 4
Explanation:
For the first key character 'g', since it is already in place, we just need 1 step to spell this character.
For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
Also, we need 1 more step for spelling.
So the final output is 4.
Note:

Length of both ring and key will be in range 1 to 100.
There are only lowercase letters in both strings and might be some duplcate characters in both strings.
It's guaranteed that string key could always be spelled by rotating the string ring.
*/

func findRotateSteps_dp(ring string, key string) int {

	min := func(a, b int) int {
		if a < b {
			return a
		}
		return b
	}

	abs := func(a int) int {
		if a > 0 {
			return a
		}
		return -a
	}

	ringPos := make(map[byte][]int, 0)
	for i := range ring {
		if _, ok := ringPos[ring[i]]; !ok {
			ringPos[ring[i]] = make([]int, 0)
		}

		ringPos[ring[i]] = append(ringPos[ring[i]], i)
	}

	N := len(ring)
	maxv := len(ring)*len(key) + len(key)
	dp := make([]int, len(ring))
	for i := range dp {
		dp[i] = maxv
		if key[0] == ring[i] {
			dp[i] = min(i, N-i) + 1
		}
	}

	for i := 1; i < len(key); i++ {

		if key[i] == key[i-1] {
			for _, c := range ringPos[key[i]] {
				dp[c]++
			}
			continue
		}

		for _, c := range ringPos[key[i]] {
			res := maxv
			for _, l := range ringPos[key[i-1]] {
				s := min(abs(l-c), N-abs(l-c)) + dp[l]
				if s < res {
					res = s
				}
			}
			dp[c] = res + 1
		}
	}

	res := maxv
	for _, c := range ringPos[key[len(key)-1]] {
		if res > dp[c] {
			res = dp[c]
		}
	}
	return res
}

func search_next(ringPos map[byte][]int, key string, pos, index int, memo [][]int) int {

	min := func(a, b int) int {
		if a < b {
			return a
		}
		return b
	}

	abs := func(a int) int {
		if a > 0 {
			return a
		}
		return -a
	}

	if memo[pos][index] != 0 {
		return memo[pos][index]
	}

	if index == len(key) {
		return 0
	}

	res := len(memo) * len(key)
	for _, c := range ringPos[key[index]] {

		cur := 1 + min(abs(c-pos), len(memo)-abs(c-pos))
		next := search_next(ringPos, key, c, index+1, memo)

		if res > next+cur {
			res = next + cur
		}
	}

	memo[pos][index] = res
	return res
}

func findRotateSteps_dp_dfs_recur(ring string, key string) int {

	ringPos := make(map[byte][]int, 0)

	for i := range ring {
		if _, ok := ringPos[ring[i]]; !ok {
			ringPos[ring[i]] = make([]int, 0)
		}

		ringPos[ring[i]] = append(ringPos[ring[i]], i)
	}

	memo := make([][]int, len(ring))
	for i := range memo {
		memo[i] = make([]int, len(key))
	}

	return search_next(ringPos, key, 0, 0, memo)
}
