/*
 
 1206. Design Skiplist
 
 Design a Skiplist without using any built-in libraries.

 A Skiplist is a data structure that takes O(log(n)) time to add, erase and search.
 Comparing with treap and red-black tree which has the same function and performance,
 the code length of Skiplist can be comparatively short and the idea behind Skiplists are just simple linked lists.

 For example: we have a Skiplist containing [30,40,50,60,70,90] and we want to add 80 and 45 into it. The Skiplist works this way:


 Artyom Kalinin [CC BY-SA 3.0], via Wikimedia Commons

 You can see there are many layers in the Skiplist. Each layer is a sorted linked list. With the help of the top layers, add , erase and search can be faster than O(n).
 It can be proven that the average time complexity for each operation is O(log(n)) and space complexity is O(n).

 To be specific, your design should include these functions:

 bool search(int target) : Return whether the target exists in the Skiplist or not.
 void add(int num): Insert a value into the SkipList.
 bool erase(int num): Remove a value in the Skiplist. If num does not exist in the Skiplist, do nothing and return false.
 If there exists multiple num values, removing any one of them is fine.
 See more about Skiplist : https://en.wikipedia.org/wiki/Skip_list

 Note that duplicates may exist in the Skiplist, your code needs to handle this situation.

  

 Example:

 Skiplist skiplist = new Skiplist();

 skiplist.add(1);
 skiplist.add(2);
 skiplist.add(3);
 skiplist.search(0);   // return false.
 skiplist.add(4);
 skiplist.search(1);   // return true.
 skiplist.erase(0);    // return false, 0 is not in skiplist.
 skiplist.erase(1);    // return true.
 skiplist.search(1);   // return false, 1 has already been erased.
  

 Constraints:

 0 <= num, target <= 20000
 At most 50000 calls will be made to search, add, and erase.
 
 
 */
#include <memory>
#include <stack>

using std::stack;
using std::shared_ptr;



class Skiplist {
    
    
    struct Node {
        Node(int val = 1, shared_ptr<Node> next = nullptr, shared_ptr<Node> down = nullptr): val(val), down(down), right(next) {}
        int val;
        std::shared_ptr<Node> down, right;
    };
    
    std::shared_ptr<Node> _head;
    
public:
    Skiplist() {
        _head = std::make_shared<Node>();
    }
    
    bool search(int target) {
        
        for (auto node = _head; node; node = node->down) {
            
            while (node->right && node->right->val < target) {
                node = node->right;
            }
            
            if (node->right && node->right->val == target)
                return true;
        }
        return false;
    }
    
    void add(int num) {
        
        stack<shared_ptr<Node>> st;
        
        for (auto node = _head; node; node = node->down) {
            while (node->right && node->right->val < num) {
                node = node->right;
            }
            st.push(node);
        }
        
        bool insert = true;
        shared_ptr<Node> down = nullptr;
        while (insert && !st.empty()) {
            
            auto cur = st.top(); st.pop();
            auto future = cur->right;
            cur->right = std::make_shared<Node>(num, cur->right, down);
            down = cur->right;
            insert = rand() % 1;
        }
        
        if (insert)
            _head = std::make_shared<Node>(-1, nullptr, _head);
    }
    
    bool erase(int num) {
        
        bool found = false;
        
        for (auto node = _head; node; node = node->down) {
            
            while (node->right && node->right->val < num) {
                node = node->right;
            }
            
            if (node->right && node->right->val == num) {
                found = true;
                node->right = node->right->right;
            }
        }
        
        return found;
    }
};
