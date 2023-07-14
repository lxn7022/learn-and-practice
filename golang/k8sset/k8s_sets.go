package k8sset

import (
	"fmt"

	"k8s.io/apimachinery/pkg/util/sets"
)

// ExamSets ...
func ExamSets() {
	s := sets.String{}
	s.Insert("a", "b")
	s.Insert("c")
	s.Insert([]string{"d", "e"}...)
	if s.Has("a") {
		fmt.Printf("S has a: %+v\n", s)
	}
	s.Delete("a")
	if s.Has("a") {
		fmt.Printf("S has a: %+v\n", s)
	}
	s.Insert("a")
	if s.HasAll("a", "b", "d") {
		fmt.Printf("S HasAll: %+v\n", s)
	}

	s2 := sets.NewString([]string{"1", "2", "3"}...)
	s3 := s.Union(s2)
	fmt.Printf("s: %+v\n", s)
	fmt.Printf("s3: %+v\n", s3)

	for k := range s {
		fmt.Printf("elems: %+v\n", k)
	}
}

// ExamSets2 ...
func ExamSets2() {
	s1 := sets.NewInt([]int{1, 2, 3}...)
	s2 := sets.NewInt([]int{3, 4, 5}...)
	fmt.Printf("s1 + s2: %+v\n", s1.Union(s2))
	fmt.Printf("s1 & s2: %+v\n", s1.Intersection(s2))
	fmt.Printf("s1 - s2: %+v\n", s1.Difference(s2))
	fmt.Printf("s1 Has 1: %+v\n", s1.Has(1))
	fmt.Printf("s1 HasAll []int{1,2}: %+v\n", s1.HasAll([]int{1, 2}...))
	fmt.Printf("s1 HasAny []int{3,4}: %+v\n", s1.HasAny([]int{3, 4}...))
	fmt.Printf("s1 to List: %+v\n", s1.List())
}
