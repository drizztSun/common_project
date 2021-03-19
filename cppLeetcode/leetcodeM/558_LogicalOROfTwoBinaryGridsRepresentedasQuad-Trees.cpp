/*
558. Logical OR of Two Binary Grids Represented as Quad-Trees

A Binary Matrix is a matrix in which all the elements are either 0 or 1.

Given quadTree1 and quadTree2. quadTree1 represents a n * n binary matrix and quadTree2 represents another n * n binary matrix. 

Return a Quad-Tree representing the n * n binary matrix which is the result of logical bitwise OR of the two binary matrixes represented by quadTree1 and quadTree2.

Notice that you can assign the value of a node to True or False when isLeaf is False, and both are accepted in the answer.

A Quad-Tree is a tree data structure in which each internal node has exactly four children. Besides, each node has two attributes:

val: True if the node represents a grid of 1's or False if the node represents a grid of 0's. 
isLeaf: True if the node is leaf node on the tree or False if the node has the four children.
class Node {
    public boolean val;
    public boolean isLeaf;
    public Node topLeft;
    public Node topRight;
    public Node bottomLeft;
    public Node bottomRight;
}
We can construct a Quad-Tree from a two-dimensional area using the following steps:

If the current grid has the same value (i.e all 1's or all 0's) set isLeaf True and set val to the value of the grid and set the four children to Null and stop.
If the current grid has different values, set isLeaf to False and set val to any value and divide the current grid into four sub-grids as shown in the photo.
Recurse for each of the children with the proper sub-grid.

If you want to know more about the Quad-Tree, you can refer to the wiki.

Quad-Tree format:

The input/output represents the serialized format of a Quad-Tree using level order traversal, where null signifies a path terminator where no node exists below.

It is very similar to the serialization of the binary tree. The only difference is that the node is represented as a list [isLeaf, val].

If the value of isLeaf or val is True we represent it as 1 in the list [isLeaf, val] and if the value of isLeaf or val is False we represent it as 0.

 

Example 1:

 
Input: quadTree1 = [[0,1],[1,1],[1,1],[1,0],[1,0]]
, quadTree2 = [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
Output: [[0,0],[1,1],[1,1],[1,1],[1,0]]
Explanation: quadTree1 and quadTree2 are shown above. You can see the binary matrix which is represented by each Quad-Tree.
If we apply logical bitwise OR on the two binary matrices we get the binary matrix below which is represented by the result Quad-Tree.
Notice that the binary matrices shown are only for illustration, you don't have to construct the binary matrix to get the result tree.

Example 2:

Input: quadTree1 = [[1,0]]
, quadTree2 = [[1,0]]
Output: [[1,0]]
Explanation: Each tree represents a binary matrix of size 1*1. Each matrix contains only zero.
The resulting matrix is of size 1*1 with also zero.
Example 3:

Input: quadTree1 = [[0,0],[1,0],[1,0],[1,1],[1,1]]
, quadTree2 = [[0,0],[1,1],[1,1],[1,0],[1,1]]
Output: [[1,1]]
Example 4:

Input: quadTree1 = [[0,0],[1,1],[1,0],[1,1],[1,1]]
, quadTree2 = [[0,0],[1,1],[0,1],[1,1],[1,1],null,null,null,null,[1,1],[1,0],[1,0],[1,1]]
Output: [[0,0],[1,1],[0,1],[1,1],[1,1],null,null,null,null,[1,1],[1,0],[1,0],[1,1]]
Example 5:

Input: quadTree1 = [[0,1],[1,0],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
, quadTree2 = [[0,1],[0,1],[1,0],[1,1],[1,0],[1,0],[1,0],[1,1],[1,1]]
Output: [[0,0],[0,1],[0,1],[1,1],[1,0],[1,0],[1,0],[1,1],[1,1],[1,0],[1,0],[1,1],[1,1]]
 

Constraints:

quadTree1 and quadTree2 are both valid Quad-Trees each representing a n * n grid.
n == 2^x where 0 <= x <= 9.


*/




class GridsRepresentedQuadTrees {

    class Node {
    public:
        bool val;
        bool isLeaf;
        Node* topLeft;
        Node* topRight;
        Node* bottomLeft;
        Node* bottomRight;
        Node() {}
        Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
            val = _val;
            isLeaf = _isLeaf;
            topLeft = _topLeft;
            topRight = _topRight;
            bottomLeft = _bottomLeft;
            bottomRight = _bottomRight;
        }
    };

    /*
        558.Quad-Tree-Intersection
        此题设计了一个叫做四分树的数据结构。我们知道，任何树的题目，都可以用递归来实现。

        我们考虑DFS(A,B)的时候，说明A和B肯定是同级的。但是，本题最大的难点在于，A和B的分支情况可能并不相同，一个可能有，一个可能无，无法直接做类似DFS(A->left,B->left)这种递归，怎么办呢？

        四分树恰恰有这么一个特殊的性质，那就是如果A->isLeaf的话，那么就隐含着意味着A相当于有着val和它自身相同的四个分支！所以，我们可以用DFS(A,B->left)这种形式继续递归下去，递归的底层是直到遇到两个参数都是isLeaf为止。

        本题还有需要注意的一点是，上述的例子中，假设C=DFS(A,B)，我们把已经是leaf的A“隐式地”添加了四个分支，以方便和B继续递归下去。如果这四个分支反馈的val都是相同的，那么根据四分树的定义C是不能有分支的，所以我们需要check这四个子递归的结果，如果这四个分支都是相同的val，那么我们需要标记C为isLeaf即没有分支。
    */

public:
    
    
    Node* intersect(Node* quadTree1, Node* quadTree2) 
    {
        if (quadTree1->isLeaf && quadTree2->isLeaf)
        {
            Node* node = new Node(quadTree1->val || quadTree2->val, true, NULL, NULL, NULL, NULL);
            return node;
        }
        
        if (quadTree1->isLeaf && quadTree1->val || quadTree2->isLeaf && quadTree2->val)
        {
            Node* node = new Node(1, true, NULL, NULL, NULL, NULL);
            return node;
        }
        
        Node* A;
        Node* B;
            
        A = quadTree1->isLeaf ? quadTree1 : quadTree1->topLeft;
        B = quadTree2->isLeaf ? quadTree2 : quadTree2->topLeft;            
        Node* topLeft = intersect(A,B);
            
        A = quadTree1->isLeaf ? quadTree1 : quadTree1->topRight;
        B = quadTree2->isLeaf ? quadTree2 : quadTree2->topRight;            
        Node* topRight = intersect(A,B);
            
        A = quadTree1->isLeaf ? quadTree1 : quadTree1->bottomLeft;
        B = quadTree2->isLeaf ? quadTree2 : quadTree2->bottomLeft;            
        Node* bottomLeft = intersect(A,B);
            
        A = quadTree1->isLeaf ? quadTree1 : quadTree1->bottomRight;
        B = quadTree2->isLeaf ? quadTree2 : quadTree2->bottomRight;            
        Node* bottomRight = intersect(A,B);
            
        if (topLeft->isLeaf && topRight->isLeaf && bottomLeft->isLeaf && bottomRight->isLeaf \\
            && topLeft->val==topRight->val && topRight->val==bottomLeft->val && bottomLeft->val==bottomRight->val )
        {
            Node* node = new Node(topLeft->val, true, NULL, NULL, NULL, NULL);
            return node;
        }
        else
        {
            Node* node = new Node(0, false, NULL, NULL, NULL, NULL);
            node->topLeft = topLeft;
            node->topRight = topRight;
            node->bottomLeft = bottomLeft;
            node->bottomRight = bottomRight;
            return node;
        }
    }
};



