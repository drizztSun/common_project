# 953. Verifying an Alien Dictionary


class IsAlienSorted:

    def doit(self, words, order):

        order_map = {c: i for i, c in enumerate(order)}

        def word_order(w1, w2):
            i = 0
            while i < len(w1) and i < len(w2):
                if order_map[w1[i]] > order_map[w2[i]]:
                    return False
                elif order_map[w1[i]] < order_map[w2[i]]:
                    return True
                i += 1

            return len(w1) < len(w2)

        for i in range(len(words) - 1):
            if not word_order(words[i], words[i+1]):
                return False
        return True

    """
    Approach 1: Check Adjacent Words

    Intuition
    The words are sorted lexicographically if and only if adjacent words are.
    This is because order is transitive: a <= b and b <= c implies a <= c.

    Algorithm

    Let's check whether all adjacent words a and b have a <= b.
    To check whether a <= b for two adjacent words a and b, we can find their first difference.
    For example, "applying" and "apples" have a first difference of y vs e.
    After, we compare these characters to the index in order.

    Care must be taken to deal with the blank character effectively.
    If for example, we are comparing "app" to "apply", this is a first difference of (null) vs "l".
    """

    def doit(self, words, order):
        order_index = {c: i for i, c in enumerate(order)}

        for i in xrange(len(words) - 1):
            word1 = words[i]
            word2 = words[i+1]

            # Find the first difference word1[k] != word2[k].
            for k in xrange(min(len(word1), len(word2))):
                # If they compare badly, it's not sorted.
                if word1[k] != word2[k]:
                    if order_index[word1[k]] > order_index[word2[k]]:
                        return False
                    break
            else:
                # If we didn't find a first difference, the
                # words are like ("app", "apple").
                if len(word1) > len(word2):
                    return False

        return True


if __name__ == '__main__':

    res = IsAlienSorted().doit(
        words=["hello", "leetcode"], order="hlabcdefgijkmnopqrstuvwxyz")  # true

    res = IsAlienSorted().doit(
        words=["word", "world", "row"], order="worldabcefghijkmnpqstuvxyz")  # false

    res = IsAlienSorted().doit(
        words=["apple", "app"], order="abcdefghijklmnopqrstuvwxyz")  # false

    pass
