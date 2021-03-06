/*
 
 
 636. Exclusive Time of Functions
 
 On a single threaded CPU, we execute some functions.  Each function has a unique id between 0 and N-1.

 We store logs in timestamp order that describe when a function is entered or exited.

 Each log is a string with this format: "{function_id}:{"start" | "end"}:{timestamp}".
 
 For example, "0:start:3" means the function with id 0 started at the beginning of timestamp 3.
              "1:end:2" means the function with id 1 ended at the end of timestamp 2.

 A function's exclusive time is the number of units of time spent in this function.
 Note that this does not include any recursive calls to child functions.

 The CPU is single threaded which means that only one function is being executed at a given time unit.

 Return the exclusive time of each function, sorted by their function id.

Example 1:
  
 Input:
 n = 2
 logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]
 Output: [3, 4]

 Explanation:
 Function 0 starts at the beginning of time 0, then it executes 2 units of time and reaches the end of time 1.
 Now function 1 starts at the beginning of time 2, executes 4 units of time and ends at time 5.
 Function 0 is running again at the beginning of time 6, and also ends at the end of time 6, thus executing for 1 unit of time.
 So function 0 spends 2 + 1 = 3 units of total time executing, and function 1 spends 4 units of total time executing.

 
 */

#include <vector>
#include <stack>
#include <string>

using std::vector;
using std::string;
using std::stack;


class ExclusiveTime {
    /*
            636.Exclusive-Time-of-Functions
        很明显此题应该用到栈。遇到start就入栈，遇到end就出栈。

        stack<pair<int,int>>Stack; //记录id和时刻
        遇到end（该事件的结束点）时，出栈一个元素（该事件的起始点）做匹配，算出这个事件A的时间差，累计在这个事件A上（用一个数组来记录）。
        同时，因为这个事件A占用的时间要从它的上级事件中扣除，所以还要考察此时的栈顶元素B，在相应B的runtime记录里减去这段时间。这种补偿只需要做一次，因为等事件B退栈时，所占用的总时间（包括A的）也会再从更上级事件C里面扣除的。以此类推。

        注意start和end的计时标准不一致。比较巧妙的方法就是对于end所标记的时刻，人为加上1，这样计算时间差的时候就可以直接相减。
    */
    vector<int> doit_stack(int n, vector<string>& logs) 
    {
        stack<std::pair<int,int>>Stack;
        vector<int>results(n,0);
        
        for (auto s: logs)
        {
            int pos1 = s.find(":",0);
            int pos2 = s.find(":",pos1+1);
            int id = stoi(s.substr(0,pos1));
            bool flag = s.substr(pos1+1,pos2-pos1-1)=="start"? true:false;
            int timeStamp = stoi(s.substr(pos2+1));
            
            if (flag)
                Stack.push({id,timeStamp});
            else
            {
                int start = Stack.top().second;
                int duration = timeStamp - start + 1;
                results[id] += duration;
                Stack.pop();
                
                if (!Stack.empty())
                {
                    int prevId = Stack.top().first;
                    results[prevId] -= duration;
                }
            }            
        }
        
        return results;
    }
public:
    
    vector<int> doit_stack(int n, vector<string>&& logs) {
        
        vector<int> ans(n, 0);
        vector<vector<int>> buf;
        
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
    
    vector<int> doit1(int n, vector<string>&& logs) {
        int len = logs.size();
        if(len==0) return {};
        vector<int> res(n);
        stack<int> my; // taskID
        int pretime = 0;
        for(string log : logs) {
            int i= log.find(':');
            int j= log.find_last_of(':');
            int taskid = stoi( log.substr(0, i) );
            int ts = stoi( log.substr(j+1) );
            string status = log.substr(i+1, j-i-1);
            if(!my.empty())
                res[my.top()] += ts - pretime;
            pretime = ts;
            if(status == "start")
                my.push(taskid);
            else {
                res[my.top()]++; my.pop();
                pretime++;
            }
        }
        return res;
    }
};

void test_636_exclusive_time_of_functions() {
    
    auto res1 = ExclusiveTime().doit(2, vector<string>{"0:start:0","1:start:2","1:end:5","0:end:6"});
    
    auto res2 = ExclusiveTime().doit(1, vector<string>{"0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"});
    
    auto res3 = ExclusiveTime().doit(2, vector<string>{"0:start:0","0:start:2","0:end:5","1:start:6","1:end:6","0:end:7"});

    return;
}
