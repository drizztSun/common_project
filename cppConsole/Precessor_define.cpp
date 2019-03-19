#include <iostream>

/*

# and ## operators
In function-like macros, a # operator before an identifier in the replacement-list runs the identifier 
through parameter replacement and encloses the result in quotes, effectively creating a string literal. 
In addition, the preprocessor adds backslashes to escape the quotes surrounding embedded string literals, 
if any, and doubles the backslashes within the string as necessary. All leading and trailing whitespace is removed, 
and any sequence of whitespace in the middle of the text (but not inside embedded string literals) is collapsed to a single space. 
This operation is called "stringification". 
If the result of stringification is not a valid string literal, the behavior is undefined.


A ## operator between any two successive identifiers in the replacement-list runs parameter replacement on the two identifiers 
(which are not macro-expanded first) and then concatenates the result. This operation is called "concatenation" or "token pasting". 
Only tokens that form a valid token together may be pasted: identifiers that form a longer identifier, 
digits that form a number, or operators + and = that form a +=. 

A comment cannot be created by pasting / and * because comments are removed from text before macro substitution is considered. 
If the result of concatenation is not a valid token, the behavior is undefined.

Note: some compilers offer an extension that allows ## to appear after a comma and before __VA_ARGS__, 
in which case the ## does nothing when the variable arguments are present, 
but removes the comma when the variable arguments are not present: 

this makes it possible to define macros such as fprintf (stderr, format, ##__VA_ARGS__)
*/


// make function factory and use it
#define FUNCTION(name, a) int func_##name() {return a;}

FUNCTION(ABCD, 12)
FUNCTION(fff, 2)
FUNCTION(qqq, 3)


#undef FUNCTION

#define FUNCTION 34
#define OUTPUT(a) std::cout<< "output : "  #a << '\n';

void test_define() {

	std::cout << "ABCD " << func_ABCD() << '\n';
	std::cout << "fff " << func_fff() << '\n';
	std::cout << "qqq " << func_qqq() << '\n';
	std::cout << FUNCTION << '\n';

	OUTPUT(million)
}