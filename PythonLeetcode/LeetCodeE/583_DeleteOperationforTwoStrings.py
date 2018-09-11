# 583. Delete Operation for Two Strings


# Given two words word1 and word2, find the minimum number of steps required to make word1 
# and word2 the same, where in each step you can delete one character in either string.

# Example 1:
# Input: "sea", "eat"
# Output: 2
# Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
# Note:
# The length of given words won't exceed 500.
# Characters in given words can only be lower-case letters.

class MinDistance:


    def doit(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rty
        """
        # To really compute the DP we dont need like the whole matrix.
        # All we need is the current row and previous
        
        dp = [0] * (len(word2) + 1)
        
        for c1 in word1:
            newDp = dp[:]
            for i,c2 in enumerate(word2):
                if c1 == c2:
                    newDp[i+1] = 1 + dp[i]
                else:
                    newDp[i+1] = max(newDp[i], dp[i+1])
            dp = newDp
        return len(word1) + len(word2) - 2 * dp[-1]


    def doit(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """


        # It is a typical dp problem, just like longest common subsequence. Firstly, 
        # we should figure out how to get the longest common subsequence comm. 
        # Setup a 2D arrays dp[n1+1][n2+1]. dp[i][j] means the longest subsequence between two substring word1[0:i]
        #  and word2[0:j]. We can deduce the equation like below:

        # word1[i-1] == word2[j-1]: dp[i][j] = dp[i-1][j-1] + 1
        # word1[i-1] != word2[j-1]: dp[i][j] = max(dp[i-1][j], dp[i][j-1])
        # Iterate like that, finally, dp[n1][n2] is the longest common subsequence length. 
        # In order to get the subsequence, each word has to delete length - dp[n1][n2] chars, so the result is
        # n1 - dp[n1][n2] + n2 - dp[n1][n2].

        if word1 == word2:
            return 0

        if not word1 or not word2:
            return max(len(word2), len(word1))
   
        dp = [ [0 for _ in range(len(word2) + 1)] for _ in range(len(word1) + 1)]

        for i in range(1, len(word1) + 1):

            for j in range(1, len(word2) + 1):

                if word1[i-1] == word2[j-1]:
                    dp[i][j] = dp[i-1][j-1] + 1

                else:
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1])

        return len(word1) + len(word2) - 2 * dp[-1][-1]
                                           

    #TLE
    def doit2(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        #bfs
        buff = [(word1, word2, 0)]
        visited = set()
        
        while buff:

            w1, w2, s = buff.pop(0)

            if w1 == w2:
                return s

            for i in range(len(w1)):
                buff.append((w1[:i] + w1[i+1:], w2, s + 1))

            for i in range(len(w2)):
                buff.append((w1, w2[:i] + w2[i+1:], s + 1))


        return 
            
            
        


    # TLE
    def doit1(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        minimal_steps = float('inf')
        visited = set()

        def dfs(w1, w2, step):
            nonlocal minimal_steps
            if step > minimal_steps:
                return 

            if w1 == w2:
                minimal_steps = min(minimal_steps, step)
                return
            
            if (w1, w2, step) in visited:
                return

            
            for i in range(len(w1)):
                dfs(w1[:i] + w1[i+1:], w2, step + 1)

            for i in range(len(w2)):
                dfs(w1, w2[:i] + w2[i+1:], step + 1)
                        

        dfs(word1, word2, 0)
        return minimal_steps

            

           


if __name__ == "__main__":

    res = MinDistance().doit("sea", "eat")

    res = MinDistance().doit("plasma", "altruism")

    res = 1