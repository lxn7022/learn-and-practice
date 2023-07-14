package function

import "fmt"

type Foo func()

func (f Foo) Add(x, y int) int {
	return x + y
}
func (f Foo) Sub(x, y int) int {
	return x - y
}

func Example() {
	var f Foo = func() {}
	fmt.Printf("Foo.Add:%+v\n", f.Add(1, 2))
	fmt.Printf("Foo.Sub:%+v\n", f.Sub(5, 2))
}

type Bar struct{}

func (b Bar) Add(x, y int) int {
	return x + y
}
func (b Bar) Sub(x, y int) int {
	return x - y
}
func Example2() {
	b := Bar{}
	fmt.Printf("Bar.Add:%+v\n", b.Add(1, 2))
	fmt.Printf("Bar.Sub:%+v\n", b.Sub(5, 2))
}

type I interface {
	Add(int, int) int
	Sub(int, int) int
}

func Example3() {
	var f Foo = func() {}
	var b Bar = Bar{}
	add := func(i I, x, y int) int {
		return i.Add(x, y)
	}
	sub := func(i I, x, y int) int {
		return i.Sub(x, y)
	}
	fmt.Printf("Foo.Add:%+v\n", add(f, 1, 2))
	fmt.Printf("Foo.Sub:%+v\n", sub(f, 5, 2))
	fmt.Printf("Bar.Add:%+v\n", add(b, 1, 2))
	fmt.Printf("Bar.Sub:%+v\n", sub(b, 5, 2))
}

func Example4() {
	type Person struct {
		Name string
		Age  int
	}

	p := Person{"lark", 18}
	fmt.Printf("Name:%+v\nAge:%+v\n", p.Name, p.Age)

	p2 := struct {
		Name string
		Age  int
	}{"lark", 18}
	fmt.Printf("Name:%+v\nAge:%+v\n", p2.Name, p2.Age)
}

func Example5() {
	var s []int
	fmt.Printf("s=%#v， len=%+v,cap=%+v\n", s, len(s), cap(s))

	s1 := make([]int, 5, 5)
	fmt.Printf("s1=%#v: len=%+v,cap=%+v\n", s1, len(s1), cap(s1))

	s2 := s1[2:4]
	fmt.Printf("s2=%#v: len=%+v,cap=%+v\n", s2, len(s2), cap(s2))

	s2[0] = 3
	fmt.Printf("s1=%#v: len=%+v,cap=%+v\n", s1, len(s1), cap(s1))
	fmt.Printf("s2=%#v: len=%+v,cap=%+v\n", s2, len(s2), cap(s2))
	for i, v := range s1 {
		fmt.Printf("%+v:%+v\n", i, v)
	}
}

func Example6() {
	m := map[string]int{}
	m["aaa"] = 1
	m["bbb"] = 2
	m["ccc"] = 3
	if v, ok := m["ccc"]; ok {
		fmt.Printf("v:%+v\n", v)
	} else {
		fmt.Printf("不存在\n")
	}

	for k, v := range m {
		fmt.Printf("%+v:%+v\n", k, v)
	}

}

func Example7() {
	a := [...]int{1, 2, 3, 4, 5, 6}
	b := a[3:5]

	fmt.Printf("a:%#v\n", a)
	fmt.Printf("b:%#v\n", b)

	fmt.Printf("a=%#v: len=%+v,cap=%+v\n", a, len(a), cap(a))
	fmt.Printf("b=%#v: len=%+v,cap=%+v\n", b, len(b), cap(b))

	b[0] = 10
	fmt.Printf("a:%#v\n", a)
	fmt.Printf("b:%#v\n", b)

	b = append(b, 10, 11, 12, 13)
	fmt.Printf("a=%#v: len=%+v,cap=%+v\n", a, len(a), cap(a))
	fmt.Printf("b=%#v: len=%+v,cap=%+v\n", b, len(b), cap(b))
}

func Example8() {
	A := struct {
		a int
		b int
	}{1, 2}
	fmt.Printf("A.a:%+v,  A.b:%+v\n", A.a, A.b)
}
