package golangset

import (
	"fmt"

	mapset "github.com/deckarep/golang-set"
)

// Example ...
func Example() {
	kide := mapset.NewSet()
	kide.Add("xiaorui.cc")
	kide.Add("blog.xiaorui.cc")
	kide.Add("vps.xiaorui.cc")
	kide.Add("linode.xiaorui.cc")

	special := []interface{}{"Biology", "Chemistry"}
	scienceClasses := mapset.NewSetFromSlice(special)

	address := mapset.NewSet()
	address.Add("beijing")
	address.Add("nanjing")
	address.Add("shanghai")

	bonusClasses := mapset.NewSet()
	bonusClasses.Add("Go Programming")
	bonusClasses.Add("Python Programming")

	//一个并集的运算
	allClasses := kide.Union(scienceClasses).Union(address).Union(bonusClasses)
	fmt.Println(allClasses)

	//是否包含"Cookiing"
	fmt.Println(scienceClasses.Contains("Cooking")) //false

	//两个集合的差集
	fmt.Println(allClasses.Difference(scienceClasses)) //Set{Music, Automotive, Go Programming, Python Programming, Cooking, English, Math, Welding}

	//两个集合的交集
	fmt.Println(scienceClasses.Intersect(kide)) //Set{Biology}

	//有多少基数
	fmt.Println(bonusClasses.Cardinality()) //2

}

// Example2 ...
func Example2() {
	s1 := mapset.NewSet([]interface{}{1, 2, 3}...)
	s2 := mapset.NewSet([]interface{}{3, 4, 5}...)

	fmt.Printf("s1 + s2: %+v\n", s1.Union(s2))
	fmt.Printf("s1 & s2: %+v\n", s1.Intersect(s2))
	fmt.Printf("s1 - s2: %+v\n", s1.Difference(s2))
	fmt.Printf("s1 Contains 1: %+v\n", s1.Contains(1))
	fmt.Printf("s1 Contains a: %+v\n", s1.Contains("a"))

	s3 := mapset.NewSet([]interface{}{"a", "b", "c"}...)
	s4 := s1.Union(s3)
	fmt.Printf("s1 + s3: %+v\n", s4)

}

//YourType ...
type YourType struct {
	Name string
}

//ExampleIterator ...
func ExampleIterator() {
	set := mapset.NewSetFromSlice([]interface{}{
		&YourType{Name: "Alise"},
		&YourType{Name: "Bob"},
		&YourType{Name: "John"},
		&YourType{Name: "Nick"},
	})

	var found *YourType
	it := set.Iterator()

	for elem := range it.C {
		if elem.(*YourType).Name == "John" {
			found = elem.(*YourType)
			it.Stop()
		}
	}

	fmt.Printf("Found %+v\n", found)

	// Output: Found &{Name:John}
}

//ExampleIterator2 ...
func ExampleIterator2() {
	set := mapset.NewSetFromSlice([]interface{}{
		YourType{Name: "Alise"},
		YourType{Name: "Bob"},
		YourType{Name: "John"},
		YourType{Name: "Nick"},
	})

	var found YourType
	it := set.Iterator()

	for elem := range it.C {
		if elem.(YourType).Name == "John" {
			found = elem.(YourType)
			it.Stop()
		}
	}

	fmt.Printf("Found %+v\n", found)

	// Output: Found &{Name:John}

	for elem := range set.Iterator().C {
		fmt.Printf("Elem %+v\n", elem.(YourType))
	}
}
