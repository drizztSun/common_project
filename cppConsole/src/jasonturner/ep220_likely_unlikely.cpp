#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <string>

/*
 
 C++ attribute: likely, unlikely (since C++20)
 
 Allow the compiler to optimize for the case where paths of execution including that statement are more or less likely than any alternative path of execution that does not include such a statement

 Syntax
 [[likely]]    (1)
 [[unlikely]]    (2)
 Explanation
 These attributes may be applied to labels and statements (other than declaration-statements). They may not be simultaneously applied to the same label or statement.

 1) Applies to a statement to allow the compiler to optimize for the case where paths of execution including that statement are more likely than any alternative path of execution that does not include such a statement.
 2) Applies to a statement to allow the compiler to optimize for the case where paths of execution including that statement are less likely than any alternative path of execution that does not include such a statement.
 A path of execution is deemed to include a label if and only if it contains a jump to that label:

 int f(int i)
 {
     switch(i)
     {
         case 1: [[fallthrough]];
         [[likely]] case 2: return 1;
     }
     return 2;
 }
 i == 2 is considered more likely than any other value of i, but the [[likely]] has no effect on the i == 1 case even though it falls through the case 2: label.
 
 */





int value(const int argc, const char * []) {
    if (argc > 5) [[unlikely]]{
        return 29;
    } else [[likely]]{
        return 42;
    }
}

void test(const int argc, const char * argv[]) {
    if (argc > 5) [[unlikely]]{
        std::puts(argv[5]);
        // std::cout << argv[5] << '\n';
    } else [[likely]]{
        std::puts(argv[0]);
        //std::cout << argv[0] << '\n';
    }
}

/* -std=c++2a -O3
 xxx(int, char const**):
         cmp     edi, 5
         mov     edx, 42
         mov     eax, 29
         cmovle  eax, edx
         ret
 test:
         sub     rsp, 8
         cmp     edi, 5
         jg      .L9
         mov     rdi, QWORD PTR [rsi]
         call    puts
 .L7:
         xor     eax, eax
         add     rsp, 8
         ret
 .L9:
         mov     rdi, QWORD PTR [rsi+40]
         call    puts
         jmp     .L7
 _GLOBAL__sub_I_xxx(int, char const**):
         sub     rsp, 8
         mov     edi, OFFSET FLAT:_ZStL8__ioinit
         call    std::ios_base::Init::Init() [complete object constructor]
         mov     edx, OFFSET FLAT:__dso_handle
         mov     esi, OFFSET FLAT:_ZStL8__ioinit
         mov     edi, OFFSET FLAT:_ZNSt8ios_base4InitD1Ev
         add     rsp, 8
         jmp     __cxa_atexit
 */
