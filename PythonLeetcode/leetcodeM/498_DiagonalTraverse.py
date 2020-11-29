"""
498. Diagonal Traverse


Given a matrix of M x N elements (M rows, N columns), return all elements of the matrix in diagonal order as shown in the below image.



Example:

Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]

Output:  [1,2,4,7,5,3,6,8,9]

Explanation:



Note:

The total number of elements of the given matrix will not exceed 10,000.




"""


class DiagonalOrder:

    """
    Algorithm

    Initialize a result array that we will eventually return.

    We would have an outer loop that will go over each of the diagonals one by one.
    As mentioned before, the elements in the first row and the last column would actually be the heads of their corresponding diagonals.

    We then have an inner while loop that iterates over all the elements in the diagonal. We can calculate the number of elements in the corresponding diagonal by doing some math
    but we can simply iterate until one of the indices goes out of bounds.

    For each diagonal we will need a new list or dynamic array like data structure since we don't know what size to allocate.
    Again, we can do some math and calculate the size of that particular diagonal and allocate memory; but it's not necessary for this explanation.

    For odd numbered diagonals, we simply need to add the elements in our intermediary array, in reverse order to the final result array.

    """
    def doit(self, matrix: list) -> list:

        # Check for empty matrices
        if not matrix or not matrix[0]:
            return []

        # Variables to track the size of the matrix
        N, M = len(matrix), len(matrix[0])

        # The two arrays as explained in the algorithm
        result, intermediate = [], []

        # We have to go over all the elements in the first
        # row and the last column to cover all possible diagonals
        for d in range(N + M - 1):

            # Clear the intermediate array everytime we start
            # to process another diagonal
            intermediate.clear()

            # We need to figure out the "head" of this diagonal
            # The elements in the first row and the last column
            # are the respective heads.
            r, c = 0 if d < M else d - M + 1, d if d < M else M - 1

            # Iterate until one of the indices goes out of scope
            # Take note of the index math to go down the diagonal
            while r < N and c > -1:
                intermediate.append(matrix[r][c])
                r += 1
                c -= 1

            # Reverse even numbered diagonals. The
            # article says we have to reverse odd
            # numbered articles but here, the numbering
            # is starting from 0 :P
            if d % 2 == 0:
                result.extend(intermediate[::-1])
            else:
                result.extend(intermediate)
        return result

    def doit_simulation(self, matrix: list) -> list:

        # Check for an empty matrix
        if not matrix or not matrix[0]:
            return []

        # The dimensions of the matrix
        N, M = len(matrix), len(matrix[0])

        # Incides that will help us progress through
        # the matrix, one element at a time.
        row, column = 0, 0

        # As explained in the article, this is the variable
        # that helps us keep track of what direction we are
        # processing the current diaonal
        direction = 1

        # Final result array that will contain all the elements
        # of the matrix
        result = []

        # The uber while loop which will help us iterate over all
        # the elements in the array.
        while row < N and column < M:

            # First and foremost, add the current element to
            # the result matrix.
            result.append(matrix[row][column])

            # Move along in the current diagonal depending upon
            # the current direction.[i, j] -> [i - 1, j + 1] if
            # going up and [i, j] -> [i + 1][j - 1] if going down.
            new_row = row + (-1 if direction == 1 else 1)
            new_column = column + (1 if direction == 1 else -1)

            # Checking if the next element in the diagonal is within the
            # bounds of the matrix or not. If it's not within the bounds,
            # we have to find the next head.
            if new_row < 0 or new_row == N or new_column < 0 or new_column == M:

                # If the current diagonal was going in the upwards
                # direction.
                if direction:

                    # For an upwards going diagonal having [i, j] as its tail
                    # If [i, j + 1] is within bounds, then it becomes
                    # the next head. Otherwise, the element directly below
                    # i.e. the element [i + 1, j] becomes the next head
                    row += (column == M - 1)
                    column += (column < M - 1)
                else:

                    # For a downwards going diagonal having [i, j] as its tail
                    # if [i + 1, j] is within bounds, then it becomes
                    # the next head. Otherwise, the element directly below
                    # i.e. the element [i, j + 1] becomes the next head
                    column += (row == N - 1)
                    row += (row < N - 1)

                # Flip the direction
                direction = 1 - direction
            else:
                row = new_row
                column = new_column

        return result

    def doit(self, matrix: list) -> list:

        if not matrix or not matrix[0]:
            return []

        M, N = len(matrix), len(matrix[0])
        ascend = True
        i, j = 0, 0
        res = []

        while len(res) < M * N:

            res.append(matrix[i][j])

            if ascend and (i == 0 or j == N - 1):
                if j == N - 1:
                    i += 1
                else:
                    j += 1
                ascend = not ascend

            elif not ascend and (j == 0 or i == M - 1):
                if i == M - 1:
                    j += 1
                else:
                    i += 1
                ascend = not ascend

            else:
                if not ascend:
                    i += 1
                    j -= 1
                else:
                    i -= 1
                    j += 1

        return res


if __name__ == '__main__':

    DiagonalOrder().doit([
                         [ 1, 2, 3 ],
                         [ 4, 5, 6 ],
                         [ 7, 8, 9 ]
                        ])