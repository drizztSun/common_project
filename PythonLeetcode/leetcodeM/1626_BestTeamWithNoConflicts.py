"""
1626. Best Team With No Conflicts

You are the manager of a basketball team. For the upcoming tournament, you want to choose the team with the highest overall score. The score of the team is the sum of scores of all the players in the team.

However, the basketball team is not allowed to have conflicts. A conflict exists if a younger player has a strictly higher score than an older player. A conflict does not occur between players of the same age.

Given two lists, scores and ages, where each scores[i] and ages[i] represents the score and age of the ith player, respectively, return the highest overall score of all possible basketball teams.



Example 1:

Input: scores = [1,3,5,10,15], ages = [1,2,3,4,5]
Output: 34
Explanation: You can choose all the players.
Example 2:

Input: scores = [4,5,6,5], ages = [2,1,2,1]
Output: 16
Explanation: It is best to choose the last 3 players. Notice that you are allowed to choose multiple people of the same age.
Example 3:

Input: scores = [1,2,3,5], ages = [8,9,10,1]
Output: 6
Explanation: It is best to choose the first 3 players.


Constraints:

1 <= scores.length, ages.length <= 1000
scores.length == ages.length
1 <= scores[i] <= 106
1 <= ages[i] <= 1000
"""


class BestTeamScore:


    """
        O(n^2)
    """
    def doit_dp(self, scores: list, ages: list) -> int:

        n = len(scores)
        idx = [i for i in range(n)]

        idx.sort(key=lambda x: (ages[x], scores[x]))

        dp = [0 for _ in range(len(idx))]
        ans = 0

        for i in range(len(idx)):
            
            dp[i] = scores[idx[i]]
        
            for j in reversed(range(i)):

                if scores[idx[j]] <= scores[idx[i]]:

                    dp[i] = max(dp[i], dp[j] + scores[idx[i]])

            ans = max(ans, dp[i])

        return ans

    def doit_(self, scores: list, ages: list) -> int:
        
#         # Making a zipped list 
#         adj=list(zip(ages,scores))
        
#         # Sorting on the basis of age as by default first parameter
#         adj.sort()
        
#         # Making a dp list and storing that individual score as it can always be the answer
#         dp=[-1 for i in scores]
#         print(dp)
        
        
#         for i in range(len(scores)):
#             dp[i]=adj[i][1]
#             for j in range(i):
#                 if(adj[i][1]>=adj[j][1]):   # If the score of the ith age (which surely is large then jth age) as sorted  is greater or equal
#                     dp[i]=max(dp[i],dp[j]+adj[i][1])
                    
#         print(dp)            
#         return max(dp);

#         adj=list(zip(ages,scores))
#         adj.sort()
#         dp = [-1 for j in ages]
        max_scores=[0]*(max(ages)+1)
        
        for score, age in sorted(zip(scores, ages)): 
            max_scores[age] = score + max(max_scores[:age + 1])

        return max(max_scores)

    """
        O(n*log(n))
    """
    def doit_dp_BIT(self, scores: list, ages: list) -> int:

        tuples = sorted(zip(scores, ages))
        
        dp = [0] * (max(ages))
        
        for score, age in tuples:
		
			#query the max score
            m = 0
            i = age
            while i > 0:
                m = max(m, dp[i-1])
                i -= i&(-i)
            dp[age-1] = m+score

			# update the tree
            i = age
            while i <= len(dp):
                dp[i-1] = max(dp[age-1], dp[i-1])
                i += i&(-i)
            
        return max(dp)
		