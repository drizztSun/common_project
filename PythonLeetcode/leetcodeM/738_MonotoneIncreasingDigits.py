"""
738. Monotone Increasing Digits

Given a non-negative integer N, find the largest number that is less than or equal to N with monotone increasing digits.

(Recall that an integer has monotone increasing digits if and only if each pair of adjacent digits x and y satisfy x <= y.)

Example 1:
Input: N = 10
Output: 9
Example 2:
Input: N = 1234
Output: 1234
Example 3:
Input: N = 332
Output: 299
Note: N is an integer in the range [0, 10^9].
"""


class MonotoneIncreasingDigits:

    """
    Approach #1: Greedy [Accepted]
    Intuition

    Let's construct the answer digit by digit.

    If the current answer is say, 123, and the next digit is 5, then the answer must be at least 123555...5,
    since the digits in the answer must be monotonically increasing. If this is larger than N, then it's impossible.

    Algorithm

    For each digit of N, let's build the next digit of our answer ans. We'll find the smallest possible digit d such that ans + (d repeating) > N
    when comparing by string; that means d-1 must have satisfied ans + (d-1 repeating) <= N, and so we'll add d-1 to our answer. If we don't find such a digit, we can add a 9 instead.

    Complexity Analysis

    Time Complexity: O(D^2), where D \approx \log ND≈logN is the number of digits in NN. We do O(D)O(D) work building and comparing each candidate, and we do this O(D)O(D) times.
    Space Complexity: O(D), the size of the answer and the temporary string we are comparing.
    """
    def doit_greedy(self, N: int) -> int:
        digits = []
        A = map(int, str(N))
        for i in range(len(A)):
            for d in range(1, 10):
                if digits + [d] * (len(A)-i) > A:
                    digits.append(d-1)
                    break
            else:
                digits.append(9)

        return int("".join(map(str, digits)))

    """
    Approach #2: Truncate After Cliff [Accepted]
    Intuition
    
    One initial thought that comes to mind is we can always have a candidate answer of d999...9 (a digit 0 <= d <= 9 
    followed by some number of nines.) For example if N = 432543654, we could always have an answer of at least 399999999.
    
    We can do better. For example, when the number is 123454321, we could have a candidate of 123449999. 
    It seems like a decent strategy is to take a monotone increasing prefix of N, then decrease the number before the "cliff" 
    (the index where adjacent digits decrease for the first time) if it exists, and replace the rest of the characters with 9s.
    
    When does that strategy fail? If N = 333222, then our strategy would give us the candidate answer of 332999 - but this isn't monotone increasing. 
    However, since we are looking at all indexes before the original first occurrence of a cliff, the only place 
    where a cliff could exist, is next to where we just decremented a digit.
    
    Thus, we can repair our strategy, by successfully morphing our answer 332999 -> 329999 -> 299999 with a linear scan.
    
    Algorithm
    
    We'll find the first cliff S[i-1] > S[i]. Then, while the cliff exists, we'll decrement the appropriate digit and move i back. 
    Finally, we'll make the rest of the digits 9s and return our work.
    
    We can prove our algorithm is correct because every time we encounter a cliff, the digit we decrement has to decrease by at least 1. 
    Then, the largest possible selection for the rest of the digits is all nines, which is always going to be monotone 
    increasing with respect to the other digits occurring earlier in the number.
    
    Complexity Analysis

    Time Complexity: O(D), where D \approx \log ND≈logN is the number of digits in NN. Each step in the algorithm is a linear scan of the digits.
    Space Complexity: O(D), the size of the answer.
    """
    def doit_truncate_after_cliff(self, N):
        S = list(str(N))
        i = 1
        while i < len(S) and S[i-1] <= S[i]:
            i += 1
        while 0 < i < len(S) and S[i-1] > S[i]:
            S[i-1] = str(int(S[i-1]) - 1)
            i -= 1
        S[i+1:] = '9' * (len(S) - i-1)
        return int("".join(S))