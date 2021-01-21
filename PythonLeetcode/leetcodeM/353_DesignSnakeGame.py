"""
353. Design Snake Game

Design a Snake game that is played on a device with screen size height x width. Play the game online if you are not familiar with the game.

The snake is initially positioned at the top left corner (0, 0) with a length of 1 unit.

You are given an array food where food[i] = (ri, ci) is the row and column position of a piece of food that the snake can eat. When a snake eats a piece of food, its length and the game's score both increase by 1.

Each piece of food appears one by one on the screen, meaning the second piece of food will not appear until the snake eats the first piece of food.

When a piece of food appears on the screen, it is guaranteed that it will not appear on a block occupied by the snake.

The game is over if the snake goes out of bounds (hits a wall) or if its head occupies a space that its body occupies after moving (i.e. a snake of length 4 cannot run into itself).

Implement the SnakeGame class:

SnakeGame(int width, int height, int[][] food) Initializes the object with a screen of size height x width and the positions of the food.
int move(String direction) Returns the score of the game after applying one direction move by the snake. If the game is over, return -1.
 

Example 1:


Input
["SnakeGame", "move", "move", "move", "move", "move", "move"]
[[3, 2, [[1, 2], [0, 1]]], ["R"], ["D"], ["R"], ["U"], ["L"], ["U"]]
Output
[null, 0, 0, 1, 1, 2, -1]

Explanation
SnakeGame snakeGame = new SnakeGame(3, 2, [[1, 2], [0, 1]]);
snakeGame.move("R"); // return 0
snakeGame.move("D"); // return 0
snakeGame.move("R"); // return 1, snake eats the first piece of food. The second piece of food appears
                     // at (0, 1).
snakeGame.move("U"); // return 1
snakeGame.move("L"); // return 2, snake eats the second food. No more food appears.
snakeGame.move("U"); // return -1, game over because snake collides with border
 

Constraints:

1 <= width, height <= 104
1 <= food.length <= 50
food[i].length == 2
0 <= ri < height
0 <= ci < width
direction.length == 1
direction is 'U', 'D', 'L', or 'R'.
At most 104 calls will be made to move.

"""
from collections import deque


class SnakeGameI:

    def __init__(self, width: int, height: int, food: list):
        """
        Initialize your data structure here.
        @param width - screen width
        @param height - screen height 
        @param food - A list of food positions
        E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0].
        """
        self._body = deque([(0, 0)])
        self._moves = {'U': (-1, 0), 'L': (0, -1), 'R': (0, 1), 'D': (1, 0)}
        self._bodylength = 1
        self._food = food
        self._bodyset = set()
        self._bodyset.add((0, 0))
        self._height = height
        self._width = width
        
    def move(self, direction: str) -> int:
        """
        Moves the snake.
        @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down 
        @return The game's score after the move. Return -1 if game over. 
        Game over when snake crosses the screen boundary or bites its body.
        """
        x = self._body[0][0] + self._moves[direction][0]
        y = self._body[0][1] + self._moves[direction][1]
        
        if x < 0 or x == self._height or y < 0 or y == self._width or (x, y) in self._bodyset:
            return -1
        
        if self._bodylength-1 < len(self._food) and x == self._food[self._bodylength-1][0] and y == self._food[self._bodylength-1][1]:
            self._bodylength += 1
        
        self._body.appendleft((x, y))
        self._bodyset.add((x, y))
        
        if len(self._body) > self._bodylength:
            self._bodyset.remove(self._body.pop())
        
        return self._bodylength - 1


"""
Approach: Queue and Hash Set
Intuition

Let's start by thinking about how we want to store the snake?

In terms of the grid, a snake is just an ordered collection of cells.

We can technically use an array to store the cells representing a snake. However, we would need to instantiate an array the size of width * height of the grid since a snake can be composed of all the the cells of the grid in the worst case. 
A spiral kind of a snake. Let's look at such a snake occupying the grid.


This structure is highly unlikely given the random nature of food items appearing on the grid. However, we would need an array the size of the grid to be able to hold this big a snake. 
The breaking point for an array is when we have to move the snake from one position to another. Let's see what happens to the snake when it moves by one in a direction. 
The result overall would be the same with some minor changes based on the direction.


In the above figure, we have a snake that occupies 4 cells across the grid or in other words, is of length 4. The snake can be represented by the following collection of cells: [(1,1), (1,2), (1,3), (2,3)]. 
Now say we have the snake move in the right direction i.e. R. The snake now would look like this across the grid.


Now here, after moving one step to the right, the snake is represented by the cells [(1,2), (1,3), (2,3), (2,4)].

In order to achieve this with an array, we would have to move all the cells around per move which is not exactly ideal.
We can build some complicated logic around the movement of the snake in an array but that won't be worth the fixed space complexity that an array would occupy.

Let's see what data structure would naturally fit our requirements for the snake. There are two basic requirements we need to satisfy:

Dynamically add new cells to the snake's body and
Move the snake in constant amount of time across the grid.
Let's look at the snake representation between moves from the example above to understand what really is happening here and that will help us get to the data structure we need to use for solving this problem.

Move with No Food

We already have an example for such a move so we will simply be looking at the snake representation on the grid to understand what's really happening here.

Before the move, the snake was occupying the following cells of the grid in the specified order:

(1,1), (1,2), (1,3), (2,3)
and after the move, the snake was occupying the following positions on the grid:

(1,2), (1,3), (2,3), (2,4)
If you think about this from a sliding window perspective, we simply moves the window one step forward i.e. we removed the tail of the window and added a new head to the window. The tail in this case was (1,2) and the new head being (2,4).

Move with Food Consumption

Now let's look at a move by the snake wherein they consume a food item and grow in length. Suppose the move was the same as before and the spot (2,4) contained a food item. The snake head from the previous example, was at (2,3) on the grid. So, a move to the right would cause them to consume this food item thus extending their overall length by one. So now, instead of occupying 4 cells on the grid, the snake would occupy 5 cells. Let's concretely look at the snake representations before and after the move.

Before the move, the snake was occupying the following cells of the grid in the specified order:

(1,1), (1,2), (1,3), (2,3)
and after the move, the snake was occupying the following positions on the grid:

(1,1), (1,2), (1,3), (2,3), (2,4)
Here, we simply added a new head to the snake with the head being the cell (2,4). The tail remained the same in this case. These are the only two possibilities for moves that can happen other than the termination conditions for the game. Based on them, let's see what operations out data structure needs to support concretely for us to be able to perform these moves efficiently.

Our abstract data structure needs to support the following operations efficiently.

Grow in size dynamically. Note that we never shrink in size. The snake can stay the same size as before or grow in size due to the consumption of a food item on the grid. But they can't shrink in size.
Maintain a specified ordering of cells in order to represent the snake.
Extract the tail cell and potentially add a new head cell to the ordering of cells to represent the updated snake post a move. This is the most important operation of all and this points to a very specific data structure.
Based on the third operation, we can see that the Queue would be a good data structure to use since we need to have quick access to the first and last elements of an ordered list and a queue gives us exactly that.

A queue is an abstract data structure with some specified properties which meets our requirements. It can be represented by an array or a linked list. For our purposes, since we need a data structure with dynamic sizing, we would go with a linked-list based implementation for a queue rather than an array since we don't want to pre-allocate any memory for the array and only allocate on the fly. A linked list would be a great fit here since we don't require random access to cells of the snake.

Algorithm

Initialize a queue containing a single cell (0,0) which is the initial position of the snake at the beginning of the game. Note that we will be doing this in the constructor of the class and not in the move function.

The fist thing we need to do inside the move function is to compute the new head based on the direction of the move. As we saw in the intuition section, irrespective of the kind of move, we will always get a new head. We need the new head position to determine if the snake has hit a boundary and hence, terminate the game.

Let's first discuss the termination conditions before moving on to the modifications we would make to our queue data structure.

The first condition is if the snake cross either of the boundaries of the grid after the mode, then we terminate. So for this, we simply check if the new head (new_head) satisfies new_head[0] < 0 or new_head[0] > height or new_head[1] < 0 or new_head[1] > width.
The second condition is if the snake bites itself after the move. An important thing to remember here is that the current tail of the snake is not a part of the snake's body. If the move doesn't involve a food, then the tail gets updated (removed) as we have seen. If this is a food move, then the snake cannot bite itself because the food cannot appear on any of the cells occupied by the snake (according to the problem statement).
In order to check if the snake bites itself we need to check if the new head already exists in our queue or not. This can turn out to be an \mathcal{O}(N)O(N) operation and that would be costly. So, at the expense of memory, we can also use an additional dictionary data structure to keep the positions of the snake. This dictionary will only be used for this particular check. We can't do with just a dictionary because a dictionary doesn't have an ordered list of elements and we need the ordering for our implementation.

If none of the termination conditions have been met, then we will continue to update our queue with the new head and potentially remove the old tail. If the new head lands on a position which contains food, then we simply add the new head to our queue representing the snake. We won't pop the tail in this case since the length of the snake has increased by 1.

After each move, we return the length of the snake if this was a valid move. Else, we return -1 to indicate that the game is over.
"""

class SnakeGame:

    def __init__(self, width: int, height: int, food: list):
        """
        Initialize your data structure here.
        @param width - screen width
        @param height - screen height 
        @param food - A list of food positions
        E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0].
        """
        self.snake = deque([(0,0)])    # snake head is at the front
        self.snake_set = {(0,0) : 1}
        self.width = width
        self.height = height
        self.food = food
        self.food_index = 0
        self.movement = {'U': [-1, 0], 'L': [0, -1], 'R': [0, 1], 'D': [1, 0]}
        

    def move(self, direction: str) -> int:
        """
        Moves the snake.
        @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down 
        @return The game's score after the move. Return -1 if game over. 
        Game over when snake crosses the screen boundary or bites its body.
        """
        
        newHead = (self.snake[0][0] + self.movement[direction][0], self.snake[0][1] + self.movement[direction][1])
        
        # Boundary conditions.
        crosses_boundary1 = newHead[0] < 0 or newHead[0] >= self.height
        crosses_boundary2 = newHead[1] < 0 or newHead[1] >= self.width
        
        # Checking if the snake bites itself.
        bites_itself = newHead in self.snake_set and newHead != self.snake[-1]
     
        # If any of the terminal conditions are satisfied, then we exit with rcode -1.
        if crosses_boundary1 or crosses_boundary2 or bites_itself:
            return -1

        # Note the food list could be empty at this point.
        next_food_item = self.food[self.food_index] if self.food_index < len(self.food) else None
        
        # If there's an available food item and it is on the cell occupied by the snake after the move, eat it
        if self.food_index < len(self.food) and next_food_item[0] == newHead[0] and next_food_item[1] == newHead[1]:  # eat food
            self.food_index += 1
        else:    # not eating food: delete tail                 
            tail = self.snake.pop()  
            del self.snake_set[tail]
            
        # A new head always gets added
        self.snake.appendleft(newHead)
        
        # Also add the head to the set
        self.snake_set[newHead] = 1

        return len(self.snake) - 1



if __name__ == '__main__':

    game = SnakeGameI(3, 2, [[1, 2], [0, 1]])

    game.move('R')
    game.move('D')
    game.move('R')
    game.move('U')
    game.move('L')
    game.move('U')


    game1 = SnakeGameI(3, 3, [[2,0],[0,0],[0,2],[2,2]])

    game1.move("D")
    game1.move("D")
    game1.move("R")
    game1.move("U")
    game1.move("U")
    game1.move("L")
    game1.move("D")
    game1.move("R")
    game1.move("R")
    game1.move("U")
    game1.move("L")
    game1.move("D")
