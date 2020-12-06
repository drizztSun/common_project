"""
1307. Verbal Arithmetic Puzzle

Given an equation, represented by words on left side and the result on right side.

You need to check if the equation is solvable under the following rules:

Each character is decoded as one digit (0 - 9).
Every pair of different characters they must map to different digits.
Each words[i] and result are decoded as one number without leading zeros.
Sum of numbers on left side (words) will equal to the number on right side (result).
Return True if the equation is solvable otherwise return False.



Example 1:

Input: words = ["SEND","MORE"], result = "MONEY"
Output: true
Explanation: Map 'S'-> 9, 'E'->5, 'N'->6, 'D'->7, 'M'->1, 'O'->0, 'R'->8, 'Y'->'2'
Such that: "SEND" + "MORE" = "MONEY" ,  9567 + 1085 = 10652
Example 2:

Input: words = ["SIX","SEVEN","SEVEN"], result = "TWENTY"
Output: true
Explanation: Map 'S'-> 6, 'I'->5, 'X'->0, 'E'->8, 'V'->7, 'N'->2, 'T'->1, 'W'->'3', 'Y'->4
Such that: "SIX" + "SEVEN" + "SEVEN" = "TWENTY" ,  650 + 68782 + 68782 = 138214
Example 3:

Input: words = ["THIS","IS","TOO"], result = "FUNNY"
Output: true
Example 4:

Input: words = ["LEET","CODE"], result = "POINT"
Output: false


Constraints:

2 <= words.length <= 5
1 <= words[i].length, result.length <= 7
words[i], result contains only upper case English letters.
Number of different characters used on the expression is at most 10.



"""


class VerbalArithmeticPuzzle:

    """
    Approach:

    Treat the puzzle like an equation left = sum(words) and right = result.
    The goal is to have left = right after assigning a number to each letter.
    This means left - right equals zero.
    So instead of keeping track of left and right separately, just keep track of total = left - right.

    i.e. ["SEND", "MORE"] = "MONEY"
         Say we assign 5 to the letter "E".
         total = 500 + 5 - 50
         because "E" is in the second position on the right (-50)
         and "E" is in the first and third position on the left (5 + 500)

         {'S': 9, 'E': 5, 'N': 6, 'D': 7, 'M': 1, 'O': 0, 'R': 8, 'Y': '2'} is a solution because total = 0

           S      E    N    D      M     O   R    E       M     O    N    E    Y
         (9000 + 500 + 60 + 7) + (1000 + 0 + 80 + 5) - (10000 + 0 + 600 + 50 + 2) = 0
    Start with numbers 0 - 9 that you can assign to any of the characters.
    Iterate over the characters and assign a number to each character, update the total and remove the used number from available numbers.
    Once a number has been assigned to all of the characters, if the total is zero a solution has been found.

    Optimizations: (click to show)
    Optimizations:

    Early Stopping is the biggest optimization so let's start there. The goal is to make the sum of the words on the left side of the equation equal the result word on the right side of the equation. In the example ["SEND", "MORE"] = "MONEY", this means that "D" + "E" - "Y" must have a zero in the ones place, because "D", "E", and "Y" are the only letters that affect the ones place.

    Use a checkpoint list to make sure that the (ones / tens / hundreds / ...) digit of total is zero after a number has been assigned to all of the characters that affect the digit.
    Here is what the checkpoint list looks like:
                       0    1    2    3    4    5    6    7
        characters = ['D', 'Y', 'E', 'N', 'R', 'O', 'M', 'S']
        checkpoint = {2: [0], 4: [1], 5: [2], 7: [3, 4]}
        This means at index 2 numbers have been assigned to 'D', 'Y', 'E' ~ all the characters that affect the 0th digit place.
                at index 4 numbers have been assigned to 'D', 'Y', 'E', 'N', 'R' ~ all the characters that affect the 1st digit place.
                at index 5 numbers have been assigned to 'D', 'Y', 'E', 'N', 'R', 'O' ~ all the characters that affect the 2nd digit place.
                at index 7 numbers have been assigned to 'D', 'Y', 'E', 'N', 'R', 'O', 'M', 'S' ~ all the characters that affect the 3rd and 4th digit places.

        After index 2, if 'D'+'Y'+'E' = -10, 0, 10, 20, ... then all is good because the 0th digit place is 0
        but if 'D'+'Y'+'E' = 11, 17, 5, 3, ... then stop because a wrong number was assigned to 'D', 'Y', or 'E'
    Sort the characters according to their digit place: ['D', 'Y', 'E', 'N', 'R', 'O', 'M', 'S'] notice 'D', 'Y', 'E' come first because they are in the 0th digit place.
    Remove 0 weight characters. If a character has the same weight on the left and right side of the equation, remove it from characters, it can be any number.
        i.e. ["MODE", "IDOL"] = "DOOM"
             "O" is in the 1st and 2nd digit in both the left and right side of the equation
             left_weight = 10 + 100 = right_weight so it is free to be any character
    Check the lengths of the words and the length of the result. i.e. ["AB", "CD"] = "EFGHI" must be False because no two 2 digit numbers sum to a 5 digit number.
    Same is true for ["ABCD", "CD"] = "EFG".
    Check if result is in words. Lastly if result is in the words list then the result is only True if words = [result] or words = [result, one_letter_word]


    """

    def doit_(self, words: list, result: str) -> bool:
        import functools
        import collections

        @functools.lru_cache(None)
        def helper(i, total, nums):

            if i == len(chars):
                return total == 0

            if i - 1 in checkpoints:
                t = str(abs(total))[::-1]
                for j in checkpoints[i - 1]:
                    if (j < len(t)) and (t[j] != '0'):
                        return False

            for j in range(len(nums)):
                if (nums[j] == 0) and (chars[i] not in not_zero) and helper(i + 1, total, nums[:j] + nums[j + 1:]):
                    return True
                elif (nums[j] != 0) and helper(i + 1, total + nums[j] * mult[chars[i]], nums[:j] + nums[j + 1:]):
                    return True

            return False

        # 1. Check the lengths of each word and result
        longest_word = len(max(words, key=len))
        if (len(result) < longest_word) or (len(result) > longest_word + 1):
            return False

        # 2. Check if result is in words
        if result in words:
            return len(words) < 3 and all(word == result or len(word) == 1 for word in words)

        # 3. Leading letters cannot be zero unless the length of the word is 1
        not_zero = set((word[0] for word in words if len(word) > 1))
        if len(result) > 1: not_zero.add(result[0])

        # 4. Set of all letters
        chars = set(result + ''.join(words))

        # 5. Letters in words add to the total
        mult = {char: 0 for char in chars}
        groups = collections.defaultdict(set)
        for word in words:
            for i, char in enumerate(reversed(word)):
                mult[char] += 10 ** i
                groups[i].add(char)

        # 6. And letters in result subtract from the total
        for i, char in enumerate(reversed(result)):
            mult[char] -= 10 ** i
            groups[i].add(char)

        # 7. Letters that add and subtract the same amount can be any number, so ignore them.
        chars = {char for char in chars if mult[char]}
        for g in groups:
            groups[g] = groups[g].intersection(chars)
        chars = list(chars)

        # 8. All letters that occur later in the word may affect letters ealrier in the word
        for g in range(1, len(groups)):
            groups[g] |= groups[g - 1]
        chars.sort(key=lambda c: min(g for g in range(len(groups)) if c in groups[g]))

        # 9. Once a number has been assigned to all the letters in a group
        #    the digit in total at position 10**i must be zero for a solution to exist
        checkpoints = collections.defaultdict(list)
        seen = set()
        checked = set()
        for i, char in enumerate(chars):
            seen.add(char)
            for g in groups:
                if (g not in checked) and groups[g].issubset(seen):
                    checked.add(g)
                    checkpoints[i].append(g)

        return helper(0, 0, tuple(range(10)))
