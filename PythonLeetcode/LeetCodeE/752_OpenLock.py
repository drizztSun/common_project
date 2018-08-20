# 752. Open the Lock

# You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. 
# The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning one wheel one slot.

# The lock initially starts at '0000', a string representing the state of the 4 wheels.

# You are given a list of deadends dead ends, meaning if the lock displays any of these codes, 
# the wheels of the lock will stop turning and you will be unable to open it.

# Given a target representing the value of the wheels that will unlock the lock,
# return the minimum total number of turns required to open the lock, or -1 if it is impossible.

# Example 1:
# Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
# Output: 6
# Explanation:
# A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
# Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
# because the wheels of the lock become stuck after the display becomes the dead end "0102".

# Example 2:
# Input: deadends = ["8888"], target = "0009"
# Output: 1
# Explanation:
# We can turn the last wheel in reverse to move from "0000" -> "0009".

# Example 3:
# Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
# Output: -1
# Explanation:
# We can't reach the target without getting stuck.

# Example 4:
# Input: deadends = ["0000"], target = "8888"
# Output: -1
# Note:
# The length of deadends will be in the range [1, 500].
# target will not be in the list deadends.
# Every string in deadends and the string target will be a string of 4 digits from the 10,000 possibilities '0000' to '9999'.


class OpenLock(object):


    def doit(self, deadends, target):
        """
        :type deadends: List[str]
        :type target: str
        :rtype: int
        """
        if '0000' in deadends:
            return -1
        
        # Bi-direction BFS
        step = 0
        startSet = set(['0000'])
        endSet = set([target])
        visited = set()
        children = [(0,1),(0,-1),(1,1),(1,-1),(2,1),(2,-1),(3,1),(3,-1)]
        dead = set(deadends)

        while startSet:

            if len(startSet) > len(endSet):
                startSet, endSet = endSet, startSet

            newSet = set()
            for element in startSet:
                if element in endSet:
                    return step

                visited.add(element)
                for pos, d in children:
                    val = (int(element[pos]) + d) % 10
                    new_element = element[:pos] + str(val) + element[pos+1:]

                    if not new_element in dead and not new_element in visited:
                        newSet.add(new_element)

            step += 1
            startSet = newSet

        return -1


    def doit(self, deadends, target):
        """
        :type deadends: List[str]
        :type target: str
        :rtype: int
        """
        qu = [('0000', 0)]
        visited = set('0000')
        ended = set(deadends)
        if '0000' in ended:
            return -1

        while qu:

            length = len(qu)
            while length > 0:

                v, s = qu.pop(0)

                if v == target:
                    return s

                for i in range(4):

                    cur = int(v[i]) - int('0')

                    s1 = v[:i] + "0123456789"[0 if cur == 9 else cur + 1] + v[i+1:]
                    s2 = v[:i] + '0123456789'[9 if cur == 0 else cur - 1] + v[i+1:]

                    if s1 not in visited and s1 not in ended:
                        qu.append((s1, s + 1))
                        visited.add(s1)

                    if s2 not in visited and s2 not in ended:
                        qu.append((s2, s + 1))
                        visited.add(s2)

                length -= 1
                
        return -1


if __name__ == "__main__":

    res = OpenLock().doit(["0201","0101","0102","1212","2002"], "0202")

    res = OpenLock().doit(["8888"], "0009")

    res = OpenLock().doit(["8887","8889","8878","8898","8788","8988","7888","9888"], "8888")

    res = OpenLock().doit(["0000"], "8888")

    pass        
        