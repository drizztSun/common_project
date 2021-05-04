/*
428. Serialize and Deserialize N-ary Tree

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize an N-ary tree. An N-ary tree is a rooted tree in which each node has no more than N children. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that an N-ary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following 3-ary tree



as [1 [3[5 6] 2 4]]. Note that this is just an example, you do not necessarily need to follow this format.

Or you can follow LeetCode's level order traversal serialization format, where each group of children is separated by the null value.



For example, the above tree may be serialized as [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14].

You do not necessarily need to follow the above suggested formats, there are many more different formats that work so please be creative and come up with different approaches yourself.

 

Constraints:

The number of nodes in the tree is in the range [0, 104].
0 <= Node.val <= 104
The height of the n-ary tree is less than or equal to 1000
Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.

*/


/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
#include <vector>
#include <string>
#include <sstream>

using std::stringstream;
using std::string;
using std::vector;


class Codec {

    // Definition for a Node.
    class Node {
    public:
        int val;
        vector<Node*> children;

        Node() {}

        Node(int _val) {
            val = _val;
        }

        Node(int _val, vector<Node*> _children) {
            val = _val;
            children = _children;
        }
    };

    /*
        428.Serialize-and-Deserialize-N-ary-Tree
        此题可以仿照297.Serialize-and-Deserialize-Binary-Tree中用先序遍历的思想来编码和解码。

        在编码的过程中，我们对于每个节点要存储val之外，还需要存储有多少个child。第二个信息对于重构树的形状很重要，而且它还可以帮助我们在encode时省去存储空的叶子节点。

        decode的具体算法：将编码分解为若干个节点（不存在空节点，因为编码的时候省去了）放在数组里。此时cur=0，调用递归函数dfs(cur)。因为数组的第一个元素cur必然就是根节点，我们可以获取val和它的孩子的数目k。
        然后我们循环k次，从数组的第cur+1个元素开始依次构建它的k个child节点。更具体地，我们构建了第一个子树dfs(cur+1)之后，数一下这个子树共有k1个元素，那么我们就从数组的第cur+k1+1个元素开始通过dfs(cur+k1+1)构建第二个子树；
        再数一下这个子树共有k2个元素，就调用dfs(cur+k1+k2+1)构建第三个子树...直至把cur的所有子树都构建完毕。
    */
    // Encodes a tree to a single string.
    string serialize(Node* root) 
    {        
        if (root==NULL) return "#";
        string ret = std::to_string(root->val) + ":" + std::to_string(root->children.size()) + ",";
        for (int i=0; i<root->children.size(); i++)
            ret += serialize(root->children[i]) + ",";
        ret.pop_back();
        return ret;
    }
	
    // Decodes your encoded data to tree.
    Node* deserialize(string data) 
    {
        if (data=="#") return NULL;
        vector<Node*>nodes;
        for (int i=0; i<data.size(); i++)
        {
            int j = i;
            while (j<data.size() && data[j]!=',')
                j++;
            string str = data.substr(i,j-i);
            int pos = str.find(":");
            Node* node = new Node(stoi(str.substr(0,pos)));
            node->children.resize(stoi(str.substr(pos+1)));
            nodes.push_back(node);
            i = j;
        }

        return dfs(nodes, 0);   
    }
    
    Node* dfs(vector<Node*>&nodes, int cur)
    {
        int start = cur+1;
        for (int i=0; i<(nodes[cur]->children.size()); i++)
        {
            nodes[cur]->children[i] = dfs(nodes, start);
            start += getSize(nodes[cur]->children[i]);
        }
        return nodes[cur];
    }
    
    int getSize(Node* node)
    {
        if (node==NULL) return 0;
        int count = 1;
        for (int i=0; i<node->children.size(); i++)
            count += getSize(node->children[i]);
        return count;
    }

public:

    // Encodes a tree to a single string.
    string serialize(Node* root) 
    {
        string serStr;
       
        getSerializedStr(root, serStr);
       
        return serStr;
    }
	
     void getSerializedStr(Node* root, string& serStr)
    {
        if(!root)
            return;
       
        serStr += std::to_string(root->val) + " ";
       
        int n = root->children.size();
       
        for(int i = 0; i < n; i++)
        {
            getSerializedStr(root->children[i], serStr);
        }
       
        serStr += ", ";
    }
    
    
    // Decodes your encoded data to tree.
    Node* deserialize(string data) 
    {
        
        if(data.empty())
            return nullptr;
        
        stringstream stream(data);        
       
        return getResultTree(stream);
    }   
    
    Node* getResultTree(stringstream& stream)
    {
        if(stream.eof())
            return nullptr;
       
        string val;
       
        stream >> val;
       
        if(val == ",")
            return nullptr;
       
        Node* root = new Node;
        root->val = stoi(val);

        while(1)
        {
            Node* child = getResultTree(stream);
       
            if(!child)
            {            
                return root;
            }            
            else
                root->children.push_back(child);
        }        
        
        return nullptr;
    }
};