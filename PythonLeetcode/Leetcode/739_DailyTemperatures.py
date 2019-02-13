# 739. Daily Temperatures

# Given a list of daily temperatures T, return a list such that, for each day in the input, 
# tells you how many days you would have to wait until a warmer temperature. 
# If there is no future day for which this is possible, put 0 instead.

# For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73], your output should be [1, 1, 4, 2, 1, 1, 0, 0].

# Note: The length of temperatures will be in the range [1, 30000]. Each temperature will be an integer in the range [30, 100].


class DailyTemperatures:

    # O(n)
    def doit(self, T: 'List[int]') -> 'list[int]':
        # Intuition: The intuition is to traverse the array in reverse. 
        # And to find the index of the higher temperature by using the previously calculated values.
        ans = [0]*len(T)
        for i in range(len(T) - 2, -1, -1):

            if T[i] < T[i+1]:
                ans[i] = 1
            else:
                m = i + 1 + ans[i+1]
                while m < len(T):
                    if T[i] < T[m]:
                        ans[i] = m - i
                        break
                    else:
                        if ans[m]:
                            m = m + ans[m]
                        else:
                            ans[i] = 0
                            break

        return ans


    def doit_but_tls(self, T: 'List[int]') -> 'List[int]':
        
        dates = {}
        for i, c in enumerate(T):
            if c not in dates:
                dates[c] = []
            dates[c].append(i)
            
        ans = []
        keys = sorted(dates.keys())
        for i, c in enumerate(T):
            days = float('inf')
            # too much for and increse the 
            for n in keys:
                if c < n:
                    for d in dates[n]:
                        if d > i and d < days:
                            days = d
                            
            ans.append(days - i if days != float('inf') else 0)
            
        return ans
            
    # worst one 
    # Complexity Analysis
    # Time Complexity: O(NW)O(NW), where NN is the length of T and WW is the number of allowed values for T[i]. 
    # Since W = 71W=71, we can consider this complexity O(N)O(N).
    # Space Complexity: O(N + W)O(N+W), the size of the answer and the next array.
    def doit1(self, T):

        nxt = [float('inf')] * 102
        ans = [0] * len(T)

        for i in range(len(T) - 1, -1, -1):
            #Use 102 so min(nxt[t]) has a default value
            warmer_index = min(nxt[t] for t in xrange(T[i]+1, 102))
            if warmer_index < float('inf'):
                ans[i] = warmer_index - i
            nxt[T[i]] = i
        return ans

    # Complexity Analysis
    # Time Complexity: O(N)O(N), where NN is the length of T and WW is the number of allowed values for T[i]. 
    # Each index gets pushed and popped at most once from the stack.
    # Space Complexity: O(W)O(W). The size of the stack is bounded as it represents strictly increasing temperatures.
    def doit2(self, T):
        ans = [0] * len(T)
        stack = [] #indexes from hottest to coldest
        for i in xrange(len(T) - 1, -1, -1):
            while stack and T[i] >= T[stack[-1]]:
                stack.pop()
            if stack:
                ans[i] = stack[-1] - i
            stack.append(i)
        return ans            