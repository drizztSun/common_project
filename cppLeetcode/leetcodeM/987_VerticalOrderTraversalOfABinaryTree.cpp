/*
 
 
 987. Vertical Order Traversal of a Binary Tree
 
 Given a binary tree, return the vertical order traversal of its nodes values.

 For each node at position (X, Y), its left and right children respectively will be at positions (X-1, Y-1) and (X+1, Y-1).

 Running a vertical line from X = -infinity to X = +infinity, whenever the vertical line touches some nodes,
 we report the values of the nodes in order from top to bottom (decreasing Y coordinates).

 If two nodes have the same position, then the value of the node that is reported first is the value that is smaller.

 Return an list of non-empty reports in order of X coordinate.  Every report will have a list of values of nodes.

  

 Example 1:
 
 Input: [3,9,20,null,null,15,7]
 Output: [[9],[3,15],[20],[7]]
 Explanation:
 Without loss of generality, we can assume the root node is at position (0, 0):
 Then, the node with value 9 occurs at position (-1, -1);
 The nodes with values 3 and 15 occur at positions (0, 0) and (0, -2);
 The node with value 20 occurs at position (1, -1);
 The node with value 7 occurs at position (2, -2).
 
 Example 2:
 
 Input: [1,2,3,4,5,6,7]
 Output: [[4],[2],[1,5,6],[3],[7]]
 Explanation:
 The node with value 5 and the node with value 6 have the same position according to the given scheme.
 However, in the report "[1,5,6]", the node value of 5 comes first since 5 is smaller than 6.
 
 
 
 */

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

class VerticalTraversal {
    
public:
    
    vector<vector<int>> doit(TreeNode* root) {
        
        
        vector<std::tuple<int, int, TreeNode*>> pq;
        pq.push_back({0, 0, root});
        int i = 0;
        
        while (i < pq.size()) {
            
            auto& p = pq[i];
            int x = std::get<0>(p), y = std::get<1>(p);
            TreeNode* n = std::get<2>(p);
            
            if (n->left)
                pq.push_back({x - 1, y - 1, n->left});
                
            if (n->right)
                pq.push_back({x + 1, y - 1, n->right});
            
            i++;
        }
        
        std::sort(pq.begin(), pq.end(), [](auto& a, auto&b) {
            int ax = std::get<0>(a), ay = std::get<1>(a);
            int bx = std::get<0>(b), by = std::get<1>(b);
            TreeNode* ar = std::get<2>(a);
            TreeNode* br = std::get<2>(b);
            return ax < bx || (ax == bx && ay > by) || (ax == bx && ay == by && ar->val < br->val);
        });
        
        
        vector<vector<int>> ans;
        ans.push_back({});
        int base = std::get<0>(pq[0]);
        
        for (auto& c : pq) {
            
            if (base != std::get<0>(c)) {
                base = std::get<0>(c);
                ans.push_back({});
            }
            
            ans.back().push_back(std::get<2>(c)->val);
        }
        
        return ans;
    }
};

class Solution_verticalTraversal {
public:
    int min_left=0;
    int max_right=0;
    void DFS(TreeNode* root,int x,int y,unordered_map<int,vector<std::pair<int,int>>> &umap)
    {
        if(root==NULL)
            return ;
        if(y<0 && y < min_left)
            min_left = y;
        if(y>=0 && y > max_right)
            max_right = y;
        umap[y].push_back({x,root->val});
        DFS(root->left,x+1,y-1,umap);
        DFS(root->right,x+1,y+1,umap);
        
        
       
    }
    vector<vector<int>> doit(TreeNode* root) {
        if(root==nullptr)
            return {};
        
        unordered_map<int,vector<std::pair<int,int>>> temp;
        DFS(root,0,0,temp);
        vector<vector<int>> result;
        for(int i=min_left;i<=max_right;i++)
        {
            sort(temp[i].begin(),temp[i].end());
            vector<int> mid;
            for(int j=0;j<temp[i].size();j++)
            {
                mid.push_back(temp[i][j].second);
            }
            result.push_back(mid);
            
        }
        return result;
    }
};


void test_987_vertical_order_traversal_of_binary_tree() {
    
    TreeNode r(3);
    TreeNode r9(9);
    TreeNode l2(20);
    TreeNode r1(15);
    TreeNode r7(7);
    
    r.left = &r9;
    r.right = &l2;
    l2.left = &r1;
    l2.right = &r7;
    
    auto res1 = VerticalTraversal().doit(&r);
    
    return;
}
