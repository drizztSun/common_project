


# 514. Freedom Trail

# In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring",
# and use the dial to spell a specific keyword in order to open the door.

# Given a string ring, which represents the code engraved on the outer ring and another string key,
# which represents the keyword needs to be spelled. You need to find the minimum number of steps in order to spell all the characters in the keyword.

# Initially, the first character of the ring is aligned at 12:00 direction.
# You need to spell all the characters in the string key one by one by rotating the ring clockwise or anticlockwise to make each character of the string key aligned at 12:00 direction and then by pressing the center button. 
# At the stage of rotating the ring to spell the key character key[i]:
# You can rotate the ring clockwise or anticlockwise one place, which counts as 1 step.
# The final purpose of the rotation is to align one of the string ring's characters at the 12:00 direction,
# where this character must equal to the character key[i].

# If the character key[i] has been aligned at the 12:00 direction, you need to press the center button to spell, which also counts as 1 step.
# After the pressing, you could begin to spell the next character in the key (next stage), otherwise, you've finished all the spelling.
# Example:



# Input: ring = "godding", key = "gd"
# Output: 4
# Explanation:
# For the first key character 'g', since it is already in place, we just need 1 step to spell this character. 
# For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
# Also, we need 1 more step for spelling.
# So the final output is 4.

import collections

class FindRotateSteps:


    # <dfs> <DP>
    def doit1(self, ring, key):
        """
        :type ring: str
        :type key: str
        :rtype: int
        """
        def search(rIndex, kIndex) :

            if kIndex == len(key):
                return 0
            
            if (rIndex, kIndex) in D:
                return D[(rIndex, kIndex)]

            res = float('inf')
            for pos in charDict[key[kIndex]]:

                step = min(abs(pos - rIndex), len(ring) - abs(pos - rIndex))
                res = min(res, step + search(pos, kIndex + 1))
            
            D[(rIndex, kIndex)] = res + 1
            return D[(rIndex, kIndex)]

        charDict = collections.defaultdict(list)
        D = {}
        for i, c in enumerate(ring):
            charDict[c].append(i)

        return search(0, 0)


    # <DP>
    def doit(self, ring, key):
        """
        :type ring: str
        :type key: str
        :rtype: int
        """
        length = len(ring)

        def distance(pre, next):

            return min(abs(pre - next), length - abs(pre - next))

        h = {}
        for i, c in enumerate(ring):
            if c not in h:
                h[c] = []
            h[c].append(i)

        pcl_pre = [[0, 0]]

        for k in key:

            pcl_next = [[p, 0] for p in h[k]]

            for pclnext in pcl_next:

                cmin = float('inf')
                for pclpre in pcl_pre:

                    cmin = min(cmin, pclpre[1] + distance(pclpre[0], pclnext[0]))

                pclnext[1] = cmin

            pcl_pre = pcl_next

        cmin = float('inf')
        for c in pcl_pre:
            cmin = min(cmin, c[1])

        return len(key) + cmin


# Simple dp idea

# recording each index of characters in ring,beacuse each characters we have search in this time would be starting index in the next search
# How could we solve the problem that rotate the ring to the left or right ?
# My idea is min((tmp[j] + size -it)%size,(it + size - tmp[j])%size)
# Suppose you want to rotate the ring to the right and search ‘k’, and the size is 5.
# We could calculate it by this + size -k(index)%size
# this -  -  -  -  k
# If we want to rotate the ring to the left，what should we do? It is the same problem with above problem,move this to its right,and reach k
# k -  -  -  -   this
# So we could calculate it by k(index) + size -this%size
# There are many people use abs() instead of %size,I think it’s faster than mine :)


    def doit(self, ring, key):
        """
        :type ring: str
        :type key: str
        :rtype: int
        """

        pass









                        
        




if __name__=="__main__":

    res = FindRotateSteps().doit("godding", "gd")



    pass
    