

# 433. Minimum Genetic Mutation

# A gene string can be represented by an 8-character long string, with choices from "A", "C", "G", "T".

# Suppose we need to investigate about a mutation (mutation from "start" to "end"), where ONE mutation is defined as ONE single character changed in the gene string.

# For example, "AACCGGTT" -> "AACCGGTA" is 1 mutation.

# Also, there is a given gene "bank", which records all the valid gene mutations. A gene must be in the bank to make it a valid gene string.

# Now, given 3 things - start, end, bank, your task is to determine what is the minimum number of mutations needed to mutate from "start" to "end".
# If there is no such a mutation, return -1.

# Note:

# Starting point is assumed to be valid, so it might not be included in the bank.
# If multiple mutations are needed, all mutations during in the sequence must be valid.
# You may assume start and end string is not the same.
# Example 1:

# start: "AACCGGTT"
# end:   "AACCGGTA"
# bank: ["AACCGGTA"]

# return: 1

# Example 2:

# start: "AACCGGTT"
# end:   "AAACGGTA"
# bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]

# return: 2

# Example 3:

# start: "AAAAACCC"
# end:   "AACCCCCC"
# bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]

# return: 3


import collections
class minMutation(object):


    def doit(self, start, end, bank):
        """
        :type start: str
        :type end: str
        :type bank: List[str]
        :rtype: int
        """
        def mutation(current, next):
            if len(current) != len(next):
                return False
            mutation = False
            for i in range(len(current)):
                if current[i] != next[i]:
                    if mutation == True:
                        return False
                    mutation = True

            return mutation


        #########
        queue = collections.deque()
        while queue:
            current, prev, step = queue.popleft()
    
            if current == end:
                return step
        
            for c in bank:
                if mutation(c, current) and c != prev:
                    queue.append([c, current, step+1])

        return -1




    def doit(self, start, end, bank):
        """
        :type start: str
        :type end: str
        :type bank: List[str]
        :rtype: int
        """
        def viableMutation(current_mutation, next_mutation):
            changes = 0
            for i in range(len(current_mutation)):
                if current_mutation[i] != next_mutation[i]:
                    changes += 1
            return changes == 1

        queue = collections.deque()
        queue.append([start, start, 0]) # current, previous, num_steps

        while queue:
            current, previous, num_steps = queue.popleft()
            if current == end:  # in BFS, the first instance of current == end will yield the minimum
                return num_steps
            for string in bank:
                if viableMutation(current, string) and string != previous:
                    queue.append([string, current, num_steps+1])

        return -1



    def doit1(self, start, end, bank):
        """
        :type start: str
        :type end: str
        :type bank: List[str]
        :rtype: int
        """
        def mutation(s, e):
            if len(s) != len(e):
                return False

            ismutation = False
            for i in range(len(s)):
                if s[i] != e[i]:
                    if ismutation:
                        return False
                    ismutation = True

            return ismutation


        maxstep = len(bank)
        sSteps, eSteps = 0, 0
        sGroup, eGroup = [start], [end]
        sBank, eBank = set(), set()

        for i, c in enumerate(bank):
            if start == c:
               sBank.add(i)

            if end == c:
               eBank.add(i)

        if not eBank:
            return -1

        for _ in range(maxstep):

            stmp = set()
            for s in sGroup:
                for i, a in enumerate(bank):
                    if i not in sBank and mutation(s, a):
                        stmp.add(a)
                        sBank.add(i)

            etmp = set()
            for e in eGroup:
                for i, a in enumerate(bank):
                    if i not in eBank and mutation(e, a):
                        etmp.add(a)
                        eBank.add(i)

            for c in eGroup:
                if c in stmp:
                    return sSteps + eSteps + 1

            for c in sGroup:
                if c in etmp:
                    return sSteps + eSteps + 1

            for c in stmp:
                if c in etmp:
                    return sSteps + eSteps + 2

            sSteps += 1
            eSteps += 1
            
            sGroup, eGroup = list(stmp), list(etmp)

            if not sGroup or not eGroup:
                break
            
        return -1
            


if __name__=="__main__":


    res = minMutation().doit("AACCGGTT", "AACCGGTA", ["AACCGGTA"])

    
    res = minMutation().doit("AACCGGTT", "AAACGGTA", ["AACCGGTA", "AACCGCTA", "AAACGGTA"])


    res = minMutation().doit("AAAAACCC", "AACCCCCC", ["AAAACCCC", "AAACCCCC", "AACCCCCC"])


    res = minMutation().doit1("AAAAAAAA", "CCCCCCCC", ["AAAAAAAA","AAAAAAAC","AAAAAACC","AAAAACCC","AAAACCCC","AACACCCC","ACCACCCC","ACCCCCCC","CCCCCCCA"])

    pass