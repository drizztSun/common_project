package main

import (
	"fmt"
	"sort"
	"math"
)

type PersonInfo struct {
	Name string
	Age int
}

type ByAge []PersonInfo

func (a ByAge) Len() int { return len(a)}
func (a ByAge) Less(i, j int) bool { return a[i].Age < a[j].Age }
func (a ByAge) Swap(i, j int) { a[i], a[j] = a[j], a[i] }

// test_sort_basic
func test_sort_basic() {
	persons := ByAge {
		{"Tom", 19},
		{"Peter", 20},
		{"Mike", 13},
	}

	fmt.Println(persons)

	sort.Sort(persons)

	fmt.Println(persons)

	sort.Slice(persons, func(i, j int) bool {
		return persons[i].Age < persons[j].Age
	})

	fmt.Println(persons)
}

// A couple of type definitions to make the units clear.
type earthMass float64
type au float64

// A Planet defines the properties of a solar system object.
type Planet struct {
	name     string
	mass     earthMass
	distance au
}

// By is the type of a "less" function that defines the ordering of its Planet arguments.
type By func(p1, p2 *Planet) bool

// Sort is a method on the function type, By, that sorts the argument slice according to the function.
func (by By) Sort(planets []Planet) {
	ps := &planetSorter{
		planets: planets,
		by:      by, // The Sort method's receiver is the function (closure) that defines the sort order.
	}
	sort.Sort(ps)
}

// planetSorter joins a By function and a slice of Planets to be sorted.
type planetSorter struct {
	planets []Planet
	by      func(p1, p2 *Planet) bool // Closure used in the Less method.
}

// Len is part of sort.Interface.
func (s *planetSorter) Len() int {
	return len(s.planets)
}

// Swap is part of sort.Interface.
func (s *planetSorter) Swap(i, j int) {
	s.planets[i], s.planets[j] = s.planets[j], s.planets[i]
}

// Less is part of sort.Interface. It is implemented by calling the "by" closure in the sorter.
func (s *planetSorter) Less(i, j int) bool {
	return s.by(&s.planets[i], &s.planets[j])
}

// test_sort_sortkeys
func test_sort_sortkeys() {
	
	var planets = []Planet{
		{"Mercury", 0.055, 0.4},
		{"Venus", 0.815, 0.7},
		{"Earth", 1.0, 1.0},
		{"Mars", 0.107, 1.5},
	}

	// Closures that order the Planet structure.
	name := func(p1, p2 *Planet) bool {
		return p1.name < p2.name
	}
	mass := func(p1, p2 *Planet) bool {
		return p1.mass < p2.mass
	}
	distance := func(p1, p2 *Planet) bool {
		return p1.distance < p2.distance
	}
	decreasingDistance := func(p1, p2 *Planet) bool {
		return distance(p2, p1)
	}
	
	// Sort the planets by the various criteria.
	By(name).Sort(planets)
	fmt.Println("By name:", planets)

	By(mass).Sort(planets)
	fmt.Println("By mass:", planets)

	By(distance).Sort(planets)
	fmt.Println("By distance:", planets)

	By(decreasingDistance).Sort(planets)
	fmt.Println("By decreasing distance:", planets)	
}

// A Change is a record of source code changes, recording user, language, and delta size.
type Change struct {
	user     string
	language string
	lines    int
}

type lessFunc func(p1, p2 *Change) bool

// multiSorter implements the Sort interface, sorting the changes within.
type multiSorter struct {
	Changes []Change
	less []lessFunc
}

// Sort sorts the argument slice according to the less functions passed to OrderedBy.
func (ms *multiSorter) Sort(changes []Change) {
	ms.Changes = changes
	sort.Sort(ms)
} 

// OrderedBy returns a Sorter that sorts using the less functions, in order.
// Call its Sort method to sort the data.
func OrderedBy(less ...lessFunc) *multiSorter {
	return &multiSorter{ less: less }
}

// Len is part of sort.Interface.
func (ms *multiSorter) Len() int {
	return len(ms.Changes)
}

// Swap is part of sort.Interface.
func (ms *multiSorter) Swap(i, j int) {
	ms.Changes[i], ms.Changes[j] = ms.Changes[j], ms.Changes[i]
}

// Less is part of sort.Interface. It is implemented by looping along the
// less functions until it finds a comparison that discriminates between
// the two items (one is less than the other). Note that it can call the
// less functions twice per call. We could change the functions to return
// -1, 0, 1 and reduce the number of calls for greater efficiency: an
// exercise for the reader.
func (ms *multiSorter) Less(i, j int) bool {
	p, q := &ms.Changes[i], &ms.Changes[j]
	// Try all but the last comparison.
	var k = 1
	for k = 0; k < len(ms.less) - 1; k++ {
		less := ms.less[k]
		switch {		
		case less(p, q):
			// p < q, so we have a decision.
			return true			
		case less(q, p):
			// p > q, so we have a decision.
			return false
		}
		// p == q; try the next comparison.
	}
	// All comparisons to here said "equal", so just return whatever
	// the final comparison reports.
	return ms.less[k](p, q)
}

func test_sort_multikeys() {
	var changes = []Change{
		{"gri", "Go", 100},
		{"ken", "C", 150},
		{"glenda", "Go", 200},
		{"rsc", "Go", 200},
		{"r", "Go", 100},
		{"ken", "Go", 200},
		{"dmr", "C", 100},
		{"r", "C", 150},
		{"gri", "Smalltalk", 80},
	}
	
	// Closures that order the Change structure.
	user := func(c1, c2 *Change) bool {
		return c1.user < c2.user
	}
	language := func(c1, c2 *Change) bool {
		return c1.language < c2.language
	}
	increasingLines := func(c1, c2 *Change) bool {
		return c1.lines < c2.lines
	}
	decreasingLines := func(c1, c2 *Change) bool {
		return c1.lines > c2.lines // Note: > orders downwards.
	}

	// Simple use: Sort by user.
	OrderedBy(user).Sort(changes)
	fmt.Println("By user:", changes)

	// More examples.
	OrderedBy(user, increasingLines).Sort(changes)
	fmt.Println("By user,<lines:", changes)

	OrderedBy(user, decreasingLines).Sort(changes)
	fmt.Println("By user,>lines:", changes)

	OrderedBy(language, increasingLines).Sort(changes)
	fmt.Println("By language,<lines:", changes)

	OrderedBy(language, increasingLines, user).Sort(changes)
	fmt.Println("By language,<lines,user:", changes)
}




type Grams int

func (m Grams) String() string {
	return fmt.Sprintf("%d g", int(m))
}

type Organ struct {
	Name string
	Weight Grams
}

type Organs []*Organ

func (s Organs) Len() int {
	return len(s)
}

func (s Organs) Swap(i, j int) {
	s[i], s[j] = s[j], s[i]
}

// ByName implements sort.Interface by providing Less and using the Len and
// Swap methods of the embedded Organs value.
type ByName struct {
	Organs
}

func (n ByName) Less(i, j int) bool {
	return n.Organs[i].Name < n.Organs[j].Name
}

// ByWeight implements sort.Interface by providing Less and using the Len and
// Swap methods of the embedded Organs value.
type ByWeight struct {
	Organs
}

func (w ByWeight) Less(i, j int) bool {
	return w.Organs[i].Weight < w.Organs[j].Weight
}


func printOrgans(s []*Organ) {
	for _, o := range s {
		fmt.Printf("%-8s (%v)\n", o.Name, o.Weight)
	}
}

func test_sort_sortwrapper() {

	s := []*Organ{
		{"brain", 1340},
		{"heart", 290},
		{"liver", 1494},
		{"pancreas", 131},
		{"prostate", 62},
		{"spleen", 162},
	}

	sort.Sort(ByWeight{s})
	fmt.Println("Organs by weight:")
	printOrgans(s)

	sort.Sort(ByName{s})
	fmt.Println("Organs by name:")
	printOrgans(s)
}


func test_sort_basic_func() {

	// sort.Strings
	{
		s := []string{"Go", "Bravo", "Gopher", "Alpha", "Grin", "Delta"}
		sort.Strings(s)
		fmt.Println(s)

		// sort.StringsAreSorted
		fmt.Println("s isSorted : ", sort.StringsAreSorted(s))
	}

	{
		s := []int{5, 2, 6, 3, 1, 4} // unsorted
		sort.Ints(s)
		fmt.Println(s)

		// IntsAreSorted 
		fmt.Println("ages is sorted : ", sort.IntsAreSorted(s))
	}

	{
		s := []float64{5.2, -1.3, 0.7, -3.8, 2.6} // unsorted
		sort.Float64s(s)
		fmt.Println(s) // [-3.8 -1.3 0.7 2.6 5.2]
		// Float64sAreSorted
		fmt.Println("Distance are sorted : ", sort.Float64sAreSorted(s))
	
		s = []float64{math.Inf(1), math.NaN(), math.Inf(-1), 0.0} // unsorted
		sort.Float64s(s)
		fmt.Println(s) // [NaN -Inf 0 +Inf]
		// Float64sAreSorted
		fmt.Println("Distance are sorted : ", sort.Float64sAreSorted(s))
	}


	{
		a := []int{1, 3, 6, 10, 15, 21, 28, 36, 45, 55}
		x := 6
	
		i := sort.Search(len(a), func(i int) bool { return a[i] >= x })
		// found 6 at index 2 in [1 3 6 10 15 21 28 36 45 55]

		if i < len(a) && a[i] == x {
			fmt.Printf("found %d at index %d in %v\n", x, i, a)
		} else {
			fmt.Printf("%d not found in %v\n", x, a)
		}

	}

	{
		a := []int{55, 45, 36, 28, 21, 15, 10, 6, 3, 1}
		x := 6
	
		i := sort.Search(len(a), func(i int) bool { return a[i] <= x })
		if i < len(a) && a[i] == x {
			fmt.Printf("found %d at index %d in %v\n", x, i, a)
		} else {
			fmt.Printf("%d not found in %v\n", x, a)
		}
	}

	{
		// sort.Slice
		people := []struct {
			Name string
			Age  int
		}{
			{"Gopher", 7},
			{"Alice", 55},
			{"Vera", 24},
			{"Bob", 75},
		}
		sort.Slice(people, func(i, j int) bool { return people[i].Name < people[j].Name })
		fmt.Println("By name:", people)
	
		sort.Slice(people, func(i, j int) bool { return people[i].Age < people[j].Age })
		fmt.Println("By age:", people)
	}
	
	// StringSlice (Increasing order)
	names := sort.StringSlice{"TOM", "PETER", "MICHAEL", "Messi", "ada"}
	sort.Sort(names)
	fmt.Println("names : ", names) // [MICHAEL Messi PETER TOM ada]

	// IntSlice (Increasing order)
	ages := sort.IntSlice{100, 1, 2, 3, 4, 5, 6}
	sort.Sort(ages)
	fmt.Println("Ages : ", ages) //  [1 2 3 4 5 6 100]

	// Float64Slice (Increasing order)
	distances := sort.Float64Slice{2.2, 3.3, 4.4, 4.5, 3.4, 6.0}
	sort.Sort(distances)
	fmt.Println("Distances : ", distances) // [2.2 3.3 3.4 4.4 4.5 6]

	fmt.Println("names sorted : ", sort.IsSorted(names))
	fmt.Println("ages sorted : ", sort.IsSorted(ages))
	fmt.Println("distances sorted : ", sort.IsSorted(distances))

	{
		// Search uses binary search to find and return the smallest index i in [0, n) at which f(i) is true
		a := []int{1, 3, 6, 10, 15, 21, 28, 36, 45, 55}
		x := 6
	
		// found 6 at index 2 in [1 3 6 10 15 21 28 36 45 55]
		i := sort.Search(len(a), func(i int) bool { return a[i] >= x })
		if i < len(a) && a[i] == x {
			fmt.Printf("found %d at index %d in %v\n", x, i, a)
		} else {
			fmt.Printf("%d not found in %v\n", x, a)
		}
	}

	{
		a := []int{55, 45, 36, 28, 21, 15, 10, 6, 3, 1}
		x := 6
		// found 6 at index 7 in [55 45 36 28 21 15 10 6 3 1]
		i := sort.Search(len(a), func(i int) bool { return a[i] <= x })
		if i < len(a) && a[i] == x {
			fmt.Printf("found %d at index %d in %v\n", x, i, a)
		} else {
			fmt.Printf("%d not found in %v\n", x, a)
		}
	}

}

func test_sort() {

	test_sort_basic_func()

	test_sort_basic()

	test_sort_sortwrapper() 

}
