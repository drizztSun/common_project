package main

import (
	"fmt"
	"log"
	"strconv"
)

func Test_strconver() {

	var pln = fmt.Println
	{
		// The most common numeric conversions are Atoi (string to int) and Itoa (int to string).
		i, err := strconv.Atoi("-42")
		s := strconv.Itoa(-42)

		if err == nil {
			fmt.Println(i)
		}

		fmt.Println(s)

		v := "10"
		if s, err := strconv.Atoi(v); err == nil {
			fmt.Printf("%T, %v", s, s)
		}
	}

	{
		i := 10
		s := strconv.Itoa(i)
		fmt.Printf("%T, %v\n", s, s) // string, 10
	}

	{
		//ParseBool, ParseFloat, ParseInt, and ParseUint convert strings to values:
		b, err1 := strconv.ParseBool("true")
		fmt.Println(b, err1)

		f, err2 := strconv.ParseFloat("3.1415", 64)
		fmt.Println(f, err2)

		i, err3 := strconv.ParseInt("-42", 10, 64)
		fmt.Println(i, err3)

		u, err4 := strconv.ParseUint("42", 10, 64)
		fmt.Println(u, err4)
	}

	{
		// The parse functions return the widest type (float64, int64, and uint64),
		// but if the size argument specifies a narrower width the result can be converted to that narrower type without data loss:

		s := "2147483647" // biggest int32
		i64, err := strconv.ParseInt(s, 10, 32)
		i := int32(i64)
		fmt.Println(i, err)
	}

	{
		v := "true"
		if s, err := strconv.ParseBool(v); err == nil {
			fmt.Printf("%T, %v\n", s, s) // bool, true
		}
	}

	{
		v := "3.1415926535"
		if s, err := strconv.ParseFloat(v, 32); err == nil {
			fmt.Printf("%T, %v\n", s, s) // float64, 3.1415927410125732
		}
		if s, err := strconv.ParseFloat(v, 64); err == nil {
			fmt.Printf("%T, %v\n", s, s) // float64, 3.1415926535
		}
	}

	{
		// int64, -354634382
		// int64, -3546343826724305832
		v32 := "-354634382"
		if s, err := strconv.ParseInt(v32, 10, 32); err == nil {
			fmt.Printf("%T, %v\n", s, s)
		}
		if s, err := strconv.ParseInt(v32, 16, 32); err == nil {
			fmt.Printf("%T, %v\n", s, s)
		}

		v64 := "-3546343826724305832"
		if s, err := strconv.ParseInt(v64, 10, 64); err == nil {
			fmt.Printf("%T, %v\n", s, s)
		}
		if s, err := strconv.ParseInt(v64, 16, 64); err == nil {
			fmt.Printf("%T, %v\n", s, s)
		}
	}

	{
		// uint64, 42
		// uint64, 42
		v := "42"
		if s, err := strconv.ParseUint(v, 10, 32); err == nil {
			fmt.Printf("%T, %v\n", s, s)
		}
		if s, err := strconv.ParseUint(v, 10, 64); err == nil {
			fmt.Printf("%T, %v\n", s, s)
		}
	}

	{
		// FormatBool, FormatFloat, FormatInt, and FormatUint convert values to strings:
		pln(strconv.FormatBool(true))
		pln(strconv.FormatFloat(3.1415, 'E', -1, 64))
		pln(strconv.FormatInt(-42, 16))
		pln(strconv.FormatUint(42, 16))
	}

	{
		v := true
		s := strconv.FormatBool(v)
		fmt.Printf("%T, %v\n", s, s) // string, true
	}

	{
		v := 3.1415926535

		s32 := strconv.FormatFloat(v, 'E', -1, 32)
		fmt.Printf("%T, %v\n", s32, s32) // string, 3.1415927E+00

		s64 := strconv.FormatFloat(v, 'E', -1, 64)
		fmt.Printf("%T, %v\n", s64, s64) // string, 3.1415926535E+00
	}

	{
		v := int64(-42)

		s10 := strconv.FormatInt(v, 10)
		fmt.Printf("%T, %v\n", s10, s10) // string, -42

		s16 := strconv.FormatInt(v, 16)
		fmt.Printf("%T, %v\n", s16, s16) // string, -2a
	}

	{
		v := uint64(42)

		s10 := strconv.FormatUint(v, 10)
		fmt.Printf("%T, %v\n", s10, s10) // string, 42

		s16 := strconv.FormatUint(v, 16)
		fmt.Printf("%T, %v\n", s16, s16) // string, 2a
	}

	{
		c := strconv.IsPrint('\u263a')
		fmt.Println(c) // true

		bel := strconv.IsPrint('\007')
		fmt.Println(bel) // false
	}

	// String Conversions
	{
		// Quote and QuoteToASCII convert strings to quoted Go string literals.
		// The latter guarantees that the result is an ASCII string, by escaping any non-ASCII Unicode with \u:
		// QuoteRune and QuoteRuneToASCII are similar but accept runes and return quoted Go rune literals.
		q := strconv.Quote("Hello, 世界 😂")
		pln(q)

		q = strconv.QuoteToASCII("Hello, 世界 😂")
		pln(q)

		q = strconv.QuoteToGraphic("Hello, 世界 😂")
		pln(q)

		q = strconv.QuoteRune('😂')
		pln(q)

		q = strconv.QuoteRuneToASCII('😂')
		pln(q)

		q = strconv.QuoteRuneToGraphic('😂')
		pln(q)

	}

	{
		s := strconv.Quote(`"Fran & Freddie's Diner	☺"`)
		fmt.Println(s) // "\"Fran & Freddie's Diner\t☺\""
	}

	{
		s := strconv.QuoteToASCII(`"Fran & Freddie's Diner	☺"`)
		fmt.Println(s) // "\"Fran & Freddie's Diner\t\u263a\""
	}

	{

	}

	{
		s := strconv.QuoteRune('☺')
		fmt.Println(s) // '☺'
	}

	{
		s := strconv.QuoteRuneToASCII('☺')
		fmt.Println(s) // '\u263a'
	}

	{
		s, err := strconv.Unquote("You can't unquote a string without quotes")
		fmt.Printf("%q, %v\n", s, err) // "", invalid syntax
		s, err = strconv.Unquote("\"The string must be either double-quoted\"")
		fmt.Printf("%q, %v\n", s, err) // "The string must be either double-quoted", <nil>
		s, err = strconv.Unquote("`or backquoted.`")
		fmt.Printf("%q, %v\n", s, err)       // "or backquoted.", <nil>
		s, err = strconv.Unquote("'\u263a'") // single character only allowed in single quotes
		fmt.Printf("%q, %v\n", s, err)       // "☺", <nil>
		s, err = strconv.Unquote("'\u2639\u2639'")
		fmt.Printf("%q, %v\n", s, err) // "", invalid syntax
	}

	{
		v, mb, t, err := strconv.UnquoteChar(`\"Fran & Freddie's Diner\"`, '"')
		if err != nil {
			log.Fatal(err)
		}

		fmt.Println("value:", string(v)) // value: "
		fmt.Println("multibyte:", mb)    // fmt.Println("multibyte:", mb)
		fmt.Println("tail:", t)          // tail: Fran & Freddie's Diner\"
	}

	{
		b := []byte("bool:")
		b = strconv.AppendBool(b, true)
		fmt.Println(string(b)) // bool:true
	}

	{
		b32 := []byte("float32:")
		b32 = strconv.AppendFloat(b32, 3.1415926535, 'E', -1, 32)
		fmt.Println(string(b32)) // float32:3.1415927E+00

		b64 := []byte("float64:")
		b64 = strconv.AppendFloat(b64, 3.1415926535, 'E', -1, 64)
		fmt.Println(string(b64)) // float64:3.1415926535E+00
	}

	{
		b10 := []byte("int (base 10):")
		b10 = strconv.AppendInt(b10, -42, 10)
		fmt.Println(string(b10)) // int (base 10):-42

		b16 := []byte("int (base 16):")
		b16 = strconv.AppendInt(b16, -42, 16)
		fmt.Println(string(b16)) // int (base 16):-2a
	}

	{
		b := []byte("quote:")
		b = strconv.AppendQuote(b, `"Fran & Freddie's Diner"`)
		fmt.Println(string(b)) // quote:"\"Fran & Freddie's Diner\""
	}

	{
		b := []byte("rune:")
		b = strconv.AppendQuoteRune(b, '☺')
		fmt.Println(string(b)) // rune:'☺'
	}

	{
		b := []byte("rune (ascii):")
		b = strconv.AppendQuoteRuneToASCII(b, '☺')
		fmt.Println(string(b)) // rune (ascii):'\u263a'
	}

	{
		b := []byte("quote (ascii):")
		b = strconv.AppendQuoteToASCII(b, `"Fran & Freddie's Diner"`)
		fmt.Println(string(b)) // quote (ascii):"\"Fran & Freddie's Diner\""
	}

	{
		b10 := []byte("uint (base 10):")
		b10 = strconv.AppendUint(b10, 42, 10)
		fmt.Println(string(b10)) // uint (base 10):42

		b16 := []byte("uint (base 16):")
		b16 = strconv.AppendUint(b16, 42, 16)
		fmt.Println(string(b16)) // uint (base 16):2a
	}

	{
		str := "Not a number"
		if _, err := strconv.ParseFloat(str, 64); err != nil {
			e := err.(*strconv.NumError)
			fmt.Println("Func:", e.Func) // Func: ParseFloat
			fmt.Println("Num:", e.Num)   // Num: Not a number
			fmt.Println("Err:", e.Err)   // Err: invalid syntax
			fmt.Println(err)             // strconv.ParseFloat: parsing "Not a number": invalid syntax
		}
	}
}
