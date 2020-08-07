//
//  ep231_multiple_destruction.cpp
//  cppconsole
//
//  Created by Yuxin Sun on 8/6/20.
//  Copyright © 2020 Yuxin Sun. All rights reserved.
//

#include <stdio.h>
#include <utility>
#include <string>
#include <type_traits>


/*
 
 Trivial destructor
 The destructor for class T is trivial if all of the following is true:

 The destructor is not user-provided (meaning, it is either implicitly declared, or explicitly defined as defaulted on its first declaration)
 The destructor is not virtual (that is, the base class destructor is not virtual)
 All direct base classes have trivial destructors
 All non-static data members of class type (or array of class type) have trivial destructors
 
 A trivial destructor is a destructor that performs no action. Objects with trivial destructors don't require a delete-expression and may be disposed of by simply deallocating their storage.
 All data types compatible with the C language (POD types) are trivially destructible
 
 C++20 allow multiple-destructor defined.
 
 */



struct Optional_trivial {

};

template <typename Type>
struct Optional_nontrivial {
    ~Optional_nontrivial() {
        static_cast<Type *>(this)->data.~Contained();
    }
};


template<typename Contained>
struct Optional //: std::conditional_t<std::is_trivially_destructible_v<Contained>, Optional_trivial, Optional_nontrivial<Optional<Contained>>>
{
    union { Contained data; };
    bool initialized = false;

    constexpr Optional &operator=(Contained &&data) {
        this->data = std::move(data);
        initialized = true;
        return *this;
    }

    // default is trivially destructible
    ~Optional()=default;  //c++17
    // constexpr ~Optional() = default; // c++20

    // having used-defined destructor means its not trivially destructible.
    
    // ~Optional() // c++17
    // constexpr ~Optional() requires(!std::is_trivially_destructible_v<Containeed>) // c++20
    //{
    //    if (initialized) {
    //        data.~Contained();
    //    }
    //}
};

void test_ep_231() {
    Optional<int> obj;
    obj = 5;

    static_assert(std::is_trivially_destructible_v<Optional<int>>);

    static_assert(!std::is_trivially_destructible_v<Optional<std::string>>);
    
    
}
