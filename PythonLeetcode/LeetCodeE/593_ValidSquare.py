# 593. Valid Square

# Given the coordinates of four points in 2D space, return whether the four points could construct a square.

# The coordinate (x,y) of a point is represented by an integer array with two integers.

# Example:
# Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
# Output: True
# Note:

# All the input integers are in the range [-10000, 10000].
# A valid square has four equal sides with positive length and four equal angles (90-degree angles).
# Input points have no order.


class ValidSquare:

    def doit(self, p1, p2, p3, p4):
        """
        :type p1: List[int]
        :type p2: List[int]
        :type p3: List[int]
        :type p4: List[int]
        :rtype: bool
        """
        if p1==p2==p3==p4:
            return False

        dist = lambda x, y: (x[0]-y[0])**2 + (x[1]-y[1])**2

        ls=[dist(p1,p2),dist(p1,p3),dist(p1,p4),dist(p2,p3),dist(p2,p4),dist(p3,p4)]
        ls.sort()

        return ls[0]==ls[1]==ls[2]==ls[3] and ls[4]==ls[5]

    def doit1(self, p1, p2, p3, p4):
        """
        :type p1: List[int]
        :type p2: List[int]
        :type p3: List[int]
        :type p4: List[int]
        :rtype: bool
        """

        num = sorted([p1, p2, p3, p4], key = lambda x: (x[0], x[1]))
        p1, p2, p3, p4 = num[0], num[1], num[2], num[3]
        
        diff = lambda x, y: (x[0] - y[0], x[1] - y[1])
        
        length = lambda x : x[0] ** 2 + x[1] ** 2

        ortho = lambda x, y: x[0] * y[0] + x[1] * y[1] == 0

        l12 = diff(p1, p2)
        l13 = diff(p1, p3)
        l24 = diff(p2, p4)
        l34 = diff(p3, p4)

        return length(l12) == length(l13) and length(l24) == length(l34) and length(l13) == length(l24) and ortho(l12, l13)
                    




if __name__ == "__main__":

    res = ValidSquare().doit(p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1])

    res = True