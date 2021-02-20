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
import collections


class CatMouseGame:

    """
        Approach 1: Minimax / Percolate from Resolved States
        Intuition

        The state of the game can be represented as (m, c, t) where m is the location of the mouse, c is the location of the cat, and t is 1 if it is the mouse's move, else 2. Let's call these states nodes. 
        These states form a directed graph: the player whose turn it is has various moves which can be considered as outgoing edges from this node to other nodes.

        Some of these nodes are already resolved: if the mouse is at the hole (m = 0), then the mouse wins; if the cat is where the mouse is (c = m), then the cat wins. 
        Let's say that nodes will either be colored \small\text{MOUSE}MOUSE, \small\text{CAT}CAT, or \small\text{DRAW}DRAW depending on which player is assured victory.

        As in a standard minimax algorithm, the Mouse player will prefer \small\text{MOUSE}MOUSE nodes first, \small\text{DRAW}DRAW nodes second, and \small\text{CAT}CAT nodes last, and the Cat player prefers these nodes in the opposite order.

        Algorithm

        We will color each node marked \small\text{DRAW}DRAW according to the following rule. (We'll suppose the node has node.turn = Mouse: the other case is similar.)

        ("Immediate coloring"): If there is a child that is colored \small\text{MOUSE}MOUSE, then this node will also be colored \small\text{MOUSE}MOUSE.

        ("Eventual coloring"): If all children are colored \small\text{CAT}CAT, then this node will also be colored \small\text{CAT}CAT.

        We will repeatedly do this kind of coloring until no node satisfies the above conditions. To perform this coloring efficiently, we will use a queue and perform a bottom-up percolation:

        Enqueue any node initially colored (because the Mouse is at the Hole, or the Cat is at the Mouse.)

        For every node in the queue, for each parent of that node:

        Do an immediate coloring of parent if you can.

        If you can't, then decrement the side-count of the number of children marked \small\text{DRAW}DRAW. If it becomes zero, then do an "eventual coloring" of this parent.

        All parents that were colored in this manner get enqueued to the queue.

        Proof of Correctness

        Our proof is similar to a proof that minimax works.

        Say we cannot color any nodes any more, and say from any node colored \small\text{CAT}CAT or \small\text{MOUSE}MOUSE we need at most KK moves to win. 
        If say, some node marked \small\text{DRAW}DRAW is actually a win for Mouse, it must have been with > K>K moves. 
        Then, a path along optimal play (that tries to prolong the loss as long as possible) must arrive at a node colored \small\text{MOUSE}MOUSE (as eventually the Mouse reaches the Hole.) 
        Thus, there must have been some transition \small\text{DRAW} \rightarrow \small\text{MOUSE}DRAW→MOUSE along this path.

        If this transition occurred at a node with node.turn = Mouse, then it breaks our immediate coloring rule. If it occured with node.turn = Cat, and all children of node have color \small\text{MOUSE}MOUSE, then it breaks our eventual coloring rule. 
        If some child has color \small\text{CAT}CAT, then it breaks our immediate coloring rule. Thus, in this case node will have some child with \small\text{DRAW}DRAW, which breaks our optimal play assumption, 
        as moving to this child ends the game in > K>K moves, whereas moving to the colored neighbor ends the game in \leq K≤K moves.

        Complexity Analysis

        Time Complexity: O(N^3), where NN is the number of nodes in the graph. There are O(N^2) states, and each state has an outdegree of NN, as there are at most NN different moves.

        Space Complexity: O(N^2)
    """
    def doit_minimax(self, graph):
        N = len(graph)

        # What nodes could play their turn to
        # arrive at node (m, c, t) ?
        def parents(m, c, t):
            if t == 2:
                for m2 in graph[m]:
                    yield m2, c, 3-t
            else:
                for c2 in graph[c]:
                    if c2:
                        yield m, c2, 3-t

        DRAW, MOUSE, CAT = 0, 1, 2
        color = collections.defaultdict(int)

        # degree[node] : the number of neutral children of this node
        # t is 1 if it is the mouse's move, else 2.
        degree = {}
        for m in range(N):
            for c in range(N):
                degree[m, c, 1] = len(graph[m])
                degree[m, c, 2] = len(graph[c]) - (0 in graph[c])

        # enqueued : all nodes that are colored
        queue = collections.deque([])
        for i in range(N):
            for t in range(1, 3):
                color[0, i, t] = MOUSE
                queue.append((0, i, t, MOUSE))
                if i > 0:
                    color[i, i, t] = CAT
                    queue.append((i, i, t, CAT))

        # percolate
        while queue:
            # for nodes that are colored :
            i, j, t, c = queue.popleft()
            # for every parent of this node i, j, t :
            for i2, j2, t2 in parents(i, j, t):
                # if this parent is not colored :
                if color[i2, j2, t2] is DRAW:
                    # if the parent can make a winning move (ie. mouse to MOUSE), do so
                    if t2 == c:  # winning move
                        color[i2, j2, t2] = c
                        queue.append((i2, j2, t2, c))
                    # else, this parent has degree[parent]--, and enqueue if all children
                    # of this parent are colored as losing moves
                    else:
                        degree[i2, j2, t2] -= 1
                        if degree[i2, j2, t2] == 0:
                            color[i2, j2, t2] = 3 - t2
                            queue.append((i2, j2, t2, 3 - t2))

        return color[1, 2, 1]

    """
        913.Cat-and-Mouse
        此题是game thoery中的好题．看上去像常规的minMax问题，但实际上几乎所有的DFS解法都是不完备的，参看leetcode的讨论区．

        正确的解法是用BFS.我们设计节点状态是(m,c,turn)，用color[m][c][turn]来记忆该状态的输赢情况．

        首先我们将所有已知的状态加入一个队列．已知状态包括(0,c,turn)肯定是老鼠赢，(x,x,turn)且x!=0肯定是猫赢．我们尝试用BFS的思路，将这些已知状态向外扩展开去．

        扩展的思路是：从队列中取出队首节点状态（m,c,t），找到它的所有邻接的parent的状态（m2,c2,t2）．这里的父子关系是指，(m2,c2,t2)通过t2轮（老鼠或猫）的操作，能得到(m,c,t).我们发现，
        如果(m,c,t)是老鼠赢而且t2是老鼠轮，那么这个(m2,c2,t2)一定也是老鼠赢．同理，猫赢的状态也类似．于是，我们找到了一种向外扩展的方法．

        向外扩展的第二个思路是：对于(m2,c2,t2)，我们再去查询它的所有children（必定是对手轮）是否都已经标注了赢的状态．如果都是赢的状态，
        那么说明(m2,c2,t2)无路可走，只能标记为输的状态．特别注意的是，第一条规则通过child找parent，和第二条规则通过parent找child的算法细节是不一样的，一定要小心．

        这样我们通过BFS不断加入新的探明输赢的节点．直到队列为空，依然没有探明输赢的节点状态，就是平局的意思！
    """
    def catMouseGame(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: int
        """
        N = len(graph)
        color = [[[0]*3 for _ in range(N)] for _ in range(N)]        
        q = collections.deque()
        for i in range(1,N):            
            for t in range(1,3):                
                color[0][i][t] = 1
                q.append((0,i,t))                                                
                color[i][i][t] = 2                
                q.append((i,i,t))
        
        while (q):
            curStatus = q.popleft()            
            cat,mouse,turn = curStatus
            
            for prevStatus in self.findAllPrevStatus(graph,curStatus):
                
                if color[prevStatus[0]][prevStatus[1]][prevStatus[2]]!=0: continue
                
                # immediate win for prevStatus
                if color[cat][mouse][turn]==3-turn:
                    color[prevStatus[0]][prevStatus[1]][prevStatus[2]] = prevStatus[2]
                    q.append(prevStatus)
                
                # forced to lose for prevStatus
                elif self.allNeighboursWin(color,graph,prevStatus):
                    color[prevStatus[0]][prevStatus[1]][prevStatus[2]] = 3-prevStatus[2]
                    q.append(prevStatus)
            
        return color[1][2][1]
    
    def findAllPrevStatus(self,graph,curStatus):
        ret = []
        mouse,cat,turn = curStatus
        if turn==1:
            for prevCat in graph[cat]:
                if prevCat==0: continue
                ret.append((mouse,prevCat,2))
        else:
            for prevMouse in graph[mouse]:
                ret.append((prevMouse,cat,1))
        return ret
    
    def allNeighboursWin(self,color,graph,status):
        mouse,cat,turn = status
        if turn==1:
            for nextMouse in graph[mouse]:                
                if color[nextMouse][cat][2]!=2:
                    return False
        elif turn==2:            
            for nextCat in graph[cat]:
                if nextCat==0: continue
                if color[mouse][nextCat][1]!=1:
                    return False
        return True
    

    def doit1(self, graph):

        MOUSE, CAT, DRAW = 1, 2, 0
        l = len(graph)
        origin_status = (1, 2, MOUSE)
        status_value = dict()
        queue = collections.deque()
        for i in range(1, l):
            queue.append((i, i, MOUSE))
            queue.append((i, i, CAT))
            status_value[(i, i, MOUSE)] = CAT
            status_value[(i, i, CAT)] = CAT

            queue.append((0, i, MOUSE))
            queue.append((0, i, CAT))
            status_value[(0, i, MOUSE)] = MOUSE
            status_value[(0, i, CAT)] = MOUSE

        while len(queue) != 0:
            mouse_pos, cat_pos, turn = queue.popleft()
            if turn == MOUSE:
                for pre_cat_pos in graph[cat_pos]:
                    if pre_cat_pos != 0:
                        pre_status = (mouse_pos, pre_cat_pos, CAT)
                        if pre_status not in status_value:
                            values = [status_value[(mouse_pos, nxt_cat_pos, MOUSE)] for nxt_cat_pos in
                                      graph[pre_cat_pos] if (mouse_pos, nxt_cat_pos, MOUSE) in status_value]
                            if CAT in values:
                                status_value[pre_status] = CAT
                                queue.append(pre_status)
                            elif len(values) == (
                            len(graph[pre_cat_pos]) - 1 if 0 in graph[pre_cat_pos] else len(graph[pre_cat_pos])):
                                status_value[pre_status] = MOUSE
                                queue.append(pre_status)
            else:
                for pre_mouse_pos in graph[mouse_pos]:
                    pre_status = (pre_mouse_pos, cat_pos, MOUSE)
                    if pre_status not in status_value:
                        values = [status_value[(nxt_mouse_pos, cat_pos, CAT)] for nxt_mouse_pos in graph[pre_mouse_pos]
                                  if (nxt_mouse_pos, cat_pos, CAT) in status_value]
                        if MOUSE in values:
                            status_value[pre_status] = MOUSE
                            queue.append(pre_status)
                        elif len(values) == len(graph[pre_mouse_pos]):
                            status_value[pre_status] = CAT
                            queue.append(pre_status)

            if origin_status in status_value:
                return status_value[origin_status]

        return DRAW


if __name__ == '__main__':

    res = CatMouseGame().doit1([[2, 5], [3], [0, 4, 5], [1, 4, 5], [2, 3], [0, 2, 3]])  # 0

    res = CatMouseGame().doit1([[1,3],[0],[3],[0,2]]) # 1