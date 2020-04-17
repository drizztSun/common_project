# 917. Reverse Only Letters

# Given a string S, return the "reversed" string where all characters that are not a letter stay in the same place,
# and all letters reverse their positions.


# Example 1:

# Input: "ab-cd"
# Output: "dc-ba"

# Example 2:

# Input: "a-bC-dEf-ghIj"
# Output: "j-Ih-gfE-dCba"

# Example 3:

# Input: "Test1ng-Leet=code-Q!"
# Output: "Qedo1ct-eeLg=ntse-T!"


class ReverseOnlyLetters:
    def doit(self, S):
        ans = [s for s in S]
        lo, hi = 0, len(ans)-1

        while lo < hi:
            if not ans[lo].isalpha():
                lo += 1
                continue
            elif not ans[hi].isalpha():
                hi -= 1
                continue
            else:
                ans[lo], ans[hi] = ans[hi], ans[lo]
                lo += 1
                hi -= 1

        return ''.join(ans)
