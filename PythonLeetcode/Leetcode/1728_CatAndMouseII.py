"""
1728. Cat and Mouse II


A game is played by a cat and a mouse named Cat and Mouse.

The environment is represented by a grid of size rows x cols, where each element is a wall, floor, player (Cat, Mouse), or food.

Players are represented by the characters 'C'(Cat),'M'(Mouse).
Floors are represented by the character '.' and can be walked on.
Walls are represented by the character '#' and cannot be walked on.
Food is represented by the character 'F' and can be walked on.
There is only one of each character 'C', 'M', and 'F' in grid.
Mouse and Cat play according to the following rules:

Mouse moves first, then they take turns to move.
During each turn, Cat and Mouse can jump in one of the four directions (left, right, up, down). They cannot jump over the wall nor outside of the grid.
catJump, mouseJump are the maximum lengths Cat and Mouse can jump at a time, respectively. Cat and Mouse can jump less than the maximum length.
Staying in the same position is allowed.
Mouse can jump over Cat.
The game can end in 4 ways:

If Cat occupies the same position as Mouse, Cat wins.
If Cat reaches the food first, Cat wins.
If Mouse reaches the food first, Mouse wins.
If Mouse cannot get to the food within 1000 turns, Cat wins.
Given a rows x cols matrix grid and two integers catJump and mouseJump, return true if Mouse can win the game if both Cat and Mouse play optimally, otherwise return false.

 

Example 1:



Input: grid = ["####F","#C...","M...."], catJump = 1, mouseJump = 2
Output: true
Explanation: Cat cannot catch Mouse on its turn nor can it get the food before Mouse.
Example 2:



Input: grid = ["M.C...F"], catJump = 1, mouseJump = 4
Output: true
Example 3:

Input: grid = ["M.C...F"], catJump = 1, mouseJump = 3
Output: false
Example 4:

Input: grid = ["C...#","...#F","....#","M...."], catJump = 2, mouseJump = 5
Output: false
Example 5:

Input: grid = [".M...","..#..","#..#.","C#.#.","...#F"], catJump = 3, mouseJump = 1
Output: true
 

Constraints:

rows == grid.length
cols = grid[i].length
1 <= rows, cols <= 8
grid[i][j] consist only of characters 'C', 'M', 'F', '.', and '#'.
There is only one of each character 'C', 'M', and 'F' in grid.
1 <= catJump, mouseJump <= 8

"""

class CatAndMouseII:

    def doit_(self, grid: list, catJump: int, mouseJump: int) -> bool:
        import functools
        m,n = len(grid), len(grid[0])
        block=0

        for i in range(m):
            for j in range(n):
                if grid[i][j]=='#': block+=1
                if grid[i][j]=='C': catPos0=(i,j)
                elif grid[i][j]=='M': mousePos0=(i,j)
                elif grid[i][j]=='F': foodPos=(i,j)
        maxTurn=(n*m-block-2)*2
        
        @functools.lru_cache(None)
        def move(mousePos,catPos,turn):

            if turn>maxTurn or mousePos==catPos or catPos==foodPos: return False

            if mousePos==foodPos: return True

            jump=[mouseJump,catJump][turn%2]
            curPos=[mousePos,catPos][turn%2]

            for di,dj in [(1,0),(0,1),(-1,0),(0,-1)]:

                for jumpStep in range(jump+1):

                    if not jumpStep and turn%2==0: # cat can stay, mouse must move
                        continue

                    i2,j2=curPos[0]+di*jumpStep,curPos[1]+dj*jumpStep

                    if i2>=m or i2<0 or j2>=n or j2<0 or grid[i2][j2]=='#':
                        break

                    mousePos2,catPos2=(mousePos,(i2,j2)) if turn%2==1 else ((i2,j2),catPos)
                    mouseWin=move(mousePos2,catPos2,turn+1)

                    if turn%2==0 and mouseWin: 
                        return True

                    if turn%2!=0 and not mouseWin:
                        return False

            return False if turn%2==0 else True

        return move(mousePos0,catPos0,0)