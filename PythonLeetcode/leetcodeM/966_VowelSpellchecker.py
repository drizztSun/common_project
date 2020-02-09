# 966. Vowel Spellchecker

# Given a wordlist, we want to implement a spellchecker that converts a query word into a correct word.

# For a given query word, the spell checker handles two categories of spelling mistakes:

# Capitalization: If the query matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the case in the wordlist.
# Example: wordlist = ["yellow"], query = "YellOw": correct = "yellow"
# Example: wordlist = ["Yellow"], query = "yellow": correct = "Yellow"
# Example: wordlist = ["yellow"], query = "yellow": correct = "yellow"
# Vowel Errors: If after replacing the vowels ('a', 'e', 'i', 'o', 'u') of the query word with any vowel individually, it matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the match in the wordlist.
# Example: wordlist = ["YellOw"], query = "yollow": correct = "YellOw"
# Example: wordlist = ["YellOw"], query = "yeellow": correct = "" (no match)
# Example: wordlist = ["YellOw"], query = "yllw": correct = "" (no match)
# In addition, the spell checker operates under the following precedence rules:

# When the query exactly matches a word in the wordlist (case-sensitive), you should return the same word back.
# When the query matches a word up to capitlization, you should return the first such match in the wordlist.
# When the query matches a word up to vowel errors, you should return the first such match in the wordlist.
# If the query has no matches in the wordlist, you should return the empty string.
# Given some queries, return a list of words answer, where answer[i] is the correct word for query = queries[i].


# Example 1:

# Input: wordlist = ["KiTe","kite","hare","Hare"], queries = ["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
# Output: ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]


# Note:

# 1 <= wordlist.length <= 5000
# 1 <= queries.length <= 5000
# 1 <= wordlist[i].length <= 7
# 1 <= queries[i].length <= 7
# All strings in wordlist and queries consist only of english letters.


class Spellchecker:

    """
    Approach 1: HashMap
    Intuition and Algorithm

    We analyze the 3 cases that the algorithm needs to consider:
    when the query is an exact match,
    when the query is a match up to capitalization,
    and when the query is a match up to vowel errors.

    In all 3 cases, we can use a hash table to query the answer.

    For the first case (exact match), we hold a set of words to efficiently test whether our query is in the set.
    For the second case (capitalization), we hold a hash table that converts the word from its lowercase version to the original word (with correct capitalization).
    For the third case (vowel replacement), we hold a hash table that converts the word from its lowercase version with the vowels masked out, to the original word.
    The rest of the algorithm is careful planning and reading the problem carefully.

    Complexity Analysis
    Time Complexity: O(C), where C is the total content of wordlist and queries.
    Space Complexity: O(C).
    """

    def doit(self, wordlist, queries):

        def wildcast_word(word):
            return ''.join(['*' if c in 'aeiou' else c for c in word])

        words_set = set()
        words_case = {}
        words_vom = {}

        for word in wordlist:
            words_set.add(word)
            wordlowcase = word.lower()
            words_case.setdefault(wordlowcase, word)
            words_vom.setdefault(wildcast_word(wordlowcase), word)

        def query(word):

            if word in words_set:
                return word

            word = word.lower()
            if word in words_case:
                return words_case[word]

            word = wildcast_word(word)
            if word in words_vom:
                return words_vom[word]

            return ''

        return list(map(query, queries))

    def doit(self, wordlist, queries):

        dic = collections.Counter(wordlist)
        cap = collections.defaultdict(list)
        vowel = collections.defaultdict(list)

        for w in wordlist:
            cap[w.lower()].append(w)
            vowel[w.lower().replace('e', 'a').replace(
                'i', 'a').replace('o', 'a').replace('u', 'a')].append(w)

        ans = []
        for q in queries:
            ql = q.lower()
            qv = ql.replace('e', 'a').replace(
                'i', 'a').replace('o', 'a').replace('u', 'a')
            if(q in dic):
                ans.append(q)
            elif(ql in cap):
                ans.append(cap[q.lower()][0])
            elif(qv in vowel):
                ans.append(vowel[qv][0])
            else:
                ans.append("")
        return ans


if __name__ == '__main__':

    res = Spellchecker().doit(wordlist=["KiTe", "kite", "hare", "Hare"], queries=[
        "kite", "Kite", "KiTe", "Hare", "HARE", "Hear", "hear", "keti", "keet", "keto"])  # ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]

    pass
