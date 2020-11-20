/*
 1643. Kth Smallest Instructions
 
 Bob is standing at cell (0, 0), and he wants to reach destination: (row, column). He can only travel right and down. You are going to help Bob by providing instructions for him to reach destination.

 The instructions are represented as a string, where each character is either:

 'H', meaning move horizontally (go right), or
 'V', meaning move vertically (go down).
 Multiple instructions will lead Bob to destination. For example, if destination is (2, 3), both "HHHVV" and "HVHVH" are valid instructions.

 However, Bob is very picky. Bob has a lucky number k, and he wants the kth lexicographically smallest instructions that will lead him to destination. k is 1-indexed.

 Given an integer array destination and an integer k, return the kth lexicographically smallest instructions that will take Bob to destination.



 Example 1:



 Input: destination = [2,3], k = 1
 Output: "HHHVV"
 Explanation: All the instructions that reach (2, 3) in lexicographic order are as follows:
 ["HHHVV", "HHVHV", "HHVVH", "HVHHV", "HVHVH", "HVVHH", "VHHHV", "VHHVH", "VHVHH", "VVHHH"].
 Example 2:



 Input: destination = [2,3], k = 2
 Output: "HHVHV"
 Example 3:



 Input: destination = [2,3], k = 3
 Output: "HHVVH"


 Constraints:

 destination.length == 2
 1 <= row, column <= 15
 1 <= k <= nCr(row + column, row), where nCr(a, b) denotes a choose b.
 
 
 */

#include <string>
#include <vector>

using std::vector;
using std::string;

class KthSmallestPath {
public:
    string doit_dp(vector<int>&& destination, int k) {
        
        auto V = destination[0], H = destination[0];
        auto num = 0;
        int v = 0;
        string res;
        
        auto steps = [](int step, int b) {
            long long res = 1;
            for (auto i = 0; i < b; i++) {
                res *= (step - i);
                res /= (i+1);
            }
            return res;
        };
        
        for (auto i = 0; i < V+H; i++) {
            
            auto s = steps(V+H - i - 1, V - v);
            
            if (num + s < k) {
                v += 1;
                res.push_back('V');
                num += s;
            } else {
                res.push_back('H');
            }
        }
        
        return res;
    }

    /*
     Fundamentals
     We need to move to the right col steps and down row steps to reach to the destination (bottom right) cell => the result string is always:
     of length col + row
     consisted of row 'H's and col 'V's
     The possible strings are lexicographically ordered => 'H' < 'V'
     The total number of possible paths (number of combinations of row 'H's and col 'V's) is nCr(row + col, row). i.e., "length of string" choose "number of H"
     Why? We have row + col positions in the string, we need to choose row of them for 'H'.
     How to calculate N choose K?
     N!/(N-K)!/K! (Why? this is a math question. I'm not going to explain it here)
     tgamma(x) returns (x-1)!
     There are many other methods to calculate N choose K
     Solve the Problem
     Let's only consider the first letter.
     a) Say, we have h of 'H's and v of 'V's, there are x possible combinations (x = nCr(h+v, h))
     b) The chance we choose 'H' for the first letter is h/(h+v) => in all combinations, there are y of them (y = x * h/(h+v)) have 'H' as the first letter
     c) All the combinations are lexicographically ordered => the first y combinations have 'H' as the first letter
     d) We want the kth combination => if k <= y, the first letter should be 'H', otherwise it should be 'V'.
     We have found the first letter. Now let's look at the next one:
     a) If the first letter is 'H'
     - The number of combinations start with 'H' is y (calculated in step 1)
     - We have used one 'H', and we have h-1 left
     - The length of rest of strting is h+v-1
     - The remaining combinations (all start with 'H') - from 1st to yth, since k fell into this range, it remains the same (we need to find kth combination of 1 to y).
     b) If the first letter is 'V'
     - The number of combinations start with 'V' is x - y
     - We didn't use 'H', so we still have h 'H's left
     - The length of rest of strting is h+v-1
     - The remaining combinations (all start with 'V') are from y+1 to x => we need to find (kth from 1st, that is) k-yth combination from y+1.
     c) Apply same method of step 1, we can find the 2nd letter.
     Repeated step 2 until we used either all 'H's or all 'V's.
     Fill rest of the string with the other letter.
     
     Complexity
     We built the string of length row + col letter by letter => O(n), where n = row + col

     Additional Note
     Calculating N choose K can be time consuming. We only need to calculate it once in this solution, instead of every step (like many other solutions do).
     
     */
    
    
    
    string doit_dp_1(vector<int>& destination, int k) {
        
        auto NChooseK = [](int n, int k) {
            return round(tgamma(n+1)/tgamma(k+1)/tgamma(n-k+1));
        };
        
        int numHLeft = destination[1], numCharsToBuild = destination[0] + destination[1];
        uint64_t totalMax = NChooseK(numCharsToBuild, numHLeft);
        string ans = "";
        
        
        while (numHLeft && numHLeft < numCharsToBuild) {
            uint64_t maxH = totalMax*numHLeft/numCharsToBuild;
            if (k <= maxH) {
                ans += "H";
                numHLeft--;
                totalMax = maxH;
            } else {
                ans += "V";
                totalMax -= maxH;
                k -= maxH;
            }
            numCharsToBuild--;
        }
        ans += string(numCharsToBuild, numHLeft ? 'H' : 'V');
        return ans;
    }
};

void test_1643_kth_smallest_path() {
    
    KthSmallestPath().doit_dp(vector<int>{2, 3}, 1);
    
}
