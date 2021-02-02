"""
451. Sort Characters By Frequency

Given a string, sort it in decreasing order based on the frequency of characters.

Example 1:

Input:
"tree"

Output:
"eert"

Explanation:
'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
Example 2:

Input:
"cccaaa"

Output:
"cccaaa"

Explanation:
Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
Note that "cacaca" is incorrect, as the same characters must be together.
Example 3:

Input:
"Aabb"

Output:
"bbAa"

Explanation:
"bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.
"""


class FrequencySort:

    """
        Approach 3: Multiset and Bucket Sort
        Intuition

        While the second approach is probably adequate for an interview, there is actually a way of solving this problem with a time complexity of O(n)O(n).

        Firstly, observe that because all of the characters came out of a String of length nn, the maximum frequency for any one character is nn. This means that once we've determined all the letter frequencies using a HashMap,
         we can sort them in O(n)O(n) time using Bucket Sort. Recall that for our previous approaches, we used comparison-based sorts, which have a cost of O(n \, \log \, n)O(nlogn).

        This was the HashMap from earlier.

        The HashMap created with the string.

        Recall that Bucket Sort is the sorting algorithm where items are placed at Array indexes based on their values (the indexes are called "buckets"). 
        For this problem, we'll need to have a List of characters at each index. For example, here is how our String from before goes into the buckets.

        The HashMap bucket sorted

        While we could simply make our bucket Array length nn, we're best to just look for the maximum value (frequency) in the HashMap. 
        That way, we only use as much space as we need, and won't need to iterate over heaps of empty buckets during the next phase.

        Finally, we need to iterate over the buckets, starting with the largest and ending with the smallest, building up the string in much the same way as we did before.

        Algorithm

        Bucket sort

        Complexity Analysis

        Let nn be the length of the input String. The kk (number of unique characters in the input String that we considered for the last approach makes no difference this time).

        Time Complexity : O(n).

        Like before, the HashMap building has a cost of O(n).

        The bucket sorting is O(n), because inserting items has a cost of O(k) (each entry from the HashMap), and building the buckets initially has a worst case of O(n) (which occurs when k=1). 
        Because k ≤ nk≤n, we're left with O(n).

        So in total, we have O(n).

        It'd be impossible to do better than this, because we need to look at each of the nn characters in the input String at least once.

        Space Complexity : O(n).

        Same as above. The bucket Array also uses O(n) space, because its length is at most nn, and there are k items across all the buckets.
    """
    def doit_sort(self, s: str) -> str:
        from collections import Counter
        if not s: return s
        
        # Determine the frequency of each character.
        counts = Counter(s)
        max_freq = max(counts.values())
        
        # Bucket sort the characters by frequency.
        buckets = [[] for _ in range(max_freq + 1)]
        for c, i in counts.items():
            buckets[i].append(c)
            
        # Build up the string.
        string_builder = []
        for i in range(len(buckets) - 1, 0, -1):
            for c in buckets[i]:
                string_builder.append(c * i)
                
        return "".join(string_builder)

    """
        Approach 2: HashMap and Sort
        Intuition

        Another approach is to use a HashMap to count how many times each character occurs in the String; the keys are characters and the values are frequencies.

        The HashMap created with the string.

        Next, extract a copy of the keys from the HashMap and sort them by frequency using a Comparator that looks at the HashMap values to make its decisions.

        The HashMap created with the string.

        Finally, initialise a new StringBuilder and then iterate over the list of sorted characters (sorted by frequency). Look up the values in the HashMap to know how many of each character to append to the StringBuilder.

        Algorithm


        Complexity Analysis

        Let nn be the length of the input String and kk be the number of unique characters in the String.

        We know that k ≤ nk≤n, because there can't be more unique characters than there are characters in the String. We also know that kk is somewhat bounded by the fact that there's only a finite number of characters in Unicode (or ASCII, which I suspect is all we need to worry about for this question).

        There are two ways of approaching the complexity analysis for this question.

        We can disregard kk, and consider that in the worst case, k = n.
        We can consider kk, recognising that the number of unique characters is not infinite. This is more accurate for real world purposes.
        I've provided analysis for both ways of approaching it. I choose not to bring it up for the previous approach, because it made no difference there.

        Time Complexity : O(nlogn) OR O(n+klogk).

        Putting the characterss into the HashMap has a cost of O(n)O(n), because each of the nn characterss must be put in, and putting each in is an O(1)O(1) operation.

        Sorting the HashMap keys has a cost of O(k \, \log \, k)O(klogk), because there are kk keys, and this is the standard cost for sorting. If only using nn, then it's O(n \, \log \, n)O(nlogn). For the previous question, the sort was carried out on nn items, not kk, so was possibly a lot worse.

        Traversing over the sorted keys and building the String has a cost of O(n)O(n), as nn characters must be inserted.

        Therefore, if we're only considering nn, then the final cost is O(n \, \log \, n)O(nlogn).

        Considering kk as well gives us O(n + k \, \log \, k)O(n+klogk), because we don't know which is largest out of nn and k \, \log \, kklogk. We do, however, know that in total this is less than or equal to O(n \, \log \, n)O(nlogn).

        Space Complexity : O(n).

        The HashMap uses O(k) space.

        However, the StringBuilder at the end dominates the space complexity, pushing it up to O(n)O(n), as every character from the input String must go into it. Like was said above, it's impossible to do better with the space complexity here.

        What's interesting here is that if we only consider nn, the time complexity is the same as the previous approach. But by considering kk, we can see that the difference is potentially substantial.
        
    """
    def doit_sort(self, s: str) -> str:
        from collections import Counter
        return ''.join(s[0]*s[1] for s in sorted(Counter(s).items(), key=lambda x: -x[1]))

    def doit_sort(self, s):
        """
        :type s: str
        :rtype: str
        """
        alphabet = {}
        for c in s:
            alphabet[c] = alphabet.get(c, 0) + 1

        data = []
        for c in alphabet.keys():
            data.append((alphabet[c], c))

        data.sort(key=lambda x: x[0], reverse=1)

        res = ''
        for c in data:
            res += c[1] * c[0]

        return res

    """
        Approach 1: Arrays and Sorting
        Intuition

        In order to sort the characters by frequency, we firstly need to know how many of each there are. One way to do this is to sort the characters by their numbers so that identical characters are side-by-side (all characters in a programming language are identified by a unique number). Then, knowing how many times each appears will be a lot easier.

        Because Strings are immutable though, we cannot sort the String directly. Therefore, we'll need to start by converting it from a String to an Array of characters.

        Converting the string "welcometoleetcode" to a list.

        Now that we have an Array, we can sort it, which will make all identical characters side-by-side.

        The Array of characters sorted.

        There are a few different ways we can go from here. One easy-to-understand way is to create a new Array of Strings. Each String in the list will consist of one of the unique characters from the sorted characters Array.

        The characters grouped into strings of the same character.

        Remember: do this process using StringBuilders, not naïve String appending! (See the first section of this article if you're confused).

        The next step is to sort this Array of Strings by length. To do this, we'll need to implement a suitable Comparator. Recall that there is no requirement for characters of the same frequency to appear in a specific order.

        The strings sorted by length.

        Finally, we can convert this Array of Strings into a single String. In Java, this can be done by passing the Array into a StringBuilder and then calling .toString(...) on it.

        String building the strings into a single string.

        Algorithm


        Complexity Analysis

        Let nn be the length of the input String.

        Time Complexity : O(nlogn).

        The first part of the algorithm, converting the String to a List of characters, has a cost of O(n)O(n), because we are adding nn characters to the end of a List.

        The second part of the algorithm, sorting the List of characters, has a cost of O(n \, \log \, n)O(nlogn).

        The third part of the algorithm, grouping the characters into Strings of similar characters, has a cost of O(n)O(n) because each character is being inserted once into a StringBuilder and once converted into a String.

        Finally, the fourth part of the algorithm, sorting the Strings by length, has a worst case cost of O(n)O(n), which occurs when all the characters in the input String are unique.

        Because we drop constants and insignificant terms, we get O(n \, \log \, n) + 3 \cdot O(n) = O(n \, \log \, n)O(nlogn)+3⋅O(n)=O(nlogn).

        Be careful with your own implementation—if you didn't do the string building process in a sensible way, then your solution could potentially be O(n^2)O(n 
        2
        ).

        Space Complexity : O(n).

        It is impossible to do better with the space complexity, because Strings are immutable. The List of characters, List of Strings, and the final output String, are all of length nn, so we have a space complexity of O(n)O(n).
    """
    def frequencySort(self, s: str) -> str:
        if not s: return s
        
        # Convert s to a list.
        s = list(s)
        
        # Sort the characters in s.
        s.sort()
        
        # Make a list of strings, one for each unique char.
        all_strings = []
        cur_sb = [s[0]]
        for c in s[1:]:
            # If the last character on string builder is different...
            if cur_sb[-1] != c:
                all_strings.append("".join(cur_sb))
                cur_sb = []
            cur_sb.append(c)
        all_strings.append("".join(cur_sb))
        
        # Sort the strings by length from *longest* to shortest.
        all_strings.sort(key=lambda string : len(string), reverse=True)
        
        # Convert to a single string to return.
        # Converting a list of strings to a string is often done
        # using this rather strange looking python idiom.
        return "".join(all_strings)