/*
 
 429. N-ary Tree Level Order Traversal
 
 Given an n-ary tree, return the level order traversal of its nodes' values.

 Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).
 
 */


#include <vector>
using std::vector;

#include <deque>
using std::deque;

#include <queue>
using std::queue;

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



class LevelOrder {
    
public:
    vector<vector<int>> doit(Node* root) {
        
        deque<Node*> buf;
        if (root)
            buf.push_back(root);
        vector<vector<int>> ans;
        int i = 0;
        
        while (i != buf.size()) {
            
            vector<int> res;
            size_t end = buf.size();
            for (; i < end; i++) {
                
                res.push_back(buf[i]->val);
                
                for (auto c : buf[i]->children) {
                    buf.push_back(c);
                }
            }
            ans.push_back(res);
        }
        return ans;
    }
    
    vector<vector<int>> doit2(Node* root) {
        
        deque<Node*> buf;
        if (root)
            buf.push_back(root);
        vector<vector<int>> ans;
        
        while (!buf.empty()) {
            
            vector<int> res;
            size_t end = buf.size();
            for (int i = 0; i < end; i++) {
                auto parent = buf.front();
                res.push_back(parent->val);
                
                for (auto c : parent->children) {
                    buf.push_back(c);
                }
                buf.pop_front();
            }
            ans.push_back(res);
        }
        return ans;
    }
    
    vector<vector<int>> doit1(Node* root) {
        vector<vector<int>> v;
        
        if (root == nullptr)
        {
            return v;
        }

        queue<Node*> q;
        
        q.push(root);
        
        while (!q.empty())
        {
            int size = q.size();
            
            vector<int> vl;
            vl.reserve(size);
            while (--size >= 0)
            {
                auto node = q.front();
                q.pop();
                
                vl.push_back(node->val);
                
                for (auto & c : node->children)
                {
                    q.push(c);
                }
            }
            v.push_back(vl);
        }
        
        return v;
    }
};

void test_429_nary_tree_level_order_traversal() {
    
    
    
    
}
