# The functools module is for higher-order functions: functions that act on or return other functions.
# In general, any callable object can be treated as a function for the purposes of this module.

# The functools module defines the following functions:

import urllib
import functools

# functools.lru_cache


class LRU_CACHE:

    """
    @functools.lru_cache(user_function)
    @functools.lru_cache(maxsize=128, typed=False)
    Decorator to wrap a function with a memoizing callable that saves up to the maxsize most recent calls.
    It can save time when an expensive or I/O bound function is periodically called with the same arguments.

    Since a dictionary is used to cache results, the positional and keyword arguments to the function must be hashable.

    Distinct argument patterns may be considered to be distinct calls with separate cache entries.
    For example, f(a=1, b=2) and f(b=2, a=1) differ in their keyword argument order and may have two separate cache entries.

    If user_function is specified, it must be a callable.
    This allows the lru_cache decorator to be applied directly to a user function,
    leaving the maxsize at its default value of 128:

    @lru_cache
    def count_vowels(sentence):
        sentence = sentence.casefold()
        return sum(sentence.count(vowel) for vowel in 'aeiou')

    """

    def doit1(self, piles):
        dp = {}
        N = len(piles)

        def wins(i, j):
            # The value of the game [piles[i], piles[i+1], ..., piles[j]].
            if i > j:
                return 0

            if (i, j) not in dp:

                parity = (j - i + 1) % 2
                if parity == 0:  # first player
                    dp[(i, j)] = max(piles[i] + wins(i+1, j),
                                     piles[j] + wins(i, j-1))
                else:
                    dp[(i, j)] = min(-piles[i] + wins(i+1, j), -
                                     piles[j] + wins(i, j-1))

            return dp[(i, j)]

        return wins(0, N - 1) > 0

    def doit(self, piles):

        N = len(piles)

        @lru_cache(None)
        def dp(i, j):
            # The value of the game [piles[i], piles[i+1], ..., piles[j]].
            if i > j:
                return 0
            parity = (j - i - N) % 2
            if parity == 1:  # first player
                return max(piles[i] + dp(i+1, j), piles[j] + dp(i, j-1))
            else:
                return min(-piles[i] + dp(i+1, j), -piles[j] + dp(i, j-1))

        return dp(0, N - 1) > 0


"""
If maxsize is set to None, the LRU feature is disabled and the cache can grow without bound.
The LRU feature performs best when maxsize is a power-of-two.

If typed is set to true, function arguments of different types will be cached separately.
For example, f(3) and f(3.0) will be treated as distinct calls with distinct results.

To help measure the effectiveness of the cache and tune the maxsize parameter,
the wrapped function is instrumented with a cache_info() function that returns a named tuple showing
hits, misses, maxsize and currsize. In a multi-threaded environment, the hits and misses are approximate.

The decorator also provides a cache_clear() function for clearing or invalidating the cache.

The original underlying function is accessible through the __wrapped__ attribute.
This is useful for introspection, for bypassing the cache, or for rewrapping the function with a different cache.

An LRU (least recently used) cache works best when the most recent calls are the best predictors of upcoming calls
(for example, the most popular articles on a news server tend to change each day).
The cache’s size limit assures that the cache does not grow without bound on long-running processes such as web servers.

In general, the LRU cache should only be used when you want to reuse previously computed values. Accordingly,
it doesn’t make sense to cache functions with side-effects, functions that need to create distinct mutable objects on each call, or impure functions such as time() or random().

Example of an LRU cache for static web content:
"""
@lru_cache(maxsize=32)
def get_pep(num):
    'Retrieve text of a Python Enhancement Proposal'
    resource = 'http://www.python.org/dev/peps/pep-%04d/' % num
    try:
        with urllib.request.urlopen(resource) as s:
            return s.read()
    except urllib.error.HTTPError:
        return 'Not Found'


@lru_cache(maxsize=None)
def fib(n):
    if n < 2:
        return n
    return fib(n-1) + fib(n-2)


def test_lru_cache():

    for n in 8, 290, 308, 320, 8, 218, 320, 279, 289, 320, 9991:
        pep = get_pep(n)
        print(n, len(pep))

    # CacheInfo(hits=3, misses=8, maxsize=32, currsize=8)
    print(get_pep.cache_info())

    print([fib(n) for n in range(16)])

    fib.cache_info()  # CacheInfo(hits=28, misses=16, maxsize=None, currsize=16)


"""
# @functools.total_ordering

Given a class defining one or more rich comparison ordering methods, this class decorator supplies the rest.
This simplifies the effort involved in specifying all of the possible rich comparison operations:

The class must define one of __lt__(), __le__(), __gt__(), or __ge__(). In addition, the class should supply an __eq__() method.
"""
@total_ordering
class Student:
    def _is_valid_operand(self, other):
        return (hasattr(other, "lastname") and
                hasattr(other, "firstname"))

    def __eq__(self, other):
        if not self._is_valid_operand(other):
            return NotImplemented
        return ((self.lastname.lower(), self.firstname.lower()) ==
                (other.lastname.lower(), other.firstname.lower()))

    def __lt__(self, other):
        if not self._is_valid_operand(other):
            return NotImplemented
        return ((self.lastname.lower(), self.firstname.lower()) <
                (other.lastname.lower(), other.firstname.lower()))


if __name__ == '__main__':

    test_lru_cache()
