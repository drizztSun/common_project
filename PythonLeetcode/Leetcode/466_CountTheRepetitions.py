


# 466. Count The Repetitions

# Define S = [s,n] as the string S which consists of n connected strings s.
# For example, ["abc", 3] ="abcabcabc".

# On the other hand, we define that string s1 can be obtained from string s2
# if we can remove some characters from s2 such that it becomes s1. 

# For example,
# 'abc' can be obtained from 'abdbec' based on our definition, but it can not be obtained from 'acbbe'

# You are given two non-empty strings s1 and s2 (each at most 100 characters long) and 
# two integers 0  < n1 < 106 and 1 < n2 < 106.
# Now consider the strings S1 and S2, where S1=[s1,n1] and S2=[s2,n2].
# Find the maximum integer M such that [S2,M] can be obtained from S1.

# Example:

# Input:
# s1="acb", n1=4
# s2="ab", n2=2

# Return:
# 2


class GetMaxRepetitions:
    def doit(self, s1, n1, s2, n2):
        """
        :type s1: str
        :type n1: int
        :type s2: str
        :type n2: int
        :rtype: int
        """
        start = {}
        s1_round, s2_round, s2_index = 0, 0, 0

        while s1_round < n1:

            s1_round += 1
            for c in s1:
                if c == s2[s2_index]:
                    s2_index += 1

                    if s2_index == len(s2):
                        s2_round += 1
                        s2_index = 0

            if s2_index in start:
                prev_s1_round, prev_s2_round = start[s2_index]
                circle_s1_round, circle_s2_round = s1_round - prev_s1_round, s2_round - prev_s2_round
                
                res = (n1 - s1_round) / circle_s1_round * circle_s2_round

                left_s1_round = (n1 - s1_round) % circle_s1_round + prev_s1_round
        
                for key, val in start.items():
                    if val[0] == left_s1_round:
                        res += val[1]
                        break
                return res / n2
            else:
                start[s2_index] = (s1_round, s2_round)

        return s2_round / n2

if __name__=="__main__":
    
    obj = GetMaxRepetitions()

    res = obj.doit("acb", 4, "ab", 2)


    pass