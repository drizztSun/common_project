//
//  test_constructible_destructible_copy.cpp
//  cppconsole
//
//  Created by Yuxin Sun on 8/23/20.
//  Copyright © 2020 Yuxin Sun. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <type_traits>

namespace function_test{

    class Foo {
        int v1;
        double v2;
     public:
        Foo(int n) : v1(n), v2() {}
        Foo(int n, double f) noexcept : v1(n), v2(f) {}
    };

    /*
        std::is_constructible,
        std::is_trivially_constructible,
        std::is_nothrow_constructible
     
        1) If T is an object or reference type and the variable definition T obj(std::declval<Args>()...); is well-formed, provides the member constant value equal to true. In all other cases, value is false.
        For the purposes of this check, the variable definition is never interpreted as a function declaration, and the use of std::declval is not considered an odr-use.
        Access checks are performed as if from a context unrelated to T and any of the types in Args. Only the validity of the immediate context of the variable definition is considered.

        2) same as 1), but the variable definition does not call any operation that is not trivial. For the purposes of this check, the call to std::declval is considered trivial.

        3) same as 1), but the variable definition is noexcept.

        T and all types in the parameter pack Args shall each be a complete type, (possibly cv-qualified) void, or an array of unknown bound. Otherwise, the behavior is undefined.
        If an instantiation of a template above depends, directly or indirectly, on an incomplete type, and that instantiation could yield a different result if that type were hypothetically completed, the behavior is undefined.
        The behavior of a program that adds specializations for any of the templates described on this page is undefined.
     */
    void test_constructible_basic() {
        std::cout << "Foo is ...\n" << std::boolalpha
                  << "\tTrivially-constructible from const Foo&? "
                  << std::is_trivially_constructible<Foo, const Foo&>::value << '\n'
                  << "\tTrivially-constructible from int? "
                  << std::is_trivially_constructible<Foo, int>::value << '\n'
                  << "\tConstructible from int? "
                  << std::is_constructible<Foo, int>::value << '\n'
                  << "\tNothrow-constructible from int? "
                  << std::is_nothrow_constructible<Foo, int>::value << '\n'
                  << "\tNothrow-constructible from int and double? "
                  << std::is_nothrow_constructible<Foo, int, double>::value << '\n';
        
        // Foo is ...
        //      Trivially-constructible from const Foo&? true
        //      Trivially-constructible from int? false
        //      Constructible from int? true
        //      Nothrow-constructible from int? false
        //      Nothrow-constructible from int and double? true
    }


    /*
        std::is_destructible,
        std::is_trivially_destructible,
        std::is_nothrow_destructible     (since C++11)
     
        1) If T is a reference type, provides the member constant value equal true
        If T is (possibly cv-qualified) void, a function type, or an array of unknown bound, value equals false.
        If T is an object type, then, for the type U equal std::remove_all_extents<T>::type, if the expression std::declval<U&>().~U() is well-formed in unevaluated context, value equals true. Otherwise, value equals false.

        2) same as (1) and additionally std::remove_all_extents<T>::type is either a non-class type or a class type with a trivial destructor.

        3) same as (1), but the destructor is noexcept.

        T shall be a complete type, (possibly cv-qualified) void, or an array of unknown bound. Otherwise, the behavior is undefined.
        If an instantiation of a template above depends, directly or indirectly, on an incomplete type, and that instantiation could yield a different result if that type were hypothetically completed, the behavior is undefined.
        The behavior of a program that adds specializations for any of the templates described on this page is undefined.
     
        
    */
    struct Foo1 {
       std::string str;
       ~Foo1() noexcept {};
    };

    struct Bar {
        ~Bar() = default; // trivial and non-throwing
    };


    void test_destructible_basic() {
        
        std::cout << std::boolalpha
                  << "std::string is destructible? "
                  << std::is_destructible<std::string>::value << '\n'
                  << "Foo is nothrow destructible? "
                  << std::is_nothrow_destructible<Foo1>::value << '\n'
                  << "Bar is trivally destructible? "
                  << std::is_trivially_destructible<Bar>::value << '\n';
        
        // std::string is destructible? true
        // Foo is nothrow destructible? true
        // Bar is trivally destructible? true
        
        std::cout << std::boolalpha
                    << "std::string is destructible? "
                    << std::is_destructible<std::string>::value << '\n'
                    << "string is nothrow destructible? "
                    << std::is_nothrow_destructible<std::string>::value << '\n'
                    << "string is trivally destructible? "
                    << std::is_trivially_destructible<std::string>::value << '\n';
        
        std::cout << std::boolalpha
                  << "Foo is destructible? "
                  << std::is_destructible<Foo1>::value << '\n'
                  << "Foo is nothrow destructible? "
                  << std::is_nothrow_destructible<Foo1>::value << '\n'
                  << "Foo is trivally destructible? "
                  << std::is_trivially_destructible<Foo1>::value << '\n';
        
        std::cout << std::boolalpha
                  << "Bar is destructible? "
                  << std::is_destructible<Bar>::value << '\n'
                  << "Bar is nothrow destructible? "
                  << std::is_nothrow_destructible<Bar>::value << '\n'
                  << "Bar is trivally destructible? "
                  << std::is_trivially_destructible<Bar>::value << '\n';
        
    }

    /*
        std::is_move_constructible,
        std::is_trivially_move_constructible,
        std::is_nothrow_move_constructible
     
        1) If T is not a referenceable type (i.e., possibly cv-qualified void or a function type with a cv-qualifier-seq or a ref-qualifier), provides a member constant value equal to false.
            Otherwise, provides a member constant value equal to std::is_constructible<T, T&&>::value.
        2) Same as (1), but uses std::is_trivially_constructible<T, T&&>.
        3) Same as (1), but uses std::is_nothrow_constructible<T, T&&>.
            T shall be a complete type, (possibly cv-qualified) void, or an array of unknown bound. Otherwise, the behavior is undefined.

        If an instantiation of a template above depends, directly or indirectly, on an incomplete type, and that instantiation could yield a different result if that type were hypothetically completed, the behavior is undefined.

        The behavior of a program that adds specializations for any of the templates described on this page is undefined.
        
     
     */
    struct Ex1 {
        std::string str; // member has a non-trivial but non-throwing move ctor
    };
    struct Ex2 {
        int n;
        Ex2(Ex2&&) = default; // trivial and non-throwing
        
        Ex2(const Ex2&) = default; // trivial and non-throwing
    };
    struct NoMove {
        // prevents implicit declaration of default move constructor
        // however, the class is still move-constructible because its
        // copy constructor can bind to an rvalue argument
        NoMove(const NoMove&) {}
    };

    void test_move_able() {
        
       std::cout << std::boolalpha << "Ex1 is move-constructible? "
                 << std::is_move_constructible<Ex1>::value << '\n'
                 << "Ex1 is trivially move-constructible? "
                 << std::is_trivially_move_constructible<Ex1>::value << '\n'
                 << "Ex1 is nothrow move-constructible? "
                 << std::is_nothrow_move_constructible<Ex1>::value << '\n'
                 << "Ex2 is trivially move-constructible? "
                 << std::is_trivially_move_constructible<Ex2>::value << '\n'
                 << "Ex2 is nothrow move-constructible? "
                 << std::is_nothrow_move_constructible<Ex2>::value << '\n';

       std::cout << std::boolalpha
                 << "NoMove is move-constructible? "
                 << std::is_move_constructible<NoMove>::value << '\n'
                 << "NoMove is nothrow move-constructible? "
                 << std::is_nothrow_move_constructible<NoMove>::value << '\n';
        
        
        // Ex1 is move-constructible? true
        // Ex1 is trivially move-constructible? false
        // Ex1 is nothrow move-constructible? true
        // Ex2 is trivially move-constructible? true
        // Ex2 is nothrow move-constructible? true
        // NoMove is move-constructible? true
        // NoMove is nothrow move-constructible? false
    }

    /*
     
        std::is_copy_constructible,
        std::is_trivially_copy_constructible,
        std::is_nothrow_copy_constructible
     
        1) If T is not a referenceable type (i.e., possibly cv-qualified void or a function type with a cv-qualifier-seq or a ref-qualifier), provides a member constant value equal to false.
            Otherwise, provides a member constant value equal to std::is_constructible<T, const T&>::value.
        2) Same as (1), but uses std::is_trivially_constructible<T, const T&>.
        3) Same as (1), but uses std::is_nothrow_constructible<T, const T&>.
        T shall be a complete type, (possibly cv-qualified) void, or an array of unknown bound. Otherwise, the behavior is undefined.
        If an instantiation of a template above depends, directly or indirectly, on an incomplete type, and that instantiation could yield a different result if that type were hypothetically completed, the behavior is undefined.
        The behavior of a program that adds specializations for any of the templates described on this page is undefined.
     */

    void test_copy_able() {
        std::cout << std::boolalpha << "Ex1 is copy-constructible? "
                  << std::is_copy_constructible<Ex1>::value << '\n'
                  << "Ex1 is trivially copy-constructible? "
                  << std::is_trivially_copy_constructible<Ex1>::value << '\n'
                  << "Ex2 is trivially copy-constructible? "
                  << std::is_trivially_copy_constructible<Ex2>::value << '\n'
                  << "Ex2 is nothrow copy-constructible? "
                  << std::is_nothrow_copy_constructible<Ex2>::value << '\n';
        
        // Ex1 is copy-constructible? true
        // Ex1 is trivially copy-constructible? false
        // Ex2 is trivially copy-constructible? true
        // Ex2 is nothrow copy-constructible? true
    }
}


void test_function_able() {
    
    function_test::test_constructible_basic();
    
    function_test::test_destructible_basic();
    
    function_test::test_copy_able();
    
    function_test::test_move_able();
}
