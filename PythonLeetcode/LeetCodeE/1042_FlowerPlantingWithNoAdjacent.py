# 1042. Flower Planting With No Adjacent

# You have N gardens, labelled 1 to N.  In each garden, you want to plant one of 4 types of flowers.

# paths[i] = [x, y] describes the existence of a bidirectional path from garden x to garden y.

# Also, there is no garden that has more than 3 paths coming into or leaving it.

# Your task is to choose a flower type for each garden such that, for any two gardens connected by a path, they have different types of flowers.

# Return any such a choice as an array answer, where answer[i] is the type of flower planted in the (i+1)-th garden.  The flower types are denoted 1, 2, 3, or 4.
# It is guaranteed an answer exists.


# Example 1:

# Input: N = 3, paths = [[1,2],[2,3],[3,1]]
# Output: [1,2,3]

# Example 2:

# Input: N = 4, paths = [[1,2],[3,4]]
# Output: [1,2,1,2]

# Example 3:

# Input: N = 4, paths = [[1,2],[2,3],[3,4],[4,1],[1,3],[2,4]]
# Output: [1,2,3,4]


class GardenNoAdj:

    def doit(self, N, paths):

        g = [[] for _ in range(N)]
        for f, t in paths:
            g[f-1].append(t-1)
            g[t-1].append(f-1)

        all_flowers = set([1, 2, 3, 4])
        ans = [0 for _ in range(N)]

        for i in range(N):

            tmp = set([ans[c] for c in g[i]])

            ans[i] = list(all_flowers - tmp)[0]

        return ans


if __name__ == '__main__':

    res = GardenNoAdj().doit(N=3, paths=[[1, 2], [2, 3], [3, 1]])

    res = GardenNoAdj().doit(N=4, paths=[[1, 2], [3, 4]])

    res = GardenNoAdj().doit(
        N=4, paths=[[1, 2], [2, 3], [3, 4], [4, 1], [1, 3], [2, 4]])

    pass
