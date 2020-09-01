
/*
 
 
 std::to_array
  C++ Containers library std::array
 Defined in header <array>
 template<class T, std::size_t N>
 constexpr std::array<std::remove_cv_t<T>, N> to_array(T (&a)[N]);   (1)    (since C++20)
 
 template<class T, std::size_t N>
 constexpr std::array<std::remove_cv_t<T>, N> to_array(T (&&a)[N]);   (2)    (since C++20)
 
 Creates a std::array from the one dimensional built-in array a. The elements of the std::array are copy-initialized from the corresponding element of a. Copying or moving multidimensional built-in array is not supported.

 1) For every i in 0, ..., N - 1, copy-initializes result's correspond element with a[i]. This overload would be ill-formed when std::is_constructible_v<T, T&> is false.
 2) For every i in 0, ..., N - 1, copy-initializes result's correspond element with std::move(a[i]). This overload would be ill-formed when std::is_move_constructible_v<T> is false.
 Both overloads would be ill-formed when std::is_array_v<T> is true.

 Parameters
 a    -    the built-in array to be converted the std::array
 
 Type requirements
 -T must meet the requirements of CopyConstructible in order to use overload (1).
 -T must meet the requirements of MoveConstructible in order to use overload (2).
 
 Return value
 1) std::array<std::remove_cv_t<T>, N>{ a[0], ..., a[N - 1] }
 2) std::array<std::remove_cv_t<T>, N>{ std::move(a[0]), ..., std::move(a[N - 1]) }
 
 Notes
 There are some occasions where class template argument deduction of std::array cannot be used while to_array being available:

 1) to_array can be used when the element type of the std::array is manually specified and the length is deduced, which is preferable when implicit conversion is wanted.
 2) to_array can copy a string literal, while the class template argument deduction creating a std::array of one pointer to its first character.

 std::to_array<long>({3, 4}); // OK: implicit conversion
 // std::array<long>{3, 4};   // error: too few template arguments
 std::to_array("foo");        // creates std::array<char, 4>{ 'f', 'o', 'o', '\0' }
 std::array{"foo"};           // creates std::array<const char*, 1>{ +"foo" }
 
 
 Possible implementation
 
                *** First version ***
 
 namespace detail {
  
     template <class T, std::size_t N, std::size_t... I>
     constexpr std::array<std::remove_cv_t<T>, N>
         to_array_impl(T (&a)[N], std::index_sequence<I...>)
     {
         return { {a[I]...} };
     }
  
 }
  
 template <class T, std::size_t N>
 constexpr std::array<std::remove_cv_t<T>, N> to_array(T (&a)[N])
 {
     return detail::to_array_impl(a, std::make_index_sequence<N>{});
 }
 
 
            *** Second version ***
 namespace detail {
  
     template <class T, std::size_t N, std::size_t... I>
     constexpr std::array<std::remove_cv_t<T>, N>
         to_array_impl(T (&&a)[N], std::index_sequence<I...>)
     {
         return { {std::move(a[I])...} };
     }
  
 }
  
 template <class T, std::size_t N>
 constexpr std::array<std::remove_cv_t<T>, N> to_array(T (&&a)[N])
 {
     return detail::to_array_impl(std::move(a), std::make_index_sequence<N>{});
 }
 
 */

#include <stdio.h>
#include <type_traits>
#include <utility>
#include <array>
#include <memory>

using namespace std;


void test_to_array() {
    /*
   // copies a string literal
   auto a1 = std::to_array("foo");
   static_assert(a1.size() == 4);

   // deduces both element type and length
   auto a2 = std::to_array({ 0, 2, 1, 3 });
   static_assert(std::is_same_v<decltype(a2), std::array<int, 4>>);

   // deduces length with element type specified
   // implicit conversion happens
   auto a3 = std::to_array<long>({ 0, 1, 3 });
   static_assert(std::is_same_v<decltype(a3), std::array<long, 3>>);

   auto a4 = std::to_array<std::pair<int, float>>(
       { { 3, .0f }, { 4, .1f }, { 4, .1e23f } });
   static_assert(a4.size() == 3);

   // creates a non-copyable std::array
   auto a5 = std::to_array({ std::make_unique<int>(3) });
   static_assert(a5.size() == 1);

   // error: copying multidimensional arrays is not supported
   // char s[2][6] = { "nice", "thing" };
   // auto a6 = std::to_array(s);
     */
}
