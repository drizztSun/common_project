package router

import (
	"encoding/json"
	"log"
	"net/http"

	"github.com/gorilla/mux"
)

// The person Type (more like an object)
type Person struct {
	ID        string   `json:"id,omitempty"`
	Firstname string   `json:"firstname,omitempty"`
	Lastname  string   `json:"lastname,omitempty"`
	Address   *Address `json:"address,omitempty"`
}
type Address struct {
	City  string `json:"city,omitempty"`
	State string `json:"state,omitempty"`
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
	p := People{[]Person{
		Person{ID: "1", Firstname: "John", Lastname: "Doe", Address: &Address{City: "City X", State: "State X"}},
		Person{ID: "2", Firstname: "Koko", Lastname: "Doe", Address: &Address{City: "City Z", State: "State Y"}}}}

	r.HandleFunc("/people", p.getPeople).Methods("GET")
	r.HandleFunc("/people/{id}", p.getPerson).Methods("GET")
	r.HandleFunc("/people/{id}", p.createPerson).Methods("PUT")
	r.HandleFunc("/people/{id}", p.deletePerson).Methods("DELETE")

	log.Fatal(http.ListenAndServe(":8000", r))
}
