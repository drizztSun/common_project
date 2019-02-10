package main

import (
	"fmt"
	"strings"
	"unicode"
)

func Test_strings() {

	test_strings_reader()

	test_strings_build()
}

func test_strings_build() {
	var b strings.Builder
	b.Grow(20)

	for i := 3; i >= 1; i-- {
		fmt.Fprintf(&b, "%d ...", i)
	}

	b.WriteString("ignition")

	fmt.Printf("b len = %d, %s", b.Len(), b.String())

	b.Write([]byte("  abc   "))
	b.WriteByte('d')
	b.WriteByte('e')
	b.WriteByte('f')

	b.WriteRune('😂')

	fmt.Printf("b len = %d, %s\n", b.Len(), b.String())

	b.Reset()

	fmt.Printf("b len = %d, %s\n", b.Len(), b.String())
}

func test_strings_reader() {

	// A Reader implements the io.Reader, io.ReaderAt, io.Seeker, io.WriterTo, io.ByteScanner, and io.RuneScanner interfaces by reading from a string.

	b := strings.NewReader("3 ...2 ...1 ...ignition  abc   def😂")

	fmt.Printf("b len = %d, size = %d \n", b.Len(), b.Size())

	c := make([]byte, 10)
	n, err := b.Read(c)
	if err == nil {
		fmt.Println(n, string(c))
	}

	n, err = b.ReadAt(c, 3)
	if err == nil {
		fmt.Println(n, string(c))
	}

	fmt.Println(b.ReadByte())

	b.Seek(35, 0)
	fmt.Println(b.ReadRune())

	b.Reset("abcdefg")

	fmt.Println(b.Len())
}

func test_strings() {

	fmt.Println(strings.Compare("a", "b")) // -1
	fmt.Println(strings.Compare("a", "a")) // 0
	fmt.Println(strings.Compare("b", "a")) // 1

	fmt.Println(strings.Contains("seafood", "foo")) // true
	fmt.Println(strings.Contains("seafood", "bar")) // false
	fmt.Println(strings.Contains("seafood", ""))    // true
	fmt.Println(strings.Contains("", ""))           // true

	fmt.Println(strings.ContainsAny("team", "i"))        // false
	fmt.Println(strings.ContainsAny("failure", "u & i")) // true
	fmt.Println(strings.ContainsAny("foo", ""))          // false
	fmt.Println(strings.ContainsAny("", ""))             // false

	// Finds whether a string contains a particular Unicode code point.
	// The code point for the lowercase letter "a", for example, is 97.
	fmt.Println(strings.ContainsRune("aardvark", 97)) // true
	fmt.Println(strings.ContainsRune("timeout", 97))  // false

	fmt.Println(strings.Count("cheese", "e")) // 3
	fmt.Println(strings.Count("five", ""))    // 5 before & after each rune

	fmt.Println(strings.EqualFold("Go", "go")) // true

	fmt.Printf("Fields are: %q", strings.Fields("  foo bar  baz   ")) // Fields are: ["foo" "bar" "baz"]

	f := func(c rune) bool {
		return !unicode.IsLetter(c) && !unicode.IsNumber(c)
	}
	fmt.Printf("Fields are: %q", strings.FieldsFunc("  foo1;bar2,baz3...", f)) // Fields are: ["foo1" "bar2" "baz3"]

	fmt.Println(strings.HasPrefix("Gopher", "Go")) // true
	fmt.Println(strings.HasPrefix("Gopher", "C"))  // false
	fmt.Println(strings.HasPrefix("Gopher", ""))   // true

	fmt.Println(strings.HasSuffix("Amigo", "go"))  // true
	fmt.Println(strings.HasSuffix("Amigo", "O"))   // false
	fmt.Println(strings.HasSuffix("Amigo", "Ami")) // false
	fmt.Println(strings.HasSuffix("Amigo", ""))    // true

	fmt.Println(strings.Index("chicken", "ken")) // 4
	fmt.Println(strings.Index("chicken", "dmr")) // -1

	fmt.Println(strings.IndexAny("chicken", "aeiouy")) // 2
	fmt.Println(strings.IndexAny("crwth", "aeiouy"))   // -1

	fmt.Println(strings.IndexByte("golang", 'g'))  // 0
	fmt.Println(strings.IndexByte("gophers", 'h')) // 3
	fmt.Println(strings.IndexByte("golang", 'x'))  // -1

	f = func(c rune) bool {
		return unicode.Is(unicode.Han, c)
	}
	fmt.Println(strings.IndexFunc("Hello, 世界", f))    // 7
	fmt.Println(strings.IndexFunc("Hello, world", f)) // -1

	fmt.Println(strings.IndexRune("chicken", 'k')) // 4
	fmt.Println(strings.IndexRune("chicken", 'd')) // -1

	fmt.Println(strings.Join([]string{"foo", "bar", "baz"}, ", ")) // foo, bar, baz

	fmt.Println(strings.Index("go gopher", "go"))         // 0
	fmt.Println(strings.LastIndex("go gopher", "go"))     // 3
	fmt.Println(strings.LastIndex("go gopher", "rodent")) // -1

	fmt.Println(strings.LastIndexAny("go gopher", "go"))     // 4
	fmt.Println(strings.LastIndexAny("go gopher", "rodent")) // 8
	fmt.Println(strings.LastIndexAny("go gopher", "fail"))   // -1

	fmt.Println(strings.LastIndexByte("Hello, world", 'l')) // 10
	fmt.Println(strings.LastIndexByte("Hello, world", 'o')) // 8
	fmt.Println(strings.LastIndexByte("Hello, world", 'x')) // -1

	fmt.Println(strings.LastIndexFunc("go 123", unicode.IsNumber)) // 5
	fmt.Println(strings.LastIndexFunc("123 go", unicode.IsNumber)) // 2
	fmt.Println(strings.LastIndexFunc("go", unicode.IsNumber))     // -1

	rot13 := func(r rune) rune {
		switch {
		case r >= 'A' && r <= 'Z':
			return 'A' + (r-'A'+13)%26
		case r >= 'a' && r <= 'z':
			return 'a' + (r-'a'+13)%26
		}
		return r
	}
	fmt.Println(strings.Map(rot13, "'Twas brillig and the slithy gopher...")) // 'Gjnf oevyyvt naq gur fyvgul tbcure...

	fmt.Println("ba" + strings.Repeat("na", 2)) // banana

	fmt.Println(strings.Replace("oink oink oink", "k", "ky", 2))      // oinky oinky oink
	fmt.Println(strings.Replace("oink oink oink", "oink", "moo", -1)) // moo moo moo

	fmt.Printf("%q\n", strings.Split("a,b,c", ","))                        // ["a" "b" "c"]
	fmt.Printf("%q\n", strings.Split("a man a plan a canal panama", "a ")) // ["" "man " "plan " "canal panama"]
	fmt.Printf("%q\n", strings.Split(" xyz ", ""))                         // [" " "x" "y" "z" " "]
	fmt.Printf("%q\n", strings.Split("", "Bernardo O'Higgins"))            // [""]

	fmt.Printf("%q\n", strings.SplitAfter("a,b,c", ",")) // ["a," "b," "c"]

	fmt.Printf("%q\n", strings.SplitAfterN("a,b,c", ",", 2)) // ["a," "b,c"]

	fmt.Printf("%q\n", strings.SplitN("a,b,c", ",", 2)) // ["a" "b,c"]
	z := strings.SplitN("a,b,c", ",", 0)
	fmt.Printf("%q (nil = %v)\n", z, z == nil) // [] (nil = true)

	fmt.Println(strings.Title("her royal highness")) // Her Royal Highness

	fmt.Println(strings.ToLower("Gopher")) // gopher

	fmt.Println(strings.ToLowerSpecial(unicode.TurkishCase, "Önnek İş")) // önnek iş

	fmt.Println(strings.ToTitle("loud noises")) // LOUD NOISES
	fmt.Println(strings.ToTitle("хлеб"))        // ХЛЕБ

	fmt.Println(strings.ToTitleSpecial(unicode.TurkishCase, "dünyanın ilk borsa yapısı Aizonai kabul edilir")) // DÜNYANIN İLK BORSA YAPISI AİZONAİ KABUL EDİLİR

	fmt.Println(strings.ToUpper("Gopher")) // GOPHER

	fmt.Println(strings.ToUpperSpecial(unicode.TurkishCase, "örnek iş")) // ÖRNEK İŞ

	fmt.Print(strings.Trim("¡¡¡Hello, Gophers!!!", "!¡")) // Hello, Gophers

	fmt.Print(strings.TrimFunc("¡¡¡Hello, Gophers!!!", func(r rune) bool {
		return !unicode.IsLetter(r) && !unicode.IsNumber(r)
	})) // Hello, Gophers

	fmt.Print(strings.TrimLeft("¡¡¡Hello, Gophers!!!", "!¡")) // Hello, Gophers!!!

	fmt.Print(strings.TrimLeftFunc("¡¡¡Hello, Gophers!!!", func(r rune) bool {
		return !unicode.IsLetter(r) && !unicode.IsNumber(r)
	})) // Hello, Gophers!!!

	var s = "¡¡¡Hello, Gophers!!!"
	s = strings.TrimPrefix(s, "¡¡¡Hello, ")
	s = strings.TrimPrefix(s, "¡¡¡Howdy, ")
	fmt.Print(s) // Gophers!!!

	fmt.Print(strings.TrimRight("¡¡¡Hello, Gophers!!!", "!¡")) // ¡¡¡Hello, Gophers

	fmt.Print(strings.TrimRightFunc("¡¡¡Hello, Gophers!!!", func(r rune) bool {
		return !unicode.IsLetter(r) && !unicode.IsNumber(r)
	})) // ¡¡¡Hello, Gophers

	fmt.Println(strings.TrimSpace(" \t\n Hello, Gophers \n\t\r\n")) // Hello, Gophers

	s = "¡¡¡Hello, Gophers!!!"
	s = strings.TrimSuffix(s, ", Gophers!!!")
	s = strings.TrimSuffix(s, ", Marmots!!!")
	fmt.Print(s) // ¡¡¡Hello

}
