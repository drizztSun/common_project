

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

	operator string() const {
		string a = x + "" + y;
		return a;
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

		cout << "key : " << t.first.x << " , " << t.first.y << " num " << t.second << endl;
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

	/*
	template <class... Args>
		pair<iterator, bool> emplace ( Args&&... args );
	Construct and insert element
	Inserts a new element in the unordered_map if its key is unique. This new element is constructed in place using args as the arguments for the element's constructor.

	The insertion only takes place if no element in the container has a key equivalent to the one being emplaced (keys in an unordered_map are unique).

	If inserted, this effectively increases the container size by one.

	A similar member function exists, insert, which either copies or moves existing objects into the container.
	*/
	cord2_map.emplace(cord2(5, 8), 9);
	cord2_map.emplace(cord2(7, 8), 10);

	/*
	template <class... Args>
		iterator emplace_hint ( const_iterator position, Args&&... args );
		Construct and insert element with hint
	Inserts a new element in the unordered_map if its key is unique. This new element is constructed in place using args as the arguments for the element's constructor. position points to a location in the container suggested as a hint on where to start the search for its insertion point (the container may or may not use this suggestion to optimize the insertion operation).

	The insertion only takes place if no element in the container has a key equivalent to the one being emplaced (keys in an unordered_map are unique).

	If inserted, this effectively increases the container size by one.

	A similar member function exists, insert, which either copies or moves an existing object into the container, and may also take a position hint.
	*/
	auto it = cord2_map.begin();
	it = cord2_map.emplace_hint(it, cord2(7, 9), 100);
	it = cord2_map.emplace_hint(it, cord2(8, 9), 200);

	for (auto c = cord2_map.begin(); c != cord2_map.end(); c++) {
		cout << static_cast<string>(c->first).c_str() << " : " << c->second << endl;
	}


	/*
	by position (1)	
	iterator erase ( const_iterator position );
	by key (2)	
	size_type erase ( const key_type& k );
	range (3)	
	iterator erase ( const_iterator first, const_iterator last );
	Erase elements
	Removes from the unordered_map container either a single element or a range of elements ([first,last)).

	This effectively reduces the container size by the number of elements removed, calling each element's destructor.
	*/

	cord2_map.erase(cord2_map.begin()); // erasing by iterator
	cord2_map.erase(cord2(2, 3)); // erasing by key
	cord2_map.erase(cord2_map.find(cord2(7, 9)), cord2_map.end()); // erasing by range

	for ( auto& x: cord2_map )
    	std::cout << static_cast<string>(x.first).c_str() << ": " << x.second << std::endl;
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
    
    // Capacity
    {
        // empty()
        // Test whether container is empty
        // Returns a bool value indicating whether the unordered_map container is empty, i.e. whether its size is 0.
        std::unordered_map<int,int> first;
        std::unordered_map<int,int> second = {{1,10},{2,20},{3,30}};
        std::cout << "first " << (first.empty() ? "is empty" : "is not empty" ) << std::endl;
        std::cout << "second " << (second.empty() ? "is empty" : "is not empty" ) << std::endl;
        
        // size()
        // Return container size
        // Returns the number of elements in the unordered_map container.
        
        std::unordered_map<std::string,double> mymap = {
             {"milk",2.30},
             {"potatoes",1.90},
             {"eggs",0.40}
        };

        std::cout << "mymap.size() is " << mymap.size() << std::endl;
        
        // max_size()
        // Return maximum size
        // Returns the maximum number of elements that the unordered_map container can hold.
        // This is the maximum potential number of elements the container can hold due to system constraints or limitations on its library implementation.
        
        std::unordered_map<int,int> mymap1;

        std::cout << "max_size = " << mymap1.max_size() << std::endl;
        std::cout << "max_bucket_count = " << mymap1.max_bucket_count() << std::endl;
        std::cout << "max_load_factor = " << mymap1.max_load_factor() << std::endl;
    }
    
    // Iterators
    {
        // begin() or end()
        // Return iterator to beginning
        // Returns an iterator pointing to the first element in the unordered_map container (1) or in one of its buckets (2).

        // Notice that an unordered_map object makes no guarantees on which specific element is considered its first element. But, in any case, the range that goes from its begin to its end covers all the elements in the container (or the bucket), until invalidated.
        std::unordered_map<std::string,std::string> mymap;
        mymap = {{"Australia","Canberra"},{"U.S.","Washington"},{"France","Paris"}};

        std::cout << "mymap contains:";
        for ( auto it = mymap.begin(); it != mymap.end(); ++it )
          std::cout << " " << it->first << ":" << it->second;
        std::cout << std::endl;

        std::cout << "mymap's buckets contain:\n";
        for ( unsigned i = 0; i < mymap.bucket_count(); ++i) {
          std::cout << "bucket #" << i << " contains:";
          for ( auto local_it = mymap.begin(i); local_it!= mymap.end(i); ++local_it )
            std::cout << " " << local_it->first << ":" << local_it->second;
          std::cout << std::endl;
        }
            
        // cbegin() or cend()
        // Return const_iterator to beginning
        // Returns a const_iterator pointing to the first element in the unordered_map container (1) or in one of its buckets (2).
        std::cout << "mymap contains:";
        for ( auto it = mymap.cbegin(); it != mymap.cend(); ++it )
          std::cout << " " << it->first << ":" << it->second;  // cannot modify *it
        std::cout << std::endl;

        std::cout << "mymap's buckets contain:\n";
        for ( unsigned i = 0; i < mymap.bucket_count(); ++i) {
          std::cout << "bucket #" << i << " contains:";
          for ( auto local_it = mymap.cbegin(i); local_it!= mymap.cend(i); ++local_it )
            std::cout << " " << local_it->first << ":" << local_it->second;
          std::cout << std::endl;
        }
    }
    
            
    {
        // Element Access
        
        // unordered_map::operator[]
        // mapped_type& operator[] ( const key_type& k );
        // mapped_type& operator[] ( key_type&& k );
        // Access element
        // If k matches the key of an element in the container, the function returns a reference to its mapped value.
        std::unordered_map<std::string,std::string> mymap;

        mymap["Bakery"]="Barbara";  // new element inserted
        mymap["Seafood"]="Lisa";    // new element inserted
        mymap["Produce"]="John";    // new element inserted

        std::string name = mymap["Bakery"];   // existing element accessed (read)
        mymap["Seafood"] = name;              // existing element accessed (written)

        mymap["Bakery"] = mymap["Produce"];   // existing elements accessed (read/written)

        name = mymap["Deli"];      // non-existing element: new element "Deli" inserted!

        mymap["Produce"] = mymap["Gifts"];    // new element "Gifts" inserted, "Produce" written

        for (auto& x: mymap) {
          std::cout << x.first << ": " << x.second << std::endl;
        }
        
        // std::unordered_map::at
        // mapped_type& at ( const key_type& k );
        // const mapped_type& at ( const key_type& k ) const;
        // Access element
        // Returns a reference to the mapped value of the element with key k in the unordered_map.

        // If k does not match the key of any element in the container, the function throws an out_of_range exception.
        
        std::unordered_map<std::string,int> mymap1 = {
                      { "Mars", 3000},
                      { "Saturn", 60000},
                      { "Jupiter", 70000 } };

        mymap1.at("Mars") = 3396;
        mymap1.at("Saturn") += 272;
        mymap1.at("Jupiter") = mymap1.at("Saturn") + 9638;

        for (auto& x: mymap) {
          std::cout << x.first << ": " << x.second << std::endl;
        }
    }

    // Element lookup
    {
        // find
        // Searches the container for an element with k as key and returns an iterator to it if found,
        // otherwise it returns an iterator to unordered_map::end (the element past the end of the container).
        
        std::unordered_map<std::string,double> mymap = {
           {"mom",5.4},
           {"dad",6.1},
           {"bro",5.9} };

        std::unordered_map<std::string,double>::const_iterator got = mymap.find ("mom");

        if ( got == mymap.end() )
          std::cout << "not found";
        else
          std::cout << got->first << " is " << got->second;

        std::cout << std::endl;
        
        // count
        // Searches the container for elements whose key is k and returns the number of elements found.
        // Because unordered_map containers do not allow for duplicate keys, this means that the function actually returns 1 if an element with that key exists in the container, and zero otherwise.
        std::unordered_map<std::string,double> mymap1 = {
           {"Burger",2.99},
           {"Fries",1.99},
           {"Soda",1.50}
        };

        for (auto& x: {"Burger","Pizza","Salad","Soda"}) {
          if (mymap1.count(x)>0)
            std::cout << "mymap has " << x << std::endl;
          else
            std::cout << "mymap has no " << x << std::endl;
        }
        
        //
    }
            
    // Modifiers
    {
        // emplace
        // Construct and insert element
        // Inserts a new element in the unordered_map if its key is unique. This new element is constructed in place using args as the arguments for the element's constructor.
        {
            std::unordered_map<std::string,std::string> mymap;

            mymap.emplace ("NCC-1701", "J.T. Kirk");
            mymap.emplace ("NCC-1701-D", "J.L. Picard");
            mymap.emplace ("NCC-74656", "K. Janeway");

            std::cout << "mymap contains:" << std::endl;
            for (auto& x: mymap)
              std::cout << x.first << ": " << x.second << std::endl;

            std::cout << std::endl;
        }
        
        // insert
        // Insert elements
        // Inserts new elements in the unordered_map.
        // Each element is inserted only if its key is not equivalent to the key of any other element already in the container (keys in an unordered_map are unique).
        // This effectively increases the container size by the number of elements inserted.
        // The parameters determine how many elements are inserted and to which values they are initialized:
        {
            std::unordered_map<std::string,double>
                        myrecipe,
                        mypantry = {{"milk",2.0},{"flour",1.5}};

            std::pair<std::string,double> myshopping ("baking powder",0.3);

            myrecipe.insert (myshopping);                        // copy insertion
            myrecipe.insert (std::make_pair<std::string,double>("eggs",6.0)); // move insertion
            myrecipe.insert (mypantry.begin(), mypantry.end());  // range insertion
            myrecipe.insert ( {{"sugar",0.8},{"salt",0.1}} );    // initializer list insertion

            std::cout << "myrecipe contains:" << std::endl;
            for (auto& x: myrecipe)
              std::cout << x.first << ": " << x.second << std::endl;

            std::cout << std::endl;
        }
        
        // erase
        // Erase elements
        // Removes from the unordered_map container either a single element or a range of elements ([first,last)).
        // This effectively reduces the container size by the number of elements removed, calling each element's destructor.
        {
            std::unordered_map<std::string,std::string> mymap1;

            // populating container:
            mymap1["U.S."] = "Washington";
            mymap1["U.K."] = "London";
            mymap1["France"] = "Paris";
            mymap1["Russia"] = "Moscow";
            mymap1["China"] = "Beijing";
            mymap1["Germany"] = "Berlin";
            mymap1["Japan"] = "Tokyo";

            // erase examples:
            mymap1.erase ( mymap1.begin() );      // erasing by iterator
            mymap1.erase ("France");             // erasing by key
            mymap1.erase ( mymap1.find("China"), mymap1.end() ); // erasing by range

            // show content:
            for ( auto& x: mymap1 )
              std::cout << x.first << ": " << x.second << std::endl;
        }
        
        // clear
        // Clear content
        // All the elements in the unordered_map container are dropped: their destructors are called, and they are removed from the container, leaving it with a size of 0.
        {
            std::unordered_map<std::string,std::string> mymap =
                   { {"house","maison"}, {"car","voiture"}, {"grapefruit","pamplemousse"} };

            std::cout << "mymap contains:";
            for (auto& x: mymap) std::cout << " " << x.first << "=" << x.second;
            std::cout << std::endl;

            mymap.clear();
            mymap["hello"]="bonjour";
            mymap["sun"]="soleil";

            std::cout << "mymap contains:";
            for (auto& x: mymap) std::cout << " " << x.first << "=" << x.second;
            std::cout << std::endl;
        }
        
        // swap
        // Swap content
        // Exchanges the content of the container by the content of ump, which is another unordered_map object containing elements of the same type. Sizes may differ.

        // After the call to this member function, the elements in this container are those which were in ump before the call, and the elements of ump are those which were in this. Other objects kept internally by the containers (such as their hasher or key_equal objects) are also swapped.
        {
            std::unordered_map<std::string,std::string>
               first = {{"Star Wars","G. Lucas"},{"Alien","R. Scott"},{"Terminator","J. Cameron"}},
               second  = {{"Inception","C. Nolan"},{"Donnie Darko","R. Kelly"}};

            first.swap(second);

            std::cout << "first: ";
            for (auto& x: first) std::cout << x.first << " (" << x.second << "), ";
            std::cout << std::endl;

            std::cout << "second: ";
            for (auto& x: second) std::cout << x.first << " (" << x.second << "), ";
            std::cout << std::endl;
        }
    }

    // Bucket
    {
        {
            // bucket_count()
            // size_type bucket_count() const noexcept;
            // Return number of buckets
            // Returns the number of buckets in the unordered_map container.
            // A bucket is a slot in the container's internal hash table to which elements are assigned based on the hash value of their key.
            std::unordered_map<std::string,std::string> mymap = {
                      {"house","maison"},
                      {"apple","pomme"},
                      {"tree","arbre"},
                      {"book","livre"},
                      {"door","porte"},
                      {"grapefruit","pamplemousse"}
            };

            unsigned n = mymap.bucket_count();

            std::cout << "mymap has " << n << " buckets.\n";

            for (unsigned i=0; i<n; ++i) {
              std::cout << "bucket #" << i << " contains: ";
              for (auto it = mymap.begin(i); it!=mymap.end(i); ++it)
                std::cout << "[" << it->first << ":" << it->second << "] ";
              std::cout << "\n";
            }
            
        }
        
        {
            // max_bucket_count
            // Return maximum number of buckets
            // Returns the maximum number of buckets that the unordered_map container can have.

            // This is the maximum potential number of buckets the container can have due to system constraints or limitations on its library implementation.
            std::unordered_map<int,int> mymap;

            std::cout << "max_size = " << mymap.max_size() << std::endl;
            std::cout << "max_bucket_count = " << mymap.max_bucket_count() << std::endl;
            std::cout << "max_load_factor = " << mymap.max_load_factor() << std::endl;
        }
            
        {
            // bucket
            // Locate element's bucket
            // Returns the bucket number where the element with key k is located.
            // A bucket is a slot in the container's internal hash table to which elements are assigned based on the hash value of their key. Buckets are numbered from 0 to (bucket_count-1).
            // Individual elements in a bucket can be accessed by means of the range iterators returned by unordered_map::begin and unordered_map::end.
            
            std::unordered_map<std::string,std::string> mymap = {
              {"us","United States"},
              {"uk","United Kingdom"},
              {"fr","France"},
              {"de","Germany"}
            };

            for (auto& x: mymap) {
              std::cout << "Element [" << x.first << ":" << x.second << "]";
              std::cout << " is in bucket #" << mymap.bucket(x.first) << std::endl;
            }
        }
            
        {
            // bucket_size
            // Return bucket size
            // Returns the number of elements in bucket n.
            // A bucket is a slot in the container's internal hash table to which elements are assigned based on the hash value of their key.
            std::unordered_map<std::string,std::string> mymap = {
              {"us","United States"},
              {"uk","United Kingdom"},
              {"fr","France"},
              {"de","Germany"}
            };

            unsigned nbuckets = mymap.bucket_count();

            std::cout << "mymap has " << nbuckets << " buckets:\n";

            for (unsigned i=0; i<nbuckets; ++i) {
              std::cout << "bucket #" << i << " has " << mymap.bucket_size(i) << " elements.\n";
            }
        }
    }
    
    // hash policy
    {
        {
            // load_factor
            // Return load factor
            // Returns the current load factor in the unordered_map container.
            // The load factor is the ratio between the number of elements in the container (its size) and the number of buckets (bucket_count):
            
            std::unordered_map<int,int> mymap;

            std::cout << "size = " << mymap.size() << std::endl;
            std::cout << "bucket_count = " << mymap.bucket_count() << std::endl;
            std::cout << "load_factor = " << mymap.load_factor() << std::endl;
            std::cout << "max_load_factor = " << mymap.max_load_factor() << std::endl;
        }
        
        {
            // max_load_factor
            // get (1)
            // float max_load_factor() const noexcept;
            // set (2)
            // void max_load_factor ( float z );
            // Get or set maximum load factor
            // The first version (1) returns the current maximum load factor for the unordered_map container.
            // The second version (2) sets z as the new maximum load factor for the unordered_map container.
            
            std::unordered_map<std::string,std::string> mymap = {
               {"Au","gold"},
               {"Ag","Silver"},
               {"Cu","Copper"},
               {"Pt","Platinum"}
             };

             std::cout << "current max_load_factor: " << mymap.max_load_factor() << std::endl;
             std::cout << "current size: " << mymap.size() << std::endl;
             std::cout << "current bucket_count: " << mymap.bucket_count() << std::endl;
             std::cout << "current load_factor: " << mymap.load_factor() << std::endl;

             float z = mymap.max_load_factor();
             mymap.max_load_factor ( z / 2.0 );
             std::cout << "[max_load_factor halved]" << std::endl;

             std::cout << "new max_load_factor: " << mymap.max_load_factor() << std::endl;
             std::cout << "new size: " << mymap.size() << std::endl;
             std::cout << "new bucket_count: " << mymap.bucket_count() << std::endl;
             std::cout << "new load_factor: " << mymap.load_factor() << std::endl;
        }
        
        {
            // rehash
            // void rehash( size_type n );
            // Set number of buckets
            // Sets the number of buckets in the container to n or more.
            // If n is greater than the current number of buckets in the container (bucket_count), a rehash is forced. The new bucket count can either be equal or greater than n.
            std::unordered_map<std::string,std::string> mymap;

            mymap.rehash(20);

            mymap["house"] = "maison";
            mymap["apple"] = "pomme";
            mymap["tree"] = "arbre";
            mymap["book"] = "livre";
            mymap["door"] = "porte";
            mymap["grapefruit"] = "pamplemousse";

            std::cout << "current bucket_count: " << mymap.bucket_count() << std::endl;
        }
        
        {
            // reserve
            // void reserve ( size_type n );
            // Request a capacity change
            // Sets the number of buckets in the container (bucket_count) to the most appropriate to contain at least n elements.

            // If n is greater than the current bucket_count multiplied by the max_load_factor, the container's bucket_count is increased and a rehash is forced.

            // If n is lower than that, the function may have no effect.
            std::unordered_map<std::string,std::string> mymap;

            mymap.reserve(6);

            mymap["house"] = "maison";
            mymap["apple"] = "pomme";
            mymap["tree"] = "arbre";
            mymap["book"] = "livre";
            mymap["door"] = "porte";
            mymap["grapefruit"] = "pamplemousse";

            for (auto& x: mymap) {
              std::cout << x.first << ": " << x.second << std::endl;
            }
        }
    }
    
    // Observes
    {
        {
            // hash_function
            // hasher hash_function() const;
            // Get hash function
            // Returns the hash function object used by the unordered_map container.
            typedef std::unordered_map<std::string,std::string> stringmap;
            stringmap mymap;
            stringmap::hasher fn = mymap.hash_function();
            std::cout << "this: " << fn ("this") << std::endl;
            std::cout << "thin: " << fn ("thin") << std::endl;
        }
        
        {
            // key_eq
            // key_equal key_eq() const;
            // Get key equivalence predicate
            // Returns the key equivalence comparison predicate used by the unordered_map container.

            // The key equivalence comparison is a predicate that takes two arguments of the key type and returns a bool value indicating whether they are to be considered equivalent. It is adopted by the container on construction (see unordered_map's constructor for more info). By default, it is equal_to<key_type>, which returns the same as applying the equal-to operator (==) to the arguments.
            
            std::unordered_map<std::string,std::string> mymap;

            bool case_insensitive = mymap.key_eq()("test","TEST");

            std::cout << "mymap.key_eq() is ";
            std::cout << ( case_insensitive ? "case insensitive" : "case sensitive" );
            std::cout << std::endl;
        }
    }
}

void TestUnorderMap() {

    BasicKeyInMap();

    UserDefinedKeyInMap();

    UserDefinedClassAsKeyInMap();
}
