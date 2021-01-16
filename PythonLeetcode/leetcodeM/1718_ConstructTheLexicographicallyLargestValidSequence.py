"""
1718. Construct the Lexicographically Largest Valid Sequence


Given an integer n, find a sequence that satisfies all of the following:

1. The integer 1 occurs once in the sequence.
2. Each integer between 2 and n occurs twice in the sequence.
2. For every integer i between 2 and n, the distance between the two occurrences of i is exactly i.

The distance between two numbers on the sequence, a[i] and a[j], is the absolute difference of their indices, |j - i|.

Return the lexicographically largest sequence. It is guaranteed that under the given constraints, there is always a solution.

A sequence a is lexicographically larger than a sequence b (of the same length) if in the first position where a and b differ, sequence a has a number greater than the corresponding number in b. 
For example, [0,1,9,0] is lexicographically larger than [0,1,5,6] because the first position they differ is at the third number, and 9 is greater than 5.

 

Example 1:

Input: n = 3
Output: [3,1,2,3,2]
Explanation: [2,3,2,1,3] is also a valid sequence, but [3,1,2,3,2] is the lexicographically largest valid sequence.
Example 2:

Input: n = 5
Output: [5,3,1,4,3,5,2,4,2]
 

Constraints:

1 <= n <= 20
"""


class ConstructDistancedSequence: 
    
    def doit_(self, n: int) -> list:

        res = [-1] * (2*n-1)
        used = [False] * (n+1)
         
        def dfs(pos):

            if pos == len(res):
                return True

            if res[pos] > 0:
                return dfs(pos+1)

            for i in reversed(range(1, n+1)):

                if used[i]: continue
                
                if i > 1 and (pos + i >= len(res) or res[pos+i] != -1):
                    continue

                used[i] = True
                res[pos] = i
                if i > 1: 
                    res[pos+i] = i 
                
                if (dfs(pos+1)):
                    return True

                res[pos] = -1
                if i > 1: 
                    res[pos+i] = -1
                used[i] = False

        dfs(0)
        return res


if __name__ == '__main__':

    ConstructDistancedSequence().doit_(1)
    
    ConstructDistancedSequence().doit_(2)
    
    ConstructDistancedSequence().doit_(3)
    
    ConstructDistancedSequence().doit_(4)
    
    ConstructDistancedSequence().doit_(5)
    
    ConstructDistancedSequence().doit_(6)


        