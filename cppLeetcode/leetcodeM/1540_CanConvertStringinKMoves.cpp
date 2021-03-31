/*
1540. Can Convert String in K Moves

Given two strings s and t, your goal is to convert s into t in k moves or less.

During the ith (1 <= i <= k) move you can:

    . Choose any index j (1-indexed) from s, such that 1 <= j <= s.length and j has not been chosen in any previous move, and shift the character at that index i times.
    . Do nothing.

Shifting a character means replacing it by the next letter in the alphabet (wrapping around so that 'z' becomes 'a'). Shifting a character by i means applying the shift operations i times.

Remember that any index j can be picked at most once.

Return true if it's possible to convert s into t in no more than k moves, otherwise return false.

 

Example 1:

Input: s = "input", t = "ouput", k = 9
Output: true
Explanation: In the 6th move, we shift 'i' 6 times to get 'o'. And in the 7th move we shift 'n' to get 'u'.
Example 2:

Input: s = "abc", t = "bcd", k = 10
Output: false
Explanation: We need to shift each character in s one time to convert it into t. We can shift 'a' to 'b' during the 1st move. However, there is no way to shift the other characters in the remaining moves to obtain t from s.
Example 3:

Input: s = "aab", t = "bbb", k = 27
Output: true
Explanation: In the 1st move, we shift the first 'a' 1 time to get 'b'. In the 27th move, we shift the second 'a' 27 times to get 'b'.
 

Constraints:

1 <= s.length, t.length <= 10^5
0 <= k <= 10^9
s, t contain only lowercase English letters.

*/
#include <string>
#include <vector>

using std::vector;
using std::string;


class CanConvertString {

    /*
        1536.Minimum-Swaps-to-Arrange-a-Binary-Grid
        本题先进行一下转换。将每行末尾的零的个数统计一下，得到数组zeros，即zeros[i]表示第i行末尾的零的个数。我们的目标是将zeros通过adjacent swap操作，变成一个数组target，其中target[i]>=n-1-i. 求最小的操作数。

        我们首先考虑target[0]，它的要求最高（需要有n-1个零）。我们考察所有的行，看看有哪些满足条件。加入有a和b两行满足条件，即zeros[a]>=n-1，zeros[b]>=n-1，那么我们应该选择将哪一行挪到第0行的位置上来呢？我们不妨举个例子：

        X X X a X b X
        如果我们选择将第b行提到最前面，那么需要操作5次得到

        b X X X a X X   (1)
        如果我们选择将第a行提到最前面，那么需要操作3次得到

        a X X X X b X   (2)
        别停，我们如果对(2)继续操作1次（将b前移一位）能得到

        a X X X b X X   (3)
        我们比较一下(1)和(3)。我们发现对于第0行的处理，两种方案都满足条件。唯一的区别是，第一种方案第4行是zeros[a]，第二种方案第4行是zeros[b]。但是由于zeros[a]和zeros[b]都是大于等于n-1的，而除了target[0]之外的target[i]的要求都不到n-1，所以这两行（a和b）对于以后的安排而言都是“溢价”的，即“价值”是没有区别的。但是第一种方案需要5次操作，第二种方案只需要4次操作。

        所以我们得到一个贪心的结论：当我们处理target[i]时需要找某个zeros[j]>=n-1-i时，只要从i开始往后顺次查找第一个满足zeros[j]>=n-1-i的位置即可。然后将j所对应的行提前到第i行。然后处理target[i+1]，不断重复。
    */
    int minSwaps(vector<vector<int>>& grid) 
    {
        int n = grid.size();
        vector<int>zeros(n);
        for (int i=0; i<n; i++)
        {
            int count = 0;
            for (int j=n-1; j>=0; j--)
            {
                if (grid[i][j]!=0)
                    break;
                count++;
            }
            zeros[i] = count;            
        }
        
        int count = 0;
        for (int i=0; i<n-1; i++)
        {
            int num = n-1-i;
            int j = i;
            for (; j<n; j++)
            {
                if (zeros[j]>=num)
                    break;
            }
            if (j==n) return -1;
            count += j-i;
            int temp = zeros[j];
            for (int k=j; k>i; k--)
                zeros[k] = zeros[k-1];
            zeros[i] = temp;
        }
        
        return count;
    }
    
public:
    
    bool doit_greedy(string s, string t, int k) {
        
        if (s.length() != t.length()) return false;
        
        vector<int> available(26, k/26);
        k %=26;
        for (int i = 0; i <=k; i++) available[i]++;
        
        vector<int> needs(26, 0);
        for (int i = 0; i < s.length(); i++)
            needs[(t[i] - s[i] + 26) % 26]++;
        
        for (int i = 1; i < 26; i++)
            if (needs[i] > available[i]) return false; 
        
        return true;

    }
};