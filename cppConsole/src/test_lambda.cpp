#include <stdio.h>
#include <iostream>
#include <vector>
#include <functional>
#include <chrono>

/*
lambda

	[capture list] (params list) <mutable exception> -> <return type> { function body }

	# Capture variables
	[ variable (by-val) | & variable (by-ref) | = (by-val) | & (by-ref)]

	1) [] capture nothing
	2) [variable ...] by-val capture some varaible
	3) [this] capture 'this' by-val
	4) [=] capture all outside variable by-val
	5) [&] capture all outside variable by-ref
	6) [=,&x] only capture x by-ref, others by-val
	7) [&, x] only capture x by-val, others by-ref

	# params list

	1) no default param
	2) no variadic param
	3) must be named by each param

	# mutable 

	allow lambda to change the outside variable, when using by-value.
	always by-ref variable is changable

	# -> 

	return type

	# {function-body}

	By default, the member function inside the closure class generated from operator()
	a lambda is const. That has the effect of rendering all data members in the closure
	const within the body of the lambda. The move-constructed copy of data inside the
	bind object is not const, however, so to prevent that copy of data from being modified
	inside the lambda, the lambda’s parameter is declared reference-to-const. If the
	lambda were declared mutable, operator() in its closure class would not be
	declared const, and it would be appropriate to omit const in the lambda’s parameter
	declaration:

*/

void test_lambda() {

	{
		auto f = []() { std::cout << ""; };
		f();

		int x = 10;

		// by-val
		auto c1 = [x](int y) -> bool { return x * y < 50;  };

		std::cout << "c1(2) = " << c1(2) << '\n';

		std::cout << "c1(10) = " << c1(10) << '\n';

		// by-ref
		auto c2 = [&x](int y) -> bool { return x * y < 50;  };

		std::cout << "c2(2) = " << c2(2) << '\n';

		x = 100;
		std::cout << "c2(2) = " << c2(2) << '\n';
	}


	{
		int x = 6;
		int y = 6;
		int z = 6;
		// all by-val
		auto c3 = [=]()-> int { return x + y + z; };

		// all by-ref
		auto c4 = [&]()-> int { return x + y + z; };

		std::cout << "c3() = " << c3() << '\n';
		std::cout << "c4() = " << c4() << '\n';

		x = y = z = 10;
		std::cout << "after change x = y = z" << '\n';
		std::cout << "c3() = " << c3() << '\n';
		std::cout << "c4() = " << c4() << '\n';

		/*
		A by-reference capture causes a closure to contain a reference to a local variable or to
		a parameter that’s available in the scope where the lambda is defined. If the lifetime
		of a closure created from that lambda exceeds the lifetime of the local variable or
		parameter, the reference in the closure will dangle.
		*/

		/*
		If you know that a closure will be used immediately (e.g., by being passed to an STL
		algorithm) and won’t be copied, there is no risk that references it holds will outlive
		the local variables and parameters in the environment where its lambda is created. In
		that case, you might argue, there’s no risk of dangling references, hence no reason to
		avoid a default by-reference capture mode.
		*/
	}
}

template <typename C>
void workWithContainer(const C& container) {

	auto divisor = 5;

	using ContElem = typename C::value_type;

	using std::begin;
	using std::end;

	/*
	It’s true, this is safe, but its safety is somewhat precarious. If the lambda were found
	to be useful in other contexts (e.g., as a function to be added to the filters container)
	and was copy-and-pasted into a context where its closure could outlive divisor, 
	you’d be back in dangle-city, and there’d be nothing in the capture clause to
	specifically remind you to perform lifetime analysis on divisor.
	*/
	std::all_of(begin(container), end(container),
		[&](const ContElem& Value) { return Value % divisor == 0; });

	/*
	Long-term, it’s simply better software engineering to explicitly list the local variables
	and parameters that a lambda depends on.
	By the way, the ability to use "auto" in C++14 lambda parameter specifications means
	that the code above can be simplified in C++14. The ContElemT typedef can be eliminated,
	and the if condition can be revised as follows:
	*/
	std::all_of(begin(container), end(container),
		[&](const auto& value) { return value % divisor == 0; });


	/*
	One way to solve our problem with divisor would be a default by-value capture mode.

	This suffices for this example, but, in general, default by-value capture isn’t the antidangling
	elixir you might imagine. The problem is that if you capture a pointer by
	value, you copy the pointer into the closures arising from the lambda, but you don’t
	prevent code outside the lambda from deleteing the pointer and causing your
	copies to dangle.
	*/

    std::all_of(begin(container), end(container), [=](const auto& value) -> bool{
                return value % divisor == 0;
    });
}

class Widget {

public:

	void addFilter() const {

		/*
		Captures apply only to non-static local variables (including parameters) visible in
		the scope where the lambda is created.

		In the body of Widget::addFilter, divisor
		is not a local variable, it’s a data member of the Widget class. It can’t be captured. Yet
		if the default capture mode is eliminated, the code won’t compile:
		*/
	
		filter.emplace_back([=](int value)-> bool { return value % divisor == 0; });  // error, because divisor not in this function scope
	

		// In C++14, a better way to capture a data member is to use generalized lambda capture (see Item 32) :
		filter.emplace_back([divisor = divisor](int value) -> bool { return value % divisor == 0; });
		
		auto c = divisor;
		filter.emplace_back([c](int value) mutable ->bool {
			c = 10;  
			return value % c == 0; });

		auto currentObj = this;
		filter.emplace_back([=](int value) ->bool {return value % currentObj->divisor == 0; });
	
	} 

	bool isValid() const { return true;  }
	bool isArchived() const { return true; }

private:

	using FilterContainer = std::vector<std::function<bool(int)>>;

	mutable FilterContainer filter;

	int divisor;
};


void test_lambda_object() {

	/*
	One of the most exciting features of C++14 is generic lambdas—lambdas that use
	auto in their parameter specifications. The implementation of this feature is straightforward:
	operator() in the lambda’s closure class is a template.
	*/

}

using Time = std::chrono::steady_clock::time_point;

enum class Sound { Beep, Siren, Whistle };

using Duration = std::chrono::steady_clock::duration;

enum class Volume {Normal, loud, loudPlus};

void setAlarm(Time t, Sound s, Duration d, Volume v) {
	return;
}

void setAlarm(Time t, Sound s, Duration d) {
	return;
}

void test_lambda_bind() {

	// The lambda continues to work as before, because overload resolution chooses the three - argument version of setAlarm
	auto setSoundL = [](Sound s) {
		using namespace std::chrono;
		using namespace std::literals;
		//setAlarm(steady_clock::now() + hours(1), s, seconds(30));

		setAlarm(steady_clock::now() + 1h, s, 30s);
	};


	using namespace std::chrono;
	using namespace std::literals;
	using namespace std::placeholders;

	using setAlarm3Param = void(*)(Time, Sound, Duration);
	//
	auto setSoundB = std::bind(static_cast<setAlarm3Param>(setAlarm), // overload function setAlarm, need to static_cast
		// std::bind(std::plus<steady_clock::time_point>(), steady_clock::now(), 1h),  // c++11
		 std::bind(std::plus<>(), steady_clock::now(), 1h), // C++14 can ignore the parameter
		_1, 
		30s);


}

/*
*
*	recursive lambda
*
*
*/
// 1) wrong way
constexpr auto fb = [](int n) {
	if (n < 2) {
		return 1;
	}
	// return fb(n - 1) + fb(n - 2); // error because fb used before it is initialized
    return 2;
};

// 2) fix to above
constexpr auto fb1 = [](const auto fb1, int n) -> int {
	if (n < 2) {
		return 1;
	}
	return fb1(fb1, n - 1) + fb1(fb1, n - 2);
};

// 3) 
constexpr auto fb2 = [](int n) -> int{

	const auto fb_ = [](const auto fib, int n) {
		if (n < 2) {
			return 1;
		}
		return fib(fib, n - 1) + fib(fib, n - 2);
	};

	return fb_(fb_, n);
};

// 4)
auto f1 = [](const auto f1, const auto f2, int n) {
	if (n < 2) {
		return 1;
	}
	return n + f2(f1, f2, n - 1);
};

auto f2 = [](const auto f1, const auto f2, int n) {
	if (n < 2) {
			return 1;
	}
	return n + f1(f1, f2, n - 1);
};


void test_recursive_lambda() {


	std::cout << "test_recursive_lambda \n";

	std::cout << "fb1(fb1, 5) is " << fb1(fb1, 5) << "\n";

	std::cout << "fb2(5) is " << fb2(5) << "\n";

	std::cout << "f1(f1, f2, 5) is " << f1(f1, f2, 5) << "\n";

	return;
}
