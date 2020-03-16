#include <stdlib.h>
#include <iostream>
#include <unordered_set>
#include <functional>

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

void Test_normal_set() {

	unordered_set<int> cord{ 1, 2, 3, 4, 5, 6};

	if (cord.find(2) != cord.end()) {

		cout << " Have it done " << endl;
	} else {

		cout << " Haven't found it " << endl;
	}
	
}


void Test_UserDefined_set() {

	// typedef unordered_set<CORD, function<decltype(cord_hash1)>> CORD_SET;

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


	if (CordSet.find(Cord(2, 4)) == CordSet.end()) {
		cout << "Didn't find it" << endl;
	}
	else {
		cout << "find it" << endl;
	}

}




void Test_Unordered_set() {

	Test_UserDefined_set2();

	Test_normal_set();

	Test_UserDefined_set(); 

}



