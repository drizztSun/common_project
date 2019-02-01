# 754. Reach a Number

# You are standing at position 0 on an infinite number line. There is a goal at position target.

# On each move, you can either go left or right. During the n-th move (starting from 1), you take n steps.

# Return the minimum number of steps required to reach the destination.

# Example 1:
# Input: target = 3
# Output: 2
# Explanation:
# On the first move we step from 0 to 1.
# On the second step we step from 1 to 3.

# Example 2:
# Input: target = 2
# Output: 3
# Explanation:
# On the first move we step from 0 to 1.
# On the second move we step  from 1 to -1.
# On the third move we step from -1 to 2.

class ReachNumber:

# Brute method is backtracking, but it throws run time error.

# So the new idea is keeping adding. For example, the target the 12, if always points to the positive way, it will become 1+2+3+4+5=15, 
# which is the first position larger than our target. The gap between 12 and 15 is 3, if we can find the combination of 3, 
# then we can come out the solution and the minimal step is 5.

# Wait a minute! if we directly change the 3rd step from +3 to -3(1+2-3+4+5), the new sum will become 9, 
# which actually introduce 6 loss to original result. So, it indicates that the gap must be an even number. 
# 1+2+3+4+5+6 = 21(gap is 21-12=9), 1+2+3+4+5+6+7 = 28(gap is 28-12=16), so the result is step 7. 1-2+3+4+5-6+7= 12

    def doit(self, target):
        """
        :type target: int
        :rtype: int
        """
        target = abs(target)
        step, total = 1, 0

        while True:

            total += step
            if total >= target and (total - target) % 2 == 0:
                return step
            step += 1

# Let's look at some small n and the positions we can reach:
# n = 1, pos = [-1, 1]
# n = 2, pos = [-3, -1, 1, 3]
# n = 3, pos = [-6, -4, -2, 0, 2, 4, 6]
# n = 4, pos = [-10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10]
# ....

# Basically we can observe that after n step and the farthest position is m = n*(n+1)/2, 
# then the positionss we can reach are [-m, -m+2, -m+4, ......, m-4, m-2, m]. It can be proved by Mathematical Induction.

# Then our code is simple:

    def doit2(self, target):
        """
        :type target: int
        :rtype: int
        """
        target = abs(target)
        n, m = 0, 0

        while m < target:
            n += 1
            m += n

        while m % 2 != target % 2:
            n += 1
            m += n
        
        return n
        
        

    def doit1(self, target):
        """
        :type target: int
        :rtype: int
        """
        buff = [0]
        visited = set()
        i = 0
        
        while buff :
            i += 1
            tmp = []
            
            for c in buff:
                if target in (c + i, c- i):
                    return i
                
                if c + i not in visited:
                    tmp.append(c+i)
                    #visited.add(c+i)
                
                if c - i not in visited:
                    tmp.append(c-i)
                    #visited.add(c-i)
                    
            buff = tmp
        
        return -1


if __name__ == "__main__":
    
    res = ReachNumber().doit(2)
    
    res = ReachNumber().doit(3)
            
            
        
