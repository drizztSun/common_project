# 990. Satisfiability of Equality Equations

# Given an array equations of strings that represent relationships between variables,
# each string equations[i] has length 4 and takes one of two different forms: "a==b" or "a!=b".
# Here, a and b are lowercase letters (not necessarily different) that represent one-letter variable names.

# Return true if and only if it is possible to assign integers to variable names so as to satisfy all the given equations.


# Example 1:

# Input: ["a==b","b!=a"]
# Output: false
# Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.
# There is no way to assign the variables to satisfy both equations.

# Example 2:

# Input: ["b==a","a==b"]
# Output: true
# Explanation: We could assign a = 1 and b = 1 to satisfy both equations.

# Example 3:

# Input: ["a==b","b==c","a==c"]
# Output: true

# Example 4:

# Input: ["a==b","b!=c","c==a"]
# Output: false

# Example 5:

# Input: ["c==c","b==d","x!=z"]
# Output: true


# Note:

# 1 <= equations.length <= 500
# equations[i].length == 4
# equations[i][0] and equations[i][3] are lowercase letters
# equations[i][1] is either '=' or '!'
# equations[i][2] is '='

class EquationsPossible:

    """
    Approach 1: Connected Components
    Intuition

    All variables that are equal to each other form connected components.
    For example, if a=b, b=c, c=d then a, b, c, d are in the same connected component as they all must be equal to each other.

    Algorithm

    First, we use a depth first search to color each variable by connected component based on these equality equations.

    After coloring these components, we can parse statements of the form a != b.
    If two components have the same color, then they must be equal, so if we say they can't be equal then it is impossible to satisfy the equations.

    Otherwise, our coloring demonstrates a way to satisfy the equations, and thus the result is true.

    Complexity Analysis

    Time Complexity: O(N) where N is the length of equations.

    Space Complexity: O(1), assuming the size of the alphabet is O(1).
    """

    def doit(self, equations):

        graph = [[] for _ in range(26)]

        for eqn in equations:
            if eqn[1] == '=':
                x = ord(eqn[0]) - ord('a')
                y = ord(eqn[3]) - ord('a')
                graph[x].append(y)
                graph[y].append(x)

        color = [None] * 26
        t = 0
        for start in range(26):
            if color[start] is None:
                t += 1
                stack = [start]
                while stack:
                    node = stack.pop()
                    for nei in graph[node]:
                        if color[nei] is None:
                            color[nei] = t
                            stack.append(nei)

        for eqn in equations:
            if eqn[1] == '!':
                x = ord(eqn[0]) - ord('a')
                y = ord(eqn[3]) - ord('a')
                if x == y:
                    return False  # lee
                if color[x] is not None and color[x] == color[y]:
                    return False
        return True


if __name__ == '__main__':

    res = EquationsPossible().doit(["a==b", "b!=a"])

    res = EquationsPossible().doit(["b==a", "a==b"])

    res = EquationsPossible().doit(["a==b", "b==c", "a==c"])

    res = EquationsPossible().doit(["a==b", "b!=c", "c==a"])

    res = EquationsPossible().doit(["c==c", "b==d", "x!=z"])

    res = EquationsPossible().doit(["e==e", "d!=e", "c==d", "d!=e"])

    pass
