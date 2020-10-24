"""
1024. Video Stitching

# You are given a series of video clips from a sporting event that lasted T seconds.
# These video clips can be overlapping with each other and have varied lengths.

# Each video clip clips[i] is an interval: it starts at time clips[i][0] and ends at time clips[i][1].
# We can cut these clips into segments freely: for example, a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].

# Return the minimum number of clips needed so that we can cut the clips into segments that cover the entire sporting event ([0, T]).
# If the task is impossible, return -1.


# Example 1:

# Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], T = 10
# Output: 3
# Explanation:
# We take the clips [0,2], [8,10], [1,9]; a total of 3 clips.
# Then, we can reconstruct the sporting event as follows:
# We cut [1,9] into segments [1,2] + [2,8] + [8,9].
# Now we have segments [0,2] + [2,8] + [8,10] which cover the sporting event [0, 10].

# Example 2:

# Input: clips = [[0,1],[1,2]], T = 5
# Output: -1
# Explanation:
# We can't cover [0,5] with only [0,1] and [0,2].

# Example 3:

# Input: clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], T = 9
# Output: 3
# Explanation:
# We can take clips [0,4], [4,7], and [6,9].

# Example 4:

# Input: clips = [[0,4],[2,8]], T = 5
# Output: 2
# Explanation:
# Notice you can have extra video after the event ends.
"""


class VideoStitching:

    """
    Solution 2: Sort + DP
    Sort clips first.
    Then for each clip, update dp[clip[0]] ~ dp[clip[1]].

    Time O(NlogN + NT), Space O(T)

    """
    def doit_dp(self, clips, T):
        """
        :param clips:
        :param T:
        :return:
        """
        clips.sort(key=lambda x: x[0])
        dp = [float('inf') for _ in range(T+1)]
        dp[0] = 0

        for c in clips:
            for i in range(c[0], min(T+1, c[1]+1)):
                dp[i] = min(dp[i], dp[c[0]] + 1)

        return -1 if dp[-1] == float('inf') else dp[-1]

    def doit_sort(self, clips, T):
        #
        end, end2, res = -1, 0, 0
        for i, j in sorted(clips):
            if end2 >= T or i > end2:
                break
            elif end < i <= end2:
                res, end = res + 1, end2
            end2 = max(end2, j)
        return res if end2 >= T else -1

    def doit(self, clips, T):

        # Greedy
        # 类似的题目都是左端点排序，右端点比大小
        cur_end, aim_end, ans = -1, 0, 0
        clips.sort(key=lambda x: x[0])
        for s, e in clips:
            if aim_end >= T or s > aim_end:
                break
            elif cur_end < s <= aim_end:
                ans += 1
                cur_end = aim_end
            aim_end = max(aim_end, e)

        return ans if aim_end >= T else -1

    def doit(self, clips, T):

        clips.sort(key=lambda x: (x[0], -x[1]))

        ans = []
        for c in clips:

            if not ans:
                if c[0] != 0:
                    return -1
                ans.append(c)

            elif c[0] > ans[-1][1]:
                return -1
            elif c[1] <= ans[-1][1]:
                continue
            elif c[0] <= ans[-1][0] and c[1] > ans[-1][1]:
                t = ans.pop()
                ans.append((t[0], c[1]))
            else:
                ans.append((ans[-1][1], c[1]))

            if ans and ans[-1][1] >= T:
                return len(ans)

        return -1

    '''
    First, sort the clips based on the starting time.
    Apply DP to solve this problem
    DP[limit] = Cnt means we can use minimal Cnt clips to cover 0 to limit, inclusive.
    Initially, DP[0] = 0
    When a clip C comes, iterate limits between C[0] and min(T, C[1]), inclusive.
    We can merge interval in this region
    for Limit in range(c[0], newLimit+1):
    DP[newLimit] = min(DP[newLimit], DP[Limit] + 1)
    When last clip is checked, iterate DP list again to find the smallest C that can cover T.
    Time: O(T*n+nlogn), n is the length of clips
    Space: O(T)
    '''

    def doit(self, clips, T):
        DP = [0] + [float('inf')] * T
        clips.sort()
        for c in clips:
            if c[0] > T:
                break
            newLimit = min(T, c[1])
            for Limit in range(c[0], newLimit+1):
                DP[newLimit] = min(DP[newLimit], DP[Limit] + 1)

        if DP[-1] == float('inf'):
            return -1
        return DP[-1]


if __name__ == '__main__':

    res = VideoStitching().doit(clips=[[0, 2], [4, 6], [8, 10], [1, 9], [1, 5], [5, 9]], T=10)

    res = VideoStitching().doit(clips=[[0, 1], [1, 2]], T=5)

    res = VideoStitching().doit(clips=[[0, 1], [6, 8], [0, 2], [5, 6], [0, 4], [0, 3], [6, 7], [1, 3], [4, 7], [1, 4], [2, 5], [2, 6], [3, 4], [4, 5], [5, 7], [6, 9]], T=9)

    res = VideoStitching().doit(clips=[[0, 4], [2, 8]], T=5)

    res = VideoStitching().doit([[5, 7], [1, 8], [0, 0], [2, 3], [4, 5], [0, 6], [5, 10], [7, 10]], 5)