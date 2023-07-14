package struct0

import "fmt"

type Circle struct {
	x      int
	y      int
	Radius int
}

func (c *Circle) XY() (int, int) {
	return c.x, c.y
}

func Example1() {
	var c Circle = Circle{
		x:      100,
		y:      100,
		Radius: 50, // 注意这里的逗号不能少
	}
	fmt.Printf("%+v\n", c)
	fmt.Printf("x:%+v\n", c.x)
	fmt.Printf("y:%+v\n", c.y)

	x, y := c.XY()
	fmt.Printf("x:%+v, y:%+v\n", x, y)
}

type People struct {
	name string
}

func (p *People) Name() {
	fmt.Printf("name:%+v\n", p.name)
}

type Man struct {
	People
	age int
}

func (m *Man) Age() {
	fmt.Printf("age:%+v\n", m.age)
}

func Example2() {
	m := Man{People{"alice"}, 18}
	m.Name() //方法继承
	m.Age()
	fmt.Printf("name:%+v\n", m.name) //字段继承
	fmt.Printf("age:%+v\n", m.age)

}

type person struct{}

func (p *person) speak() {
	fmt.Println("speak in person")
}

func Example3() {
	a := struct {
		person
		a int
	}{a: 123}
	a.speak()
	a.person.speak()

}
