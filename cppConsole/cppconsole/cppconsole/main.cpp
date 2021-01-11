//
//  main.cpp
//  cppconsole
//
//  Created by Yuxin Sun on 3/15/20.
//  Copyright © 2020 Yuxin Sun. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <unordered_map>
#include <queue>
#include <unordered_set>


using std::unordered_set;
using std::unordered_map;
using std::string;
using std::vector;
using std::queue;

void TestUnorderMap();

void Test_Unordered_set();

void test_vector_morden_cpp();

void Test_share_ptr();

void test_constrexpr();

void test_deque();

void test_stack();

void Test_move_forward();

void Test_value_categories();

void Test_fold_expression();

void Test_type_deduce();

void test_basic();

void test_async();

void test_function_able();

void Test_priority_queue();

void TestUnorderMap();

void Test_map();



int treeDiameter(vector<vector<int>>&& edges) {
    vector<vector<int>> graph(edges.size()+1);

    for (auto& c : edges) {
        graph[c[0]].push_back(c[1]);
        graph[c[1]].push_back(c[0]);
    }

    auto bfs = [&](int org) -> std::pair<int, int> {
        
        queue<std::pair<int,int>> qu;
        qu.push({org, 0});
        unordered_set<int> seen;
        seen.insert(org);
        int maxdepth = 0, node = 0;

        while (!qu.empty()) {

            int size = qu.size();

            while (size--) {

                auto [cur, dep] = qu.front();
                qu.pop();
                if (maxdepth < dep) {
                    maxdepth = dep;
                    node = cur;
                }

                for (auto nc : graph[cur]) {

                    if (seen.find(nc) == seen.end()) {
                        seen.insert(nc);
                        qu.push({nc, dep + 1});
                    }
                }
            }
        }

        return {node, maxdepth};
    };

    auto [n, depth1] = bfs(0);

    auto [n2, depth2] = bfs(n);

    return depth2;
}

int main(int argc, const char * argv[]) {


    treeDiameter(vector<vector<int>>{{0, 1}, {0, 2}});
    
    
    // Test_map();
    
    // TestUnorderMap();
    
    // Test_priority_queue();
    
    // test_function_able();
    
    // test_basic();
    
    // Test_type_deduce();
    
    // Test_fold_expression();
    
    // Test_value_categories();
    
    // Test_move_forward();

    // TestUnorderMap();

    // Test_Unordered_set();

    // test_vector_morden_cpp();

    // Test_share_ptr();
    
    // test_constrexpr();
    
    // test_deque();
    
    // test_stack();
    
    // test_async();

    return 1;
}

