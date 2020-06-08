#include <iostream>
#include <vector>
#include <climits>
#include <cstdint>
#include <type_traits>
#include <utility>


/*
    *** fold expression(since C++17) ***

     Reduces (folds) a parameter pack over a binary operator.
     
     Syntax
     ( pack op ... )    (1)
     ( ... op pack )    (2)
     ( pack op ... op init )    (3)
     ( init op ... op pack )    (4)
 
     1) unary right fold
     2) unary left fold
     3) binary right fold
     4) binary left fold
 
     op    -    any of the following 32 binary operators: + - * / % ^ & | = < > << >> += -= *= /= %= ^= &= |= <<= >>= == != <= >= && || , .* ->*. In a binary fold, both ops must be the same.
     pack    -    an expression that contains an unexpanded parameter pack and does not contain an operator with precedence lower than cast at the top level (formally, a cast-expression)
     init    -    an expression that does not contain an unexpanded parameter pack and does not contain an operator with precedence lower than cast at the top level (formally, a cast-expression)
     Note that the open and closing parentheses are part of the fold expression.

     Explanation
     The instantiation of a fold expression expands the expression e as follows:

     1) Unary right fold (E op ...) becomes (E1 op (... op (E[N-1] op E[N])))
 
     2) Unary left fold (... op E) becomes (((E1 op E2) op ...) op EN)
 
     3) Binary right fold (E op ... op I) becomes (E1 op (... op (EN−1 op (EN op I))))
 
     4) Binary left fold (I op ... op E) becomes ((((I op E1) op E2) op ...) op EN)
 
     (where N is the number of elements in the pack expansion)

     For example,

     template<typename... Args>
     bool all(Args... args) { return (... && args); }
      
     bool b = all(true, true, true, false);
      // within all(), the unary left fold expands as
      //  return ((true && true) && true) && false;
      // b is false
     When a unary fold is used with a pack expansion of length zero, only the following operators are allowed:

     1) Logical AND (&&). The value for the empty pack is true
     2) Logical OR (||). The value for the empty pack is false
     3) The comma operator (,). The value for the empty pack is void()
     Note
     If the expression used as init or as pack has an operator with precedence below cast at the top level, it can be parenthesized:

     template<typename ...Args>
     int sum(Args&&... args) {
     //    return (args + ... + 1 * 2); // Error: operator with precedence below cast
         return (args + ... + (1 * 2)); // OK
     }
 
*/

template<typename... Args>
void printer(Args&&... args) {
    (std::cout<< ... << args) << '\n';
}


template<typename T, typename... Args>
void push_back_vec(std::vector<T>& v, Args&&... args) {
    
    static_assert((std::is_constructible_v<T, Args&&>&& ...));
    (v.push_back(std::forward<Args>(args)), ...);
    
}

// compile-time endianness swap based on http://stackoverflow.com/a/36937049
template<class T, std::size_t... N>
constexpr T bswap_impl(T i, std::index_sequence<N...>) {
    return ( ( ( i >> N * CHAR_BIT & std::uint8_t(-1)) << (sizeof(T) - 1 - N) * CHAR_BIT) | ...);
}

template<class T, class U = std::make_unsigned_t<T>>
constexpr U bswap(T i) {
    return bswap_impl<U>(i, std::make_index_sequence<sizeof(T)>{});
}

void Test_fold_expression() {
    
    std::cout << "*** start Test_fold_expression ***" << std::endl;
    
    printer(1, 2, 3, "abc");

    std::vector<int> v;
    push_back_vec(v, 6, 2, 45, 12);
    push_back_vec(v, 1, 2, 9);
    for (int i : v)
        std::cout << i << ' ';

    static_assert(bswap<std::uint16_t>(0x1234u)==0x3412u);
    static_assert(bswap<std::uint64_t>(0x0123456789abcdefULL)==0xefcdab8967452301ULL);
    
    std::cout << "*** end Test_fold_expression ***" << std::endl;
}
