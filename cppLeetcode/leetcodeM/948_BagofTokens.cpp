/*
948. Bag of Tokens

You have an initial power of P, an initial score of 0, and a bag of tokens where tokens[i] is the value of the ith token (0-indexed).

Your goal is to maximize your total score by potentially playing each token in one of two ways:

    . If your current power is at least tokens[i], you may play the ith token face up, losing tokens[i] power and gaining 1 score.
    . If your current score is at least 1, you may play the ith token face down, gaining tokens[i] power and losing 1 score.
Each token may be played at most once and in any order. You do not have to play all the tokens.

Return the largest possible score you can achieve after playing any number of tokens.

 

Example 1:

Input: tokens = [100], P = 50
Output: 0
Explanation: Playing the only token in the bag is impossible because you either have too little power or too little score.
Example 2:

Input: tokens = [100,200], P = 150
Output: 1
Explanation: Play the 0th token (100) face up, your power becomes 50 and score becomes 1.
There is no need to play the 1st token since you cannot play it face up to add to your score.
Example 3:

Input: tokens = [100,200,300,400], P = 200
Output: 2
Explanation: Play the tokens in this order to get a score of 2:
1. Play the 0th token (100) face up, your power becomes 100 and score becomes 1.
2. Play the 3rd token (400) face down, your power becomes 500 and score becomes 0.
3. Play the 1st token (200) face up, your power becomes 300 and score becomes 1.
4. Play the 2nd token (300) face up, your power becomes 0 and score becomes 2.
 

Constraints:

0 <= tokens.length <= 1000
0 <= tokens[i], P < 104

*/

#include <vector>
#include <algorithm>

using std::vector;


class BagOfTokensScore {

    /*
        948.Bag-of-Tokens
        本题的大体思路是，我们先将tokens排序，优先用手头的P去收购面值最小的tokens[i]，等到手头的P不够用了怎么办？我们将当前手头最小的token[i]兑换成1个point再去兑换面值最大的token[j]，
        这样空手套白狼，就将手头的P又凭空增加了token[j]．但代价有两个：第一是我们少了一个point；第二是我们失去未来收购面值最大的token[j]的机会．

        所以，总体的最优策略已经出来了．那就是按照上面的方法，手头的Ｐ按从小到大能收购多少token那就收购，不能收购就卖掉面值减去1分（卖掉最小的token）换面值最大的，增值手头的Ｐ．然后重复上述过程．整个流程中，手头曾持有最多的token的数量，就是答案．

        核心的代码如下：

                while (i<=j)  // 保证手头待买入的i必须在待替换的j之前
                {
                    if (P>=tokens[i])   // 仍然有钱买入
                    {
                        P-=tokens[i];
                        i++;
                        points++;
                        result = max(result,points);
                    }
                    else if (points>0)  // 没钱买了，但是仍有分可以卖
                    {
                        points--;
                        P+=tokens[j];
                        j--;
                    }
                    else                // 既不能买，也不能卖，策略结束
                        break;
                }
    */
    int bagOfTokensScore(vector<int>& tokens, int P) 
    {
        std::sort(tokens.begin(),tokens.end());
        int i = 0;
        int j = tokens.size()-1;
        int score = 0;
        int result = 0;
        
        while (i<=j)
        {
            if (P>=tokens[i])
            {
                P-=tokens[i];
                i++;
                score++;
                result = std::max(result,score);
            }
            else if (score>0)
            {
                score--;
                P+=tokens[j];
                j--;
            }
            else
                break;
        }
        
        return result;
    }


public:

    int doit_greedy(vector<int>& tokens, int P) {
        
        std::sort(begin(tokens), end(tokens));
        
        int low = 0, high = tokens.size()-1;
        int score = 0, ans = 0;
        
        while (low <= high && (P >= tokens[low] || score > 0)) {
            
            while (low <= high && P >= tokens[low]) {
                P -= tokens[low++];
                score++;
            }
            
            ans = std::max(ans, score);
            
            if (low <= high && score > 0) {
                P += tokens[high--];
                score--;
            }
        }
        
        return ans;
    }
};