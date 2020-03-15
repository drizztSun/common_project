#include <iostream>
#include <stdexcept>

/*
The constexpr specifier declares that it is possible to evaluate the value of the function or variable at compile time. 
Such variables and functions can then be used where only compile time constant expressions are allowed 
(provided that appropriate function arguments are given). 
A constexpr specifier used in an object declaration or non-static member function (until C++14) implies const. 

A constexpr specifier used in a function or static member variable (since C++17) declaration implies inline. 
If any declaration of a function or function template has a constexpr specifier, then every declaration must contain that specifier.

https://en.cppreference.com/w/cpp/language/constexpr
*/


// C++11 constexpr functions use recursion rather than iteration
// (C++14 constexpr functions may use local variables and loops)
constexpr int factorial(int n) {
	return n <= 1 ? 1 : n * factorial(n - 1);
}

//literal class
class conststr {

	const char* p;
	std::size_t sz;

public:

	template<std::size_t N>
	constexpr conststr(const char(&a)[N]) : p(a), sz(N - 1) { } // const char(&a)[N] pointer to a char[N]

	// constexpr functions signal errors by throwing exceptions
	// in C++11, they must do so from the conditional operator ?:
	constexpr char operator[] (std::size_t n) const {
		return n < sz ? p[n] : throw std::out_of_range("");
	}

	constexpr std::size_t size() const {
		return sz;
	}
};

// C++11 constexpr functions had to put everything in a single return statement
// (C++14 doesn't have that requirement)
constexpr std::size_t countlower(conststr s, std::size_t n = 0, std::size_t c = 0) {
	
	return n == s.size() ? c :
		'a' <= s[n] && s[n] <= 'z' ? countlower(s, n + 1, c + 1) :
									countlower(s, n + 1, c);
}

// output function that requires a compile-time constant, for testing
template <int n>
struct constN {
	constN() {
		std::cout << n << "\n";
	}
};


void test_constrexpr() {

	std::cout << "4! = ";
	constN<factorial(4)> out1; // computed at compile time

	volatile int k = 8; // disallow optimization using volatile
	std::cout << k << "! = " << factorial(k) << '\n'; // computed at run time

	std::cout << "the number of lowercase letters in \"Hello, world!\" is ";
	constN<countlower("Hello world!")> out2; // implicitly converted to conststr
}