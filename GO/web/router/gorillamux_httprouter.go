package router

import (
	"fmt"
	"net/http"

	"github.com/gorilla/mux"
)

func contact(w http.ResponseWriter, r *http.Request) {

	w.Header().Set("Content-Type", "text/html")

	fmt.Fprint(w, "To get in touch, please send a email to <a href=\"freesssbrd@gmail.com\">support me</a>")
}

func home(w http.ResponseWriter, r *http.Request) {

	w.Header().Set("Content-Type", "text/html")

	fmt.Fprint(w, "<h1> Welcome to my GO web site </h1>")
}

func faq(w http.ResponseWriter, r *http.Request) {

	w.Header().Set("Content-Type", "text/html")

	fmt.Fprint(w, "<h1> Frequently Asked Questins </h1> <p> Here is a list of questions that our users commonly ask. </p>")
}

func notFound(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "text/html")
	w.WriteHeader(http.StatusNotFound)
	fmt.Fprint(w, "<h1> sorry, but we couldn't find the page you were looking for </h1>")
}

func GorillaMux_httpRouter(host string) {

	r := mux.NewRouter()
	r.HandleFunc("/", home)
	r.HandleFunc("/contact", contact)
	r.HandleFunc("/faq", faq)
	r.NotFoundHandler = http.HandlerFunc(notFound)

	http.ListenAndServe(host+":3000", r)

}
