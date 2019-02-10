package main

import (
	"fmt"
	"strings"
	"unicode/utf8"
)

func test_runa() {

	/*
		“Rune” means Unicode codepoint. (think of it as a character.) It is a jargon golang invented.
		When you see the word “rune”, you can think of it as any or all of the following:

		A integer. (possible values are from 0 to 2^32-1, but not all are valid unicode codepoint.)
		A golang type, with keyword rune. It is alias to the type int32
		A unicode codepoint.
		A character.*/

	var capA = 'A'

	fmt.Printf("%d %x %U\n", capA, capA, capA) // 65 41 U+0041
	/*
		Print Rune
		Rune is codepoint, thus is a integer.

		The following Printf formats work with integer:

		%c → character as is.
		%q → rune syntax. e.g. 'a'.
		%U → Unicode notation. e.g. U+03B1.
		%b → base 2
		%o → base 8
		%d → base 10
		%x → base 16, with lower-case letters for a-f*/

	var x = '😂'

	fmt.Printf("%c\n", x) // 😂
	fmt.Printf("%q\n", x) // '😂'
	fmt.Printf("%U\n", x) // U+1F602

	fmt.Printf("%b\n", x) // 11111011000000010
	fmt.Printf("%o\n", x) // 373002
	fmt.Printf("%d\n", x) // 128514
	fmt.Printf("%x\n", x) // 1f602
}

func test_Stringtofrombytes() {

	{
		// String to byte slice: []byte(str)
		var a = "abc→"
		var bs = ([]byte)(a)

		fmt.Printf("len of a : %d\n", len(a))
		fmt.Printf("len of bs: %d\n", len(bs))

		fmt.Printf("%v\n", bs) // [97 98 99 226 134 146]
	}

	{
		// Byte slice to string: string(byteslice)

		var bs = []byte{"a"[0], "b"[0], "c"[0], 0xE2, 0x86, 0x92}
		// 0xE2, 0x86, 0x92 is the utf8 encoding for →

		// convert byte slice to string
		var str = string(bs)

		fmt.Printf("%v\n", str) // abc→

		// print type
		fmt.Printf("%T\n", str) // string
	}
}

func test_StringToFromRune() {
	// Convert String To/From Rune Slice

	{ // String to rune slice: []rune(str)
		var str = "abc→"
		var rs = ([]rune)(str)

		fmt.Printf("%v \n", rs)
		fmt.Printf("%T \n", rs)
	}

	{ // Rune slice to string: string(runeslice)

		var rs = []rune{'a', 'b', 'c', '→'}

		// convert rune slice to string
		var str = string(rs)

		fmt.Printf("%#v\n", str) // "abc→"

		// print type
		fmt.Printf("%T\n", str) // string
	}
}

func test_BytesToFromRune() {
	// Convert Byte Slice To/From Rune Slice
	{
		var bs = []byte{"a"[0], "b"[0], "c"[0], 0xE2, 0x86, 0x92}
		// 0xE2, 0x86, 0x92 is the utf8 encoding for →

		// convert byte slice to rune slice
		var rs = []rune(string(bs))

		for _, v := range rs {
			fmt.Printf("%c", v)
		}
		// abc→

		fmt.Printf("\n")

		// print type
		fmt.Printf("%T\n", rs) // []int32
	}
}

func test_NumberOfCharacter() {
	/*
	   Number of Characters
	   To count the number of character, there are few ways:

	   Use import "unicode/utf8"

	   utf8.RuneCount(byteSlice) → return the number of characters in byteSlice.

	   utf8.RuneCountInString(string) → returns the number of character in string. (character here means Unicode codepoint, aka rune)

	   Or convert it to rune slice, then call len, e.g. len([]rune("I ♥ U"))*/

	var x = "I ♥ U"

	// number of bytes
	fmt.Printf("%v\n", len(x)) // 7

	// number of characters
	fmt.Printf("%v\n", utf8.RuneCountInString(x)) // 5
}

func test_substringByCharactorIndex() {
	// Substring by Character Index
	// To get a substring with proper character boundaries, convert it to rune slice first. Like this:
	// string of unicode
	var x = "♥😂→★🍎"

	// convert to rune slice
	var y = []rune(x)

	// take a slice from index 2 to 3
	var z = y[2:4]

	// print as chars
	fmt.Printf("%q\n", z) // ['→' '★']

	// print in go syntax
	fmt.Printf("%#v\n", z) // []int32{8594, 9733}
}

func Test_RuneIndex() {

	/*
		Given Byte Index that Start a Character, Find Its Char Index
		given a index (of a char start byte) of a string (or byte slice), find the corresponding rune (char start) index.
		solution:
		utf8.RuneCount(byteSlice[0,index])
		or
		utf8.RuneCountInString(textStr[0,index])
	*/
	// chinese text (or any text containing non-ASCII)
	var x = "中文和英文"

	// 6 is the start of the char 和
	var i = 6

	fmt.Printf("position of 和 is: %v\n", utf8.RuneCountInString(x[0:i])) // 2
	// position of 和 is: 2
}

func Test_randomRuneIndex() {
	/*
		Given a Random Byte Index, Find the Index that Start a Char
		given index of a byte slice, how to find the byte index that starts a character before the byte? (the byte slice may contain unicode)
		Solution:
		import "unicode/utf8"
		and
		for !utf8.RuneStart(textBytes[index]) { index-- }
	*/
	var x = "中文"
	// chinese

	var i = 4

	fmt.Printf("%q\n", x[i]) // '\u0096'
	// result is a byte inside unicode byte sequence

	// set index to the index that begins a char
	for !utf8.RuneStart(x[i]) {
		i--
	}

	fmt.Printf("%v\n", i) // 3
	// the index that begins a unicode char is 3

	fmt.Printf("%q\n", x[i:len(x)]) // "文"
	// now u can extra substring properly
}

func test_loopRuneString() {
	// 0 'a'
	// 1 'b'
	// 2 'c'
	// 3 '♥'
	// 6 ' '
	// 7 '😂'
	// 11 'd'
	const x = "abc♥ 😂d"
	for i, c := range x {
		fmt.Printf("%v %q\n", i, c)
	}
}

func Test_str() {

	test_basic()

	test_strreplace()
}

func replaceAtIndex1(str string, replacement rune, index int) string {

	out := []rune(str)
	out[index] = replacement
	// out = append(out[:i], string(replacement), out[i+1:]...)
	return string(out)
}

// it is wrong way, because string is utf8 and index can be nonsense
// we should find the correct index
func replaceAtIndex2(str string, replacement rune, index int) string {
	a, b := index, index
	for a > 0 && !utf8.RuneStart(str[a]) {
		a--
	}

	for b < len(str) && !utf8.RuneStart(str[b]) {
		b++
	}

	// index in utf8 string will automatically be treated as byte, so index + 1 is not a correct one
	return str[:a] + string(replacement) + str[b:]
}

func replaceAtIndex3(input string, replacement byte, index int) string {
	return strings.Join([]string{input[:index], string(replacement), input[index+1:]}, "")
}

func test_strreplace() {

	var a = "abcdefg"
	a = replaceAtIndex1(a, 'A', 2)
	fmt.Println(a)

	var b = "abc and ♥"
	b = replaceAtIndex1(b, '😂', 8)
	fmt.Println(b)

	var c = "abc and ♥"
	c = replaceAtIndex2(c, '😂', 10)
	fmt.Println(c)

	value := "Your cat is cute"
	fmt.Println(value)

	// Replace the "cat" with a "dog."
	result := strings.Replace(value, "cat", "dog", -1)
	fmt.Println(result)
	fmt.Println(value)
}

func test_strings_lib() {

	// String Functions
	// String functions are in package “strings”.

	var pl = fmt.Println

	pl(strings.Contains("abcd", "bc")) // true

	pl(strings.HasPrefix("abca", "ab")) // true

	pl(strings.HasSuffix("abca", "ca")) // true

	pl(strings.ToLower("ABC") == "abc") // true

	pl(strings.Trim(" abc ", " ") == "abc") // true

	pl(strings.Count("abcaab", "ab") == 2) // true

	pl(strings.Index("abc", "bc") == 1) // true

	pl(strings.Join([]string{"a", "and", "b"}, " ") == "a and b") // true

	// split into slice
	pl(strings.Split("a b c", " ")) // [a b c]

	pl(strings.Replace("This is Mike", "Mike", "Peter", -1))

	c := "This is Mike"

	pl(strings.Join([]string{c[:8], string('😂'), c[8:]}, ""))

	var b strings.Builder
	for i := 3; i >= 1; i-- {
		fmt.Fprintf(&b, "%d...", i)
	}

	b.WriteString("ignition")
	fmt.Println(b.String())

	r := strings.NewReplacer("<", "&lt;", ">", "&gt;")
	fmt.Println(r.Replace("This is <b>HTML</b>!"))
}

func test_basic() {

	var a = "abc and ♥"

	fmt.Println(a)

	var b = "can't do \n \"thing\" "

	fmt.Println(b)

	/*
	   \a → U+0007 alert or bell
	   \b → U+0008 backspace
	   \f → U+000C form feed
	   \n → U+000A line feed or newline
	   \r → U+000D carriage return
	   \t → U+0009 horizontal tab
	   \v → U+000b vertical tab
	   \\ → U+005c backslash
	   \" → U+0022 double quote
	   \ooo → o is octal digit.
	   \xhh → a byte. h here is a hexadecimal digit.
	   \uhhhh → a Unicode character whose codepoint can be expressed in 4 hexadecimal digits. (pad 0 in front)
	   \Uhhhhhhhh → a Unicode character whose codepoint can be expressed in 8 hexadecimal digits. (pad 0 in front)
	*/

	fmt.Printf("%v\n", "A" == "\x41")       // true
	fmt.Printf("%v\n", "♥" == "\u2665")     // true
	fmt.Printf("%v\n", "😂" == "\U0001f602") // true

	// If you don't want backslash to have special meaning, use ` (U+60: GRAVE ACCENT) to quote the string.
	// var c = 'this is rough string'

	var c = "abc"
	// s[n] → returns the nth byte of string s. The return value's type is unit8. (unit8 is an alias of byte)
	fmt.Printf("%#v\n", c[0]) // 0x61
	fmt.Printf("%#v\n", c[1]) // 0x62
	fmt.Printf("%#v\n", c[2]) // 0x63

	// When you use a string index, e.g. "abc"[0], the value is a byte.
	// You may print it as hexadecimal, or integer (unicode codepoint), or as a char.

	fmt.Printf("%#v\n", c[0]) // as hexadecimal 0x61
	fmt.Printf("%d\n", c[0])  // as integer/codepoint 97
	fmt.Printf("%q\n", c[0])  // as char 'a'

	var y = "👍"
	// utf8 encoding for thumb up char emoji 👍 is 4 bytes: #xF0 #x9F #x91 #x8D

	fmt.Printf("%#v\n", y[0]) // 0xf0
	fmt.Printf("%d\n", y[0])  // 240
	fmt.Printf("%q\n", y[0])  // 'ð'

	// SubString
	// s[n:m] returns a substring of s from index n to m (excluding m). The return value's type is string.

	var x = "012345"

	// substring
	fmt.Printf("%#v\n", x[2:3]) // "2"

	fmt.Printf("%#v\n", x[2:4]) // "23"

	fmt.Printf("%#v\n", x[2:2]) // ""

	// Remember, string is a sequence of bytes.
	// So, if you have non-ASCII unicode in string, arbitrary index range may create a string that's not a sequence of characters.
	const x1 = "♥♥♥"

	fmt.Printf("%#v\n", x1[2:4]) // "\xa5\xe2"

	// Length (Number of Bytes)
	// len(string) → returns the number of bytes in string.

	fmt.Printf("%v\n", len("abc")) // 3
	fmt.Printf("%v\n", len("ab♥")) // 5

	// Join String
	// Use + to join string. e.g.
	fmt.Printf("%v\n", "a"+"b")     // ab
	fmt.Printf("%v\n", "abc"+"def") // abcdef

	// Embed Expression in String?
	// There is no embeding expression in string. (as in Ruby or JavaScript)
	// The closest is this:
	var name = "John"
	var age = 30

	var s = fmt.Sprintf("Name: %v, Age: %v", name, age)

	fmt.Println(s) // Name: John, Age: 30

	// Find Replace
	// Use the regex package.
	// Print String: Bytes vs Characters
	// Because string is byte sequence, sometimes you want to print them as hexadecimal to see the bytes. Other times you want to print them as characters.

	// The fmt.Printf function has several verbs to help.

	// %s → the uninterpreted bytes of the string or slice. If string contain arbitrary bytes or non-printable characters, this can cause problem in output.
	// %q → output in golang string syntax, using backslash escape sequence for non-printable characters. (example: emoji will be printed as is)
	// %+q → output in golang string syntax, using backslash escape for anything that's not printable ASCII. (example: emoji will be escaped)
	// % x → hexadecimal, with space between each 2 digits. (Every 2 hexadecimal is a byte) This is best if you want to see raw bytes. e.g. you want to see how the string is encoded in utf8.
	x = "♥\t😂" // with a tab (U+0009) in middle

	fmt.Printf("%s\n", x)  // ♥ 😂
	fmt.Printf("%q\n", x)  // "♥\t😂"
	fmt.Printf("%+q\n", x) // "\u2665\t\U0001f602"
	fmt.Printf("% x\n", x) // e2 99 a5 09 f0 9f 98 82

	// turn the string into rune slice, then print it with %U
	fmt.Printf("%U\n", []rune(x)) // [U+2665 U+0009 U+1F602]

	// change str value
	var cw = "This is legend"
	fmt.Print("%s \n", cw)

	// Strings are immutable in Go
	// cw[0] = 'A'
	fmt.Print("%s \n", cw)
}
