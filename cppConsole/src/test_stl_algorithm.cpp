/*
 
 Algorithms library
  C++ Algorithm library
 The algorithms library defines functions for a variety of purposes (e.g. searching, sorting, counting, manipulating) that operate on ranges of elements. Note that a range is defined as [first, last) where last refers to the element past the last element to inspect or modify.

 Constrained algorithms
 C++20 provides constrained versions of most algorithms in the namespace std::ranges. In these algorithms, a range can be specified as either an iterator-sentinel pair or as a single range argument, and projections and pointer-to-member callables are supported. Additionally, the return types of most algorithms have been changed to return all potentially useful information computed during the execution of the algorithm.

 std::vector<int> v = {7, 1, 4, 0, -1};
 std::ranges::sort(v); // constrained algorithm
 The header <iterator> provides a set of concepts and related utilities designed to ease constraining common algorithm operations.
 
 
 */

#include <stdio.h>

#include <algorithm>


void test_sort() {
    
}

void test_heap() {
    
}

void test_permutation() {
    
}

void test_for_each() {
    
}



void test_algorithm() {
    
    test_sort();
}
