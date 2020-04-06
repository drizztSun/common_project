#include <stdlib.h>
#include <iostream>
#include <unordered_set>
#include <functional>
#include <array>

using namespace std;

/*

There are 2 ways to make an unordered_set of User Define Types / Classes i.e.

1. Create special functions to make default std::hash<> & std::equals_to<> functions to work with User Defined classes

2. Creating Custom Hasher and Comparision Functors and pass it to unordered_set.

*/

typedef pair<int, int> CORD;

size_t cord_hash1(const CORD& cord) {
	return hash<int>()(cord.first) ^ hash<int>()(cord.second);
}

/*
 Unordered Set
 Unordered sets are containers that store unique elements in no particular order, and which allow for fast retrieval of individual elements based on their value.

 In an unordered_set, the value of an element is at the same time its key, that identifies it uniquely.
 Keys are immutable, therefore, the elements in an unordered_set cannot be modified once in the container - they can be inserted and removed, though.

 Internally, the elements in the unordered_set are not sorted in any particular order,
 but organized into buckets depending on their hash values to allow for fast access to individual elements directly by their values (with a constant average time complexity on average).

 unordered_set containers are faster than set containers to access individual elements by their key, although they are generally less efficient for range iteration through a subset of their elements.

 Iterators in the container are at least forward iterators.
 
 */

void Test_normal_set() {

	unordered_set<int> cord{ 1, 2, 3, 4, 5, 6};
    
    cout << "cord is empty : " << cord.empty() << endl;

    // find
	if (cord.find(2) != cord.end()) {
		cout << " Have it done " << endl;
	} else {
		cout << " Haven't found it " << endl;
	}
    
    // Searches the container for elements with a value of k and returns the number of elements found.
    // Because unordered_set containers do not allow for duplicate values,
    // this means that the function actually returns 1 if an element with that value exists in the container, and zero otherwise.
    cout << " cord has 2 : " << cord.count(2) << endl;
    cout << " cord has 10 : " << cord.count(10) << endl;
    
    for (auto it = cord.begin(); it != cord.end(); it++) {
        cout << "cord has " << *it << endl;
    }
    
    for (auto it = cord.cbegin(); it != cord.cend(); it++) {
        cout << "cord has const " << *it << endl;
    }
    
    
    // Removes from the unordered_set container either a single element or a range of elements ([first,last)).
    cord.erase(2);
    cord.erase(cord.find(6));
    
    for (auto it = cord.begin(); it != cord.end(); it++) {
        cout << "cord has " << *it << endl;
    }
    
    {
         std::unordered_set<std::string> myset = {"USA","Canada","France","UK","Japan","Germany","Italy"};

         myset.erase ( myset.begin() );                    // erasing by iterator
         myset.erase ( "France" );                         // erasing by key
         myset.erase ( myset.find("Japan"), myset.end() ); // erasing by range

         std::cout << "myset contains:";
         for ( auto& x: myset )
             std::cout << " " << x.c_str() ;
         std::cout << std::endl;
    }
    
    // insert
    // Inserts new elements in the unordered_set.
    // Each element is inserted only if it is not equivalent to any other element already in the container (elements in an unordered_set have unique values).
    {
        std::unordered_set<std::string> myset = {"yellow","green","blue"};
        std::array<std::string,2> myarray{"black","white"};
        std::string mystring = "red";

        auto s = myset.insert (mystring);                        // copy insertion
        if (s.second) {
            std::cout << "insert element " << s.first->c_str() << endl;
        }
        
        myset.insert (mystring+"dish");                 // move insertion
        myset.insert (myarray.begin(), myarray.end());  // range insertion
        myset.insert ( {"purple","orange"} );           // initializer list insertion


        std::cout << "myset contains:";
        for (auto& x: myset)
            std::cout << " " << x.c_str();
        std::cout <<  std::endl;
    }
    
    // emplace
    // Inserts a new element in the unordered_set if its value is unique. This new element is constructed in place using args as the arguments for the element's constructor.
    //The insertion only takes place if no element in the container has a value equivalent to the one being emplaced (elements in an unordered_set have unique values).
    // If inserted, this effectively increases the container size by one.
    // A similar member function exists, insert, which either copies or moves existing objects into the container.
    {
        std::unordered_set<std::string> myset;

        myset.emplace ("potatoes");
        myset.emplace ("milk");
        myset.emplace ("flour");

        std::cout << "myset contains:";
        for (auto& x: myset)
            std::cout << " " << x.c_str();

        std::cout << std::endl;
    }
    
    // hash_function
    // The hash function is a unary function that takes an object of type key_type as argument and returns a unique value of type size_t based on it.
    // It is adopted by the container on construction (see unordered_set's constructor for more info). By default, it is the default hashing function for the corresponding key type: hash<key_type>.
    {
        std::unordered_set<std::string> myset;
        
        std::unordered_set<std::string>::hasher fn = myset.hash_function();
        std::cout << "that: " << fn ("that") << std::endl;
        std::cout << "than: " << fn ("than") << std::endl;
    }
    
    // key_eq
    // Returns the key equivalence comparison predicate used by the unordered_set container.
    // The key equivalence comparison is a predicate that takes the value of two elements as arguments and returns a bool value indicating whether they are to be considered equivalent. It is adopted by the container on construction (see unordered_set's constructor for more info). By default, it is equal_to<key_type>, which returns the same as applying the equal-to operator (==) to the arguments.
    {
        std::unordered_set<std::string> myset;

        bool case_insensitive = myset.key_eq()("checking","CHECKING");

        std::cout << "myset.key_eq() is ";
        std::cout << ( case_insensitive ? "case insensitive" : "case sensitive" );
        std::cout << std::endl;
    }

    // max_size
    // Return maximum size
    // Returns the maximum number of elements that the unordered_set container can hold.
    // This is the maximum potential number of elements the container can hold due to system constraints or limitations on its library implementation.
    
    // max_bucket_size
    // Returns the maximum number of buckets that the unordered_set container can have.
    // This is the maximum potential number of buckets the container can have due to system constraints or limitations on its library implementation.
    {
        std::unordered_set<int> myset;

        std::cout << "max_size = " << myset.max_size() << std::endl;
        std::cout << "max_bucket_count = " << myset.max_bucket_count() << std::endl;
        std::cout << "max_load_factor = " << myset.max_load_factor() << std::endl;
    }
    
    // max_load_factor
    // The first version (1) returns the current maximum load factor for the unordered_set container.
    // The second version (2) sets z as the new maximum load factor for the unordered_set container.
    // The load factor is the ratio between the number of elements in the container (its size) and the number of buckets (bucket_count).
    // By default, unordered_set containers have a max_load_factor of 1.0.
    {
        std::unordered_set<std::string> myset = {"New York", "Paris", "London", "Hong Kong", "Bangalore", "Tel Aviv"};

        std::cout << "current max_load_factor: " << myset.max_load_factor() << std::endl;
        std::cout << "current size: " << myset.size() << std::endl;
        std::cout << "current bucket_count: " << myset.bucket_count() << std::endl;
        std::cout << "current load_factor: " << myset.load_factor() << std::endl;

        float z = myset.max_load_factor();
        myset.max_load_factor ( z / 2.0 );
        std::cout << "[max_load_factor halved]" << std::endl;

        std::cout << "new max_load_factor: " << myset.max_load_factor() << std::endl;
        std::cout << "new size: " << myset.size() << std::endl;
        std::cout << "new bucket_count: " << myset.bucket_count() << std::endl;
        std::cout << "new load_factor: " << myset.load_factor() << std::endl;
    }

    
    // swap
    {
        std::unordered_set<std::string> first = {"Metropolis","Solaris","Westworld"}, second  = {"Avatar","Inception"};

         swap(first, second);

         std::cout << "first:";
         for (auto& x: first) 
			 std::cout << " " << x.c_str();
         std::cout << std::endl;

         std::cout << "second:";
         for (auto& x: second) 
			 std::cout << " " << x.c_str();
         std::cout << std::endl;
    }
    
    // clear all element
    cord.clear();
}


/*
 
 Unordered Multiset
 Unordered multisets are containers that store elements in no particular order, allowing fast retrieval of individual elements based on their value,
 much like unordered_set containers, but allowing different elements to have equivalent values.

 In an unordered_multiset, the value of an element is at the same time its key, used to identify it.
 Keys are immutable, therefore, the elements in an unordered_multiset cannot be modified once in the container - they can be inserted and removed, though.

 Internally, the elements in the unordered_multiset are not sorted in any particular, but organized into buckets depending on their hash values to allow for fast access to individual elements directly by their values (with a constant average time complexity on average).

 Elements with equivalent values are grouped together in the same bucket and in such a way that an iterator (see equal_range) can iterate through all of them.

 Iterators in the container are at least forward iterators.

 Notice that this container is not defined in its own header, but shares header <unordered_set> with unordered_set.
 
 */
void Test_normal_multiset() {

    
}

void Test_UserDefined_set() {

    auto hash_cord = [](const CORD& c) {
        return hash<int>()(c.first) ^ hash<int>()(c.second);
    };
    
    auto equal_cord = [](const CORD& a, const CORD& b){
        return a.first == b.first && a.second == b.second;
    };
    
    typedef unordered_set<CORD, decltype(hash_cord), decltype(equal_cord)> CORD_SET;
    
	CORD_SET A(10, hash_cord, equal_cord);
	CORD c = make_pair(1, 2);
	CORD d = make_pair(0, 0);

	A.emplace(c);


	if (A.find(c) != A.end()) {
		cout << "find it" << endl;
	}

	if (A.find(d) != A.end()) {
		cout << "find it" << endl;
	}
}


struct Cord {
	int x, y;

	Cord(int i, int j) : x(i), y(j) {}

	bool operator == (const Cord& c) const {
		return this->x == c.x && this->y == c.y;
	}
};

namespace std {

	template<>
	class hash<Cord> {
	public:

		size_t operator ()(const Cord& d) const {
			return hash<int>()(d.x) ^ hash<int>()(d.y);
		}
	};

}

void Test_UserDefined_set2() {

	unordered_set<Cord> CordSet;

	CordSet.insert(Cord(1, 2));
	CordSet.insert(Cord(2, 3));

	if (CordSet.find(Cord(1, 2)) == CordSet.end()) {
		cout << "Didn't find it" << endl;
	}
	else {
		cout << "find it" << endl;
	}
    
    cout << "Count of Cord(1,2) : " << CordSet.count(Cord(1, 2)) << endl;


	if (CordSet.find(Cord(2, 4)) == CordSet.end()) {
		cout << "Didn't find it" << endl;
	}
	else {
		cout << "find it" << endl;
	}
    
    cout << "Count of Cord(2, 4) : " << CordSet.count(Cord(2, 4)) << endl;

}




void Test_Unordered_set() {

	Test_UserDefined_set2();

	Test_normal_set();

	Test_UserDefined_set(); 

}



