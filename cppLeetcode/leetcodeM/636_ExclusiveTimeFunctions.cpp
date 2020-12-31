/*

636. Exclusive Time of Functions

On a single-threaded CPU, we execute a program containing n functions. Each function has a unique ID between 0 and n-1.

Function calls are stored in a call stack: when a function call starts, its ID is pushed onto the stack, and when a function call ends, its ID is popped off the stack. The function whose ID is at the top of the stack is the current function being executed. Each time a function starts or ends, we write a log with the ID, whether it started or ended, and the timestamp.

You are given a list logs, where logs[i] represents the ith log message formatted as a string "{function_id}:{"start" | "end"}:{timestamp}". For example, "0:start:3" means a function call with function ID 0 started at the beginning of timestamp 3, and "1:end:2" means a function call with function ID 1 ended at the end of timestamp 2. Note that a function can be called multiple times, possibly recursively.

A function's exclusive time is the sum of execution times for all function calls in the program. For example, if a function is called twice, one call executing for 2 time units and another call executing for 1 time unit, the exclusive time is 2 + 1 = 3.

Return the exclusive time of each function in an array, where the value at the ith index represents the exclusive time for the function with ID i.

 

Example 1:


Input: n = 2, logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]
Output: [3,4]
Explanation:
Function 0 starts at the beginning of time 0, then it executes 2 for units of time and reaches the end of time 1.
Function 1 starts at the beginning of time 2, executes for 4 units of time, and ends at the end of time 5.
Function 0 resumes execution at the beginning of time 6 and executes for 1 unit of time.
So function 0 spends 2 + 1 = 3 units of total time executing, and function 1 spends 4 units of total time executing.
Example 2:

Input: n = 1, logs = ["0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"]
Output: [8]
Explanation:
Function 0 starts at the beginning of time 0, executes for 2 units of time, and recursively calls itself.
Function 0 (recursive call) starts at the beginning of time 2 and executes for 4 units of time.
Function 0 (initial call) resumes execution then immediately calls itself again.
Function 0 (2nd recursive call) starts at the beginning of time 6 and executes for 1 unit of time.
Function 0 (initial call) resumes execution at the beginning of time 7 and executes for 1 unit of time.
So function 0 spends 2 + 4 + 1 + 1 = 8 units of total time executing.
Example 3:

Input: n = 2, logs = ["0:start:0","0:start:2","0:end:5","1:start:6","1:end:6","0:end:7"]
Output: [7,1]
Explanation:
Function 0 starts at the beginning of time 0, executes for 2 units of time, and recursively calls itself.
Function 0 (recursive call) starts at the beginning of time 2 and executes for 4 units of time.
Function 0 (initial call) resumes execution then immediately calls function 1.
Function 1 starts at the beginning of time 6, executes 1 units of time, and ends at the end of time 6.
Function 0 resumes execution at the beginning of time 6 and executes for 2 units of time.
So function 0 spends 2 + 4 + 1 = 7 units of total time executing, and function 1 spends 1 unit of total time executing.
Example 4:

Input: n = 2, logs = ["0:start:0","0:start:2","0:end:5","1:start:7","1:end:7","0:end:8"]
Output: [8,1]
Example 5:

Input: n = 1, logs = ["0:start:0","0:end:0"]
Output: [1]


*/
#include <stack>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::stack;



class ExclusiveTime {

public:
    
    vector<int> doit_stack_1(int n, vector<string>& logs) {
        
        vector<int> ans(n, 0);
        vector<vector<int>> buf;
        int last = -1, lasttime = -1;
        
        for (auto& c : logs) {
            
            int i = 0;
            int func = -1, action = -1, time = 0;
            for (int j = 0; j < c.length(); j++) {
                
                if (c[j] == ':') {
                    if (i == 0) {
                        func = std::stoi(c.substr(0, j));
                        i = j+1;
                    } else {
                        
                        if (c.substr(i, j - i) == "start") {
                            action = 1;
                        } else {
                            action = 0;
                        }
                        
                        time = std::stoi(c.substr(j+1, c.length() - j - 1));
                        break;
                    }
                }
            }
            
            if (action) {
                buf.push_back({func, time, 0});
            } else {
                vector<int> tmp = buf.back();
                buf.pop_back();
                
                int spent = time - tmp[1] + 1 - tmp[2];
                ans[func] += spent;
                
                if (!buf.empty())
                    buf.back()[2] += time - tmp[1] + 1;
                
            }
        }
        
        return ans;
    }
    
    vector<int> doit_stack(int n, vector<string>& logs) {

        stack<vector<int>> st;
        vector<int> ans(n);

        for (const auto& c : logs) {

            int i = c.find_first_of(':'), j = c.find_last_of(':');

            string action = c.substr(1+1, j-i-1);

            int c1 = std::stoi(c.substr(0, i)), c2 = std::stoi(c.substr(j+1, c.length()-j-1));

            if (action == "start") {
                st.push(vector<int>{c1, c2, 0});
            } else {
                auto& c = st.top();

                int v0 = c[0], v1 = c[1], v2 = c[2];

                int total = c2 - v1 + 1;

                st.pop();

                if (!st.empty())
                    st.top()[2] += total;

                ans[v0] += total - v2;
            }

        }

        return ans;
    }
};


