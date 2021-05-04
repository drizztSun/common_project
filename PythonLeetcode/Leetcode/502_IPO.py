"""
# 502. IPO

# Suppose LeetCode will start its IPO soon. In order to sell a good price of its shares to Venture Capital,
# LeetCode would like to work on some projects to increase its capital before the IPO. Since it has limited resources,
# it can only finish at most k distinct projects before the IPO.
# Help LeetCode design the best way to maximize its total capital after finishing at most k distinct projects.

# You are given several projects. For each project i, it has a pure profit Pi and a minimum capital of Ci is needed to
# start the corresponding project. Initially, you have W capital. When you finish a project,
# you will obtain its pure profit and the profit will be added to your total capital.

# To sum up, pick a list of at most k distinct projects from given projects to maximize your final capital,
# and output your final maximized capital.

#Example 1:

# Input: k=2, W=0, Profits=[1,2,3], Capital=[0,1,1].

# Output: 4

# Explanation: Since your initial capital is 0, you can only start the project indexed 0.
#             After finishing it you will obtain profit 1 and your capital becomes 1.
#             With capital 1, you can either start the project indexed 1 or the project indexed 2.
#             Since you can choose at most 2 projects, you need to finish the project indexed 2 to get the maximum capital.
#             Therefore, output the final maximized capital, which is 0 + 1 + 3 = 4.

"""


class findMaximizedCapital(object):

    def doit_heap_greedy(self, k: int, W: int, Profits: list, Capital: list) -> int:

        from heapq import heappush, heappop, heapify

        projects = sorted([(c1, c2) for c1, c2 in zip(Capital, Profits)])

        i, heap = 0, []
        heapify(heap)

        while k > 0:

            while i < len(projects) and projects[i][0] <= W:
                heappush(heap, -projects[i][1])
                i += 1

            if not heap: break

            W -= heappop(heap)
            k -= 1

        return W

    """
        Approach 1: Greedy with Heap
            Intuition
            
            This is a greedy problem, and the only hard moment here is that capital is changing and so the list of available projects.
            
            fig
            
            That could be solved by using two data structures:
            
            projects to track all the projects which are not implemented yet.
            
            available to track projects available with the current capital.
            
            pic
            
            Algorithm
            
            To speed up, first check if here is a situation when all the projects are available with the initial capital W >= max(Capital). If so, return the sum of kth largest elements in Profits.
            
            Build structure projects which
            
            contains an information about capital and profit from each project,
            
            is sorted by capitals, and
            
            provides pop operation to remove already taken projects.
            
            That could be min heap in Java and array of sets in Python.
            
            Iterate over k to choose k projects. At each step
            
            Update a list of projects available with the current capital. One could choose max heap as a structure for available projects to simplify the peek of the most profitable one on the next step.
            
            If there are any, choose the most profitable one, update W and proceed further.
            
            Break, if the capital isn't large enough to start any project.
            
            Return W.
            
            Implementation
            
            
            Complexity Analysis
            
            Time complexity:
            
            \mathcal{O}(N \log k)O(Nlogk) in the best case when all projects are available with the initial capital.
            
            Otherwise, one needs \mathcal{O}(N \log N)O(NlogN) time to create and sort projects, and another \mathcal{O}(N \log N)O(NlogN) to update the available projects, and finally \mathcal{O}(k \log N)O(klogN) to compute the capital.
            
            Hence, the overall time complexity is \mathcal{O}(N \log N + N \log N + k \log N)O(NlogN+NlogN+klogN). Assuming that k < Nk<N, we would have \mathcal{O}(N \log N)O(NlogN) time complexity at the end.
            
            Space complexity : \mathcal{O}(N)O(N).
    """
    def doit_heap_greedy(self, k: int, W: int, Profits: list, Capital: list) -> int:
        from heapq import nlargest, heappop, heappush

        # to speed up: if all projects are available
        if W >= max(Capital):
            return W + sum(nlargest(k, Profits))

        n = len(Profits)
        projects = [(Capital[i], Profits[i]) for i in range(n)]
        # sort the projects :
        # the most available (= the smallest capital) is the last one
        projects.sort(key=lambda x: -x[0])

        available = []
        while k > 0:
            # update available projects
            while projects and projects[-1][0] <= W:
                heappush(available, -projects.pop()[1])
            # if there are available projects,
            # pick the most profitable one
            if available:
                W -= heappop(available)
            # not enough capital to start any project
            else:
                break
            k -= 1
        return W

    """
        Approach 2: Greedy with Array
        Intuition
        
        In the previous approach, we applied the Heap data structure to track the available projects and the ones that are implemented. We could actually implement the Greedy algorithm without the need of Heap.
        
        The idea is to keep all projects in the list, and use the technique of in-place modification to mark the ones that have been selected.
        
        Here one could set the capital to start as infinity for the projects which are already done.
        
        fic
        
        Algorithm
        
        To speed up, first check if here is a situation when all the projects are available with the initial capital W >= max(Capital). If so, return the sum of kth largest elements in Profits.
        
        Iterate over k to choose k projects. At each step
        
        Choose the most profitable project. For that, iterate over all N projects and between the ones with W >= Capital[j], choose the project with max Profits[j].
        
        Break, if the capital isn't large enough to start any project.
        
        Update W to add the profit from the chosen project W += Profits[idx] and then discard this project from the further consideration Capital[j] = Integer.MAX_VALUE.
        
        Return W.
        
        Implementation
        
        
        Complexity Analysis
        
        Time complexity:
        
        \mathcal{O}(N \log k)O(Nlogk) in the best case when all projects are available with the initial capital.
        
        Otherwise, \mathcal{O}(k \cdot N)O(k⋅N), assuming k < Nk<N.
        
        Space complexity:
        
        If all projects are available with the initial capital, then \mathcal{O}(k)O(k) in Java and \mathcal{O}(1)O(1) in Python.
        
        Otherwise, it is a constant space solution \mathcal{O}(1)O(1).
    """

    def doit_greedy_(self, k: int, W: int, Profits: list, Capital: list) -> int:
        # to speed up: if all projects are available
        if W >= max(Capital):
            return W + sum(nlargest(k, Profits))

        n = len(Profits)
        for i in range(min(n, k)):
            idx = -1
            # if there are available projects,
            # pick the most profitable one
            for j in range(n):
                if W >= Capital[j]:
                    if idx == -1:
                        idx = j
                    elif Profits[idx] < Profits[j]:
                        idx = j

            # not enough capital to start any project
            if idx == -1:
                break

            # add the profit from chosen project
            # and remove the project from further consideration
            W += Profits[idx]
            Capital[idx] = float('inf')

        return W

    # <greedy> <heap>
    def doit1(self, k, W, Profits, Capital):
        """
        :type k: int
        :type W: int
        :type Profits: List[int]
        :type Capital: List[int]
        :rtype: int
        """
        import heapq
        candidates = sorted(zip(Capital, Profits), reverse = 1)
        buff = []

        for _ in range(k):
    
            while candidates and candidates[-1][0] <= W:

                heapq.heappush(buff, -candidates.pop()[1])

            if buff:
                W += -heapq.heappop(buff)

        return W    


if __name__=="__main__":

    res = findMaximizedCapital().doit(k=2, W=0, Profits=[1,2,3], Capital=[0,1,1]) # 4
