/*
 488. Zuma Game
 
 
 Think about Zuma Game. You have a row of balls on the table, colored red(R), yellow(Y), blue(B), green(G), and white(W). You also have several balls in your hand.

 Each time, you may choose a ball in your hand, and insert it into the row (including the leftmost place and rightmost place).
 Then, if there is a group of 3 or more balls in the same color touching, remove these balls. Keep doing this until no more balls can be removed.

 Find the minimal balls you have to insert to remove all the balls on the table. If you cannot remove all the balls, output -1.

  

 Example 1:

 Input: board = "WRRBBW", hand = "RB"
 Output: -1
 Explanation: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW
 Example 2:

 Input: board = "WWRRBBWW", hand = "WRBRW"
 Output: 2
 Explanation: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW -> empty
 Example 3:

 Input: board = "G", hand = "GGGGG"
 Output: 2
 Explanation: G -> G[G] -> GG[G] -> empty
 Example 4:

 Input: board = "RBYYBBRRB", hand = "YRBGB"
 Output: 3
 Explanation: RBYYBBRRB -> RBYY[Y]BBRRB -> RBBBRRB -> RRRB -> B -> B[B] -> BB[B] -> empty
  

 Constraints:

 You may assume that the initial row of balls on the table won’t have any 3 or more consecutive balls with the same color.
 1 <= board.length <= 16
 1 <= hand.length <= 5
 Both input strings will be non-empty and only contain characters 'R','Y','B','G','W'.
 */
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

using std::unordered_map;
using std::vector;
using std::string;


class ZumaGame {
    
    /*
    
        488.Zuma-Game
        解法1
        此题并没有太多的技巧，就是暴力的深度搜索，遍历每次取的hand ball、以及它在board中可以插入的位置，更新得到newboard和newhand，然后不停地调用DFS(newboard,newhand)即可。

        可以剪枝的地方有两处：

        手头的hand里面如果有若干个球是同色的话，那么只需要考察其中一个即可。也就是说，DFS的时候只遍历hand里面不同色的球。
        选定了一个hand ball之后，那么它在board里插入的位置也不是随意的。显然，如果将hand ball插入board里同色的位置肯定是较优的。也就是说对于hand[i]和board的位置j，如果board[j]!=hand[i]那么就直接跳过。

        解法2
        跟上面的解法不同，有另外一种DFS的写法。基本框架不变，但是在分支的思路上不一样。解法1，是遍历手头的ball，再遍历所有它适合插入的位置，这是一个两层的遍历。但在下面这个更高效的解法中，我们遍历所有可以插入的位置，然后查看是否手头有足够的球能使得这个位置上产生三连消。

        这样的思想依据是：对于任何一个ZUMA Game的初始board，在消除的过程中，不管情况多复杂，最后必然会引发第一个引爆点。比如说WBBRRW，第一个引爆点可能是W(WW)BBRRW，条件是你手头有两个W；也可能是WBB(B)RRW，条件是你手头有一个B；又有可能是WBBRR(R)W，条件是你手头有一个R；也有可能是W(WW)BBRRW(WW)，条件还是你手头有两个W。如果相应的条件满足，这些位置都有可能是第一个引爆点。为什么只关心引爆点呢，因为你即使先做了其他操作，使得乱如WXBXXBXRRXW，最终还是会引爆的，而引爆的一个导火索，就是最初WBBRRW中的某个元素。

        于是你分支去DFS，进入不同的平行时空，再考察下一个层级下的第一个引爆点...因此类推，依然是一个常规的DFS。但是效率会大大提高。

        ======================================================

        注意下面这个case，OJ给的标准答案是错误的。很不幸，这里的解答也都是错误的。这个case太NB了，我服气，
    */
    int result;
    
    int findMinStep(string board, string hand) 
    {
        result = INT_MAX;
        unordered_map<char,int>Hand;
        for (auto x:hand) Hand[x]++;
        
        DFS(board,Hand,0);
        if (result==INT_MAX) return -1;
        else return result;
    }
    
    void DFS(string board, unordered_map<char,int>&Hand, int curCount)
    {
        
        if (board=="")
        {
            result = min(result,curCount);
            return;
        }
        if (curCount>=result) return;
            
        for (auto elem: Hand)
        {
            
            if (elem.second==0) continue;
            char c = elem.first;
            
            Hand[c]--;
                        
            for (int i=0; i<board.size(); i++)
            {
                if (board[i]!=c) continue;
                if (i>0 && board[i]==board[i-1]) continue;
                
                string newBoard = board;
                newBoard.insert(i,1,c);
                
                newBoard = clean(newBoard);
                DFS(newBoard, Hand, curCount+1);
            }
            
            Hand[c]++;
            
        }
    }
    
    string clean(string s)
    {
        string t="";
        while (1)
        {
            t = "";
            for (int i=0; i<s.size(); i++)
            {
                int i0=i;
                while (i<s.size() && s[i]==s[i0]) i++;
                if (i-i0<3)
                    t = t+s.substr(i0,i-i0);
                i--;
            }
            if (t==s) return t;
            s = t;
        }
        
        return s;
    }

public:

    int result;

    int findMinStep(string board, string hand) 
    {
        result = INT_MAX;
        unordered_map<char,int>Hand;
        for (auto x:hand) Hand[x]++;
        
        DFS(board,Hand,0);
        if (result==INT_MAX) return -1;
        else return result;
    }
    
    void DFS(string board, unordered_map<char,int>&Map, int curCount)
    {
        if (board=="")
        {
            result = std::min(result,curCount);
            return;
        }
        if (curCount>=result) return;
        
        for (int i=0; i<board.size(); i++)
        {
            int i0=i;
            while (i<board.size() && board[i]==board[i0]) i++;
            if (3-(i-i0) <= Map[board[i0]])
            {
                string newBoard = board.substr(0,i0)+board.substr(i);
                newBoard = clean(newBoard);
                Map[board[i0]] -= (3-(i-i0));
                DFS(newBoard, Map, curCount+(3-(i-i0)));
                    
                Map[board[i0]] += (3-(i-i0));    
            }
            i--;
        }   
    }
    
    string clean(string s)
    {
        string t="";
        while (1)
        {
            t = "";
            for (int i=0; i<s.size(); i++)
            {
                int i0=i;
                while (i<s.size() && s[i]==s[i0]) i++;
                if (i-i0<3)
                    t = t+s.substr(i0,i-i0);
                i--;
            }
            if (t==s) return t;
            s = t;
        }
        return s;
    }

    
public:

    int findMinStep(string board, string hand) {
        vector<int> h(128, 0);
        for (char color : hand) ++h[color];
        return dfs(board, h);
    }

    // Return the min # of balls needed in hand to clear the board.
    // Returns -1 if not possible.
    int dfs(const string& board, vector<int>& hand) {
        if (board.empty()) return 0;
        
        int ans = INT_MAX;
        int i = 0;
        int j = 0;
        while (i < board.size()) {
            while (j < board.size() && board[i] == board[j]) ++j;
            // board[i] ~ board[j - 1] have the same color
            const char color = board[i];
            // Number of balls needed to clear board[i] ~ board[j - 1]
            const int b = 3 - (j - i);
            // Have sufficient balls in hand
            if (hand[color] >= b) {
                // Remove board[i] ~ board[j - 1] and update the board
                string nb = update(board.substr(0, i) + board.substr(j));
                // Find the solution on new board with updated hand
                hand[color] -= b;
                int r = dfs(nb, hand);
                if (r >= 0) ans = std::min(ans, r + b);
                // Recover the balls in hand
                hand[color] += b;
            }
            i = j;
        }
        return ans == INT_MAX ? -1 : ans;
    }
    
    // Update the board by removing all consecutive 3+ balls.
    // "YWWRRRWWYY" -> "YWWWWYY" -> "YYY" -> ""
    string update(string board) {
        int i = 0;
        while (i < board.size()) {
            int j = i;
            while (j < board.size() && board[i] == board[j]) ++j;
            if (j - i >= 3) {
                board = board.substr(0, i) + board.substr(j);
                i = 0;
            } else {
                ++i;
            }
        }
        return board;
    }
    
    
public:
    
    /*
        "RRWWRRBBRR"
        "WB"

        Failed on conor case.
    */
    int doit_dfs(string board, string hand) {

        int cnt[26] = {0};
        char base = 'A';
        for (auto c : hand) {
            cnt[c-base]++;
        }

        std::function<string(string)> update = [&](string path) {
            
            for (int i = 0; i < path.size(); i++) {
                
                int j = i;
                while (j < path.size() && path[j] == path[i]) j++;
                
                if (j - i >= 3) {
                    path = path.substr(0, i) + path.substr(j);
                    i = 0;
                } else
                    i++;
            }
            return path;
        };
        
        std::function<int(string)> dfs = [&](string path) {
            
            if (path.size() == 0)
                return 0;
            
            int res = INT_MAX;
            
            for (auto i = 0; i < path.size(); i++){
                
                int j = i;
                while (j < path.size() && path[j] == path[i]) j++;
                
                int c = path[i]-base;
                int b = 3- (j - i);
                
                
                if (cnt[c] >= b) {
                    
                    string nexttarget = update(path.substr(0, i) + path.substr(j));
                    
                    cnt[c] -= b;
                    
                    int ans = dfs(nexttarget);
                    if (ans > 0 ) res = std::min(res, ans + b);
                    
                    cnt[c] += b;
                }
                i = j;
            }
            
            
            return res == INT_MAX ? -1 : res;
        };
        

        
        return dfs(board);
    }
};
