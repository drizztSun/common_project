#include <stdio.h>
#include <string_view>
#include <stdexcept>
#include <algorithm>
#include <array>
#include <map>

/*
 
 C++ attribute: nodiscard (since C++17)
 If a function declared nodiscard or a function returning an enumeration or class declared nodiscard by value is called from a discarded-value expression other than a cast to void, the compiler is encouraged to issue a warning.
 
 Syntax
 [[nodiscard]]    (1)
 [[nodiscard( string-literal )]]    (2)    (since C++20)
 string-literal    -    text that could be used to explain the rationale for why the result should not be discarded
 Explanation
 Appears in a function declaration, enumeration declaration, or class declaration.

 If, from a discarded-value expression other than a cast to void,

 a function declared nodiscard is called, or
 a function returning an enumeration or class declared nodiscard by value is called, or
 a constructor declared nodiscard is called by explicit type conversion or static_cast, or
 an object of an enumeration or class type declared nodiscard is initialized by explicit type conversion or static_cast,
 the compiler is encouraged to issue a warning.

 The string-literal, if specified, is usually included in the warnings.

 
 (since C++20)
 Example
 Run this code
 
 struct [[nodiscard]] error_info { };
 
 error_info enable_missile_safety_mode();
 
 void launch_missiles();
 
 void test_missiles() {
    enable_missile_safety_mode(); // compiler may warn on discarding a nodiscard value
    launch_missiles();
 }
 
 error_info& foo();
 void f1() {
     foo(); // nodiscard type is not returned by value, no warning
 }

 */

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
    
    // map.at(sv); discard return value and error reports
    
    return map.at(sv);
}

int test_main() {
    static constexpr auto map = Map<std::string_view, int, color_values.size()>{{color_values}};
    auto value = map.at("green");
    // with thie constexpr, the ASM code will be only one line, 'ret 2'
    // and if key 'green' has typo, it will report compile error, because of constexpr.
    // without this one, that will be a full function call to Map.at('green')
    return value;
}
