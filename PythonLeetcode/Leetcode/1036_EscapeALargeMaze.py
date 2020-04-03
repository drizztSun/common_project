# 1036. Escape a Large Maze

# In a 1 million by 1 million grid, the coordinates of each grid square are (x, y) with 0 <= x, y < 10^6.

# We start at the source square and want to reach the target square.
# Each move, we can walk to a 4-directionally adjacent square in the grid that isn't in the given list of blocked squares.

# Return true if and only if it is possible to reach the target square through a sequence of moves.


# Example 1:

# Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
# Output: false
# Explanation:
# The target square is inaccessible starting from the source square, because we can't walk outside the grid.


# Example 2:

# Input: blocked = [], source = [0,0], target = [999999,999999]
# Output: true
# Explanation:
# Because there are no blocked cells, it's possible to reach the target square.

from collections import deque


class IsEscapePossible:
    def doit1(self, blocked, source, target):

        N = 10 ** 6
        blocked = set(tuple(c) for c in blocked)

        def bfs(p):
            q = deque()
            q.append(p)
            seen = set([tuple(p)])

            while q:
                x, y = q.popleft()
                if len(seen) > 19900:
                    return 1  # outside
                for c in ((x - 1, y), (x, y - 1), (x, y + 1), (x + 1, y)):
                    if c not in blocked and c not in seen and 0 <= c[0] < N and 0 <= c[1] < N:
                        q.append(c)
                        seen.add(c)

            return 0  # inside

        return bfs(source) ^ bfs(target) != 1

    def doit(self, blocked, source, target):
        """
        :type blocked: List[List[int]]
        :type source: List[int]
        :type target: List[int]
        :rtype: bool
        """

        # Based on Lee215's inspiration, but with some modifications. Ideas are below:
        # we can track the visited blocked, if all blocked are visited and BFS queue is not empty, then it means source is not trapped
        # if we have more alive nodes in our BFS queue than the count of non-visited blocks, then source is definitely not trapped.
        # using BFS depth as the termination condition is very time-consuming as BFS queue increases very quickly
        # changing:
        # len(queue) > len(blocked) - len(seen_block)
        # to:
        # len(queue) > (len(blocked) - len(seen_block))*2
        # will only cost one more BFS step instead of double it

        def bfs(blocked, source, target):
            queue = deque([source])
            visited = set([source])
            seen_block = set()     # the visited blocks
            while queue:
                for _ in range(len(queue)):
                    i, j = queue.popleft()
                    if (i, j) == target:
                        return True
                    for v in ((0, 1), (0, -1), (1, 0), (-1, 0)):
                        p, q = i+v[0], j+v[1]
                        if (p, q) in blocked:
                            seen_block.add((p, q))
                            continue
                        if p >= 0 and q >= 0 and (p, q) not in visited:
                            queue.append((p, q))
                            visited.add((p, q))
                if len(queue) > len(blocked) - len(seen_block):   # much faster than BFS_depth > len(blocked)*2
                    return True
            return False

        blocked = map(tuple, blocked)  # list is not hashable
        blocked = set(blocked)  # don't forget !
        source = tuple(source)
        target = tuple(target)
        if not blocked:
            return True

        if target in blocked or source in blocked:
            return False

        return bfs(blocked, source, target) and bfs(blocked, target, source)


if __name__ == "__main__":

    res = IsEscapePossible().doit(blocked=[[0, 1], [1, 0]], source=[0, 0], target=[0, 2])

    res = IsEscapePossible().doit(blocked=[], source=[0, 0], target=[999999, 999999])

    res = IsEscapePossible().doit([[0, 3], [1, 0], [1, 1], [1, 2], [1, 3]], [0, 0], [0, 2])

    res = IsEscapePossible().doit(
        [
            [0, 199],
            [1, 198],
            [2, 197],
            [3, 196],
            [4, 195],
            [5, 194],
            [6, 193],
            [7, 192],
            [8, 191],
            [9, 190],
            [10, 189],
            [11, 188],
            [12, 187],
            [13, 186],
            [14, 185],
            [15, 184],
            [16, 183],
            [17, 182],
            [18, 181],
            [19, 180],
            [20, 179],
            [21, 178],
            [22, 177],
            [23, 176],
            [24, 175],
            [25, 174],
            [26, 173],
            [27, 172],
            [28, 171],
            [29, 170],
            [30, 169],
            [31, 168],
            [32, 167],
            [33, 166],
            [34, 165],
            [35, 164],
            [36, 163],
            [37, 162],
            [38, 161],
            [39, 160],
            [40, 159],
            [41, 158],
            [42, 157],
            [43, 156],
            [44, 155],
            [45, 154],
            [46, 153],
            [47, 152],
            [48, 151],
            [49, 150],
            [50, 149],
            [51, 148],
            [52, 147],
            [53, 146],
            [54, 145],
            [55, 144],
            [56, 143],
            [57, 142],
            [58, 141],
            [59, 140],
            [60, 139],
            [61, 138],
            [62, 137],
            [63, 136],
            [64, 135],
            [65, 134],
            [66, 133],
            [67, 132],
            [68, 131],
            [69, 130],
            [70, 129],
            [71, 128],
            [72, 127],
            [73, 126],
            [74, 125],
            [75, 124],
            [76, 123],
            [77, 122],
            [78, 121],
            [79, 120],
            [80, 119],
            [81, 118],
            [82, 117],
            [83, 116],
            [84, 115],
            [85, 114],
            [86, 113],
            [87, 112],
            [88, 111],
            [89, 110],
            [90, 109],
            [91, 108],
            [92, 107],
            [93, 106],
            [94, 105],
            [95, 104],
            [96, 103],
            [97, 102],
            [98, 101],
            [99, 100],
            [100, 99],
            [101, 98],
            [102, 97],
            [103, 96],
            [104, 95],
            [105, 94],
            [106, 93],
            [107, 92],
            [108, 91],
            [109, 90],
            [110, 89],
            [111, 88],
            [112, 87],
            [113, 86],
            [114, 85],
            [115, 84],
            [116, 83],
            [117, 82],
            [118, 81],
            [119, 80],
            [120, 79],
            [121, 78],
            [122, 77],
            [123, 76],
            [124, 75],
            [125, 74],
            [126, 73],
            [127, 72],
            [128, 71],
            [129, 70],
            [130, 69],
            [131, 68],
            [132, 67],
            [133, 66],
            [134, 65],
            [135, 64],
            [136, 63],
            [137, 62],
            [138, 61],
            [139, 60],
            [140, 59],
            [141, 58],
            [142, 57],
            [143, 56],
            [144, 55],
            [145, 54],
            [146, 53],
            [147, 52],
            [148, 51],
            [149, 50],
            [150, 49],
            [151, 48],
            [152, 47],
            [153, 46],
            [154, 45],
            [155, 44],
            [156, 43],
            [157, 42],
            [158, 41],
            [159, 40],
            [160, 39],
            [161, 38],
            [162, 37],
            [163, 36],
            [164, 35],
            [165, 34],
            [166, 33],
            [167, 32],
            [168, 31],
            [169, 30],
            [170, 29],
            [171, 28],
            [172, 27],
            [173, 26],
            [174, 25],
            [175, 24],
            [176, 23],
            [177, 22],
            [178, 21],
            [179, 20],
            [180, 19],
            [181, 18],
            [182, 17],
            [183, 16],
            [184, 15],
            [185, 14],
            [186, 13],
            [187, 12],
            [188, 11],
            [189, 10],
            [190, 9],
            [191, 8],
            [192, 7],
            [193, 6],
            [194, 5],
            [195, 4],
            [196, 3],
            [197, 2],
            [198, 1],
            [199, 0],
        ],
        [0, 0],
        [200, 200],
    )

    pass
