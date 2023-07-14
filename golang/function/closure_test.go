package function

import (
	"fmt"
	"testing"
)

func TestFib(t *testing.T) {
	tests := []struct {
		name string
	}{
		// TODO: Add test cases.
		{"TestFib"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Fib()
		})
	}
}

func TestAdd(t *testing.T) {
	tests := []struct {
		name string
	}{
		// TODO: Add test cases.
		{"TestAdd"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			add := Add()
			fmt.Printf("Add:%+v\n", add(1, 2))
		})
	}
}

func TestCalc(t *testing.T) {
	tests := []struct {
		name string
	}{
		// TODO: Add test cases.
		{"TestCalc"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Calc()
		})
	}
}
