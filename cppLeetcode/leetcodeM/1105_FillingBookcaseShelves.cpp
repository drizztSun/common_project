/*
 
 1105. Filling Bookcase Shelves
 
 
 We have a sequence of books: the i-th book has thickness books[i][0] and height books[i][1].

 We want to place these books in order onto bookcase shelves that have total width shelf_width.

 We choose some of the books to place on this shelf (such that the sum of their thickness is <= shelf_width), then build another level of shelf of the bookcase
 so that the total height of the bookcase has increased by the maximum height of the books we just put down.  We repeat this process until there are no more books to place.

 Note again that at each step of the above process, the order of the books we place is the same order as the given sequence of books.
 For example, if we have an ordered list of 5 books, we might place the first and second book onto the first shelf, the third book on the second shelf, and the fourth and fifth book on the last shelf.

 Return the minimum possible height that the total bookshelf can be after placing shelves in this manner.



 Example 1:


 Input: books = [[1,1],[2,3],[2,3],[1,1],[1,1],[1,1],[1,2]], shelf_width = 4
 Output: 6
 Explanation:
 The sum of the heights of the 3 shelves are 1 + 3 + 2 = 6.
 Notice that book number 2 does not have to be on the first shelf.


 Constraints:

 1 <= books.length <= 1000
 1 <= books[i][0] <= shelf_width <= 1000
 1 <= books[i][1] <= 1000
 
 
 */
#include <vector>


using std::vector;


class MinHeightShelves {

public:
    int doit_dp(vector<vector<int>>& books, int shelf_width) {
        
        auto N = books.size();
        
        vector<int> dp(N, INT_MAX);
        
        for (auto i = 0; i < N; i++) {
            
            int max_height = 0, width = 0;
            
            for (auto j = i; j > -1; j--) {
                
                max_height = std::max(max_height, books[j][1]);
                width += books[j][0];
                
                if (width > shelf_width)
                    break;
                
                dp[i] = std::min(dp[i], (j > 0 ? dp[j-1] : 0) + max_height);
            }
        }
        
        return dp[dp.size()-1];
    }
};
