# 821. Shortest Distance to a Character

# Given a string S and a character C, return an array of integers representing the shortest distance 
# from the character C in the string.

# Example 1:

# Input: S = "loveleetcode", C = 'e'
# Output: [3, 2, 1, 0, 1, 0, 0, 1, 2, 2, 1, 0]
 

# Note:

# S string length is in [1, 10000].
# C is a single character, and guaranteed to be in string S.
# All letters in S and C are lowercase.

class ShortestToChar:
    def doit(self, S: 'str', C: 'str') -> 'List[int]':
        
        left, right = -1, S.find(C)
        ans = []
        
        for i in range(len(S)):
            if S[i] == C:
                left, right = right, S.find(C, i+1)
                
            leftDis = float('inf') if left == -1 else abs(i - left)
            rightDis = float('inf') if right == -1 else abs(right - i)
                
            ans.append(min(leftDis, rightDis))
            
        return ans


    def doit1(self, S: 'str', C: 'str') -> 'List[int]':

        prev = float('-inf')
        ans = []
        for i, x in enumerate(S):
            if x == C: 
                prev = i
            ans.append(i - prev)

        prev = float('inf')
        for i in range(len(S) - 1, -1, -1):
            if S[i] == C: prev = i
            ans[i] = min(ans[i], prev - i)

        return ans


if __name__ == "__main__":

    res = ShortestToChar().doit("loveleetcode", "e")

    res = ShortestToChar().doit("aabb", "b")