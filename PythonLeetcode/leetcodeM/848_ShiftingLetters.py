"""
848. Shifting Letters


We have a string S of lowercase letters, and an integer array shifts.

Call the shift of a letter, the next letter in the alphabet, (wrapping around so that 'z' becomes 'a'). 

For example, shift('a') = 'b', shift('t') = 'u', and shift('z') = 'a'.

Now for each shifts[i] = x, we want to shift the first i+1 letters of S, x times.

Return the final string after all such shifts to S are applied.

Example 1:

Input: S = "abc", shifts = [3,5,9]
Output: "rpl"
Explanation: 
We start with "abc".
After shifting the first 1 letters of S by 3, we have "dbc".
After shifting the first 2 letters of S by 5, we have "igc".
After shifting the first 3 letters of S by 9, we have "rpl", the answer.
Note:

1 <= S.length = shifts.length <= 20000
0 <= shifts[i] <= 10 ^ 9

"""


class ShiftingLetters:


    def doit_(self, S: str, shifts: list) -> str:

        MOD = ord('a') + 26
        final = [0] * (len(S) + 1)
        
        for i in range(len(shifts)-1, -1, -1):
            final[i] = final[i+1] + shifts[i]
            final[i] = final[i] % 26

        ans = ''
        for i, c in enumerate(S):
            base = (ord(c) + final[i])
            ans += chr((base % MOD + ord('a')) if base >= MOD else base)

        return ans

    """
        Approach #1: Prefix Sum [Accepted]
        Intuition

        Let's ask how many times the ith character is shifted.

        Algorithm

        The ith character is shifted shifts[i] + shifts[i+1] + ... + shifts[shifts.length - 1] times. That's because only operations at the ith operation and after, affect the ith character.

        Let X be the number of times the current ith character is shifted. Then the next character i+1 is shifted X - shifts[i] times.

        For example, if S.length = 4 and S[0] is shifted X = shifts[0] + shifts[1] + shifts[2] + shifts[3] times, then S[1] is shifted shifts[1] + shifts[2] + shifts[3] times, S[2] is shifted shifts[2] + shifts[3] times, and so on.

        In general, we need to do X -= shifts[i] to maintain the correct value of X as we increment i.

        Complexity Analysis

        Time Complexity: O(N), where NN is the length of S (and shifts).

        Space Complexity: O(N), the space needed to output the answer.
    """
    def shiftingLetters(self, S, shifts):
        ans = []
        X = sum(shifts) % 26
        for i, c in enumerate(S):
            index = ord(c) - ord('a')
            ans.append(chr(ord('a') + (index + X) % 26))
            X = (X - shifts[i]) % 26

        return "".join(ans)