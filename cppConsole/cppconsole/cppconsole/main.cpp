//
//  main.cpp
//  cppconsole
//
//  Created by Yuxin Sun on 3/15/20.
//  Copyright © 2020 Yuxin Sun. All rights reserved.
//

#include <iostream>


void TestUnorderMap();

void Test_Unordered_set();

void test_vector_morden_cpp();

void Test_share_ptr();

void test_constrexpr();

void test_deque();

void test_stack();

int main(int argc, const char * argv[]) {

    std::cout << "Hello, World!\n";

    TestUnorderMap();

    Test_Unordered_set();

    test_vector_morden_cpp();

    Test_share_ptr();
    
    test_constrexpr();
    
    test_deque();
    
    test_stack();

    return 1;
}

