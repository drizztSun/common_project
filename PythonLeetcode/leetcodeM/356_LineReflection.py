"""
356. Line Reflection

Given n points on a 2D plane, find if there is such a line parallel to y-axis that reflect the given points symmetrically,
in other words, answer whether or not if there exists a line that after reflecting all points over the given line the set of the original points is the same that the reflected ones.

Note that there can be repeated points.

Follow up:
Could you do better than O(n2) ?



Example 1:


Input: points = [[1,1],[-1,1]]
Output: true
Explanation: We can choose the line x = 0.
Example 2:


Input: points = [[1,1],[-1,-1]]
Output: false
Explanation: We can't choose a line.


Constraints:

n == points.length
1 <= n <= 10^4
-10^8 <= points[i][j] <= 10^8



"""


class LineReflection:

    """
    Idea: The algorithm consists of two steps:

    We group the points by their y coordinates. We construct a dictionary dic, and for each group,
    dic maps the y coordinate of the group to the list of x coordinates of the points in the group.

    We initialize a variable line = None, denoting the x coordinate of the reflection line. We then enumerate the key,
    val pairs of dic, and for each key, val pair, we sort val (i.e., we let all points with y == key line up along the x axis).
    We enumerate pairs of points x_head, x_tail at the two ends of val, and gradually moving towards the middle.
    If line == None, then we assign line = (x_head + x_tail) / 2, because x_head and x_tail must be mirror image of each other with respect to line;
    Else, if line is already assigned some value, we need to check if line == (x_head + x_tail) /

    2. If not, we return False. If all such pairs have been check and we didn't return False, we return True.

    Time complexity: O(n log n),
    space complexity: O(n).
    """

    def doit_(self, points: list) -> bool:

        from collections import defaultdict

        graph = defaultdict(list)
        for x, y in points:
            graph[y].append(x)

        line = None
        for xs in graph.values():
            xs.sort()

            for i in range((len(xs) + 1) // 2):
                median = (xs[i] + xs[len(xs) - i - 1]) / 2

                if not line:
                    line = median

                if median != line:
                    return False

        return True


if __name__ == '__main__':

    LineReflection().doit_([[1,1],[-1,1]])

    LineReflection().doit_([[0,0],[1,0],[3,0]])

