"""
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

"""


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
            # put a 'A'
            if 0 <= a[0] + a[1] < 2 * target and (a[0] + a[1], a[1] * 2) not in visited:
                st.append((a[0] + a[1], a[1] * 2, a[2] + 'A'))
                visited.add((a[0] + a[1], a[1] * 2))

            # put a 'R'
            if a[0] >= 0 and (a[0], -1 if a[1] > 0 else 1) not in visited:
                st.append((a[0], -1 if a[1] > 0 else 1, a[2] + 'R'))
                visited.add((a[0], -1 if a[1] > 0 else 1))

        return -1


    """
    Approach #1: Dijkstra's [Accepted]
    Intuition
    
    With some target, we have different moves we can perform (such as k[1] =0,1,2,⋯, using the notation from our Approach Framework), with different costs.
    This is an ideal setup for Dijkstra's algorithm, which can help us find the shortest cost path in a weighted graph.
    
    Algorithm
    Dijkstra's algorithm uses a priority queue to continually searches the path with the lowest cost to destination, 
    so that when we reach the target, we know it must have been through the lowest cost path. Refer to this link for more detail.
    
    Back to the problem, as described above, we have some barrier where we are guaranteed to never cross. 
    We will also handle negative targets; in total we will have 2 * barrier + 1 nodes.
    
    After, we could move walk = 2**k - 1 steps for a cost of k + 1 (the 1 is to reverse). If we reach our destination exactly, we don't need the R, so it is just k steps.
    
    Complexity Analysis

    Time Complexity: O(TlogT). There are O(T) nodes, we process each one using O(logT) work (both popping from the heap and adding the edges).
    
    Space Complexity: O(T).
    """
    def doit_dijstra(self, target):
        import heapq
        K = target.bit_length() + 1
        barrier = 1 << K
        pq = [(0, target)]
        dist = [float('inf')] * (2 * barrier + 1)
        dist[target] = 0

        while pq:
            steps, targ = heapq.heappop(pq)
            if dist[targ] > steps:
                continue

            for k in range(K+1):
                walk = (1 << k) - 1
                steps2, targ2 = steps + k + 1, walk - targ
                if walk == targ:
                    steps2 -= 1 #No "R" command if already exact

                if abs(targ2) <= barrier and steps2 < dist[targ2]:
                    heapq.heappush(pq, (steps2, targ2))
                    dist[targ2] = steps2

        return dist[0]

    """
    Approach #2: Dynamic Programming [Accepted]
    Intuition and Algorithm
    
    As in our Approach Framework, we've framed the problem as a series of moves k[i]
    Now say we have some target 2**(k-1) <= t < 2**k and we want to know the cost to go there, if we know all the other costs dp[u] (for u < t).
    
    If t == 2**k - 1, the cost is just k: we use the command A**k, and clearly we can't do better.
    
    Otherwise, we might drive without crossing the target for a position change of 2**{k-1} - 2**j, by the command A**{k-1} R A**{j}, for a total cost of k - 1 + j + 2k−1+j+2.
    
    Finally, we might drive 2**k - 1 which crosses the target, by the command A**k R, for a total cost of k + 1.
    We can use dynamic programming together with the above recurrence to implement the code below.
    """
    def doit_dp(self, target):
        """
        :type target: int
        :rtype: int
        """
        dp = [0, 1, 4] + [float('inf')] * target
        for t in range(3, target + 1):
            k = t.bit_length()
            if t == 2**k - 1:
                dp[t] = k
                continue
            for j in range(k - 1):
                dp[t] = min(dp[t], dp[t - 2**(k - 1) + 2**j] + k - 1 + j + 2)
            if 2**k - 1 - t < t:
                dp[t] = min(dp[t], dp[2**k - 1 - t] + k + 1)
        return dp[target]


    def doit_dp_1(self, target: int) -> int:
        dp = {0: 0}
        def search(t):
            if t in self.dp:
                return self.dp[t]
            n = t.bit_length()
            if 2 ** n - 1 == t:
                self.dp[t] = n
            else:
                self.dp[t] = search(2 ** n - 1 - t) + n + 1
                for m in range(n - 1):
                    self.dp[t] = min(self.dp[t], search(t - 2 ** (n - 1) + 2 ** m) + n + m + 1)
        return self.dp[target]


if __name__ == "__main__":

    res = Racecar().doit_dijstra(6)

    res = Racecar().doit_dp(3)

    res = Racecar().doit(1)
