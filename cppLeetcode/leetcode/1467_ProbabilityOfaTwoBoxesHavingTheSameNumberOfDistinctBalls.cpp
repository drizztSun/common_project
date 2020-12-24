/*
1467. Probability of a Two Boxes Having The Same Number of Distinct Balls

Given 2n balls of k distinct colors. You will be given an integer array balls of size k where balls[i] is the number of balls of color i. 

All the balls will be shuffled uniformly at random, then we will distribute the first n balls to the first box and the remaining n balls to the other box (Please read the explanation of the second example carefully).

Please note that the two boxes are considered different. For example, if we have two balls of colors a and b, and two boxes [] and (), then the distribution [a] (b) is considered different than the distribution [b] 
(a) (Please read the explanation of the first example carefully).

We want to calculate the probability that the two boxes have the same number of distinct balls.

 

Example 1:

Input: balls = [1,1]
Output: 1.00000
Explanation: Only 2 ways to divide the balls equally:
- A ball of color 1 to box 1 and a ball of color 2 to box 2
- A ball of color 2 to box 1 and a ball of color 1 to box 2
In both ways, the number of distinct colors in each box is equal. The probability is 2/2 = 1
Example 2:

Input: balls = [2,1,1]
Output: 0.66667
Explanation: We have the set of balls [1, 1, 2, 3]
This set of balls will be shuffled randomly and we may have one of the 12 distinct shuffles with equale probability (i.e. 1/12):
[1,1 / 2,3], [1,1 / 3,2], [1,2 / 1,3], [1,2 / 3,1], [1,3 / 1,2], [1,3 / 2,1], [2,1 / 1,3], [2,1 / 3,1], [2,3 / 1,1], [3,1 / 1,2], [3,1 / 2,1], [3,2 / 1,1]
After that we add the first two balls to the first box and the second two balls to the second box.
We can see that 8 of these 12 possible random distributions have the same number of distinct colors of balls in each box.
Probability is 8/12 = 0.66667
Example 3:

Input: balls = [1,2,1,2]
Output: 0.60000
Explanation: The set of balls is [1, 2, 2, 3, 4, 4]. It is hard to display all the 180 possible random shuffles of this set but it is easy to check that 108 of them will have the same number of distinct colors in each box.
Probability = 108 / 180 = 0.6
Example 4:

Input: balls = [3,2,1]
Output: 0.30000
Explanation: The set of balls is [1, 1, 1, 2, 2, 3]. It is hard to display all the 60 possible random shuffles of this set but it is easy to check that 18 of them will have the same number of distinct colors in each box.
Probability = 18 / 60 = 0.3
Example 5:

Input: balls = [6,6,6,6,6,6]
Output: 0.90327
 

Constraints:

1 <= balls.length <= 8
1 <= balls[i] <= 6
sum(balls) is even.
Answers within 10^-5 of the actual value will be accepted as correct.
*/
#include <vector>
#include <numeric>

using std::vector;

class SameNumbnerDistictBalls {

public:

    /*
    Depuplication 
    4 balls, why not 4! = 24?

    Since there are balls with the same color, permurating 


    Solution 0: Permutation (TLE)
    Enumerate all permutations of the balls, count valid ones and divide that by the total.

    Time complexity: O((8*6)!) = O(48!)
    After deduplication: O(48!/(6!)^8) ~ 1.7e38
    Space complexity: O(8*6)
    */
    double doit_math(vector<int>& balls) {

        const int k = balls.size();
        vector<int> bs;
        for (int i = 0; i < k; ++i)
            for (int j = 0; j < balls[i]; ++j)
                bs.push_back(i);

        const int n = bs.size();
        double total = 0.0;
        double valid = 0.0;
        // d : depth
        // used : bitmap of bs's usage
        // c1: bitmap of colors of box1
        // c2: bitmap of colors of box1
        std::function<void(int, long, int, int)> dfs = [&](int d, long used, int c1, int c2) {    
            if (d == n) {          
                total += 1;
                valid += __builtin_popcount(c1) == __builtin_popcount(c2);                
                return;
            }

            for (int i = 0; i < n; ++i) {
                if (used & (1L << i)) 
                    continue;

                // Deduplication.
                if (i > 0 && bs[i] == bs[i - 1] && !(used & (1L << (i - 1)))) 
                    continue;        
                
                int tc1 = (d < n / 2) ? (c1 | (1 << bs[i])) : c1;
                int tc2 = (d < n / 2) ? c2 : (c2 | (1 << bs[i])); // adding this color to that boxes
                
                dfs(d + 1, used | (1L << i), tc1, tc2);
            }
        };

        dfs(0, 0, 0, 0);    
        return valid / total;
    }

    /*



        Solution 1: Combination
        For each color, put n_i balls into box1, the left t_i – n_i balls go to box2.
        permutations = fact(n//2) / PROD(fact(n_i)) * fact(n//2) * PROD(fact(t_i – n_i))
        E.g
        balls = [1×2, 2×6, 3×4]
        One possible combination:
        box1: 1 22 333
        box2: 1 2222 3
        permutations = 6! / (1! * 2! * 3!) * 6! / (1! * 4! * 1!) = 1800

        Time complexity: O((t+1)^k) = O(7^8)
        Space complexity: O(k + (t*k)) = O(8 + 48)
    */
    double doit_math_1(vector<int>& balls) {
        const int n = std::accumulate(begin(balls), end(balls), 0);
        const int k = balls.size();        
        double total = 0.0;
        double valid = 0.0;
        vector<double> fact(50, 1.0);
        for (int i = 1; i < fact.size(); ++i)
        fact[i] = fact[i - 1] * i;
        // d: depth
        // b1, b2: # of balls in box1, box2
        // c1, c2: # of distinct colors in box1, box2
        // p1, p2: # permutations of duplicate balls in box1, box2
        std::function<void(int, int, int, int, int, double, double)> dfs = [&] (int d, int b1, int b2, int c1, int c2, double p1, double p2) {
            if (b1 > n / 2 || b2 > n / 2) 
                return;
            
            if (d == k) {
                const double count = fact[b1] / p1 * fact[b2] / p2;
                total += count;
                valid += count * (c1 == c2);
                return;
            }
            
            for (int s1 = 0; s1 <= balls[d]; ++s1) {
                const int s2 = balls[d] - s1; 
                dfs(d + 1,
                    b1 + s1, 
                    b2 + s2,
                    c1 + (s1 > 0), 
                    c2 + (s2 > 0), 
                    p1 * fact[s1], 
                    p2 * fact[s2]);
            }
        };
        dfs(0, 0, 0, 0, 0, 1.0, 1.0);
        return valid / total;
    }

    double doit_math_2(vector<int>& balls) {
        const int k = balls.size();                    
        const int n = accumulate(begin(balls), end(balls), 0);
        vector<double> fact(49, 1.0);

        for (int i = 1; i < fact.size(); ++i)
            fact[i] = fact[i - 1] * i;
            auto perms = [&](const vector<int>& bs, int n) -> double {
            double p = fact[n];
            for (int b : bs) p /= fact[b];        
            return p;
        };
        vector<int> box1, box2;
        
        std::function<double(int)> dfs = [&](int d) -> double {
            const int n1 = accumulate(begin(box1), end(box1), 0);
            const int n2 = accumulate(begin(box2), end(box2), 0);
            if (n1 > n / 2 || n2 > n / 2) return 0;
            if (d == k)
                return (box1.size() == box2.size()) * perms(box1, n1) * perms(box2, n2);
            double total = 0;
            for (int s1 = 0; s1 <= balls[d]; ++s1) {
                const int s2 = balls[d] - s1;
                if (s1) box1.push_back(s1);
                if (s2) box2.push_back(s2);
                total += dfs(d + 1);
                if (s1) box1.pop_back();
                if (s2) box2.pop_back();
            }
            return total;
        };
        return dfs(0) / perms(balls, n);
    }
};
 