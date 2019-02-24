# 784. Letter Case Permutation

# Given a string S, we can transform every letter individually to be lowercase or uppercase to create another string.  
# Return a list of all possible strings we could create.

# Examples:
# Input: S = "a1b2"
# Output: ["a1b2", "a1B2", "A1b2", "A1B2"]

# Input: S = "3z4"
# Output: ["3z4", "3Z4"]

# Input: S = "12345"
# Output: ["12345"]
# Note:

# S will be a string with length between 1 and 12.
# S will consist only of letters or digits.

class LetterCasePermutation:
    def doit(self, S: str) -> List[str]:
        
        def build(S, i):
            
            if i == len(S):
                return [""]

            res = []
            for c in build(S, i+1):
                
                if S[i].isalpha():
                    for s in (S[i].lower(), S[i].upper()):
                        res.append(s + c)
                else:
                    res.append(S[i] + c)
            
            return res
        
        return build(S, 0)
