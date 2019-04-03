#include <stdlib.h>
#include <string>

/*
We use typename... "Ts" to declare Ts as a so-called "template parameter pack". 
You’ll often see these called as e.g. Ts, as in, multiple Ts. 
Other common names are Args, or Rest. The ellipsis (...) operator is used here to declare that Ts truly is a template parameter pack.
*/
template <typename ... Ts> // 'T' as a so-called 'template parameter pack'. 
void ignore(const Ts& ... ts) {
	
}


template <typename T1, typename T2, typename ...T3, typename Tn>
void ignore(T1 t1, T2 t2, T3 ..., Tn tn) {

}

template<class ... Types> struct Tuple {};

void test_variadic_template() {

	Tuple<> t0;           // Types contains no arguments
	Tuple<int> t1;        // Types contains one argument: int
	Tuple<int, float> t2; // Types contains two arguments: int and float
	// Tuple<0> error;       // error: 0 is not a type


	//auto res = std::to_string(1, "234", 4);

	ignore<int, double, bool>(1, 2.0, true);
}