/*
484. Find Permutation


By now, you are given a secret signature consisting of character 'D' and 'I'. 'D' represents a decreasing relationship between two numbers, 
'I' represents an increasing relationship between two numbers. 

And our secret signature was constructed by a special integer array, which contains uniquely all the different number from 1 to n (n is the length of the secret signature plus 1). 

For example, the secret signature "DI" can be constructed by array [2,1,3] or [3,1,2], but won't be constructed by array [3,2,4] or [2,1,3,4], which are both illegal constructing special string that can't represent the "DI" secret signature.

On the other hand, now your job is to find the lexicographically smallest permutation of [1, 2, ... n] could refer to the given secret signature in the input.

Example 1:
Input: "I"
Output: [1,2]
Explanation: [1,2] is the only legal initial spectial string can construct secret signature "I", where the number 1 and 2 construct an increasing relationship.
Example 2:
Input: "DI"
Output: [2,1,3]
Explanation: Both [2,1,3] and [3,1,2] can construct the secret signature "DI", 
but since we want to find the one with the smallest lexicographical permutation, you need to output [2,1,3]
Note:

The input string will only contain the character 'D' and 'I'.
The length of input string is a positive integer and will not exceed 10,000

*/

#include <vector>
#include <string>
#include <stack>

using std::stack;
using std::string;
using std::vector;

class FindPermutation {

    /*
        484.Find-Permutation
        需要人工分析出最优的策略。

        以“下拐点”为分界点将s序列分为若干个II...IIDD...DD的组合。对于每个II...IIDD...DD，可以知道最优方法是：将除最后一个I之外的所有I对应一个递增数列，剩下的一个I和所有的D对应一个递减数列，且递减数列的最小值是那个递增数列最大值加1。
        更有用的是，可以知道，所有的递增数列的值都是和它的index值是对应的results[i]=i+1。

        那么s的位数和results的位数不一样怎么办？一个简单的方法是s.insert(s.begin(),s[0])，这样s和results的元素数目就是一致的，且各个位置都适用同样的代码语句。
    */
    vector<int> findPermutation(string s) 
    {
        s.insert(s.begin(),s[0]);
        int N=s.size();
        vector<int>results(N,0);
        
        int left=0;
        int right=0;
        
        while (right<s.size())
        {
            while (right+1<s.size() && !(s[right]=='D' && s[right+1]=='I'))
                   right++;
            if (right==s.size()) right--;
            
            int top=left;
            while (s[top+1]=='I') top++;
            for (int i=left; i<top; i++)
                results[i]=i+1;
            for (int i=top; i<=right; i++)
                results[i]=top+1+right-i;
            left=right+1;
            right=right+1;
        }
        
        return results;
            
    }

public:

    /*
        Approach #1 Using Stack [Accepted]
        Let's revisit the important points of the given problem statement. For a given nn, we need to use all the integers in the range (1,n)(1,n) to generate a lexicographically smallest permutation of these nn numbers which satsfies the pattern given in the string ss.

        Firstly, we note that the lexicographically smallest permutation that can be generated(irrelevant of the given pattern ss) using the nn integers from (1,n)(1,n) is [1, 2, 3,.., n][1,2,3,..,n](say minmin). Thus, while generating the required permutation, we can surely say that the permutation generated should be as close as possible to minmin.

        Now, we can also note that the number generated will be the smallest possible only if the digits lying towards the most significant positions are as small as possible while satisfying the given pattern. Now, to understand how these observations help in providing the solution of the given problem, we'll look at a simple example.

        Say, the given pattern ss is "DDIIIID". This corresponds to n=8n=8. Thus, the minmin permutation possible will be [1, 2, 3, 4, 5, 6, 7, 8]. Now, to satisfy the first two "DD" pattern, we can observe that the best course of action to generate the smallest arrangement will be to rearrange only 1, 2, 3, because these are the smallest numbers that can be placed at the three most significant positions to generate the smallest arrangement satisfying the given pattern till now, leading to the formation of [3, 2, 1, 4, 5, 6, 7, 8] till now. We can note that placing any number larger than 3 at any of these positions will lead to the generation of a lexicographically larger arrangement as discussed above.

        We can also note that irrespective of how we rearrange the first three 1, 2, 3, the relationship of the last number among them with the next number always satisfies the criteria required for satisfying the first I in ss. Further, note that, the pattern generated till now already satisfies the subpattern "IIII" in ss. This will always be satisfied since the minmin number considered originally always satisfies the increasing criteria.

        Now, when we find the last "D" in the pattern ss, we again need to make rearrangements in the last two positions only and we need to use only the numbers 7, 8 in such rearrangements at those positions. This is because, again, we would like to keep the larger number towards the least significant possible as much as possible to generate the lexicographically smallest arrangement. Thus, to satisfy the last "D" the best arrangement of the last two numbers is 8, 7 leading to the generation of [3, 2, 1, 4, 5, 6, 8, 7] as the required output.

        Based on the above example, we can summarize that, to generate the required arrangement, we can start off with the minmin number that can be formed for the given nn. Then, to satisfy the given pattern ss, we need to reverse only those subsections of the minmin array which have a D in the pattern at their corresponding positions.

        To perform these operations, we need not necessarily create the minmin array first, because it simply consists of numbers from 11 to nn in ascending order.

        To perform the operations discussed above, we can make use of a stackstack. We can start considering the numbers ii from 11 to nn. For every current number, whenver we find a D in the pattern ss, we just push that number onto the stackstack. This is done so that, later on, when we find the next I, we can pop off these numbers from the stack leading to the formation of a reversed (descending) subpattern of those numbers corrresponding to the D's in ss(as discussed above).

        When we encounter an I in the pattern, as discussed above, we push the current number as well onto the stackstack and then pop-off all the numbers on the stackstack and append these numbers to the resultant pattern formed till now.

        Now, we could reach the end of the pattern ss with a trail of D's at the end. In this case, we won't find an ending I to pop-off the numbers on the stackstack. Thus, at the end, we push the value nn on the stack and then pop all the values on the stackstack and append them to the resultant pattern formed till now. Now, if the second last character in ss was an I, nn will be appended at the end of the resultant arrangement correctly. If the second last character was a D, the reversed pattern appended at the end of the resultant arrangement will be reversed including the last number nn. In both the cases, the resultant arrangement turns out to be correct.

        The following animation better illustrates the process.

        Current
        1 / 20
        Below code is inpired by @horseno


        Complexity Analysis
        Time complexity : O(n). nn numbers will be pushed and popped from the stackstack. Here, nn refers to the number of elements in the resultant arrangement.
        Space complexity : O(n). The stackstack can grow upto a depth of nn in the worst case.
    */
    vector<int> doit_stack(string s) {

        int n = s.length();
        vector<int> res(n+1);
        stack<int> st;
        int j = 0;
        
        for (int i = 1; i <= s.length(); i++) {
            if (s[i-1] == 'I') {
                st.push(i);
                while (!st.empty()) {
                    res[j++] = st.top();
                    st.pop();
                }
            } else {
                st.push(i);
            }
        }
        
        st.push(n+1);
        while (!st.empty()) {
            res[j++] = st.top();
            st.pop();
        }
        
        return res;
    }

    /*
        Approach #2 Reversing the subarray [Accepted]
        Algorithm

        In order to reverse the subsections of the minmin array, as discussed in the last approach, we can also start by initializing the resultant arrangement resres with the minmin array i.e. 
        by filling with elements (1,n)(1,n) in ascending order. 
        Then, while traversing the pattern ss, we can keep a track of the starting and ending indices in resres corresponding to the D's in the pattern ss, and reverse the portions of the sub-arrays in resres corresponding to these indices. 
        The reasoning behind this remains the same as discussed in the last approach.

        The following animation illustrates the process.

        Current
        1 / 14

        Complexity Analysis

        Time complexity : O(n). The resultant array of size nn is traversed atmost three times, in the worst case e.g. "DDDDDD"
        Space complexity : O(1). Constant extra space is used.
    */
    vector<int> doit_gready(string s) {
        
        int n = s.length();
        vector<int> res(n+1);
        
        for (int i = 0; i < res.size(); i++) 
            res[i] = i + 1;
        
        auto reverse = [&](int s, int e) {
            for (int k = 0; k < (e-s)/2; k++)
                std::swap(res[s+k], res[e-k-1]);
        };
        
        int i = 1;
        while (i <= s.length()) {
            int j = i;
            while (i <= s.length() && s[i-1] == 'D') i++;
            reverse(j-1, i);
            i++;
        }
        
        return res;
    }

    /*
        Approach #3 Two pointers [Accepted]
        Algorithm

        Instead of initializing the resres array once with ascending numbers, we can save one iteration over resres if we fill it on the fly. To do this, we can keep on filling the numbers in ascending order in resres for I's found in the pattern ss. Whenever we find a D in the pattern ss, we can store the current position(counting from 1) being filled in the resres array in a pointer jj. Now, whenever we find the first I following this last consecutive set of D's, say at the i^{th}i 
        th
        position(counting from 1) in resres, we know, that the elements from j^{th}j 
        th
        position to the i^{th}i 
        th
        position in resres need to be filled with the numbers from jj to ii in reverse order. Thus, we can fill the numbers in resres array starting from the j^{th}j 
        th
        position, with ii being the number filled at that position and continue the filling in descending order till reaching the i^{th}i 
        th
        position. In this way, we can generate the required arrangement without initializing resres.

        **Complexity Analysis**
        Time complexity : O(n)O(n). The resultant array of size nn is traversed atmost two times, in the worst case e.g. "DDDDDD"

        Space complexity : O(1)O(1). Constant extra space is used.
    */
    vector<int> doit_greedy(string s) {
        
        int n = s.length();
        vector<int> res(n+1);
        res[0] = 1;
        int i = 1;
        
        while (i <= s.length()) {
            
            res[i] = i+1;
            int j = i;
            if (s[i-1] == 'D') {
                while (i <= s.length() && s[i-1] == 'D') i++;
                
                for (int k = j-1, c = i; k <= i-1; k++, c--) {
                    res[k] = c;
                }
            } else {
                i++;
            }
        }
        
        return res;
    }
};