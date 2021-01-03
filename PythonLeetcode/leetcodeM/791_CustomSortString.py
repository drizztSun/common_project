"""
791. Custom Sort String

S and T are strings composed of lowercase letters. In S, no letter occurs more than once.

S was sorted in some custom order previously. We want to permute the characters of T so that they match the order that S was sorted. More specifically, 
if x occurs before y in S, then x should occur before y in the returned string.

Return any permutation of T (as a string) that satisfies this property.

Example :
Input: 
S = "cba"
T = "abcd"
Output: "cbad"
Explanation: 
"a", "b", "c" appear in S, so the order of "a", "b", "c" should be "c", "b", and "a". 
Since "d" does not appear in S, it can be at any position in T. "dcba", "cdba", "cbda" are also valid outputs.
 

Note:

S has length at most 26, and no character is repeated in S.
T has length at most 200.
S and T consist of lowercase letters only.

"""




class CustomSortString:

    
    """
    Approach #1: Count and Write [Accepted]
    Intuition

    Let's first write to our answer the elements of T that occur in S, in order of S. After, we'll write any elements of T we didn't write. This obviously keeps all the ordering relationships we wanted.

    In the second write, the order doesn't matter because those elements aren't in S, so there are no ordering relationships these elements have to satisfy.

    Algorithm

    The trick is to count the elements of T. After we have some count[char] = (the number of occurrences of char in T), we can write these elements in the order we want. The order is S + (characters not in S in any order).

    For more details on the algorithm, please see the inlined comments in each implementation.

    Complexity Analysis

    Time Complexity: O(S.\text{length} + T.\text{length})O(S.length+T.length), the time it takes to iterate through S and T

    Space Complexity: O(T.\text{length})O(T.length). We count at most 26 different lowercase letters, but the final answer has the same length as T.
    """
    def doit_hashtable(self, S, T):
        # count[char] will be the number of occurrences of
        # 'char' in T.
        count = collections.Counter(T)
        ans = []

        # Write all characters that occur in S, in the order of S.
        for c in S:
            ans.append(c * count[c])
            # Set count[c] = 0 to denote that we do not need
            # to write 'c' to our answer anymore.
            count[c] = 0

        # Write all remaining characters that don't occur in S.
        # That information is specified by 'count'.
        for c in count:
            ans.append(c * count[c])

        return "".join(ans)

    def customSortString(self, S: str, T: str) -> str:
        from collections import Counter        
        cnt = Counter(T)
        output = []
        
        for s in S:
            if s in T:
                output.append(cnt[s] * s)
                del cnt[s]
                
        for s, num in cnt.items():
            output.append(s * num)
            
        return ''.join(output)