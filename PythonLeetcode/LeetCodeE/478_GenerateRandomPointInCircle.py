# 478. Generate Random Point in a Circle

# Given the radius and x-y positions of the center of a circle, write a function randPoint which generates a uniform random point in the circle.

# Note:

# input and output values are in floating-point.
# radius and x-y position of the center of the circle is passed into the class constructor.
# a point on the circumference of the circle is considered to be in the circle.
# randPoint returns a size 2 array containing x-position and y-position of the random point, in that order.

# Example 1:

# Input: 
# ["Solution","randPoint","randPoint","randPoint"]
# [[1,0,0],[],[],[]]
# Output: [null,[-0.72939,-0.65505],[-0.78502,-0.28626],[-0.83119,-0.19803]]

# Example 2:

# Input: 
# ["Solution","randPoint","randPoint","randPoint"]
# [[10,5,-7.5],[],[],[]]

# Output: [null,[11.52438,-8.33273],[2.46992,-16.21705],[11.13430,-12.42337]]

# Explanation of Input Syntax:

# The input is two lists: the subroutines called and their arguments. Solution's constructor has three arguments, 
# the radius, x-position of the center, and y-position of the center of the circle. randPoint has no arguments.
# Arguments are always wrapped with a list, even if there aren't any.

import random

# Above is the solution that some currently most voted post used to solve this question.
# Posters are using Math.sqrt() to get the graph with correct random points.
# However, what's happening here? Why the points will go near to center if we don't use Math.sqrt()?
# Here is some expanation with graph to show what's behind this.

# First, in above solution, we need to know that we are using one random Length to multiply on a random normalized vector(x^2 + y^2 = 1) to get the random point.
# Sounds good right?
# However, if we directly multiply them, we will get a graph that points placed averagely according to Length/Radius.
# image -->  image

# In the smallest circle (i.e. radius = 0.1), it can get a same amount of points with the larger circle (i.e. radius = 0.9)!
# Therefore, we need to decrease the chance that the point can placed there according to how close it is to the center (how short is the that position's radius).

# Then, finally, Here is Math.sqrt()
# image
# *Red line is normal random, Green line is Math.sqrt(random)
# This is exactly what we want!

# After using this, we can get a correct graph!
# image -->  image

# Undeniably, using Math.sqrt() is a clever method.
# However, I think it is quite difficult to understand without explanation.
# I hope this can help if you don't understand why Math.sqrt().
class Solution(object):

    def __init__(self, radius, x_center, y_center):
        """
        :type radius: float
        :type x_center: float
        :type y_center: float
        """
        self.radius = radius
        self.x = x_center
        self.y = y_center

    def randPoint(self):
        """
        :rtype: List[float]
        """
        while True:
            x = random.uniform(-1, 1)
            y = random.uniform(-1, 1)
            if x**2 + y**2 <= 1:
                return self.x + x*self.radius, self.y + y*self.radius


class RandomPointInCircle(object):

    def __init__(self, radius, x_center, y_center):
        """
        :type radius: float
        :type x_center: float
        :type y_center: float
        """
        self.x_center = x_center
        self.y_center = y_center
        self.radius = radius

    def randPoint(self):
        """
        :rtype: List[float]
        """
        import random
        import math

        length = random.random() * self.radius
        delta = random.random() * 2 * math.pi

        return [length * math.cos(delta) + self.x_cernter, length * math.sin(delta) + self.y_center]
                         


# Your Solution object will be instantiated and called as such:
# obj = Solution(radius, x_center, y_center)
# param_1 = obj.randPoint()
