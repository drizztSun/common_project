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
#include <array>
#include <functional>
#include <numeric>
#include <random>
#include <functional>
#include <forward_list>
#include <iomanip>

void test_sort();
void test_partition();
void test_permutation();
void test_max_min();


static bool abs_compare(int a, int b)
{
    return (std::abs(a) < std::abs(b));
}
 
void test_max_min()
{
    {
        // std::max_element
       std::vector<int> v{ 3, 1, -14, 1, 5, 9 };
       std::vector<int>::iterator result;
    
       result = std::max_element(v.begin(), v.end());
       std::cout << "max element at: " << std::distance(v.begin(), result) << '\n';
    
       result = std::max_element(v.begin(), v.end(), abs_compare);
       std::cout << "max element (absolute) at: " << std::distance(v.begin(), result) << '\n';
    }
    
    {
        // std::min_element
       std::vector<int> v{3, 1, 4, 1, 5, 9};
    
       std::vector<int>::iterator result = std::min_element(v.begin(), v.end());
       std::cout << "min element at: " << std::distance(v.begin(), result);
    }
    
    {
        // std::minmax_element
       const auto v = { 3, 9, 1, 4, 2, 5, 9 };
       const auto [min, max] = std::minmax_element(begin(v), end(v));
    
       std::cout << "min = " << *min << ", max = " << *max << '\n';
    }
    
    {
        // std::clamp
        // clamps a value between a pair of boundary values
        // template<class T>
        // constexpr const T& clamp( const T& v, const T& lo, const T& hi );

        // template<class T, class Compare>
        // constexpr const T& clamp( const T& v, const T& lo, const T& hi, Compare comp );
        // 1) If v compares less than lo, returns lo; otherwise if hi compares less than v, returns hi; otherwise returns v. Uses operator< to compare the values.
        std::mt19937 g(std::random_device{}());
        std::uniform_int_distribution<> d(-300, 300);
        std::cout << " raw   clamped to int8_t   clamped to uint8_t\n";
        for(int n = 0; n < 5; ++n) {
            int v = d(g);
            std::cout << std::setw(4) << v
                      << std::setw(20) << std::clamp(v, INT8_MIN, INT8_MAX)
                      << std::setw(21) << std::clamp(v, 0, UINT8_MAX) << '\n';
        }
    }
    
    {
        // std::minmax
        // returns the smaller and larger of two elements
        
       std::vector<int> v {3, 1, 4, 1, 5, 9, 2, 6};
       std::srand(std::time(0));
       std::pair<int, int> bounds = std::minmax(std::rand() % v.size(),
                                                std::rand() % v.size());
    
       std::cout << "v[" << bounds.first << "," << bounds.second << "]: ";
       for (int i = bounds.first; i < bounds.second; ++i) {
           std::cout << v[i] << ' ';
       }
       std::cout << '\n';
    }
}


template <class ForwardIt>
void quicksort(ForwardIt first, ForwardIt last)
{
   if(first == last) return;
   auto pivot = *std::next(first, std::distance(first,last)/2);
   ForwardIt middle1 = std::partition(first, last,
                        [pivot](const auto& em){ return em < pivot; });
   ForwardIt middle2 = std::partition(middle1, last,
                        [pivot](const auto& em){ return !(pivot < em); });
   quicksort(first, middle1);
   quicksort(middle2, last);
}

void test_partition() {
    
    
    {
        // std::is_partitioned
        // determines if the range is partitioned by the given predicate
        
        // 1) Returns true if all elements in the range [first, last) that satisfy the predicate p appear before all elements that don't. Also returns true if [first, last) is empty.
        
       std::array<int, 9> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        
       auto is_even = [](int i){
           return i % 2 == 0;
       };
        
       std::cout.setf(std::ios_base::boolalpha);
       std::cout << std::is_partitioned(v.begin(), v.end(), is_even) << ' ';
    
       std::partition(v.begin(), v.end(), is_even);
       std::cout << std::is_partitioned(v.begin(), v.end(), is_even) << ' ';
    
       std::reverse(v.begin(), v.end());
       std::cout << std::is_partitioned(v.begin(), v.end(), is_even);
    }
    
    {
        // std::partition
        // divides a range of elements into two groups
        
       std::vector<int> v = {0,1,2,3,4,5,6,7,8,9};
       std::cout << "Original vector:\n    ";
       for(int elem : v) std::cout << elem << ' ';
    
       auto it = std::partition(v.begin(), v.end(), [](int i){
           return i % 2 == 0;
       });
    
       std::cout << "\nPartitioned vector:\n    ";
       std::copy(std::begin(v), it, std::ostream_iterator<int>(std::cout, " "));
       std::cout << " * ";
       std::copy(it, std::end(v), std::ostream_iterator<int>(std::cout, " "));
    
       std::forward_list<int> fl = {1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92};
       std::cout << "\nUnsorted list:\n    ";
       for(int n : fl) std::cout << n << ' ';
       std::cout << '\n';
    
       quicksort(std::begin(fl), std::end(fl));
       std::cout << "Sorted using quicksort:\n    ";
       for(int fi : fl) std::cout << fi << ' ';
       std::cout << '\n';
    }
    
    {
        // std::partition_copy
        // copies a range dividing the elements into two groups
        
        // 1) Copies the elements from the range [first, last) to two different ranges depending on the value returned by the predicate p. The elements that satisfy the predicate p are copied to the range beginning at d_first_true. The rest of the elements are copied to the range beginning at d_first_false.
        // The behavior is undefined if the input range overlaps either of the output ranges.
        
       int arr [10] = {1,2,3,4,5,6,7,8,9,10};
       int true_arr [5] = {0};
       int false_arr [5] = {0};
    
       std::partition_copy(std::begin(arr), std::end(arr),
                           std::begin(true_arr),std::begin(false_arr),
                           [] (int i) {return i > 5;
       });
    
       std::cout << "true_arr: ";
       for (int x : true_arr) {
           std::cout << x << ' ';
       }
       std::cout << '\n';
    
       std::cout << "false_arr: ";
       for (int x : false_arr) {
           std::cout << x << ' ';
       }
       std::cout << '\n';
    }
    
    {
        // std::stable_partition
        // divides elements into two groups while preserving their relative order
        
        // 1) Reorders the elements in the range [first, last) in such a way that all elements for which the predicate p
        // returns true precede the elements for which predicate p returns false. Relative order of the elements is preserved.
        std::vector<int> v{0, 0, 3, 0, 2, 4, 5, 0, 7};
        std::stable_partition(v.begin(), v.end(), [](int n){return n>0;});
        for (int n : v) {
            std::cout << n << ' ';
        }
    }
    
    {
        // std::partition_point
        // locates the partition point of a partitioned range
        
        // Examines the partitioned (as if by std::partition) range [first, last) and locates the end of the first partition,
        // that is, the first element that does not satisfy p or last if all elements satisfy p.
        
       std::array<int, 9> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    
       auto is_even = [](int i){ return i % 2 == 0; };
       std::partition(v.begin(), v.end(), is_even);
    
       auto p = std::partition_point(v.begin(), v.end(), is_even);
    
       std::cout << "Before partition:\n    ";
       std::copy(v.begin(), p, std::ostream_iterator<int>(std::cout, " "));
       std::cout << "\nAfter partition:\n    ";
       std::copy(p, v.end(), std::ostream_iterator<int>(std::cout, " "));
    }
}





struct Employee
{
    int age;
    std::string name;  // Does not participate in comparisons
};
 
bool operator<(const Employee & lhs, const Employee & rhs)
{
    return lhs.age < rhs.age;
}

void test_sort() {
    
    {
        // is_sorted
        // checks whether a range is sorted into ascending order
        
        // template< class ForwardIt >
        // bool is_sorted( ForwardIt first, ForwardIt last );
        
        // template< class ForwardIt, class Compare >
        // bool is_sorted( ForwardIt first, ForwardIt last, Compare comp );
        
       int digits[] = {3, 1, 4, 1, 5};
    
       for (auto i : digits) std::cout << i << ' ';
       std::cout << ": is_sorted: " << std::boolalpha << std::is_sorted(std::begin(digits), std::end(digits)) << '\n';
    
       std::sort(std::begin(digits), std::end(digits));
    
       for (auto i : digits)
           std::cout << i << ' ';
       std::cout << ": is_sorted: " << std::is_sorted(std::begin(digits), std::end(digits)) << '\n';
    }
    
    {
        // std::is_sorted_until
        // finds the largest sorted subrange
        
        // template< class ForwardIt >
        // ForwardIt is_sorted_until( ForwardIt first, ForwardIt last );
        
        // template< class ForwardIt, class Compare >
        // ForwardIt is_sorted_until( ForwardIt first, ForwardIt last, Compare comp );
        
       std::random_device rd;
       std::mt19937 g(rd());
       const int N = 6;
       int nums[N] = {3, 1, 4, 1, 5, 9};
    
       const int min_sorted_size = 4;
       int sorted_size = 0;
       do {
           std::shuffle(nums, nums + N, g);
           int *sorted_end = std::is_sorted_until(nums, nums + N);
           sorted_size = std::distance(nums, sorted_end);
    
           for (auto i : nums) std::cout << i << ' ';
           std::cout << " : " << sorted_size << " initial sorted elements\n";
       } while (sorted_size < min_sorted_size);
    }
    
    {
        // std::sort
        // sorts a range into ascending order
        
        // template< class RandomIt >
        // void sort( RandomIt first, RandomIt last );
        
        // template< class RandomIt, class Compare >
        // void sort( RandomIt first, RandomIt last, Compare comp );
        
           std::array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
        
           // sort using the default operator<
           std::sort(s.begin(), s.end());
           for (auto a : s) {
               std::cout << a << " ";
           }
           std::cout << '\n';
        
           // sort using a standard library compare function object
           std::sort(s.begin(), s.end(), std::greater<int>());
           for (auto a : s) {
               std::cout << a << " ";
           }
           std::cout << '\n';
        
           // sort using a custom function object
           // using default struct
           struct {
               bool operator()(int a, int b) const
               {
                   return a < b;
               }
           } customLess;
           std::sort(s.begin(), s.end(), customLess);
           for (auto a : s) {
               std::cout << a << " ";
           }
           std::cout << '\n';
        
           // sort using a lambda expression
           std::sort(s.begin(), s.end(), [](int a, int b) {
               return a > b;
           });
           for (auto a : s) {
               std::cout << a << " ";
           }
           std::cout << '\n';
    }
    
    {
        // std::partial_sort
        // sorts the first N elements of a range
        
        // template< class RandomIt >
        // void partial_sort( RandomIt first, RandomIt middle, RandomIt last );
        
        // template< class RandomIt, class Compare >
        // void partial_sort( RandomIt first, RandomIt middle, RandomIt last, Compare comp );
        
       std::array<int, 10> s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    
       std::partial_sort(s.begin(), s.begin() + 3, s.end());
       for (int a : s) {
           std::cout << a << " ";
       } // 0 1 2 7 8 6 5 9 4 3
    }
    
    {
        // std::partial_sort_copy
        // copies and partially sorts a range of elements
        
        // Sorts some of the elements in the range [first, last) in ascending order, storing the result in the range [d_first, d_last).
        // At most d_last - d_first of the elements are placed sorted to the range [d_first, d_first + n).
        // n is the number of elements to sort (n = min(last - first, d_last - d_first)). The order of equal elements is not guaranteed to be preserved.
       std::vector<int> v0{4, 2, 5, 1, 3};
       std::vector<int> v1{10, 11, 12};
       std::vector<int> v2{10, 11, 12, 13, 14, 15, 16};
       std::vector<int>::iterator it;
    
       it = std::partial_sort_copy(v0.begin(), v0.end(), v1.begin(), v1.end());
    
       std::cout << "Writing to the smaller vector in ascending order gives: ";
       for (int a : v1) {
           std::cout << a << " ";
       }
       std::cout << '\n';
       if(it == v1.end())
           std::cout << "The return value is the end iterator\n";
    
       it = std::partial_sort_copy(v0.begin(), v0.end(), v2.begin(), v2.end(),
                                   std::greater<int>());
    
       std::cout << "Writing to the larger vector in descending order gives: ";
       for (int a : v2) {
           std::cout << a << " ";
       }
       std::cout << '\n' << "The return value is the iterator to " << *it << '\n';
    }
    
    {
        // std::stable_sort
        // sorts a range of elements while preserving order between equal elements
        
        // template< class RandomIt >
        // void stable_sort( RandomIt first, RandomIt last );
    
        // template< class RandomIt, class Compare >
        // void stable_sort( RandomIt first, RandomIt last, Compare comp );
        
       std::vector<Employee> v =
       {
           {108, "Zaphod"},
           {32, "Arthur"},
           {108, "Ford"},
       };
    
       std::stable_sort(v.begin(), v.end());
    
       for (const Employee & e : v)
           std::cout << e.age << ", " << e.name << '\n';
        // 32, Arthur
        // 108, Zaphod
        // 108, Ford
    }
    
    {
        // std::nth_element
        // partially sorts the given range making sure that it is partitioned by the given element
        
        // nth_element is a partial sorting algorithm that rearranges elements in [first, last) such that:

        // The element pointed at by nth is changed to whatever element would occur in that position if [first, last) were sorted.
        // All of the elements before this new nth element are less than or equal to the elements after the new nth element.
        // More formally, nth_element partially sorts the range [first, last) in ascending order so that the condition !(*j < *i) (for (1-2), or comp(*j, *i) == false for (3-4)) is met for any i in the range [first, nth) and for any j in the range [nth, last). The element placed in the nth position is exactly the element that would occur in this position if the range was fully sorted.

        // nth may be the end iterator, in this case the function has no effect.
        
       std::vector<int> v{5, 6, 4, 3, 2, 6, 7, 9, 3};
    
       std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
       std::cout << "The median is " << v[v.size()/2] << '\n';
    
       std::nth_element(v.begin(), v.begin()+1, v.end(), std::greater<int>());
       std::cout << "The second largest element is " << v[1] << '\n';
    }
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
    
    // test_permutation
    {
        // std::is_permutation
        // determines if a sequence is a permutation of another sequence
        
           std::vector<int> v1{1,2,3,4,5};
           std::vector<int> v2{3,5,4,1,2};
           std::cout << "3,5,4,1,2 is a permutation of 1,2,3,4,5? "
                     << std::boolalpha
                     << std::is_permutation(v1.begin(), v1.end(), v2.begin()) << '\n';
        
        // 3,5,4,1,2 is a permutation of 1,2,3,4,5? true
        
           std::vector<int> v3{3,5,4,1,1};
           std::cout << "3,5,4,1,1 is a permutation of 1,2,3,4,5? "
                     << std::boolalpha
                     << std::is_permutation(v1.begin(), v1.end(), v3.begin()) << '\n';
        
        // 3,5,4,1,1 is a permutation of 1,2,3,4,5? false
    }
    
    {
        // std::next_permutation
        // generates the next greater lexicographic permutation of a range of elements
        
       std::string s = "aba";
       std::sort(s.begin(), s.end());
       do {
           std::cout << s << '\n';
       } while(std::next_permutation(s.begin(), s.end()));
    }
    
    {
        // std::prev_permutation
        // generates the next smaller lexicographic permutation of a range of elements
        
        std::string s="abc";
        std::sort(s.begin(), s.end(), std::greater<char>());
        do {
            std::cout << s << ' ';
        } while(std::prev_permutation(s.begin(), s.end()));
        std::cout << '\n';
        // cba cab bca bac acb abc
    }
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
        // finds the first position where two ranges differ
        
        // template< class InputIt1, class InputIt2 >
        // std::pair<InputIt1,InputIt2> mismatch( InputIt1 first1, InputIt1 last1, InputIt2 first2 );
        
        // template< class InputIt1, class InputIt2, class BinaryPredicate >
        // constexpr std::pair<InputIt1,InputIt2>
        // mismatch( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p );
        
        auto mirror_ends = [](const std::string& in) -> std::string {
            return std::string(in.begin(), std::mismatch(in.begin(), in.end(), in.rbegin()).first);
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
