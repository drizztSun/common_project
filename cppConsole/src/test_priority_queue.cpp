/*
 template<
     class T,
     class Container = std::vector<T>,
     class Compare = std::less<typename Container::value_type>
 > class priority_queue;
 A priority queue is a container adaptor that provides constant time lookup of the largest (by default) element, at the expense of logarithmic insertion and extraction.

 A user-provided Compare can be supplied to change the ordering, e.g. using std::greater<T> would cause the smallest element to appear as the top().

 Working with a priority_queue is similar to managing a heap in some random access container, with the benefit of not being able to accidentally invalidate the heap.
 
 Template parameters
 T    -    The type of the stored elements. The behavior is undefined if T is not the same type as Container::value_type. (since C++17)
 Container    -    The type of the underlying container to use to store the elements. The container must satisfy the requirements of SequenceContainer, and its iterators must satisfy the requirements of LegacyRandomAccessIterator. Additionally, it must provide the following functions with the usual semantics:
 front()
 push_back()
 pop_back()
 The standard containers std::vector and std::deque satisfy these requirements.

 Compare    -    A Compare type providing a strict weak ordering.
 Note that the Compare parameter is defined such that it returns true if its first argument comes before its second argument in a weak ordering. But because the priority queue outputs largest elements first, the elements that "come before" are actually output last. That is, the front of the queue contains the "last" element according to the weak ordering imposed by Compare.


 */

#include <stdio.h>
#include <queue>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace::std;

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

void test_priority_queue_basic() {
    
    {
        std::priority_queue<int> q;
     
        for(int n : {1,8,5,6,3,4,0,9,7,2})
            q.push(n);
     
        while(!q.empty()) {
            std::cout << q.top() << " ";
            q.pop();
        }
        std::cout << '\n';
    }
    
    {
        std::priority_queue<int, std::vector<int>, std::greater<int> > q2;
         
        for(int n : {1,8,5,6,3,4,0,9,7,2})
            q2.push(n);
         
        print_queue(q2);
    }
    

    {
        // Using lambda to compare elements.
        auto cmp = [](int left, int right) {
            return (left ^ 1) < (right ^ 1);
        };
        
        std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
     
        for(int n : {1,8,5,6,3,4,0,9,7,2})
            q3.push(n);
     
        print_queue(q3);
    }
    
    {
        std::string s("AABBCCDDD");
        
        std::unordered_map<char, int> cnt;
        std::priority_queue<std::pair<int, char>, vector<std::pair<int, char>>, less<std::pair<int, char>>> qu;
        for (auto c: s)
            cnt[c]++;
        for (auto k : cnt) {
            qu.push(std::make_pair(k.second, k.first));
        }
        
        string res = "";
        while (!qu.empty()) {

            std::pair<int, char> pt = qu.top();
            for (; pt.first > 0; pt.first--)
                res += pt.second;
            qu.pop();
        }
        
        std::cout << "res " << res << '\n';
    }
}


void Test_priority_queue() {
    
    test_priority_queue_basic();
}


