package function

import "fmt"

func fib() func() int {
	a, b := 0, 1
	return func() int {
		a, b = b, a+b
		return a
	}
}

// Fib ...
func Fib() {
	f := fib()
	var sum int
	for i := 0; i < 100; i++ {
		sum = f()
	}
	fmt.Printf("Fib(100):%+v\n", sum)
}

// Add ...
func Add() func(int, int) int {
	base := 100
	foo := func(a, b int) int {
		return base + a + b
	}
	return foo
}

func calc(base int) (func(int) int, func(int) int) {

	fmt.Printf("%p\n", &base)
	add := func(i int) int {
		fmt.Printf("%p\n", &base)
		base += i
		return base
	}

	sub := func(i int) int {
		fmt.Printf("%p\n", &base)
		base -= i
		return base
	}

	return add, sub
}

// Calc ...
func Calc() {
	f1, f2 := calc(100)

	fmt.Println(f1(1), f2(2)) //执行顺序：f1 f2 println
	fmt.Println(f1(3), f2(4))
	fmt.Println(f1(5), f2(6))
	fmt.Println(f1(7), f2(8))
}
