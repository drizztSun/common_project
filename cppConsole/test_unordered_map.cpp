

#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include <functional>

using namespace std;


typedef pair<int, int> CORD;

size_t cord_hash(const CORD& cord) {
	return hash<int>()(cord.first) ^ hash<int>()(cord.second);
}


void UserDefinedKeyInMap() {


	typedef unordered_map<CORD, int, function<decltype(cord_hash)>> CORD_MAP;
	CORD_MAP ids(100, cord_hash);

	ids[CORD({ 1, 2 })] = 3;
	ids[CORD({ 3, 4 })] = 7;
	ids[CORD({ 4, 3 })] = 7;

	ids.insert(CORD_MAP::value_type(make_pair(1, 3), 5));
	ids.insert(CORD_MAP::value_type(make_pair(1, 3), 4));

	ids.insert(CORD_MAP::value_type(make_pair(1, 3), 4));
	ids.insert(CORD_MAP::value_type(make_pair(1, 4), 5));
	ids.insert(CORD_MAP::value_type(make_pair(1, 5), 6));

	for (auto it = ids.begin(); it != ids.end(); it++) {

		cout << "x: " << it->first.first << " y: " << it->first.second << " Val: " << it->second << endl;
	}


	if (ids.find(CORD({ 1, 2 })) != ids.end()) {
		auto it = ids.find(CORD({ 1, 2 }));
		cout << " found element : " << it->second << endl;
	}


	if (ids.find(CORD({ 0, 2 })) != ids.end()) {
		auto it = ids.find(CORD({ 1, 2 }));
		cout << " found element : " << it->second << endl;
	}
	else {
		cout << " found no element" << endl;
	}
}


void BasicKeyInMap() {

	unordered_map<string, int> week{ {"Mon", 0}, {"Fri", 0} };

	week["Mon"] = 1;
	week["Fri"] = 5;

	week.emplace("Tue", 2);
	week.emplace("Thur", 4);

	week.insert(make_pair("Wed", 3));


	week.insert(unordered_map<string, int>::value_type("Sat", 6));
	week.insert(unordered_map<string, int>::value_type("Sun", 7));


	for (auto& c : week) {
		cout << " Weekday : " << c.first.c_str() << " Num: " << c.second;
	}


	


	week["Mon"] += 10;
	week.at("Tue") = week.at("Tue") + 10;

	cout << " Mon is only : " << week.count("Mon");
	cout << " Sunn is no : " << week.count("Sunn");

}

class cord2 {

public:

	int x, y;

	cord2() : x(0), y(0) {
	
	};

	cord2(int i, int j) : x(i), y(j) {

	};

	bool operator == (const cord2& a) const {
		return this->x == a.x && this->y == a.y;
	}
};

namespace std {


	template <>
	class hash<cord2> {

	public:

		size_t operator() (const cord2& d) const {

			return hash<int>()(d.x) ^ hash<int>()(d.y);
		}
	};

}



void UserDefinedClassAsKeyInMap() {

	unordered_map<cord2, int> cord2_map{ { cord2(1, 2), 3 } };

	cord2_map[cord2(3, 4)] = 7;
	cord2_map[cord2(5, 6)] = 11;

	for (auto t : cord2_map) {

		cout << "key : " << t.first.x << " , " << t.first.y << " num" << t.second << endl;
	}

	if (cord2_map.find(cord2(3, 4)) != cord2_map.end()) {
		cout << "find it " << endl;
	}
	else {
		cout << "didn't find it" << endl;
	}

	
	if (cord2_map.find(cord2(3, 3)) != cord2_map.end()) {
		cout << "find it " << endl;
	}
	else {
		cout << "didn't find it" << endl;
	}

}


void TestUnorderMap() {

	BasicKeyInMap();

	UserDefinedKeyInMap();

	UserDefinedClassAsKeyInMap();
}