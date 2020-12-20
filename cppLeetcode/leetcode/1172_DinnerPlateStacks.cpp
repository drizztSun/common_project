/*

1172. Dinner Plate Stacks

You have an infinite number of stacks arranged in a row and numbered (left to right) from 0, each of the stacks has the same maximum capacity.

Implement the DinnerPlates class:

DinnerPlates(int capacity) Initializes the object with the maximum capacity of the stacks.
void push(int val) Pushes the given positive integer val into the leftmost stack with size less than capacity.
int pop() Returns the value at the top of the rightmost non-empty stack and removes it from that stack, and returns -1 if all stacks are empty.
int popAtStack(int index) Returns the value at the top of the stack with the given index and removes it from that stack, and returns -1 if the stack with that given index is empty.
Example:

Input: 
["DinnerPlates","push","push","push","push","push","popAtStack","push","push","popAtStack","popAtStack","pop","pop","pop","pop","pop"]
[[2],[1],[2],[3],[4],[5],[0],[20],[21],[0],[2],[],[],[],[],[]]
Output: 
[null,null,null,null,null,null,2,null,null,20,21,5,4,3,1,-1]

Explanation: 
DinnerPlates D = DinnerPlates(2);  // Initialize with capacity = 2
D.push(1);
D.push(2);
D.push(3);
D.push(4);
D.push(5);         // The stacks are now:  2  4
                                           1  3  5
                                           ﹈ ﹈ ﹈
D.popAtStack(0);   // Returns 2.  The stacks are now:     4
                                                       1  3  5
                                                       ﹈ ﹈ ﹈
D.push(20);        // The stacks are now: 20  4
                                           1  3  5
                                           ﹈ ﹈ ﹈
D.push(21);        // The stacks are now: 20  4 21
                                           1  3  5
                                           ﹈ ﹈ ﹈
D.popAtStack(0);   // Returns 20.  The stacks are now:     4 21
                                                        1  3  5
                                                        ﹈ ﹈ ﹈
D.popAtStack(2);   // Returns 21.  The stacks are now:     4
                                                        1  3  5
                                                        ﹈ ﹈ ﹈ 
D.pop()            // Returns 5.  The stacks are now:      4
                                                        1  3 
                                                        ﹈ ﹈  
D.pop()            // Returns 4.  The stacks are now:   1  3 
                                                        ﹈ ﹈   
D.pop()            // Returns 3.  The stacks are now:   1 
                                                        ﹈   
D.pop()            // Returns 1.  There are no stacks.
D.pop()            // Returns -1.  There are still no stacks.
 

Constraints:

1 <= capacity <= 20000
1 <= val <= 20000
0 <= index <= 100000
At most 200000 calls will be made to push, pop, and popAtStack.


*/


#include <vector>
#include <deque>
#include <set>
#include <stack>

using std::set;
using std::vector;
using std::stack;


class DinnerPlates {

    set<int> _idx;
    vector<stack<int>> _stacks;
    int _cap;
public:

    DinnerPlates(int capacity) {
        _cap = capacity;
    }
    
    void push(int val) {
        
        int idx = _idx.empty() ? _stacks.size() : *begin(_idx);
        if (idx == _stacks.size())
            _stacks.emplace_back();

        auto& it = _stacks[idx];
        it.push(val);

        if (it.size() == _cap)
            _idx.erase(idx);
        else if (it.size() == 1)
            _idx.insert(idx);
    }
    
    int pop() {
        return popAtStack(_stacks.size()-1);
    }
    
    int popAtStack(int index) {
        
        if (index < 0 || index >= _stacks.size() || _stacks[index].empty())
            return -1;

        auto& it = _stacks[index];
        int revt = it.top();
        it.pop();

        if (it.size() == _cap - 1)
            _idx.insert(index);

        while (!_stacks.empty() && _stacks.back().empty()) {
            _stacks.pop_back();
            _idx.erase(_stacks.size());
        }

        return revt;
    }
};


class DinnerPlatesII {
public:
    vector<vector<int>> st;
    int lim;
    int l; // points to left most stack where new element can be pushed
    int r; // points to right most stack where an element can be popped if not all empty
    DinnerPlatesII(int capacity) {
        lim = capacity;
        st.push_back(vector<int>()); // right now stack is emty
        l=0,r=0;
    }

    void push(int val) { // l must be valid always
        st[l].push_back(val);
        if(r<l)
            r=l; // update right most index only after push
    
        int i = l+1;
        if(st[l].size() != lim)
            return;
        
        // update l if needed
        while(i < st.size()){
            if(st[i].size() < lim){
                l = i;
                break;
            }
            i++;
        } 
        
        if (i==st.size()) { // all stacks are full , create a new stack. Once created stack will never be deleted
            st.push_back(vector<int>());
            l=i;
        }
        return;
    }

    int pop() {
        if(r<0 || st[r].size()==0)
            return -1;
    
        int item = st[r][st[r].size()-1];
        st[r].pop_back(); 
        while(r>=0 && st[r].size()==0)// after popping if becomes empty
            r--;
    
        if(r==-1) // if everything is empty
            l=0;
    
        return item;
    }

    int popAtStack(int index) {
        if(index>=st.size() || st[index].size()==0)
            return -1;
    
        int item = st[index][st[index].size()-1];
        st[index].pop_back(); 
        if(r==index){
            while(r>=0 && st[r].size()==0)// after popping if becomes empty
                r--;
        }
    
        if(index <= l) // if new left side stack has got some space now
            l = index;
    
        if(r ==-1) // if everything is empty
            l=0;
    
        return item;
    }
};
