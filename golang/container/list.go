package container

import (
	"container/list"
	"fmt"
)

// User ...
type User struct {
	name string
	age  int
}

// Exam_List ...
func ExamList() {
	link := list.New()

	user := User{"alice", 10}

	for i := 0; i <= 10; i++ {
		user.age++
		link.PushBack(user)
	}

	for p := link.Front(); p != link.Back(); p = p.Next() {
		user := p.Value.(User)
		if user.age == 15 {
			q := p
			p = p.Next()
			link.Remove(q)
		}
		fmt.Printf("User:%+v\n", p.Value)
	}

}
