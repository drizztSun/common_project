package router

import (
	"encoding/json"
	"log"
	"net/http"

	"github.com/gorilla/mux"
)

type Person struct {
	ID        string
	FristName string
	LastName  string
	Address   *Adress
}

type Adress struct {
	City  string
	State string
}

//var people []Person
type People struct {
	persons []Person
}

func (p *People) getPeople(w http.ResponseWriter, r *http.Request) {
	json.NewEncoder(w).Encode(p.persons)
}

func (p *People) getPerson(w http.ResponseWriter, r *http.Request) {
	params := mux.Vars(r)
	for _, item := range p.persons {
		if item.ID == params["id"] {
			json.NewEncoder(w).Encode(item)
			return
		}
	}
	json.NewEncoder(w).Encode(&Person{})
}

func (p *People) createPerson(w http.ResponseWriter, r *http.Request) {
	params := mux.Vars(r)
	var person Person
	_ = json.NewDecoder(r.Body).Decode(&person)
	person.ID = params["id"]
	p.persons = append(p.persons, person)
	json.NewEncoder(w).Encode(*p)
}

func (p *People) deletePerson(w http.ResponseWriter, r *http.Request) {

	params := mux.Vars(r)
	for index, item := range p.persons {
		if item.ID == params["id"] {
			p.persons = append(p.persons[:index], p.persons[index+1:]...)
			break
		}
	}
	json.NewEncoder(w).Encode(*p)
}

func testRestfulAPI() {

	r := mux.NewRouter()
	p := People{}

	r.HandleFunc("/people", p.getPeople).Methods("GET")
	r.HandleFunc("/people/{id}", p.getPerson).Methods("GET")
	r.HandleFunc("/people/{id}", p.createPerson).Methods("PUT")
	r.HandleFunc("/people/{id}", p.deletePerson).Methods("DELETE")

	log.Fatal(http.ListenAndServe(":8000", r))
}
