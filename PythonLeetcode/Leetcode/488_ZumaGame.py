

# 488. Zuma Game

# Think about Zuma Game. You have a row of balls on the table, colored red(R), yellow(Y), blue(B), green(G), and white(W).
# You also have several balls in your hand.

# Each time, you may choose a ball in your hand, and insert it into the row (including the leftmost place and rightmost place).
# Then, if there is a group of 3 or more balls in the same color touching, remove these balls. Keep doing this until no more balls can be removed.

# Find the minimal balls you have to insert to remove all the balls on the table. If you cannot remove all the balls, output -1.

# Examples:

# Input: "WRRBBW", "RB"
# Output: -1
# Explanation: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW

# Input: "WWRRBBWW", "WRBRW"
# Output: 2
# Explanation: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW -> empty

# Input:"G", "GGGGG"
# Output: 2
# Explanation: G -> G[G] -> GG[G] -> empty 

# Input: "RBYYBBRRB", "YRBGB"
# Output: 3
# Explanation: RBYYBBRRB -> RBYY[Y]BBRRB -> RBBBRRB -> RRRB -> B -> B[B] -> BB[B] -> empty 

# Note:
# You may assume that the initial row of balls on the table won�t have any 3 or more consecutive balls with the same color.
# The number of balls on the table won't exceed 20, and the string represents these balls is called "board" in the input.
# The number of balls in your hand won't exceed 5, and the string represents these balls is called "hand" in the input.
# Both input strings will be non-empty and only contain characters 'R','Y','B','G','W'.


class findMinStep(object):
    

    def doit(self, board, hand):
        """
        :type board: str
        :type hand: str
        :rtype: int
        """
        def longestConsecutive(board):
            start, s, e = 0, 0, 0

            for i in range(len(board)):
                if board[i] != board[start]:
                    start = i

                if i-start > e-s:
                    s,e = start,i

            return (s,e)

        def minStep(board):

            i, n, localMin = 0, len(board), float('inf')
            if n==0: 
                return 0

            start,end = longestConsecutive(board)
            if end-start > 1:
                return minStep(board[:start]+board[end+1:])

            while i < n:
                ball, step = board[i], 1 if i < n-1 and board[i] == board[i+1] else 2

                if hm[ball] >= step:
                    hm[ball] -= step
                    ms = minStep(board[:i] + board[i+3-step:])
                    localMin = min(localMin, (step + ms) if ms != -1 else localMin)
                    hm[ball] += step

                i += 3-step

            return localMin if localMin != float('inf') else -1
        
        hm = collections.defaultdict(int)
        for b in hand: 
            hm[b] += 1

        return minStep(board)


    def doit1(self, board, hand):
        """
        :type board: str
        :type hand: str
        :rtype: int
        """
        def removeTouchBalls(content):
            if len(content) < 3:
                return content

            i, last = 0, 0
            while i <= len(content):
                if i == len(content) or content[i] != content[last]:
                    if i - last > 2:
                        content = content[:last] + content[i:]
                        i, last = 0, 0
                    else:
                        last = i
                i += 1

            return content

        def search(tables, balls):

            if tables == "":
                return 0
            
            A = (tables, balls) 
            if A in D:
                return D[(tables, balls)]

            group = set(tables)
            if len(group) == 1 and len(tables) > 2:
                D[(tables, balls)] = 0
                return D[(tables, balls)]

            
            tables = removeTouchBalls(tables)
            if not tables:
                return 0

            if not balls:
                D[(tables, balls)] = float('inf')
                return D[(tables, balls)]

            res = float('inf')            
            ballsGroup = set(balls)
            for c in ballsGroup:
                j = balls.find(c)
                i = 0
                while True:
                    i = tables.find(c*2, i)
                    if i == -1:
                        break;
                    res = min( res , search(tables[:i] + tables[i+2:], balls[:j] + balls[j+1:]) + 1)
                    i += 2

                i = 0
                while True:
                    i = tables.find(c, i)
                    if i == -1:
                        break 
                    if (i + 1 == len(tables) or tables[i+1] != c):
                        res = min( res, search(tables[:i] + c + tables[i:], balls[:j] + balls[j+1:]) + 1)
                    i += 1

            D[A] = res               
            return res                            
                    
        D = {}
        res = search(board, hand)            
        return -1 if res == float('inf') else res     

             
            
        



if __name__=="__main__":

    
    res = findMinStep().doit("WRRBBW", "RB") # -1

    res = findMinStep().doit("WWRRBBWW", "WRBRW") # 2

    res = findMinStep().doit("G", "GGGGG") # 2

    res = findMinStep().doit("RBYYBBRRB", "YRBGB") # 3

    res = findMinStep().doit("WWGWGW", "GWBWR") #3

    res = findMinStep().doit("RWYWRRWRR", "YRY") #3

    res = findMinStep().doit("YYGGRRYYGGYYGY", "RGG") #2

    pass


    

    



    