package router

import (
	"fmt"
	"net/http"
)

func handlerFunc(w http.ResponseWriter, r *http.Request) {

	w.Header().Set("Content-Type", "text/html")

	if r.URL.Path == "/" {
		fmt.Fprint(w, "<h1> Welcome to my GO web site </h1>")
	} else if r.URL.Path == "/contact" {
		fmt.Fprint(w, "To get in touch, please send a email to <a href=\"freesssbrd@gmail.com\">support me</a>")
	} else {
		w.WriteHeader(http.StatusNotFound)
		fmt.Fprint(w, "<h1> Couldn't find the page you are looking for</h1>")
	}

}

func Standard_router(host string) {

	// register handle function for different path
	// http.HandleFunc("/", handlerFunc)
	// http has a default "ServeMux", so we create one
	mux := &http.ServeMux{}
	mux.HandleFunc("/", handlerFunc)

	// start a server to listen on a port
	//http.ListenAndServe(localhost+":3000", nil)
	http.ListenAndServe(host+":3000", mux) // nil means http will use defaultMux
}
