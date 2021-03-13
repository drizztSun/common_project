/*
454. 4Sum II

Given four lists A, B, C, D of integer values, compute how many tuples (i, j, k, l) there are such that A[i] + B[j] + C[k] + D[l] is zero.

To make problem a bit easier, all A, B, C, D have same length of N where 0 ≤ N ≤ 500. All integers are in the range of -228 to 228 - 1 and the result is guaranteed to be at most 231 - 1.

Example:

Input:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]

Output:
2

Explanation:
The two tuples are:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0

*/


#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>

using std::unordered_map;
using std::vector;



class FourSumCount {

public:

    /*
        Approach 1: Hashmap
        A brute force solution will be to enumerate all combinations of elements using four nested loops, which results in \mathcal{O}(n^4)O(n 
        4
        ) time complexity. A faster approach is to use three nested loops, and, for each sum a + b + c, search for a complementary value d == -(a + b + c) in the fourth array. We can do the search in \mathcal{O}(1)O(1) if we populate the fourth array into a hashmap.

        Note that we need to track the frequency of each element in the fourth array. If an element is repeated multiple times, it will form multiple quadruples. Therefore, we will use hashmap values to store counts.

        Building further on this idea, we can observe that a + b == -(c + d). First, we will count sums of elements a + b from the first two arrays using a hashmap. Then, we will enumerate elements from the third and fourth arrays, and search for a complementary sum a + b == -(c + d) in the hashmap.

        Current
        1 / 8
        Algorithm

        For each a in A.

        For each b in B.
        If a + b exists in the hashmap m, increment the value.
        Else add a new key a + b with the value 1.
        For each c in C.

        For each d in D.
        Lookup key -(c + d) in the hashmap m.
        Add its value to the count cnt.
        Return the count cnt.


        Complexity Analysis

        Time Complexity: \mathcal{O}(n^2)O(n 
        2
        ). We have 2 nested loops to count sums, and another 2 nested loops to find complements.

        Space Complexity: \mathcal{O}(n^2)O(n 
        2
        ) for the hashmap. There could be up to \mathcal{O}(n^2)O(n 
        2
        ) distinct a + b keys.
    */

    int doit_hashtable(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        
        unordered_map<int, int> ab;
        for (auto a: A)
            for (auto b: B)
                ab[a + b]++;
        
        int ans = 0;
        for (auto c: C)
            for (auto d: D) {
                int target = 0 - (c+d);
                if (ab.count(target))
                    ans += ab[target];
            }
        
        return ans;
    }

    /*
        Approach 2: kSum II
        After you solve 4Sum II, an interviewer can follow-up with 5Sum II, 6Sum II, and so on. What they are really expecting is a generalized solution for k input arrays. Fortunately, the hashmap approach can be easily extended to handle more than 4 arrays.

        Above, we divided 4 arrays into two equal groups, and processed each group independently. Same way, we will divide kk arrays into two groups. For the first group, we will have \frac{k}{2} 
        2
        k
        ​	
        nested loops to count sums. Another \frac{k}{2} 
        2
        k
        ​	
        nested loops will enumerate arrays in the second group and search for complements.

        Algorithm

        We can implement \frac{k}{2} 
        2
        k
        ​	
        nested loops using a recursion, passing the index i of the current list as the parameter. The first group will be processed by addToHash recursive function, which accumulates sum and terminates when adding the final sum to a hashmap m.

        The second function, countComplements, will process the other group, accumulating the complement value. In the end, it searches for the final complement value in the hashmap and adds its count to the result.


        Complexity Analysis

        Time Complexity: \mathcal{O}(n^{\frac{k}{2}})O(n 
        2
        k
        ​	
        
        ), or \mathcal{O}(n^2)O(n 
        2
        ) for 4Sum II. We have \frac{k}{2} 
        2
        k
        ​	
        nested loops to count sums, and another \frac{k}{2} 
        2
        k
        ​	
        nested loops to find complements.

        If the number of arrays is odd, the time complexity will be \mathcal{O}(n^{\frac{k+1}{2}})O(n 
        2
        k+1
        ​	
        
        ). We will pass \frac{k}{2} 
        2
        k
        ​	
        arrays to addToHash, and \frac{k+1}{2} 
        2
        k+1
        ​	
        arrays to kSumCount to keep the space complexity \mathcal{O}(n ^ {\frac{k}{2}})O(n 
        2
        k
        ​	
        
        ).

        Space Complexity: \mathcal{O}(n^{\frac{k}{2}})O(n 
        2
        k
        ​	
        
        ) for the hashmap. The space needed for the recursion will not exceed \frac{k}{2} 
        2
        k  
    */
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {

        std::function<void(vector<vector<int>>&, unordered_map<int, int>, int, int)> addToHash = [&](vector<vector<int>> &lists, unordered_map<int, int> &m, int i, int sum) {
            if (i == lists.size() / 2)
                ++m[sum];
            else
                for (int a : lists[i])
                    addToHash(lists, m, i + 1, sum + a);
        };

        std::function<int(vector<vector<int>>&, unordered_map<int, int>&, int, int)> countComplements = [&](vector<vector<int>> &lists, unordered_map<int, int> &m, int i, int complement) {
            if (i == lists.size()) {
                auto it = m.find(complement);
                return it == end(m) ? 0 : it->second;
            }
            int cnt = 0;
            for (int a : lists[i])
                cnt += countComplements(lists, m, i + 1, complement - a);
            return cnt;
        };

        auto kSumCount = [&](vector<vector<int>> &lists) ->int {
            unordered_map<int, int> m;
            addToHash(lists, m, 0, 0);
            return countComplements(lists, m, lists.size() / 2, 0);
        };

        return kSumCount(vector<vector<int>>() = {A, B, C, D});
    }

};