/*
1663. Smallest String With A Given Numeric Value

The numeric value of a lowercase character is defined as its position (1-indexed) in the alphabet, so the numeric value of a is 1, the numeric value of b is 2, the numeric value of c is 3, and so on.

The numeric value of a string consisting of lowercase characters is defined as the sum of its characters' numeric values. For example, the numeric value of the string "abe" is equal to 1 + 2 + 5 = 8.

You are given two integers n and k. Return the lexicographically smallest string with length equal to n and numeric value equal to k.

Note that a string x is lexicographically smaller than string y if x comes before y in dictionary order, that is, either x is a prefix of y, or if i is the first position such that x[i] != y[i], then x[i] comes before y[i] in alphabetic order.

 

Example 1:

Input: n = 3, k = 27
Output: "aay"
Explanation: The numeric value of the string is 1 + 1 + 25 = 27, and it is the smallest string with such a value and length equal to 3.
Example 2:

Input: n = 5, k = 73
Output: "aaszz"
 

Constraints:

1 <= n <= 10^5
n <= k <= 26 * n



    Overview
    We have to build a string of length nn that consists of English lowercase characters a-z by ensuring that following conditions are satisfied,

    The numeric value of a string must be equal to a given value kk. The numeric value of a string is equal to the sum of numeric values of all its characters. 
    The numeric value of alphabet characters ranges from 11 to 2626, where value of a = 1a=1, b=2b=2 and so on.
    
    The string must be lexicographically smallest string. In other words, we must build a string that would be the smallest in its dictionary order for a given numeric value.
    The value of kk would be at least nn. If k = nk=n, the numeric value of every position would be 11 (a).

    Example: if n = 3 and k = 3, result would be aaa.

    The value of kk would be at most (n * 26)(n∗26). If k = (n*26)k=(n∗26), the numeric value of every position would be 2626 (z).

    Example: if n = 3 and k = 78 (3 * 26) , result would be zzz.

    Based on these insights, let's implement the solution using different approaches.

*/
#include <string>

using std::string;

class SmallestString {

public:

    string doit_greedy(int n, int k) {
        // Greedy: for each index from 1 to n, find the smallest character could be inserted.
        // The smallest possible character can be found in this way:
        // 1) Find the value of 26*(n - i) and k - accumulate_sum_so_far, saying n1 and n2.
        // 2) if (n2 - n1) <= 1, we can insert 'a' in current position.
        // 3) Otherwise the smallest possible character would be 'a' + (n2 - n1) - 1.
        int acc = 0;
        string res;
        
        for (int i = 1; i <= n; ++i)
        {
            int n1 = 26 * (n - i), n2 = k - acc;
            if (n2 - n1 <= 1) 
            {
                // if rest them we can enought to use 'z' 16, we can try to use 'a' 1.
                res += 'a';
                acc += 1;
            }
            else
            {
                res += (char)('a' + n2 - n1 - 1);
                acc += n2 - n1;
            }
        }
        
        return res;
    }

    /*
        Approach 1: Build number from left to right
        Intuition

        Typically, we have to build a string by filling each position with a character that satisfies some conditions. To implement the solution for this problem we must answer the following question: 
        How to choose a character to be put for a given position in the string.

        To answer this question we must have information on 2 parameters,

        The remaining value of kk at any given point.
        The number of positions that are yet to be filled.
        Let's assume, we are given n = 4n=4 and we have the first 22 positions in the result filled with a. Now we have to decide which character to put at 3^{rd}3 
        rd
        position. Let's understand scenarios with different kk values.

        Scenario 1: If the given kk value is 3232. After filling first 2 positions with a ( numeric value = 11), the remaining kk value would be 3030. Now we have to split 3030 into remaining 22 positions in such a way that resultant string is lexicographically smallest.

        Lexicographically smallest string is always alphabetically sorted. But an alphabetically sorted string may not be always lexicographically sorted. Example, numeric value of dzdz (4 + 26 = 30) is same as the numeric value of eyey (5 + 25 = 30). Both the strings are alphabetically sorted. But, the former is also lexicographically sorted while the latter is not.

        Thus, we have to choose the character at 3^{rd}3 
        rd
        position in such a way that the character at 4^{th}4 
        th
        position would be as large as possible. We know that the largest possible character is z with a numeric value of 2626. As the remaining kk value is 3030, we can reserve 2626 for 4^{th}4 
        th
        position and use the remaining for current position 33.

        Hence, the numeric value chosen for 3^{rd}3 
        rd
        position would be 44 (30 - 26) and the character with the numeric value 44 is dd. The resultant string would be aadz.

        The following figure illustrates the idea.

        img

        Scenario 2: If the given kk value is 2424. After filling first 2 positions with a (numeric value = 1), the remaining kk value would be 2222. Now, since the remaining kk value is less than 2626, we must assign 3^{rd}3 
        rd
        position with smallest character i.e a having numeric value 11 and leave the rest for 4^{th}4 
        th
        position. The resultant string would be aaau.

        The following figure illustrates the idea.

        img

        Based on the above examples, we could develop the following intuition to choose a character for a position.

        Given a value kk and number of positions left to be filled as \text{positionsLeft}positionsLeft,

        If kk is greater than \text{positionsLeft} * 26positionsLeft∗26, we can reserve the maximum numeric value 2626 (character = z) for all the positions left. After that we could assign numeric value k - (\text{positionsLeft} * 26)k−(positionsLeft∗26) for the current position.

        Otherwise, we must assign the smallest character i.e a at the current position.

        Algorithm

        Build a string or character array result to store the characters chosen for each position.

        Iterate from position 11 to nn and fill the character at each position. Find the positions left to be filled excluding the current position given by positionsLeft as n - position - 1.

        If value of kk is greater than positionsLeft * 26, we could reserve numeric value 2626 (character = z) for all the remaining positions positionsLeft.

        The numeric value for current position given by variable add would be k - (positionsLeft * 26). Subtract the calculated value add from k to find the remaining k value after filling the current position.

        Otherwise, we must fill the the current position with the smallest character a having numeric value 11. Subtract 11 from k to find the remaining k value after filling the current position.

        The process would continue until all the positions are filled.

        Implementation


        Complexity Analysis

        Time Complexity: \mathcal{O}(n)O(n), as we iterate over nn positions to build the resultant string.

        Space Complexity: \mathcal{O}(1)O(1), as we use constant extra space to store add and position variables.
    
    */
    
    string doit_greedy(int n, int k) {
        
        string result(n, 0);

        for (int position = 0; position < n; position++) {
            int positionsLeft = n - position - 1;
            if (k > positionsLeft * 26) {
                int add = k - (positionsLeft * 26);
                result[position] = ('a' + add - 1);
                k -= add;
            } else {
                result[position] = 'a';
                k--;
            }
        }
        return result;
    }

    /*
        Approach 2: Build number from right
        Intuition

        There is another way of looking at the problem. We know that we must fill all the nn positions and the smallest character could be a with numeric value 11. 
        If we have any kk left, we try to reserve as much as possible for the last positions.

        Hence, we could first fill all the positions with a. Then iterate from backward: the last position to the first position. As we iterate from n^{th}n 
        th
        position, we must try to allocate the maximum possible value to each position.

        Algorithm

        Build a string or character array result to store the characters chosen for each position.

        Fill all the n positions in result with character a. Since character a has numeric value 11, subtract n from k. (since we have filled n positions with numeric value 11).

        Now, start iterating from the last position n-1 and allocate the maximum possible numeric value to each position based on the remaining k. As we have already allocated a at each position with a value 11, 
        the maximum additional value that we can add at each position would be 2525 (26 - 1).

        Calculate the additional value to be added given by add as a minimum of 25 and k. Add the calculated value add at the current position and also subtract it from k.

        The process would continue until either all the positions are filled or there are no k values left (k = 0).

        Implementation


        Complexity Analysis

        Time Complexity: \mathcal{O}(n)O(n), as we iterate over nn positions to build the resultant string. First, to initialize all the positions with character a and then to add the additional value.

        Space Complexity: \mathcal{O}(1)O(1), as we use constant extra space to store add and position variables.

    */
    string doit_greedy(int n, int k) {
        string result(n, 'a');
        k -= n;
        for (int position = n - 1; position >= 0 && k > 0; position--) {
            int add = std::min(k, 25);
            result[position] = (char)(result[position] + add);
            k -= add;
        }
        return result;
    }

    /*
        Approach 3: Build number from right - Optimised solution
        Intuition

        In Approach 2, we first filled all the positions with the smallest character a, subtracted 11 numeric value for each position from kk, and later calculated the additional value. Instead of that, we could simply leave some value from kk for the remaining positions while iterating over each position from backward.

        While allocating a numeric value at any position, we must just make sure that there would be sufficient k values left such that all the remaining positions would get at least the smallest numeric value i.e 1.

        Algorithm

        Build a string or character array result to store the character chosen for each position.

        Start iterating from last position n-1 and allocate maximum possible numeric value to each position based on remaining k.

        We know that the largest character at any position could be z with numeric value 2626. Also, we must leave some value from k, that is, 1 numeric value for each remaining position (k - position). Thus the maximum numeric value for the current position given by add can be calculated as, minimum of k - position and 26.

        Subtract the value calculated for the current position add from k.

        The process would continue until all the positions are filled.

        Implementation


        Complexity Analysis

        Time Complexity: \mathcal{O}(n)O(n), as we iterate over nn positions to build the resultant string.

        Space Complexity: \mathcal{O}(1)O(1), as we use constant extra space to store add and position variables.
    
    */

    string getSmallestString(int n, int k) {
        string result(n, 0);
        for (int position = n - 1; position >= 0; position--) {
            int add = std::min(k - position, 26);
            result[position] = (char)(add + 'a' - 1);
            k -= add;
        }
        return result;
    }
};