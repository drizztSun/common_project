#include <stdio.h>
#include <string_view>
#include <iostream>
#include <stdexcept>

/*
 std::basic_string_view
 
 Defined in header <string_view>
 
 template<
     class CharT,
     class Traits = std::char_traits<CharT>
 > class basic_string_view;
 
 (since C++17)
 
 The class template basic_string_view describes an object that can refer to a constant contiguous sequence of char-like objects with the first element of the sequence at position zero.
 A typical implementation holds only two members: a pointer to constant CharT and a size.
 
 private:
 const   value_type* __data;
 size_type           __size;
 
 Several typedefs for common character types are provided:

 Defined in header <string_view>
 Type    Definition
 std::string_view    std::basic_string_view<char>
 std::wstring_view    std::basic_string_view<wchar_t>
 std::u8string_view (C++20)    std::basic_string_view<char8_t>
 std::u16string_view    std::basic_string_view<char16_t>
 std::u32string_view    std::basic_string_view<char32_t>
 
 Template parameters
 CharT    -    character type
 Traits    -    CharTraits class specifying the operations on the character type. Like for basic_string, Traits::char_type must name the same type as CharT or the program is ill-formed.
 
 Member types
 Member type    Definition
 traits_type    Traits
 value_type    CharT
 pointer    CharT*
 const_pointer    const CharT*
 reference    CharT&
 const_reference    const CharT&
 const_iterator    implementation-defined constant LegacyRandomAccessIterator, ConstexprIterator (since C++20) and LegacyContiguousIterator whose value_type is CharT
 iterator    const_iterator
 const_reverse_iterator    std::reverse_iterator<const_iterator>
 reverse_iterator    const_reverse_iterator
 size_type    std::size_t
 difference_type    std::ptrdiff_t
 Note: iterator and const_iterator are the same type because string views are views into constant character sequences.

 All requirements on the iterator types of a Container applies to the iterator and const_iterator types of basic_string_view as well.
 */





void test_string_view() {
    
    // Iterator
    {
       std::string_view str_view("abcd");
    
       auto begin = str_view.begin();
       auto cbegin = str_view.cbegin();
    
       std::cout << *begin << '\n';
       std::cout << *cbegin << '\n';
    
       std::cout << std::boolalpha << (begin == cbegin) << '\n';
       std::cout << std::boolalpha << (*begin == *cbegin) << '\n';
    }
    
    {
       std::string_view str_view("abcd");
    
       auto end = str_view.end();
       auto cend = str_view.cend();
    
       std::cout << *std::prev(end) << '\n';
       std::cout << *std::prev(cend) << '\n';
    
       std::cout << std::boolalpha << (end == cend) << '\n';
    }
    
    {
       std::ostream_iterator<char> out_it(std::cout);
       std::string_view str_view("abcdef");
    
       std::copy(str_view.rbegin(), std::next(str_view.rbegin(), 3), out_it);
       *out_it = '\n';
    
       std::copy(str_view.crbegin(), std::next(str_view.crbegin(), 3), out_it);
       *out_it = '\n';
    }
    
    {
       std::ostream_iterator<char> out_it(std::cout);
       std::string_view str_view("abcdef");
    
       std::copy(str_view.rbegin(), str_view.rend(), out_it);
       *out_it = '\n';
    
       std::copy(str_view.crbegin(), str_view.crend(), out_it);
       *out_it = '\n';
    }
    
    // Element Access
    {
        std::string str = "Exemplar";
        std::string_view v = str;
        std::cout << v[2] << '\n';
        //***  v[2] = 'y'; // Error: cannot modify through a string view
        str[2] = 'y';
        std::cout << v[2] << '\n';
    }
    
    {
        std::string_view str_view("abcdef");
     
        try {
            for (std::size_t i = 0; true; ++i)
                std::cout << i << ": " << str_view.at(i) << '\n';
        }
        catch (const std::out_of_range& e) {
            std::cout << "Whooops. Index is out of range.\n";
            std::cout << e.what() << '\n';
        }
    }
    
    {
        std::wstring_view wcstr_v = L"xyzzy";
        std::cout << std::wcslen(wcstr_v.data()) << '\n';
        // OK: the underlying character array is null-terminated
     
        char array[3] = {'B', 'a', 'r'};
        std::string_view array_v(array, sizeof array);
        // std::cout << std::strlen(array_v.data()) << '\n';
        // error: the underlying character array is not null-terminated
     
        std::string str(array_v.data(), array_v.size()); // OK
        std::cout << std::strlen(str.data()) << '\n';
        // OK: the underlying character array of a std::string is always null-terminated
    }
    
    // Capacity
    {
        std::string_view ref("abcdef");
        // Print a string surrounded by single quotes, its length
        // and whether it is considered empty.
        std::cout << std::boolalpha
                  << "'" << ref << "' has " << ref.size()
                  << " character(s); emptiness: " << ref.empty() << '\n';
    }
    
    // Modifiers
    {
        std::string str = "   trim me";
        std::string_view v = str;
        v.remove_prefix(std::min(v.find_first_not_of(" "), v.size()));
        std::cout << "String: '" << str << "'\n"
                  << "View  : '" << v << "'\n";
    }
    
    {
        char arr[] = {'a', 'b', 'c', 'd', '\0', '\0', '\0'};
        std::string_view v(arr, sizeof arr);
        auto trim_pos = v.find('\0');
        if(trim_pos != v.npos)
            v.remove_suffix(v.size() - trim_pos);
        std::cout << "Array: '" << arr << "', size=" << sizeof arr << '\n'
                  << "View : '" << v << "', size=" << v.size() << '\n';
    }
    
    // Operations

    {
        using namespace std::literals;
     
        std::cout
            << std::boolalpha
     
            // bool starts_with(basic_string_view x) const noexcept;
            << std::string_view("https://cppreference.com").starts_with("http"sv) << ' ' // true
            << std::string_view("https://cppreference.com").starts_with("ftp"sv) << ' '  // false
     
            // bool starts_with(CharT x) const noexcept;
            << std::string_view("C++20").starts_with('C') << ' ' // true
            << std::string_view("C++20").starts_with('J') << ' ' // false
     
            // bool starts_with(const CharT* x) const;
            << std::string_view("string_view").starts_with("string") << ' ' // true
            << std::string_view("string_view").starts_with("String") << ' ' // false
            << '\n';
    }
    
    {
        using namespace std::literals;
     
        std::cout
            << std::boolalpha
     
            // (1) bool ends_with( basic_string_view sv ) const noexcept;
            << std::string_view("https://cppreference.com").ends_with(".com"sv) << ' ' // true
            << std::string_view("https://cppreference.com").ends_with(".org"sv) << ' ' // false
     
            // (2) bool ends_with( CharT c ) const noexcept;
            << std::string_view("C++20").ends_with('0') << ' ' // true
            << std::string_view("C++20").ends_with('3') << ' ' // false
     
            // (3) bool ends_with( const CharT* s ) const;
            << std::string_view("string_view").ends_with("view") << ' ' // true
            << std::string_view("string_view").ends_with("View") << ' ' // false
            << '\n';
    }
}
