package leetcodem

/*

1024. Video Stitching

You are given a series of video clips from a sporting event that lasted T seconds.  These video clips can be overlapping with each other and have varied lengths.

Each video clip clips[i] is an interval: it starts at time clips[i][0] and ends at time clips[i][1].  We can cut these clips into segments freely: for example, a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].

Return the minimum number of clips needed so that we can cut the clips into segments that cover the entire sporting event ([0, T]).  If the task is impossible, return -1.



Example 1:

Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], T = 10
Output: 3
Explanation:
We take the clips [0,2], [8,10], [1,9]; a total of 3 clips.
Then, we can reconstruct the sporting event as follows:
We cut [1,9] into segments [1,2] + [2,8] + [8,9].
Now we have segments [0,2] + [2,8] + [8,10] which cover the sporting event [0, 10].

Example 2:

Input: clips = [[0,1],[1,2]], T = 5
Output: -1
Explanation:
We can't cover [0,5] with only [0,1] and [0,2].

Example 3:

Input: clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], T = 9
Output: 3
Explanation:
We can take clips [0,4], [4,7], and [6,9].

Example 4:

Input: clips = [[0,4],[2,8]], T = 5
Output: 2
Explanation:
Notice you can have extra video after the event ends.

*/

import "sort"

func videoStitching(clips [][]int, T int) int {

	sort.Slice(clips, func(i, j int) bool {
		return clips[i][0] < clips[j][0] || (clips[i][0] == clips[j][0] && clips[i][1] >= clips[j][1])
	})

	st := make([][]int, 0)

	for i := range clips {

		if len(st) == 0 {
			st = append(st, clips[i])
			if clips[i][0] != 0 {
				return -1
			}
		} else {
			l := len(st)

			if st[l-1][1] < clips[i][0] {
				return -1
			}

			if st[l-1][0] >= clips[i][0] && st[l-1][1] < clips[i][1] {
				st = st[:l-1]
				st = append(st, []int{st[l-2][1], clips[i][1]})
			} else if st[l-1][1] < clips[i][1] {
				st = append(st, []int{st[l-1][1], clips[i][1]})
			}
		}

		if st[len(st)-1][1] >= T {
			return len(st)
		}
	}

	return -1
}

func Test_1024_VideoStiching() {

	videoStitching([][]int{[]int{0, 2}, []int{4, 6}, []int{8, 10}, []int{1, 9}, []int{1, 5}, []int{5, 9}}, 10)
}
