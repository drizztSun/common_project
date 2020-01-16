# 870. Advantage Shuffle

# Given two arrays A and B of equal size, the advantage of A with respect to B is the number of indices i for which A[i] > B[i].

# Return any permutation of A that maximizes its advantage with respect to B.

# Example 1:

# Input: A = [2,7,11,15], B = [1,10,4,11]
# Output: [2,11,7,15]

# Example 2:

# Input: A = [12,24,8,32], B = [13,25,32,11]
# Output: [24,32,8,12]


# Note:

# 1 <= A.length = B.length <= 10000
# 0 <= A[i] <= 10^9
# 0 <= B[i] <= 10^9

class AdvantageCount:
    def doit(self, A, B):
        """
        Approach 1: Greedy
        Intuition

        If the smallest card a in A beats the smallest card b in B, we should pair them. Otherwise, a is useless for our score, as it can't beat any cards.

        Why should we pair a and b if a > b? Because every card in A is larger than b, any card we place in front of b will score a point.
        We might as well use the weakest card to pair with b as it makes the rest of the cards in A strictly larger, and thus have more potential to score points.

        Algorithm

        We can use the above intuition to create a greedy approach. The current smallest card to beat in B will always be b = sortedB[j].
        For each card a in sortedA, we will either have a beat that card b (put a into assigned[b]), or throw a out (put a into remaining).

        Afterwards, we can use our annotations assigned and remaining to reconstruct the answer. Please see the comments for more details.
        """
        sortedA, sortedB = sorted(A), sorted(B)
        B_pos = {b: [] for b in B}
        remaining = []
        j = 0

        for a in sortedA:
            if a > sortedB[j]:
                B_pos[sortedB[j]].append(a)
                j += 1
            else:
                remaining.append(a)

        return [B_pos[b].pop() if B_pos[b] else remaining.pop() for b in B]

    def doit(self, A, B):

        if not A:
            return []

        results = [0]*len(A)

        A.sort()
        B = sorted([(number, i) for i, number in enumerate(B)])

        start = 0
        end = len(B) - 1
        for number in A:
            if number > B[start][0]:
                results[B[start][1]] = number
                start += 1
            else:
                results[B[end][1]] = number
                end -= 1
        return results


if __name__ == '__main__':

    res = AdvantageCount().doit(A=[2, 7, 11, 15], B=[
        1, 10, 4, 11])  # [2,11,7,15]

    res = AdvantageCount().doit(A=[12, 24, 8, 32], B=[
        13, 25, 32, 11])  # [24,32,8,12]

    pass
