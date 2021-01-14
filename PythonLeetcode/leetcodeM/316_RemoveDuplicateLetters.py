"""
316. Remove Duplicate Letters

Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Note: This question is the same as 1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/

 

Example 1:

Input: s = "bcabc"
Output: "abc"
Example 2:

Input: s = "cbacdcbc"
Output: "acdb"

"bcdbcda" 
"bcda"

Constraints:

1 <= s.length <= 10^4
s consists of lowercase English letters.


Intuition
First we should make sure we understand what "lexicographical order" means. Comparing strings doesn't work the same way as comparing numbers. Strings are compared from the first character to the last one. Which string is greater depends on the comparison between the first unequal corresponding character in the two strings. As a result any string beginning with a will always be less than any string beginning with b, regardless of the ends of both strings.

Because of this, the optimal solution will have the smallest characters as early as possible. We draw two conclusions that provide different methods of solving this problem in O(N)O(N):

The leftmost letter in our solution will be the smallest letter such that the suffix from that letter contains every other. This is because we know that the solution must have one copy of every letter, and we know that the solution will have the lexicographically smallest leftmost character possible.

If there are multiple smallest letters, then we pick the leftmost one simply because it gives us more options. We can always eliminate more letters later on, so the optimal solution will always remain in our search space.

As we iterate over our string, if character i is greater than character i+1 and another occurrence of character i exists later in the string, deleting character i will always lead to the optimal solution. Characters that come later in the string i don't matter in this calculation because i is in a more significant spot. Even if character i+1 isn't the best yet, we can always replace it for a smaller character down the line if possible.

Since we try to remove characters as early as possible, and picking the best letter at each step leads to the best solution, "greedy" should be going off like an alarm

"""

class RemoveDuplicateLetters:

    """
        Approach 1: Greedy - Solving Letter by Letter
        Algorithm

        We use idea number one from the intuition. In each iteration, we determine leftmost letter in our solution. 
        This will be the smallest character such that its suffix contains at least one copy of every character in the string. 
        We determine the rest our answer by recursively calling the function on the suffix we generate from the original string (leftmost letter is removed).

        Implementation

        Note that the code in this section is a translated / commented version of the code in this post originally written by lixx2100.

        Complexity Analysis

        Time complexity : O(N). Each recursive call will take O(N). The number of recursive calls is bounded by a constant (26 letters in the alphabet), so we have O(N) * C = O(N)O(N)∗C=O(N).

        Space complexity : O(N). Each time we slice the string we're creating a new one (strings are immutable). The number of slices is bound by a constant, so we have O(N) * C = O(N)O(N)∗C=O(N).

    """
    def doit_(self, s: str) -> str:
        from collections import Counter

        def search(s):
            # find pos - the index of the leftmost letter in our solution
            # we create a counter and end the iteration once the suffix doesn't have each unique character
            # pos will be the index of the smallest character we encounter before the iteration ends
            c = Counter(s)
            pos = 0
            for i in range(len(s)):
                if s[i] < s[pos]: pos = i
                c[s[i]] -=1
                if c[s[i]] == 0: break
            # our answer is the leftmost letter plus the recursive call on the remainder of the string
            # note we have to get rid of further occurrences of s[pos] to ensure that there are no duplicates
            return s[pos] + search(s[pos:].replace(s[pos], "")) if s else ''
        
        return search(s)

    """
        Approach 2: Greedy - Solving with Stack
        Algorithm

        We use idea number two from the intuition. We will keep a stack to store the solution we have built as we iterate over the string, 
        and we will delete characters off the stack whenever it is possible and it makes our string smaller.

        Each iteration we add the current character to the solution if it hasn't already been used. We try to remove as many characters as possible off the top of the stack, 
        and then add the current character

        The conditions for deletion are:

        The character is greater than the current characters
        The character can be removed because it occurs later on
        At each stage in our iteration through the string, we greedily keep what's on the stack as small as possible.

        The following animation makes this more clear:

        Current
        1 / 12
        Implementation


        Complexity Analysis

        Time complexity : O(N). Although there is a loop inside a loop, the time complexity is still O(N)O(N). 
        This is because the inner while loop is bounded by the total number of elements added to the stack (each time it fires an element goes). 
        This means that the total amount of time spent in the inner loop is bounded by O(N)O(N), giving us a total time complexity of O(N)O(N)

        Space complexity : O(1). At first glance it looks like this is O(N)O(N), but that is not true! seen will only contain unique elements, 
        so it's bounded by the number of characters in the alphabet (a constant). You can only add to stack if an element has not been seen, 
        so stack also only consists of unique elements. This means that both stack and seen are bounded by constant, giving us O(1)O(1) space complexity.
    """
    def doit_stack(self, s) -> int:

        stack = []

        # this lets us keep track of what's in our solution in O(1) time
        seen = set()

        # this will let us know if there are no more instances of s[i] left in s
        last_occurrence = {c: i for i, c in enumerate(s)}


        for i, c in enumerate(s):

            # we can only try to add c if it's not already in our solution
            # this is to maintain only one of each character
            if c not in seen:
                # if the last letter in our solution:
                #    1. exists
                #    2. is greater than c so removing it will make the string smaller
                #    3. it's not the last occurrence
                # we remove it from the solution to keep the solution optimal
                while stack and c < stack[-1] and i < last_occurrence[stack[-1]]:
                    seen.discard(stack.pop())
                seen.add(c)
                stack.append(c)
                
        return ''.join(stack)
