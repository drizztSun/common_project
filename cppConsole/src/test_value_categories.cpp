
#include <stdlib.h>
#include <stdio.h>
/*
 
 Each C++ expression (an operator with its operands, a literal, a variable name, etc.) is characterized by two independent properties: a type and a value category.
 Each expression has some non-reference type, and each expression belongs to exactly one of the three primary value categories: prvalue, xvalue, and lvalue.

 1) a glvalue (“generalized” lvalue) is an expression whose evaluation determines the identity of an object, bit-field, or function;
 2) a prvalue (“pure” rvalue) is an expression whose evaluation either
 
    (until C++17)
    1)computes a value that is not associated with an object
    2) creates a temporary object and denotes it
 
    (since c++17)
    1) computes the value of the operand of an operator or is a void expression (such prvalue has no result object), or
    2) initializes an object or a bit-field (such prvalue is said to have a result object). With the exception of decltype, all class and array prvalues have a result object even if it is discarded.
            The result object may be a variable, an object created by new-expression, a temporary created by temporary materialization, or a member thereof;

 3） an xvalue (an “eXpiring” value) is a glvalue that denotes an object or bit-field whose resources can be reused;
 
 4） an lvalue (so-called, historically, because lvalues could appear on the left-hand side of an assignment expression) is a glvalue that is not an xvalue;
 5） an rvalue (so-called, historically, because rvalues could appear on the right-hand side of an assignment expression) is a prvalue or an xvalue.
 
 
 
 *** Primary categories
 *** lvalue
 The following expressions are lvalue expressions:

    * the name of a variable, a function, a template parameter object (since C++20), or a data member, regardless of type, such as std::cin or std::endl. Even if the variable's type is rvalue reference, the expression consisting of its name is an lvalue expression;
    * a function call or an overloaded operator expression, whose return type is lvalue reference, such as std::getline(std::cin, str), std::cout << 1, str1 = str2, or ++it;
    * a = b, a += b, a %= b, and all other built-in assignment and compound assignment expressions;
    * ++a and --a, the built-in pre-increment and pre-decrement expressions;
    * *p, the built-in indirection expression;
    * a[n] and p[n], the built-in subscript expressions, where one operand in a[n] is an array lvalue (since C++11);
    * a.m, the member of object expression, except where m is a member enumerator or a non-static member function, or where a is an rvalue and m is a non-static data member of non-reference type;
    * p->m, the built-in member of pointer expression, except where m is a member enumerator or a non-static member function;
    * a.*mp, the pointer to member of object expression, where a is an lvalue and mp is a pointer to data member;
    * p->*mp, the built-in pointer to member of pointer expression, where mp is a pointer to data member;
    * a, b, the built-in comma expression, where b is an lvalue;
    * a ? b : c, the ternary conditional expression for certain b and c (e.g., when both are lvalues of the same type, but see definition for detail);
    * a string literal, such as "Hello, world!";
    * a cast expression to lvalue reference type, such as static_cast<int&>(x);
 
    （ since C++11 )
    * a function call or an overloaded operator expression, whose return type is rvalue reference to function;
    * a cast expression to rvalue reference to function type, such as static_cast<void (&&)(int)>(x).
 
    Properties:

    * Same as glvalue (below).
    * Address of an lvalue may be taken by built-in address-of operator: &++i[1] and &std::endl are valid expressions.
    * A modifiable lvalue may be used as the left-hand operand of the built-in assignment and compound assignment operators.
    * An lvalue may be used to initialize an lvalue reference; this associates a new name with the object identified by the expression.
 
 *** prvalue
 The following expressions are prvalue expressions:

    * a literal (except for string literal), such as 42, true or nullptr;
    * a function call or an overloaded operator expression, whose return type is non-reference, such as str.substr(1, 2), str1 + str2, or it++;
    * a++ and a--, the built-in post-increment and post-decrement expressions;
    * a + b, a % b, a & b, a << b, and all other built-in arithmetic expressions;
    * a && b, a || b, !a, the built-in logical expressions;
    * a < b, a == b, a >= b, and all other built-in comparison expressions;
    * &a, the built-in address-of expression;
    * a.m, the member of object expression, where m is a member enumerator or a non-static member function[2], or where a is an rvalue and m is a non-static data member of non-reference type (until C++11);
    * p->m, the built-in member of pointer expression, where m is a member enumerator or a non-static member function[2];
    * a.*mp, the pointer to member of object expression, where mp is a pointer to member function[2], or where a is an rvalue and mp is a pointer to data member (until C++11);
    * p->*mp, the built-in pointer to member of pointer expression, where mp is a pointer to member function[2];
    * a, b, the built-in comma expression, where b is an rvalue;
    * a ? b : c, the ternary conditional expression for certain b and c (see definition for detail);
    * a cast expression to non-reference type, such as static_cast<double>(x), std::string{}, or (int)42;
    * the this pointer;
    * an enumerator;
    * non-type template parameter unless its type was a class or (since C++20) an lvalue reference type;
 
    * a lambda expression, such as [](int x){ return x * x; };  (since C++11)
 
    (since C++20)
    * a requires-expression, such as requires (T i) { typename T::type; };
    * a specialization of a concept, such as std::equality_comparable<int>.
 
 Properties:

    * Same as rvalue (below).
    * A prvalue cannot be polymorphic: the dynamic type of the object it denotes is always the type of the expression.
    * A non-class non-array prvalue cannot be cv-qualified. (Note: a function call or cast expression may result in a prvalue of non-class cv-qualified type, but the cv-qualifier is immediately stripped out.)
    * A prvalue cannot have incomplete type (except for type void, see below, or when used in decltype specifier)
    * A prvalue cannot have abstract class type or an array thereof.
 
 
 *** xvalue
 The following expressions are xvalue expressions:

    * a function call or an overloaded operator expression, whose return type is rvalue reference to object, such as std::move(x);
    * a[n], the built-in subscript expression, where one operand is an array rvalue;
    * a.m, the member of object expression, where a is an rvalue and m is a non-static data member of non-reference type;
    * a.*mp, the pointer to member of object expression, where a is an rvalue and mp is a pointer to data member;
    * a ? b : c, the ternary conditional expression for certain b and c (see definition for detail);
    * a cast expression to rvalue reference to object type, such as static_cast<char&&>(x);
    (since C++17)
    * any expression that designates a temporary object, after temporary materialization.
 
 Properties:

    * Same as rvalue (below).
    * Same as glvalue (below).
 In particular, like all rvalues, xvalues bind to rvalue references, and like all glvalues, xvalues may be polymorphic, and non-class xvalues may be cv-qualified.

 *** Mixed categories
 
 *** glvalue
    A glvalue expression is either lvalue or xvalue.

 Properties:

    * A glvalue may be implicitly converted to a prvalue with lvalue-to-rvalue, array-to-pointer, or function-to-pointer implicit conversion.
    * A glvalue may be polymorphic: the dynamic type of the object it identifies is not necessarily the static type of the expression.
    * A glvalue can have incomplete type, where permitted by the expression.
 
 *** rvalue
 An rvalue expression is either prvalue or xvalue.

 Properties:

    * Address of an rvalue cannot be taken by built-in address-of operator: &int(), &i++[3], &42, and &std::move(x) are invalid.
    * An rvalue can't be used as the left-hand operand of the built-in assignment or compound assignment operators.
    * An rvalue may be used to initialize a const lvalue reference, in which case the lifetime of the object identified by the rvalue is extended until the scope of the reference ends.
    
    (since C++11)
    * An rvalue may be used to initialize an rvalue reference, in which case the lifetime of the object identified by the rvalue is extended until the scope of the reference ends.
    * When used as a function argument and when two overloads of the function are available, one taking rvalue reference parameter and the other taking lvalue reference to const parameter,
        an rvalue binds to the rvalue reference overload (thus, if both copy and move constructors are available, an rvalue argument invokes the move constructor, and likewise with copy and move assignment operators).
 
 Special categories
 
 *** Pending member function call
 The expressions a.mf and p->mf, where mf is a non-static member function, and the expressions a.*pmf and p->*pmf, where pmf is a pointer to member function, are classified as prvalue expressions,
 but they cannot be used to initialize references, as function arguments, or for any purpose at all, except as the left-hand argument of the function call operator, e.g. (p->*pmf)(args).

 *** Void expressions
 Function call expressions returning void, cast expressions to void, and throw-expressions are classified as prvalue expressions, but they cannot be used to initialize references or as function arguments.
 They can be used in discarded-value contexts (e.g. on a line of its own, as the left-hand operand of the comma operator, etc.) and in the return statement in a function returning void. In addition, throw-expressions may be used as the second and the third operands of the conditional operator ?:.

 Void expressions have no result object.  (since C++17)
 
 *** Bit fields
 An expression that designates a bit field (e.g. a.m, where a is an lvalue of type struct A { int m: 3; }) is a glvalue expression: it may be used as the left-hand operand of the assignment operator,
 but its address cannot be taken and a non-const lvalue reference cannot be bound to it.
 A const lvalue reference or rvalue reference can be initialized from a bit-field glvalue, but a temporary copy of the bit-field will be made: it won't bind to the bit field directly.

 */


void test_value_categories_basic() {
    
    
    int i  = 42;
    
    int& l_ref = i; // correct
    // int&& r_ref = i; // error, can't binding a lvalue to rvalue_ref
    // int& l_ref = i * 42; // eror, can't bind to a lvalue_ref, because I * 42 res is a rvalue
    const int& l_ref2 = i * 42; // correct, can bind a lvalue_red to a rvalue
    int&& r_ref = i*42; // correct, bing rvalue_ref to r-value result
    int&& r_ref2 = 42; // correct, bind rvalue_ref to a literal value.
    
    
    printf("l_ref %d\n", l_ref);
    printf("l_ref %d\n", l_ref2);
    
    printf("r_ref %d\n", r_ref);
    printf("r_ref2 %d\n", r_ref2);
    
    r_ref2 = 100;
    printf("r_ref2 %d\n", r_ref2);
    
    r_ref = 1000;
    printf("r_ref %d\n", r_ref);
}

void Test_value_categories() {
    
    test_value_categories_basic();
}
