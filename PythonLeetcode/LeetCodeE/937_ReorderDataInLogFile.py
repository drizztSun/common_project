# 937. Reorder Data in Log Files

# You have an array of logs.  Each log is a space delimited string of words.

# For each log, the first word in each log is an alphanumeric identifier.  Then, either:

# Each word after the identifier will consist only of lowercase letters, or;
# Each word after the identifier will consist only of digits.
# We will call these two varieties of logs letter-logs and digit-logs.  It is guaranteed that each log has at least one word after its identifier.

# Reorder the logs so that all of the letter-logs come before any digit-log.
# The letter-logs are ordered lexicographically ignoring identifier, with the identifier used in case of ties.  The digit-logs should be put in their original order.

# Return the final order of the logs.


# Example 1:

# Input: logs = ["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"]
# Output: ["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig2 3 6"]


# Constraints:

# 0 <= logs.length <= 100
# 3 <= logs[i].length <= 100
# logs[i] is guaranteed to have an identifier, and a word after the identifier.


class ReorderLogFiles:

    """
    Approach 1: Custom Sort
    Intuition and Algorithm

    Instead of sorting in the default order, we'll sort in a custom order we specify.

    The rules are:

    Letter-logs come before digit-logs;
    Letter-logs are sorted alphanumerically, by content then identifier;
    Digit-logs remain in the same order.
    It is straightforward to translate these ideas into code.

    Complexity Analysis

    Time Complexity: O(AlogA), where A is the total content of logs.

    Space Complexity: O(A).
    O(\mathcal{A}\log \mathcal{A})O(AlogA),
    """

    def doit(self, logs):

        def f(log):
            id_, rest = log.split(' ', 1)
            return (0, rest, id_) if rest[0].isalpha() else (1,)

        return sorted(logs, key=f)

    def doit(self, logs):

        digits = []
        letters = []

        for i, st in enumerate(logs):
            word = st.split()
            if word[1][0].isalpha():
                letters.append((' '.join(word[1:]), word[0], st))
            else:
                digits.append(st)

        letters.sort(key=lambda x: (x[0], x[1]))

        return [c[2] for c in letters] + digits


if __name__ == '__main__':

    # ["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig2 3 6"]
    res = ReorderLogFiles().doit(
        logs=["dig1 8 1 5 1", "let1 art can", "dig2 3 6", "let2 own kit dig", "let3 art zero"])

    pass
