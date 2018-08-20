


# 406. Queue Reconstruction by Height

# Suppose you have a random list of people standing in a queue.
# Each person is described by a pair of integers (h, k),
# where h is the height of the person and k is the number of people in front of this person
# who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.

# Note:
# The number of people is less than 1,100.


# Example

# Input:
# [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

# Output:
# [[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]

class reconstructQueue:
    def doit(self, people):
        """
        :type people: List[List[int]]
        :rtype: List[List[int]]
        """
        import collections
        data = collections.defaultdict(list)
        for c in people:
            data[c[0]].append(c[1])

        index = list(data.keys())
        index.sort(reverse=1)
        res = []
        for c in index:
            data[c].sort()
            for y in data[c]:
                res.insert(y, [c, y])

        return res

    # <steve>
    def doit1(self, peoplr):
        """
        :type people: List[List[int]]
        :rtype: List[List[int]]
        """
        result = []
        for i in sorted(people, key=lambda x: (-x[0], x[1])):
            result.insert(i[1], i)
        return result

       



if __name__=="__main__":


    res = reconstructQueue().doit([[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]])


    pass
        