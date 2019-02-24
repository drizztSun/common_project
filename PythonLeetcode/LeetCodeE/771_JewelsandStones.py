# 771. Jewels and Stones

# You're given strings J representing the types of stones that are jewels, and S representing the stones you have.  
# Each character in S is a type of stone you have.  You want to know how many of the stones you have are also jewels.

# The letters in J are guaranteed distinct, and all characters in J and S are letters. 
# Letters are case sensitive, so "a" is considered a different type of stone from "A".

# Example 1:

# Input: J = "aA", S = "aAAbbbb"
# Output: 3

# Example 2:

# Input: J = "z", S = "ZZ"
# Output: 0

class NumJewelsInStones:

    def doit(self, J: str, S: str) -> int:
        types = set(c for c in J)
        return sum(1 for c in S if c in types)

    def doit1(self, J: str, S: str) -> int:
        if J.isalpha() and S.isalpha and len(J) == len(set(J)):
            t = 0
            for i in J:
                for j in S:
                    if i== j:
                        t += 1
            return t
        else:
            return None

    def doit2(self, J: str, S: str) -> int:
        count = 0
        for char in J:
            for word in S:
                if char == word:
                    count += 1
        return count


    def doit3(self, J: str, S: str) -> int:

        return sum(S.count(c) for c in J)