package channel

import (
	"testing"
)

func TestExample1(t *testing.T) {
	tests := []struct {
		name string
	}{
		// TODO: Add test cases.
		{"TestExample1:"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example1()
		})
	}
}

func TestExample2(t *testing.T) {
	tests := []struct {
		name string
	}{
		// TODO: Add test cases.
		{"TestExample2:"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example2()
		})
	}
}

func TestExample3(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"TestExample3  :"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example3()
		})
	}
}

func TestExample4(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"TestExample4:"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example4()
		})
	}
}

func TestExample5(t *testing.T) {
	tests := []struct {
		name string
	}{
		{"TestExample5:"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			Example5()
		})
	}
}
