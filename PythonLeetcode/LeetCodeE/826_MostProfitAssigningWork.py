# 826. Most Profit Assigning Work

# We have jobs: difficulty[i] is the difficulty of the ith job, and profit[i] is the profit of the ith job. 

# Now we have some workers. worker[i] is the ability of the ith worker, which means that this worker can only complete a job with difficulty at most worker[i]. 

# Every worker can be assigned at most one job, but one job can be completed multiple times.

# For example, if 3 people attempt the same job that pays $1, then the total profit will be $3.  If a worker cannot complete any job, his profit is $0.

# What is the most profit we can make?

# Example 1:

# Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
# Output: 100 
# Explanation: Workers are assigned jobs of difficulty [4,4,6,6] and they get profit of [20,20,30,30] seperately.
# Notes:

# 1 <= difficulty.length = profit.length <= 10000
# 1 <= worker.length <= 10000
# difficulty[i], profit[i], worker[i]  are in range [1, 10^5]

class MaxProfitAssignment:
    def doit1(self, difficulty, profit, worker):
        """
        :type difficulty: List[int]
        :type profit: List[int]
        :type worker: List[int]
        :rtype: int
        """
        import bisect
        total = 0
        map_maxprofit = {}
        maxv = 0
        for i in range(len(difficulty)):
            maxv = max(maxv, profit[i])
            map_maxprofit[difficulty[i]] = maxv

        for c in worker:

            i = bisect.bisect_left(difficulty, c)
            if i == len(difficulty) or difficulty[i] > c:
                i -= 1

            if i >= 0:
                total += map_maxprofit[difficulty[i]]

        return total


    def doit(self, difficulty, profit, worker):
            """
            :type difficulty: List[int]
            :type profit: List[int]
            :type worker: List[int]
            :rtype: int
            """
            import bisect
            nums = sorted(list(zip(difficulty, profit)))
            maxv, total = 0, 0
            maxprofit = {}
        
            for i, c in enumerate(nums):
                maxv = max(maxv, c[1])
                maxprofit[c[0]] = maxv

            difficulty.sort()
            for c in worker:
                i = bisect.bisect_left(difficulty, c)
                if i == len(difficulty) or difficulty[i] > c:
                    i -= 1

                if i >= 0:
                    total += maxprofit[difficulty[i]]

            return total                



if __name__ == "__main__":

    res = MaxProfitAssignment().doit(difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7])

    res = MaxProfitAssignment().doit([5, 50, 92, 21, 24, 70, 17, 63, 30, 53],
                                     [68,100,3,  99, 56, 43, 26, 93, 55, 25],
                                     [96,3,55,30,11,58,68,36,26,1])
    
    res = 1