/*
895. Maximum Frequency Stack

Design a stack-like data structure to push elements to the stack and pop the most frequent element from the stack.

Implement the FreqStack class:

. FreqStack() constructs an empty frequency stack.
. void push(int val) pushes an integer val onto the top of the stack.
. int pop() removes and returns the most frequent element in the stack.

If there is a tie for the most frequent element, the element closest to the stack's top is removed and returned.
 

Example 1:

Input
["FreqStack", "push", "push", "push", "push", "push", "push", "pop", "pop", "pop", "pop"]
[[], [5], [7], [5], [7], [4], [5], [], [], [], []]
Output
[null, null, null, null, null, null, null, 5, 7, 5, 4]

Explanation
FreqStack freqStack = new FreqStack();
freqStack.push(5); // The stack is [5]
freqStack.push(7); // The stack is [5,7]
freqStack.push(5); // The stack is [5,7,5]
freqStack.push(7); // The stack is [5,7,5,7]
freqStack.push(4); // The stack is [5,7,5,7,4]
freqStack.push(5); // The stack is [5,7,5,7,4,5]
freqStack.pop();   // return 5, as 5 is the most frequent. The stack becomes [5,7,5,7,4].
freqStack.pop();   // return 7, as 5 and 7 is the most frequent, but 7 is closest to the top. The stack becomes [5,7,5,4].
freqStack.pop();   // return 5, as 5 is the most frequent. The stack becomes [5,7,4].
freqStack.pop();   // return 4, as 4, 5 and 7 is the most frequent, but 4 is closest to the top. The stack becomes [5,7].
 

Constraints:

0 <= val <= 109
At most 2 * 104 calls will be made to push and pop.
It is guaranteed that there will be at least one element in the stack before calling pop.

*/
#include <stack>
#include <map>
#include <vector>
#include <unordered_map>

using std::stack;
using std::unordered_map;
using std::map;
using std::vector;


class FreqStack {

    unordered_map<int, int> _counter;
    map<int, vector<int>> _freq;

public:

    FreqStack() {}
    
    void push(int val) {
        
        _counter[val]++;
        _freq[_counter[val]].push_back(val);
    }
    
    int pop() {

        while (!_freq.empty() && _freq.rbegin()->second.empty()) {
            _freq.erase(prev(_freq.end()));
        }

        if (_freq.empty()) return -1;

        auto it = prev(_freq.end());
        int v = it->second.back();
		_counter[v]--;
        it->second.pop_back();
		if (it->second.empty())
			_freq.erase(it->first);
        return v;
    }
};

/*
    Hash map freq will count the frequence of elements.
    Hash map m is a map of stack.
    If element x has n frequence, we will push x n times in m[1], m[2] .. m[n]
    maxfreq records the maximum frequence.

    push(x) will push x tom[++freq[x]]
    pop() will pop from the m[maxfreq]
*/
class FreqStack {

    unordered_map<int, int> freq;
    unordered_map<int, stack<int>> m;
    int maxfreq = 0;

public:

    void push(int x) {
        maxfreq = std::max(maxfreq, ++freq[x]);
        m[freq[x]].push(x);
    }

    int pop() {
        int x = m[maxfreq].top();
        m[maxfreq].pop();
        if (!m[freq[x]--].size()) maxfreq--;
        return x;
    }
};

/*
    895.Maximum-Frequency-Stack
    很显然我们会设计unordered_map<int, vector<int>> freq2nums用来记录当前拥有相同频次的那些数。然后用unordered_map<int, int> count来记录每个元素对应出现的频次也是很好想的。

    那么我们push(x)的时候，提取freq=count[x]，然后会更新freq2nums[freq+1].push_back(x)。但是注意，我们不需要对freq2nums[freq]做任何关于x的改动（指从里面删去x的记录）。
    事实上，我们需要保留x在freq2nums[freq]中的位置，这样当maxFreq再次回落到freq的时候，我们就可以从freq2nums[freq]对应的数组里面得到应该优先弹出哪个元素。

    同理，我们pop()的时候，提取x=freq2nums[maxFreq].back()，然后我们会更新freq2nums[maxFreq].pop_back()。但是注意，我们不需要再对freq2nums[maxFreq-1]做任何关于x的改动（指从里面增加x的记录）。
    这是因为在之前加入第maxFreq-1个x的时候，我们已经在freq2nums[maxFreq-1]里面保留了关于x的位置。现在最高频次回落了，我们就可以从freq2nums[maxFreq-1]的末尾直接得到以后应该弹出的元素（因此它是最后一个放入freq2nums[maxFreq-1]里面的）。
*/
class FreqStack {
    unordered_map<int, vector<int>> freq2nums;  // freq -> a series of nums
    unordered_map<int, int> count; // num -> freq
    int maxFreq = 0;
    
public:
    FreqStack() {}
    
    void push(int x) 
    {
        int freq = count[x];
        
        freq2nums[freq+1].push_back(x);
        count[x] = freq+1;        
        maxFreq = std::max(maxFreq, freq+1);
    }
    
    int pop() 
    {
        int x = freq2nums[maxFreq].back();
        int freq = count[x];
        
        freq2nums[freq].pop_back();
        count[x] = freq-1;
        
        if (freq2nums[maxFreq].size()==0)
            maxFreq -= 1;
        
        return x;
    }
};