/*
 
 pair, tuple and
 
 
 */

#include <iostream>

#include <tuple>
using std::tuple;

#include <string>
using std::string;

#include <set>


// helper function to print a tuple of any size
template<class Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const Tuple& t)
    {
        TuplePrinter<Tuple, N-1>::print(t);
        std::cout << ", " << std::get<N-1>(t);
    }
};
 
template<class Tuple>
struct TuplePrinter<Tuple, 1> {
    static void print(const Tuple& t)
    {
        std::cout << std::get<0>(t);
    }
};
 
template<typename... Args, std::enable_if_t<sizeof...(Args) == 0, int> = 0>
void print(const std::tuple<Args...>& t)
{
    std::cout << "()\n";
}
 
template<typename... Args, std::enable_if_t<sizeof...(Args) != 0, int> = 0>
void print(const std::tuple<Args...>& t)
{
    std::cout << "(";
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
    std::cout << ")\n";
}
// end helper function

std::tuple<double, char, std::string> get_student(int id)
{
    if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
    if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
    if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
    throw std::invalid_argument("id");
}

struct S {
    int n;
    std::string s;
    float d;
    bool operator<(const S& rhs) const
    {
        // compares n to rhs.n,
        // then s to rhs.s,
        // then d to rhs.d
        return std::tie(n, s, d) < std::tie(rhs.n, rhs.s, rhs.d);
    }
};

template <class T>
void test(T t)
{
    int a[std::tuple_size<T>::value]; // can be used at compile time
 
    std::cout << std::tuple_size<T>::value << '\n'; // or at run time
}

void test_tuple() {
    
    tuple<int, float, string> sd(1, 3.14, "circle rate");
    
    std::cout << "{1} " << std::get<0>(sd)
            << "{2} " << std::get<1>(sd)
            << "{3} " << std::get<2>(sd)
            << std::endl;
    
    
    {
        
       auto student0 = get_student(0);
       std::cout << "ID: 0, "
                 << "GPA: " << std::get<0>(student0) << ", "
                 << "grade: " << std::get<1>(student0) << ", "
                 << "name: " << std::get<2>(student0) << '\n';
    
       double gpa1;
       char grade1;
       std::string name1;
       std::tie(gpa1, grade1, name1) = get_student(1);
       std::cout << "ID: 1, "
                 << "GPA: " << gpa1 << ", "
                 << "grade: " << grade1 << ", "
                 << "name: " << name1 << '\n';
    
       // C++17 结构化绑定：
       auto [ gpa2, grade2, name2 ] = get_student(2);
       std::cout << "ID: 2, "
                 << "GPA: " << gpa2 << ", "
                 << "grade: " << grade2 << ", "
                 << "name: " << name2 << '\n';
    }
    
    {
        // tie
        // template< class... Types >
        // tuple<Types&...> tie( Types&... args ) noexcept;
        // Creates a tuple of lvalue references to its arguments or instances of std::ignore.
       std::set<S> set_of_s; // S is LessThanComparable
    
       S value{42, "Test", 3.14};
       std::set<S>::iterator iter;
       bool inserted;
    
       // unpacks the return value of insert into iter and inserted
       std::tie(iter, inserted) = set_of_s.insert(value);
    
       if (inserted)
           std::cout << "Value was inserted successfully\n";
    }
    
    {
       // std::ignore
       // An object of unspecified type such that any value can be assigned to it with no effect.
       // Intended for use with std::tie when unpacking a std::tuple, as a placeholder for the arguments that are not used.
        std::set<std::string> set_of_str;
        bool inserted = false;
        std::tie(std::ignore, inserted) = set_of_str.insert("Test");
        if (inserted) {
            std::cout << "Value was inserted successfully\n";
        }
    }
    
    {
        // tuple_cat
        // template< class... Tuples >
        // std::tuple<CTypes...> tuple_cat(Tuples&&... args);
                
        // Constructs a tuple that is a concatenation of all tuples in args.

        // The behavior is undefined if any type in std::decay_t<Tuples>... is not a specialization of std::tuple.
        // However, an implementation may choose to support types (such as std::array and std::pair) that follow the tuple-like protocol.
        
        std::tuple<int, std::string, float> t1(10, "Test", 3.14);
        int n = 7;
        auto t2 = std::tuple_cat(t1, std::make_tuple("Foo", "bar"), t1, std::tie(n));
        n = 10;
        print(t2);
        // (10, Test, 3.14, Foo, bar, 10, Test, 3.14, 10)
    }
    
    {
        // std::tuple_size<std::tuple>
        // Provides access to the number of elements in a tuple as a compile-time constant expression.
        // In addition to being available via inclusion of the <tuple> header, the templates (3-5) are available when either of the headers <array> or <utility> are included.
        
        test(std::make_tuple(1, 2, 3.14));
    }
}

void test_pair() {
    
    
}

void test_tuple_pair() {
    
    test_tuple();
    
    test_pair();
}
