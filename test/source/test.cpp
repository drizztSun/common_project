#include <stdio.h>
#include <map>

using std::map;

int main() {

    map<int, int> dp;

    dp.insert({1, 2});
    dp.insert({2, 3});
    dp.insert({3, 4});
    dp.insert({4, 5});
    dp.insert({5, 6});

    for (auto it = begin(dp); it != dp.end(); it++) {
        
        std::cout << it->first << ":" << it->second << std::endl;

        it = dp.erase(it);
    }
}