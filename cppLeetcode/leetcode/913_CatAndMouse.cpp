/*
 
 # 913. Cat and Mouse

 # A game on an undirected graph is played by two players, Mouse and Cat, who alternate turns.

 # The graph is given as follows: graph[a] is a list of all nodes b such that ab is an edge of the graph.

 # Mouse starts at node 1 and goes first, Cat starts at node 2 and goes second, and there is a Hole at node 0.

 # During each player's turn, they must travel along one edge of the graph that meets where they are.
 # For example, if the Mouse is at node 1, it must travel to any node in graph[1].

 # Additionally, it is not allowed for the Cat to travel to the Hole (node 0.)

 # Then, the game can end in 3 ways:

 # If ever the Cat occupies the same node as the Mouse, the Cat wins.
 # If ever the Mouse reaches the Hole, the Mouse wins.
 # If ever a position is repeated (ie. the players are in the same position as a previous turn, and it is the same player's turn to move), the game is a draw.
 # Given a graph, and assuming both players play optimally, return 1 if the game is won by Mouse, 2 if the game is won by Cat, and 0 if the game is a draw.


 # Example 1:

 # Input: [[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
 # Output: 0
 # Explanation:
 # 4---3---1
 # |   |
 # 2---5
 #  \ /
 #   0


 """
 Approach 1: Minimax / Percolate from Resolved States
 Intuition

 The state of the game can be represented as
 (m, c, t)
 where m is the location of the mouse,
 c is the location of the cat,
 and t is 1 if it is the mouse's move, else 2.

 Let's call these states nodes. These states form a directed graph:
 the player whose turn it is has various moves which can be considered as outgoing edges from this node to other nodes.

 Some of these nodes are already resolved:
 if the mouse is at the hole (m = 0), then the mouse wins; if the cat is where the mouse is (c = m), then the cat wins.
 Let's say that nodes will either be colored:
 MOUSE, CAT, or DRAW depending on which player is assured victory.

 As in a standard minimax algorithm,
 the Mouse player will prefer MOUSE nodes first, DRAW nodes second, and CAT nodes last,

 and the Cat player prefers these nodes in the opposite order.

 Algorithm

 We will color each node marked 'DRAW' according to the following rule.
 (We'll suppose the node has node.turn = Mouse: the other case is similar.)

 1) ("Immediate coloring"): If there is a child that is colored 'MOUSE', then this node will also be colored 'MOUSE'.

 2) ("Eventual coloring"): If all children are colored 'CAT', then this node will also be colored 'CAT'.

 We will repeatedly do this kind of coloring until no node satisfies the above conditions.
 To perform this coloring efficiently, we will use a queue and perform a bottom-up percolation:

 1) Enqueue any node initially colored (because the Mouse is at the Hole, or the Cat is at the Mouse.)

 2) For every node in the queue, for each parent of that node:

     1. Do an immediate coloring of parent if you can.

     2. If you can't, then decrement the side-count of the number of children marked 'DRAW'.
     If it becomes zero, then do an "eventual coloring" of this parent.

     3. All parents that were colored in this manner get enqueued to the queue.

 Proof of Correctness

 Our proof is similar to a proof that minimax works.

 Say we cannot color any nodes any more, and say from any node colored 'CAT' or 'MOUSE' we need at most K moves to win.
 If say, some node marked 'DRAW' is actually a win for Mouse, it must have been with > K moves.
 Then, a path along optimal play (that tries to prolong the loss as long as possible) must arrive at a node colored
 'MOUSE' (as eventually the Mouse reaches the Hole.) Thus, there must have been some transition 'DRAW' => 'MOUSE' along this path.

 If this transition occurred at a node with node.turn = Mouse, then it breaks our immediate coloring rule.
 If it occured with node.turn = Cat, and all children of node have color 'MOUSE', then it breaks our eventual coloring rule.
 If some child has color "CAT", then it breaks our immediate coloring rule.
 Thus, in this case node will have some child with 'DRAW', which breaks our optimal play assumption,
 as moving to this child ends the game in > K moves, whereas moving to the colored neighbor ends the game in ≤K moves.

 Complexity Analysis

 Time Complexity: O(N^3), where NN is the number of nodes in the graph.
 There are O(N^2) states, and each state has an outdegree of N, as there are at most N different moves.

 Space Complexity: O(N^2).
 """
 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <deque>
#include <queue>
#include <array>

using std::vector;
using std::unordered_map;
using std::deque;
using std::queue;
using std::array;

namespace std
{
template <>
struct hash<std::pair<int, int>>
{
    inline size_t operator()(const std::pair<int, int> &a) const
    {
        std::hash<int> hashint;
        return hashint(a.first) ^ hashint(a.second);
    }
};
} // namespace std

class CatMouseGame {

public:

    /*
        913.Cat-and-Mouse
        此题是game thoery中的好题．看上去像常规的minMax问题，但实际上几乎所有的DFS解法都是不完备的，参看leetcode的讨论区．

        正确的解法是用BFS.我们设计节点状态是(m,c,turn)，用color[m][c][turn]来记忆该状态的输赢情况．

        首先我们将所有已知的状态加入一个队列．已知状态包括(0,c,turn)肯定是老鼠赢，(x,x,turn)且x!=0肯定是猫赢．我们尝试用BFS的思路，将这些已知状态向外扩展开去．

        扩展的思路是：从队列中取出队首节点状态（m,c,t），找到它的所有邻接的parent的状态（m2,c2,t2）．这里的父子关系是指，(m2,c2,t2)通过t2轮（老鼠或猫）的操作，能得到(m,c,t).我们发现，
        如果(m,c,t)是老鼠赢而且t2是老鼠轮，那么这个(m2,c2,t2)一定也是老鼠赢．同理，猫赢的状态也类似．于是，我们找到了一种向外扩展的方法．

        向外扩展的第二个思路是：对于(m2,c2,t2)，我们再去查询它的所有children（必定是对手轮）是否都已经标注了赢的状态．如果都是赢的状态，那么说明(m2,c2,t2)无路可走，
        只能标记为输的状态．特别注意的是，第一条规则通过child找parent，和第二条规则通过parent找child的算法细节是不一样的，一定要小心．

        这样我们通过BFS不断加入新的探明输赢的节点．直到队列为空，依然没有探明输赢的节点状态，就是平局的意思！
    */
    
    int color[50][50][3];

    int catMouseGame(vector<vector<int>>& graph) 
    {
        int N = graph.size();
                
        queue<vector<int>>q;
        for (int i=0; i<N; i++)
            for (int turn=1; turn<=2; turn++)
            {
                color[0][i][turn] = 1;  // mouse win conditions
                q.push({0,i,turn});
                
                if (i!=0)               
                {
                    color[i][i][turn] = 2;  // cat win conditions
                    q.push({i,i,turn});
                }
            }
        
        while (!q.empty()) {
                
            int m = q.front()[0]; 
            int c = q.front()[1];
            int t = q.front()[2];            
            int status = color[m][c][t];
            q.pop();
                        
            for (auto nextNode: findAllParents(graph,m,c,t)) {

                int m2 = nextNode[0];
                int c2 = nextNode[1];
                int t2 = nextNode[2];
                
                if (color[m2][c2][t2]!=0) continue; // has been determined
                
                if (t2==status)   // immediate win, (m2,c2,t2)->(m,c,t)
                {
                    color[m2][c2][t2] = status;
                    q.push({m2,c2,t2});                    
                }
                else if (allChildrenWin(graph, m2,c2,t2))    // eventually lose
                {
                    color[m2][c2][t2] = (t2==1)? 2:1;
                    q.push({m2,c2,t2});                
                }                
            }
        }
        return color[1][2][1];
    }
    
    
    vector<vector<int>> findAllParents(vector<vector<int>>& graph, int m, int c, int t)
    {
        vector<vector<int>>neighbours;
        if (t==1)
        {
            for (int c_next: graph[c])
                if (c_next!=0) neighbours.push_back({m,c_next,2});
        }
        else
        {
            for (int m_next: graph[m])
                neighbours.push_back({m_next,c,1});
        }
        return neighbours;
    }
    
    bool allChildrenWin(vector<vector<int>>& graph, int m, int c, int t)
    {
        if (t==1)
        {
            for (int m_next: graph[m])
                if (color[m_next][c][2]!=2)
                    return false;
        }
        else if (t==2)
        {
            for (int c_next: graph[c])
                if (c_next!=0 && color[m][c_next][1]!=1)
                    return false;
        }
        return true;
    }

    //----------------------

    int doit(vector<vector<int>> &&graph)
    {

        int N = graph.size();
        int Draw = 0, Mouse = 1, Cat = 2;

        auto parents = [&graph](int m, int c, int t) {
            vector<std::tuple<int, int, int>> pa;
            if (t == 2)
                for (auto mx : graph[m])
                    pa.push_back({mx, c, 1});
            else
                for (auto cx : graph[c])
                    if (cx != 0)
                        pa.push_back({m, cx, 2});
            return pa;
        };

        unordered_map<std::pair<int, int>, vector<int>> color;
        unordered_map<std::pair<int, int>, vector<int>> degree;

        for (int c = 0; c < N; c++)
        {
            for (int m = 0; m < N; m++)
            {
                if (degree[{m, c}].empty())
                    degree[{m, c}].resize(3);

                degree[{m, c}][1] = graph[m].size();
                degree[{m, c}][2] = graph[c].size();
                for (auto s : graph[c])
                {
                    if (s == 0)
                    {
                        degree[{m, c}][2]--;
                        break;
                    }
                }
            }
        }

        deque<std::tuple<int, int, int, int>> queue;
        for (int i = 0; i < N; i++)
            for (auto t : vector<int>{0, 1, 2})
            {
                if (color[{0, i}].empty())
                    color[{0, i}].resize(3);

                color[{0, i}][t] = Mouse;
                queue.push_back({0, i, t, Mouse});

                if (i > 0)
                {
                    if (color[{i, i}].empty())
                        color[{i, i}].resize(3);
                    color[{i, i}][t] = Cat;
                    queue.push_back({i, i, t, Cat});
                }
            }

        while (!queue.empty())
        {
            auto top = queue.front();
            int m = std::get<0>(top), c = std::get<1>(top), t = std::get<2>(top), win = std::get<3>(top);

            for (auto &n : parents(m, c, t))
            {
                int pm = std::get<0>(n), pc = std::get<1>(n), pt = std::get<2>(n);

                if (color[{pm, pc}].empty())
                    color[{pm, pc}].resize(3);

                if (color[{pm, pc}][pt] == Draw)
                {
                    if (pt == win)
                    {
                        color[{pm, pc}][pt] = win;
                        queue.push_back({pm, pc, pt, win});
                    }
                    else
                    {
                        degree[{pm, pc}][pt] -= 1;
                        if (degree[{pm, pc}][pt] == 0)
                        {
                            color[{pm, pc}][pt] = win;
                            queue.push_back({pm, pc, pt, win});
                        }
                    }
                }
            }

            queue.pop_front();
        }

        return color[{1, 2}][1];
    }
};

/*
 
 First you need understand the N position and P postion from Combinatorial Game Theory.
 P-Position is previous player win, N-Position is next player (current player) win.
 A position is a N-Position as long as one of its following positions is P-Position, i.e. if current player take this move, in next turn he as the previous player is guaranteed to win.
 A position is a P-Position only if all its following positions are N-Position, i.e. no matter how current player move, the previous player is guaranteed to win in next turn.

 The algorithm:

 1. Initalize cat win or mouse win final states:
 Mouse Win: mouse is at the hole.
 Cat Win: cat is over mouse.
 Push them into a queue.
 
 2. Pop out a known state from queue:
 a. N-positon. If it's a mouse win, mark the connected neighbor node's mouse turn as mouse win.
 If it's a cat win, mark the connected neighbor node's cat turn as cat win.
 
 b. P-position, topological sort. Since current node as a child of the neighbor has been check, we reduce the indegree of the other turn of the neighbor by 1.
 By "other turn of the neighbor", it means if it's mouse win, reduce indegree of cat turn of neighbor by 1. If the indegree of the other turn of the neighbor becomes 0, means the neighbor in this state has no choice (P position).
 How about draw? Because in every step, we only count into definite winning state (cat or mouse win), so if a node's degree reduced to 0, all it's children must be in a definite winning state, that's why above P position assertion is correct.
 */

class CatMouseGame1
{

public:
    int doit(vector<vector<int>> &graph)
    {
        const int n = graph.size();
        vector<vector<int>> v_rat(n, vector<int>(n, 0)), v_cat(n, vector<int>(n, 0));

        for (int r = 0; r < n; ++r)
            v_rat[r][r] = -1, v_cat[r][r] = 1;

        for (int c = 0; c < n; ++c)
            v_rat[0][c] = 1, v_cat[0][c] = -1;

        for (int t = 0; t < n; ++t)
        {

            for (int r = 1; r < n; ++r)
            {
                for (int c = 1; c < n; ++c)
                {
                    if (c == r)
                        continue;
                    int max_val = -2;
                    for (int i : graph[r])
                    {
                        max_val = std::max(max_val, -v_cat[i][c]);
                        if (-v_cat[i][c] == 1)
                            break;
                    }
                    v_rat[r][c] = max_val;
                }
            }

            for (int c = 1; c < n; ++c)
            {
                for (int r = 1; r < n; ++r)
                {
                    if (c == r)
                        continue;
                    int max_val = -2;
                    for (int j : graph[c])
                    {
                        if (j == 0)
                            continue;
                        max_val = std::max(max_val, -v_rat[r][j]);
                        if (max_val == 2)
                            break;
                    }
                    v_cat[r][c] = max_val;
                }
            }
        }

        if (v_rat[1][2] == -1)
            return 2;
        else if (v_rat[1][2] == 1)
            return 1;
        else
            return 0;
    }

public:
    int doit3(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<vector<vector<char>>> states(n, vector<vector<char>>(n, vector<char>(2, Draw)));
        vector<vector<vector<int>>> indegree(n, vector<vector<int>>(n, vector<int>(2)));
        queue<vector<int>> q;
        for (int i = 0; i < n; i++)
        {
            if (0 != i)
            {
                states[0][i][MTurn] = states[0][i][CTurn] = MWin;
                q.emplace(vector<int>{0, i, MTurn, (int)MWin});
                q.emplace(vector<int>{0, i, CTurn, (int)MWin});
                states[i][i][MTurn] = states[i][i][CTurn] = CWin;
                q.emplace(vector<int>{i, i, MTurn, (int)CWin});
                q.emplace(vector<int>{i, i, CTurn, (int)CWin});
            }
            for (int j = 0; j < n; j++)
            {
                indegree[i][j][MTurn] = graph[i].size(); // when the mouse is at i, the cat is at j, and it's mouse's turn, how many routes the mouse can go.
                indegree[i][j][CTurn] = graph[j].size(); // when the mouse is at i, the cat is at j, and it's cat's turn, how many routes the cat can go.
                if (find(graph[j].begin(), graph[j].end(), 0) != graph[j].end())
                    indegree[i][j][CTurn]--; // cat cannot move to the hole, so 0 cannot be considered as a route for cat.
            }
        }

        while (!q.empty())
        {
            int m_pos = q.front()[0], c_pos = q.front()[1], turn = q.front()[2], result = q.front()[3];
            q.pop();
            int prev_turn = !turn;
            if (MTurn == prev_turn)
            { // previous turn is mouse's turn
                for (auto &i : graph[m_pos])
                {
                    if (Draw == states[i][c_pos][prev_turn])
                    {
                        if (MWin == result)
                        { // N-position, the mouse found a way to escape
                            states[i][c_pos][prev_turn] = MWin;
                        }
                        else
                        {
                            indegree[i][c_pos][prev_turn]--; // this way is blocked by the cat
                            if (0 == indegree[i][c_pos][prev_turn])
                                states[i][c_pos][prev_turn] = CWin; // P-position, the mouse has no choices
                        }
                        if (Draw != states[i][c_pos][prev_turn])
                        {
                            q.emplace(vector<int>{i, c_pos, prev_turn, (int)states[i][c_pos][prev_turn]});
                        }
                    }
                }
            }
            else
            { // previous turn is cat's turn
                for (auto &i : graph[c_pos])
                {
                    if (0 == i)
                        continue; // cat cannot be at the hole!!
                    if (Draw == states[m_pos][i][prev_turn])
                    {
                        if (CWin == result)
                        { // N-position, the cat is guaranteed to catch the mouse in next step
                            states[m_pos][i][prev_turn] = CWin;
                        }
                        else
                        {
                            indegree[m_pos][i][prev_turn]--; // the mouse can escape if the cat take this move
                            if (0 == indegree[m_pos][i][prev_turn])
                                states[m_pos][i][prev_turn] = MWin; // P-position, the cat has no choices
                        }
                        if (Draw != states[m_pos][i][prev_turn])
                        {
                            q.emplace(vector<int>{m_pos, i, prev_turn, (int)states[m_pos][i][prev_turn]});
                        }
                    }
                }
            }
        }
        return states[1][2][MTurn];
    }

private:
    const int MTurn = 0;
    const int CTurn = 1;
    const char Draw = 0;
    const char MWin = 1;
    const char CWin = 2;

public:
    int dp(vector<vector<int>> &&graph)
    {

        int n = graph.size();
        std::vector<std::vector<int>> dp(2, std::vector<int>(n * n, 0));
        std::queue<std::vector<int>> q; // [0] turn, [1] mouse, [2] cat

        for (int i = 0; i < n; ++i)
        {
            // mouse is 0 or cat is 0, Mouse win is 1.
            dp[0][i] = 1;
            dp[1][i] = 1;
            dp[0][n * i] = 1;
            dp[1][n * i] = 1;
            q.push({1, 0, i});
        }

        for (int i = 1; i < n; ++i)
        {
            // any mouse i and car i, Cat win is 2
            dp[0][n * i + i] = 2;
            dp[1][n * i + i] = 2;
            q.push({1, i, i});
            q.push({0, i, i});
        }

        while (!q.empty())
        {
            int s = q.size();

            for (int c = 0; c < s; ++c)
            {

                auto const &v = q.front();
                int k(v[0]), i(v[1]), j(v[2]); // k is turn, i Mouse, j Cat

                int w = k == 0 ? j : i;  // k == 0, W is Cat. k == 1, W is mouse. last step's turn
                int &u = k == 0 ? j : i; // k == 1, it is cat turn

                for (size_t d = 0; d < graph[w].size(); ++d)
                { // list all parent node

                    u = graph[w][d]; // w's parent node

                    if (dp[k ^ 1][n * i + j] == 0)
                    { // k^1 turn and at i,j is draw, we check each node's parent node

                        bool bl(false);
                        if (dp[k][n * v[1] + v[2]] % 2 != k)
                        { //v[0],v[1] is a losing position for current player.
                            int a(i), b(j);
                            int &x = k == 0 ? b : a;
                            for (int e = 0; e < graph[u].size(); ++e)
                            {
                                x = graph[u][e];
                                if (dp[k][n * a + b] != dp[k][n * v[1] + v[2]])
                                {
                                    bl = true;
                                    break;
                                }
                            }
                        }

                        if (!bl)
                        {
                            //setting cat or mouse winning position: bl is false when
                            //current player has the choice to go to already known winning position,
                            // or current player has no choice other than to go to losing position.
                            dp[k ^ 1][n * i + j] = dp[k][n * v[1] + v[2]];
                            if (k ^ 1 == 0 && i == 1 && j == 2)
                                return dp[k ^ 1][n * i + j];
                            q.push({k ^ 1, i, j});
                        }
                    }
                }
                q.pop();
            }
        }

        return 0;
    }
};

// so far best one
class CatMouseGameIII
{
public:
    int doit(vector<vector<int>> && graph)
    {
        int n = graph.size();
        vector<vector<array<unsigned long, 2>>> adj_cnt(n, vector<array<unsigned long, 2>>(n));
        // adj_cnt[mouse position][cat position][0/1 = mouse/cat to move]
        // is the number of possibly non-losing moves for current player
        // (if zero, means the state has been solved)

        for (auto i = 0; i < n; ++i)
            for (auto j = 0; j < n; ++j)
                adj_cnt[i][j] = {graph[i].size(), graph[j].size()};

        deque<std::pair<array<int, 2>, std::pair<bool, bool>>> q;
        // {{mouse pos, cat pos}, {0/1 = mouse/cat, 0/1 = current/previous player wins}}

        for (auto i = 1; i < n; ++i)
        {
            q.push_back({{i, i}, {0, 1}});
            q.push_back({{i, i}, {1, 0}});
            q.push_back({{0, i}, {1, 1}}); // if mouse reaches 0, it's cat's turn to move and it loses
            q.push_back({{i, 0}, {0, 0}}); // if cat reaches 0 (invalid move), it's mouse's turn to move and it wins
            adj_cnt[i][i] = {0, 0};
            adj_cnt[0][i] = adj_cnt[i][0] = {0, 0};
            // mark all these states as solved
        }

        while (!q.empty())
        {
            auto sz = q.size();
            for (auto i = 0; i < sz; ++i)
            {
                auto entry = q[0];
                q.pop_front();
                bool curr_player, prev_win;
                std::tie(curr_player, prev_win) = entry.second;

                entry.second.first ^= true, entry.second.second ^= true; // considering last move, switch player and winning side
                auto &lpp_ref = entry.first[!curr_player];               // location of previous player
                auto lpp = lpp_ref;
                // current status has been resolved
                for (auto j : graph[lpp])
                {
                    // retrograde expansion, generate all possible previous state
                    lpp_ref = j;
                    auto &table_entry = adj_cnt[entry.first[0]][entry.first[1]][!curr_player]; // check parent status, if it is 0, solved, or then we check
                    if (table_entry)
                    {
                        if (prev_win || --table_entry == 0)
                        { // found one winning move, or all moves have been marked losing
                            table_entry = 0, q.push_back(entry);
                            if (curr_player && entry.first[0] == 1 && entry.first[1] == 2) // initial state is marked
                                return prev_win ? 1 : 2;
                        }
                    }
                }
            }
        }
        return 0;
        // the initial state belongs to the set of states that are never marked as solved.
        // For each state in this set, the current player can either choose a losing move, or a move that again lands in a state in this set.
        // So the best outcome is a draw.
        // (After making a losing move, the winning strategy of the other player won't make use of any state in the never-marked set.)
    }
};

void test_939_CatAndMouse()
{

    auto res = CatMouseGameIII().doit(vector<vector<int>>{{2, 5}, {3}, {0, 4, 5}, {1, 4, 5}, {2, 3}, {0, 2, 3}});

    auto res1 = CatMouseGameIII().doit(vector<vector<int>>{{1, 3}, {0}, {3}, {0, 2}});
}
