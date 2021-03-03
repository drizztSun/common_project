/*
946. Validate Stack Sequences

Given two sequences pushed and popped with distinct values, return true if and only if this could have been the result of a sequence of push and pop operations on an initially empty stack.

 

Example 1:

Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
Output: true
Explanation: We might do the following sequence:
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
Example 2:

Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
Output: false
Explanation: 1 cannot be popped before 2.
 

Constraints:

0 <= pushed.length == popped.length <= 1000
0 <= pushed[i], popped[i] < 1000
pushed is a permutation of popped.
pushed and popped have distinct values.

*/
#include <stack>
#include <vector>


using std::stack;
using std::vector;


class ValidateStackSequences {

    /*
        946.Validate-Stack-Sequences
        本题的解法类似于贪心。我们从前往后观察pushed，一旦发现pushed末尾有任何长度的序列和poped队首的对应长度序列正好是反向关系，就将两者相消。然后继续观察剩下的pushed和poped，继续往后遍历pushed，做同样的操作。直到两者的序列都彼此消掉，说明两者对应的是一个合法的入栈/出栈操作。

        A     B    C     D
        *******++++++*****++++++
                        ++++++  E
                        ----------  F
        *******++++++*****---------- 
        J       I    H    G
        举如上的例子，相同的序列段用同样的字符表示。实际栈操作的顺序是 +A +B +C +D -E +F -G -H -I -J。所以相应的pushed = ABCDF, poped = EGHIJ。其中D和E是对应的，F和G是对应的，H和C是对应的，I和B是对应的，J和A是对应的。

        根据我们上述的算法，当查看到pushed里面的B时，发现恰好与poped中的E相同，根据规则需要将B和E进行相消。但实际上的操作里面，D与E才是相消关系。所以这种算法合理吗？

        答案是合理的。因为尽管我们将B和E进行了错误的对消，但是必然存在D和I也可以在后续得到对消。不信我们试一试，此时栈操作的顺序（根据我们的算法理解）变相成了 +A +B -E +C +D +F -G -H -I -J，尽管提前做了出栈的操作-E，但总的pushed = ABCDF, poped = EGHIJ 依然不变。就是这么神奇。
    */
    bool doit_stack(vector<int>& pushed, vector<int>& popped) 
    {
        stack<int>Stack;
        int j = 0;
        for (int i=0; i<pushed.size(); i++)
        {
            Stack.push(pushed[i]);
            while (i<popped.size() && !Stack.empty() && Stack.top()==popped[j])
            {
                Stack.pop();
                j++;
            }
        }
        return j==popped.size();
    }

public:

    bool doit_stack(vector<int>& pushed, vector<int>& popped) {
        
        int i = 0, j = 0;
        stack<int> st;
        while (i < pushed.size()) {
            
            if (st.empty() || st.top() != popped[j])
                st.push(pushed[i]);
                
            while (!st.empty() && j < popped.size() && popped[j] == st.top()) {
                st.pop();
                j++;
            }
            
            i++;
        }
        
        return st.empty() && i == pushed.size() && j == popped.size();
    }
};