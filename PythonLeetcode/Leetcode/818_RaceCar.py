# 818. Race Car

# Your car starts at position 0 and speed +1 on an infinite number line.  (Your car can go into negative positions.)

# Your car drives automatically according to a sequence of instructions A (accelerate) and R (reverse).

# When you get an instruction "A", your car does the following: position += speed, speed *= 2.

# When you get an instruction "R", your car does the following: if your speed is positive then speed = -1 , 
# otherwise speed = 1.  (Your position stays the same.)

# For example, after commands "AAR", your car goes to positions 0->1->3->3, and your speed goes to 1->2->4->-1.

# Now for some target position, say the length of the shortest sequence of instructions to get there.

# Example 1:
# Input: 
# target = 3
# Output: 2
# Explanation: 
# The shortest instruction sequence is "AA".
# Your position goes from 0->1->3.

# Example 2:
# Input: 
# target = 6
# Output: 5
# Explanation: 
# The shortest instruction sequence is "AAARA".
# Your position goes from 0->1->3->7->7->6.
 

# Note:

# 1 <= target <= 10000.



class Racecar:

    # <BFS>
    def doit(self, target):
        """
        :type target: int
        :rtype: int
        """
        st = [(0, 1, '')]
        visited = set()

        while st:
            
            a = st.pop(0)
            if a[0] == target:

                return len(a[2])
            else:
                # put a 'A'
                if 0<= a[0] + a[1] < 2 * target and (a[0] + a[1], a[1] * 2) not in visited:         
                    st.append((a[0] + a[1], a[1] * 2, a[2] + 'A'))
                    visited.add((a[0] + a[1], a[1] * 2))

                # put a 'R'
                if a[0] >= 0 and (a[0], -1 if a[1] > 0 else 1) not in visited: 
                    st.append((a[0], -1 if a[1] > 0 else 1, a[2] + 'R'))
                    visited.add((a[0], -1 if a[1] > 0 else 1))

        return -1


    # <DP>
    def doit1(self, target):
        """
        :type target: int
        :rtype: int
        """
        


        return -1

if __name__ == "__main__":

    res = Racecar().doit(6)

    res = Racecar().doit(3)

    res = Racecar().doit(1)

    pass


        