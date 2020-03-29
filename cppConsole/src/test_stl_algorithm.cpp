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
#include <iostream>

#include <vector>
using std::vector;

#include <algorithm>


void test_sort() {
    
}

void test_heap() {
    
    // Heap operations
    
    {
        // make_heap
        /*
            template< class RandomIt >
            void make_heap( RandomIt first, RandomIt last );
            (until C++20)
            template< class RandomIt >
            constexpr void make_heap( RandomIt first, RandomIt last );
            (since C++20)
            (2)
            template< class RandomIt, class Compare >
            void make_heap( RandomIt first, RandomIt last,
                            Compare comp );
            (until C++20)
            template< class RandomIt, class Compare >
            constexpr void make_heap( RandomIt first, RandomIt last,
                                      Compare comp );
         
         Constructs a max heap in the range [first, last). The first version of the function uses operator< to compare the elements,
         the second uses the given comparison function comp.
         */
        
           std::cout << "Max heap:\n";
        
           std::vector<int> v { 3, 2, 4, 1, 5, 9 };
        
           std::cout << "initially, v: ";
           for (auto i : v)
               std::cout << i << ' ';
           std::cout << '\n';
        
           std::make_heap(v.begin(), v.end());
        
           std::cout << "after make_heap, v: ";
           for (auto i : v)
               std::cout << i << ' ';
           std::cout << '\n';
        
           std::pop_heap(v.begin(), v.end());
        
           std::cout << "after pop_heap, v: ";
           for (auto i : v)
               std::cout << i << ' ';
           std::cout << '\n';
        
           auto top = v.back();
           v.pop_back();
           std::cout << "former top element: " << top << '\n';
        
           std::cout << "after removing the former top element, v: ";
           for (auto i : v)
               std::cout << i << ' ';
           std::cout << '\n' << '\n';
        
           std::cout << "Min heap:\n";
        
           std::vector<int> v1 { 3, 2, 4, 1, 5, 9 };
        
           std::cout << "initially, v1: ";
           for (auto i : v1)
               std::cout << i << ' ';
           std::cout << '\n';
        
           std::make_heap(v1.begin(), v1.end(), std::greater<>{});
        
           std::cout << "after make_heap, v1: ";
           for (auto i : v1)
               std::cout << i << ' ';
           std::cout << '\n';
        
           std::pop_heap(v1.begin(), v1.end(), std::greater<>{});
        
           std::cout << "after pop_heap, v1: ";
           for (auto i : v1)
               std::cout << i << ' ';
           std::cout << '\n';
        
           auto top1 = v1.back();
           v1.pop_back();
           std::cout << "former top element: " << top1 << '\n';
        
           std::cout << "after removing the former top element, v1: ";
           for (auto i : v1)
               std::cout << i << ' ';
           std::cout << '\n';
    }
    
    {
        /*
         // push_heap
         template< class RandomIt >
         void push_heap( RandomIt first, RandomIt last );
         (until C++20)
         template< class RandomIt >
         constexpr void push_heap( RandomIt first, RandomIt last );
         (since C++20)
         (2)
         template< class RandomIt, class Compare >
         void push_heap( RandomIt first, RandomIt last,
                         Compare comp );
         (until C++20)
         template< class RandomIt, class Compare >
         constexpr void push_heap( RandomIt first, RandomIt last,
                                   Compare comp );
         (since C++20)
         Inserts the element at the position last-1 into the max heap defined by the range [first, last-1).
         The first version of the function uses operator< to compare the elements, the second uses the given comparison function comp.
         */
           std::vector<int> v { 3, 1, 4, 1, 5, 9 };
        
           std::make_heap(v.begin(), v.end());
        
           std::cout << "v: ";
           for (auto i : v) std::cout << i << ' ';
           std::cout << '\n';
        
           v.push_back(6);
        
           std::cout << "before push_heap: ";
           for (auto i : v) std::cout << i << ' ';
           std::cout << '\n';
        
           std::push_heap(v.begin(), v.end());
        
           std::cout << "after push_heap: ";
           for (auto i : v) std::cout << i << ' ';
           std::cout << '\n';
    }
    
    {
        // pop_heap
        /*
            template< class RandomIt >
            void pop_heap( RandomIt first, RandomIt last ); (until C++20)
            template< class RandomIt >
            constexpr void pop_heap( RandomIt first, RandomIt last );  (since C++20)
            (2)
            template< class RandomIt, class Compare >
            void pop_heap( RandomIt first, RandomIt last, Compare comp ); (until C++20)
            
            template< class RandomIt, class Compare >
            constexpr void pop_heap( RandomIt first, RandomIt last, Compare comp ); (since C++20)
            Swaps the value in the position first and the value in the position last-1 and makes the subrange [first, last-1) into a heap. This has the effect of removing the first element from the heap defined by the range [first, last).

            The first version of the function uses operator< to compare the elements, which makes the heap a max heap. The second uses the given comparison function comp.
         */
           std::vector<int> v { 3, 1, 4, 1, 5, 9 };
        
           std::make_heap(v.begin(), v.end());
        
           std::cout << "v: ";
           for (auto i : v) std::cout << i << ' ';
           std::cout << '\n';
        
           std::pop_heap(v.begin(), v.end()); // moves the largest to the end
        
           std::cout << "after pop_heap: ";
           for (auto i : v) std::cout << i << ' ';
           std::cout << '\n';
        
           int largest = v.back();
           v.pop_back();  // actually removes the largest element
           std::cout << "largest element: " << largest << '\n';
        
           std::cout << "heap without largest: ";
           for (auto i : v) std::cout << i << ' ';
           std::cout << '\n';
    }
    
    {
        // sort_heap
        /*
         template< class RandomIt >
         void sort_heap( RandomIt first, RandomIt last );  (until C++20)
         template< class RandomIt >
         constexpr void sort_heap( RandomIt first, RandomIt last ); (since C++20)
         
         (2)
         template< class RandomIt, class Compare >
         void sort_heap( RandomIt first, RandomIt last, Compare comp );  (until C++20)
         template< class RandomIt, class Compare >
         constexpr void sort_heap( RandomIt first, RandomIt last, Compare comp ); (since C++20)
         
         Converts the max heap [first, last) into a sorted range in ascending order. The resulting range no longer has the heap property.

         The first version of the function uses operator< to compare the elements, the second uses the given comparison function comp.
         */
        
           std::vector<int> v = {3, 1, 4, 1, 5, 9};
        
           std::make_heap(v.begin(), v.end());
        
           std::cout << "heap:\t";
           for (const auto &i : v) {
               std::cout << i << ' ';
           }
        
           std::sort_heap(v.begin(), v.end());
        
           std::cout << "\nsorted:\t";
           for (const auto &i : v) {
               std::cout << i << ' ';
           }
           std::cout << '\n';
    }
    
    {
        // is_heap
        /*
         template< class RandomIt >
         bool is_heap( RandomIt first, RandomIt last );
         
         template< class RandomIt, class Compare >
         bool is_heap( RandomIt first, RandomIt last, Compare comp );
         
         Checks if the elements in range [first, last) are a max heap.

         1) Elements are compared using operator<.
         3) Elements are compared using the given binary comparison function comp.
         
         */
        
           std::vector<int> v { 3, 1, 4, 1, 5, 9 };
        
           std::cout << "initially, v: ";
           for (auto i : v) std::cout << i << ' ';
           std::cout << '\n';
        
           if (!std::is_heap(v.begin(), v.end())) {
               std::cout << "making heap...\n";
               std::make_heap(v.begin(), v.end());
           }
        
           std::cout << "after make_heap, v: ";
           for (auto i : v) std::cout << i << ' ';
           std::cout << '\n';
    }
    
    {
        // is_heap_until
        /*
         
         template< class RandomIt >
         RandomIt is_heap_until( RandomIt first, RandomIt last );
         
         template< class RandomIt, class Compare >
         RandomIt is_heap_until( RandomIt first, RandomIt last, Compare comp );
                 
        Examines the range [first, last) and finds the largest range beginning at first which is a max heap.

        1) Elements are compared using operator<.
        3) Elements are compared using the given binary comparison function comp.*/
           std::vector<int> v { 3, 1, 4, 1, 5, 9 };
        
           std::make_heap(v.begin(), v.end());
        
           // probably mess up the heap
           v.push_back(2);
           v.push_back(6);
        
           auto heap_end = std::is_heap_until(v.begin(), v.end());
        
           std::cout << "all of v: ";
           for (auto i : v) std::cout << i << ' ';
           std::cout << '\n';
        
           std::cout << "only heap: ";
           for (auto i = v.begin(); i != heap_end; ++i) std::cout << *i << ' ';
           std::cout << '\n';
    }
}

void test_permutation() {
    
}


struct Sum
{
    Sum(): sum{0} { }
    void operator()(int n) { sum += n; }
    int sum;
};

void test_for_each() {
    
    /*  Non-modifying sequence operations  */
    
    {   // for_each
        
        /*
         template< class InputIt, class UnaryFunction >
         UnaryFunction for_each( InputIt first, InputIt last, UnaryFunction f ); (until C++20)
        
          template< class InputIt, class UnaryFunction >
          constexpr UnaryFunction for_each( InputIt first, InputIt last, UnaryFunction f ); (since C++20)
        
          template< class ExecutionPolicy, class ForwardIt, class UnaryFunction2 >
          void for_each( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryFunction2 f );
           
            // 1) Applies the given function object f to the result of dereferencing every iterator in the range [first, last), in order.
           // 2) Applies the given function object f to the result of dereferencing every iterator in the range [first, last) (not necessarily in order). The algorithm is executed according to policy. This overload does not participate in overload resolution unless std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> is true.
         */
        
       std::vector<int> nums{3, 4, 2, 8, 15, 267};
    
       auto print = [](const int& n) { std::cout << " " << n; };
    
       std::cout << "before:";
       std::for_each(nums.begin(), nums.end(), print);
       std::cout << '\n';
    
       std::for_each(nums.begin(), nums.end(), [](int &n){ n++; });
    
       // calls Sum::operator() for each number
       Sum s = std::for_each(nums.begin(), nums.end(), Sum());
    
       std::cout << "after: ";
       std::for_each(nums.begin(), nums.end(), print);
       std::cout << '\n';
       std::cout << "sum: " << s.sum << '\n';
    }
    
    {
        // for_each_n
        /*
         template< class InputIt, class Size, class UnaryFunction >
         InputIt for_each_n( InputIt first, Size n, UnaryFunction f );  (since C++17)  (until C++20)
         template< class InputIt, class Size, class UnaryFunction >
         constexpr InputIt for_each_n( InputIt first, Size n, UnaryFunction f ); (since C++20)
         
         template< class ExecutionPolicy, class ForwardIt, class Size, class UnaryFunction2 >
         ForwardIt for_each_n( ExecutionPolicy&& policy, ForwardIt first, Size n, UnaryFunction2 f ); (2)    (since C++17)
         
         
         */
        std::vector<int> ns{1, 2, 3, 4, 5};
        for (auto n: ns) std::cout << n << ", ";
        std::cout << '\n';
        std::for_each_n(ns.begin(), 3, [](auto& n){ n *= 2; });
        for (auto n: ns) std::cout << n << ", ";
        std::cout << '\n';
    }
    
    {
        //
    }
}



void test_algorithm() {
    
    test_for_each();
    
    test_sort();
}
