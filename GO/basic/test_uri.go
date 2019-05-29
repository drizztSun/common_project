package main

import (
	"fmt"
	"net/url"
	"strings"
)
/*
	The general form represented is:
	[scheme:][//[userinfo@]host][/]path[?query][#fragment]

	URLs that do not start with a slash after the scheme are interpreted as:
	scheme:opaque[?query][#fragment]
*/
func test_uri_basic() {
	
	u, err := url.Parse("http://bing.com/search?q=dotnet")

	if err != nil {
		fmt.Println("URL failed to parsed")
		return
	}

	fmt.Println("URL host : ", u.Host)
	fmt.Println("URL scheme : ", u.Scheme)
	fmt.Println("URL path : ", u.Path)
	fmt.Println("URL RawPath : ", u.RawPath)
	fmt.Println("URL RequestURI ", u.RequestURI())

	usrInfo := u.User
	fmt.Printf("UserName: %s, Password: %s\n", usrInfo.Username())
	if password, ok := usrInfo.Password(); ok {
		fmt.Println("Password : ", password)
	}
	// username[:password]
	fmt.Println("Usenameinfo, ", usrInfo)

	u.Scheme = "https"
	u.Host = "www.google.com"
	q := u.Query()
	q.Set("q", "golang")
	u.RawQuery = q.Encode()
	fmt.Println("")

	fmt.Println("url : ", u)

	// encoding url
	{
		u, err := url.Parse("https://exsample.com/foo%2fbar")
		if err != nil {
			fmt.Println("err : ", err.Error())
			return
		}
		fmt.Println("Path : ", u.Path)
		fmt.Println("RawaPath : ", u.RawPath)
		fmt.Println("URl : ", u)
	}

	// escape path
	{
		u, err := url.Parse("http://example.com/path with spaces")
		if err != nil {
			fmt.Println("Err : ", err.Error())
			return 
		}

		fmt.Println("Enscaped URL : ", u.EscapedPath())
	}

	// host name and port
	{
		u, err := url.Parse("https://example.org:8000/path")
		if err != nil {
			fmt.Println("Err : ", err.Error())
			return
		}
		fmt.Println("Host and port : ", u.Host) // example.org:8080/
		fmt.Printf("Host : %s, Port: %s\n", u.Hostname(), u.Port()) // example.org

		u, err = url.Parse("https://[2001:0db8:85a3:0000:0000:8a2e:0370:7334]:17000")
		if err != nil {
			fmt.Println("Err : ", err.Error())
			return
		}
		fmt.Println("Host and port : ", u.Host) // [2001:0db8:85a3:0000:0000:8a2e:0370:7334]:17000
		fmt.Printf("Host : %s, Port: %s\n", u.Hostname(), u.Port())  // 2001:0db8:85a3:0000:0000:8a2e:0370:7334
	}

	// IsAbs
	{
		u := url.URL{Host: "example.com", Path: "foo"}
		fmt.Println(u.IsAbs()) // false
		u.Scheme = "http"
		fmt.Println(u.IsAbs()) // true
	}

	// Parse
	{
		u, err := url.Parse("htts://exsample.org")
		if err != nil {
			fmt.Println("Err : ", err.Error())
			return
		}

		rel, err := u.Parse("/foo")
		if err != nil {
			fmt.Println("Err : ", err.Error())
			return
		}

		fmt.Println("Relative path: ", rel)

		_, err = u.Parse(":foo")
		if _, ok := err.(*url.Error); !ok {
			fmt.Println("Err : ", err.Error())
		}
	}

	// Query
	{
		u, err := url.Parse("https://example.org/?a=1&a=2&b=&=3&&&&")
		if err != nil {
			fmt.Println("Err : ", err.Error())
			return
		}

		q := u.Query()
		fmt.Println(q["a"]) // [1, 2]
		fmt.Println(q.Get("b")) // " "
		fmt.Println(q.Get("")) // 3
	}

	// RequestURI
	{
		u, err := url.Parse("https://example.org/path?foo=bar")
		if err != nil {
			fmt.Println("Err : ", err.Error())
			return
		}
		fmt.Println("RequestURI : ", u.RequestURI()) // /path?foo=bar
	}

	// ResovleReferrence
	{
		u, err := url.Parse("../../..//Search?q=donet")
		if err != nil {
			fmt.Println("Err : ", err.Error())
			return
		}

		base, err := url.Parse("http://exsample.org/xxxx")
		if err != nil {
			fmt.Println("Err : ", err.Error())
			return
		}

		fmt.Println("Combined URL : ", base.ResolveReference(u)) //http://example.com/search?q=dotnet
	}
}

func replaceHostInURl(target string, newHost string) (string, error) {

	u, err := url.Parse(target)
	if err != nil {
		fmt.Printf("Parse url err : %s", err.Error())
		return "", err
	}

	//u.Host = newHost + u.Port()
	colon := strings.IndexByte(u.Host, ':') 
	if colon == -1 { 
		u.Host = newHost
	} else {
		u.Host = newHost + u.Host[colon:]
	}

	return u.String(), nil
}

func test_uri_replace() {

	for _, v := range []struct{
		host string
		replace string
	} {
		{
			"https://www.google.com/index?q=a&c=b",
			"www.bing.com",
		},
		{
			"https://127.0.0.1/index?q=a&c=b",
			"www.yahoo.com",
		},
	} {
		link, err := replaceHostInURl(v.host, v.replace);
		if  err != nil {
			fmt.Printf("Erros : %s", err.Error())
		}
	
		fmt.Printf("Orig: %s, replace %s, Link : %s\n", v.host, v.replace, link)
	}


}

func test_uri() {

	fmt.Println("---- test_uri ---- ")

	test_uri_replace()

	//test_uri_basic()

	fmt.Println("---- test_uri ---- ")

}