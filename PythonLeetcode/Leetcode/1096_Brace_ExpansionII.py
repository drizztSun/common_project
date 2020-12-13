"""

1096. Brace Expansion II


Under a grammar given below, strings can represent a set of lowercase words.  Let's use R(expr) to denote the set of words the expression represents.

Grammar can best be understood through simple examples:

Single letters represent a singleton set containing that word.
R("a") = {"a"}
R("w") = {"w"}
When we take a comma delimited list of 2 or more expressions, we take the union of possibilities.
R("{a,b,c}") = {"a","b","c"}
R("{{a,b},{b,c}}") = {"a","b","c"} (notice the final set only contains each word at most once)
When we concatenate two expressions, we take the set of possible concatenations between two words where the first word comes from the first expression
and the second word comes from the second expression.

R("{a,b}{c,d}") = {"ac","ad","bc","bd"}
R("a{b,c}{d,e}f{g,h}") = {"abdfg", "abdfh", "abefg", "abefh", "acdfg", "acdfh", "acefg", "acefh"}
Formally, the 3 rules for our grammar:

For every lowercase letter x, we have R(x) = {x}
For expressions e_1, e_2, ... , e_k with k >= 2, we have R({e_1,e_2,...}) = R(e_1) ∪ R(e_2) ∪ ...
For expressions e_1 and e_2, we have R(e_1 + e_2) = {a + b for (a, b) in R(e_1) × R(e_2)}, where + denotes concatenation, and × denotes the cartesian product.
Given an expression representing a set of words under the given grammar, return the sorted list of words that the expression represents.



Example 1:

Input: "{a,b}{c,{d,e}}"
Output: ["ac","ad","ae","bc","bd","be"]
Example 2:

Input: "{{a,z},a{b,c},{ab,z}}"
Output: ["a","ab","ac","z"]
Explanation: Each distinct word is written only once in the final answer.



"""


class BraceExpansionII:

    def doit_(self, expression: str) -> list:

        def get_next(i):
            if i >= len(expression):
                return None, i
            if not expression[i].isalpha():
                return expression[i], i + 1
            j = i + 1
            while j < len(expression) and expression[j].isalpha():
                j += 1
            return expression[i:j], j

        def eval_words(i):
            words_all = []
            words_all_set = set()
            words_cur = []
            while i < len(expression):
                # print(i)
                token, i = get_next(i)
                if token is None:
                    return words, i
                elif token == ',':
                    words_cur = [w for w in words_cur if w not in words_all_set]
                    words_all.extend(words_cur)
                    words_all_set |= set(words_cur)
                    words_cur = []
                elif token == '{':
                    sub_words, i = eval_words(i)
                    if not words_cur:
                        words_cur.extend(sub_words)
                    else:
                        words_cur = product(words_cur, sub_words)
                        words_cur = [''.join(w) for w in words_cur]
                elif token == '}':
                    words_cur = [w for w in words_cur if w not in words_all_set]
                    words_all.extend(words_cur)
                    return words_all, i
                else:
                    if not words_cur:
                        words_cur.append(token)
                    else:
                        words_cur = product(words_cur, [token])
                        words_cur = [''.join(w) for w in words_cur]
                # print(words_all)
            if words_cur:
                words_cur = [w for w in words_cur if w not in words_all_set]
                words_all.extend(words_cur)
            return words_all, i

        words, _ = eval_words(0)
        # words = list(set(words))
        return sorted(words)






