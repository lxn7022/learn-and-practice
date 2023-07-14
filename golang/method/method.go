package method

import "fmt"

// Age and int are two distinct types. We can't declare
// methods for int and *int, but can for Age and *Age.
type Age int

func Increase(age *Age) {
	*age++
}

func (age *Age) Increase() {
	*age++
}

func (age Age) LargerThan(a Age) bool {
	return age > a
}

func (age *Age) IsNil() bool {
	return age == nil
}

// Receiver of custom defined function type.
type FilterFunc func(in int) bool

func (ff FilterFunc) Filte(in int) bool {
	return ff(in)
}

// Receiver of custom defined map type.
type StringSet map[string]struct{}

func (ss StringSet) Has(key string) bool {
	_, present := ss[key]
	return present
}
func (ss StringSet) Add(key string) {
	ss[key] = struct{}{}
}
func (ss StringSet) Remove(key string) {
	delete(ss, key)
}

// Receiver of custom defined struct type.
type Book struct {
	pages int
}

func (b Book) Pages() int {
	return b.pages
}
func (b *Book) SetPages(pages int) {
	b.pages = pages
}

func Example1() {
	var book Book

	fmt.Printf("%T \n", book.Pages)       // func() int
	fmt.Printf("%T \n", (&book).SetPages) // func(int)
	// &book 有一个隐含类型。
	fmt.Printf("%T \n", (&book).Pages) // func() int

	// Call the three methods.
	(&book).SetPages(123)
	book.SetPages(123)           // 为啥这个也行了，其实这是一种语法糖，编译器会自动将book转换成它的指针类型
	fmt.Println(book.Pages())    // 123
	fmt.Println((&book).Pages()) // 123
}

func Example2() {
	_ = (StringSet(nil)).Has   // will not panic
	_ = ((*Age)(nil)).IsNil    // will not panic
	_ = ((*Age)(nil)).Increase // will not panic

	_ = (StringSet(nil)).Has("key") // will not panic
	_ = ((*Age)(nil)).IsNil()       // will not panic

	// 下面这行将会恐慌，但是不是因为函数调用导致的恐慌。
	// 原因在于方法内部调用了指针的实体
	//((*Age)(nil)).Increase()
}

func Example3() {
	var b Book
	b.SetPages(123)
	fmt.Println(b.pages) // 123
}

type Kook struct {
	pages int
}

func (b *Kook) SetPages(pages int) {
	b.pages = pages
}

func main() {
	var b Kook
	b.SetPages(123)
	fmt.Println(b.pages) // 123
}

type Books []Book

func (books Books) Modify() {
	// 对接收器底层部分的修改将体现在方法外部.
	books[0].pages = 500
	//对接收器直接部分的修改，将不会体现在方法外部
	books = append(books, Book{789})
}

func Example5() {
	var books = Books{{123}, {456}}
	books.Modify()
	fmt.Println(books) // [{500} {456}]
}

func Example6() {
	b1 := Books{{123}, {456}}
	b2 := b1[:1]
	b2 = append(b2, Book{789})
	fmt.Println(b1) //[{123} {789}]
	fmt.Println(b2) //[{123} {789}]
}

func Example7() {
	b1 := Books{{123}, {456}}
	b2 := b1[:1]
	b2 = append(b2, Book{789})
	b2 = append(b2, Book{78910})
	fmt.Println(b1) //[{123} {789}]
	fmt.Println(b2) //[{123} {789} {78910}]
}

func Example8() {
	b1 := Books{{123}, {456}}
	b2 := b1[:1]
	b2 = append(b2, Book{789}, Book{78910})
	fmt.Println(b1) //[{123} {456}]
	fmt.Println(b2) //[{123} {789} {78910}]
}

func Example9() {
	b1 := Books{{123}, {456}}
	b2 := b1[:1:1]
	b2 = append(b2, Book{789})
	b2 = append(b2, Book{78910})
	fmt.Println(b1) //[{123} {456}]
	fmt.Println(b2) //[{123} {789} {78910}]
}

type Cook Kook

func Example10() {
	k := Kook{100}
	k.SetPages(90)
	fmt.Println(k)
	c := Cook{100}
	//c.SetPages() c.SetPages undefined
	fmt.Println(c)
}
