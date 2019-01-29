#include <stdlib.h>
#include <iostream>
#include <random>
#include <memory>
#include <functional>


void f(int n1, int n2, int n3, const int& n4, int n5) {
	std::cout << n1 << " " << n2 << " " << n3 << " " << n4 << " " << n5 << " " << std::endl;
}

int g(int n1)
{
	return n1;
}

struct Foo {
	void print_sum(int n1, int n2)
	{
		std::cout << n1 + n2 << '\n';
	}
	int data = 10;
};

void test_bind() {

	using namespace std::placeholders; // for _1, _2, _3...
	
	// demonstrates argument reordering and pass-by-reference
	int n = 7;
	auto f1 = std::bind(f, _2, _1, 42, std::cref(n), n);
	// (_1 and _2 are from std::placeholders, and represent future
	// arguments that will be passed to f1)

	n = 10;
	f1(1, 2, 1001); // because 1 is _1, 2 is _2, 1001_ is _3, but not used
	// 1 is bound by _1, 2 is bound by _2, 1001 is unused
					// makes a call to f(2, 1, 42, n, 7)

	// nested bind subexpressions share the placeholders
	auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
	f2(10, 11, 12); // makes a call to f(12, g(12), 12, 4, 5);


	 // common use case: binding a RNG with a distribution
	std::default_random_engine e;
	std::uniform_int_distribution<> d(0, 10);
	auto rnd = std::bind(d, e); // a copy of e is stored in rnd
	for (int n = 0; n < 10; ++n)
		std::cout << rnd() << ' ';
	std::cout << '\n';

	// bind to a pointer to member function
	Foo foo;
	auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);
	f3(5);

	// bind to a pointer to data member
	auto f4 = std::bind(&Foo::data, _1);
	std::cout << f4(foo) << '\n';

	// smart pointers can be used to call members of the referenced objects, too
	std::cout << f4(std::make_shared<Foo>(foo)) << '\n'
		<< f4(std::make_unique<Foo>(foo)) << '\n';
}

class date 
{
public:
	date(int year, int month, int day_in_month);
	
	date(const date &);

	date& operator=(const date&);

	// get_* is not-functional way to define function name. it is side-effect
	//int get_year() const;
	//int get_month() const;
	//int get_day_in_month() const;
	int year() const;
	int month() const;
	int day_in_month() const;

	void set(int year, int month, int day_in_month);

};



void Test_functional() {

	test_bind();

}