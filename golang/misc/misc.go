package misc

import "fmt"

func Example() {

	s := "helloworld"
	for _, v := range s {
		fmt.Printf("%+v\n", v)
		fmt.Printf("%+v\n", string(v))
	}

}
