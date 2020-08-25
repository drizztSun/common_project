#include <stdio.h>
#include <string_view>
#include <stdexcept>
#include <algorithm>
#include <array>
#include <map>

template <typename Key, typename Value, std::size_t Size>
struct Map {
    std::array<std::pair<Key, Value>, Size> data;

    [[nodiscard]] constexpr Value at(const Key &key) const {
        const auto itr = std::find_if(begin(data), end(data), [&key](const auto &v) {return v.first == key;});
        if (itr != end(data)) {
            return itr->second;
        }
        throw std::range_error("Not Found");
    }
};

using namespace std::literals::string_view_literals;
static constexpr std::array<std::pair<std::string_view, int>, 8> color_values{
    {{"black"sv, 7}, // sv 
    {"blue"sv, 3},
    {"cyan"sv, 5},
    {"green"sv, 2},
    {"magenta"sv, 6},
    {"red"sv, 1},
    {"white"sv, 8},
    {"yellow"sv, 4}}};

// Compiler Explorer, we can verify the ASM code
// in lookup_value, the code "map.at(sv)" will be expanded into code to check string key and return the int value.
// you can refer it from Compiler Explorer

int lookup_value(const std::string_view sv) { // sv will be to pass by value by using [rsi] pointer to string, [rdi] size

    
    // standard map, 10 times slower than constexpr
    // static const auto map = std::map<std::string_view, int>{color_values.begin(), color_values.end()}

    // static is important key that makes 'map' allocate from application global static memory
    // without static, it will expand this in current function call stack.
    //
    static constexpr auto map = Map<std::string_view, int, color_values.size()>{{color_values}};
    
    // flat map way,
    // auto map = Map<std::string_view, int, color_values.size()>{{color_values}};
    
    return map.at(sv);
}

int test_main() {
    static constexpr auto map = Map<std::string_view, int, color_values.size()>{{color_values}};
    constexpr auto value = map.at("green");
    // with thie constexpr, the ASM code will be only one line, 'ret 2'
    // and if key 'green' has typo, it will report compile error, because of constexpr.
    // without this one, that will be a full function call to Map.at('green')
    return value;
}
