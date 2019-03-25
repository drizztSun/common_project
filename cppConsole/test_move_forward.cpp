#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <array>

/*

std::move
  C++  Utilities library
Defined in header <utility>
template< class T >
typename std::remove_reference<T>::type&& move( T&& t ) noexcept;
(since C++11)
(until C++14)

template< class T >
constexpr typename std::remove_reference<T>::type&& move( T&& t ) noexcept;
(since C++14)

std::move is used to indicate that an object t may be "moved from", i.e. 
allowing the efficient transfer of resources from t to another object.

In particular, std::move produces an xvalue expression that identifies its argument t. 
It is exactly equivalent to a static_cast to an rvalue reference type.

Notes
The functions that accept rvalue reference parameters (including move constructors, move assignment operators, 
and regular member functions such as std::vector::push_back) are selected, by overload resolution, when called with rvalue arguments 
(either prvalues such as a temporary objects or xvalues such as the one produced by std::move). 

If the argument identifies a resource-owning object, these overloads have the option, but aren't required, 
to move any resources held by the argument. For example, a move constructor of a linked list might copy the pointer 
to the head of the list and store nullptr in the argument instead of allocating and copying individual nodes.

Names of rvalue reference variables are lvalues and have to be converted to xvalues to be bound 
to the function overloads that accept rvalue reference parameters, 
which is why move constructors and move assignment operators typically use std::move:

// Simple move constructor
A(A&& arg) : member(std::move(arg.member)) // the expression "arg.member" is lvalue
{}
// Simple move assignment operator
A& operator=(A&& other) {
	 member = std::move(other.member);
	 return *this;
}
One exception is when the type of the function parameter is rvalue reference to type template parameter 
("forwarding reference" or "universal reference"), in which case std::forward is used instead.

Unless otherwise specified, all standard library objects that have been moved from are placed in a valid but unspecified state. 
That is, only the functions without preconditions, such as the assignment operator, 
can be safely used on the object after it was moved from:

std::vector<std::string> v;
std::string str = "example";
v.push_back(std::move(str)); // str is now valid but unspecified
str.back(); // undefined behavior if size() == 0: back() has a precondition !empty()
str.clear(); // OK, clear() has no preconditions
Also, the standard library functions called with xvalue arguments may assume the argument is the only reference to the object;
if it was constructed from an lvalue with std::move, no aliasing checks are made. 
In particular, this means that standard library move assignment operators do not have to perform self-assignment checks:

std::vector<int> v = {2, 3, 3};
v = std::move(v); // the value of v is unspecified


*/

void test_stdmove() {
	// <output>
	//After copy, str is "Hello"
	//After move, str is ""
	//The contents of the vector are "Hello", "Hello"

	std::string s = "Hello";

	std::vector<std::string> v;

	// uses the push_back(const T&) overload, which means 
	// we'll incur the cost of copying str
	v.push_back(s);
	std::cout << "After copy, str is \"" << s << "\"\n";


	// uses the rvalue reference push_back(T&&) overload, 
	// which means no strings will be copied; instead, the contents
	// of str will be moved into the vector.  This is less
	// expensive, but also means str might now be empty.
	v.push_back(std::move(s));
	std::cout << "After move, str is " << s << "\n";

	std::cout << "The content of vector are \"" << v[0] << "\", \"" << v[1] << "\"\n";

}

/*
std::move_if_noexcept
  C++  Utilities library
Defined in header <utility>

template< class T >
typename std::conditional<
	!std::is_nothrow_move_constructible<T>::value && std::is_copy_constructible<T>::value,
	const T&,
	T&&
>::type move_if_noexcept(T& x) noexcept;
(since C++11)
(until C++14)

template< class T >
constexpr typename std::conditional<
	!std::is_nothrow_move_constructible<T>::value && std::is_copy_constructible<T>::value,
	const T&,
	T&&
>::type move_if_noexcept(T& x) noexcept;
(since C++14)

move_if_noexcept obtains an rvalue reference to its argument if its move constructor does not throw exceptions or 
if there is no copy constructor (move-only type), otherwise obtains an lvalue reference to its argument. 
It is typically used to combine move semantics with strong exception guarantee.
*/

struct Bad {
	Bad() {}

	Bad(Bad&&) {
		std::cout << "Throwing move constructor called\n";
	}

	Bad(const Bad&) {
		std::cout << "Throwing copy constructor caller";
	}
};

struct Good {
	Good() {}

	Good(Good&&) noexcept {
		std::cout << "Non-Throwding move constructor called \n";
	}

	Good(const Good&) noexcept {
		std::cout << "Non-throwing copy constructor called \n";
	}
};

void test_move_if_noexcept() {

	Good g;
	Bad b;
	
	// Non-throwing move constructor called
	// Throwing copy constructor called
	Good g2 = std::move_if_noexcept(g);
	Bad b2 = std::move_if_noexcept(b);
}

/*
std::forward
  C++  Utilities library
Defined in header <utility>

template< class T >
T&& forward( typename std::remove_reference<T>::type& t ) noexcept;
(1)	(since C++11)
(until C++14)

template< class T >
constexpr T&& forward( typename std::remove_reference<T>::type& t ) noexcept;
(1)	(since C++14)

template< class T >
T&& forward( typename std::remove_reference<T>::type&& t ) noexcept;
(2)	(since C++11)
(until C++14)

template< class T >
constexpr T&& forward( typename std::remove_reference<T>::type&& t ) noexcept;
(2)	(since C++14)

*/

struct A { 
	A(int&& n) {
		std::cout << "rvalue overload, n = " << n << '\n';
	}

	A(int& n) {
		std::cout << "lvalue overload, n = " << n << '\n';
	}
};

struct B {
	template <class T1, class T2, class T3>
	B(T1&& t1, T2&& t2, T3&&t3):
		a1_{std::forward<T1>(t1)},
		a2_{ std::forward<T2>(t2) },
		a4_{ std::forward<T3>(T3) } {

	}

	int a1_, a2_, a4_;
};

template <class T, class U>
std::unique_ptr<T> make_unique1(U&& u) {
	return std::unique<T>(new T(std::forward<U>(u));
}

template <class T, class... U>
std::unique_ptr<T> make_unique2(U&& ... u) {
	return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}

void test_forward() {
	auto p1 = make_unique1<A>(2);
	int i = 2;
	auto p2 = make_unique1<A>(i);

	std::cout << "B\n";
	auto t = make_unique2<B>(2, i, 3);
}
