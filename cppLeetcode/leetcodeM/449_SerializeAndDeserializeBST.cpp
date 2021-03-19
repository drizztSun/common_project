/*
449. Serialize and Deserialize BST

Serialization is converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, 
or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. 
You need to ensure that a binary search tree can be serialized to a string, and this string can be deserialized to the original tree structure.

The encoded string should be as compact as possible.

 

Example 1:

Input: root = [2,1,3]
Output: [2,1,3]
Example 2:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 104].
0 <= Node.val <= 104
The input tree is guaranteed to be a binary search tree.

*/

#include <vector>
#include <string>
#include <functional>

using std::vector;
using std::string;


/*
    449.Serialize-and-Deserialize-BST
    此题是297.Serialize and Deserialize Binary Tree的扩展。对于任意的二叉树，仅根据一种遍历无法还原这课树，一般需要两种遍历序列，或者是level order加上NULL节点的信息。

    但对于BST，它有一个非常好的性质，就是仅用其先序遍历就可逆！

    一种直观的想法就是，根据“先序遍历的首元素是根节点”，通过逐个大小比较，将之后的元素分为左子树和右子树两部分，分别递归构建左子树和右子树。这种方法会对同一个元素多次进行比较，需要o(n^2)的时间，太慢。
    
    (参考255.Verify Preorder Sequence in Binary Search Tree）

    比较巧妙的DFS解法，是根据首元素（根节点）来更新之后左右子树的上下限。构造DFS函数

        TreeNode* DFS2(vector<int>& preorder,int curIdx, int MIN, int MAX)
        {
            if (curIdx>=preorder.size()) return NULL;
            
            if (preorder[curIdx]<MIN || preorder[curIdx]>MAX)
                return DFS2(preorder, curIdx+1, MIN, MAX);
            
            TreeNode* root = new TreeNode(preorder[curIdx]);
            root->left = DFS2(preorder,curIdx+1,MIN,root->val);
            root->right = DFS2(preorder,curIdx+1,root->val,MAX); 
            
            return root;
        }
    每次DFS都推进一位（curIdx）。如果preorder[curIdx]不合当前上下限的，就不理会，继续往后面的元素找；如果符合当前上下限，那么说明preorder[curIdx]本身就适合当一个根节点，其左右子树必定在之后的元素里，于是推进一位递归调用DFS，只要合理更新上下限即可。
*/


class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) 
    {
        string s;
        DFS(root,s);
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) 
    {
        if (data.size()==0) return NULL;
        vector<int>preorder;
        int i=0;
        while (i<data.size())
        {
            string s="";
            while (data[i]!=',')
            {
                s+=data[i];
                i++;
            }
            preorder.push_back(stoi(s));
            i++;
        }
        
        TreeNode *root = DFS2(preorder,0,INT_MIN,INT_MAX);
        return root;
    }
    
private:
    void DFS(TreeNode* root, string& s)
    {
        if (root==NULL) return;
        
        s+=to_string(root->val)+',';
        DFS(root->left,s);
        DFS(root->right,s);
    }
    
    TreeNode* DFS2(vector<int>& preorder,int curIdx, int MIN, int MAX)
    {
        if (curIdx>=preorder.size()) return NULL;
        
        if (preorder[curIdx]<MIN || preorder[curIdx]>MAX)
            return DFS2(preorder, curIdx+1, MIN, MAX);
        
        TreeNode* root = new TreeNode(preorder[curIdx]);
        root->left = DFS2(preorder,curIdx+1,MIN,root->val);
        root->right = DFS2(preorder,curIdx+1,root->val,MAX); 
        
        return root;
    }
};

// postorder
class Codec {


    string int2str(int val) {
        char bytes[4];
        for (int i = 3; i > -1; i--)
            bytes[3-i] = char((val >> i * 8) & 0xff);
        return string(bytes);
    }
    
    int str2int(string bytes) {
        int result = 0;
        for (char b :bytes) {
            result = (result << 8) + (int) b;
        }
        return result;
    }

public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {

        string ans;
        std::function<void(TreeNode*)> postorder = [&](TreeNode* p) {
            if (!p) return;

            postorder(p->left);
            postorder(p->right);
            ans += std::to_string(p->val);
            ans += " ";
        };

        postorder(root);
        //if (ans.size() > 0) ans.pop_back();
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {

        vector<int> buf;
        int i = 0;
        while (i < data.length()) {
            int j = data.find(' ', i);
            if (j == -1) break;
            buf.push_back(std::stoi(data.substr(i, j - i)));
            i = j + 1;
        };

        std::reverse(begin(buf), end(buf));

        int index = 0;
        std::function<TreeNode*(int, int)> helper = [&](int minv, int maxv) -> TreeNode* {

            if (index >= buf.size()) return NULL;

            if (buf[index] < minv || buf[index] > maxv) return NULL;

            int val = buf[index++];
            TreeNode *node = new TreeNode(val);
            node->right = helper(val, maxv);
            node->left = helper(minv, val);

            return node;
        };

        return helper(INT_MIN, INT_MAX);
    }
};