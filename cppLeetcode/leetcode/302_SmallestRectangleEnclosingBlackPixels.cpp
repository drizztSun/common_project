/*
302. Smallest Rectangle Enclosing Black Pixels

An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel. The black pixels are connected, i.e., there is only one black region. 
Pixels are connected horizontally and vertically. Given the location (x, y) of one of the black pixels, return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.

Example:

Input:
[
  "0010",
  "0110",
  "0100"
]
and x = 0, y = 2

Output: 6

*/

#include <vector>
#include <functional>

using std::vector;


class MinArea {

    /*
        302.Smallest-Rectangle-Enclosing-Black-Pixels
        立足所给的点(x,y)，划分整个区域为上半部分、下半部分、左半部分、右半部分。

        对于上半部分，从第0行到第x行进行二分搜索，找到第一个出现1的行 (该行的所有列中至少有一个1)。注意，因为right的初始值x已知是含有1的，所以需要选择搜索机制保证收敛时必为含有1的行。

            int UPPER(vector<vector<char>>& image,int RowMin, int RowMax, int ColMin, int ColMax)
            {
                int left = RowMin;
                int right = RowMax;
                int mid;
                while (left<right)
                {
                    mid = left+(right-left)/2;
                    int flag = 0;
                    for (int i=ColMin; i<=ColMax; i++)
                    {
                        if (image[mid][i]=='1')
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if (flag==0)
                        left = mid+1; //将不合格的行排除的搜索范围之外（没有1）
                    else
                        right = mid; // 保持右界始终是合格的行（含有1）
                }
                return left;  // 这样最终收敛的结果必定是合格的行，不必复查
        }
        同理，对于下半部分，从第x行到第M-1行进行二分搜索，找到最后一个出现1的行。

        对于左半部分，从第0列到第y列进行二分搜索，找到第一个出现1的列。

        对于右半部分，从第y列到第N-1列进行二分搜索，找到最后一个出现1的列。

        整个时间复杂度 o(4NlogN)

        对比：宽度遍历完整的1矩阵，o(N*N)    
    */
    int minArea(vector<vector<char>>& image, int x, int y) 
    {
        int M=image.size();
        int N=image[0].size();
        
        int upper = UPPER(image,0,x,0,N-1);
        int down = DOWN(image,x,M-1,0,N-1);
        int left = LEFT(image,0,M-1,0,y);
        int right = RIGHT(image,0,M-1,y,N-1);
        
        return (right-left+1)*(down-upper+1);

    }
    
    int UPPER(vector<vector<char>>& image,int RowMin, int RowMax, int ColMin, int ColMax)
    {
        int left = RowMin;
        int right = RowMax;
        int mid;
        while (left<right)
        {
            mid = left+(right-left)/2;
            int flag = 0;
            for (int i=ColMin; i<=ColMax; i++)
            {
                if (image[mid][i]=='1')
                {
                    flag = 1;
                    break;
                }
            }
            if (flag==0)
                left = mid+1;
            else
                right = mid;
        }
        return left;
    }
    
    int DOWN(vector<vector<char>>& image,int RowMin, int RowMax, int ColMin, int ColMax)
    {
        int left = RowMin;
        int right = RowMax;
        int mid;
        while (left<right)
        {
            mid = left+(right-left)/2+1;
            int flag = 0;
            for (int i=ColMin; i<=ColMax; i++)
            {
                if (image[mid][i]=='1')
                {
                    flag = 1;
                    break;
                }
            }
            if (flag==0)
                right = mid-1;
            else
                left = mid;
        }
        return left;
    }
    
    int LEFT(vector<vector<char>>& image,int RowMin, int RowMax, int ColMin, int ColMax)
    {
        int left = ColMin;
        int right = ColMax;
        int mid;
        while (left<right)
        {
            mid = left+(right-left)/2;
            int flag = 0;
            for (int i=RowMin; i<=RowMax; i++)
            {
                if (image[i][mid]=='1')
                {
                    flag = 1;
                    break;
                }
            }
            if (flag==1)
                right = mid;
            else
                left = mid+1;
        }
        return left;
    }    
    
    int RIGHT(vector<vector<char>>& image,int RowMin, int RowMax, int ColMin, int ColMax)
    {
        int left = ColMin;
        int right = ColMax;
        int mid;
        while (left<right)
        {
            mid = left+(right-left)/2+1;
            int flag = 0;
            for (int i=RowMin; i<=RowMax; i++)
            {
                if (image[i][mid]=='1')
                {
                    flag = 1;
                    break;
                }
            }
            if (flag==1)
                left = mid;
            else
                right = mid-1;
        }
        return left;
    }     



public:

    /*
        Approach 1: Naive Linear Search
        Intuition

        Traversal all the pixels. Keep the maximum and minimum values of black pixels coordinates.

        Algorithm

        We keep four boundaries, left, right, top and bottom of the rectangle. Note that left and top are inclusive while right and bottom are exclusive. We then traversal all the pixels and update the four boundaries accordingly.

        The recipe is following:

        Initialize left, right, top and bottom
        Loop through all (x, y) coordinates
        if image[x][y] is black
        left = min(left, x)
        right = max(right, x + 1)
        top = min(top, y)
        bottom = max(bottom, y + 1)
        Return (right - left) * (bottom - top)

        Complexity Analysis

        Time complexity : O(mn)O(mn). mm and nn are the height and width of the image.

        Space complexity : O(1)O(1). All we need to store are the four boundaries.
    */
    int doit_(vector<vector<char>>& image, int x, int y) {
        
        int top = x, bottom = x;
        int left = y, right = y;
        for (x = 0; x < image.size(); ++x) {
            for (y = 0; y < image[0].size(); ++y) {
                if (image[x][y] == '1') {
                    top = std::min(top, x);
                    bottom = std::max(bottom, x + 1);
                    left = std::min(left, y);
                    right = std::max(right, y + 1);
                }
            }
        }
        return (right - left) * (bottom - top);
    }

    /*
        Approach 2: DFS or BFS
        Intuition

        Explore all the connected black pixel from the given pixel and update the boundaries.

        Algorithm

        The naive approach did not use the condition that all the black pixels are connected and that one of the black pixels is given.

        A simple way to use these facts is to do an exhaustive search starting from the given pixel. Since all the black pixels are connected, 
        DFS or BFS will visit all of them starting from the given black pixel. The idea is similar to what we did for 200. Number of Island. Instead of many islands, we have only one island here, and we know one pixel of it.


        Complexity Analysis

        Time complexity : O(E) = O(B) = O(mn).
        Here EE is the number of edges in the traversed graph. BB is the total number of black pixels. Since each pixel have four edges at most, O(E) = O(B). In the worst case, O(B) = O(mn).

        Space complexity : O(V) = O(B) = O(mn).
        The space complexity is O(V) where V is the number of vertices in the traversed graph. In this problem O(V) = O(B). Again, in the worst case, O(B) = O(mn).

        Comment

        Although this approach is better than naive approach when BB is much smaller than mnmn, it is asymptotically the same as approach #1 when B is comparable to mn. And it costs a lot more auxiliary space.
    */
    int doit_bfs(vector<vector<char>>& image, int x, int y) {


        if(image.size() == 0 || image[0].size() == 0) return 0;

        int top = x,  bottom = x;
        int left = y, right = y;

        std::function<void(int x, int y)> dfs = [&](int x, int y) {
            if(x < 0 || y < 0 || x >= image.size() || y >= image[0].size() || image[x][y] == '0')
                return;
                
            image[x][y] = '0'; // mark visited black pixel as white
            top = std::min(top, x);
            bottom = std::max(bottom, x + 1);
            left = std::min(left, y);
            right = std::max(right, y + 1);

            dfs(x + 1, y);
            dfs(x - 1, y);
            dfs(x, y - 1);
            dfs(x, y + 1);
        };
        
        dfs(x, y);
        
        return (right - left) * (bottom - top);
    }
    


    /*
        Approach 3: Binary Search
        Intuition

        Project the 2D image into a 1D array and use binary search to find the boundaries.

        Algorithm

        matrix projection

        *Figure 1. Illustration of image projection.

        Suppose we have a 10 \times 1110×11 image as shown in figure 1, if we project each column of the image into an entry of row vector v with the following rule:

        v[i] = 1 if exists x such that image[x][i] = 1
        v[i] = 0 otherwise
        That is

        If a column has any black pixel it's projection is black otherwise white.

        Similarly, we can do the same for the rows, and project the image into a 1D column vector. The two projected vectors are shown in figure 1.

        Now, we claim the following lemma:

        Lemma

        If there are only one black pixel region, then in a projected 1D array all the black pixels are connected.

        Proof by contradiction

        Assume to the contrary that there are disconnected black pixels at i and j where i < j in the 1D projection array. Thus, there exists one column k, k in (i, j) and the column k in the 2D array has no black pixel. Therefore, in the 2D array there exist at least two black pixel regions separated by column k which contradicting the condition of "only one black pixel region". Therefore, we conclude that all the black pixels in the 1D projection array are connected.

        With this lemma, we have the following algorithm:

        Project the 2D array into a column array and a row array
        Binary search to find left in the row array within [0, y)
        Binary search to find right in the row array within [y + 1, n)
        Binary search to find top in the column array within [0, x)
        Binary search to find bottom in the column array within [x + 1, m)
        Return (right - left) * (bottom - top)
        However, the projection step cost O(mn)O(mn) time which dominates the entire algorithm.If so, we gain nothing comparing with previous approaches.

        The trick is that we do not need to do the projection step as a preprocess. We can do it on the fly, i.e. "don't project the column/row unless needed".

        Recall the binary search algorithm in a 1D array, each time we only check one element, the pivot, to decide which half we go next.

        In a 2D array, we can do something similar. The only difference here is that the element is not a number but a vector. For example, a m by n matrix can be seen as n column vectors.

        In these n elements/vectors, we do a binary search to find left or right. Each time we only check one element/vector, the pivot, to decide which half we go next. In total it checks O(\log n)O(logn) vectors, and each check is O(m)O(m) (we simply traverse all the m entries of the pivot vector).

        So it costs O(m \log n)O(mlogn) to find left and right. Similarly it costs O(n \log m)O(nlogm) to find top and bottom. The entire algorithm has a time complexity of O(m \log n + n \log m)O(mlogn+nlogm)


        Complexity Analysis

        Time complexity : O(m \log n + n \log m)O(mlogn+nlogm).
        Here, mm and nn are the height and width of the image. We embedded a linear search for every iteration of binary search. See previous sections for details.

        Space complexity : O(1)O(1).
        Both binary search and linear search used only constant extra space.
    */
    int doit_binary_search(vector<vector<char>>& image, int x, int y) {

        int m = image.size(), n = image[0].size();

        std::function<int(int, int, bool)> searchRows = [&] (int i, int j, bool black) {

            while (i < j) {

                int mid = (i + j) / 2, k = 0;

                while (k < n && image[mid][k] == '1') k++;

                if (k < n == black) 
                    j = mid;
                else
                    i = mid + 1;
            }

            return i;
        };

        std::function<int(int, int, bool)> searchCols = [&] (int i, int j, bool black) {

            while (i < j) {

                int mid = (i + j) / 2, k = 0;

                while (k < m && image[k][mid] == '1') k++;

                if (k < m == black) 
                    j = mid;
                else
                    i = mid + 1;
            }

            return i;
        };

        int top = searchRows(0, x, true);
        int bottom = searchRows(x, m, false);

        int left = searchCols(0, y, true);
        int right = searchCols(y, n, false);


        return (right - left) * (bottom - top);
    }
};