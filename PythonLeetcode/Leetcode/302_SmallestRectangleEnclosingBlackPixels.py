


# 302 Smallest Rectangle Enclosing Black Pixels

# An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel.
# The black pixels are connected, i.e., there is only one black region.
# Pixels are connected horizontally and vertically. Given the location (x, y) of one of the black pixels,
# return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.

# For example, given the following image:

# [
#  "0010",
#  "0110",
#  "0100"
# ]
# and x = 0, y = 2,
 
# Return 6.


# <hard> <important>
class SmeallestRectEnclosingBlackPixels(object):


    # <dfs>  O(n**2)
    def doit(self, matrix, x, y):
        """
        : type  List[str]
        : type int 
        : type int
        : rtype int 
        """
        def dfs(matrix, a, b, path):

            nextPoint = [(a+1, b), (a-1, b), (a, b+1), (a, b-1)]
            for c in nextPoint:
                if c in path:
                    continue

                x, y = c
                if 0 <= x < len(matrix) and 0 <= y < len(matrix[x]) and matrix[x][y] == '1':

                    rect[0] = min(x, rect[0])
                    rect[1] = max(x, rect[1])
                    rect[2] = min(y, rect[2])
                    rect[3] = max(y, rect[3])
                    
                    path.add((x, y))
                    
                    dfs(matrix, x, y, path)


        rect = [len(matrix), 0, len(matrix[0]), 0]
        dfs(matrix, x, y, set())

        return (rect[1] - rect[0] + 1) * (rect[3] - rect[2] + 1)


    # <binarySearch> O(m*lg(m) + n*lg(n)) O(1)
    def doit(self, matrix, x, y):
        """
        : type  List[str]
        : type int 
        : type int
        : rtype int 
        """
        # axis is scanning direction, isBlack is '1' or '0'
        def search(M, low, high, min, max, axis, isBlack):
            
            while low < high:
                mid = (low + high) // 2
                found = False 
                
                for i in range(min, max):
                    if (axis and M[i][mid] == '1') or ( not axis and M[mid][i] == '1'):
                        found = True
                        break

                if found == isBlack:
                    high = mid
                else:
                    low = mid + 1
            
            return low

        m, n = len(matrix), len(matrix[0])

        left = search(matrix, 0, y, 0, m, True, True)
        right = search(matrix, y+1, n, 0, m, True, False)
        
        up = search(matrix, 0, x, 0, n, False, True)
        bottom = search(matrix, x+1, m, 0, n, False, False)

        return (right - left) * (bottom - up) 
        


if __name__ == "__main__":


    A = [
      "0010",
      "0110",
      "0100"
     ]

    res = SmeallestRectEnclosingBlackPixels().doit(A, 0, 2)


    pass
        