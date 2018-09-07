# 474. Ones and Zeroes

# In the computer world, use restricted resource you have to generate maximum benefit is what we always want to pursue.

# For now, suppose you are a dominator of m 0s and n 1s respectively. On the other hand, there is an array with strings consisting of only 0s and 1s.

# Now your task is to find the maximum number of strings that you can form with given m 0s and n 1s. Each 0 and 1 can be used at most once.

# Note:
# The given numbers of 0s and 1s will both not exceed 100
# The size of given string array won't exceed 600.
# Example 1:
# Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
# Output: 4

# Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3 1s, which are “10,”0001”,”1”,”0”
# Example 2:
# Input: Array = {"10", "0", "1"}, m = 1, n = 1
# Output: 2

# Explanation: You could form "10", but then you'd have nothing left. Better form "0" and "1".


class FindMaxForm:

    # best one
    def doit3(self, strs, m, n):
        """
        :type strs: List[str]
        :type m: int
        :type n: int
        :rtype: int
        """
        def getMax(arr, m, n):
            res = 0

            for e in arr:
                if m >= e[0] and n >= e[1]:
                    res += 1
                    m -= e[0]
                    n -= e[1]

            return res

        arr = [(s.count('0'), s.count('1')) for s in strs]
        arr1 = sorted(arr, key=lambda s: -min(m - s[0], n - s[1]))
        arr2 = sorted(arr, key=lambda s: min(s[0], s[1]))
        res = max(getMax(arr1, m, n), getMax(arr2, m, n))

        return res


    def doit(self, strs, m, n):
        """
        :type strs: List[str]
        :type m: int
        :type n: int
        :rtype: int
        """
        numbers = list(map(lambda x: (x.count('0'), x.count('1')), strs))
        numbers.sort()
        dp = {}

        def dfs(m, n, idx):

            if (m, n, idx) in dp:
                return dp[(m, n, idx)]
            
            tmp = 0
            i = idx
            while i < len(numbers):

                if numbers[i][0] <= m and numbers[i][1] <= n:
                    tmp = max(tmp, 1 + dfs(m - numbers[i][0], n - numbers[i][1], i + 1))

                while i < len(numbers) - 1 and numbers[i] == numbers[i+1]:
                    i += 1

                i += 1

            dp[(m, n, idx)] = tmp
            return tmp

        return dfs(m, n, 0)


    def doit1(self, strs, m, n):
        """
        :type strs: List[str]
        :type m: int
        :type n: int
        :rtype: int
        """
        number = []
        for s in strs:
            counter = collections.Counter(s)
            if '0' not in counter:
                counter['0'] = 0
            elif '1' not in counter:
                counter['1'] = 0
            number.append((counter['0'], counter['1']))
        number.sort()   
        dp = collections.defaultdict(int)
        
        def dfs(m, n, idx):
            if (m, n, idx) in dp:
                return dp[(m, n, idx)]
            tmp = 0
            i = idx
            while i < len(strs):
                zeros, ones = number[i]
                if m - zeros >= 0 and n - ones >= 0:
                    tmp = max(tmp, 1+dfs(m - zeros, n - ones, i+1))
                
                while i < len(strs)-1 and number[i] == number[i+1]:
                    i += 1
                i += 1
                    
            dp[(m,n,idx)] = tmp
            return tmp
        
        return dfs(m, n, 0)        
        



if __name__ == "__main__":

    res = FindMaxForm().doit(["10", "0001", "111001", "1", "0"], m = 5, n = 3)

    res = FindMaxForm().doit(["10", "0", "1"], m = 1, n = 1)

    res = FindMaxForm().doit(["0","0","1","1"], m = 2, n = 2)

    res = 1