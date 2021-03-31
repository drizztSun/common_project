/*
1055. Shortest Way to Form String

From any string, we can form a subsequence of that string by deleting some number of characters (possibly no deletions).

Given two strings source and target, return the minimum number of subsequences of source such that their concatenation equals target. If the task is impossible, return -1.

 

Example 1:

Input: source = "abc", target = "abcbc"
Output: 2
Explanation: The target "abcbc" can be formed by "abc" and "bc", which are subsequences of source "abc".
Example 2:

Input: source = "abc", target = "acdbc"
Output: -1
Explanation: The target string cannot be constructed from the subsequences of source string due to the character "d" in target string.
Example 3:

Input: source = "xyz", target = "xzyxz"
Output: 3
Explanation: The target string can be constructed as follows "xz" + "y" + "xz".
 

Constraints:

Both the source and target strings consist of only lowercase English letters from "a"-"z".
The lengths of source and target string are between 1 and 1000.
*/
#include <string>

using std::string;

class ShortestWay {

    /*
        1055.Shortest-Way-to-Form-String
        本题的最优策略就是贪心。我们总试图在source里找到一个subsequence去匹配target的前几个字符。匹配完若干个字符后，就从头再在source里找subsequence去匹配target的接下来的几个字符。直至把target全部匹配完，或者source完全无法提供匹配。

        这样的解法有多种多样，但最优的写法可以做到o(N)级别。

        我们预先用o(26N)的时间来处理source。我们构建next[i][k]表示在source的第i个位置的下一个字符k在哪个位置。注意为了方便起见，我们将source调整为1-index。如果i的位置后面没有字符k，则令next[i][k]=-1.

        接下来我们遍历target，用i表示我们在source里寻找target的第i个字符，用j表示我们当前位于source里的位置。假设我们在source的位置j找到了target[i-1]，那么target[i]就应该位于next[j][target[i]]。于是接下来我们需要更新

        j = next[j][target[i]];
        注意，如果此时j=-1，表示我们已经搜完了一遍source但是没有找到匹配target[i]，此时需要重置j=0再在source中搜一轮。如果j!=-1，那么说明target[i]已经找到，可以i+=1.

        特别注意，当i前进至target.size()时，意味着轮数需要额外增加1.

        最终统计我们在source里面搜过了几轮，就是需要几个source的subsequence来拼接成target。
    */
    int next[1001][26];
public:
    int shortestWay(string source, string target) 
    {
        int n = source.size();
        source = "#" + source;
        
        for (int k=0; k<26; k++)
            next[n][k] = -1;
        
        for (int i=n-1; i>=0; i--)        
            for (int k=0; k<26; k++)
            {
                if (k == source[i+1]-'a')
                    next[i][k] = i+1;
                else
                    next[i][k] = next[i+1][k];                
            }
        
        int j = 0;
        int count = 0;
        for (int i=0; i<target.size();)
        {       
            if (next[0][target[i]-'a']==-1)
                return -1;
                        
            j = next[j][target[i]-'a'];
            
            if (j==-1)
            {
                j = 0;
                count++;                    
            }            
            else if ( j!= -1)  
            {                
                i += 1;
                if (i==target.size())
                {
                    count++;
                    break;
                }                    
            }    
        }
        return count;        
    }

public:
    
    int doit_greedy_twopointer(string source, string target) {
        int count = 0;
        int i = 0 ; 
        int j = 0;

        while(i < target.length())
        {
            int start = j;
            while(j < source.length() && source[j] != target[i])
                j++;

            if(start == 0 && j == source.length())
                return -1;

            if(j != source.length() && source[j] == target[i])
            {
                j++;
                i++;
                if(i == target.length() && j < source.length())
                    count++;
            }
            
            if(j == source.length())
            {
                j = 0;
                count++;
            }
        }
        return count;
    }
};