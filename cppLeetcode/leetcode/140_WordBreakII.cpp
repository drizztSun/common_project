/*
 140. Word Break II
 
 Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences.

 Note:

 The same word in the dictionary may be reused multiple times in the segmentation.
 You may assume the dictionary does not contain duplicate words.
 Example 1:

 Input:
 s = "catsanddog"
 wordDict = ["cat", "cats", "and", "sand", "dog"]
 Output:
 [
   "cats and dog",
   "cat sand dog"
 ]
 Example 2:

 Input:
 s = "pineapplepenapple"
 wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
 Output:
 [
   "pine apple pen apple",
   "pineapple pen apple",
   "pine applepen apple"
 ]
 Explanation: Note that you are allowed to reuse a dictionary word.
 Example 3:

 Input:
 s = "catsandog"
 wordDict = ["cats", "dog", "sand", "and", "cat"]
 Output:
 []
 
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

using std::vector;
using std::string;
using std::unordered_map;


class WordBreakII {

public:
    
    /*
        Approach 1: Top-Down Dynamic Programming
        Intuition

        Let us start with the top-down approach, which is more efficient compared to bottom-up approach in this case.

        Given an input string \text{s} = \text{`catsanddog'}s=‘catsanddog’, we define the results of breaking it into words with the function \text{F(s)}F(s).

        For any word (denoted as \text{w}w) in the dictionary, if it matches with a prefix of the input string, we then can divide the string into two parts: the word and the postfix, i.e. s = \text{w} + \text{postfix}s=w+postfix.

        Consequently, the solution for the input string can be represented as follows:

        \forall \text{w} \in \text{dict}, \quad s = \text{w} + \text{postfix} \implies \{ \text{w} + \text{F(postfix)} \} \subseteq \text{F(s)}∀w∈dict,s=w+postfix⟹{w+F(postfix)}⊆F(s)

        i.e. we add the matched word to the solutions from the postfix.

        For example, the word cat matches with a prefix of the string. As a result, we can divide the string into s = \text{`cat'} + \text{`sanddog'}s=‘cat’+‘sanddog’.

        For the postfix of sanddog, we could obtain the results by recursively applying our function, i.e. \text{F(`sanddog')} = \{ \text{`sand dog'} \}F(‘sanddog’)={‘sand dog’}. By adding the prefix word to the solutions of the postfix, we then obtain one of the solutions for the original string, i.e. \text{`cat sand dog'} \in \text{F(s)}‘cat sand dog’∈F(s).

        The above approach can be considered as a top-down DP. The reason lies in the part that we adopt the laissez-faire strategy, i.e. we simply take a first step, while assuming the subsequent steps will figure out on their owns.

        In our case, we first find a match to a prefix of the string, while assuming that we would eventually obtain the results for the corresponding postfix.

        In the following graph, we illustrate how the top-down approach works with a concrete example, i.e. with the input string as s="catsanddogo" and the word dictionary as wordDict=["cat", "cats", "and", "sand", "dog", "do", "go"].

        Algorithm

        Following the above intuition, it seems intuitive to implement the solution with recursion.

        We define a recursive function called _wordBreak_topdown(s) which generates the results for the input string. Here are a few steps to implement our recursive function.

        First of all, as the base case of the recursion, when the input string is empty, the recursion would terminate. Note that we return a list of empty list as the result, rather than just an empty list.

        As the main body of the function, we run an iteration over all the prefixes of the input string. If the corresponding prefix happens to match a word in the dictionary, we then invoke recursively the function on the postfix.

        At the end of the iteration, we keep the results in the hashmap named memo with each valid postfix string as its key and the list of words that compose the prefix of as the value. For instance, for the postfix dogo, its corresponding entry in the hashmap would be memo["dogo"] = ["do", "go"].

        Finally, as the result, we return the entry of memo with the input string as the key. (The string itself is a postfix of the string itself.)


    */
    vector<string> doit_dp_topdown(string s, vector<string>&& wordDict) {
     
        unordered_map<int, vector<string>> memo;
        memo[s.length()] = vector<string>{};

        std::function<void(int)> search = [&](int index) {
    
            if (memo.count(index) != 0) {
                return;
            }
            
            vector<string> ans;
            for (auto& word : wordDict) {
                
                if (word == s.substr(index, word.length())) {
                    
                    if (index + word.length() == s.length()) {
                        ans.push_back(word);
                        continue;
                    }

                    search(index + word.length());
                    
                    for (auto c : memo[index+word.length()]) {
                        ans.push_back(word + " " + c);
                    }
                }
            }
            
            memo[index] = ans;
            return;
        };

        search(0);
        return memo[0];
    }

    /*
        Approach 2: Bottom-Up Dynamic Programming
        Intuition

        As opposed to the top-down approach, the bottom-up dynamic programming progressively builds up the solutions for the sub-problems upfront, rather than delaying them to the end.

        We will demonstrate the difference between the two approaches with a concrete example later.

        Following the same definition in the top-down approach, given an input string \text{s}s, e.g. \text{s} = \text{`catsanddog'}s=‘catsanddog’, we define the results of breaking it into words with the function \text{F(s)}F(s).

        For any word (denoted as \text{w}w) in the dictionary, if it matches with a postfix of the input string, we then can divide the string into two parts: the prefix and the word, i.e. s = \text{prefix} + \text{w}s=prefix+w.

        Consequently, the solution for the input string can be represented as follows:

        \forall \text{w} \in \text{dict}, \quad s = \text{prefix} + \text{w} \implies \{ \text{F(prefix)} + \text{w} \} \subseteq \text{F(s)}∀w∈dict,s=prefix+w⟹{F(prefix)+w}⊆F(s)

        i.e. we add the matched word to the solutions from the prefix.

        We start from an empty prefix (i.e. the bottom case), to progressively extend the solutions to a larger prefix. Eventually, the extended prefix would grow to be the original string.

        In the following graph, we demonstrate how the bottom-up approach works for the same example in the top-down approach, i.e. with the input string as s="catsanddogo" and the word dictionary as wordDict=["cat", "cats", "and", "sand", "dog", "do", "go"].

        DP table

        As one can see from the above graph, by appending words to the prefixes, we obtain the solutions for the larger strings. At the end, we calculate the solutions for all possible prefixes, which includes the solutions for the original string, since the string itself is a prefix of the string.

        Algorithm

        To implement the bottom-up DP approach, we often use an array to keep track of all the intermediate solutions. The problem is no exception.

        We define an array called dp. Each element in the array (dp[i]) would be used to hold the solutions for the corresponding prefix s[0:i].

        For example, for the prefix of s[0:3] = "cat", the value for the element of dp[3] would be ["cat"], as we indicated in the previous graph.

        The goal of the algorithm boils down to calculating each element in the dp array. And the desired result would be the last element in the array, i.e. dp[len(s)], which corresponds to the results for the entire string.

        Here are a few steps on how to calculate the values for the dp array:

        First of all, we create an empty dp array to hold all the intermediate solutions.

        We then iterate through all prefixes of the input string, from the bottom case (empty string) to the entire string.

        For each prefix, we enumerate all possible combinations to see if we could reuse the solutions from the previous prefixes.


        Note: since this is not the most efficient algorithm, as we will see in the analysis later, we added an additional check at the beginning of the algorithm, to see if the input string contains some characters that do not appear in any of the words in the dictionary. If this is the case, then we are sure that the input string cannot be broken down into words, which can save us from running the algorithm.

        With this check, we could by pass some tricky test cases, not ending up with the TLE (Time Limit Exceeded) error.

        We mentioned previously that we could consider the top-down DP approach as the DFS (Depth-First Traversal) over the structure of graph.

        Similarly, we could consider the bottom-up DP approach as the BFS (Breadth-First Search) over the same graph structure, as shown in the following graph.

        BFS with DP table

        Rather than going in depth, the bottom-up DP approach explores the breadth first. It is not the best strategy in the case, since not every branch would lead to a potential solution, yet with BFS we have to keep all the intermediate solutions regardless of whether they would lead to a final solution or not. While in DFS, no intermediate solution is kept until it leads to a final solution. This is the main reason why DFS (top-down approach) is a much more efficient algorithm for this problem, compared to BFS (bottom-down approach).

        Keep Breaks Not Words

        One of the drawbacks of the above bottom-up implementation is that we keep the intermediate solutions in the form of strings, e.g. dp[7] = ['cat sand', 'cats and'].

        It is rather costly to do so. The rationale is twofold: 1). we have to keep many copies of string in the memory. 2). we have to iterate through the string to make a new copy, which is time-consuming.

        One of the optimizations that we can do is that rather than keeping the words (strings), we simply keep the positions to insert the breaks into the original string. For the same example of dp[7], we can store the values as dp[7] = [[3, 7], [4, 7]], which we could interpret as follows:

        For the solution of [3, 7], by inserting a break respectively at the indices of 3 and 7 in the original string, we could obtain a list of words, i.e. "cat sand".

        Similarly, the solution of [4, 7] corresponds to the list of words "cats and".

        With this optimization, we then can convert the previous dp array to the following: BFS with breaks As one can see, not only do we save the space to store the intermediate solutions, but also the time to calculate them.


        Recursive Encoding

        Although we save quite some efforts by storing just the breaks rather than the words themselves, still we were repeating the solutions of small prefixes in the solutions for the larger prefixes.

        To avoid this repetition, we could simply refer to the previous solutions with their indices in the dp array, rather than copying them.

        With the above recursive encoding schema, we could further reduce the dp array into the following:

        BFS with recursive encoding

        As shown in the above graph, each element in the encoding is a two-element tuple as [previous_dp_index, word_end_index]. First of all, the two indices define the scope of the word to be added. In addition, the first index (i.e. previous_dp_index) indicates the previous dp entry that we should recursively look into, in order to add the words that compose the prefix.

        With this schema, we could further save some space and time to calculate the intermediate solutions.

        One caveat though is that it is slightly more complex to decode the final solutions from the encoded results.


        Complexity Analysis

        Let NN be the length of the input string and WW be the number of words in the dictionary.

        Time Complexity: \mathcal{O}(N^2 + 2 ^ N + W)O(N 
        2
        +2 
        N
        +W)

        As we discussed before, in the worst case, it could be possible to insert a break between every adjacent characters in the input string, i.e. each prefix of length kk would have 2 ^ {k-1}2 
        k−1
        number of solutions.

        While we iterate over all prefixes of the input string, starting from the empty prefix, the number of solutions for each prefix would double at each step.

        Assume that we adopt the most optimal recursive encoding for the solutions, we would need kk steps to build solutions for the prefix of length kk. In total, we would need \sum_{i=1}^{N}{i} = \frac{(N+1) \cdot N}{2}∑ 
        i=1
        N
        ​	
        i= 
        2
        (N+1)⋅N
        ​	
        steps to build all intermediate solutions.

        However, at the end, we need to reconstruct the solutions from the encoding. In the worst case, we would have 2 ^ {N-1}2 
        N−1
        number of solutions. Thus it would take at least 2 ^ {N-1}2 
        N−1
        steps to reconstruct the solutions.

        Similarly, it would take WW steps to build the word set from the dictionary.

        In total, the overall time complexity for the bottom-up DP approach with the recursive encoding is \mathcal{O}(\frac{(N+1) \cdot N}{2} + 2 ^ {N-1} + W ) = \mathcal{O}(N^2 + 2 ^ N + W)O( 
        2
        (N+1)⋅N
        ​	
        +2 
        N−1
        +W)=O(N 
        2
        +2 
        N
        +W).

        Space Complexity: \mathcal{O}(2^N \cdot N + N^2 + W)O(2 
        N
        ⋅N+N 
        2
        +W)

        As stated above, in the worst case, each prefix of length kk would have 2 ^ {k-1}2 
        k−1
        number of solutions. Therefore, in total, we would have \sum_{k=1}^{N}{2 ^ {k-1}} = 2^N∑ 
        k=1
        N
        ​	
        2 
        k−1
        =2 
        N
        intermediate solutions. If we keep the solutions as words or breaks, we would need NN space for each solution. Thus, it amounts to 2^N \cdot N2 
        N
        ⋅N for the approaches that keep the intermediate solutions as words or breaks.

        On the other hand, if we use the recursive encoding, each prefix of length kk would only need kk entries at most to keep its solutions. With the encoding, we would only need \sum_{k=1}^{N}{k} = \frac{(1+N) \cdot N}{2}∑ 
        k=1
        N
        ​	
        k= 
        2
        (1+N)⋅N
        ​	
        space to keep all intermediate solutions.

        As always, we would need an additional WW space to hold the words in the dictionary.

        In total, the space complexity of the algorithm is \mathcal{O}(2^N \cdot N + N^2 + W)O(2 
        N
        ⋅N+N 
        2
        +W), if we adopt the recursive encoding schema.
    */

    vector<string> doit_dp_bottomup(string s, vector<string>&& wordDict) {

        int n = s.length();
        vector<vector<string>> dp(n + 1);
        dp[0] = { "" };

        for (int i = 0; i < n; i++) {

            vector<string> tmp;
            for (auto& w : wordDict) {
                int j = i - w.length();
                if (j >= -1 && s.substr(j + 1, w.length()) == w) {
                    if (!dp[j + 1].empty()) {
                        for (auto c : dp[j + 1]) {
                            tmp.push_back(c.empty() ? w : c + ' ' + w);
                        }
                    }
                }
            }

            dp[i + 1] = tmp;
        }

        return dp[n];
    }
};