"""
1552. Magnetic Force Between Two Balls



In universe Earth C-137, Rick discovered a special form of magnetic force between two balls if they are put in his new invented basket. 
Rick has n empty baskets, the ith basket is at position[i], Morty has m balls and needs to distribute the balls into the baskets such that the minimum magnetic force between any two balls is maximum.

Rick stated that magnetic force between two different balls at positions x and y is |x - y|.

Given the integer array position and the integer m. Return the required force.

 

Example 1:


Input: position = [1,2,3,4,7], m = 3
Output: 3
Explanation: Distributing the 3 balls into baskets 1, 4 and 7 will make the magnetic force between ball pairs [3, 3, 6]. The minimum magnetic force is 3. We cannot achieve a larger minimum magnetic force than 3.
Example 2:

Input: position = [5,4,3,2,1,1000000000], m = 2
Output: 999999999
Explanation: We can use baskets 1 and 1000000000.
 

Constraints:

n == position.length
2 <= n <= 10^5
1 <= position[i] <= 10^9
All integers in position are distinct.
2 <= m <= position.length



"""


class MagneticForceBetweenTwoBalls:

    def doit_binary_search(self, position: list, m: int) -> int:

        position.sort()
        
        def search(gap):
            
            i, count = 0, 1
            base = position[i]
            
            while i < len(position) and count < m:
                if position[i] - base >= gap:
                    count += 1
                    base = position[i]
                i +=1
                    
            return count
        
        left, right = 0, position[-1] + 1
        ans = 0
        while left < right:
            
            mid = (left + right) // 2
            
            if search(mid) >= m:
                ans = max(ans, mid) 
                left = mid + 1
            else:
                right = mid
                
        return ans

    def doit_binary_search_1(self, position: list, m: int) -> int:
        import math
        n = len(position)
        position = sorted(position)
        left, right = 1, math.ceil((position[-1] - position[0]) / (m-1))

        while left < right:
            mid = (left + right + 1) // 2
            balls = 1
            cur = 0
            for i in range(1,n):
                cur += position[i] - position[i-1]
                if cur >= mid:
                    balls += 1
                    cur = 0
                    
            if balls >= m:
                left = mid
            else:
                right = mid - 1

        return left


if __name__ == '__main__':

    MagneticForceBetweenTwoBalls().doit_binary_search([1,2,3,4,7], 3)