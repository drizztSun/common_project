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

#include <functional>
#include <numeric>

#include <functional>


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

template <typename Container>
bool in_quote(const Container& cont, const std::string& s)
{
    return std::search(cont.begin(), cont.end(), s.begin(), s.end()) != cont.end();
}

void test_for_each() {
    
    /*  Non-modifying sequence operations  */
    
    {
        // for_each
        // applies a function to a range of elements
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
        // std::all_of, any_of, none_of
        // checks if a predicate is true for all, any or none of the elements in a range
           std::vector<int> v(10, 2);
           std::partial_sum(v.cbegin(), v.cend(), v.begin());
           std::cout << "Among the numbers: ";
           std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
           std::cout << '\n';
        
           if (std::all_of(v.cbegin(), v.cend(), [](int i){ return i % 2 == 0; })) {
               std::cout << "All numbers are even\n";
           }
           if (std::none_of(v.cbegin(), v.cend(), std::bind(std::modulus<int>(),
                                                            std::placeholders::_1, 2))) {
               std::cout << "None of them are odd\n";
           }
           struct DivisibleBy
           {
               const int d;
               DivisibleBy(int n) : d(n) {}
               bool operator()(int n) const { return n % d == 0; }
           };
        
           if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(7))) {
               std::cout << "At least one number is divisible by 7\n";
           }
    }
    
    
    {
        // std::count, std::count_if
        // returns the number of elements satisfying specific criteria
       std::vector<int> v{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };
    
       // determine how many integers in a std::vector match a target value.
       int target1 = 3;
       int target2 = 5;
       int num_items1 = std::count(v.begin(), v.end(), target1);
       int num_items2 = std::count(v.begin(), v.end(), target2);
       std::cout << "number: " << target1 << " count: " << num_items1 << '\n';
       std::cout << "number: " << target2 << " count: " << num_items2 << '\n';
    
       // use a lambda expression to count elements divisible by 3.
       int num_items3 = std::count_if(v.begin(), v.end(), [](int i) {
           return i % 3 == 0;
       });
       std::cout << "number divisible by three: " << num_items3 << '\n';
    }
    
    {
        // std::find, std::find_if, std::find_if_not
        // finds the first element satisfying specific criteria
        
        // template< class InputIt, class T >
        // InputIt find( InputIt first, InputIt last, const T& value ); (since C++20)

        // template< class InputIt, class UnaryPredicate >
        // bInputIt find_if( InputIt first, InputIt last, UnaryPredicate p );

        // template< class InputIt, class UnaryPredicate >
        // InputIt find_if_not( InputIt first, InputIt last, UnaryPredicate q );
        
       int n1 = 3;
       int n2 = 5;
    
       std::vector<int> v{0, 1, 2, 3, 4};
    
       auto result1 = std::find(std::begin(v), std::end(v), n1);
       auto result2 = std::find(std::begin(v), std::end(v), n2);
    
       if (result1 != std::end(v)) {
           std::cout << "v contains: " << n1 << '\n';
       } else {
           std::cout << "v does not contain: " << n1 << '\n';
       }
    
       if (result2 != std::end(v)) {
           std::cout << "v contains: " << n2 << '\n';
       } else {
           std::cout << "v does not contain: " << n2 << '\n';
       }
        
        auto res1 = std::find_if(std::begin(v), std::end(v), [](auto a) {
            return a % 2 == 0;
        });
        
        auto res2 = std::find_if_not(std::begin(v), std::end(v), [](auto a) {
            return a % 2 == 0;
        });
    }
    
    {
        // std::find_first_of
        // searches for any one of a set of elements
        
        // template< class ForwardIt1, class ForwardIt2>
        // ForwardIt1 find_first_of( ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last );
        
        // template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
        // ForwardIt1 find_first_of( ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p );
        
        // Searches the range [first, last) for any of the elements in the range [s_first, s_last).

        // 1) Elements are compared using operator==.
        // 3) Elements are compared using the given binary predicate p.
       std::vector<int> v{0, 2, 3, 25, 5};
       std::vector<int> t{3, 19, 10, 2};
    
       auto result = std::find_first_of(v.begin(), v.end(), t.begin(), t.end());
    
       if (result == v.end()) {
           std::cout << "no elements of v were equal to 3, 19, 10 or 2\n";
       } else {
           std::cout << "found a match at "
                     << std::distance(v.begin(), result) << "\n";
       }
        
        auto res = std::find_first_of(v.begin(), v.end(), t.begin(), t.end(), [](auto& c, auto& d) {
            return c + d > 30;
        });
        
    }
    
    {
        // std::find_end
        // finds the last sequence of elements in a certain range
        
        // template< class ForwardIt1, class ForwardIt2 >
        // ForwardIt1 find_end( ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last );
        
        // template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
        // constexpr ForwardIt1 find_end( ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p );
    
       std::vector<int> v{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
       std::vector<int>::iterator result;
    
       std::vector<int> t1{1, 2, 3};
    
       result = std::find_end(v.begin(), v.end(), t1.begin(), t1.end());
       if (result == v.end()) {
           std::cout << "sequence not found\n";
       } else {
           std::cout << "last occurrence is at: "
                     << std::distance(v.begin(), result) << "\n";
       }
    
       std::vector<int> t2{4, 5, 6};
        result = std::find_end(v.begin(), v.end(), t2.begin(), t2.end(), [](auto& c, auto& d) {
            return c * d > 10;
        });
        
       if (result == v.end()) {
           std::cout << "sequence not found\n";
       } else {
           std::cout << "last occurrence is at: "
                     << std::distance(v.begin(), result) << "\n";
       }
        
    }
    
    
    {
        // adjacent_find
        // finds the first two adjacent items that are equal (or satisfy a given predicate)
        
        // template< class ForwardIt >
        // ForwardIt adjacent_find( ForwardIt first, ForwardIt last );
        
        // template< class ForwardIt, class BinaryPredicate>
        // ForwardIt adjacent_find( ForwardIt first, ForwardIt last, BinaryPredicate p );
       std::vector<int> v1{0, 1, 2, 3, 40, 40, 41, 41, 5};
    
       auto i1 = std::adjacent_find(v1.begin(), v1.end());
    
       if (i1 == v1.end()) {
           std::cout << "no matching adjacent elements\n";
       } else {
           std::cout << "the first adjacent pair of equal elements at: "
                     << std::distance(v1.begin(), i1) << '\n';
       }
    
       auto i2 = std::adjacent_find(v1.begin(), v1.end(), std::greater<int>());
       if (i2 == v1.end()) {
           std::cout << "The entire vector is sorted in ascending order\n";
       } else {
           std::cout << "The last element in the non-decreasing subsequence is at: "
                     << std::distance(v1.begin(), i2) << '\n';
       }
    }
    
    {
        // search
        // searches for a range of elements
        
        // template< class ForwardIt1, class ForwardIt2 >
        // ForwardIt1 search( ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last );
        
        // template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
        // ForwardIt1 search( ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p );
        
       std::string str = "why waste time learning, when ignorance is instantaneous?";
       // str.find() can be used as well
       std::cout << std::boolalpha << in_quote(str, "learning") << '\n'
                                   << in_quote(str, "lemming")  << '\n';
    
       std::vector<char> vec(str.begin(), str.end());
       std::cout << std::boolalpha << in_quote(vec, "learning") << '\n'
                                   << in_quote(vec, "lemming")  << '\n';
    
       // The C++17 overload demo:
       std::string in = "Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
                        " sed do eiusmod tempor incididunt ut labore et dolore magna aliqua";
       std::string needle = "pisci";
        
       auto it = std::search(in.begin(), in.end(),
                      //std::boyer_moore_searcher(
                         needle.begin(), needle.end());
       if(it != in.end())
           std::cout << "The string " << needle << " found at offset "
                     << it - in.begin() << '\n';
       else
           std::cout << "The string " << needle << " not found\n";
        
    }
    
    {
        // search_n
        // searches a range for a number of consecutive copies of an element
        // 1) Elements are compared using operator==.
        // 3) Elements are compared using the given binary predicate p.
       std::vector<int> v1{0, 1, 2, 3, 40, 40, 41, 41, 5};
    
       auto i1 = std::adjacent_find(v1.begin(), v1.end());
    
       if (i1 == v1.end()) {
           std::cout << "no matching adjacent elements\n";
       } else {
           std::cout << "the first adjacent pair of equal elements at: "
                     << std::distance(v1.begin(), i1) << '\n';
       }
    
       auto i2 = std::adjacent_find(v1.begin(), v1.end(), std::greater<int>());
       if (i2 == v1.end()) {
           std::cout << "The entire vector is sorted in ascending order\n";
       } else {
           std::cout << "The last element in the non-decreasing subsequence is at: "
                     << std::distance(v1.begin(), i2) << '\n';
       }
    }
    
    {
        // std::mismatch
        // template< class InputIt1, class InputIt2 >
        // std::pair<InputIt1,InputIt2> mismatch( InputIt1 first1, InputIt1 last1, InputIt2 first2 );
        
        // template< class InputIt1, class InputIt2, class BinaryPredicate >
        // constexpr std::pair<InputIt1,InputIt2>
        // mismatch( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p );
        
        auto mirror_ends = [](const std::string& in) -> std::string {
            return std::string(in.begin(),
                               std::mismatch(in.begin(), in.end(), in.rbegin()).first);
        };
        
        std::cout << mirror_ends("abXYZba") << '\n'
                     << mirror_ends("abca") << '\n'
                     << mirror_ends("aba") << '\n';
    }
}




void test_algorithm() {
    
    test_for_each();
    
    test_sort();
}
