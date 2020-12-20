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
When we concatenate two expressions, we take the set of possible concatenations between two words where the first word
comes from the first expression and the second word comes from the second expression.
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


Constraints:

1 <= expression.length <= 60
expression[i] consists of '{', '}', ','or lowercase English letters.
The given expression represents a set of words based on the grammar given in the description.



"""
union = lambda a, b: a | b
prod = lambda a, b: {x + y for x in a for y in b}


class BraceExpansionII:

    def doit_(self, expression: str) -> list:

        from itertools import product

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

            if words_cur:
                words_cur = [w for w in words_cur if w not in words_all_set]
                words_all.extend(words_cur)
            return words_all, i

        words, _ = eval_words(0)
        return sorted(words)

    def readStr(self, expr: str, i: int):
        s = ''
        while i < len(expr) and expr[i].isalpha():
            s += expr[i]
            i += 1
        return s, i - 1

    def eval(self, args, op) -> None:
        f, xs = op.pop(), args.pop()
        if len(xs) == 1:
            res = xs[0]
        else:
            res = reduce(f, xs)
        args[-1].append(res)

    def braceExpansionII(self, expr: str):
        args, op = [[], []], [prod]
        i, n = 0, len(expr)
        while i < n:
            c = expr[i]
            if c.isalpha():
                s, i = self.readStr(expr, i)
                args[-1].append({s})
            elif c == '{':
                args += [[], []]
                op += [union, prod]
            elif c == ',':
                self.eval(args, op)
                args.append([])
                op.append(prod)
            elif c in '}':
                self.eval(args, op)
                self.eval(args, op)
            i += 1
        self.eval(args, op)
        return sorted(args.pop()[0])

    def doit_(self, expression: str) -> list:

        from itertools import product

        def gen_next(i):
            if i == len(expression):
                return None, i
            elif not expression[i].isalpha():
                return expression[i], i + 1
            else:
                j = i
                while i < len(expression) and expression[i].isalpha():
                    i += 1
                return expression[j:i], i

        def search(i):
            allwordsSet, allwords, cur = set(), [], []

            while i < len(expression):

                token, i = gen_next(i)

                if token == None:
                    return allwords, i

                elif token == '{':

                    subwords, i = search(i)
                    if not cur:
                        cur.extend(subwords)
                    else:
                        cur = product(cur, subwords)
                        cur = [''.join(w) for w in cur]

                elif token == '}':
                    cur = [w for w in cur if w not in allwordsSet]
                    allwords.extend(cur)
                    return allwords, i

                elif token == ',':
                    cur = [w for w in cur if w not in allwordsSet]
                    allwords.extend(cur)
                    allwordsSet |= set(cur)
                    cur = []
                else:
                    if not cur:
                        cur.append(token)
                    else:
                        cur = product(cur, [token])
                        cur = [''.join(w) for w in cur]

            if cur:
                cur = [w for w in cur if w not in allwordsSet]
                allwords.extend(cur)

            return allwords, i

        words, _ = search(0)
        return sorted(words)


if __name__ == '__main__':

    BraceExpansionII().doit_("{a,b}{c,{d,e}}")

    BraceExpansionII().doit_("{{a,z},a{b,c},{ab,z}}")
