"""
# 72. Edit Distance


# Given two words word1 and word2, find the minimum number of steps required
# to convert word1 to word2. (each operation is counted as 1 step.)

# You have the following 3 operations permitted on a word:

# a) Insert a character
# b) Delete a character
# c) Replace a character

"""


class MinDistance:

    # O(n**2) <DP>
    def doit_dp(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        m, n = len(word1), len(word2)
        dp = [[0 for _ in range(n+1)] for x in range(m+1)]

        for x in range(m+1):
            dp[x][0] = x

        for y in range(n+1):
            dp[0][y] = y

        for i in range(1, m+1):
            for j in range(1, n+1):
                dp[i][j] = min(dp[i-1][j-1] + (1 if word1[i-1] != word2[j-1] else 0), min(dp[i-1][j], dp[i][j-1]) + 1)

        return dp[m][n]

    def doit_dp_1(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        if len(word1) < len(word2):
            word1, word2 = word2, word1

        D = [x for x in range(len(word1)+1)]
        DL = D[:]

        for i in range(1, len(word2)+1):
            D[0] = i

            for j in range(1, len(word1)+1):

                #if word2[i-1] == word1[j-1]:
                #    D[j] = DL[j-1]
                #else:
                #    D[j] = min(DL[j], D[j-1], DL[j-1]) + 1

                D[j] = min(DL[j-1] + (1 if word2[i-1] != word1[j-1] else 0), min(D[j-1], DL[j]) + 1)

            DL = D[:]

        return D[len(word1)]        

    # <BFS>
    def doit_bfs(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        def minDistanceRecurse(word1, word2, i, j, calcultedData):
            if i == -1 and j == -1:
                calcultedData[(-1,-1)] = 0
                return 0

            if i == -1:
                return j+1
            if j == -1:
                return i+1

            key = (i-1,j-1)
            if key not in calcultedData:
                calcultedData[key] = minDistanceRecurse(word1, word2, i-1, j-1, calcultedData) 
        
            if word1[i] == word2[j]:
                return calcultedData[key]
        
            option1 = 1 + calcultedData[key]
        
            key = (i, j-1)
            if key not in calcultedData:
                calcultedData[key] = minDistanceRecurse(word1, word2, i, j-1, calcultedData) 
            option2 = 1 + calcultedData[key]
        
            key = (i-1, j)
            if key not in calcultedData:
                calcultedData[key] = minDistanceRecurse(word1, word2, i-1, j, calcultedData) 
            option3 = 1 + calcultedData[key]
        
            return min(option1, option2, option3)

        calcultedData = {}
        
        return minDistanceRecurse(word1, word2, len(word1)-1, len(word2)-1, calcultedData)


if __name__=="__main__":
    
    res = MinDistance().doit_dp("", "a")